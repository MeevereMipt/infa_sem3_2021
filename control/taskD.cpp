//
// Created by Meevere on 18.11.2021.
//

#include "taskD.h"

#include <iostream>
#include <fstream>

struct Data {
    int time_stamp;
    int id;
    float vit_d;
    float acat;
    float anti_tg;
    float neural_activity;
    float mch;

    Data(): Data(0,0,0,0,0,0,0) {};
    Data(int timeStamp, int id, float vitD, float acat, float antiTg, float neuralActivity, float mch)
            : time_stamp(timeStamp), id(id), vit_d(vitD), acat(acat), anti_tg(antiTg), neural_activity(neuralActivity), mch(mch){}
};

std::ostream & operator << (std::ostream& os, const Data& data){
    return os   << data.time_stamp  << ' '
                << data.id          << ' '
                << data.vit_d       << ' '
                << data.acat        << ' '
                << data.anti_tg     << ' '
                << data.neural_activity << ' '
                << data.mch;
}

std::istream & operator >> (std::istream& is, Data& data){
    return is >> data.time_stamp
              >> data.id
              >> data.vit_d
              >> data.acat
              >> data.anti_tg
              >> data.neural_activity
              >> data.mch;
}

bool operator <(const Data& a, const Data& b){
    return a.neural_activity < b.neural_activity;
}

// What is the best data structure for that task?
// It's best to insert with O(1) with the same id
// so it's unordered_map of unordered_multimap. But at the same time we have multiple instances with same id
// So it's unordered_multimap then

// But then - how we would sort unordered_multimap...
// What about multiset? No - we need to update order in set with each entry
// But we can construct a multiset from multimap with proper ordering and then - get the desired result by lower_bound();
// neat

#include <map>
#include <set>
#include <functional>

float neural_diff(const std::multiset<Data>& set){
    if(set.size() == 1)
        return -1;
    return (*set.crbegin()).neural_activity - (*set.cbegin()).neural_activity;
}

int taskD() {

    std::ifstream fs;
    fs.open("../control/taskD.input");

    std::istream& is(fs);
    std::ostream& os(std::cout);

    std::map<int, std::multiset<Data>> map;

    int N; is >> N;
    for(int i=0; i<N; ++i){
        Data temp;
        is >> temp;
        if(map.count(temp.id) == 0){
            // O(1)
            map.emplace(temp.id,std::multiset<Data>{temp});
        } else {
            // O(ln(n) where n - amount of data samples with same id
            map.at(temp.id).emplace(temp);
        }
    }

    for(auto& it : map) {
        os << it.first << '\n';
        for(auto& it2 : it.second) {
            os << it2 << '\n';
        }
        os << '\n';
    }


    // Effectively sorting for O(N ln(n)) in best cases (with n << N), N - amount of entries
    auto comparer = [&map](int a, int b){
        return neural_diff(map[a]) < neural_diff(map[b]);
    };

    // Now we need to find bad boys by placing it in set
    // O(N log N)
    // Because there we have N log N can omit unordered map and get the ordered one
    std::multiset<int, std::function<bool(int,int)>> set(std::function<bool(int,int)>{comparer});

    for(auto & it : map){
        // we guarantee that we do not suspect members with only one entry
        if(it.second.size() == 1) continue;
        set.emplace(it.first);
    }

    if(!set.empty()) {
        auto it = set.begin();
        for (int i = 0; (i < 3) and (it != set.end()); ++i) {
            os << *it << ' ';
            ++it;
        }
    } else {
        os << -1;
    }

    return 0;
}

