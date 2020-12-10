#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

size_t move(const std::vector<std::string> &toboggan,
            size_t right,
            size_t down = 1)
{
  size_t counter{};
  size_t pos{};
  size_t index{};
  for (const std::string &row : toboggan) {
    if (down != 1 && index % down != 0) {
      index++;
      continue;
    }

    if (row[pos] == '#') {
      counter++;
    }

    pos += right;
    pos %= row.size();
    index++;
  }
  return counter;
}

size_t part_one(const std::vector<std::string> &toboggan)
{
  return move(toboggan, 3);
}

size_t part_two(const std::vector<std::string> &toboggan)
{
  return move(toboggan, 1) * move(toboggan, 3) * move(toboggan, 5) * move(toboggan, 7) * move(toboggan, 1, 2);
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

  std::vector<std::string> toboggan;
  std::string input;
  while (std::getline(input_file, input)) {
    toboggan.emplace_back(input);
  }

  size_t target_one{181};
  size_t result_one = part_one(toboggan);
  bool ok_one = target_one == result_one;
  std::cout << "Part 1: " << target_one << (ok_one ? " == " : " != ") << result_one << std::endl;
  if (!ok_one) {
    return 1;
  }

  size_t target_two{249};
  size_t result_two = part_two(toboggan);
  bool ok_two = target_two == result_two;
  std::cout << "Part 2: " << target_two << (ok_two ? " == " : " != ") << result_two << std::endl;
  if (!ok_two) {
    return 2;
  }

  return 0;
}
