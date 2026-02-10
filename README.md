# RunX
An app registry and launcher for linux operating systems

## Usage
```bash
# Register an application with RunX
runx add <app_name> <executable_directory_path>

# Unregister application(s)
runx rm <app_name1> <app_name2> <app_name...>

# List registered applications
runx ls    # Cleaner list
runx ls -a # Full list including executable directories

# Run an application
runx run <app_name>
```

## Installation
### From Releases:
```
Place downloaded runx executable in one of your $PATH directories (e.g. /usr/bin/)
```
### From Source (CMake):
```bash
# In source directory (where CMakeList.txt is)
mkdir build
cd build
cmake ..
cmake --build .
```
