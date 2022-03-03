#include "lexer.hpp"

/*!include:re2c "unicode.re.txt" */
/*!re2c
	newline = '\r\n' | '\r' | '\n' | '\x85' | '\u2028' | '\u2029';
	whitespace = Zs | '\x0b' | '\x0c'; //| '\x09' (horizontal tab)
	tab = '\t';

	sign = [+-];
	hexadecimalDigit = [0-9a-fA-F];
	decimalDigit = [0-9];
	binaryDigit = [01];

	digitSeparator = "_";

	decimalPrefix = "0d";
	hexadecimalPrefix = "0x";
	binaryPrefix = "0b";
	unicodePrefix = "\\u";

	unicodeLiteral = unicodePrefix hexadecimalDigit+;

	letterCharacter = L | Nl;
	combiningCharacter = Mn | Mc;
	decimalDigitCharacter = Nd;
	connectingCharacter = Pc;
	dashPunctuationCharacter = Pd;
	formattingCharacter = Cf;

	identifierStartCharacter = letterCharacter | "_";
	identifierPartCharacter = letterCharacter | combiningCharacter | decimalDigitCharacter | connectingCharacter | dashPunctuationCharacter | formattingCharacter;
	identifier = identifierStartCharacter identifierPartCharacter*;

	booleanLiteral = "true" | "false";

	decimalInteger = decimalDigit (decimalDigit | digitSeparator)*;

	integerTypeSuffix = [iu];
	integerTypeStorageSize = decimalInteger;
	integerType = integerTypeSuffix integerTypeStorageSize?;

	decimalIntegerLiteral = decimalPrefix? decimalInteger integerType?;

	hexadecimalInteger = hexadecimalDigit (hexadecimalDigit | digitSeparator)*;
	hexadecimalIntegerLiteral = hexadecimalPrefix hexadecimalInteger integerType?;

	binaryInteger = binaryDigit (binaryDigit | digitSeparator)*;
	binaryIntegerLiteral = binaryPrefix binaryInteger integerType?;

	realTypeSuffix = "f";
	realTypeStorageSizeHalf     = "16";
	realTypeStorageSizeSingle   = "32";
	realTypeStorageSizeDouble   = "64";
	realTypeStorageSizeExtended = "80";
	realTypeStorageSizeQuad     = "128";
	realTypeStorageSize = realTypeStorageSizeHalf | realTypeStorageSizeSingle | realTypeStorageSizeDouble | realTypeStorageSizeExtended | realTypeStorageSizeQuad;
	realType = realTypeSuffix realTypeStorageSize?;

	decimalExponentPart = [Ee] sign? decimalInteger;
	binaryExponentPart = [Ee] sign? binaryInteger;

	decimalRealLiteral
		= decimalInteger "." decimalInteger decimalExponentPart? realType?
		| "." decimalInteger decimalExponentPart? realType?
		| decimalInteger decimalExponentPart realType?
		| decimalInteger realType
		;

	binaryRealHalfLiteral     = binaryPrefix binaryDigit "." binaryDigit{5}  "." binaryDigit{10}  (realTypeSuffix realTypeStorageSizeHalf)?;
	binaryRealSingleLiteral   = binaryPrefix binaryDigit "." binaryDigit{8}  "." binaryDigit{23}  (realTypeSuffix realTypeStorageSizeSingle)?;
	binaryRealDoubleLiteral   = binaryPrefix binaryDigit "." binaryDigit{11} "." binaryDigit{52}  (realTypeSuffix realTypeStorageSizeDouble)?;
	binaryRealExtendedLiteral = binaryPrefix binaryDigit "." binaryDigit{15} "." binaryDigit{64}  (realTypeSuffix realTypeStorageSizeExtended)?;
	binaryRealQuadLiteral     = binaryPrefix binaryDigit "." binaryDigit{15} "." binaryDigit{112} (realTypeSuffix realTypeStorageSizeQuad)?;
*/

#include <string_view>
using namespace std;

Token lex(string_view sv) {
	if (sv.empty())
		return { TokenType::Eof, sv };
	auto YYCURSOR = sv.data();
	decltype(YYCURSOR) YYMARKER;

#define RETURN_TOKEN(tokenName) return { TokenType::tokenName, { sv.data(), static_cast<size_t>(YYCURSOR - sv.data()) } }
	/*!re2c
	re2c:define:YYCTYPE = 'char unsigned';
	re2c:yyfill:enable = 0;

	binaryRealHalfLiteral     { RETURN_TOKEN(BinaryRealHalfLiteral    ); }
	unicodeLiteral            { RETURN_TOKEN(Invalid                  ); }
	decimalIntegerLiteral     { RETURN_TOKEN(DecimalIntegerLiteral    ); }
	hexadecimalIntegerLiteral { RETURN_TOKEN(HexadecimalIntegerLiteral); }
	binaryIntegerLiteral      { RETURN_TOKEN(BinaryIntegerLiteral     ); }
	decimalRealLiteral        { RETURN_TOKEN(DecimalRealLiteral       ); }

	newline                   { RETURN_TOKEN(Newline                  ); }
	whitespace                { RETURN_TOKEN(Whitespace               ); }
	tab                       { RETURN_TOKEN(Tab                      ); }

	"use"                     { RETURN_TOKEN(Use                      ); }
	"namespace"               { RETURN_TOKEN(Namespace                ); }
	"type"                    { RETURN_TOKEN(Type                     ); }
	"enum"                    { RETURN_TOKEN(Enum                     ); }
	"struct"                  { RETURN_TOKEN(Struct                   ); }
	"interface"               { RETURN_TOKEN(Interface                ); }
	"trait"                   { RETURN_TOKEN(Trait                    ); }
	"delegate"                { RETURN_TOKEN(Delegate                 ); }
	"field"                   { RETURN_TOKEN(Field                    ); }
	"prop"                    { RETURN_TOKEN(Prop                     ); }
	"func"                    { RETURN_TOKEN(Func                     ); }
	"local"                   { RETURN_TOKEN(Local                    ); }
	"true"                    { RETURN_TOKEN(True                     ); }
	"false"                   { RETURN_TOKEN(False                    ); }

	"if"                      { RETURN_TOKEN(If                       ); }
	"else"                    { RETURN_TOKEN(Else                     ); }
	"match"                   { RETURN_TOKEN(Match                    ); }

	"->"                      { RETURN_TOKEN(Arrow                    ); }
	"<="                      { RETURN_TOKEN(LessOrEqual              ); }
	">="                      { RETURN_TOKEN(GreaterOrEqual           ); }
	".."                      { RETURN_TOKEN(Range                    ); }
	"><"                      { RETURN_TOKEN(InRange                  ); }
	"<>"                      { RETURN_TOKEN(NotInRange               ); }
	"<"                       { RETURN_TOKEN(LessThan                 ); }
	">"                       { RETURN_TOKEN(GreaterThan              ); }
	"!="                      { RETURN_TOKEN(NotEqual                 ); }
	"=="                      { RETURN_TOKEN(Equal                    ); }

	"and"                     { RETURN_TOKEN(And                      ); }
	"or"                      { RETURN_TOKEN(Or                       ); }
	"nand"                    { RETURN_TOKEN(Nand                     ); }
	"nor"                     { RETURN_TOKEN(Nor                      ); }
	"xor"                     { RETURN_TOKEN(Nor                      ); }
	"xnor"                    { RETURN_TOKEN(Xnor                     ); }
	"not"                     { RETURN_TOKEN(Not                      ); }
	"is"                      { RETURN_TOKEN(Is                       ); }
	"isnt"                    { RETURN_TOKEN(Isnt                     ); }

	"**"                      { RETURN_TOKEN(Power                    ); }
	"-"                       { RETURN_TOKEN(Minus                    ); }
	"*"                       { RETURN_TOKEN(Multiply                 ); }
	"/"                       { RETURN_TOKEN(Divide                   ); }
	"%"                       { RETURN_TOKEN(Modulo                   ); }
	"+"                       { RETURN_TOKEN(Plus                     ); }
	"#"                       { RETURN_TOKEN(Octothorp                ); }
	"~"                       { RETURN_TOKEN(Tilde                    ); }
	"."                       { RETURN_TOKEN(Dot                      ); }
	"="                       { RETURN_TOKEN(EqualsSign               ); }
	"("                       { RETURN_TOKEN(LeftParenthesis          ); }
	")"                       { RETURN_TOKEN(RightParenthesis         ); }
	"{"                       { RETURN_TOKEN(LeftBrace                ); }
	"}"                       { RETURN_TOKEN(RightBrace               ); }
	"["                       { RETURN_TOKEN(LeftBracket              ); }
	"]"                       { RETURN_TOKEN(RightBracket             ); }
	";"                       { RETURN_TOKEN(SemiColon                ); }
	","                       { RETURN_TOKEN(Comma                    ); }

	identifier                { RETURN_TOKEN(Identifier               ); }
	*                         { RETURN_TOKEN(Invalid                  ); }

	*/
#undef RETURN_TOKEN
}