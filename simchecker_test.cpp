#include "gmock/gmock.h"
#include "simchecker.h"

using namespace testing;

TEST(SimCheckerLengthScore, SameLength_Returns60) {
    SimChecker checker;
    EXPECT_EQ(60, checker.calcLengthScore("hello", "world"));
}

TEST(SimCheckerLengthScore, SlightlyDifferentLength_ReturnsPartialScore) {
    SimChecker checker;
    // 4 vs 5: gap=1, B=4, (1 - 1/4) * 60 = 45
    EXPECT_EQ(45, checker.calcLengthScore("abcd", "abcde"));
}

TEST(SimCheckerLengthScore, ExactlyDoubleDifference_Returns0) {
    SimChecker checker;
    // 2 vs 4: gap=2, B=2, (1 - 2/2) * 60 = 0
    EXPECT_EQ(0, checker.calcLengthScore("ab", "abcd"));
}

TEST(SimCheckerLengthScore, MoreThanDoubleDifference_Returns0) {
    SimChecker checker;
    // 1 vs 3: longer(3) >= 2 * shorter(1)
    EXPECT_EQ(0, checker.calcLengthScore("a", "abc"));
}
