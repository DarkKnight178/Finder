/*
Character.cpp
Sergey Aksenov, 2012
ÇÀÎ "İÍÊÎÌ"
*/


#include "Character.h"


TCHAR Character::ToLower(TCHAR character)
{
	if (IsCapitalLetter(character)) return towlower(character);
	else return character;
}

TCHAR Character::ToUpper(TCHAR character)
{
	if (IsSmallLetter(character)) return towlower(character);
	else return character;
}

bool Character::IsSmallLetter(TCHAR character)
{
	return (_istlower(character) != 0) ? true : false;
}

bool Character::IsCapitalLetter(TCHAR character)
{
	return (_istupper(character) != 0) ? true : false;
}

bool Character::IsLetter( TCHAR character )
{
	bool _smallLiteral = (character >= 'a')&&(character <= 'z');
	bool _capitalLiteral = (character >= 'A')&&(character <= 'Z');

	return _smallLiteral || _capitalLiteral;
}

bool Character::IsDigit( TCHAR character )
{
	return (_istdigit(character) != 0) ? true : false;
}

bool Character::IsLetterOrDigit( TCHAR character )
{
	return (_istalnum(character) != 0) ? true : false;
}

bool Character::IsFormatingOrTab( TCHAR character )
{
	return ((character == TAB)||(character == VT)||(character == LF)||(character == CR)||(character == NLB_CSS2)||(character == FF));
}

bool Character::IsCombinator( TCHAR character )
{
	return ((character == SPACE)||(character == GREATER_THAN_SIGN)||(character == EQUIVALENCY_SIGN_TIDE)||(character == PLUS));
}

bool Character::IsAttributeOperator( TCHAR character )
{
	return ((character == Character::EQUALS_SIGN)||(character == Character::EQUIVALENCY_SIGN_TIDE)||(character == Character::CARET_CURCUMFLEX)||(character == Character::DOLLAR_SIGN)||(character == Character::ASTERISK)||(character == Character::VERTICAL_BAR));
}

bool Character::IsIllegalCharacter( TCHAR character )
{
	return false;
}

bool Character::IsHexidimalDigit( TCHAR character )
{
	bool _smallLiteral = (character >= 'a')&&(character <= 'f');
	bool _capitalLiteral = (character >= 'A')&&(character <= 'F');

	return _smallLiteral || _capitalLiteral || _istdigit(character);
}
