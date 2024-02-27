cmake_minimum_required(VERSION 3.16.3)
project(conclave-room-client C)
enable_testing()

add_subdirectory(deps/piot/clog/src/lib)
add_subdirectory(deps/piot/conclave-room-serialize-c/src/lib)
add_subdirectory(deps/piot/flood-c/src/lib)
add_subdirectory(deps/piot/imprint/src/lib)
add_subdirectory(deps/piot/tiny-libc/src/lib)


add_subdirectory(src)
