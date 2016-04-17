#include "Queue.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <queue>
#include <thread>
#include <random>
namespace {
	const int MAX = 100000;
	const int REPEATE = 1000;
	class thread_guard {
	public:
		explicit thread_guard(std::thread &t):mythread{t}{}
		~thread_guard() {if (mythread.joinable()) mythread.join();}
		thread_guard(const thread_guard &)=delete;
		thread_guard& operator=(const std::thread &)=delete;
	private:
		std::thread &mythread;
	};
}

TEST(BasicTest, InsertAndDel) {
	que::PriorityQueue<int, std::vector<int>, std::greater<int>> pq;
	std::priority_queue<int, std::vector<int>, std::greater<int>> spq;
	std::default_random_engine gene;
	std::uniform_int_distribution<int> dist{1, MAX};
	auto rand = std::bind(dist, gene);
	for (int i = 0; i < REPEATE; i++) {
		int tmp{rand()};
		pq.push(tmp); spq.push(tmp);
	}
	while (!spq.empty()) {
		ASSERT_EQ(spq.top(), pq.top());
		spq.pop(); pq.pop();
	}
}

