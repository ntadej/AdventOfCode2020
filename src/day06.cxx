#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>

size_t part_one(const std::filesystem::path &file)
{
  std::ifstream input_file(file);

  size_t counter{};

  std::set<char> current;
  std::string line;
  while (std::getline(input_file, line)) {
    if (line.empty()) {
      counter += current.size();
      current.clear();
      continue;
    }

    for (char c : line) {
      current.emplace(c);
    }
  }

  // Last one
  counter += current.size();

  return counter;
}

size_t part_two(const std::filesystem::path &file)
{
  std::ifstream input_file(file);

  size_t counter{};

  bool first{true};
  std::set<char> current;
  std::set<char> single;
  std::string line;
  while (std::getline(input_file, line)) {
    if (line.empty()) {
      counter += current.size();
      current.clear();
      single.clear();
      first = true;
      continue;
    }

    if (first) {
      first = false;
      for (char c : line) {
        current.emplace(c);
      }
    } else {
      single.clear();
      for (char c : line) {
        single.emplace(c);
      }
      std::set<char> updated;
      std::set_intersection(current.begin(), current.end(), single.begin(), single.end(), std::inserter(updated, updated.begin()));

      current = std::move(updated);
    }
  }

  // Last one
  counter += current.size();

  return counter;
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
  input_file.close();

  size_t target_one{6686};
  size_t result_one = part_one(file);
  bool ok_one = target_one == result_one;
  std::cout << "Part 1: " << target_one << (ok_one ? " == " : " != ") << result_one << std::endl;
  if (!ok_one) {
    return 1;
  }

  size_t target_two{3476};
  size_t result_two = part_two(file);
  bool ok_two = target_two == result_two;
  std::cout << "Part 2: " << target_two << (ok_two ? " == " : " != ") << result_two << std::endl;
  if (!ok_two) {
    return 2;
  }

  return 0;
}
