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

TEST_CASE("Valid last row", "[row]"){
    std::bitset<N> row1         (std::string("10010011"));
    std::bitset<N> row2         (std::string("00010010"));
    std::bitset<N> row3         (std::string("00010010"));
    std::bitset<N> row4_valid   (std::string("00100010"));
    std::bitset<N> row4_invalid (std::string("10110010"));

    REQUIRE(IsValidLastRow(row1, row2, row3, row4_valid)==true);
    REQUIRE(IsValidLastRow(row1, row2, row3, row4_invalid)==false);

}

TEST_CASE("Valid 4 row", "[row]"){
    std::bitset<N> row1         (std::string("10010011"));
    std::bitset<N> row2         (std::string("00010010"));
    std::bitset<N> row3         (std::string("00010010"));
    std::bitset<N> row4_valid   (std::string("00100010"));
    std::bitset<N> row4_invalid (std::string("10110010"));

    REQUIRE(IsValid4Row(row1, row2, row3, row4_valid)==true);
    REQUIRE(IsValid4Row(row1, row2, row3, row4_invalid)==false);
}

TEST_CASE("Valid 3 row", "[row]"){
    std::bitset<N> row1         (std::string("10010011"));
    std::bitset<N> row2         (std::string("00010010"));
    std::bitset<N> row3_valid   (std::string("00100010"));
    std::bitset<N> row3_invalid (std::string("10100010"));
    std::bitset<N> row3_invalid_2 (std::string("10100011"));

    REQUIRE(IsValid3Row(row1, row2, row3_valid)==true);
    REQUIRE(IsValid3Row(row1, row2, row3_invalid)==false);
    REQUIRE(IsValid3Row(row1, row2, row3_invalid_2)==false);
}