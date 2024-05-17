all:
	g++ -std=c++11 -lbenchmark -pthread -o pthread-bench pthread-bench.cpp
