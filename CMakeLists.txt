cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)
project(bstone_solution)

message(STATUS "[bstone_solution]")

option(BSTONE_USE_STATIC_LINKING "Link build statically." OFF)
message(STATUS "[bstone_solution] Static linking: ${BSTONE_USE_STATIC_LINKING}")

option(BSTONE_TESTS "Build tests." OFF)
message(STATUS "[bstone_solution] Build tests: ${BSTONE_TESTS}")

option(BSTONE_TRIM_FILE_PATHS_IN_EXE "Trim file names on the left in the executable." OFF)
message(STATUS "[bstone_solution] Trim file names in the executable: ${BSTONE_TRIM_FILE_PATHS_IN_EXE}")

option(BSTONE_NO_ASSERT "Disable assertion." OFF)
message(STATUS "[bstone_solution] Disable assertion: ${BSTONE_NO_ASSERT}")

option(BSTONE_INTERNAL_SDL2 "Use bundled SDL2 source code." OFF)

option(BSTONE_ENABLE_VULKAN "Enable Vulkan renderer and support code." ON)

option(BSTONE_ENABLE_OPENAL "Enable OpenAL audio backend." ON)

if (EMSCRIPTEN)
	set(BSTONE_INTERNAL_SDL2 ON CACHE BOOL "Use bundled SDL2 source code." FORCE)
	set(BSTONE_ENABLE_VULKAN OFF CACHE BOOL "Enable Vulkan renderer and support code." FORCE)
	set(BSTONE_ENABLE_OPENAL OFF CACHE BOOL "Enable OpenAL audio backend." FORCE)
endif ()

message(STATUS "[bstone_solution] Internal SDL2: ${BSTONE_INTERNAL_SDL2}")
message(STATUS "[bstone_solution] Vulkan support: ${BSTONE_ENABLE_VULKAN}")
message(STATUS "[bstone_solution] OpenAL support: ${BSTONE_ENABLE_OPENAL}")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if ("${BSTONE_CI_GIT_HASH}" STREQUAL "")
	include(GetGitHeadHash)

	get_git_hash(${CMAKE_SOURCE_DIR} BSTONE_GIT_HASH)
	message(STATUS "[bstone_solution] Source Git hash: ${BSTONE_GIT_HASH}")
else ()
	message(STATUS "[bstone_solution] CI Git hash: ${BSTONE_CI_GIT_HASH}")
	set(BSTONE_GIT_HASH "${BSTONE_CI_GIT_HASH}")
endif ()

string(SUBSTRING "${BSTONE_GIT_HASH}" 0 8 BSTONE_GIT_HASH_SHORT)
message(STATUS "[bstone_solution] Short Git hash: ${BSTONE_GIT_HASH_SHORT}")

add_subdirectory(src)
