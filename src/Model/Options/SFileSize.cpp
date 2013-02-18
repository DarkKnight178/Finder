/*
	SFileSize.cpp
	Sergey Aksenov, 2013
*/


#include "SFileSize.h"


SFileSize::SFileSize()
{
	Default();
}

SFileSize::~SFileSize()
{
	// empty
}

void SFileSize::Default()
{
	BeginSize = 0;
	EndSize = UINT64_MAX;
}

bool SFileSize::IsEmpty() const
{
	return (BeginSize == 0) && (EndSize == UINT64_MAX);
}

bool SFileSize::Contans( uintmax_t size ) const
{
	if(IsEmpty()) return false;
	
	return (BeginSize <= size) && (EndSize >= size);
}
