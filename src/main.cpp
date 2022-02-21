#include <iostream>
#include <magic_enum.hpp>
#include <nlohmann/json.hpp>
#include <CLI/CLI.hpp>

using namespace std;

int main(int argc, char** argv) {
    CLI::App app{std::string(EXECUTABLE_NAME) + " compiler - version " + EXECUTABLE_VERSION, EXECUTABLE_NAME};

    app.add_flag("-v,--version", [](std::int64_t i){cout << EXECUTABLE_VERSION << endl;}, "Print version information");

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