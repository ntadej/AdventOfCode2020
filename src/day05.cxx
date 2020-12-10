#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

size_t part_one(const std::filesystem::path &file)
{
  std::ifstream input_file(file);

  size_t max{};
  std::string line;
  while (std::getline(input_file, line)) {
    std::replace(line.begin(), line.end(), 'F', '0');
    std::replace(line.begin(), line.end(), 'B', '1');
    std::replace(line.begin(), line.end(), 'L', '0');
    std::replace(line.begin(), line.end(), 'R', '1');
    size_t id = std::stoul(line, nullptr, 2);
    if (id > max) {
      max = id;
    }
  }

  return max;
}

size_t part_two(const std::filesystem::path &file)
{
  std::ifstream input_file(file);

  std::vector<size_t> ids;

  std::string line;
  while (std::getline(input_file, line)) {
    std::replace(line.begin(), line.end(), 'F', '0');
    std::replace(line.begin(), line.end(), 'B', '1');
    std::replace(line.begin(), line.end(), 'L', '0');
    std::replace(line.begin(), line.end(), 'R', '1');
    ids.emplace_back(std::stoul(line, nullptr, 2));
  }

  std::sort(ids.begin(), ids.end());

  for (size_t i = 0; i < ids.size() - 1; ++i) {
    if (ids[i + 1] - ids[i] == 2) {
      return ids[i] + 1;
    }
  }

  return 0;
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

  size_t target_one{818};
  size_t result_one = part_one(file);
  bool ok_one = target_one == result_one;
  std::cout << "Part 1: " << target_one << (ok_one ? " == " : " != ") << result_one << std::endl;
  if (!ok_one) {
    return 1;
  }

  size_t target_two{559};
  size_t result_two = part_two(file);
  bool ok_two = target_two == result_two;
  std::cout << "Part 2: " << target_two << (ok_two ? " == " : " != ") << result_two << std::endl;
  if (!ok_two) {
    return 2;
  }

  return 0;
}
