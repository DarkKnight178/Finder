/*
	IModelSubject.h
	Sergey Aksenov, 2013
*/

#pragma once

#include "..\Commons\Logger\CLogger.h"
#include "..\Controller\IObserver.h"
#include "Options\CFindOptions.h"
#include "Options\SFileDesc.h"

#define LOGGER_LOGIC_BACKGROUND BG_WHITE

class IModelSubject
{
private:
	DISALLOW_COPYING_MOVING(IModelSubject)

protected:
	IModelSubject(){;}

public:
	virtual ~IModelSubject() {;}

	virtual void SetOptions(const CFindOptions& options) = 0;

	virtual void Start() = 0;
	virtual void Stop() = 0;

	virtual void SetPause(bool pause) = 0;
	virtual bool GetPause() const = 0;

	virtual void SetObserver(IObserver& observer) = 0;
	virtual void UnSetObserver() = 0;
	virtual void NotifyObserver() const = 0;

	virtual const vector<SFileDesc*>* GetSearchResults() const = 0;

	virtual void SetLogger(CLogger* logger) = 0;
};
