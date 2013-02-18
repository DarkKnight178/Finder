/*
CDString.cpp
Sergey Aksenov, 2012
ÇÀÎ "İÍÊÎÌ"
*/

#include "CDString.h"

// static
DString DString::Empty = L"";



DString::DString()
	: stl_string()
{
	// empty
}

DString::DString( const stl_string& str )
	: stl_string(str)
{
	// empty
}

DString::DString( const stl_string&& str )
	: stl_string(str)
{
	// empty
}

DString::DString( const DString& str)
	: stl_string(str)
{
	// empty
}

DString::DString( const DString&& str)
	: stl_string(str)
{
	// empty
}

DString::DString( const TCHAR* ptr )
	: stl_string(ptr)
{
	// empty
}

DString::~DString()
{
	// empty
}

DString& DString::operator=( const stl_string& str )
{
	return (DString&)stl_string::operator=(str);
}

DString& DString::operator=( const TCHAR character )
{
	return (DString&)stl_string::operator=(character);
}

DString& DString::operator=( const TCHAR* ptr )
{
	return (DString&)stl_string::operator=(ptr);
}

DString& DString::operator=( const DString& str)
{
	return (DString&)stl_string::operator=(str);
}

DString& DString::operator=( const DString&& str)
{
	return (DString&)stl_string::operator=(str);
}

DString& DString::operator+=( const TCHAR character )
{
	return (DString&)stl_string::operator+=(character);
}

DString& DString::operator+=( const TCHAR* ptr )
{
	return (DString&)stl_string::operator+=(ptr);
}

DString& DString::operator+=( const DString& str )
{
	return (DString&)stl_string::operator+=(str);
}

DString DString::ToLower() const
{
	DString _out(*this);

	for(auto &_iterator : _out )
	{
		_iterator = towlower(_iterator);
	}

	return _out;
}

bool DString::ExistDigit() const
{
	for(auto _iterator : *this )
	{
		if(_istdigit(_iterator) != 0) return true;
	}

	return false;
}

bool DString::ExistLetter() const
{
	for(auto _iterator : *this )
	{
		if(_istalpha(_iterator) != 0) return true;
	}

	return false;
}

bool DString::Exist( TCHAR character ) const
{
	for(auto _iterator : *this )
	{
		if(character == _iterator) return true;
	}

	return false;
}

bool DString::LastCharaterIs( TCHAR character ) const
{
	return (character == this->back());
}

bool DString::LastCharacterIsDigit() const
{
	return (_istalnum(this->back()) != 0) ? true : false;
}

bool DString::IllegalURICharacter( TCHAR character )
{
	// TODO Èçó÷èòü ıòó òåìó
	if( (character == L' ')
		|| (character > 237) ) 
		return true;

	return false;
}
