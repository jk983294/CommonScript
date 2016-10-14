#include <iostream>
#include <thread>
#include <exception>
#include <vector>
#include <future>
#include <atomic>


class join_threads
{
    std::vector<std::thread>& threads;
public:
    explicit join_threads(std::vector<std::thread>& threads_):
            threads(threads_) {}
    ~join_threads() {
        for(unsigned long i=0;i<threads.size();++i)
        {
            if(threads[i].joinable())
                threads[i].join();
        }
    }
};

template<typename Iterator,typename MatchType>
Iterator parallel_find(Iterator first, Iterator last, MatchType match)
{
    struct find_element
    {
        void operator()(Iterator begin, Iterator end,
                        MatchType match,
                        std::promise<Iterator>* result,
                        std::atomic<bool>* done_flag)
        {
            try
            {
                for(; (begin != end) && !done_flag->load(); ++begin)    // always check done_flag, if find then return
                {
                    if(*begin == match)
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

    const int length = std::distance(first, last);

    if(!length)
        return last;

    const int min_per_thread = 25;
    const int max_threads= (length + min_per_thread - 1)/min_per_thread;
    const int hardware_threads= std::thread::hardware_concurrency();
    const int num_threads= std::min(hardware_threads !=0 ? hardware_threads : 2, max_threads);
    const int block_size= length / num_threads;

    std::promise<Iterator> result;
    std::atomic<bool> done_flag(false);
    std::vector<std::thread> threads(num_threads - 1);

    {
        join_threads joiner(threads);

        Iterator block_start = first;
        for(unsigned long i=0;i<(num_threads-1);++i)
        {
            Iterator block_end = block_start;
            std::advance(block_end, block_size);
            threads[i] = std::thread(find_element(), block_start, block_end, match, &result, &done_flag);
            block_start = block_end;
        }
        find_element()(block_start, last, match, &result, &done_flag);
    }

    if(!done_flag.load()) {
        return last;
    }
    return result.get_future().get();
}

int main()
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