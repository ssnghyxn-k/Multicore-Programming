#include <iostream>
#include <thread>
#include <mutex>

int g_data = 0;
bool g_ready = false;
std::mutex sr_lock;		// send-receive lock

void recv()
{
	sr_lock.lock();
	while (false == g_ready) {
		sr_lock.unlock();
		sr_lock.lock();
	}
	std::cout << "Data = " << g_data << std::endl;
	sr_lock.unlock();
}

void send()
{
	sr_lock.lock();
	std::cin >> g_data;
	g_ready = true;
	sr_lock.unlock();
}

int main()
{
	std::thread r{ recv };
	std::thread s{ send };
	r.join();
	s.join();
}