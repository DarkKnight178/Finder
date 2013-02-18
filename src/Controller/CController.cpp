/*
	CController.cpp
	Sergey Aksenov, 2013
*/

#include "CController.h"

// static
CController* CController::mInstance = nullptr;
std::once_flag CController::mInstanceFlag;


CController::CController( IModelSubject& model, CLogger* logger )
{
	mModel = &model;
	mModel->SetObserver(*this);

	mView = nullptr;

	mSearchResultsPtr = nullptr;

	mLogger = logger;

	// TODO Создавать сразу потоки для View и Model
}

CController* CController::GetInstance( IModelSubject& model, CLogger* logger )
{
	auto createInstance  = [&]() -> void 
	{ 
		if(mInstance == nullptr) mInstance = new CController(model, logger);
	};

	std::call_once(mInstanceFlag,createInstance);

	return mInstance;
}

CController::~CController()
{
	mInstance = nullptr;

	mModel->UnSetObserver();
	mModel = nullptr;

	mView = nullptr;

	mSearchResultsPtr = nullptr;

	mLogger = nullptr;
}

bool CController::Run()
{
	if(!mModel || !mView) return false;

	mView->Show();

	return true;
}

void CController::StartSearch()
{
	auto _startSearch = [&]() -> void
	{
		mView->SearchStarted();

		mModel->SetOptions(mSearchOptions);
		mModel->Start();
	};

	mSearchThread = thread(_startSearch);
}

void CController::PauseSearch()
{
	mView->SearchPaused();

	mModel->SetPause(true);
}

void CController::UnPauseSearch()
{
	mView->SearchUnPaused();

	mModel->SetPause(false);
}

void CController::StopSearch()
{
	mView->SearchDone();

	mModel->Stop();

	mSearchThread.join();
}

bool CController::GetPause() const 
{
	return mModel->GetPause();
}

void CController::SetQuery( const DString &query )
{
	std::unique_lock<std::mutex> _locker(mMutexOptions);

	mSearchOptions.SetQuery(query);
}

void CController::SetRegexQuery( const DString &regexQuery )
{
	std::unique_lock<std::mutex> _locker(mMutexOptions);

	mSearchOptions.SetQueryRegex(regexQuery);
}

void CController::AddStartDir( const DString &dir )
{
	std::unique_lock<std::mutex> _locker(mMutexOptions);

	mSearchOptions.AddStartDir(dir);
}

void CController::RemoveStartDir( const DString &dir )
{
	std::unique_lock<std::mutex> _locker(mMutexOptions);

	mSearchOptions.RemoveStartDir(dir);
}

void CController::SetSizeLimit( const SFileSize &size )
{
	std::unique_lock<std::mutex> _locker(mMutexOptions);

	mSearchOptions.Size = size;
}

void CController::SetHideFilesFlag( bool findHideFiles )
{
	std::unique_lock<std::mutex> _locker(mMutexOptions);

	mSearchOptions.HideFiles = findHideFiles;
}

void CController::SetTimeCreatedLimit( const STimePeriod &time )
{
	std::unique_lock<std::mutex> _locker(mMutexOptions);

	mSearchOptions.TimeCreated = time;
}

void CController::SetTimeModifiedLimit( const STimePeriod &time )
{
	std::unique_lock<std::mutex> _locker(mMutexOptions);

	mSearchOptions.TimeModified = time;
}

void CController::SetTimeLastAccessLimit( const STimePeriod &time )
{
	std::unique_lock<std::mutex> _locker(mMutexOptions);

	mSearchOptions.TimeLastAccess = time;
}

void CController::SetModel( IModelSubject& model )
{
	std::unique_lock<std::mutex> _locker(mMutexModel);

	mModel = &model;
}

void CController::SetView( IView& view )
{
	std::unique_lock<std::mutex> _locker(mMutexView);

	mView = &view;
}

void CController::SetLogger( CLogger* logger )
{
	std::unique_lock<std::mutex> _locker(mMutexLogger);

	mLogger = logger;
}

void CController::Update()
{
	std::unique_lock<std::mutex> _locker(mMutexResults);

	mSearchResultsPtr = mModel->GetSearchResults();

	int _lastResultID = mSearchResultsPtr->size()-1;

	if(_lastResultID < 0) goto SEARCH_DONE;

	SFileDesc* _lastResult = (*mSearchResultsPtr)[_lastResultID];

	if(_lastResult == nullptr) goto SEARCH_DONE;

	mView->AddSearchResult( *_lastResult );
	return;
	
	SEARCH_DONE:
		mSearchOptions.Default();
		mView->SearchDone();
}
