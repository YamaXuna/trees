//
// Created by USER on 18/04/2023.
//

#include "tree/tree.h"
#include <iostream>

using namespace xuna;

void creation_test(){
    tree t(1);
    tree t2(2, t, tree(3, tree(4), tree(5)));

    dfs(t2, [](const int &a){
        std::cout << a << ' ';
    });
}

int main(){
    creation_test();
}