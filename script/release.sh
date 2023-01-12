#! /usr/bin/env bash
# run this shell script with the command: ./script/release.sh

CXX_RELEASE="g++-12";
CXXFLAGS_RELEASE="-Wall -std=c++11 -O3";

if [ $# -eq 0 ]; then
  for src in release/*.cpp; do
    echo "$CXX_RELEASE $CXXFLAGS_RELEASE $src -o $src.out";
    $CXX_RELEASE $CXXFLAGS_RELEASE $src -o $src.out;

    if [ $? -ne 0 ]; then
      ./script/clear.sh;
      echo "compilation for $src fails";
      exit 1;
    fi
  done

  for bin in release/*.out; do
    echo "./$bin";
    ./$bin;
  done

else
  for src in $@; do
    echo "$CXX_RELEASE $CXXFLAGS_RELEASE $src -o $src.out";
    $CXX_RELEASE $CXXFLAGS_RELEASE $src -o $src.out;

    if [ $? -ne 0 ]; then
      ./script/clear.sh;
      echo "compilation for $src fails";
      exit 1;
    fi
  done

  for bin in $@; do
    echo "./$bin";
    ./$bin.out;
  done
fi