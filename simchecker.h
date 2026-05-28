#pragma once
#include <set>
#include <stdexcept>
#include <string>

class SimChecker {
public:
    double calcLengthScore(const std::string& a, const std::string& b) const;
    double calcAlphaScore(const std::string& a, const std::string& b) const;
    double calcScore(const std::string& a, const std::string& b) const;

private:
    int longerLength(const std::string& a, const std::string& b) const;
    int shorterLength(const std::string& a, const std::string& b) const;
    void validateUpperOnly(const std::string& s) const;
    int intersectSize(const std::set<char>& a, const std::set<char>& b) const;
};
