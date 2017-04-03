/ERROR/{
    a[$2]++
}
END{
    for(key in a){
        printf "%s show %d times\n", key, a[key]
    }
}
