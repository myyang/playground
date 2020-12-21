#ifndef LEETCODE_UTILS_H
#define LEETCODE_UTILS_H

#include <vector>
#include <string>

void printV(std::vector<int>& t) {
    for (auto i: t) {
        printf("%d ", i);
    }
    printf("\n===============\n");
}

void print2DV(std::vector<std::vector<int>>& t) {
    for (auto r: t)
    {
        for (auto i: r)
            printf("%d ", i);
        printf("\n");
    }
    printf("===============\n");
}

void printVstr(std::vector<std::string>& t) {
    for (auto i: t) {
        printf("%s ", i.c_str());
    }
    printf("\n===============\n");
}

#endif
