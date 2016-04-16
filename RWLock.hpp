#ifndef RB_LOCK_H
#define RB_LOCK_H
#include <mutex>
#include <condition_variable>
namespace rbl {
	template <typename Mutex>
	class RBLock {
	public:
		RBLock():writer{false}, reader{false}{}
		void readLock() {
			std::lock_guard<Mutex> guard(mut);
			readProcess.wait(guard, [&]{return !writer && !pendingWriter;});
			reader++;
		}
		void writeLock() {
			std::lock_guard<Mutex> guard(mut);
			pendingWriter++;
			writeProcess.wait(guard, [&]{return !writer && !reader;});
			writer = true; pendingWriter--;
		}
		void unlock() {
			std::lock_guard<Mutex> guard(mut);
			if (writer) writer = false;
			else if (reader) reader--;
			// writer = true->false; reader = 0; pendingWriter >= 0;
			// OR: writer = false; --reader >= 0; pendingWriter >= 0;
			if (!reader && pendingWriter)
				writeProcess.notify_one();
			else // reader > 0 || pendingWriter == 0
				readProcess.notify_all();
		}
	private:
		bool writer;
		int pendingWriter;
		int reader; //the number of reader processing
		Mutex mut;
		std::condition_variable writeProcess, readProcess;
	};
}
#endif
