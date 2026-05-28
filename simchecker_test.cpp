#include "gmock/gmock.h"
#include "simchecker.h"

using namespace testing;

TEST(SimCheckerLengthScore, SameLength_Returns60) {
    SimChecker checker;
    EXPECT_DOUBLE_EQ(60.0, checker.calcLengthScore("hello", "world"));
}

TEST(SimCheckerLengthScore, SlightlyDifferentLength_ReturnsPartialScore) {
    SimChecker checker;
    // 4 vs 5: gap=1, B=4, (1 - 1/4) * 60 = 45.0
    EXPECT_DOUBLE_EQ(45.0, checker.calcLengthScore("abcd", "abcde"));
}

TEST(SimCheckerLengthScore, ExactlyDoubleDifference_Returns0) {
    SimChecker checker;
    // 2 vs 4: gap=2, B=2, (1 - 2/2) * 60 = 0.0
    EXPECT_DOUBLE_EQ(0.0, checker.calcLengthScore("ab", "abcd"));
}

TEST(SimCheckerLengthScore, MoreThanDoubleDifference_Returns0) {
    SimChecker checker;
    // 1 vs 3: longer(3) >= 2 * shorter(1)
    EXPECT_DOUBLE_EQ(0.0, checker.calcLengthScore("a", "abc"));
}

TEST(SimCheckerLengthScore, NonIntegerResult_RetainsPrecision) {
    SimChecker checker;
    // 7 vs 11: gap=4, B=7, (1 - 4/7) * 60 = 180/7 ≈ 25.714...
    EXPECT_DOUBLE_EQ((3.0 / 7.0) * 60.0, checker.calcLengthScore("aaaaaaa", "aaaaaaaaaaa"));
}

TEST(SimCheckerAlphaScore, SameAlphabets_Returns40) {
    SimChecker checker;
    // {H,E,L,O} vs {H,E,L,O}: TotalCnt=4, SameCnt=4, (4/4)*40 = 40.0
    EXPECT_DOUBLE_EQ(40.0, checker.calcAlphaScore("HELLO", "HELLO"));
}

TEST(SimCheckerAlphaScore, CompletelyDifferentAlphabets_Returns0) {
    SimChecker checker;
    // {A,B,C} vs {D,E,F}: TotalCnt=6, SameCnt=0, (0/6)*40 = 0.0
    EXPECT_DOUBLE_EQ(0.0, checker.calcAlphaScore("ABC", "DEF"));
}

TEST(SimCheckerAlphaScore, PartialOverlap_ReturnsPartialScore) {
    SimChecker checker;
    // {A,B,C} vs {B,C,D}: TotalCnt=4, SameCnt=2, (2/4)*40 = 20.0
    EXPECT_DOUBLE_EQ(20.0, checker.calcAlphaScore("ABC", "BCD"));
}

TEST(SimCheckerAlphaScore, IgnoresLowercase) {
    SimChecker checker;
    // "abc" uppercase={}, "ABC" uppercase={A,B,C}: TotalCnt=3, SameCnt=0, (0/3)*40 = 0.0
    EXPECT_DOUBLE_EQ(0.0, checker.calcAlphaScore("abc", "ABC"));
}

TEST(SimCheckerTotalScore, IdenticalStrings_Returns100) {
    SimChecker checker;
    // LengthScore=60.0 (5:5) + AlphaScore=40.0 ({H,E,L,O} identical) = 100.0
    EXPECT_DOUBLE_EQ(100.0, checker.calcScore("HELLO", "HELLO"));
}

TEST(SimCheckerTotalScore, DoubleLengthWithPartialAlpha_ReturnsAlphaScoreOnly) {
    SimChecker checker;
    // LengthScore=0.0 (2:4, 2x), AlphaScore: {A,B} vs {A,B,C,D} TotalCnt=4, SameCnt=2 -> 20.0
    EXPECT_DOUBLE_EQ(20.0, checker.calcScore("AB", "ABCD"));
}
