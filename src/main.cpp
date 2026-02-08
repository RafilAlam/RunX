#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <functional>
#include <string>
#include <map>

typedef std::map<std::string, std::string> configmap;

configmap file_to_map(std::string filepath) {
  configmap map;
  std::ifstream file(filepath);
  std::string name;
  std::string path;
  while (std::getline(file, name, '=') && std::getline(file, path)) {
    map[name] = path;
  }
  file.close();
  return map;
}

void map_to_file(configmap map, std::string filepath) {
  std::ofstream file(filepath);
  for (const auto& pair : map) {
    file << pair.first << '=' << pair.second << std::endl;
  }
  file.close();
}

std::map<std::string, std::function<void(const char**)>> functions;

void init(int argc) {
  std::string path = std::getenv("HOME") + std::string("/.config/runx/");
  std::filesystem::create_directory(path);

  functions["add"] = [path](const char* argv[]) {
    std::ofstream file(path + "runx.conf", std::ios::app);
    if (!file) {
      std::cerr << "Unable to load config file!\n";
      std::exit(1);
    }

    file << argv[2] << '=' << argv[3] << std::endl;
    file.close();
  };

  functions["run"] = [path](const char* argv[]) {
    configmap map = file_to_map(path + "runx.conf");
    std::system(map[argv[2]].c_str());
  };

  functions["rm"] = [path, argc](const char* argv[]) {
    configmap map = file_to_map(path + "runx.conf");
    for (int i=2; i<argc; ++i) {
      map.erase(argv[i]);
    }
    map_to_file(map, path + "runx.conf");
  };
}

int main(int argc, const char* argv[]) {
  init(argc);
  functions[argv[1]](argv);
}
