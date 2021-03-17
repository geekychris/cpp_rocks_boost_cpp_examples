//
// Created by Collins, Chris on 2/13/21.
//

#ifndef CPP_EXAMPLES_NEW_DAT_H
#define CPP_EXAMPLES_NEW_DAT_H

#endif //CPP_EXAMPLES_NEW_DAT_H
/*
void populate (auto &data) {
    data.insert({"a", {1,4}});
    data.insert({"b", {3,1}});
    data.insert({"c", {2,3}});
}

auto merge (auto data, auto upcoming_data) {
    auto result = data;
    for (auto it: upcoming_data) {
        result.insert(it);
    }
    return result;
}

int t () {
    std::map<std::string, std::pair<int,int>> data;
    populate(data);
    std::map<std::string, std::pair<int,int>> upcoming_data;
    upcoming_data.insert({"d", {5,3}});
    auto final_data = merge(data, upcoming_data);

    for (auto itr : final_data) {
        auto [v1, v2] = itr.second;
        std::cout << itr.first << " " << v1 << " " << v2 << std::endl;
    }
}

 */