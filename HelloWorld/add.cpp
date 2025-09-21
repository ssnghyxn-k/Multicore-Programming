#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;

int sum;
mutex myl;

void worker()
{
	for (auto i = 0; i < 25000000; ++i) {
		myl.lock();
		sum += 2;
		myl.unlock();
	}
}

int main()
{
	for (int i = 1; i <= 8; i += 2) {
		sum = 0;
		vector<thread> workers;
		auto start_t = high_resolution_clock::now();
		for (int j = 0; j < i; j++)
			workers.emplace_back(worker);
		for(auto& th : workers)
			th.join();
		auto end_t = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end_t - start_t);

		cout << "number of threads = " << i << endl;
		cout << "Duration = " << duration.count() << " ms" << endl;
		cout << "Sum = " << sum << endl;
	}
}