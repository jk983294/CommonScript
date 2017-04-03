/ERROR/{
    a[$2]++
}
END{
    for(key in a){
        if (max < a[key]){
            max = a[key]
            max_occurrence_key = key
        }
    }

    printf "max_occurrence_key is %s\n", key
}
