#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::vector<std::string> expected{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
const std::vector<std::string> ecl{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

size_t part_one(const std::filesystem::path &file)
{
  std::ifstream input_file(file);

  size_t counter{};

  size_t current{};
  std::string line;
  while (std::getline(input_file, line)) {
    if (line.empty()) {
      if (current >= expected.size()) {
        counter++;
      }
      current = 0;
      continue;
    }

    for (const std::string &field : expected) {
      if (line.find(field) != std::string::npos) {
        current++;
      }
    }
  }

  // Last one
  if (current >= expected.size()) {
    counter++;
  }

  return counter;
}

bool validate(const std::string &field)
{
  std::string name = field.substr(0, 3);
  std::string value = field.substr(4);

  try {
    if (name == "byr") {
      int v = std::stoi(value);
      if (1920 <= v && v <= 2002) {
        return true;
      }
    } else if (name == "iyr") {
      int v = std::stoi(value);
      if (2010 <= v && v <= 2020) {
        return true;
      }
    } else if (name == "eyr") {
      int v = std::stoi(value);
      if (2020 <= v && v <= 2030) {
        return true;
      }
    } else if (name == "hgt") {
      int height = std::stoi(value.substr(0, value.size() - 2));
      std::string unit = value.substr(value.size() - 2);
      if (unit == "cm" && 150 <= height && height <= 193) {
        return true;
      }
      if (unit == "in" && 59 <= height && height <= 76) {
        return true;
      }
    } else if (name == "hcl") {
      if (value[0] == '#' && std::stoi(value.substr(1), nullptr, 16) >= 0x0) {
        return true;
      }
    } else if (name == "ecl") {
      if (std::find(ecl.begin(), ecl.end(), value) != ecl.end()) {
        return true;
      }
    } else if (name == "pid") {
      if (value.size() == 9 && std::stoi(value) > 0) {
        return true;
      }
    }
  } catch (const std::invalid_argument &) {
    return false;
  }

  return false;
}

size_t part_two(const std::filesystem::path &file)
{
  std::ifstream input_file(file);

  size_t counter{};

  size_t current{};
  std::string line;
  while (std::getline(input_file, line)) {
    if (line.empty()) {
      if (current >= expected.size()) {
        counter++;
      }
      current = 0;
      continue;
    }

    std::istringstream stream(line);
    std::string field;
    while (true) {
      stream >> field;
      if (validate(field)) {
        current++;
      }
      if (stream.eof()) {
        break;
      }
    }
  }

  // Last one
  if (current >= expected.size()) {
    counter++;
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

  size_t target_one{204};
  size_t result_one = part_one(file);
  bool ok_one = target_one == result_one;
  std::cout << "Part 1: " << target_one << (ok_one ? " == " : " != ") << result_one << std::endl;
  if (!ok_one) {
    return 1;
  }

  size_t target_two{179};
  size_t result_two = part_two(file);
  bool ok_two = target_two == result_two;
  std::cout << "Part 2: " << target_two << (ok_two ? " == " : " != ") << result_two << std::endl;
  if (!ok_two) {
    return 2;
  }

  return 0;
}
