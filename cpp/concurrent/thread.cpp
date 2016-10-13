#include <iostream>
#include <thread>
#include <functional>
#include <chrono>

using namespace std;
using namespace std::chrono;

void thread_function(){
    cout << "hello world from thread." << endl;
}

struct F {
    void operator()() const {
        cout << "hello world from F::operator()." << endl;
    }
};

/**
 * thread argument better to use && > by value > & by reference
 */
void work(string&& msg, int&& delay){
    for (int i = 0; i < 10; ++i) {
        cout << msg << endl;
        this_thread::sleep_for(milliseconds(delay));
    }
}


int main() {
    thread t1(thread_function);                 // create and start, no need to start explicitly like java (t.start())
    thread t2 { F() };                          // anything callable
    thread t3 { [](){
        cout << "hello world from lambda." << endl;
    } };
    cout << "hello world from main." << endl;
    t1.join();
    t2.join();
    t3.join();

    // passing argument to thread
    thread ticker(work, string("tick"), 500);
    thread tocker(work, string("tock"), 750);
    ticker.join();
    tocker.join();
    cerr << "bye..." << endl;

    return 0;
}









#include <thread>
#include <future>
#include <iostream>
#include <chrono>


/**
 * future_status, Waits for the result to become available.
 * Blocks until specified timeout_duration has elapsed or the result becomes available,
 * whichever comes first. Returns value identifies the state of the result.
 */

int main()
{
    std::future<int> future = std::async(std::launch::async, [](){
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 8;
    });

    std::cout << "waiting...\n";
    std::future_status status;
    do {
        status = future.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::deferred) {
            std::cout << "deferred\n";
        } else if (status == std::future_status::timeout) {
            std::cout << "timeout\n";
        } else if (status == std::future_status::ready) {
            std::cout << "ready!\n";
        }
    } while (status != std::future_status::ready);

    std::cout << "result is " << future.get() << '\n';
}












#include <thread>
#include <future>
#include <iostream>
#include <chrono>
#include <ctime>


/**
 * time
 */

int main()
{
    std::chrono::time_point<std::chrono::system_clock> p1, p2, p3;

    p2 = std::chrono::system_clock::now();
    p3 = p2 - std::chrono::hours(24);

    std::time_t epoch_time = std::chrono::system_clock::to_time_t(p1);
    std::cout << "epoch: " << std::ctime(&epoch_time);
    std::time_t today_time = std::chrono::system_clock::to_time_t(p2);
    std::cout << "today: " << std::ctime(&today_time);

    std::cout << "hours since epoch: "
              << std::chrono::duration_cast<std::chrono::hours>(
                   p2.time_since_epoch()).count()
              << '\n';
    std::cout << "yesterday, hours since epoch: "
              << std::chrono::duration_cast<std::chrono::hours>(
                   p3.time_since_epoch()).count()
              << '\n';
}



Before you paste, type this in normal mode:
:set paste
Then enter insert mode. You will see the status bar say insert (paste). Paste your code. Hit ESC to return to normal mode, and:
:set nopaste


















#include <thread>
#include <future>
#include <iostream>
#include <atomic>


/**
 * memory model
 * http://wilburding.github.io/blog/2013/04/07/c-plus-plus-11-atomic-and-memory-model/
 * release时，编译器保证不会把其后的写操作移到它后边，否则其他线程就看不到这个修改了；
 * acquire时，不会把其后的读操作移到它前面，否则读到的就是旧数据
 * memory_order_relaxed说明这个操作除了是原子的外，周围的操作随便移动，比较适合做计数器。
 * memory_order_acq_rel基本是memory_order_acquire和memory_order_release的合体。
 * memory_order_scq_cst是memory_order_acq_rel的加强版，除了有acq_rel语义，还保证是sequencially-consistent
 * memory_order_consume是memory_order_acquire的弱化版，它只保证不把跟当前load的变量有依赖的变量reorder，没依赖关系的随便移动
 */

std::atomic<int> flag = 0;
int data = 0;

void thread_1()
{
  data = 1;
  flag.store(1, std::memory_order_release);
}
//gdgfr
void thread_2()
{
  while(flag.load(std::memory_order_acquire) == 0);
  assert(data == 1);
}

class Foo{};

int main()
{
	std::atomic<bool> b;
	bool x1=b.load(std::memory_order_acquire);
	b.store(true);
	x1=b.exchange(false, std::memory_order_acq_rel);


	Foo some_array[5];
	std::atomic<Foo*> p(some_array);
	Foo* x=p.fetch_add(2);  // p加2，并返回原始值
	assert(x==some_array);
	assert(p.load()==&some_array[2]);
	x=(p-=1);  // p减1，并返回原始值
	assert(x==&some_array[1]);
	assert(p.load()==&some_array[1]);
}









#include <thread>
#include <future>
#include <iostream>
#include <atomic>
#include <utility>


/**
 * atomic operation
 */

std::atomic<int> data;
void do_work()
{
    data.fetch_add(5, std::memory_order_relaxed);
	data.fetch_sub(3, std::memory_order_relaxed);
	data++;
	data--;
	--data;
	++data;

	data += 1;
	data -= 1;
}

struct A { int a[100]; };
struct B { int x, y; };

int main()
{
	std::cout << std::boolalpha
              << "std::atomic<A> is lock free? "
              << std::atomic<A>{}.is_lock_free() << '\n'
              << "std::atomic<B> is lock free? "
              << std::atomic<B>{}.is_lock_free() << '\n';
	std::atomic<int> ai(5);
	bool exchanged= ai.compare_exchange_strong( 5, 3 );
	std::cout << "ai= " << ai
	      << "  exchanged= " << std::boolalpha << exchanged
	      << "\n";

	std::thread th1(do_work);
    std::thread th2(do_work);
    std::thread th3(do_work);
    std::thread th4(do_work);
    std::thread th5(do_work);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();

    std::cout << "Result:" << data << '\n';
}














#include<iostream>
#include<thread>
#include<exception>
#include<stdexcept>


/**
 * exception_ptr type that allows to transport exceptions between threads
 * unhandled exception in thread will crash whole process
 */

static std::exception_ptr teptr = nullptr;

void f()
{
    try
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        throw std::runtime_error("To be passed between threads");
    }
    catch(...)
    {
        teptr = std::current_exception();
    }
}

int main(int argc, char **argv)
{
    std::thread mythread(f);
    mythread.join();

    if (teptr) {
        try{
            std::rethrow_exception(teptr);
        }
        catch(const std::exception &ex)
        {
            std::cerr << "Thread exited with exception: " << ex.what() << "\n";
        }
    }

    return 0;
}












#include <iostream>
#include <thread>
#include <exception>
#include <vector>
#include <future>
#include <atomic>


/**
 * parallel_find
 */

class join_threads
{
  std::vector<std::thread>& threads;
public:
  explicit join_threads(std::vector<std::thread>& threads_):
    threads(threads_)
  {}
  ~join_threads()
  {
    for(unsigned long i=0;i<threads.size();++i)
    {
      if(threads[i].joinable())
        threads[i].join();
    }
  }
};

template<typename Iterator,typename MatchType>
Iterator parallel_find(Iterator first,Iterator last,MatchType match)
{
    struct find_element
    {
        void operator()(Iterator begin,Iterator end,
                        MatchType match,
                        std::promise<Iterator>* result,
                        std::atomic<bool>* done_flag)
        {
            try
            {
                for(;(begin!=end) && !done_flag->load();++begin)
                {
                    if(*begin==match)
                    {
                        result->set_value(begin);
                        done_flag->store(true);
                        return;
                    }
                }
            }
            catch(...)
            {
                try
                {
                    result->set_exception(std::current_exception());
                    done_flag->store(true);
                }
                catch(...)
                {}
            }
        }
    };

    unsigned long const length=std::distance(first,last);

    if(!length)
        return last;

    unsigned long const min_per_thread=25;
    unsigned long const max_threads=
        (length+min_per_thread-1)/min_per_thread;

    unsigned long const hardware_threads=
        std::thread::hardware_concurrency();

    unsigned long const num_threads=
        std::min(hardware_threads!=0?hardware_threads:2,max_threads);

    unsigned long const block_size=length/num_threads;

    std::promise<Iterator> result;
    std::atomic<bool> done_flag(false);
    std::vector<std::thread> threads(num_threads-1);
    {
        join_threads joiner(threads);

        Iterator block_start=first;
        for(unsigned long i=0;i<(num_threads-1);++i)
        {
            Iterator block_end=block_start;
            std::advance(block_end,block_size);
            threads[i]=std::thread(find_element(),
                                   block_start,block_end,match,
                                   &result,&done_flag);
            block_start=block_end;
        }
        find_element()(block_start,last,match,&result,&done_flag);
    }
    if(!done_flag.load())
    {
        return last;
    }
    return result.get_future().get();
}

int main(int argc, char **argv)
{
    std::vector<int> vi;
    for(int i = 0; i < 101; ++i) {
        vi.push_back(i);
    }
	auto iter = parallel_find(vi.begin(), vi.end(), 7);
	if(iter != vi.end())
		std::cout << "find: " << *iter << std::endl;

    return 0;
}












#include <iostream>
#include <vector>
#include <string>

#include <cassert>
#include <crtdbg.h>

/**
 * debug utility
 * assert, only run for debug mode
 * verify, assert for debug mode, run expression for release mode
 * trace, output something for debug mode, output nothing for release mode
 */

struct Tracer
{
	const char* file_name;
	unsigned int line;
	Tracer(const char* _file_name, const unsigned int _line): file_name(_file_name), line(_line){}
	void operator()(const std::string msg) const {
		std::cout << file_name << "(" << line << "): " << msg << std::endl;
	}
};

#ifdef _DEBUG
inline auto Trace(const std::string msg) -> void {
	std::cout << msg << std::endl;
}
#endif

#ifdef _DEBUG
#define VERIFY _ASSERTE
#define TRACE Tracer(__FILE__, __LINE__)
#else
#define VERIFY(expression) (expression)
#define TRACE __noop
#endif

auto main() -> int {
	VERIFY(std::cout << "verify test" << std::endl);
	TRACE("trace test");
	static_assert( sizeof(float) == 4, "cannot handle this kind of floats!");
	_ASSERTE(4 == 5);			// for GUI application popup, windows specific
	assert(4 == 5);				// for cmd application
}








#include <iostream>
#include <memory>
#include <vector>
#include <cstring>

using namespace std;

/**
 * unique_ptr, exclusively owns object, cannot be copied / assigned, can be moved
 * shared_ptr, reference count, can be copied / assigned, can be moved
 * weak_ptr, circle reference
 */

unique_ptr<int> clone(int p) {
    unique_ptr<int> pInt(new int(p));
    return pInt;
}

void destroy_int(int* p){
	std::cout << "deleting p, value is : " << *p << endl;
	delete p;
}
void unique_ptr_demo(){
    unique_ptr<int, void(*)(int*)> fPtr1(nullptr, destroy_int);
    unique_ptr<int, void(*)(int*)> fPtr2(new int(4), destroy_int);
    unique_ptr<int, void(*)(int*)> fPtr3(new int(5), destroy_int);

    cout << "fPtr2 release before: " << fPtr2.get() << endl;
    int *pF = fPtr2.release();
    cout << "fPtr2 release before: " << fPtr2.get() << " and pF value: " << *pF << endl;
    cout << "move before fPtr1 address: " << fPtr1.get() << " fPtr3 address: " << fPtr3.get() << endl;
    fPtr1 = move(fPtr3);
    cout << "move after fPtr1 address: " << fPtr1.get() << " fPtr3 address: " << fPtr3.get() << endl;
    fPtr1.reset();
    cout << "move after fPtr1 address: " << fPtr1.get() << endl;

    int p = 5;
    unique_ptr<int> ret = clone(p);
    cout << *ret << endl;

    // manage array
    unique_ptr<int[]> pArray(new int[5] {1, 2, 3, 4, 5});
    pArray[0] = 0;

    // manage point array
    vector<unique_ptr<int>> vec;
    unique_ptr<int> p1(new int(5));
    vec.push_back(move(p1));
}

class A;
class B;

class A {
public:
    weak_ptr<B> b;
    ~A () {
        cout<< "A released" << endl;
    }
};

class B {
public:
    weak_ptr<A> a;
    ~B () {
        cout<< "B released" << endl;
    }
    void output () {
        cout<< "I'm B" << endl;
    }
};

template <typename T>
shared_ptr<T> make_shared_array(size_t size) {
    return shared_ptr<T>(new T[size], default_delete<T[]>());
}

void shared_ptr_demo(){
	shared_ptr<int> sp = shared_ptr<int>(nullptr);
	cout << sp.use_count() << endl;
	cout << sp.unique() << endl;
	sp = make_shared<int>(5);
	cout << sp.use_count() << endl;
	cout << sp.unique() << endl;
	shared_ptr<int> sp1 = sp;
	cout << sp.use_count() << endl;
	cout << sp.unique() << endl;
	cout << (sp == sp1) << endl;

    auto sp_array = make_shared_array<char>(100);
    strcpy(sp_array.get(), "hello smart pointer");
    sp_array.get()[0] = 'a';
    cout << sp_array << endl;
}

void weak_ptr_demo(){
	cout << "weak_ptr_demo" << endl;
	shared_ptr<int> sp = shared_ptr<int>(new int(5));
	weak_ptr<int> wp = weak_ptr<int>(sp);
	cout << "this time not expired " << wp.expired() << endl;
	cout << wp.use_count() << endl;
	if(shared_ptr<int> locked = wp.lock()){				// get strong reference from weak pointer
		cout << *locked << endl;
	}
	sp = nullptr;
	cout << "this time expired " << wp.expired() << endl;
	cout << wp.use_count() << endl;
	if(shared_ptr<int> locked = wp.lock()){
		cout << *locked << endl;
	} else {
		wp.reset();										// although manged object is released, this release reference control block
	}

	shared_ptr<A> a(new A());
    shared_ptr<B> b(new B());
	// weak_ptr won't add reference count of shared_ptr, used in cyclic reference
    a->b = b;
    b->a = a;

    if(a->b.expired()){
        // because weak_ptr doesn't overload operator * and ->, so get shared_ptr from weak_ptr to handle data
        shared_ptr<B> b2(a->b.lock());
        b2->output();
    }
}


auto main() -> int {
	cout << boolalpha;
	unique_ptr_demo();
    shared_ptr_demo();
	weak_ptr_demo();
}
