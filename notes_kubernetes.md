

Preface:

In a Virtual Machine, an hypervisor is the sw layer that detaches the dependencies of an operating system with its undelingin hardware and allows several virtual machines to share that same hardware. This is know as virtualization, 

Anyway for an application all its dependencies from the sw and os, are there. Also running several applications in a single VM, has another issue, applications that share dependencies are not isolated one of each other applications, and the resources of one application can estarve another application. 

One way to overcome these issues is to implement abstraction at the application level and its dependencies. So the trick is to virtualize the user space. That is what containers are, isolated user spaces, that run application code. Containers are much lighter than VM because they don't replicate the operating system. And can be created and destroyed very fast, because they only need to handle the processes needed for the application, and not all the OS kernel. 

Another advantage is that containers make very easy to build applications that use the microservices design pattern, that is loosely coupled, fine grained components and with modular design, this allows an easy scale, and upgrade of components of the applications without changing the application as a whole. 

An application and its dependencies, are called an image.  Sw its needed to build the images, for example: Docker. Docker is an open source project that allows you to run applications in containers. Although it doesn’t have a way to orchestrate those applications. 

Containers, actually depends on several linux technologies:

Processes : each process has its virtual espace address. Isolated from all the rest of the processes. 

Namespaces: containers handle the linux namespaces to control what an application can see: process id numbers, directories trees, ip addresses ….

Cgroups: containers use linux cgroups to control what an application can use. Its maximum consumption of cpu, memory, io throughput and resources ...

Union file systems: to encapsulate applications and its dependencies. 



Kubernetes is an application for deploying containerized applications.  Kubernetes is a solution for container management and orchestations. The apps in them need to communicate over the network. Also, needs to be some network mechanism that makes it possible for the containers to find each other. 

Kubernetes handles the deployment, scaling, load balancing, monitoring and logging of containerized applications. 

How do Kubernetes works?

Each thing Kubernetes manages is viewed as an object. And it’s attributes and states can be changed. Kubernetes works with declarative management, so the expected state of each object has to be defined. And kubernetes, will handle how to have that object in that declared state.

Kuberneters objects have two elements. An object spec, that defines the desired object state. And the object status is just the current state of each object, provided by the Kubernetes control plane.  The Kubernetes control plane are the different system processes that collaborate to make a cluster work. 

The basic object for the kubernetes model is known as a Pod. Those are the smallest deployable kubernetes objects. A pod is the environment, in which the containers live. And a Pod can have one or more containers. In case of more than one container, those will share resources. Each pod has an unique IP address. In case of several containers within a Pod, those will share the network namespace, including IP address and ports, and they can communicate through the local host. A Pod, can also define a set of storage  volumes to be shared among its containers. 

For working with kubernetes, we work through the kube-API server. This component will allow us to declare commands to view or change the state of the cluster. 

 - ubctl command - connect to kubeAPI server. 

 - ETCD is the cluster database and it stores the state of the cluster. 

 - Kube-scheduler. It schedules pods into the nodes. 

 - Kube-controller. It monitors the state of the cluster. When the current state of the cluster doesn’t match the desired state, it will try to get to the desired state. 

 - Kube-cloud manager manages controllers that interact with underlying cloud providers. 

 - Kubelete, is the agent of Kubernetes, in each node. 

 - Kube-proxy  handles network connectivity among the pods in the cluster.
 
 - Kuber ADM, that can automate much of the initial setup of a cluster.


All kubernetes objects are identified by an unique name and an unique id (uid). And the objects are defined in manifest files (in YAML or JSON format). And those files define a desired state for the object, like name and container image. 


  In a Kubernetes cluster, you don't need to only specify the state of Pods.  A better solution for high availability is to define controller objects that handle the state of the pods. Controllers maintain the pod’s desired state within a cluster. Like deployments (deployment ensures that a defined set of pods is running at any given time) , stateful sets, daemon sets or jobs. 

Kubernetes services, is an abstraction that represents a service in kubernetes with a static ip address. So services provide an end-point with a non-ephemeral IP for pods giving a certain service. These kubernetes services can be only internal for the cluster, or external in a front-end way.

Kubernetes volume  - is an abstraction that represents a directory that is accessible to all the containers in a pod. One advantage is that you can configure kubernetes volumes to use network based storage from outside the pods, so you can manage to have a persistent volume storage. 

Several Kubernetes controller objects:

- ReplicaSets
- Deployments
- Replication Controllers
- StatefulSets
- DaemonSets
- Jobs

A ReplicaSet controller ensures that a population of Pods, all identical, are running at the same time. Deployments let you do declarative updates to ReplicaSets and Pods. In fact, Deployments manage their own ReplicaSets to achieve the declarative goals you prescribe, so you will most commonly work with Deployment objects.
Deployments let you create, update, roll back, and scale Pods, using ReplicaSets as needed to do so. For example, when you perform a rolling upgrade of a Deployment, the Deployment object creates a second ReplicaSet, and then increases the number of Pods in the new ReplicaSet as it decreases the number of Pods in its original ReplicaSet.
Replication Controllers perform a similar role to the combination of ReplicaSets and Deployments, but their use is no longer recommended. Because Deployments provide a helpful "front end" to ReplicaSets.
In the need to deploy applications that maintain local state, StatefulSet is a better option. A StatefulSet is similar to a Deployment in that the Pods use the same container spec. The Pods created through Deployment are not given persistent identities, however; by contrast, Pods created using StatefulSet have unique persistent identities with stable network identity and persistent disk storage. So for persistent storage, the StatefulSet is the best option, defining a network storage. 
If you need to run certain Pods on all the nodes within the cluster or on a selection of nodes, use DaemonSet. DaemonSet ensures that a specific Pod is always running on all or some subset of the nodes. If new nodes are added, DaemonSet will automatically set up Pods in those nodes with the required specification. The word "daemon" is a computer science term meaning a non-interactive process that provides useful services to other processes in the background. A Kubernetes cluster might use a DaemonSet to ensure that a logging agent like fluentd is running on all nodes in the cluster. DeamonSets are useful, if you want to have logging and auditing processes in all the nodes of your cluster. 
The Job controller creates one or more Pods required to run a task. When the task is completed, Job will then terminate all those Pods. A related controller is CronJob, which runs Pods on a time-based schedule.

https://kubernetes.io/

https://minikube.sigs.k8s.io/docs/start/

minikube is local Kubernetes, focusing on making it easy to learn and develop for Kubernetes.

https://cloud.google.com/kubernetes-engine/docs/tutorials/hello-app

https://cloud.google.com/code/docs/vscode/yaml-editing
