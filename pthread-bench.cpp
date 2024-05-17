/* g++ -std=c++11 -lbenchmark -pthread -o pthread-bench pthread-bench.cpp */

#include <atomic>
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

static void BM_pthread_spin_trylock(benchmark::State& state) {
	pthread_spinlock_t lock;

	pthread_spin_init(&lock, 0);
	for (auto _ : state) {
		pthread_spin_trylock(&lock);
		pthread_spin_unlock(&lock);
	}
	pthread_spin_destroy(&lock);
}
BENCHMARK(BM_pthread_spin_trylock);

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

static void BM_pthread_mutex_trylock(benchmark::State& state) {
	pthread_mutex_t lock;

	pthread_mutexattr_t mtx_attr;
	pthread_mutexattr_init(&mtx_attr);
	pthread_mutexattr_settype(&mtx_attr, PTHREAD_MUTEX_DEFAULT);
	pthread_mutex_init(&lock, &mtx_attr);

	for (auto _ : state) {
		pthread_mutex_trylock(&lock);
		pthread_mutex_unlock(&lock);
	}
	pthread_mutex_destroy(&lock);
}
BENCHMARK(BM_pthread_mutex_trylock);

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

static void BM_pthread_mutex_recursive_trylock(benchmark::State& state) {
	pthread_mutex_t lock;

	pthread_mutexattr_t mtx_attr;
	pthread_mutexattr_init(&mtx_attr);
	pthread_mutexattr_settype(&mtx_attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&lock, &mtx_attr);

	for (auto _ : state) {
		pthread_mutex_trylock(&lock);
		pthread_mutex_unlock(&lock);
	}
	pthread_mutex_destroy(&lock);
}
BENCHMARK(BM_pthread_mutex_recursive_trylock);

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

static void BM_atomic_load_relaxed(benchmark::State& state) {
	std::atomic<int> a;
	for (auto _ : state) {
		a.load(std::memory_order_relaxed);
	}
}
BENCHMARK(BM_atomic_load_relaxed);

static void BM_atomic_load_acquire(benchmark::State& state) {
	std::atomic<int> a;
	for (auto _ : state) {
		a.load(std::memory_order_acquire);
	}
}
BENCHMARK(BM_atomic_load_acquire);

static void BM_atomic_fetch_add_relaxed(benchmark::State& state) {
	std::atomic<int> a(0);
	for (auto _ : state) {
		a.fetch_add(std::memory_order_relaxed);
	}
}
BENCHMARK(BM_atomic_fetch_add_relaxed);

static void BM_atomic_fetch_add_acquire(benchmark::State& state) {
	std::atomic<int> a(0);
	for (auto _ : state) {
		a.fetch_add(std::memory_order_acquire);
	}
}
BENCHMARK(BM_atomic_fetch_add_acquire);

BENCHMARK_MAIN();
