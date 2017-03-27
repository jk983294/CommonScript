void sum_marix_row_major(const Matrix<int>& m, long long& sum)
{
    sum = 0;
    for (unsigned r = 0; r < m.rows(); ++r)
    {
        for (unsigned c = 0; c < m.columns(); ++c)
        {
            sum += m[r][c];
        }
    }
}

void sum_marix_column_major(const Matrix<int>& m, long long& sum)
{
    sum = 0;
    for (unsigned c = 0; c < m.columns(); ++c)
    {
        for (unsigned r = 0; r < m.rows(); ++r)
        {
            sum += m[r][c];
        }
    }
}
