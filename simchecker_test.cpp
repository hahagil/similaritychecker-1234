#include "gmock/gmock.h"
#include "simchecker.h"

using namespace testing;

class SimCheckerFixture : public Test {
protected:
    SimChecker checker;
};

class SimCheckerLengthScore : public SimCheckerFixture {};
class SimCheckerAlphaScore  : public SimCheckerFixture {};
class SimCheckerTotalScore  : public SimCheckerFixture {};

TEST_F(SimCheckerLengthScore, SameLength_Returns60) {
    EXPECT_DOUBLE_EQ(60.0, checker.calcLengthScore("hello", "world"));
}

TEST_F(SimCheckerLengthScore, SlightlyDifferentLength_ReturnsPartialScore) {
    // 4 vs 5: gap=1, B=4, (1 - 1/4) * 60 = 45.0
    EXPECT_DOUBLE_EQ(45.0, checker.calcLengthScore("abcd", "abcde"));
}

TEST_F(SimCheckerLengthScore, ExactlyDoubleDifference_Returns0) {
    // 2 vs 4: gap=2, B=2, (1 - 2/2) * 60 = 0.0
    EXPECT_DOUBLE_EQ(0.0, checker.calcLengthScore("ab", "abcd"));
}

TEST_F(SimCheckerLengthScore, MoreThanDoubleDifference_Returns0) {
    // 1 vs 3: longer(3) >= 2 * shorter(1)
    EXPECT_DOUBLE_EQ(0.0, checker.calcLengthScore("a", "abc"));
}

TEST_F(SimCheckerLengthScore, NonIntegerResult_RetainsPrecision) {
    // 7 vs 11: gap=4, B=7, (1 - 4/7) * 60 = 180/7 ≈ 25.714...
    EXPECT_DOUBLE_EQ((3.0 / 7.0) * 60.0, checker.calcLengthScore("aaaaaaa", "aaaaaaaaaaa"));
}

TEST_F(SimCheckerAlphaScore, SameAlphabets_Returns40) {
    // {H,E,L,O} vs {H,E,L,O}: TotalCnt=4, SameCnt=4, (4/4)*40 = 40.0
    EXPECT_DOUBLE_EQ(40.0, checker.calcAlphaScore("HELLO", "HELLO"));
}

TEST_F(SimCheckerAlphaScore, CompletelyDifferentAlphabets_Returns0) {
    // {A,B,C} vs {D,E,F}: TotalCnt=6, SameCnt=0, (0/6)*40 = 0.0
    EXPECT_DOUBLE_EQ(0.0, checker.calcAlphaScore("ABC", "DEF"));
}

TEST_F(SimCheckerAlphaScore, PartialOverlap_ReturnsPartialScore) {
    // {A,B,C} vs {B,C,D}: TotalCnt=4, SameCnt=2, (2/4)*40 = 20.0
    EXPECT_DOUBLE_EQ(20.0, checker.calcAlphaScore("ABC", "BCD"));
}

TEST_F(SimCheckerAlphaScore, IgnoresLowercase) {
    // "abc" uppercase={}, "ABC" uppercase={A,B,C}: TotalCnt=3, SameCnt=0, (0/3)*40 = 0.0
    EXPECT_DOUBLE_EQ(0.0, checker.calcAlphaScore("abc", "ABC"));
}

TEST_F(SimCheckerTotalScore, IdenticalStrings_Returns100) {
    // LengthScore=60.0 (5:5) + AlphaScore=40.0 ({H,E,L,O} identical) = 100.0
    EXPECT_DOUBLE_EQ(100.0, checker.calcScore("HELLO", "HELLO"));
}

TEST_F(SimCheckerTotalScore, DoubleLengthWithPartialAlpha_ReturnsAlphaScoreOnly) {
    // LengthScore=0.0 (2:4, 2x), AlphaScore: {A,B} vs {A,B,C,D} TotalCnt=4, SameCnt=2 -> 20.0
    EXPECT_DOUBLE_EQ(20.0, checker.calcScore("AB", "ABCD"));
}
