/*
	CConsoleView.h
	Sergey Aksenov, 2013
*/

#pragma once

#include "..\IView.h"
#include <thread>
#include <mutex>

using namespace std;


class CConsoleView : public IView
{
private:
	DISALLOW_COPYING_MOVING(CConsoleView)

	CConsoleView(IControllerObserver &controller, CLogger* logger = nullptr);
public:
	static CConsoleView* GetInstance(IControllerObserver &controller, CLogger* logger = nullptr);
	~CConsoleView() override;

	void Show() override;

	void SearchStarted() override;
	void SearchPaused() override;
	void SearchUnPaused() override;
	void SearchDone() override;

	void AddSearchResult(const SFileDesc& searchResult) override;

	void SetController(IControllerObserver &controller) override;

	void SetLogger(CLogger* logger) override;

protected:
	void UpdateInput();

protected:
	IControllerObserver* mController;

	bool mRun;
	bool mSearchDone;

	bool mStartButtonEnable;
	bool mPauseButtonEnable;
	bool mStopButtonEnable;

	CLogger* mLogger;

	std::thread mUIThread;

	std::mutex mMutexDraw,
				mMutexButtons,
				mMutexResults,
				mMutexLogger,
				mMutexController;

protected:
	static std::once_flag mInstanceFlag;
	static CConsoleView* mInstance;
};
