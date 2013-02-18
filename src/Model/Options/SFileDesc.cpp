/*
	SFileDesc.cpp
	Sergey Aksenov, 2013
*/

#include "SFileDesc.h"


SFileDesc::SFileDesc()
{
	Clear();
}

SFileDesc::~SFileDesc()
{
	// empty
}

void SFileDesc::Clear()
{
	Name.clear();
	Path.clear();

	Size = 0;

	Attributes = 0;

	TimeCreatiton = 0;
	TimeModified = 0;
	TimeLastAccess = 0;
}
