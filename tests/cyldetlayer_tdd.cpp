#include "include/CCylDetLayer.h"

#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

namespace {

bool nearlyEqual(double a, double b, double eps = 1e-9) {
    return std::abs(a - b) <= eps;
}

bool runCase(const std::string& name, bool ok) {
    if (!ok) {
        std::cerr << "[FAIL] " << name << '\n';
        return false;
    }
    std::cout << "[PASS] " << name << '\n';
    return true;
}

}  // namespace

int main() {
    bool allOk = true;

    const std::vector<std::array<double, 2>> uniqueRect = {
        {5.0, 26.0}, {15.0, 26.0}, {15.0, 36.0}, {5.0, 36.0}};

    const std::vector<std::array<double, 2>> duplicateRect = {
        {5.0, 26.0}, {15.0, 26.0}, {15.0, 36.0},
        {5.0, 36.0}, {15.0, 36.0}, {5.0, 26.0}};

    const std::vector<std::array<double, 2>> shuffledDuplicates = {
        {15.0, 36.0}, {5.0, 26.0}, {15.0, 26.0},
        {5.0, 36.0},  {5.0, 26.0}, {15.0, 36.0}};

    CylDetLayer layerUnique(uniqueRect, 1.0);
    CylDetLayer layerDuplicate(duplicateRect, 1.0);
    CylDetLayer layerShuffled(shuffledDuplicates, 1.0);

    const double th = 1.35;
    const double leff = 100.0;

    const double pUnique = layerUnique.inDetDec(th, leff);
    const double pDuplicate = layerDuplicate.inDetDec(th, leff);
    const double pShuffled = layerShuffled.inDetDec(th, leff);

    allOk &= runCase("baseline unique rectangle gives non-zero probability", pUnique > 0.0);
    allOk &= runCase(
        "duplicate points should preserve geometry result",
        nearlyEqual(pDuplicate, pUnique, 1e-9));
    allOk &= runCase(
        "shuffled duplicate points should preserve geometry result",
        nearlyEqual(pShuffled, pUnique, 1e-9));

    if (!allOk) {
        return 1;
    }
    return 0;
}
