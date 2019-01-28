//
// Created by Ryan Vilim on 2019-01-28.
//

#include <bitset>
#include <algorithm>
#include <iostream>
#include <set>

#include "catch.hpp"
#include "../src/params.h"
#include "../src/masks.h"

TEST_CASE( "Segment mask", "[mask]" ) {
    std::bitset<N> row1(std::string("00010010"));
    std::bitset<N> row2(std::string("11111110"));
    std::bitset<N> row3(std::string("11111111"));
    std::bitset<N> row4(std::string("00000000"));
    std::bitset<N> row5(std::string("01111111"));


    // Test 1
    std::vector<std::bitset<N>> expected1 = {
            std::bitset<N>(std::string("11100000")),
            std::bitset<N>(std::string("00001100")),
            std::bitset<N>(std::string("00000001"))
            };

    auto segmented1 = SegmentMask(row1);

    std::sort(expected1.begin(), expected1.end(), [](const auto & lhs, const auto & rhs){ return lhs.to_string() < rhs.to_string(); });
    std::sort(segmented1.begin(), segmented1.end(), [](const auto & lhs, const auto & rhs){ return lhs.to_string() < rhs.to_string(); });

    REQUIRE(expected1==segmented1);

    // Test 2
    std::vector<std::bitset<N>> expected2 = {
            std::bitset<N>(std::string("00000001"))
    };
    auto segmented2 = SegmentMask(row2);

    REQUIRE(expected2==segmented2);

    // Test 3
    auto segmented3 = SegmentMask(row3);
    REQUIRE(segmented3.empty());

    // Test 4
    std::vector<std::bitset<N>> expected4 = {
            std::bitset<N>(std::string("11111111"))
    };

    auto segmented4 = SegmentMask(row4);
    REQUIRE(segmented4==expected4);
}


TEST_CASE( "Next Mask", "[mask]" ) {
    // Test 1
    std::bitset<N> prevrow1(std::string("00010000"));
    std::vector<std::bitset<N>> prevmasks1 = SegmentMask(prevrow1);
    std::bitset<N> currentrow1(std::string("11010001"));

    std::set<std::bitset<N>,MaskCmp> expected1 = { std::bitset<N>(std::string("00100000")),
                                             std::bitset<N>(std::string("00001110"))
    };

    REQUIRE(expected1==GetNewMasks(prevrow1, currentrow1, prevmasks1));

    // Test 2
    std::bitset<N> prevrow2(std::string("00000000"));
    std::vector<std::bitset<N>> prevmasks2 = SegmentMask(prevrow1);
    std::bitset<N> currentrow2(std::string("11011011"));

    std::set<std::bitset<N>,MaskCmp> expected2 = { std::bitset<N>(std::string("00100000")),
                                                   std::bitset<N>(std::string("00000100")) };

    REQUIRE(expected2==GetNewMasks(prevrow2, currentrow2, prevmasks2));

    // Test 3
    std::bitset<N> prevrow3(std::string("11111111"));
    std::vector<std::bitset<N>> prevmasks3 = SegmentMask(prevrow1);
    std::bitset<N> currentrow3(std::string("11101111"));

    std::set<std::bitset<N>,MaskCmp> expected3 = { std::bitset<N>(std::string("00010000")) };

    REQUIRE(expected3==GetNewMasks(prevrow3, currentrow3, prevmasks3));

}