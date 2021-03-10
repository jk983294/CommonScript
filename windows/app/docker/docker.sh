# run image
man docker-run                                          # 查 docker run 参数
docker run -it ubuntu /bin/bash                         # -i STDIN -t tty 交互式
docker run -it -w /var/log ubuntu /bin/bash             # -w 设置工作路径
docker run -it -e "WEB_PORT=8080" ubuntu /bin/bash      # -e 设置环境变量
docker run -it -u kun ubuntu /bin/bash                  # -u 设置启动用户，默认为root
docker run -it -v /opt/version/latest/:/opt/version/latest/ ubuntu /bin/bash           # -v 挂载宿主机目录到容器中
docker run -it -v /home/kun/myapp:/opt/myapp:ro ubuntu /bin/bash        # -v 挂载volume read only
docker run --name kun_bash -it ubuntu /bin/bash         # 给 container 启动 name
docker run --name kun_daemon_app -d ubuntu /bin/bash -c "while true; do echo hello world; sleep 1; done"    # daemon 启动
docker run --restart=always --name kun_daemon_app -d ubuntu /bin/bash -c "while true; do echo hello world; sleep 1; done"
docker run --restart=on-failure --name kun_daemon_app -d ubuntu /bin/bash -c "while true; do echo hello world; sleep 1; done" # 上一次退出码非0才重启

# container
ls /var/lib/docker/containers/                          # 物理存放 container 地方
docker ps                                               # list container
docker ps -a                                            # 显示所有 container, 包括 stopped 的
docker ps -n 5                                          # 显示last 5 containers, 包括 stopped 的
docker inspect kun_daemon_app                           # 查看配置信息，网络配置等
docker inspect --format='{{.State.Running }}' kun_daemon_app    # 查指定内容
docker inspect -f='{{.NetworkSettings.IPAddress }}' kun_daemon_app
docker restart kun_bash                                 # 重启
docker start kun_bash                                   # 开
docker stop kun_bash                                    # 关, SIGTERM signal
docker kill kun_bash                                    # 关, SIGKILL signal, faster than stop
docker attach kun_bash                                  # attach to session
docker rm kun_bash                                      # won't show in docker ps -a
docker rm `docker ps -a -q`                             # 删除所有 container

# 提交新任务给 container
docker exec -d kun_daemon_app touch /etc/new_config_file    # daemon task
docker exec -it kun_daemon_app /bin/bash                    # 新 bash

# check container status
docker logs kun_daemon_app                              # 查看 container log
docker logs -f kun_daemon_app                           # like tail -f
docker logs --tail 1 -f kun_daemon_app                  # 控制读取最后n条log再follow
docker logs -tf kun_daemon_app                          # -t 显示时间
docker top kun_daemon_app                               # 查看容器内进程

# install
apt-get remove docker docker-engine docker.io containerd runc
curl -fsSL https://get.docker.com -o get-docker.sh
sh get-docker.sh

# uninstall Docker Engine
apt-get purge docker-ce docker-ce-cli containerd.io
rm -rf /var/lib/docker
