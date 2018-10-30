#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx; //全局互斥锁
std::condition_variable cv; //全局条件变量
bool ready = false; //全局标志位

void do_print_id(int id) {
		std::unique_lock<std::mutex> lck(mtx);
		while(!ready)
				cv.wait(lck);
		std::cout << "thread" << id << '\n';
}

void go() {
		std::unique_lock<std::mutex> lck(mtx);
		ready = true;
		cv.notify_all();
}

int main() {
		std::thread threads[10];
		for(int i=0; i<10; ++i) {
				threads[i] = std::thread(do_print_id, i);
		}

		std::cout << "10 threads ready to race... \n";
		go();

		for(auto& th: threads)
				th.join();

		return 0;
}
