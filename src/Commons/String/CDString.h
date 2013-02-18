/*
CDString.h
Sergey Aksenov, 2012
«¿Œ "›Õ ŒÃ"
*/

#pragma once

#include <tchar.h>
#include <iostream>
using namespace std;

#ifdef _UNICODE
	typedef wstring stl_string;
#else
	typedef string stl_string;
#endif


class DString : public stl_string
{
public:
	DString();
	DString(const stl_string& str);
	DString(const stl_string&& str);
	DString(const DString& str);	
	DString(const DString&& str);
	DString(const TCHAR* ptr);
	~DString();

	DString& operator=(const stl_string& str);

	DString& operator=(const TCHAR character);
	DString& operator=(const TCHAR* ptr);
	DString& operator=(const DString& str);
	DString& operator=(const DString&& str);

	DString& operator+=(const TCHAR character);
	DString& operator+=(const TCHAR* ptr);
	DString& operator+=(const DString& str);

	DString ToLower() const;

	bool ExistDigit() const;
	bool ExistLetter() const;
	bool Exist(TCHAR character) const;

	bool LastCharaterIs(TCHAR character) const;
	bool LastCharacterIsDigit() const;
public:
	static bool IllegalURICharacter(TCHAR character);

public:
	static DString Empty;
};
