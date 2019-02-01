//
// Created by Ryan Vilim on 2019-01-28.
//

#ifndef RIDDLER_CROSSWORD_PARAMS_H
#define RIDDLER_CROSSWORD_PARAMS_H

// The size of the crossword grid.
#ifdef TESTING
    // Don't change this unless you've changed the tests, they have a ton of hard coded bitsets of length 8
    const int N=8;
#else
    const int N=7;
#endif

#endif //RIDDLER_CROSSWORD_PARAMS_H
