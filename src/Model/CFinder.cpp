/*
	CFinder.cpp
	Sergey Aksenov, 2013
*/

#include "CFinder.h"

// static
CFinder* CFinder::mInstance = nullptr;
std::once_flag CFinder::mInstanceFlag;



CFinder::CFinder(CLogger* logger)
{
	mPause = false;
	mStop = false;

	mObserver = nullptr;

	mInstance = this;

	mLogger = logger;
	SAFE_ADD_TO_LOG(mLogger, FG_BLACK|LOGGER_LOGIC_BACKGROUND, __T("Finder object created!\n"));
}

CFinder::~CFinder()
{
	for (auto &fileDesc : mResultFileDescs)
	{
		SAFE_DELETE(fileDesc);
	}
	mResultFileDescs.clear();

	mObserver = nullptr;

	mInstance = nullptr;

	SAFE_ADD_TO_LOG(mLogger, FG_BLACK|LOGGER_LOGIC_BACKGROUND, __T("Finder object delete(after this message)\n"));
	mLogger = nullptr;
}

CFinder* CFinder::GetInstance(CLogger* logger)
{
	auto createInstance  = [&]() -> void 
	{ 
		if(mInstance == nullptr) mInstance = new CFinder(logger);
	};

	std::call_once(mInstanceFlag,createInstance);

	return mInstance;
}

void CFinder::SetOptions( const CFindOptions& options )
{

	std::unique_lock<std::mutex> _locker(mMutexOptions);

	mOptions = options;
}

void CFinder::Start()
{
	if(mOptions.IsEmpty()) return;

	mPause = false;
	mStop = false;

	UINT _amountStartDirs = mOptions.AmountStartDirs();
	DString _currentStartDir;

	SAFE_ADD_TO_LOG(mLogger, FG_BLACK|LOGGER_LOGIC_BACKGROUND, __T("Begin search\n"));

	
	for(UINT i=0;i<_amountStartDirs;++i)
	{
		_currentStartDir = mOptions.GetStartDir(i);
		if(fs::exists(_currentStartDir) == false) continue;

		SAFE_ADD_TO_LOG(mLogger, FG_BLACK|LOGGER_LOGIC_BACKGROUND, __T("  Current start dir: ") << _currentStartDir.c_str() << __T("\n"));

		SearchFrom(_currentStartDir);
	}


	NotifyAboutEndOfSearch();

	SAFE_ADD_TO_LOG(mLogger, FG_BLACK|LOGGER_LOGIC_BACKGROUND, __T("Search done.\n"));
}

void CFinder::Stop()
{
	std::unique_lock<std::mutex> _locker(mMutexStop);

	mStop = true;
}

void CFinder::SetPause( bool pause )
{
	std::unique_lock<std::mutex> _locker(mMutexPause);

	mPause = pause;
}

bool CFinder::GetPause() const
{
	std::unique_lock<std::mutex> _locker(mMutexPause);

	return mPause;
}

void CFinder::SetObserver( IObserver& observer )
{
	std::unique_lock<std::mutex> _locker(mMutexObserver);

	mObserver = &observer;
}

void CFinder::UnSetObserver()
{
	std::unique_lock<std::mutex> _locker(mMutexObserver);

	mObserver = nullptr;
}

void CFinder::NotifyObserver() const 
{
	std::unique_lock<std::mutex> _locker(mMutexObserver);

	if(mObserver != nullptr) mObserver->Update();
}

const vector<SFileDesc*>* CFinder::GetSearchResults() const 
{
	std::unique_lock<std::mutex> _locker(mMutexResults);

	return &mResultFileDescs;
}

void CFinder::SetLogger( CLogger* logger )
{
	std::unique_lock<std::mutex> _locker(mMutexLogger);

	mLogger = logger;
}



void CFinder::SearchFrom( const DString &startDirectory )
{
	SFileDesc* _tempFileDesc = nullptr;

	bool _fileCheckStatus = false;

	bool _checkTimeModified = !mOptions.TimeModified.IsEmpty();
	bool _checkTimeCreated = !mOptions.TimeCreated.IsEmpty();
	bool _checkTimeLastAccess = !mOptions.TimeLastAccess.IsEmpty();

	bool _checkSize = !mOptions.Size.IsEmpty();

	bool _isHideFile = false;

	fs::path _filePath;

	boost::wregex _regex(mOptions.GetQuery());

	try
	{
		for ( fs::recursive_directory_iterator end, dir(startDirectory);
			dir != end; ++dir )
		{
			while (mPause && !mStop)
			{
				// empty
			}

			if(mStop)
			{
				SAFE_DELETE(_tempFileDesc);
				return;
			}			

			_fileCheckStatus = false;

			_filePath = dir->path();

			if(_tempFileDesc == nullptr) _tempFileDesc = new SFileDesc();
			else _tempFileDesc->Clear();

			// Path
			_tempFileDesc->Path = _filePath.wstring();

			// Name
			_tempFileDesc->Name = _filePath.filename().wstring();

			// Attributes
			_tempFileDesc->Attributes = GetFileAttributesW(_tempFileDesc->Path.c_str()); 


			_isHideFile = _tempFileDesc->Attributes & FILE_ATTRIBUTE_HIDDEN;

			if( (_isHideFile == mOptions.HideFiles) || (!_isHideFile && mOptions.HideFiles) )
			{
				// Разрешаем добавлять в стек дирректорию
				static_cast<fs::recursive_directory_iterator*>(&dir)->no_push(false);

				// Проверка по запросу
				_fileCheckStatus = boost::regex_match(_tempFileDesc->Name, _regex);
				if(_fileCheckStatus == false) continue;

				// Get Size
				_tempFileDesc->Size = fs::file_size(_filePath);

				// Check Size
				if(_checkSize && (!mOptions.Size.Contans(_tempFileDesc->Size)) ) continue;

				// Get Time
				GetFileTime(_tempFileDesc);

				// Check Modified Time
				if(_checkTimeModified && (!mOptions.TimeModified.Contans(_checkTimeModified)) ) continue;

				// Check Created Time
				if(_checkTimeCreated && (!mOptions.TimeCreated.Contans(_checkTimeModified)) ) continue;

				// Check Last Access Time
				if(_checkTimeLastAccess && (!mOptions.TimeLastAccess.Contans(_checkTimeModified)) ) continue;


				if(_fileCheckStatus) 
				{
					// Critical section
					std::unique_lock<std::mutex> _locker(mMutexResults);

						mResultFileDescs.push_back(_tempFileDesc);
						_tempFileDesc = nullptr;

					_locker.unlock();

					NotifyObserver();
				}
			}
			else
			{
				// Запрещаем добавлять с стек дирректорию
				if(fs::is_directory(_filePath)) static_cast<fs::recursive_directory_iterator*>(&dir)->no_push(true);

				SAFE_ADD_TO_LOG(mLogger, FG_GREEN|LOGGER_LOGIC_BACKGROUND, __T("  Skip hidden dir/file: ") << _filePath.wstring().c_str() << __T("\n"));
			}// ~if hide file
		}// ~for(boost  dir iter)

	}
	catch (boost::exception& e)
	{
		// TODO
		//SAFE_ADD_TO_LOG(mLogger, FG_RED|LOGGER_LOGIC_BACKGROUND, ((TCHAR*)boost::exception_detail::get_diagnostic_information(e, "Exeption:")) << __T("\n"));
		SAFE_ADD_TO_LOG(mLogger, FG_RED|LOGGER_LOGIC_BACKGROUND, __T("Exeption(CFinder::Find())!") << __T("\n"));
	}
	catch (...)
	{
		// TODO
		SAFE_ADD_TO_LOG(mLogger, FG_RED|LOGGER_LOGIC_BACKGROUND, __T("Exeption(CFinder::Find())!") << __T("\n"));
	}

	// TODO (просто напоминаение чтобы не забыть об удалении _tempFileDesc в catch если они поменяются)
	SAFE_DELETE(_tempFileDesc);
}


void CFinder::NotifyAboutEndOfSearch()
{
	std::unique_lock<std::mutex> _locker(mMutexResults);

		mResultFileDescs.push_back(nullptr);

	_locker.unlock();

	NotifyObserver();
}




bool CFinder::GetFileTime( SFileDesc* fileDesc )
{
	auto _from_FILETIME_to_Posix = [](const FILETIME &time) -> time_t
	{
		ULARGE_INTEGER ull;
		ull.LowPart = time.dwLowDateTime;
		ull.HighPart = time.dwHighDateTime;
		return ull.QuadPart / 10000000ULL - 11644473600ULL;
	};

	
	HANDLE _fileHandle = CreateFile(fileDesc->Path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if(_fileHandle == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile failed with %d\n", GetLastError());
		return false;
	}

	FILETIME _creation, _modified, _access;
	bool _result = ::GetFileTime(_fileHandle, &(_creation), &(_modified), &(_access));

	if(_result)
	{
		fileDesc->TimeCreatiton = _from_FILETIME_to_Posix(_creation);
		fileDesc->TimeLastAccess = _from_FILETIME_to_Posix(_access);
		fileDesc->TimeModified = _from_FILETIME_to_Posix(_modified);
	}
	
	return _result;
}
