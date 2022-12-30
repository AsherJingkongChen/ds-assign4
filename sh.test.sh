#! /usr/bin/env bash

CXX_TEST="g++-12";
CXXFLAGS_TEST="-Wall -O0";

if [ $# -eq 0 ]; then
  for src in test/**/*.cpp; do
    echo "$CXX_TEST $CXXFLAGS_TEST $src -o $src.out";
    $CXX_TEST $CXXFLAGS_TEST $src -o $src.out;
  done

  for bin in test/**/*.out; do
    ./$bin && 
      (time ./$bin) 2>&1 > /dev/null | \
      grep "real" | \
      sed "s|real	|\.\/$bin: |g" \
    && rm $bin;
  done

else
  for src in $@; do
    echo "$CXX_TEST $CXXFLAGS_TEST $@ -o $@.out";
    $CXX_TEST $CXXFLAGS_TEST $@ -o $@.out;
  done

  for bin in $@; do
    ./$bin.out && 
      (time ./$bin.out) 2>&1 > /dev/null | \
      grep "real" | \
      sed "s|real	|\.\/$bin\.out: |g" \
    && rm $bin.out;
  done
fi