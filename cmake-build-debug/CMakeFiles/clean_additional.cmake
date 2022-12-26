# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/GraphProject_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/GraphProject_autogen.dir/ParseCache.txt"
  "GraphProject_autogen"
  )
endif()
