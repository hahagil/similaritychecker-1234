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

std::set<char> SimChecker::upperAlphaSet(const std::string& s) const {
    std::set<char> result;
    for (char c : s)
        if (std::isupper(static_cast<unsigned char>(c)))
            result.insert(c);
    return result;
}

double SimChecker::calcAlphaScore(const std::string& a, const std::string& b) const {
    std::set<char> setA = upperAlphaSet(a);
    std::set<char> setB = upperAlphaSet(b);

    std::set<char> unionSet, intersectSet;
    std::set_union(setA.begin(), setA.end(), setB.begin(), setB.end(),
                   std::inserter(unionSet, unionSet.begin()));
    std::set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(),
                          std::inserter(intersectSet, intersectSet.begin()));

    int totalCnt = static_cast<int>(unionSet.size());
    int sameCnt  = static_cast<int>(intersectSet.size());

    if (totalCnt == 0)
        return 0.0;

    return (static_cast<double>(sameCnt) / totalCnt) * 40;
}

double SimChecker::calcScore(const std::string& a, const std::string& b) const {
    return calcLengthScore(a, b) + calcAlphaScore(a, b);
}
