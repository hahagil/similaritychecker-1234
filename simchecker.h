#pragma once
#include <set>
#include <string>

class SimChecker {
public:
    double calcLengthScore(const std::string& a, const std::string& b) const;
    double calcAlphaScore(const std::string& a, const std::string& b) const;
    double calcScore(const std::string& a, const std::string& b) const;

private:
    int longerLength(const std::string& a, const std::string& b) const;
    int shorterLength(const std::string& a, const std::string& b) const;
    std::set<char> upperAlphaSet(const std::string& s) const;
};
