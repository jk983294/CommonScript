FROM ubuntu
MAINTAINER kun

USER kun                    # user:group/uid/uid:gid 容器以该身份启动, 默认以root
VOLUME ["opt/myapp"]        # 挂载点，volume可以被容器之间共享和重用

# 环境变量会作用于后面的run指令
ENV REFRESHED_AT 20210303   # 修改该处环境变量，则下面的构建会重新刷新

RUN apt-get update
RUN apt-get install python

RUN pip install flask
RUN pip install flask-mysql

COPY . /opt/source-code                 # 和ADD类似，但是不会解压缩，源路径必须在Dockerfile相同路径下
ADD software.lic /opt/app/software.lic  # 当前环境下文件复制到镜像
#ADD a.tar.gz /var/somewhere/           # 解压缩到路径 /var/somewhere/

#ONBUILD RUN cd /app/src && make        # 当image被用作其他image的基础镜像时触发

EXPOSE 80
#WORKDIR /opt/myapp/                # 为 entrypoint/cmd 指定工作路径
ENTRYPOINT FLASK_APP=/opt/source-code/app.py flask run

#CMD ["echo", "hello"]              # 容器启动时运行的命令
