/*
	IControllerObserver.h
	Sergey Aksenov, 2013
*/

#pragma once

#include "..\Model\IModelSubject.h"
#include "..\Commons\String\CDString.h"

class IView;


class IControllerObserver : public IObserver
{
private:
	DISALLOW_COPYING_MOVING(IControllerObserver)

protected:
	IControllerObserver(){;}

public:
	virtual ~IControllerObserver() {;};

	virtual bool Run() = 0;

	virtual void StartSearch() = 0;
	virtual void PauseSearch() = 0;
	virtual void UnPauseSearch() = 0;
	virtual void StopSearch() = 0;

	virtual bool GetPause() const = 0;

	virtual void SetQuery(const DString &query) = 0;
	virtual void SetRegexQuery(const DString &regexQuery) = 0;

	virtual void AddStartDir(const DString &dir) = 0;
	virtual void RemoveStartDir(const DString &dir) = 0;

	virtual void SetSizeLimit(const SFileSize &size) = 0;

	virtual void SetHideFilesFlag(bool findHideFiles) = 0;

	virtual void SetTimeCreatedLimit(const STimePeriod &time) = 0;
	virtual void SetTimeModifiedLimit(const STimePeriod &time) = 0;
	virtual void SetTimeLastAccessLimit(const STimePeriod &time) = 0;

	virtual void SetModel(IModelSubject& model) = 0;
	virtual void SetView(IView& view) = 0;

	virtual void SetLogger(CLogger* logger) = 0;
};
