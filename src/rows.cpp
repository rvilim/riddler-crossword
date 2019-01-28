//
// Created by Ryan Vilim on 2019-01-28.
//

#include "rows.h"

std::bitset<N> ReverseBitset(std::bitset<N> row){
    for(std::size_t i = 0; i < N/2; ++i) {
        bool t = row[i];
        row[i] = row[N-i-1];
        row[N-i-1] = t;
    }

    return row;
}

bool IsValid3Row(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3){
    for(unsigned int i=0; i<N; i++){
        if (row1.test(i) && !row2.test(i) && row3.test(i)){
            return false;
        }
    }
    return true;
}

bool IsValid4Row(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3, std::bitset<N> row4){
    for(unsigned int i=0; i<N; i++){
        if (!IsValid4(row1.test(i), row2.test(i), row3.test(i), row4.test(i))){
            return false;
        }
    }
    return true;
}

bool IsValid4(bool bit1, bool bit2, bool bit3, bool bit4){
    return ( (!bit1 && !bit2) || (!bit3 && !bit4) || (bit2 && bit3 ));
}

bool IsValidLastRow(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3, std::bitset<N> row4){

    for(unsigned int i=0; i<N; i++){
        bool bit1 = row1.test(i);
        bool bit2 = row2.test(i);
        bool bit3 = row3.test(i);
        bool bit4 = row4.test(i);

        bool rbit1 = row1.test(N-i-1);
        bool rbit2 = row2.test(N-i-1);
        bool rbit3 = row3.test(N-i-1);

        if ( !(IsValid4(bit1, bit2, bit3, bit4)) || // 1 2 3 4
             !(IsValid4(bit2, bit3, bit4, rbit3)) || // 2 3 4 r3
             !(IsValid4(bit3, bit4, rbit3, rbit2)) || // 3 4 r3 r2
             !(IsValid4(bit4, rbit3, rbit2, rbit1)) ){ // 4 r3 r3 r1
            return false;
        }
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

