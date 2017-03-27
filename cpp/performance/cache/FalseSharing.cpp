const int P = 10;           // thread count
const int DIM = 100;        // matrix dimension
int result[P];              // global result
int odds = 0;               // aggregated result

// each of P parallel workers processes 1/P-th of data
// the p-th worker records its partial result in result[P]
int count_odd(const Matrix<int>& m){
    for (unsigned i = 0; i < P; i++)
    {
        pool.run([&, p]{
            result[p] = 0;
            int chunkSize = DIM / P + 1;
            int myStart = p * chunkSize;
            int myEnd = min(myStart + chunkSize, DIM);

            for (int i = myStart; i < myEnd; i++)
                for (int j = 0; j < DIM; j++)
                    if (m[i * DIM + j] % 2 != 0)
                        ++result[p];
        });
    }

    pool.join();
    for (int i = 0; i < P; i++)
        odds += result[i];
}

int count_odd_locality(const Matrix<int>& m){
    for (unsigned i = 0; i < P; i++)
    {
        pool.run([&, p]{
            int local_result = 0;
            int chunkSize = DIM / P + 1;
            int myStart = p * chunkSize;
            int myEnd = min(myStart + chunkSize, DIM);

            for (int i = myStart; i < myEnd; i++)
                for (int j = 0; j < DIM; j++)
                    if (m[i * DIM + j] % 2 != 0)
                        ++local_result;

            result[p] = local_result;
        });
    }

    pool.join();
    for (int i = 0; i < P; i++)
        odds += result[i];
}
