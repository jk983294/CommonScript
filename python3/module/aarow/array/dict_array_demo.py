import pyarrow as pa

if __name__ == '__main__':
    """
    it is similar to a factor in R or a pandas.Categorical
    It enables integer indices referencing a shared dictionary containing the distinct values in the logical array.
    """
    indices = pa.array([0, 1, 0, 1, 2, 0, None, 2])
    dictionary = pa.array(['foo', 'bar', 'baz'])
    dict_array = pa.DictionaryArray.from_arrays(indices, dictionary)
    print(dict_array.type)  # dictionary<values=string, indices=int64, ordered=0>
    print(dict_array.indices)
    print(dict_array.dictionary)

    df = dict_array.to_pandas()
    print(df)
