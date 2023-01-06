#! /usr/bin/env bash
# run this shell script with the command: ./script/debug.sh

CXX_DEBUG="g++-12";
CXXFLAGS_DEBUG="-Wall -std=c++17 -O0 -g";

# include paths for debug/graph/pair_test_with_cxxgraph.cpp
#
CXXFLAGS_DEBUG+=" -I./third-party/CXXGraph/include";
CXXFLAGS_DEBUG+=" -I/usr/local/Cellar/openssl@3/3.0.7/include";

if [ $# -eq 0 ]; then
  for src in debug/**/*.cpp; do
    echo "$CXX_DEBUG $CXXFLAGS_DEBUG $src -o $src.out";
    $CXX_DEBUG $CXXFLAGS_DEBUG $src -o $src.out;

    if [ $? -ne 0 ]; then
      echo "compilation for $src fails";
      ./script/clear.sh;
      exit 1;
    fi
  done

  for bin in debug/**/*.out; do
    echo "";

    ./$bin && 
      (time ./$bin) 2>&1 > /dev/null | \
      grep "real" | \
      sed "s|real	|\.\/$bin: |g";
  done

else
  for src in $@; do
    echo "$CXX_DEBUG $CXXFLAGS_DEBUG $@ -o $@.out";
    $CXX_DEBUG $CXXFLAGS_DEBUG $@ -o $@.out;

    if [ $? -ne 0 ]; then
      echo "compilation for $src fails";
      ./script/clear.sh;
      exit 1;
    fi
  done

  for bin in $@; do
    echo "";

    bin="$bin.out";
    ./$bin && 
      (time ./$bin) 2>&1 > /dev/null | \
      grep "real" | \
      sed "s|real	|\.\/$bin: |g";
  done
fi
