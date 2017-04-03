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
        printf "%s = %s\n", key, a[key]
    }
}
