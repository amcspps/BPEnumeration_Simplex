cmake_minimum_required (VERSION 3.8)

project ("BPEnumeration_Simplex")

#add cpp files near "main.cpp"
add_executable (BPEnumeration_Simplex "main.cpp" "task.cpp" "matrix.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BPEnumeration_Simplex PROPERTY CXX_STANDARD 20)
endif()

