#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <atomic>

const int MAX_THREADS = 2;
volatile int sum = 0;
std::mutex mtx;

volatile int victim = 0;
volatile bool flags[2] = { false, false };

void p_lock(const int thread_id)	// Peterson's lock
{
	const int other = 1 - thread_id;
	flags[thread_id] = true;
	victim = thread_id;
	while((true == flags[other]) && (victim == thread_id));
}

void p_unlock(const int thread_id)
{
	flags[thread_id] = false;
}

void worker(const int thread_id, const int loop_count)
{
	for (auto i = 0; i < loop_count; ++i) {
		p_lock(thread_id);
		sum += 2;
		p_lock(thread_id);
	}
}

int main()
{
	using namespace std::chrono;

	auto start = high_resolution_clock::now();
	// Single thread
	for (int i = 0; i < 50000000; ++i)
		sum += 2;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	std::cout << "Single thread duration: " << duration.count() << "ms, SUM = " << sum << std::endl;

	for (int num_threads = 1; num_threads <= MAX_THREADS; num_threads *= 2) {
		sum = 0;
		start = high_resolution_clock::now();
		std::vector<std::thread> threads;
		for (int i = 0; i < num_threads; ++i)
			threads.emplace_back(worker, i, 50000000 / num_threads);
		for (int i = 0; i < num_threads; ++i) {
			threads[i].join();
		}
		stop = high_resolution_clock::now();
		duration = duration_cast<milliseconds>(stop - start);

		std::cout << num_threads << "thread duration: " << duration.count() << "ms, ";
		std::cout << "SUM =  " << sum << std::endl;
	}
}