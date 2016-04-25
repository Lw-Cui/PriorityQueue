_Pragma ("once");
#include "RWLock.hpp"
#include <atomic>
#include <mutex>
#include <vector>
namespace que {
	template <typename T>
	class MobileAtomic
	{
	public:
		MobileAtomic(){}
		MobileAtomic(const T& data): atom{data} {}
		// atmoic cannot copy/move. So rvalue argument is invalid.
		MobileAtomic(const MobileAtomic& mobile): atom{mobile.atom.load()} {}
		MobileAtomic& operator=(const MobileAtomic &mobile) {
			atom.store(mobile.atom.load()); return *this;
		}
		operator T() const {return atom.load();}
	private:
		std::atomic<T> atom;
	};

	template<typename T, 
		typename Con = std::vector<MobileAtomic<T>>,
		typename Cmp = std::less<typename Con::value_type>>
	class PriorityQueue {
	private:
		using read_lock = rbl::read_guard<rbl::RBLock<std::mutex>>;
		using write_lock = rbl::write_guard<rbl::RBLock<std::mutex>>;
		static const int BEG = 1;
	public:
		friend void steal(PriorityQueue &first, PriorityQueue &second) {
			first.array = std::move(second.array);
			first.compare = std::move(second.compare);
		}
		PriorityQueue(const Cmp& c = Cmp()):array{1}, compare{c} {}
		template <typename InputIt>
		PriorityQueue(InputIt first, InputIt last, const Cmp& c = Cmp())
			:PriorityQueue{c} {
			while (first != last) push(*first++);
		}
		~PriorityQueue() {}
		PriorityQueue(const PriorityQueue &other):array{other.array}, compare{other.compare} {}
		PriorityQueue(PriorityQueue &&other):PriorityQueue{} {steal(*this, other);}
		PriorityQueue& operator=(PriorityQueue other) {steal(*this, other); return *this;}
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
			array[BEG] = array.back();
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
