cmake_minimum_required(VERSION 3.0)

# set(PROFILE_FLAGS "-pg")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROFILE_FLAGS}")

project("WebWhir")

add_subdirectory(src)
add_subdirectory(tests)
