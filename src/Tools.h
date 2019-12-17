#ifndef SFML_TOOLS_H
#define SFML_TOOLS_H

#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string>

bool read_directory(const std::string& name, std::vector<std::string> &v);

#endif //SFML_TOOLS_H
