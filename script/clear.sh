#! /usr/bin/env bash
# run this shell script with the command: ./script/clear.sh

for bin in debug/**/*.out*; do
  rm -r $bin;
done
