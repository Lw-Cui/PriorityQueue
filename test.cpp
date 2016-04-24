#include "Queue.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <queue>
#include <thread>
#include <random>
namespace {
	const int MAX = 1000000;
	const int REPEATE = 10000;
	class Scope_thread {
	public:
		// Only accept rvalue reference
		explicit Scope_thread(std::thread t):mythread{std::move(t)}{}
		~Scope_thread() {mythread.join();}
		Scope_thread(const Scope_thread&)=delete;
		Scope_thread& operator=(const Scope_thread)=delete;
	private:
		std::thread mythread;
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
	while (spq.size() > REPEATE / 2) {
		ASSERT_EQ(spq.top(), pq.top());
		spq.pop(); pq.pop();
	}
	for (int i = 0; i < REPEATE; i++) {
		int tmp{rand()};
		pq.push(tmp); spq.push(tmp);
		spq.pop(); pq.pop();
	}
	while (!spq.empty()) {
		ASSERT_EQ(spq.top(), pq.top());
		spq.pop(); pq.pop();
	}
}

TEST(BasicTest, CopyAndAssign) {
	que::PriorityQueue<int> pq;
	std::vector<int> v;
	for (auto i = 0; i < REPEATE; i++) {
		pq.push(i); v.push_back(i);
	}
	que::PriorityQueue<int> copyed{pq};
	que::PriorityQueue<int> assigned; assigned = pq;
	que::PriorityQueue<int> rvalue_copyed
		{que::PriorityQueue<int>{v.begin(), v.end()}};
	que::PriorityQueue<int> rvalue_assigned 
		= que::PriorityQueue<int>{v.begin(), v.end()};
	while (!copyed.empty()) {
		ASSERT_EQ(copyed.top(), assigned.top());
		ASSERT_EQ(copyed.top(), rvalue_copyed.top());
		ASSERT_EQ(copyed.top(), rvalue_assigned.top());
		copyed.pop(); assigned.pop(); 
		rvalue_copyed.pop(); rvalue_assigned.pop();
	}
}

TEST(ThreadTest, Insert) {
	que::PriorityQueue<int> pq;
	Scope_thread p{std::thread{[&](){pq.push(10);}}};
}
