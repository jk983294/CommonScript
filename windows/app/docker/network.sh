# Bridge / none / host
docker run ubuntu    # internal network, 172.17.0.* 需要port map
docker run ubuntu --network=none
docker run ubuntu --network=host   # 自动用host port

# create user defined network
docker network create --driver bridge --subnet 182.18.0.0/16 custom_network

# show network info
docker netwok ls
docker inspect name

# embedded DNS
app.connect(container_name)
