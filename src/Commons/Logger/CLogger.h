/*
CLogger.h
Sergey Aksenov, 2012
«¿Œ "›Õ ŒÃ"
*/

#pragma once


#include <tchar.h>
#include <Windows.h>
#include <fstream>
#include "..\BasicDef.h"

//#ifdef _DEBUG
	#define SAFE_ADD_TO_LOG(logger_ptr, color, messages) if(logger_ptr) logger_ptr->SetCMDColor(color) << messages;
//#else
//	#define SAFE_ADD_TO_LOG(logger_ptr, color, messages)  
//#endif

enum CMDFGColor
{
	FG_BLACK = 0x000,
	FG_BLUE = 0x001,
	FG_GREEN = 0x002,
	FG_AQUA = 0x003,
	FG_RED = 0x004,
	FG_PURPLE = 0x005,
	FG_YELLOW = 0x006,
	FG_WHITE = 0x007,
	FG_GRAY = 0x008,
	FG_LIGHTBLUE = 0x009,
	FG_LIGHTGREEN = 0x0A,
	FG_LIGHTAQUA = 0x0B,
	FG_LIGHTRED = 0x0C,
	FG_LIGHTPURPLE = 0x0D,
	FG_LIGHTYELLOW = 0x0E,
	FG_BRIGHTWHITE = 0x0F,
};

enum CMDBGColor
{
	BG_BLACK = 0x000,
	BG_BLUE = 0x010,
	BG_GREEN = 0x020,
	BG_AQUA = 0x030,
	BG_RED = 0x040,
	BG_PURPLE = 0x050,
	BG_YELLOW = 0x060,
	BG_WHITE = 0x070,
	BG_INTENSITY = 0x080,
};

enum LogMode
{
	LM_SILENT = 1,
	LM_FILE = 2,
	LM_CMD = 4,
};


class CLogger
{
private:
	DISALLOW_COPYING_MOVING(CLogger)

public:
	CLogger(DWORD mode, const TCHAR* filePath = nullptr);
	~CLogger();
	
	template <typename T>
	CLogger& operator<<(T val);

	CLogger& SetCMDColor(WORD color = FG_WHITE);

protected:
	DWORD mMode;
	_tofstream *mFilePtr;
};
