#include "TM.h"

bool TM::init(const std::string &str, char s, const std::string &address) {
    state = 0;
    location = 1;
    stop = s;
    paper = stop + str + stop;
    stops.clear();
    rules.clear();
    return _read_rules(address);
}

auto &TM::_find() {
    for(auto& i : rules){
//        std::cout << std::get<0>(i.first)<< std::get<1>(i.first) << std::get<0>(i.second)<< std::get<1>(i.second)<< std::get<2>(i.second) << std::endl;
        if(state == std::get<0>(i.first) && paper[location] == std::get<1>(i.first)){
            return  i;
        }
    }
    return *rules.end();
}

int TM::read() {
    auto it = _find();
    if (it == *rules.end()) {
        for(auto& i :stops){
            if(paper[location] == std::get<1>(i) && state == std::get<0>(i)){
                return 2;
            }
        }
        return 0;
    } else {
        state = std::get<0>(it.second);
        paper[location] = std::get<1>(it.second);
        int old = location;
        location += (int) std::get<2>(it.second);
        if (location < 0 || location >= paper.length())
            location = old;
        return 1;
    }
}

bool TM::_read_rules(const std::string &address) {
    std::ifstream file(address);
    if (!file.is_open())
        return false;
    std::string line;
    while (std::getline(file, line)) {
        if(line == "Stop")
            break;
        auto fir = std::make_tuple(int(line[0] - '0'), line[2]);
        Direction d;
        switch (line[8]){
            case 'S':
                d = S;
                break;
            case 'R':
                d = R;
                break;
            case 'L':
                d = L;
        }
        auto sec = std::make_tuple(int(line[4] - '0'), line[6], d);
        std::pair<std::tuple<int, char>, std::tuple<int, char, Direction>> p(fir, sec);
        rules.insert(p);
    }
    while(std::getline(file, line)){
        if(line == "End")
            break;
        auto fir = std::make_tuple(int(line[0] - '0'), line[2]);
        stops.emplace_back(fir);
    }
    return true;
}




