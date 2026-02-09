#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <functional>
#include <string>
#include <limits>
#include <map>

#include <filetools.hpp>

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
    std::system((map[argv[2]] + " & disown").c_str());
  };

  functions["rm"] = [path, argc](const char* argv[]) {
    configmap map = file_to_map(path + "runx.conf");
    for (int i=2; i<argc; ++i) {
      map.erase(argv[i]);
    }
    map_to_file(map, path + "runx.conf");
  };

  functions["ls"] = [path](const char* argv[]) {
    std::ifstream file(path + "runx.conf");

    if (argv[2] && std::string(argv[2]) == "-a") {
      std::string appLine;
      while (std::getline(file, appLine)) {
        std::cout << appLine << std::endl;
      }
    }
    else {
      std::string appName;
      while (std::getline(file, appName, '=') && file.ignore(std::numeric_limits<std::streamsize>::max(), '\n')) {
        std::cout << appName << std::endl;
      }
    }
    file.close();
  };
}

int main(int argc, const char* argv[]) {
  init(argc);
  functions[argv[1]](argv);
}
