#include "simchecker.h"
#include <algorithm>
#include <iterator>
#include <set>

int SimChecker::longerLength(const std::string& a, const std::string& b) const {
    return static_cast<int>(std::max(a.size(), b.size()));
}

int SimChecker::shorterLength(const std::string& a, const std::string& b) const {
    return static_cast<int>(std::min(a.size(), b.size()));
}

double SimChecker::calcLengthScore(const std::string& a, const std::string& b) const {
    int longer  = longerLength(a, b);
    int shorter = shorterLength(a, b);

    if (longer >= 2 * shorter)
        return 0.0;

    int gap = longer - shorter;
    return (1.0 - static_cast<double>(gap) / shorter) * 60;
}

void SimChecker::validateUpperOnly(const std::string& s) const {
    for (char c : s)
        if (!std::isupper(static_cast<unsigned char>(c)))
            throw std::invalid_argument("Input must contain only uppercase letters");
}

double SimChecker::calcAlphaScore(const std::string& a, const std::string& b) const {
    validateUpperOnly(a);
    validateUpperOnly(b);

    std::set<char> setA(a.begin(), a.end());
    std::set<char> setB(b.begin(), b.end());

    std::set<char> intersectSet;
    std::set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(),
                          std::inserter(intersectSet, intersectSet.begin()));

    int sameCnt  = static_cast<int>(intersectSet.size());
    int totalCnt = static_cast<int>(setA.size() + setB.size()) - sameCnt;

    if (totalCnt == 0)
        return 0.0;

    return (static_cast<double>(sameCnt) / totalCnt) * 40;
}

double SimChecker::calcScore(const std::string& a, const std::string& b) const {
    return calcLengthScore(a, b) + calcAlphaScore(a, b);
}
