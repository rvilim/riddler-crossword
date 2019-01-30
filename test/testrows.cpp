//
// Created by Ryan Vilim on 2019-01-28.
//

#include "catch.hpp"
#include <bitset>
#include "../src/params.h"
#include "../src/rows.h"

TEST_CASE( "Row reversed", "[row]" ) {
    std::bitset<N> row1(std::string("00010010"));
    std::bitset<N> row2(std::string("00000000"));
    std::bitset<N> row3(std::string("11111111"));

    std::bitset<N> row_reversed1(std::string("01001000"));
    std::bitset<N> row_reversed2=row2;
    std::bitset<N> row_reversed3=row3;

    REQUIRE(row_reversed1==ReverseBitset(row1));
    REQUIRE(row_reversed2==ReverseBitset(row2));
    REQUIRE(row_reversed3==ReverseBitset(row3));
}

TEST_CASE("Valid row", "[row]") {
    std::bitset<N> row1(std::string("10111111"));
    std::bitset<N> row2(std::string("00010000"));
    std::bitset<N> row3(std::string("00010010"));
    std::bitset<N> row4(std::string("00111000"));
    std::bitset<N> row5(std::string("00011000"));

    REQUIRE(ValidRow(row1)==false);
    REQUIRE(ValidRow(row2)==true);
    REQUIRE(ValidRow(row3)==false);
    REQUIRE(ValidRow(row4)==false);
    REQUIRE(ValidRow(row5)==true);
}

TEST_CASE("Valid 4 row", "[row]"){
    //Test 1
    std::bitset<N> row1_1         (std::string("10010011"));
    std::bitset<N> row2_1         (std::string("00010010"));
    std::bitset<N> row3_1         (std::string("00010010"));
    std::bitset<N> row4_1_invalid (std::string("10110010"));
    std::bitset<N> row4_1_valid   (std::string("00100010"));

    REQUIRE(IsValid4Row(row1_1, row2_1, row3_1, row4_1_valid)==true);
    REQUIRE(IsValid4Row(row1_1, row2_1, row3_1, row4_1_invalid)==false);

    //Test 2
    std::bitset<N> row1_2         (std::string("11111111"));
    std::bitset<N> row2_2         (std::string("11111111"));
    std::bitset<N> row3_2         (std::string("11111111"));
    std::bitset<N> row4_2_valid   (std::string("11111111"));

    REQUIRE(IsValid4Row(row1_2, row2_2, row3_2, row4_2_valid)==true);

    //Test 3
    std::bitset<N> row1_3         (std::string("11111111"));
    std::bitset<N> row2_3         (std::string("11111111"));
    std::bitset<N> row3_3         (std::string("11100000"));
    std::bitset<N> row4_3_valid   (std::string("11000000"));

    REQUIRE(IsValid4Row(row1_3, row2_3, row3_3, row4_3_valid)==true);

}

TEST_CASE("Valid 3 row", "[row]"){
    //Test 1
    std::bitset<N> row1_1         (std::string("10010011"));
    std::bitset<N> row2_1         (std::string("00010010"));
    std::bitset<N> row3_1_valid   (std::string("00100010"));
    std::bitset<N> row3_1_invalid (std::string("10100010"));
    std::bitset<N> row3_1_invalid_2 (std::string("10100011"));

    REQUIRE(IsValid3Row(row1_1, row2_1, row3_1_valid)==true);
    REQUIRE(IsValid3Row(row1_1, row2_1, row3_1_invalid)==false);
    REQUIRE(IsValid3Row(row1_1, row2_1, row3_1_invalid_2)==false);

    //Test 2
    std::bitset<N> row1_2         (std::string("11111111"));
    std::bitset<N> row2_2         (std::string("11000001"));
    std::bitset<N> row3_2_valid   (std::string("00000001"));
    std::bitset<N> row3_2_invalid (std::string("00000011"));

    REQUIRE(IsValid3Row(row1_2, row2_2, row3_2_valid)==true);
    REQUIRE(IsValid3Row(row1_2, row2_2, row3_2_invalid)==false);
}


TEST_CASE("Valid last row", "[row]"){
    //Test 1
    std::set<std::bitset<N>, MaskCmp> masks;

    std::bitset<N> row1_1         (std::string("11111111"));
    std::bitset<N> row2_1         (std::string("11100000"));
    std::bitset<N> row3_1         (std::string("10000000"));
    std::bitset<N> row4_1_valid   (std::string("00000000"));
    std::bitset<N> row4_1_invalid (std::string("00110010"));


    REQUIRE(IsValidLastRow(masks, row1_1, row2_1, row3_1, row4_1_valid)==true);
    REQUIRE(IsValidLastRow(masks, row1_1, row2_1, row3_1, row4_1_invalid)==false);

    //Test 2
    std::bitset<N> row1_2         (std::string("11111111"));
    std::bitset<N> row2_2         (std::string("11111111"));
    std::bitset<N> row3_2         (std::string("11101111"));
    std::bitset<N> row4_2_valid   (std::string("11101111"));

    REQUIRE(IsValidLastRow(masks, row1_2, row2_2, row3_2, row4_2_valid)==false);

    //Test 3
    std::bitset<N> row1_3         (std::string("11111111"));
    std::bitset<N> row2_3         (std::string("11111111"));
    std::bitset<N> row3_3         (std::string("11111111"));
    std::bitset<N> row4_3_valid   (std::string("11111111"));

    REQUIRE(IsValidLastRow(masks, row1_3, row2_3, row3_3, row4_3_valid)==true);

}