#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<bool> ready(false);
std::atomic_flag winner = ATOMIC_FLAG_INIT;

void count1m(int id) {
		while(!ready) {
				std::this_thread::yield();
		} //等待主线程中设置ready为true

		for(int i=0; i<1000000; ++i) {
		}//计数

		if(!winner.test_and_set()) {
				std::cout << "thread #" << id << " won!\n";
		}
}

int main() {
		std::vector<std::thread> threads;
		std::cout << "swanping 10 threads that count to 1 million...\n";
		for(int i = 1; i <= 10; ++i) {
				threads.push_back(std::thread(count1m, i));
		}

		ready = true;

		for(auto & th: threads)
				th.join();

		return 0;
}


