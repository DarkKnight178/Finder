/*
	CConsoleView.cpp
	Sergey Aksenov, 2013
*/

#include "CConsoleView.h"

// static
CConsoleView* CConsoleView::mInstance = nullptr;
std::once_flag CConsoleView::mInstanceFlag;



CConsoleView::CConsoleView(IControllerObserver &controller, CLogger* logger)
{
	mController = &controller;

	mLogger = logger;

	mRun = false;
	mSearchDone = false;

	mStartButtonEnable = true;
	mPauseButtonEnable = false;
	mStopButtonEnable = false;

	// TODO Создавать поток для инпута сразу

	SAFE_ADD_TO_LOG(mLogger, FG_BLACK|LOGGER_UI_BACKGROUND, __T("ConsoleUI object created!\n"));
}

CConsoleView::~CConsoleView()
{
	mController = nullptr;

	SAFE_ADD_TO_LOG(mLogger, FG_BLACK|LOGGER_UI_BACKGROUND, __T("ConsoleUI object delete(after this message)\n"));

	mLogger = nullptr;
}

CConsoleView* CConsoleView::GetInstance(IControllerObserver &controller, CLogger* logger)
{
	auto createInstance  = [&]() -> void 
	{ 
		if(mInstance == nullptr) mInstance = new CConsoleView(controller, logger);
	};

	std::call_once(mInstanceFlag,createInstance);

	return mInstance;
}

void CConsoleView::Show()
{
	std::unique_lock<std::mutex> _locker(mMutexDraw);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_BLUE|LOGGER_UI_BACKGROUND);
		_tcout << __T("Please press:\n 's' to start find;\n 'p' to pause/unpause find;\n 'a' to abort;\n") << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_WHITE|BG_BLACK);

	_locker.unlock();

	UpdateInput();
}

void CConsoleView::SearchStarted()
{
	std::unique_lock<std::mutex> _locker(mMutexButtons);

		mStartButtonEnable = false;
		mPauseButtonEnable = true;
		mStopButtonEnable = true;

		mSearchDone = false;

	_locker.unlock();

	Show();
}

void CConsoleView::SearchPaused()
{
	std::unique_lock<std::mutex> _locker(mMutexButtons);

	mStartButtonEnable = false;
	mPauseButtonEnable = true;
	mStopButtonEnable = true;
}

void CConsoleView::SearchUnPaused()
{
	std::unique_lock<std::mutex> _locker(mMutexButtons);

	mStartButtonEnable = false;
	mPauseButtonEnable = true;
	mStopButtonEnable = true;
}

void CConsoleView::SearchDone()
{
	std::unique_lock<std::mutex> _locker(mMutexButtons);

		mStartButtonEnable = true;
		mPauseButtonEnable = false;
		mStopButtonEnable = false;

		mSearchDone = true;

	_locker.unlock();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_BLUE|LOGGER_UI_BACKGROUND);
	_tcout << __T("Search stoped!\n") << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_WHITE|BG_BLACK);
}

void CConsoleView::AddSearchResult( const SFileDesc& searchResult )
{
	//std::unique_lock<std::mutex> lock(mMutex1);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_LIGHTYELLOW|LOGGER_UI_BACKGROUND);
	_tcout << searchResult.Path << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_WHITE|BG_BLACK);
}

void CConsoleView::SetController( IControllerObserver &controller )
{
	std::unique_lock<std::mutex> _locker(mMutexController);

	mController = &controller;
}

void CConsoleView::SetLogger( CLogger* logger )
{
	std::unique_lock<std::mutex> _locker(mMutexLogger);

	mLogger = logger;
}

void CConsoleView::UpdateInput()
{	
	//std::unique_lock<std::mutex> lock(mMutex0);

	if(mRun) return;
	mRun = true;

	// UI thread
	auto ui  = [&]() -> void 
	{ 
		TCHAR _char = 0;

		while (true)
		{
			if(mSearchDone) break;

			_char = getc(stdin);

			if((_char == __T('s')) && mStartButtonEnable)
			{
				mController->AddStartDir(__T("D:/"));
				mController->SetQuery(__T("*.cpp"));
				mController->SetHideFilesFlag(false);

				SAFE_ADD_TO_LOG(mLogger, FG_BLACK|LOGGER_UI_BACKGROUND, __T("[Begin search]\n"));

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_BLUE|LOGGER_UI_BACKGROUND);
				_tcout << __T("Search started!\n") << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_WHITE|BG_BLACK);
				
				mController->StartSearch();
				continue;
			}

			if((_char == __T('p')) && mPauseButtonEnable)
			{
				bool _pause = mController->GetPause();

				if(_pause)
				{
					mController->UnPauseSearch();

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_BLUE|LOGGER_UI_BACKGROUND);
					_tcout << __T("  Search unpaused!\n") << std::endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_WHITE|BG_BLACK);
				}
				else
				{
					mController->PauseSearch();

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_BLUE|LOGGER_UI_BACKGROUND);
					_tcout << __T("  Search paused!\n") << std::endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_WHITE|BG_BLACK);
				}

				continue;
			}

			if((_char == __T('a')) && mStopButtonEnable)
			{
				mController->StopSearch();
				break;
			}

			if(_char != __T('\n'))
			{
				DString _c;
				_c += _char;
				SAFE_ADD_TO_LOG(mLogger, FG_LIGHTRED|LOGGER_UI_BACKGROUND, __T("Unknown command:") << _c.c_str() << __T("\n"));
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_WHITE|BG_BLACK);
			}
		}
	};

	mUIThread = thread(ui);

	while (!mSearchDone){;}

	mUIThread.join();
	
	SAFE_ADD_TO_LOG(mLogger, FG_BLACK|LOGGER_UI_BACKGROUND, __T("[End search]\n"));
}



