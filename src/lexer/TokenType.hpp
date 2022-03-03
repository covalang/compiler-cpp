#pragma once

#include <cstdint>

enum class TokenType : uint8_t
{
	BinaryRealHalfLiteral,
	DecimalIntegerLiteral,
	HexadecimalIntegerLiteral,
	BinaryIntegerLiteral,
	DecimalRealLiteral,

	Newline,
	Whitespace,
	Tab,

	Indent,
	Dent,
	Dedent,

	Identifier,

	Use,
	Namespace,
	Type,
	Enum,
	Struct,
	Interface,
	Trait,
	Delegate,
	Field,
	Prop,
	Func,
	Local,
	True,
	False,

	If,
	Else,
	Match,

	Arrow,
	LessOrEqual,
	GreaterOrEqual,
	Range,
	InRange,
	NotInRange,
	LessThan,
	GreaterThan,
	NotEqual,
	Equal,

	And,
	Or,
	Nand,
	Nor,
	Xor,
	Xnor,
	Not,
	Is,
	Isnt,

	Power,
	Minus,
	Multiply,
	Divide,
	Modulo,
	Plus,
	Octothorp,
	Tilde,
	Dot,
	EqualsSign,
	LeftParenthesis,
	RightParenthesis,
	LeftBrace,
	RightBrace,
	LeftBracket,
	RightBracket,
	SemiColon,
	Comma,

	Eof,
	Invalid,
};