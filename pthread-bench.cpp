/* g++ -std=c++11 -lbenchmark -pthread -o pthread-bench pthread-bench.cpp */

#include <pthread.h>
#include <benchmark/benchmark.h>

static void BM_pthread_self(benchmark::State& state) {
	for (auto _ : state) {
		pthread_self();
	}
}
BENCHMARK(BM_pthread_self);

static void BM_pthread_spinlock(benchmark::State& state) {
	pthread_spinlock_t lock;

	pthread_spin_init(&lock, 0);
	for (auto _ : state) {
		pthread_spin_lock(&lock);
		pthread_spin_unlock(&lock);
	}
	pthread_spin_destroy(&lock);
}
BENCHMARK(BM_pthread_spinlock);

static void BM_pthread_mutex(benchmark::State& state) {
	pthread_mutex_t lock;

	pthread_mutexattr_t mtx_attr;
	pthread_mutexattr_init(&mtx_attr);
	pthread_mutexattr_settype(&mtx_attr, PTHREAD_MUTEX_DEFAULT);
	pthread_mutex_init(&lock, &mtx_attr);

	for (auto _ : state) {
		pthread_mutex_lock(&lock);
		pthread_mutex_unlock(&lock);
	}
	pthread_mutex_destroy(&lock);
}
BENCHMARK(BM_pthread_mutex);

static void BM_pthread_mutex_recursive(benchmark::State& state) {
	pthread_mutex_t lock;

	pthread_mutexattr_t mtx_attr;
	pthread_mutexattr_init(&mtx_attr);
	pthread_mutexattr_settype(&mtx_attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&lock, &mtx_attr);

	for (auto _ : state) {
		pthread_mutex_lock(&lock);
		pthread_mutex_unlock(&lock);
	}
	pthread_mutex_destroy(&lock);
}
BENCHMARK(BM_pthread_mutex_recursive);

static void BM_pthread_mutex_recursive_self(benchmark::State& state) {
	pthread_mutex_t lock;

	pthread_mutexattr_t mtx_attr;
	pthread_mutexattr_init(&mtx_attr);
	pthread_mutexattr_settype(&mtx_attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&lock, &mtx_attr);

	for (auto _ : state) {
		pthread_self();
		pthread_mutex_lock(&lock);
		pthread_mutex_unlock(&lock);
	}
	pthread_mutex_destroy(&lock);
}
BENCHMARK(BM_pthread_mutex_recursive_self);

BENCHMARK_MAIN();
