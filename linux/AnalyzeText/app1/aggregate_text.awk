function sort_concat(str, delimiter){
    split(str, data, delimiter);
    n = asort(data);
    res = "";
    for (i = 1; i <= n; i++){
        if(data[i])
            res = res data[i] delimiter
    }
    return res;
}
/ERROR/{
    split($5, arr, ",");
    for(i in arr){
        if(! match(a[$2],arr[i])){
            a[$2] = a[$2] arr[i] ","
        }
    }
}
END{
    for(key in a){
        printf "%s = %s\n", key, sort_concat(a[key], ",")
    }
}
