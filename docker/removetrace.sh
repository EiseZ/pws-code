docker ps -aq | xargs docker rm
docker rmi pws:0.0.1
docker rmi pws:0.0.2
rm -r ./mounts/*
