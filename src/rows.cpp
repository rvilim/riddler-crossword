//
// Created by Ryan Vilim on 2019-01-28.
//

#include <set>
#include <bitset>
#include <iostream>

#include "masks.h"
#include "rows.h"
#include "params.h"


std::bitset<N> ReverseBitset(const std::bitset<N>& row){
    std::bitset<N> reversed_row;
    for(std::size_t i = 0; i < N; ++i) {
        reversed_row[i]=row[N-i-1];
    }

    return reversed_row;
}

bool IsValid3Row(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3){
    // This returns whether the 3 row is valid or not (row1 being the highest). You get this by writing out the truth
    // table and simplifying.

    return ((~row1) | row2 | (~row3)).all();
}

bool IsValid4Row(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3, std::bitset<N> row4){
    // This returns whether the 4 row is valid or not (row1 being the highest). You get this by writing out the truth
    // table and simplifying.

    return (((~row1) & (~row2)) | ((~row3) & (~row4)) | ((row2) & (row3))).all();
}

bool IsValidLastRow(const std::set<std::bitset<N>, MaskCmp>& masks, const std::bitset<N>& row1,
                    const std::bitset<N>& row2, const std::bitset<N>& row3, std::bitset<N>& row4){
    auto reversed_row3 = ReverseBitset(row3);
    auto reversed_row2 = ReverseBitset(row2);

    if (!((IsValid4Row(row1, row2, row3, row4)) && (IsValid4Row(row2, row3, row4, reversed_row3)) &&
            (IsValid4Row(row3, row4, reversed_row3, reversed_row2)))){
        return false;
    }
    return true;
}

std::vector<std::bitset<N> > GetValidRows() {
    std::vector<std::bitset<N> > valids;

    for(unsigned int i=0; i< 1<<N; i++){
        std::bitset<N> i_bits(i);
        if (ValidRow(i_bits)){
            valids.push_back(i_bits);
        }
    }

    return valids;
}

std::vector<std::bitset<N> > GetValidSymmetricRows(std::vector<std::bitset<N> > valids) {
    // Takes a vector of rows by value, then returns this with the non-symmetric rows removed

    valids.erase(std::remove_if(valids.begin(),
                                valids.end(),
                              [](std::bitset<N> x){return ReverseBitset(x)!=x;}),
                 valids.end());
    return valids;
}

bool ValidRow(std::bitset<N> n){
    for(unsigned int i=0; i<=N-3; i++){
        if (n.test(i) && !n.test(i+1) && n.test(i+2)){
            return false;
        }
    }

    for(unsigned int i=0; i<=N-4; i++){
        if (n.test(i) && !n.test(i+1) && !n.test(i+2) && n.test(i+3)){
            return false;
        }
    }

    if ((!n.test(0) && n.test(1)) || (!n.test(0) && !n.test(1) && n.test(2))) {
        return false;
    }

    if ((!n.test(N-1) && n.test(N-2)) || (!n.test(N-1) && !n.test(N-2) && n.test(N-3))) {
        return false;
    }

    return true;
}

