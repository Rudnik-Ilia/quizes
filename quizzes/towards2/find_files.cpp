#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <experimental/filesystem>
#include <dirent.h>
#include <sys/stat.h>
// -lstdc++fs
namespace fs = std::experimental::filesystem;

bool IsFile(FILE *fptr) 
{
    struct stat fileStat;
    int fd = fileno(fptr);
    if (fstat(fd, &fileStat) < 0) 
    {
        return false;
    }
    return true;
}

void ListFilesRecursively(const std::string& path, std::vector<std::string>& files) 
{
    for (const auto& entry : fs::directory_iterator(path)) 
    {
        if (fs::is_regular_file(entry)) 
        {
            FILE* fptr = fopen(entry.path().c_str(), "r");
            if (fptr) 
            {
                if (IsFile(fptr)) 
                {
                    files.push_back(entry.path().string());
                }
                fclose(fptr);
            }
        } 
        else if (fs::is_directory(entry)) 
        {
            ListFilesRecursively(entry.path().string(), files);
        }
    }
}

int main() 
{
    std::string root_folder = "/home/ilia53/Desktop/FlaskProject"; 
    std::vector<std::string> files;
    ListFilesRecursively(root_folder, files);

    for (const std::string& file : files) 
    {
        std::cout << file << std::endl;
    }

    return 0;
}
