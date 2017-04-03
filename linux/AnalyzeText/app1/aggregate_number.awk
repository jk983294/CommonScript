/ERROR/{
    a[$2] = a[$2] + $6
}
END{
    for(key in a){
        printf "%s = %d\n", key, a[key]
    }
}
