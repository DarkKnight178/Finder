/*
BasicDef.h
Sergey Aksenov, 2012
«¿Œ "›Õ ŒÃ"
*/

#pragma once

#ifdef _DEBUG
	#include <cassert>
#endif // _DEBUG


#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

typedef unsigned int UINT;

#define SAFE_DELETE(ptr) if(ptr!=nullptr) { delete ptr; ptr=nullptr; }


#if (__cplusplus > 199711L) // if full support C++11
	#define CPP11_BAN_USING_MEMBER = delete
#else
	#define CPP11_BAN_USING_MEMBER 
#endif

#define FILE_TRASH_CHARACTERS_COUNT 3


#ifdef _UNICODE
	typedef std::wofstream _tofstream;
	typedef std::wifstream _tifstream;
	typedef std::wfstream _tfstream;
	#define _tcout std::wcout
#else
	typedef std::ofstream _tofstream;
	typedef std::ifstream _tifstream;
	typedef std::fstream _tfstream;
	#define _tcout std::cout
#endif


// --- Java ---
#ifdef SWIG
#define  EXPORT_IN_SWIG
#endif

// enums
#ifdef EXPORT_IN_SWIG
	#define ENUM_BEGIN(name) enum name {
#define ENUM_END };
#else
	#define ENUM_BEGIN(name) enum class name : unsigned int {
	#define ENUM_END };
#endif // EXPORT_IN_SWIG


// copying & moving constructors
#ifndef EXPORT_IN_SWIG
	#define DISALLOW_COPYING_MOVING(class_name)\
		class_name(const class_name&) CPP11_BAN_USING_MEMBER;\
		void operator=(const class_name&) CPP11_BAN_USING_MEMBER;\
		class_name(const class_name&&) CPP11_BAN_USING_MEMBER;\
		void operator=(const class_name&&) CPP11_BAN_USING_MEMBER;
#else
	#define DISALLOW_COPYING_MOVING(class_name) 
#endif // EXPORT_IN_SWIG

// override
#ifndef EXPORT_IN_SWIG
	#define OVERRIDE override
#else
	#define OVERRIDE  
#endif // EXPORT_IN_SWIG

// final
#ifndef EXPORT_IN_SWIG
	#define FINAL final
#else
	#define FINAL  
#endif // EXPORT_IN_SWIG