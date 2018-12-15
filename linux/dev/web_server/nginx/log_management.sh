head /var/log/nginx/access.log


# log remote and target server
log_format main '$remote_addr - $remote_user [$time_local] "$request" '
                '$upstream_addr $status $body_bytes_sent "$http_referer" '
                '"$http_user_agent" "$http_x_forwarded_for"';
