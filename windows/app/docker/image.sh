docker images                   # list images
docker images ubuntu            # 显示 ubuntu 相关 images
docker rmi ubuntu               # remove image
docker pull ubuntu              # download image
docker pull ubuntu:18.04        # 下载带tag的image

# docker Hub, hub.docker.com
# 用户仓库 (user repository), user_name/repo_name, like kun/zerg
# 顶层仓库 (top-level repository), repo_name, like ubuntu
docker search zerg              # 查找可用 image

########################### create image
# commit method
# 创建个 container, 作出点修改，然后commit 成新的 image
docker run -it ubuntu /bin/bash
apt update
apt install vim
vim ~/.vimrc
docker commit -m="ubuntu+vim" --author="kun" 31930c58ba09 kun/ubuntu_vim:20210303


# dockerfile method
# dockerfile 每条指令执行完，执行commit操作，基于新的image运行container，然后重复执行指令，直到完成
docker build Dockerfile -t zerg/myapp .                     # -t name
docker build Dockerfile -t zerg/myapp:v1 .                  # -t name
docker push zerg/myapp                                      # push to hub
docker run -ti id /bin/bash                                 # 构建过程中错了，可以进入构建最后正确的image，然后输入RUN 那条命令去排查
docker build --no-cache -t zerg/myapp .                     # 出错了，有时候不希望docker在缓存image上继续构建，需要重头构建
docker history zerg/myapp                                   # 查看 image build 步骤

# image name convention: registry/user/image, like nginx = docker.io/nginx/nginx

# private registry
docker login private_registry.io
docker run private_registry.io/apps/internal_app

# deploy private registry
docker run -d -p 5000:5000 --name registry registry2
docker image tag my_image localhost:5000/my_image
docker push localhost:5000/my_image
docker pull localhost:5000/my_image
