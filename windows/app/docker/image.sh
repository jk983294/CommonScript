# create image
docker build Dockerfile -t zerg/myapp
docker push zerg/myapp      # push to hub

docker history image-name

# image name convention: registry/user/image, like nginx = docker.io/nginx/nginx

# private registry
docker login private_registry.io
docker run private_registry.io/apps/internal_app

# deploy private registry
docker run -d -p 5000:5000 --name registry registry2
docker image tag my_image localhost:5000/my_image
docker push localhost:5000/my_image
docker pull localhost:5000/my_image
