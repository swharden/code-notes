# Docker Notes

* In a foldre with a `Dockerfile` run `docker build --tag imagename .`
* Show available images with `docker images`
* Show running images with `docker ps` (add `-a` to see closed ones)
* Kill a running image with `docker kill [partial hash]`
* Run a docker image `docker run -p 8080:80 imagename`
* Run a detached docker image `docker run -p 8080:80 --detach imagename`
