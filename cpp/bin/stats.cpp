#include <algorithm>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class DescriptiveStatistics {
private:
    const size_t INFINITE_WINDOW = 0;
    size_t windowSize{INFINITE_WINDOW};
    std::deque<double> dq;

public:
    DescriptiveStatistics() {}

    DescriptiveStatistics(size_t window) { set_window_size(window); }

    void add_value(double v) {
        if (windowSize != INFINITE_WINDOW) {
            size_t n = size();
            if (n == windowSize) {
                dq.pop_front();
                dq.push_back(v);
            } else if (n < windowSize) {
                dq.push_back(v);
            }
        } else {
            dq.push_back(v);
        }
    }

    void sort() { std::sort(dq.begin(), dq.end()); }

    /**
     * favor percentile operation, those need sorted data
     * performance very poor if data volume is huge, use add_value and sort at last approach
     */
    void add_value_and_sort(double v) {
        add_value(v);
        insert_sort();
    }

    void remove_most_recent_value() { dq.pop_back(); }

    double replace_most_recent_value(double v) {
        double old = *(dq.end() - 1);
        *(dq.end() - 1) = v;
        return old;
    }

    double get_mean() {
        if (size() == 0) return 0;
        double sum = get_sum();
        return sum / size();
    }

    double get_geometric_mean() {
        if (size() == 0) return 0;
        double sumOfLog = 0;
        for (double x : dq) {
            sumOfLog += std::log(x);
        }
        return std::exp(sumOfLog / size());
    }

    double get_variance() { return _get_variance(true); }

    double get_population_variance() { return _get_variance(false); }

    double get_standard_deviation() {
        if (size() <= 1)
            return 0;
        else
            return std::sqrt(get_variance());
    }

    double get_skewness() {
        size_t n = size();
        if (n <= 2) return 0;

        double m = get_mean();
        double accum = 0.0;
        double accum2 = 0.0;

        for (double x : dq) {
            double d = x - m;
            accum += d * d;
            accum2 += d;
        }

        double variance = (accum - accum2 * accum2 / n) / (n - 1);
        double accum3 = 0.0;

        for (double x : dq) {
            double d = x - m;
            accum3 += d * d * d;
        }

        accum3 /= variance * std::sqrt(variance);
        return n / ((n - 1.0) * (n - 2.0)) * accum3;
    }

    double get_max() {
        if (size() == 0)
            return 0;
        else
            return *std::max_element(dq.begin(), dq.end());
    }

    double get_min() {
        if (size() == 0)
            return 0;
        else
            return *std::min_element(dq.begin(), dq.end());
    }

    size_t size() const { return dq.size(); }

    double get_sum() { return std::accumulate(dq.begin(), dq.end(), 0.0); }

    double get_sum_square() {
        double sumSq = 0.0;

        for (double x : dq) {
            sumSq += x * x;
        }

        return sumSq;
    }

    void clear() { dq.clear(); }

    size_t get_window_size() { return windowSize; }

    void set_window_size(size_t _windowSize) {
        windowSize = _windowSize;
        if (windowSize != INFINITE_WINDOW && windowSize < dq.size()) {
            auto count = dq.size() - windowSize;
            while (count > 0) {
                dq.pop_front();
                --count;
            }
        }
    }

    double get_element(int index) { return dq[index]; }

    /**
     * need call sort first if you choose add_value instead of add_value_and_sort
     */
    double get_percentile(double p) {
        if (size() == 0) return 0;

        p = std::min(p, 100.0);
        p = std::max(p, 0.0);
        int target = static_cast<int>(size() * p * 0.01);
        return dq[target];
    }

private:
    double _get_variance(bool isBiasCorrected) {
        if (size() <= 1) return 0;
        double mean = get_mean();

        double accum = 0.0;
        double dev = 0.0;
        double accum2 = 0.0;

        for (double x : dq) {
            dev = x - mean;
            accum += dev * dev;
            accum2 += dev;
        }

        double len = size();

        if (isBiasCorrected) {
            return (accum - accum2 * accum2 / len) / (len - 1.0);
        } else {
            return (accum - accum2 * accum2 / len) / len;
        }
    }

    /**
     * only the last element is not in order
     */
    void insert_sort() {
        if (size() <= 1) return;

        auto itr = dq.end() - 1;
        double key = *itr;
        --itr;
        while (itr >= dq.begin() && (key < *itr)) {
            *(itr + 1) = *itr;
            --itr;
        }
        *(itr + 1) = key;
    }
};

class LatencyStatistics {
public:
    DescriptiveStatistics ds;
    size_t span{0};       // measure in second, 0 means infinite time
    double startTime{0};  // start time to record statistics

public:
    LatencyStatistics(size_t s = 0) : span(s) {}

    void add(double v) { ds.add_value(v); }

    void print_result() {
        if (ds.size()) {
            ostringstream os;
            if (std::abs(ds.get_mean()) < 1) {
                os << std::fixed << setprecision(9);
            }
            os << "st " << startTime << " ,span " << span << " ,min " << ds.get_min() << " ,max " << ds.get_max()
               << " ,mean " << ds.get_mean() << " ,stddev " << ds.get_standard_deviation();

            ds.sort();
            for (int i = 50; i <= 90; i += 10) {
                os << " ,p" << i << " " << ds.get_percentile(i);
            }
            for (int i = 91; i <= 99; ++i) {
                os << " ,p" << i << " " << ds.get_percentile(i);
            }
            for (int i = 1; i <= 9; ++i) {
                os << " ,p99." << i << " " << ds.get_percentile((990.0 + i) * 0.1);
            }
            cout << os.str() << ",;\n";
        }
    }
};

int main() {
    LatencyStatistics statistics;
    double value;
    while (cin >> value) {
        statistics.add(value);
    }
    statistics.print_result();
    return 0;
}
