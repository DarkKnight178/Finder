/*
	CController.h
	Sergey Aksenov, 2013
*/

#pragma once

#include <io.h>
#include <windows.h>
#include <thread>
#include <mutex>

#include "IControllerObserver.h"
#include "..\View\IView.h"

class CController : public IControllerObserver
{
private:
	DISALLOW_COPYING_MOVING(CController)

	CController(IModelSubject& model, CLogger* logger = nullptr);
public:
	static CController* GetInstance(IModelSubject& model, CLogger* logger = nullptr);
	~CController() override;

	bool Run() override;

	void StartSearch() override;
	void PauseSearch() override;
	void UnPauseSearch() override;
	void StopSearch() override;

	bool GetPause() const override;

	void SetQuery(const DString &query) override;
	void SetRegexQuery(const DString &regexQuery) override;

	void AddStartDir(const DString &dir) override;
	void RemoveStartDir(const DString &dir) override;

	void SetSizeLimit(const SFileSize &size) override;

	void SetHideFilesFlag(bool findHideFiles) override;

	void SetTimeCreatedLimit(const STimePeriod &time) override;
	void SetTimeModifiedLimit(const STimePeriod &time) override;
	void SetTimeLastAccessLimit(const STimePeriod &time) override;

	void SetModel(IModelSubject& model) override;
	void SetView(IView& view) override;

	void SetLogger(CLogger* logger) override;

	void Update() override;

protected:
	IModelSubject* mModel;
	IView* mView;

	CFindOptions mSearchOptions;

	const vector<SFileDesc*> *mSearchResultsPtr;

	CLogger* mLogger;

	std::thread mSearchThread;

	std::mutex mMutexLogger,
				mMutexModel,
				mMutexView,
				mMutexOptions,
				mMutexResults;

protected:
	static std::once_flag mInstanceFlag;
	static CController* mInstance;
};
