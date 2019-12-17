#ifndef SFML_TM_H
#define SFML_TM_H

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

class TM {
public:
    enum Direction {
        L = -1, S = 0, R = 1
    };
private:
    int state;
    int location;
    char stop;
    std::string paper;
    std::map<std::tuple<int, char>, std::tuple<int, char, Direction>> rules;

    bool _read_rules(const std::string& address);
public:
    bool init(const std::string& str, char s,const std::string& address);

    /*
     * 执行下一步操作，成功返回true，停机返回false
     * */
    bool read();


};


#endif //SFML_TM_H
