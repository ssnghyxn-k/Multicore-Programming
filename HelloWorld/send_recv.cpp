#include <iostream>
#include <thread>
#include <mutex>

volatile int g_data = 0;
volatile bool g_ready = false;
std::mutex sr_lock;		// send-receive lock

void recv()
{
	while (false == g_ready);
	std::cout << "Data = " << g_data << std::endl;
}

void send()
{
	int temp = 0;
	std::cin >> temp;
	g_data = temp;
	g_ready = true;
}

int main()
{
	std::thread r{ recv };
	std::thread s{ send };
	r.join();
	s.join();
}