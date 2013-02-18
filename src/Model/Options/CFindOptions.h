/*
	CFindOptions.h
	Sergey Aksenov, 2013
*/

#pragma once

#include "..\..\Commons\BasicDef.h"
#include "..\..\Commons\String\CDString.h"
#include "..\..\Commons\String\Character.h"
#include "SFileSize.h"
#include "STimePeriod.h"


class CFindOptions
{
public:
	CFindOptions();
	~CFindOptions();
	
	void Default();

	bool IsEmpty() const;

	void AddStartDir(const DString &startDir);
	void RemoveStartDir(const DString &startDir);
	void RemoveStartDir(UINT index);
	DString GetStartDir(UINT index) const;
	UINT AmountStartDirs() const;
	
	void SetQuery(const DString &query);
	void SetQueryRegex(const DString &regexQuery);
	DString GetQuery() const;

	DString GetPureQuery() const;

private:
	void QueryParser(const DString& query);

public:
	SFileSize Size;

	STimePeriod TimeCreated;
	STimePeriod TimeModified;
	STimePeriod TimeLastAccess;

	bool HideFiles;

protected:
	vector<DString> mStartDirVec;

	DString mQuery;	
	DString mPureQuery;
};