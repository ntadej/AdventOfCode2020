#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

int part_one(const std::vector<int> &inputs)
{
  const int target{2020};
  std::unordered_set<int> diffs;

  for (int number : inputs) {
    auto it = diffs.find(target - number);
    if (it != diffs.end()) {
      return number * (*it);
    }

    diffs.emplace(number);
  }

  throw std::runtime_error("No result!");
}

int part_two(const std::vector<int> &inputs)
{
  const int target{2020};
  std::unordered_set<int> diffs;

  for (auto i = inputs.begin(); i != inputs.end(); ++i) {
    for (auto j = std::next(i); j != inputs.end(); ++j) {
      auto it = diffs.find(target - *i - *j);
      if (it != diffs.end()) {
        return (*it) * (*i) * (*j);
      }

      diffs.emplace(*i);
    }
  }

  throw std::runtime_error("No result!");
}

int main(int argc, char **argv)
{
  std::filesystem::path file = std::string(argv[0]) + ".txt";
  file = file.filename();
  if (argc >= 2) {
    file = argv[1];
  }

  std::ifstream input_file(file);
  if (!input_file.is_open()) {
    std::cerr << "Input file " << file << " can not be opened!" << std::endl;
    return 10;
  }
  std::vector<int> inputs;
  do {
    int number{};
    input_file >> number;
    inputs.emplace_back(number);
  } while (!input_file.eof());

  int target_one{355875};
  int result_one = part_one(inputs);
  bool ok_one = target_one == result_one;
  std::cout << "Part 1: " << target_one << (ok_one ? " == " : " != ") << result_one << std::endl;
  if (!ok_one) {
    return 1;
  }

  int target_two{140379120};
  int result_two = part_two(inputs);
  bool ok_two = target_two == result_two;
  std::cout << "Part 2: " << target_two << (ok_two ? " == " : " != ") << result_two << std::endl;
  if (!ok_two) {
    return 2;
  }

  return 0;
}
