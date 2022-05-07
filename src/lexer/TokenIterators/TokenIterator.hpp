#pragma once

#include <string_view>

#include "../Token.hpp"
#include "../lex.hpp"

template<typename TText = std::u8string_view>
class TokenIterator {
    TText text;
    Token token;
public:
    TokenIterator(TText text) : text(text), token() {}

    Token current() const {
        return token;
    }

    Token next() {
        text = text.substr(token.sv.length());
        return token = lex(text);
    }
};
