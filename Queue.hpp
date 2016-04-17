#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "RWLock.hpp"
#include <atomic>
#include <functional>
#include <mutex>
#include <algorithm>
#include <vector>
#include <iostream>
namespace que {
	template<typename T>
	class MobileAtomic
	{
	public:
		MobileAtomic(){}
		MobileAtomic(const T& data): atom(data) {}
		MobileAtomic(const MobileAtomic& mobile): atom(mobile.atom.load()) {}
		inline MobileAtomic& operator=(const MobileAtomic &mobile) {
			atom.store(mobile.atom.load());
			return *this;
		}
		inline operator T() const {return atom.load();}
	private:
		std::atomic<T> atom;
	};

	template<typename T, 
		typename Con = std::vector<MobileAtomic<T>>,
		typename Cmp = std::greater<typename Con::value_type>>
	class PriorityQueue {
	private:
		typedef typename rbl::read_guard<rbl::RBLock<std::mutex>> read_lock;
		typedef typename rbl::write_guard<rbl::RBLock<std::mutex>> write_lock;
		const int BEG = 1;
	public:
		PriorityQueue(const Cmp& c = Cmp()):array(1), compare(c) {}
		T top() {read_lock guard(protector); return array[BEG]; }
		int size() {read_lock guard(protector); return array.size() - BEG; }
		bool empty() {read_lock guard(protector); return !size(); }
		void push(const T& data) {
			write_lock guard(protector);
			array.push_back(data);
			up(array.size() - BEG);
		}
		void pop() {
			write_lock guard(protector);
			array[1] = array.back();
			array.pop_back(); down(BEG);
		}
	private:
		void up(size_t index);
		void down(size_t index);
		Con array; Cmp compare;
		rbl::RBLock<std::mutex> protector;
	};
}
#include "Queue.impl.hpp"
#endif
