cmake_minimum_required (VERSION 3.13)

add_executable (App src/SandBox.cpp)

target_link_libraries(App SbSpi SbCore)