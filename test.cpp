#include "Queue.h"
#include "gtest/gtest.h"
#include <iostream>
#include <set>
#include <thread>
using namespace std;
using namespace queue;
const int MAX = 100000;
TEST(BasicTest, InsertTest) {
	PriorityQueue<int> queue;
	for (int i = MAX; i > 0; i--)
		queue.insert(i);
	set<int> container;
	for (auto p: queue)
		container.insert(p);
	int cnt = 1;
	for (auto value: container)
		ASSERT_EQ(value, cnt++);
}

TEST(BasicTest, delMinTest) {
	PriorityQueue<int> queue;
	for (int i = MAX; i > 0; i--)
		queue.insert(i);
	for (int i = 1; i <= MAX; i++)
		ASSERT_EQ(queue.delMin(), i);
}

class thread_guard {
public:
	explicit thread_guard(thread& t):mythread(t){}
	~thread_guard() {if (mythread.joinable()) mythread.join();}
	thread_guard(const thread_guard &)=delete;
	thread_guard& operator=(const thread &)=delete;
private:
	std::thread& mythread;
};

void delMin(PriorityQueue<int>& p) {
	for (int i = MAX; i > 0; i--)
		p.insert(i);
}

TEST(ThreadTest, InsertTest) {
	PriorityQueue<int> p;
	thread t1(delMin, ref(p));
	thread t2(delMin, ref(p));
	thread_guard guard1(t1);
	thread_guard guard2(t2);
}
