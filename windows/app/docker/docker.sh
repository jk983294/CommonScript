# image -> container
docker version
docker inspect name
docker run docker/whalesay cowsay hello-world!
docker ps   # list container
docker ps -a  # list container which stopped also
docker stop name
docker stop id
docker rm name  # won't show in docker ps -a

docker images  # list images
docker rmi name  # remove image
docker pull name  # download image

# hub.docker.com

# install
apt-get remove docker docker-engine docker.io containerd runc
curl -fsSL https://get.docker.com -o get-docker.sh
sh get-docker.sh

# uninstall Docker Engine
apt-get purge docker-ce docker-ce-cli containerd.io
rm -rf /var/lib/docker
