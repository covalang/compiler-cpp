#include <iostream>
#include <magic_enum.hpp>
#include <nlohmann/json.hpp>
#include <CLI/CLI.hpp>

#include <antlr4-runtime/antlr4-runtime.h>
#include "CovaLexer.h"
#include "CovaParser.h"
#include "CovaParserBaseListener.h"

using namespace std;

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

//    antlr4::ANTLRFileStream input;
//    input.loadFromFile(argv[1]);
//    CovaLexer lexer(&input);
//    antlr4::CommonTokenStream tokens(&lexer);
//    CovaParser parser(&tokens);
//    CovaParserBaseListener listener;
//    parser.addParseListener(&listener);
//    parser.compilationUnit();
    return 0;
}