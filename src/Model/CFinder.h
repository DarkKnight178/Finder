/*
	CFinder.h
	Sergey Aksenov, 2013
*/

#pragma once

#include <io.h>
#include <windows.h>
#include <thread>
#include <mutex>

#include "IModelSubject.h"
#include "../Commons/String/CDString.h"

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/exception/all.hpp>

namespace fs = boost::filesystem;


class CFinder : public IModelSubject
{
private:
	DISALLOW_COPYING_MOVING(CFinder)

	CFinder(CLogger* logger = nullptr);
public:
	static CFinder* GetInstance(CLogger* logger = nullptr);
	~CFinder() override;

	void SetOptions(const CFindOptions& options) override;

	void Start() override;
	void Stop() override;

	void SetPause(bool pause) override;
	bool GetPause() const override;

	void SetObserver(IObserver& observer) override;
	void UnSetObserver() override;
	void NotifyObserver() const override;

	const vector<SFileDesc*>* GetSearchResults() const override;

	void SetLogger(CLogger* logger) override;

protected:
	void SearchFrom(const DString &startDirectory);

	void NotifyAboutEndOfSearch();

	bool GetFileTime(SFileDesc* fileDesc);

protected:
	CFindOptions mOptions;
	IObserver* mObserver;
	vector<SFileDesc*> mResultFileDescs;

	bool mPause;
	bool mStop;

	CLogger* mLogger;

protected:
	static std::once_flag mInstanceFlag;
	static CFinder* mInstance;

	mutable std::mutex mMutexOptions, 
						mMutexStop, 
						mMutexStart, 
						mMutexPause, 
						mMutexObserver,
						mMutexLogger,
						mMutexResults;
};
