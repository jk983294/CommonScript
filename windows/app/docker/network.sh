# Bridge / none / host
docker run ubuntu                                       # internal network, 172.17.0.* 需要port map
docker run -d -p 80 ubuntu                              # docker 公开 80 端口给 host机
docker run -d -p 8080:80 ubuntu                         # docker 映射内部 80 端口到 host机 8080 端口
docker run -d -p eno1:8080:80 ubuntu                    # docker 映射内部 80 端口到 host机 eno1：8080 端口
docker run -d -p eno1::80 ubuntu                        # host机 随机指定绑定
docker run -d -P myapp                                  # 公开Dockerfile中EXPOSE指定所有端口
docker run ubuntu --network=none
docker run ubuntu --network=host                        # 自动用host port

# create user defined network
docker network create --driver bridge --subnet 182.18.0.0/16 custom_network

# show network info
docker netwok ls
docker inspect container_id
docker ps -l                                        # 可以看端口映射 docker从host选49153-65535中选一个来映射内部port
docker port id 80                                   # 查看 container 80 端口的 host 映射

# embedded DNS
app.connect(container_name)
