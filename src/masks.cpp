//
// Created by Ryan Vilim on 2019-01-28.
//
#include <iostream>
#include <set>
#include "masks.h"

std::array< std::set<std::bitset<N>,MaskCmp>, 1<<N > GetSegmentedMasks(){
    std::array< std::set<std::bitset<N>,MaskCmp>, 1<<N > segmented_masks;

    for (int i=0; i< 1<<N ; i++){
        std::bitset<N> mask(i);

        auto masks = SegmentMask(mask);

//        std::cout<<std::endl;
        segmented_masks[i]=masks;
    }
    return segmented_masks;
}

std::set<std::bitset<N>,MaskCmp> SegmentMask(std::bitset<N> &mask){
    bool inrange=false;
    std::vector<std::bitset<N>> masks;
    /*
     * This function returns the masks given only a bitset, so it splits up a row into multiple contiguous chunks of
     * zeros, then applies the not operation. For example
     *
     * 100100101 -> 011000000, 000011000, 00000010
     *
     * TODO(Ryan) Make this function less ugly. Currently it constructs a vector, then converts it to a set, this was
     *  because the set emplace function is super finnicky and I can't quite nail down how to get a reference to the
     *  last inserted item.
     */

    if (mask.all()){
        std::set<std::bitset<N>,MaskCmp> t(masks.begin(), masks.end());
        return t;
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

    std::set<std::bitset<N>,MaskCmp> t(masks.begin(), masks.end());
    return t;
}

std::set<std::bitset<N>, MaskCmp> GetNewMasks(std::bitset<N> &prevrow, std::bitset<N> &currentrow, std::set<std::bitset<N>, MaskCmp> &prevmasks) {
    /*
     * GetNewMasks takes in a previous row, a collection of previous masks and generates new masks (e.g. rows which are
     * not allowed due to connectivity reasons
     *
     * There are two ways a row can be disallowed due to connectivity reasons. For example
     *
     * Rows             Masks
     * 00000000         [11111111]            This is saying that the only row that is disallowed is all ones (makes sense, that immediately creates a white island)
     * 11011011         [00100000, 00000100]
     * 11111011
     *
     * If I place that last row I would like to know what my next masks are. In this case it should be [00000100]. This
     * can be quantified by saying that a mask is 1 if the current row is zero, and a previous mask was 1, e.g. if that column
     * was disallowed before, it remains disallowed. ~cr & pm   (current row = cr, previous mask = pm). Here we generate new
     * masks by iterating through the old mask and applying this.
     *
     * Taking a trickier example
     *
     * Rows             Masks
     * 00001000         [11110000, 00000111]
     * 11100000
     *
     * The same thing works: [00010000, 00000111], column 4 is importantly not blocked off, column 5 can be (though in
     * this specific case it will result in a 1 letter down word and not be a valid word in IsValid4Row or IsValid3Row
     *
     * The next case to consider is cases like this
     *
     * Rows             Masks
     * 11111001         [00000110]
     * 11101101
     *
     * Here the new mask has to be [00010000, 00000010]. The second of these is determined by the conditions we
     * previously discussed, but we need to add a condition to take generate the first mask. We want there to be a mask
     * in at the genesis of the zero. In this case we just add a new condition that anything that is zero in the
     * previous mask, and 1 on the previous row, and 0 in the current row should be considered a zero, which we then
     * feed into getmasks.
     */

    std::set<std::bitset<N>, MaskCmp> newmasks;

    if (prevrow.all()){
        return SegmentMask(currentrow);
    }

    for (const std::bitset<N>& prevmask : prevmasks){
        std::bitset<N> continuedmask = (~currentrow & prevmask);
        if (continuedmask.any()){
            newmasks.emplace(continuedmask);
        }

        // TODO(Ryan) This is super ugly and silly, don't loop over a set to add it.
        auto a = ~((~currentrow) & (~prevmask) & prevrow);
        std::set<std::bitset<N>, MaskCmp> x = SegmentMask(a);

        for (auto elem : x) {
            newmasks.insert(elem);
        }

    }

    return newmasks;
}
