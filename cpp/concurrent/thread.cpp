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






#include <iostream>
#include <mutex>
#include <thread>
#include <type_traits>

using namespace std;

/**
 * usually dead lock caused by circle wait, break the circle to solve the dead lock issue
 */
mutex myMutex1, myMutex2;

class DeadLockObject {
public:
	void f1(int i)
	{
		lock_guard<mutex> g1(myMutex1);
		lock_guard<mutex> g2(myMutex2);
		cout << " " << i << " ";
	}

	void f2(int i)
	{
		lock_guard<mutex> g2(myMutex2);
		lock_guard<mutex> g1(myMutex1);
		cout << " " << i << " ";
	}
};

class NoDeadLockObject {
public:
	void f1(int i)
	{
		std::lock(myMutex1, myMutex2);
		cout << " " << i << " ";
	}

	void f2(int i)
	{
		std::lock(myMutex1, myMutex2);
		cout << " " << i << " ";
	}
};

/**
 * always low number block high number
 * 1 can be locked when 10 is hold lock
 * 10 cannot be locked when 1 is locked
 */
class hierarchical_mutex{
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;

    void check_for_hierarchy_violation(){
        cout << "check_for_hierarchy_violation " << this_thread_hierarchy_value << " " << hierarchy_value << endl;
        if(this_thread_hierarchy_value <= hierarchy_value)
            throw std::logic_error("mutex hierarchy violated");
    }
    void update_hierarchy_value(){
        cout << "update_hierarchy_value " << this_thread_hierarchy_value << " " << hierarchy_value << endl;
        previous_hierarchy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }
public:
    explicit hierarchical_mutex(unsigned long value): hierarchy_value(value), previous_hierarchy_value(0){}
    void lock(){
        check_for_hierarchy_violation();
        internal_mutex.lock();
        update_hierarchy_value();
    }
    void unlock(){
        this_thread_hierarchy_value = previous_hierarchy_value;
        internal_mutex.unlock();
    }
    bool try_lock(){
        check_for_hierarchy_violation();
        if(!internal_mutex.try_lock())
            return false;
        update_hierarchy_value();
        return true;
    }
};
thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(numeric_limits<unsigned long>::max());


hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);

int low_level_func(){
    std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
    return 42;
}
void high_level_func(){
    std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
    low_level_func();
}

int main(){
    high_level_func();
    return 0;
}
























#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/**
 * unique_lock is a general-purpose mutex ownership wrapper allowing deferred locking, time-constrained attempts at locking,
 * recursive locking, transfer of lock ownership, and use with condition variables.
 */
class some_big_object {};
class X
{
private:
  some_big_object some_detail;
  std::mutex m;
public:
  X(some_big_object const& sd): some_detail(sd){}
  friend void swap(X& lhs, X& rhs);
};
void swap(X& lhs, X& rhs){
	if(&lhs==&rhs) return;
    std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);
    std::lock(lock_a,lock_b);
    swap(lhs.some_detail, rhs.some_detail);
}

int main(){
    return 0;
}










#include <iostream>
#include <mutex>
#include <thread>
#include <memory>

using namespace std;

/**
 * lazy initialization
 */
struct connection_info{};
struct data_packet{};
struct connection_handle{
    void send_data(data_packet const&){}
    data_packet receive_data(){
        return data_packet();
    }
};
struct remote_connection_manager{
    connection_handle open(connection_info const&){
        return connection_handle();
    }
} connection_manager;

class X
{
private:
    connection_info connection_details;
    connection_handle connection;
    std::once_flag connection_init_flag;

    void open_connection(){
        connection = connection_manager.open(connection_details);
    }
public:
    X(connection_info const& connection_details_): connection_details(connection_details_){}
    void send_data(data_packet const& data){
        std::call_once(connection_init_flag, &X::open_connection, this);
        connection.send_data(data);
    }
    data_packet receive_data(){
        std::call_once(connection_init_flag, &X::open_connection, this);
        return connection.receive_data();
    }
};

int main(){
	connection_info info;
	X x(info);
	x.receive_data();
    return 0;
}





















#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>

using namespace std;

/**
 * producer consumer
 */

struct data_chunk {};
data_chunk prepare_data() {
	cout << "producer" << endl;
    return data_chunk();
}
void process(data_chunk&) {
	cout << "consumer" << endl;
}

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

void data_preparation_thread()
{
    while(true)
    {
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        data_chunk const data = prepare_data();
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
}

void data_processing_thread()
{
    while(true)
    {
        std::unique_lock<std::mutex> lk(mut);
		// check once, if failed, unlock lk and block this thread util notified
		// when notified, first acquire lock, then check condition
        data_cond.wait(lk, []{return !data_queue.empty();});
        data_chunk data = data_queue.front();
        data_queue.pop();
        lk.unlock();
        process(data);
    }
}

int main(){
	std::thread t1(data_preparation_thread);
    std::thread t2(data_processing_thread);

    t1.join();
    t2.join();
    return 0;
}







#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <memory>

using namespace std;

/**
 * threadsafe_queue
 */

template<typename T>
class threadsafe_queue
{
private:
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
public:
    threadsafe_queue(){}
    threadsafe_queue(threadsafe_queue const& other){
        std::lock_guard<std::mutex> lk(other.mut);
        data_queue=other.data_queue;
    }
    void push(T new_value){
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }
    void wait_and_pop(T& value){
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value=data_queue.front();
        data_queue.pop();
    }
    std::shared_ptr<T> wait_and_pop(){
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }
    bool try_pop(T& value){
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty)
            return false;
        value=data_queue.front();
        data_queue.pop();
    }
    std::shared_ptr<T> try_pop(){
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }
    bool empty() const {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};


int main(){
    return 0;
}










#include <iostream>
#include <future>
#include <string>

using namespace std;

/**
 * future wait for one-time event
 * std::launch::async 表明函数必须在其所在的独立线程上执行
 * std::launch::defered，用来表明函数调用被延迟到wait()或get()函数调用时才执行
 * d::launch::deferred | std::launch::async, 实现可以选择这两种方式的一种
 */

struct X
{
	void foo(int,std::string const&){}
	std::string bar(std::string const&){
		return string("X::bar");
	}
};

struct Y
{
	double operator()(double x){
		return x + 1.0;
	}
};

int main(){
	X x;
	future<void> f1 = std::async(&X::foo, &x, 42, "hello");		// 调用p->foo(42, "hello")，p是指向x的指针
	future<string> f2 = std::async(&X::bar, x, "goodbye");		// 调用tmpx.bar("goodbye")， tmpx是x的拷贝副本

	Y y;
	future<double> f3 = std::async(Y(), 3.141);
	future<double> f4 = std::async(std::ref(y), 2.718);

	std::cout << f2.get() << std::endl;
	std::cout << f3.get() << std::endl;
	std::cout << f4.get() << std::endl;
    return 0;
}













#include <iostream>
#include <future>
#include <string>
#include <deque>
#include <mutex>
#include <thread>
#include <utility>

using namespace std;

/**
 * packaged_task
 */

// unique function to avoid disambiguating the std::pow overload set
int f(int x, int y) { return x + y; }

void task_lambda()
{
    std::packaged_task<int(int,int)> task([](int a, int b) {
        return a + b;
    });
    std::future<int> result = task.get_future();
    task(2, 9);
    std::cout << "task_lambda:\t" << result.get() << endl;
}

void task_bind()
{
    std::packaged_task<int()> task(std::bind(f, 2, 11));
    std::future<int> result = task.get_future();
    task();
    std::cout << "task_bind:\t" << result.get() << endl;
}

void task_thread()
{
    std::packaged_task<int(int,int)> task(f);
    std::future<int> result = task.get_future();
    std::thread task_td(std::move(task), 2, 10);
	task_td.detach();
    std::cout << "task_thread:\t" << result.get() << endl;
}

int main()
{
    task_lambda();
    task_bind();
    task_thread();
	return 0;
}














#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>


/**
 * promise
 */

void accumulate(std::vector<int>::iterator first,
                std::vector<int>::iterator last,
                std::promise<int> accumulate_promise)
{
    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum);  // Notify future
}

void do_work(std::promise<void> barrier)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    barrier.set_value();
}

int main()
{
    // Demonstrate using promise<int> to transmit a result between threads.
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future();
    std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
                            std::move(accumulate_promise));
    accumulate_future.wait();  // wait for result
    std::cout << "result=" << accumulate_future.get() << '\n';
    work_thread.join();  // wait for thread completion

    // Demonstrate using promise<void> to signal state between threads.
    std::promise<void> barrier;
    std::future<void> barrier_future = barrier.get_future();
    std::thread new_work_thread(do_work, std::move(barrier));
    barrier_future.wait();
    new_work_thread.join();
}


















#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>


/**
 * shared_future
 * multiple threads are allowed to wait for the same shared state.
 */

int main()
{
    std::promise<void> ready_promise, t1_ready_promise, t2_ready_promise;
    std::shared_future<void> ready_future(ready_promise.get_future());

    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    auto fun1 = [&, ready_future]() -> std::chrono::duration<double, std::milli>
    {
        t1_ready_promise.set_value();
        ready_future.wait(); // waits for the signal from main()
        return std::chrono::high_resolution_clock::now() - start;
    };


    auto fun2 = [&, ready_future]() -> std::chrono::duration<double, std::milli>
    {
        t2_ready_promise.set_value();
        ready_future.wait(); // waits for the signal from main()
        return std::chrono::high_resolution_clock::now() - start;
    };

    auto result1 = std::async(std::launch::async, fun1);
    auto result2 = std::async(std::launch::async, fun2);

    // wait for the threads to become ready
    t1_ready_promise.get_future().wait();
    t2_ready_promise.get_future().wait();

    // the threads are ready, start the clock
    start = std::chrono::high_resolution_clock::now();

    // signal the threads to go
    ready_promise.set_value();

    std::cout << "Thread 1 received the signal "
              << result1.get().count() << " ms after start\n"
              << "Thread 2 received the signal "
              << result2.get().count() << " ms after start\n";
}
