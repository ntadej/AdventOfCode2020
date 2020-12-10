#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

constexpr size_t rows{127};
constexpr size_t seats{7};

size_t get_row(const std::string &id,
               size_t min,
               size_t max)
{
  if (id.empty()) {
    return min;
  }

  if (id[0] == 'F') {
    return get_row(id.substr(1), min, (max + min) / 2);
  }

  return get_row(id.substr(1), (max + min) / 2 + 1, max);
}

size_t get_seat(const std::string &id,
                size_t min,
                size_t max)
{
  if (id.empty()) {
    return min;
  }

  if (id[0] == 'L') {
    return get_seat(id.substr(1), min, (max + min) / 2);
  }

  return get_seat(id.substr(1), (max + min) / 2 + 1, max);
}

size_t part_one(const std::filesystem::path &file)
{
  std::ifstream input_file(file);

  size_t max{};
  std::string line;
  while (std::getline(input_file, line)) {
    size_t row = get_row(line.substr(0, 7), 0, rows);
    size_t seat = get_seat(line.substr(7), 0, seats);
    size_t id = row * 8 + seat;
    if (id > max) {
      max = id;
    }
  }

  return max;
}

size_t part_two(const std::filesystem::path &file)
{
  std::ifstream input_file(file);

  std::array<bool, (rows + 1) * 8> list{};

  std::string line;
  while (std::getline(input_file, line)) {
    size_t row = get_row(line.substr(0, 7), 0, rows);
    size_t seat = get_seat(line.substr(7), 0, seats);
    list[row * 8 + seat] = true;
  }

  for (size_t i = 1; i < (rows + 1) * 8 - 1; ++i) {
    if (!list[i] && list[i - 1] && list[i + 1]) {
      return i;
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
