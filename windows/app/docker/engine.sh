# docker cli -> rest api -> docker daemon
docker -H=10.123.2.1:2375 run nginx

# resource
docker run --cpus=.5 ubuntu
docker run --memory=100m ubuntu

# orchestration
docker service create --replicas=100 nodejs

# docker swarm
# manager -> worker

# kubernetes
kubectl run --replicas=100 my_web_server
kubectl scale --replicas=100 my_web_server
kubectl rolling-update my_web_server --image=web_server:2
kubectl rolling-update my_web_server --rollback
