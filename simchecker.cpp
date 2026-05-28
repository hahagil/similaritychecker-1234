#include "simchecker.h"
#include <algorithm>

int SimChecker::calcLengthScore(const std::string& a, const std::string& b) const {
    int longer  = static_cast<int>(std::max(a.size(), b.size()));
    int shorter = static_cast<int>(std::min(a.size(), b.size()));

    if (longer >= 2 * shorter)
        return 0;

    int gap = longer - shorter;
    return static_cast<int>((1.0 - static_cast<double>(gap) / shorter) * 60);
}
