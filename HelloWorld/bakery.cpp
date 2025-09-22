#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>

const int MAX_THREADS = 8;
volatile int sum = 0;

volatile bool flags[MAX_THREADS] = { false, false, false, false };
volatile int labels[MAX_THREADS] = { 0, 0, 0, 0 };

void b_lock(const int thread_id)
{
	flags[thread_id] = true;
	int max_label = 0;
	for (int i = 0; i < MAX_THREADS; ++i) {
		max_label = std::max(labels[thread_id], labels[i]);
	}
	labels[thread_id] = max_label + 1;		// 내 번호표 배정
	for (int k = 0; k < MAX_THREADS; ++k)
		while (flags[k] && (labels[k] < labels[thread_id] || (labels[k] == labels[thread_id] && k < thread_id)));
}

void b_unlock(const int thread_id)
{
	flags[thread_id] = false;
}

void worker(const int thread_id, const int loop_count)
{
	for (auto i = 0; i < loop_count; ++i) {
		b_lock(thread_id);
		sum += 2;
		b_unlock(thread_id);
	}
}

int main()
{
	using namespace std::chrono;

	auto start = high_resolution_clock::now();
	// Single thread
	for (int i = 0; i < 5000000; ++i)
		sum += 2;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	std::cout << "Single thread duration: " << duration.count() << "ms, SUM = " << sum << std::endl;

	for (int num_threads = 1; num_threads <= MAX_THREADS; num_threads *= 2) {
		sum = 0;
		start = high_resolution_clock::now();
		std::vector<std::thread> threads;
		for (int i = 0; i < num_threads; ++i)
			threads.emplace_back(worker, i, 5000000 / num_threads);
		for (int i = 0; i < num_threads; ++i) {
			threads[i].join();
		}
		stop = high_resolution_clock::now();
		duration = duration_cast<milliseconds>(stop - start);

		std::cout << num_threads << "thread duration: " << duration.count() << "ms, ";
		std::cout << "SUM =  " << sum << std::endl;
	}
}