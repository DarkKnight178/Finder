/*
	IView.h
	Sergey Aksenov, 2013
*/

#pragma once

#include "..\Commons\Logger\CLogger.h"
#include "..\Controller\IControllerObserver.h"
#include "..\Model\Options\SFileDesc.h"

#define LOGGER_UI_BACKGROUND BG_INTENSITY

class IView
{
private:
	DISALLOW_COPYING_MOVING(IView)

protected:
	IView(){;}

public:
	virtual ~IView() {;}

	virtual void Show() = 0;

	virtual void SearchStarted() = 0;
	virtual void SearchPaused() = 0;
	virtual void SearchUnPaused() = 0;
	virtual void SearchDone() = 0;

	virtual void AddSearchResult(const SFileDesc& searchResult) = 0;

	virtual void SetController(IControllerObserver &controller) = 0;

	virtual void SetLogger(CLogger* logger) = 0;
};

