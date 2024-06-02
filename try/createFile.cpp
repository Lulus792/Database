#include <fstream>

int main() {
  std::ofstream file("test.db");
  file << "test";
  file << "\n";
  file << "test";
  file.close();
  return 0;
}
