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
public:
    int state;
    int location;
    char stop;

    std::string paper;
    std::map<std::tuple<int, char>, std::tuple<int, char, Direction>> rules;
    std::vector<std::tuple<int,char>> stops;

    bool _read_rules(const std::string& address);
    auto& _find();
public:
    TM(){
        state = 0;
    }

    bool init(const std::string& str, char s,const std::string& address);

    /*
     * 执行下一步操作，成功返回 0 ，失败返回1，结束返回2
     * */
    int read();

    std::string get(){
        return paper;
    }

    int loc(){
        return location;
    }

    int sta(){
        return state;
    }
};


#endif //SFML_TM_H
