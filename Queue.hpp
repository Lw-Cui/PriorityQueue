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
	public:
		typedef typename Con::const_iterator const_iterator;
		PriorityQueue(const Cmp& c = Cmp()):array(1), compare(c) {}
		inline const_iterator begin() const {return ++array.begin();}
		inline const_iterator end() const {return array.end();}

		inline T top() {
			rbl::read_guard<rbl::RBLock<std::mutex>> guard(protector);
			return array[1];
		}
		inline int size() {
			rbl::read_guard<rbl::RBLock<std::mutex>> guard(protector);
			return array.size() - 1;
		}
		inline bool empty() {
			rbl::read_guard<rbl::RBLock<std::mutex>> guard(protector);
			return size() == 0;
		}

		inline void push(const T& data) {
			rbl::write_guard<rbl::RBLock<std::mutex>> guard(protector);
			array.push_back(data);
			up(array.size() - 1);
		}

		inline void pop() {
			rbl::write_guard<rbl::RBLock<std::mutex>> guard(protector);
			array[1] = array.back();
			array.pop_back();
			down(1);
		}
	private:
		void up(size_t index);
		void down(size_t index);
		Con array;
		Cmp compare;
		rbl::RBLock<std::mutex> protector;
	};
}
#include "Queue.impl.hpp"
#endif
