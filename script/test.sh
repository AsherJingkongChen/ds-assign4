#! /usr/bin/env bash
# run this shell script with the command: ./script/test.sh

CXX_TEST="g++-12";
CXXFLAGS_TEST="-Wall -O0";

if [ $# -eq 0 ]; then
  for src in test/**/*.cpp; do
    echo "$CXX_TEST $CXXFLAGS_TEST $src -o $src.out";
    $CXX_TEST $CXXFLAGS_TEST $src -o $src.out;

    if [ $? -ne 0 ]; then
      echo "compilation for $src fails";
      ./script/clear.sh;
      exit 1;
    fi
  done

  for bin in test/**/*.out; do
    echo "";

    ./$bin && 
      (time ./$bin) 2>&1 > /dev/null | \
      grep "real" | \
      sed "s|real	|\.\/$bin: |g";
  done

else
  for src in $@; do
    echo "$CXX_TEST $CXXFLAGS_TEST $@ -o $@.out";
    $CXX_TEST $CXXFLAGS_TEST $@ -o $@.out;

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
