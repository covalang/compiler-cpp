#pragma once

#include <string_view>

#include "TokenType.hpp"

struct Token {
	TokenType type;
	std::string_view sv;

	//std::string toString() const;
};