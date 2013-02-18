/*
	SFileDesc.h
	Sergey Aksenov, 2013
*/

#pragma once

#include <stdint.h>
#include "..\..\Commons\String\CDString.h"

typedef unsigned long DWORD;

struct SFileDesc
{
	SFileDesc();
	~SFileDesc();

	void Clear();

public:
	DString Path;
	DString Name;

	uintmax_t Size;

	DWORD Attributes;

	time_t TimeCreatiton;
	time_t TimeModified;
	time_t TimeLastAccess;
};