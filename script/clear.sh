#! /usr/bin/env bash
# run this shell script with the command: ./script/clear.sh

rm -r debug/**/*.out;
rm -r debug/**/*.log;
rm -r debug/**/*.dSYM;
rm -r test/*.out;
rm -r test/*.log;
rm -r test/*.dSYM;
rm -r benchmark/*.out;
rm -r benchmark/*.log;
rm -r benchmark/*.dSYM;
rm .trash;
