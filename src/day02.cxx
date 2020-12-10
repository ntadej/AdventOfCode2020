#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

size_t part_one(const std::filesystem::path &file)
{
  std::ifstream input_file(file);

  size_t counter{};

  while (true) {
    size_t min{};
    size_t max{};
    char c{};
    std::string pass;

    input_file >> min;
    input_file.ignore(1, '-');
    input_file >> max >> c;
    input_file.ignore(1, ' ');
    input_file >> pass;

    if (input_file.eof()) {
      break;
    }

    size_t n = std::count(pass.begin(), pass.end(), c);
    if (min <= n && n <= max) {
      counter++;
    }
  }

  return counter;
}

size_t part_two(const std::filesystem::path &file)
{
  std::ifstream input_file(file);

  size_t counter{};

  while (true) {
    size_t x{};
    size_t y{};
    char c{};
    std::string pass;

    input_file >> x;
    input_file.ignore(1, '-');
    input_file >> y >> c;
    input_file.ignore(1, ' ');
    input_file >> pass;

    if (input_file.eof()) {
      break;
    }

    x--;
    y--;

    if (x >= pass.size() || y >= pass.size()) {
      continue;
    }

    if ((pass[x] == c || pass[y] == c) && !(pass[x] == c && pass[y] == c)) {
      counter++;
    }
  }

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

  size_t target_one{447};
  size_t result_one = part_one(file);
  bool ok_one = target_one == result_one;
  std::cout << "Part 1: " << target_one << (ok_one ? " == " : " != ") << result_one << std::endl;
  if (!ok_one) {
    return 1;
  }

  size_t target_two{249};
  size_t result_two = part_two(file);
  bool ok_two = target_two == result_two;
  std::cout << "Part 2: " << target_two << (ok_two ? " == " : " != ") << result_two << std::endl;
  if (!ok_two) {
    return 2;
  }

  return 0;
}
