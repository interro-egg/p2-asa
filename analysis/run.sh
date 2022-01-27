#!/bin/sh

# you probably want to call this with `time ./run.sh [custom_results_csv] [custom_exe] && date`

cd "${0%/*}" # go to script directory
set -e # exit if any command fails

CSV="${1:-$(date +%s).csv}" # arg 1 with default value
EXE="${2:-../project}" # arg 2 with default value


if [ ! -f "$EXE" ]; then
	echo "Executable (arg #2, defaults to ../project) does not exist!"
	echo -e "\tFile '$EXE' not found"
	exit 1
fi

# This uses the randGeneoTree program provided by professors to generate trees. The #V parameter is gradually increased, #p is always $EDGE_PROB and no seed is provided.
EDGE_PROB=0.99

g++ -std=c++11 -O3 -Wall randGeneoTree.cpp -lm -o randGeneoTree # there's no need to always compile it, but it's easier this way

echo "V,command,mean,stddev,median,user,system,min,max" > $CSV

test() {
	echo "Testing with V = $1"
	./randGeneoTree $1 $EDGE_PROB > in.txt
	hyperfine "$EXE < in.txt" --warmup 10 --export-csv tmp.csv &>/dev/null
	echo -n $1, >> $CSV
	grep ./project tmp.csv >> $CSV # remove header
	rm in.txt
	rm tmp.csv
}

#for i in {10..99..1}; do
#	test $i
#done

#for i in {100..999..10}; do
#	test $i
#done

#for i in {1000..9999..100}; do
#	test $i
#done

#for i in {10000..99999..1000}; do
#	test $i
#done

for i in {100000..1000000..10000}; do
    test $i
done

#for i in {1000000..10000000..100000}; do
#    test $i
#done
