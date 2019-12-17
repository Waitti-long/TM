#include "TM.h"

bool TM::init(const std::string &str, char s, const std::string &address) {
    state = 0;
    location = 1;
    stop = s;
    paper = stop + str + stop;
    rules.clear();
    return _read_rules(address);
}

bool TM::read() {
    std::tuple<int, char> p(state, paper[location]);
    auto it = rules.find(p);
    if (it == rules.end()) {
        return false;
    } else {
        state = std::get<0>(it->second);
        paper[location] = std::get<1>(it->second);
        int old = location;
        location += (int) std::get<2>(it->second);
        if (location < 0 || location >= paper.length())
            location = old;
        return true;
    }
}

bool TM::_read_rules(const std::string &address) {
    std::ifstream file(address);
    if (!file.is_open())
        return false;
    std::string line;
    while (std::getline(file, line)) {
        if(line == "End")
            break;
        auto fir = std::make_tuple(int(line[0] - '0'), line[2]);
        auto sec = std::make_tuple(int(line[4] - '0'), line[6], (Direction)line[8]);
        std::pair<std::tuple<int, char>, std::tuple<int, char, Direction>> p(fir, sec);
        rules.insert(p);
    }
    return true;
}


