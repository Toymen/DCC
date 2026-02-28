#include "include/detectors.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace {
bool check(const std::string& name, bool ok) {
  if (ok) {
    std::cout << "[PASS] " << name << '\n';
    return true;
  }
  std::cerr << "[FAIL] " << name << '\n';
  return false;
}
}  // namespace

int main() {
  bool allOk = true;
  const std::vector<std::string> names = RegisteredDetectorNames();
  const std::set<std::string> unique(names.begin(), names.end());

  allOk &= check("registry is not empty", !names.empty());
  allOk &= check("registry has unique detector names", names.size() == unique.size());
  allOk &= check("registry includes DELIGHTA", unique.count("DELIGHTA") == 1);
  allOk &= check("registry includes SHiPhsds", unique.count("SHiPhsds") == 1);
  allOk &= check("registry includes FCChhCT", unique.count("FCChhCT") == 1);
  allOk &= check("registry contains expected detector count", names.size() == 27);

  return allOk ? 0 : 1;
}
