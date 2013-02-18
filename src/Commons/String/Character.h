/*
Character.h
Sergey Aksenov, 2012
«¿Œ "›Õ ŒÃ"
*/

#pragma once

#include <tchar.h>
#include <ctype.h>


namespace Character
{
	enum Character
	{
		AMPERSAND = __T('&'), // &
		ASTERISK = __T('*'), // *
		AT = __T('@'), // @
		BACKSLASH = __T('\\'), // '\'
		CARET_CURCUMFLEX = __T('^'), // ^
		CLOSE_BRACE = __T('}'), // }
		CLOSE_BRACKET = __T(')'), // )
		COLON = __T(':'), // :
		COMMA = __T(','), // ,
		CR = __T('\r'), // \r
		DOLLAR_SIGN = __T('$'), // $
		DOUBLE_QUOTE = __T('\"'), // "
		EQUALS_SIGN = __T('='), // =
		EQUIVALENCY_SIGN_TIDE = __T('~'), // ~
		EXCLAMATION_POINT = __T('!'), // !
		FF = __T('\f'), // \f
		GRAVE_ACCENT = __T('`'), // `
		GREATER_THAN_SIGN = __T('>'), // >
		HYPHEN_MINUS = __T('-'), // -
		LEFT_SQUARE_BRACKET = __T('['), // [
		LESS_THAN_SIGN = __T('<'), // <
		LF = __T('\n'), // \n
		NLB_CSS2 = __T('\a'), // \a
		NUMBER_SIGN = __T('#'), // #
		OPEN_BRACE = __T('{'), // {
		OPEN_BRACKET = __T('('), // (
		PERCENT = __T('%'), // %
		PERIOD = __T('.'), // .
		PLUS = __T('+'), // +
		QUESTION_MARK = __T('?'), // ?
		RIGHT_SQUARE_BRACKET = __T(']'), // ]
		SEMICOLON = __T(';'), // ;
		SINGLE_QUOTE = __T('\''), // '
		SLASH = __T('/'), // '/'
		SPACE = __T(' '), // <space>
		TAB = __T('\t'), // \t
		UNDERSCORE = __T('_'), // '_'
		VERTICAL_BAR = __T('|'), // '|'
		VT = __T('\v'), // \v
		NULL_EOF = __T('\0'), // \0
	};

	TCHAR ToLower(TCHAR character);

	TCHAR ToUpper(TCHAR character);

	bool IsSmallLetter(TCHAR character);

	bool IsCapitalLetter(TCHAR character);

	bool IsLetter( TCHAR character );

	bool IsDigit( TCHAR character );

	bool IsLetterOrDigit( TCHAR character );

	bool IsFormatingOrTab( TCHAR character );

	bool IsCombinator( TCHAR character );

	bool IsAttributeOperator( TCHAR character );

	bool IsIllegalCharacter( TCHAR character );

	bool IsHexidimalDigit(TCHAR character);
}