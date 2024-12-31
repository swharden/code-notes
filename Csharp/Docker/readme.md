# Docker Notes

* Build a Docker image in a folder with a `Dockerfile` using `docker build --tag 'imagename' .`
* Show available images with `docker images`
* Show running images with `docker ps` (add `-a` to see closed ones)
* Kill a running image with `docker kill [partial hash]`
* Run a docker image `docker run imagename -p 8080:8080`
* Run a detached docker image `docker run -p 8080:8080 --detach imagename`
