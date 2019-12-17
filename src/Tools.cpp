#include "Tools.h"


bool read_directory(const std::string &name, std::vector<std::string> &v) {
    DIR *dirp = opendir(name.c_str());
    if (dirp == nullptr) {
        return false;
    }
    struct dirent *dp;
    while ((dp = readdir(dirp)) != nullptr) {
        if (dp->d_name[0] != '.')
            v.emplace_back(dp->d_name);
    }
    closedir(dirp);
    return true;
}