#include "aclint.h"
#include <cxxopts.hpp>
#include <nlohmann/json.hpp>

#ifdef _MSC_VER
#include <windows.h>
#endif

int main(int argc, char** argv)
{
    cxxopts::Options options("aclint", "Adaptive Card linting tool");
    options.add_options("output")
        ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
        ("h,help", "Print usage");

    try
    {
        auto result = options.parse(argc, argv);
        options.parse_positional({"input_file", "output_file", "rest"});
        if (result["help"].as<bool>())
        {
            std::cout << options.help() << std::endl;
            return 0;
        }

        std::cout << "Hello CMake." << std::endl;
        if (result["verbose"].as<bool>())
        {
            std::cout << "verbose mode!" << std::endl;
        }
    }
    catch (const cxxopts::OptionParseException& parseException)
    {
        std::cout << CSI("1m") << CSI("31m") << parseException.what() << CSI("0m") << std::endl << std::endl;
        std::cout << options.help() << std::endl;
    }

    return 0;
}
