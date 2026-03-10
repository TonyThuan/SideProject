# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appGui_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appGui_autogen.dir\\ParseCache.txt"
  "appGui_autogen"
  )
endif()
