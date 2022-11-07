#include <iostream>
#include <cstring>
#include <optional>
#include <filesystem>

#include "scan/arguments.hpp"

namespace fs = std::filesystem;

arguments_t parse_args(int argc, char* argv[])
{
    arguments_t args;

    for (int i = 1; i < argc; ++i)
    {
        if (std::strcmp(argv[i], "--help") == 0)
            args.help = true;
        else if (std::strcmp(argv[i], "--version") == 0)
            args.version = true;
        else
            args.free.push_back(argv[i]);
    }

    return args;
}

std::optional<std::set<fs::path> > extract_dirs(std::vector<std::string> const& paths)
{
    std::set<fs::path> dirs;

    for (auto& path : paths)
    {
        fs::path dir(path);
        if (fs::exists(dir) && fs::is_directory(path))
            dirs.insert(fs::canonical(dir).lexically_normal());
        else
        {
            std::cout << "An error occured: " << path << " either doesn't exists or is not a directory !" << std::endl;
            return std::nullopt;
        }
    }

    return dirs;
}
