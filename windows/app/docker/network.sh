# Bridge / none / host
docker run ubuntu                                       # internal network, 172.17.0.* 需要port map
docker run -d -p 80 ubuntu                              # docker 公开 80 端口给 host机
docker run -d -p 8080:80 ubuntu                         # docker 映射内部 80 端口到 host机 8080 端口
docker run -d -p eno1:8080:80 ubuntu                    # docker 映射内部 80 端口到 host机 eno1：8080 端口
docker run -d -p eno1::80 ubuntu                        # host机 随机指定绑定
docker run -d -P myapp                                  # 公开Dockerfile中EXPOSE指定所有端口
docker run ubuntu --network=none
docker run ubuntu --network=host                        # 自动用host port

# docker internal network
# 每个 container 都会在docker0上分配一个地址
# 宿主机看到的docker0一般是172网段，container内部看到的是eth0
# container可以使用内部网络ip来相互访问
# 缺点是容器重启，内部地址就变了，不能hardcode
ip a show docker0

# 启动时按名字连接 --link container_name:alias_in_current_container
# 别名查 cat /etc/hosts
# 通过别名提供的env来访问, 如 DB_PORT
# link的容器必须存在在同一宿主机
docker run -d --name redis zerg/redis
docker run -it --link redis:db ubuntu /bin/bash

# create user defined network
docker network create --driver bridge --subnet 182.18.0.0/16 custom_network

# show network info
docker netwok ls
docker inspect container_id
docker ps -l                                        # 可以看端口映射 docker从host选49153-65535中选一个来映射内部port
docker port id 80                                   # 查看 container 80 端口的 host 映射

# embedded DNS
app.connect(container_name)
