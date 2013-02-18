/*
	CFindOptions.h
	Sergey Aksenov, 2013
*/

#include "CFindOptions.h"


CFindOptions::CFindOptions()
{
	Default();
}

CFindOptions::~CFindOptions()
{
	// empty
}

void CFindOptions::Default()
{
	mStartDirVec.clear();

	mQuery = DString::Empty;
	mPureQuery = DString::Empty;

	Size.Default();

	TimeModified.Default();
	TimeCreated.Default();
	TimeLastAccess.Default();

	HideFiles = false;
}

bool CFindOptions::IsEmpty() const
{
	return ( (mStartDirVec.size()==0) && (mQuery.length()==0) && Size.IsEmpty() && TimeModified.IsEmpty() && TimeCreated.IsEmpty() && TimeLastAccess.IsEmpty() );
}

void CFindOptions::AddStartDir( const DString &startDir )
{
	DString _lowercase = startDir.ToLower();

	for(auto _it : mStartDirVec)
	{
		if(_lowercase.compare(_it.ToLower()) == 0) return;
	}

	mStartDirVec.push_back( startDir );
}

void CFindOptions::RemoveStartDir( const DString &startDir )
{
	DString _lowercase = startDir.ToLower();

	for(auto _it = mStartDirVec.begin();_it<mStartDirVec.end();_it++)
	{
		if(_lowercase.compare(_it->ToLower()) == 0) 
		{
			mStartDirVec.erase(_it);
			return;
		}
	}
}

void CFindOptions::RemoveStartDir( UINT index )
{
	if(index > mStartDirVec.size()-1) return;

	mStartDirVec.erase( mStartDirVec.begin()+index );
}

DString CFindOptions::GetStartDir( UINT index ) const
{
	if(index > mStartDirVec.size()-1) return DString::Empty;;

	return mStartDirVec[index];
}

UINT CFindOptions::AmountStartDirs() const
{
	return mStartDirVec.size();
}

void CFindOptions::SetQuery( const DString &query )
{
	QueryParser(query);
}

void CFindOptions::SetQueryRegex( const DString &regexQuery )
{
	mQuery = regexQuery;
	mPureQuery = regexQuery;
}

DString CFindOptions::GetQuery() const
{
	return mQuery;
}

DString CFindOptions::GetPureQuery() const
{
	return mPureQuery;
}

void CFindOptions::QueryParser( const DString& query )
{
	mPureQuery = query;

	mQuery.clear();

	// TODO Добавлять еще в начале и конце (.*) если нет кавычек в запросе

	UINT _length = query.length();

	for(UINT i=0;i<_length;i++)
	{
		if( (query[i] == Character::ASTERISK)
			|| (query[i] == Character::SPACE) )
		{
			mQuery += L"(.*)";
			continue;
		}

		if( (query[i] == Character::PLUS) // +
			||(query[i] == Character::QUESTION_MARK) // ?
			||(query[i] == Character::CARET_CURCUMFLEX) // ^
			||(query[i] == Character::DOLLAR_SIGN) // $
			||(query[i] == Character::EXCLAMATION_POINT) // !
			||(query[i] == Character::OPEN_BRACE) // {
			||(query[i] == Character::CLOSE_BRACE) // }
			||(query[i] == Character::BACKSLASH) // '\''
			||(query[i] == Character::GREATER_THAN_SIGN) // >
			||(query[i] == Character::LESS_THAN_SIGN) // <
			||(query[i] == Character::VERTICAL_BAR) // |
			||(query[i] == Character::OPEN_BRACKET) // (
			||(query[i] == Character::CLOSE_BRACKET) // )	
			||(query[i] == Character::EQUALS_SIGN) // =
			||(query[i] == Character::LEFT_SQUARE_BRACKET) // [
			||(query[i] == Character::RIGHT_SQUARE_BRACKET) // ]
			||(query[i] == Character::COLON) // :
			||(query[i] == Character::HYPHEN_MINUS) // -
			||(query[i] == Character::PERIOD) ) // .
		{
			mQuery += L'\\';
			// And continue...
		}

		mQuery += query[i];
	}
}