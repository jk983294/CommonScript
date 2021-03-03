FROM Ubuntu
MAINTAINER kun

ENV REFRESHED_AT 20210303   # 修改该处环境变量，则下面的构建会重新刷新

RUN apt-get update
RUN apt-get install python

RUN pip install flask
RUN pip install flask-mysql

COPY . /opt/source-code

EXPOSE 80
ENTRYPOINT FLASK_APP=/opt/source-code/app.py flask run

#CMD ["echo", "hello"]           # 容器启动时运行的命令
