# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "F:/SZE/5/Mosze/mosze-2023-hw-pacman-bytebusters/ByteBusters/Build/_deps/googletest-src"
  "F:/SZE/5/Mosze/mosze-2023-hw-pacman-bytebusters/ByteBusters/Build/_deps/googletest-build"
  "F:/SZE/5/Mosze/mosze-2023-hw-pacman-bytebusters/ByteBusters/Build/_deps/googletest-subbuild/googletest-populate-prefix"
  "F:/SZE/5/Mosze/mosze-2023-hw-pacman-bytebusters/ByteBusters/Build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "F:/SZE/5/Mosze/mosze-2023-hw-pacman-bytebusters/ByteBusters/Build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "F:/SZE/5/Mosze/mosze-2023-hw-pacman-bytebusters/ByteBusters/Build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "F:/SZE/5/Mosze/mosze-2023-hw-pacman-bytebusters/ByteBusters/Build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "F:/SZE/5/Mosze/mosze-2023-hw-pacman-bytebusters/ByteBusters/Build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "F:/SZE/5/Mosze/mosze-2023-hw-pacman-bytebusters/ByteBusters/Build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
