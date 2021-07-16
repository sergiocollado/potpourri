NOTES ABOUT DOCKER


What are containers?

containers are isolated enviroments, with their own processes, or apps, their own network interfaces, mounts... . A bit like virtual machines, but their share
the OS kernel, with the system.

What is Docker?

why?
- containerize appliations
- run each service/app with its own dependencies in separate containers.

Docker is a set of products that virtualizes software in packages called containers. Containers are like VMs,
enviroments that are isolated from each other and have their own software, libraries and configurations. Containers are more lightweight than
VMs in that sense that they are running on a single OS kernel and therefore need fewer resources. Containers isolates
applications from each other more efficient compared to VMs. Even though VMs are keeping applications on the same hardware 
entirely separate from each other, they require their own OS and all the software, libraries and configurations that comes along
with that. This is bulky, hard to maintain/upgrade and typically requires storage of gigabytes. Containers shares the same underlying OS kernel
meanwhile VMs would need their own OS kernel. Containers are often measured in megabytes, use far less resources than VMs and start up very fast



Run Docker containers?

based in lxc linux containers. 

nowaday there are huge number of already containerized applications and available in a public docker repository like dockerhub or dockerstore. 

so to simply launch an aplication once installed docker, you can launch it with 

```
docker run ansible
```

an image is package or template to create containers
containers are running intantances of images.

https://docs.docker.com/get-started/


HOW TO INSTALL DOCKER IN A LINUX MACHINE

```
sudo apt-get update
sudo apt-get install docker.io
sudo docker --version
```

to get docker: https://docs.docker.com/get-docker/

choose your OS and versions. like linux/Ubuntu.


The easiest way is to install docker using the convenience script:
 https://docs.docker.com/engine/install/ubuntu/#install-using-the-convenience-script

once installed you can try to test it with a simple image, retrieve it from: https://hub.docker.com/

for example whalesay (like cowsay)


BASIC DOCKER COMMANDS

```
docker run <image>
```
example: 

```
docker --name myubuntu ubuntu:latest
```

runs an application. if the image is not present in the host, it will try to pull it down from dockerHub.

```
docker ps #list all running containers, and displays their basic information.
```

```
docker ps -all  #list all the containers running or not.
```

```
docker stop <container-name>    #stops the containers
```

```
docker rm <container-name>     #removes/deletes the contaniers, so it frees its memory.
```

```
docker images   #list the available images in the host.
```

```
docker rmi <image>    #removes an image
```

```
docker pull image  #pulls an image form dockerhub
```


To name a container:

```
docker run --name=<desired_name> <image>
```

if a OS is requested, you can use commands with it

```
docker run ubuntu <command like:sleep 42>
```

to automatically log in in a container with an os.

```
docker run -it ubuntu <command: bash>
``` 

or

```
 sudo docker run -it --name myubuntu1 ubuntu:latest
```
  
This will replicate the ubuntu terminal in our terminal.

To execute a command on a running container:

```
docker exec <container-name> <command>
```

to pass an enviroment variable
```
docker run -e MY_VARIABLE=value <image>
```

To launch a container in a detached mode use -d

```
docker run -d <image>
```

the container will run in the background process, and will be detached from the terminal. 
 
To reattach to that container, use:

```
docker attach <container>
```

or:
 
```
 docker run -d --name myapp nginx
 docker exec -it myapp bash #start a bash terminal
```
 

To map the local standard input to the input of the container, use the -i and t flag:
```
docker run -it <image>
```

- i is for interactive
- t is for terminal

Port mapping: To port mapping a container to it's docker engine

```
docker run -p 80:5000 <image>
```
this remaps the port 5000 of the container to the port 80 of the docker engine

Volume mapping: 

```
docker run -v /opt/<external_directory>:/var/<folder_inside_container> mysql
```
this way all the data will be saved in the external folder and can survive the container

container inspection:

```
docker inspect <container>
```

container logs:

```
docker logs <container>
```
 
 to commit a given image to docker hub
 
 ```
 docker commit myimage miDockerID/my_image_name
 ```
 
To log in the docker hub:
 
 ```
 docker login
 ```
 
 To upload a created image that has already been commited:
 
 ```
 docker push <image_name>
 ```
 

## DOCKER COMPOSE

to setup multiple services it is possible to do it with docker compose. But this works only within a given host. 

```
docker-compose up
```

## DOCKERFILE: 

Each Docker container starts with a Dockerfile. A Dockerfile is a text file written in an easy-to-understand syntax that includes the instructions to build a Docker image.

A Dockerfile specifies the operating system that will underlie the container, along with the languages, environmental variables, file locations, network ports, and other components it needs.

The dockerifle also specifies what the container will actually be doing once we run it. 

A very important field in every Dockerfile is the **entrypoint**. The entrypoint specifies which binary that will be executed when the container has started. 

- FROM : Download image
- WORDIR : workspace inside
- ENV: enviromental variables
- RUN: run a single command
- CMD: execute a command (can be used several times)
- COPY: copy from local docker
- EXPOSE: expose a listening port


## DOCKER IMAGE

The Dockerfile will instruct docker build on how to make a docker image. Whereas the Dockerfile is the set of instructions that tells docker build how to make the image,
a Docker image is a portable file containing the specifications for which software components the container will run and how.

An image usually contains the repository it is stored in, a tag and an image ID. Once an image is created, it’s static. So making any mistakes for example in fetching some software packages from online will require a rebuild. 


1- create a Dockerfile, and write down the instructions to setting up the application, like resolving dependincies, getting the source code, 
and defining the entry point of the application. 

Dockerfile is text file written in a given format that docker can understand, in an instruction argument format. 

2 - build the image with the 'docker build' command, specifiing the docker file as an input, as well as the tag name for the image, this will 
create a local image.

3 - 'docker push' command to make it available in dockerhub.


refs:

https://docs.docker.com/compose/

https://github.com/dockersamples/example-voting-app





https://github.com/ContainerSolutions/kubernetes-examples

https://github.com/kubernauts/practical-kubernetes-problems

https://kubernetesbyexample.com/

https://github.com/NodyHub/docker-k8s-resources/tree/master/k8s-pods















