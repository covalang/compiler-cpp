#include <iostream>
using namespace std;

#include <magic_enum.hpp>
#include <nlohmann/json.hpp>
#include <CLI/CLI.hpp>

#include "lexer/TokenIterators/TokenIterator.hpp"

int main(int argc, char** argv) {
    CLI::App app{string(EXECUTABLE_NAME) + " compiler - version " + EXECUTABLE_VERSION, EXECUTABLE_NAME};
    app.set_version_flag("-v,--version", [](){ return EXECUTABLE_VERSION; });

    if (argc <= 1)
        return app.exit(CLI::CallForHelp());
    try {
        app.parse(argc, argv);
    }
    catch (CLI::ParseError const & e) {
        return app.exit(e);
    }
    return 0;
}