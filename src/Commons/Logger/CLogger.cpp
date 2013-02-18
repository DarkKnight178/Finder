/*
CLogger.cpp
Sergey Aksenov, 2012
ÇÀÎ "ÝÍÊÎÌ"
*/

#include "CLogger.h"


CLogger::CLogger(DWORD mode, const TCHAR* filePath)
{
	mFilePtr = nullptr;
	
	mMode = mode;
	if( (mMode & LM_FILE)&&(filePath == nullptr) ) mMode &= ~LM_FILE;
	
	if(mMode & LM_FILE)
	{
		try
		{
			mFilePtr = new _tofstream();
			mFilePtr->open(filePath, ios::out|ios::trunc);
		}
		catch (...)
		{
			mMode &= ~LM_FILE;

			if(mFilePtr != nullptr)
			{
				delete mFilePtr;
				mFilePtr = nullptr;
			}

			this->operator<<(__T("Error create log file. Output in file not be.\n"));
		}
	}

	if(mMode != LM_SILENT)
	{
		*this << __T("[Begin log. Logger object created]\n");

		if(mMode & LM_CMD) this->operator<<(__T(" Allow output in CMD.\n"));
		if(mMode & LM_FILE) *this << __T(" Allow output in file(") << filePath << __T(").\n"); 
	}
}

CLogger::~CLogger()
{
	*this << __T("\n[End log. Logger Destroy]\n");

	if(mFilePtr != nullptr)
	{
		mFilePtr->close();

		delete mFilePtr;
		mFilePtr = nullptr;
	}
}

template <typename T>
CLogger& CLogger::operator<<( T val )
{
	try
	{
		if(mMode & LM_CMD) _tcout << val;
		if( (mMode & LM_FILE)&&(mFilePtr->is_open()) ) (*mFilePtr) << val;
	}
	catch (...)
	{
		this->operator<<(__T("Error add text to log\n"));
	}

	return *this;
}

CLogger& CLogger::SetCMDColor( WORD color )
{
	if(mMode & LM_CMD) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return *this;
}