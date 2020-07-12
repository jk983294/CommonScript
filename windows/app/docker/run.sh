docker run ubuntu sleep 100         # launch container
docker exec name cat /etc/hosts     # run cmd on container

docker run -d ubuntu sleep 100      # detach mode, background
docker attach id                    # background to foreground

docker run -it name                 # run interactive mode, show prompt, now stdin works

# port map
docker run -p 80:5000 mywebapp     # map host port 80 to container port 5000
docker run -p 3306:3306 mysql

# volume map
docker run -v /dat/mysql:/var/lib/mysql mysql

# env
docker run -e APP_COLOR=blue mywebapp
docker inspect name   # check env

docker run redis:4.0                # run with image tag
