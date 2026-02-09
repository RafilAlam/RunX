cmake_minimum_required(VERSION 3.23)

project(runx)

add_executable(${PROJECT_NAME} 
  ${PROJECT_SOURCE_DIR}/src/main.cpp
  ${PROJECT_SOURCE_DIR}/src/filetools.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/)
