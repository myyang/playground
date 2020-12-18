#ifndef LEETCODE_UTILS_H
#define LEETCODE_UTILS_H

#include <vector>

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

#endif
