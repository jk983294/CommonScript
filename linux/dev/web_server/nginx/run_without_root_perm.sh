nginx -c /home/kjiang/nginx.conf
nginx -c /home/kjiang/nginx.conf -s stop
$ tree
    .
    |-client_body
    |-fastcgi_temp
    |-proxy_temp
    |-scgi_temp
    |-uwsgi_temp

below also need to be changed:
    error_log (in the main scope as well as lower scopes)
    access_log
    pid
