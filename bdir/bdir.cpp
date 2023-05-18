#include <iostream>
#include <iomanip>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

void calc_dir_size(fs::path path, size_t& size);
std::string size_str(size_t size);

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    fs::path dir_path(fs::current_path());
    std::cout << std::setw(7) << "TYPE" << std::setw(15) << "SIZE" << "    " << "NAME" << std::endl;
    for (auto& path : fs::directory_iterator(dir_path))
    {
        bool is_file = fs::is_regular_file(path);
        std::cout << std::setw(7) << (is_file ? "File" : "Dir") << std::setw(15);
        if (fs::is_regular_file(path))
        {
            std::cout << size_str(fs::file_size(path));
        }
        else
        {
            size_t dir_size = 0;
            calc_dir_size(path, dir_size);
            std::cout << size_str(dir_size);
        }
        std::cout << "    " << path.path().filename().string() << std::endl;
    }
}

void calc_dir_size(fs::path path, size_t& size)
{
    for (auto& path : fs::directory_iterator(path))
        if (fs::is_regular_file(path))
            size += fs::file_size(path);
        else
            calc_dir_size(path, size);
}

std::string size_str(size_t size)
{
    std::string file_size = std::to_string(size);
    size_t str_size = file_size.size();
    if (str_size > 3)
        for (int i = file_size.size() - 3; i > 0; i -= 3)
            file_size = file_size.insert(i, ",");
    return file_size;
}