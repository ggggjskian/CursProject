# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles\\my_vet_app_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\my_vet_app_autogen.dir\\ParseCache.txt"
  "my_vet_app_autogen"
  )
endif()
