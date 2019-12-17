#include "TM.h"

bool TM::init(const std::string &str, char s) {
    state = 0;
    location = 1;
    stop = s;
    paper = stop + str + stop;
    return _read_rules();
}

bool TM::read() {
    std::tuple<int, char> p(state, paper[location]);
    auto it = rules.find(p);
    if(it == rules.end()){
        return false;
    }else{
        state = std::get<0>(it->second);
        paper[location] = std::get<1>(it->second);
        
    }
}
