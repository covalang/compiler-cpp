#ifndef RE2C_LEXER_TESTING__LEXER_HPP__INCLUDED
#define RE2C_LEXER_TESTING__LEXER_HPP__INCLUDED

#include <cstdint>
#include <map>
#include <queue>
#include <string>
#include <string_view>

#include "Token.hpp"

Token lex(std::string_view sv);

#endif