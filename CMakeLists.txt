cmake_minimum_required(VERSION 3.18)
list(APPEND CMAKE_MODULE_PATH "/usr/local/lib/cmake/OpenVDB")
find_package(OpenVDB REQUIRED)
add_executable(vdb-playground main.cxx)
target_link_libraries(vdb-playground OpenVDB::openvdb)
