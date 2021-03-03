/usr/bin/docker -d -H tcp://0.0.0.0:2375    # daemon绑定到监听tcp 2375
/usr/bin/docker -H :2375                    # client发cmd给2375口的daemon
export DOCKER_HOST="tcp://0.0.0.0:2375"     # 使用环境变量, 不用每次加上-H :2375
vim /etc/default/docker                     # 修改daemon启动配置

journalctl -u docker.service                # 查看daemon log
systemctl status docker                     # 查看daemon status

# 开关daemon
systemctl start docker
systemctl stop docker

# general info
docker version
docker info             # check if daemon running