/*
	IObserver.h
	Sergey Aksenov, 2013
*/

#pragma once

#include "..\Commons\BasicDef.h"


class IObserver
{
private:
	DISALLOW_COPYING_MOVING(IObserver)

protected:
	IObserver(){;}

public:
	virtual ~IObserver() {;};

	virtual void Update() = 0;
};
