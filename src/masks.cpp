//
// Created by Ryan Vilim on 2019-01-28.
//
#include <iostream>
#include <set>
#include "masks.h"

std::array<std::vector<std::bitset<N> >, 1<<N > GetSegmentedMasks(){
    std::array<std::vector<std::bitset<N> >, 1<<N > segmented_masks;

    for (int i=0; i< 1<<N ; i++){
        std::bitset<N> mask(i);

        auto masks = SegmentMask(mask);

        for (int j=0;j<masks.size(); j++){
            std::cout<<masks[j]<<", ";
        }
        std::cout<<std::endl;
        segmented_masks[i]=masks;
    }
    return segmented_masks;
}

std::vector<std::bitset<N>> SegmentMask(std::bitset<N> &mask){
    bool inrange=false;
    std::vector<std::bitset<N>> masks;
    /*
     * This function returns the masks given only a bitset, so it splits up a row into multiple contiguous chunks of
     * zeros, then applies the not operation. For example
     *
     * 100100101 -> 011000000, 000011000, 00000010
     *
     */

    if (mask.all()){
        return masks;
    }

    for(unsigned int i=0; i<N; i++){

        if (!mask.test(i)){
            if(!inrange) {
                std::bitset<N> m;
                masks.push_back(m);
                inrange=true;
            }
            masks[masks.size()-1].set(i,true);
        }

        if (mask.test(i) && inrange){
            inrange=false;
        }
    }

    return masks;
}

std::set<std::bitset<N>, MaskCmp> GetNewMasks(std::bitset<N> &prevrow, std::bitset<N> &currentrow, std::vector<std::bitset<N>> &prevmasks) {
    std::set<std::bitset<N>, MaskCmp> newmasks;

    for (const std::bitset<N>& prevmask : prevmasks){
        std::bitset<N> newmask = (~currentrow & (prevmask | prevrow));

        if (newmask.any()){
            newmasks.emplace(newmask);
        }

    }
    return newmasks;
}
