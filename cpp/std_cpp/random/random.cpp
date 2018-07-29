#include <algorithm>
#include <array>
#include <iostream>
#include <random>

using namespace std;

template <typename T, typename G>
void generate(string&& desc, T& distribution, G& generator) {
    std::cout << desc << std::endl;
    for (int i = 0; i < 10; ++i) std::cout << distribution(generator) << " ";
    std::cout << std::endl;
}

int main() {
    random_device rd;         // non-deterministic generator
    mt19937 generator(rd());  // to seed mersenne twister.

    // Uniform
    std::uniform_int_distribution<int> uid(0, 9);
    generate("uniform_int_distribution [0, 9]:", uid, generator);
    std::uniform_real_distribution<double> urd(0.0, 10.0);
    generate("uniform_real_distribution [0, 10.0):", urd, generator);

    // Bernoulli
    std::bernoulli_distribution bd(0.5);
    generate("1 time bernoulli experiment 0.5 up 0.5 down", bd, generator);
    std::binomial_distribution<int> bdn(10, 0.5);
    generate("10 time bernoulli experiments with 0.5 up, the up number", bdn, generator);
    std::geometric_distribution<int> gd(0.3);
    generate("the number of unsuccessful trials before a first success in a sequence of trials", gd, generator);
    std::negative_binomial_distribution<int> nbd(3, 0.5);
    generate("the number of successful trials before k unsuccessful trials in a sequence of trials", nbd, generator);

    // Rate-based
    std::poisson_distribution<int> pd(4.0);
    generate("a specific count of independent events occurring within a fixed interval with mean 4.0", pd, generator);
    std::exponential_distribution<double> ed(4.0);
    generate("the interval between two random events that are independent with avg rate 4.0", ed, generator);
    std::gamma_distribution<double> gammad(2.0, 2.0);
    generate("aggregation of α exponential distribution, each with β used to model waiting time", gammad, generator);
    std::weibull_distribution<double> wbd(2.0, 4.0);
    generate("the lifetime for which the death probability is proportional to the a-th power of time", wbd, generator);
    std::extreme_value_distribution<double> evd(2.0, 4.0);
    generate("the extreme (maximum or minimum) of a number of samples of a random variable", evd, generator);

    // Normal distribution
    std::normal_distribution<double> nd(0.0, 1.0);
    generate("normal_distribution mean & stddev", nd, generator);
    std::lognormal_distribution<double> lnd(0.0, 1.0);
    generate("random numbers whose logarithms are normally distributed", lnd, generator);
    std::chi_squared_distribution<double> csd(3.0);
    generate("the square of n independent standard normal random variables were added", csd, generator);

    std::cauchy_distribution<double> cd(5.0, 1.0);
    generate("the result of dividing two independent standard normal random variables", cd, generator);
    std::fisher_f_distribution<double> ffd(2.0, 2.0);
    generate("the result of dividing two independent Chi-squared distributions of m and n degrees of freedom", ffd,
             generator);
    std::student_t_distribution<double> sd(10.0);
    generate("result of normalize the values of small sample (n+1 values) of independent normally-distributed values",
             sd, generator);

    // shuffle
    std::array<int, 10> foo{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    shuffle(foo.begin(), foo.end(), generator);
    for (int& x : foo) std::cout << x << ' ';
    std::cout << std::endl;
    return 0;
}
