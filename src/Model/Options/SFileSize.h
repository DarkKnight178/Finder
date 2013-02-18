/*
	SFileSize.h
	Sergey Aksenov, 2013
*/

#pragma once

#include <stdint.h>

struct SFileSize
{
public:
	SFileSize();
	~SFileSize();

	void Default();

	bool IsEmpty() const;

	bool Contans(uintmax_t size) const;

public:
	uintmax_t BeginSize;
	uintmax_t EndSize;
};