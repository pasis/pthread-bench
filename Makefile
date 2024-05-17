all:
	g++ pthread-bench.cpp -std=c++11 -lbenchmark -pthread -o pthread-bench
