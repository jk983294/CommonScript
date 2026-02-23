#include <iostream>
#include <string>
#include <boost/unordered/unordered_flat_map.hpp>

int main() {
  boost::unordered_flat_map<std::string, int> counts;

  counts["apple"]  = 3;
  counts["banana"] = 5;
  counts["cherry"] = 2;

  for (const auto& [fruit, cnt] : counts) {
      std::cout << fruit << " -> " << cnt << '\n';
  }
  std::cout << "size = " << counts.size() << '\n';
  return 0;
}