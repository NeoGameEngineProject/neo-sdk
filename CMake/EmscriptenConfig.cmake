
set(SDL2_LIBRARY "sdl2")
set(SDL2_INCLUDE_DIR " ")
set(SDL2_FOUND TRUE)

set(FREETYPE_LIBRARY "freetype")
set(FREETYPE_INCLUDE_DIRS " ")
set(FREETYPE_FOUND TRUE)

set(ZLIB_LIBRARY "zlib")
set(ZLIB_INCLUDE_DIR " ")
set(ZLIB_FOUND TRUE)

set(M_LIBRARY "m")
set(M_INCLUDE_DIR " ")
set(M_FOUND TRUE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_FREETYPE=1 -s USE_ZLIB=1 -std=c++17 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_SDL=2 -s USE_FREETYPE=1 -s USE_ZLIB=1 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1")
set(CMAKE_EXE_LINK_FLAGS "${CMAKE_EXE_LINK_FLAGS} -s USE_SDL=2 -s USE_FREETYPE=1 -s USE_ZLIB=1 -lopenal -s WASM=0 -s ALLOW_MEMORY_GROWTH=1")

if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g4 -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=1 -s NO_EXIT_RUNTIME=0 ")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g4 -s DEMANGLE_SUPPORT=1 -s NO_EXIT_RUNTIME=0 ")
	set(CMAKE_EXE_LINK_FLAGS "${CMAKE_EXE_LINK_FLAGS} -g4 -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=1 -s NO_EXIT_RUNTIME=0 ")
endif()

SET(CMAKE_EXECUTABLE_SUFFIX ".html")
