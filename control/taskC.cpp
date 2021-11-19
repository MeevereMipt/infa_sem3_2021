//
// Created by Meevere on 19.11.2021.
//

#include "taskC.h"

#include <iostream>
#include <fstream>
#include <vector>

// Why the fuck standard library does not contain this function??
std::vector<std::string> explode(const std::string& str, char delimiter){
    std::vector<std::string> out{""};
    int i=0;
    for(auto symbol : str){
        if(symbol != delimiter) {
            out[i].push_back(symbol);
        } else {
            out.emplace_back("");
            ++i;
        }
    }
    out.pop_back();
    return out;
}


/////////////////////////////////////////////////////////////////
// Date struct

struct Date {
    int year;
    int month;
    int day;

    Date() = default;
    Date(const Date& other) = default;
    Date& operator=(const Date& other) = default;

    Date(const std::string& date){ // NOLINT(google-explicit-constructor)
        auto temp = explode(date, '.');
        day = std::stoi(temp[0]);
        month = std::stoi(temp[1]);
        year = std::stoi(temp[2]);
    }

    friend bool operator<(const Date &lhs, const Date &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Date &date);
};

std::ostream &operator<<(std::ostream &os, const Date &date) {
    os << "year: " << date.year << " month: " << date.month << " day: " << date.day;
    return os;
}

std::istream &operator>>(std::istream &is, Date &date) {
    std::string temp;
    is >> temp;
    date = Date(temp);
    return is;
}

bool operator<(const Date &lhs, const Date &rhs) {
    if (lhs.year < rhs.year)
        return true;
    if (rhs.year < lhs.year)
        return false;
    if (lhs.month < rhs.month)
        return true;
    if (rhs.month < lhs.month)
        return false;
    return lhs.day < rhs.day;
}

/////////////////////////////////////////////////////////////////
// main

#include <map>

int taskC(){
    int N, M;

    std::ifstream fs;
    fs.open("../control/taskC.input");

    std::istream& is(fs);
    std::ostream& os(std::cout);

    std::map<Date, int> container;

    is >> N;
    for (int i = 0; i < N; ++i) {
        Date date{}; int amount;
        is >> date >> amount;

        // If no element
        auto it = container.find(date);
        if(it == container.end()){
            container.emplace(date, amount);
        } else {
            if( it->second < amount ){
                it->second = amount;
            }
        }
    }

    // and there we mess our data!
    int temp = container.begin()->second;
    for(auto& it : container){
        if( it.second < temp )
            it.second = temp;
        else
            temp = it.second;
    }

    is >> M;
    for (int i = 0; i < M; ++i) {
        Date date{};
        is >> date;

        auto it = container.upper_bound(date);
        if (it == container.begin()) {
            os << 0 << '\n';
            continue;
        }
        --it;
        os << it->second << '\n'; // because iterator is always a good one
    }

    fs.close();
    return 0;
}