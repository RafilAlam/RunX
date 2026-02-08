#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <functional>
#include <string>
#include <map>

std::map<std::string, std::string> mapfile(std::string filepath) {
  std::map<std::string, std::string> map;
  std::ifstream file(filepath);
  std::string name;
  std::string path;
  while (std::getline(file, name, '=') && std::getline(file, path)) {
    map[name] = path;
  }
  return map;
}

std::map<std::string, std::function<void(const char**)>> functions;

void init() {
  std::string path = std::getenv("HOME") + std::string("/.config/runx/");
  std::filesystem::create_directory(path);

  functions["reg"] = [path](const char* argv[]) {
    std::ofstream file(path + "runx.conf", std::ios::app);
    if (!file) {
      std::cerr << "Unable to load config file!\n";
      std::exit(1);
    }

    file << argv[2] << '=' << argv[3] << std::endl;
    file.close();
  };

  functions["run"] = [path](const char* argv[]) {
    std::map<std::string, std::string> map = mapfile(path + "runx.conf");
    std::system(map[argv[2]].c_str());
  };
}

int main(int argc, const char* argv[]) {
  init();
  functions[argv[1]](argv);
}
