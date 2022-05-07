#pragma once

#include <string_view>

#include "../Token.hpp"
#include "../lex.hpp"
#include "TokenIterator.hpp"

template<typename TokenIterator = TokenIterator<>>
class DentedTokenIterator {
    TokenIterator & tokenIterator;
    Token token;
    uint64_t currentDentLevel;
    bool newlineSinceLastNonTab;
    uint64_t tabCount;

    Token getDentToken() {
        if (tabCount > currentDentLevel) {
            ++currentDentLevel;
            return { TokenType::Indent, { sv.data(), 0 } };
        }
        else if (tabCount < currentDentLevel) {
            --currentDentLevel;
            return { TokenType::Dedent, { sv.data(), 0 } };
        }
        else {
            return { TokenType::Dent, { sv.data(), 0 } };
        }
    }
public:
    DentedTokenIterator(TokenIterator & tokenIterator) : tokenIterator(tokenIterator), token(), currentDentLevel(), newlineSinceLastNonTab(), tabCount() {}

    Token current() const {
        return token;
    }

    Token next() {
        auto token = tokenIterator.next();

        switch (token.type) {
            case TokenType::Newline:
                newlineSinceLastNonTab = true;
                break;
            case TokenType::Tab:
                if (newlineSinceLastNonTab)
                    ++tabCount;
                break;
            case TokenType::Eof:
                tabCount = 0;
                if (currentDentLevel > 0) {
                    --currentDentLevel;
                    return { TokenType::Dedent, { sv.data(), 0 } };
                }
                break;
            default:
                if (newlineSinceLastNonTab) {
                    auto dentToken = getDentToken();
                    if (tabCount == currentDentLevel) {
                        newlineSinceLastNonTab = false;
                        tabCount = 0;
                    }
                    return dentToken;
                }
                break;
        }

        sv = sv.substr(token.sv.length());
        return token;
    }
};
