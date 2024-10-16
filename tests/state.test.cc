#include <gtest/gtest.h>
#include "aes.h"

// Unit tests for the State class. Includes testing of state manipulations
// required for the round function

using namespace aes;

TEST(StateInitTest, RejectsInvalidBlockLengths) {
    EXPECT_THROW(State a(0), InitialisationError);
    EXPECT_THROW(State a(129), InitialisationError);
    EXPECT_THROW(State a(288), InitialisationError);
}

TEST(StateInitTest, AcceptsValidBlockLengths) {
    EXPECT_NO_THROW(State a());
    EXPECT_NO_THROW(State a(128));
    EXPECT_NO_THROW(State a(256));
    EXPECT_NO_THROW(State a(224));
}

TEST(StateInitTest, CorrectlyInitialisesState) {
    // Check that input is correctly copied to the state
    FAIL();
}

// Look into using a fixture for testing the different tranformations across
// block sizes?
TEST(StateManipulationTest, ShiftRows) {
    FAIL();
}

TEST(StateManipulationTest, ShiftRowsInverse) {
    FAIL();
}

TEST(StateManipulationTest, MixColumns) {
    FAIL();
}

TEST(StateManipulationTest, MixColumnsInverse) {
    FAIL();
}

TEST(StateManipulationTest, SubBytes) {
    FAIL();
}

TEST(StateManipulationTest, SubBytesInverse) {
    FAIL();
}


TEST(StateManipulationTest, RoundKeyApplication) {
    FAIL();
}
