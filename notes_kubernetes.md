
# Preface

In a Virtual Machine, an hypervisor is the sw layer that detaches the dependencies of an operating system with its undelingin hardware and allows several virtual machines to share that same hardware. This is know as virtualization, 

Anyway for an application all its dependencies from the sw and os, are there. Also running several applications in a single VM, has another issue, applications that share dependencies are not isolated one of each other applications, and the resources of one application can estarve another application. 

One way to overcome these issues is to implement abstraction at the application level and its dependencies. So the trick is to virtualize the user space. That is what containers are, isolated user spaces, that run application code. Containers are much lighter than VM because they don't replicate the operating system. And can be created and destroyed very fast, because they only need to handle the processes needed for the application, and not all the OS kernel. 

Another advantage is that containers make very easy to build applications that use the microservices design pattern, that are loosely coupled, fine grained components and with modular design, this allows an easy scale, and upgrade of components of the applications without changing the application as a whole. 

An application and its dependencies, are called an image.  Software is needed to build the images, for example: Docker. **Docker** is an open source project that allows you to run applications in containers. Although it doesn’t have a way to orchestrate those applications. 

**Kubernetes** is an application for deploying containerized applications.  Kubernetes is a solution for container management and orchestations. The apps in them need to communicate over the network. Also, needs to be some network mechanism that makes it possible for the containers to find each other. 

see: Kubernetes Concepts Explained  https://youtu.be/BOj1sgWVXko?list=RDCMUCeRY0LppLWdxWAymRANTb0g

Kubernetes handles the deployment, scaling, load balancing, monitoring and logging of containerized applications. 

Some of its features are:

 - Automatically schedules containers based on resources
 - Self-healing. Replaces and reschedules containers from failed nodes.
 - Horizontal scaling: - scales automatically or manually.
 - Service discovery
 - Load balancing 
 - Automated rollbacks and rollaouts
 - Configuration managements
 - Storage orchestration
 - Batch execution.
 
 refence: https://blog.risingstack.com/the-history-of-kubernetes/
 
 reference: https://cloud.google.com/blog/products/gcp/bringing-pokemon-go-to-life-on-google-cloud

# How do Kubernetes works?

Each thing Kubernetes manages is viewed as an object. And it’s attributes and states can be changed. Kubernetes works with declarative management, so the expected state of each object has to be defined. And kubernetes, will handle how to have that object in that declared state.

Kuberneters objects have two elements. An object spec, that defines the desired object state. And the object status is just the current state of each object, provided by the Kubernetes control plane.  The Kubernetes control plane are the different system processes that collaborate to make a cluster work. 

The basic object for the kubernetes model is known as a **Pod**. Those are the smallest deployable kubernetes objects. A pod is the environment, in which the containers live. 

A Pod, is a group of containers that share storage and networking (all the containers share memory volumes and share the same IP).

And a Pod can have one or more application containers (like docker or others). In case of more than one container, those will share resources. Each pod has an unique IP address. In case of several containers within a Pod, those will share the network namespace, including IP address and ports, and they can communicate through the local host. A Pod can also define a set of storage  volumes to be shared among its containers. 

Kubernetes inner workings are based in several components witch are described next:

reference: https://kubernetes.io/docs/concepts/workloads/pods/

For working with kubernetes, we work through the kube-API server. This component will allow us to declare commands to view or change the state of the cluster. 

**kubectl command** - connect to kubeAPI server. Is the kuberntetes Command Line interface client. To manage the cluster and its applications. 

**ETCD** is the cluster database and it stores the state of the cluster. 

**Kube-scheduler** - It schedules pods into the nodes. 

**Kube-controller** - It monitors the state of the cluster. When the current state of the cluster doesn’t match the desired state, it will try to get to the desired state. 

**Kube-cloud** - manager manages controllers that interact with underlying cloud providers. 

**Kubelet** - is the agent of Kubernetes, in each node. It is responisble for receiving instrucctions from the kubernetes api master server and running pods on the nodes. https://kubernetes.io/docs/reference/command-line-tools-reference/kubelet/

**Kube-proxy** - handles network connectivity among the pods and services in the cluster. it monitors new services, and when a new service is create it creates new rules in each node, to fordward traffic to those services (for example defining ip-tables rules).

**KuberAdm** - Automates part of the initial setup of a cluster.

reference: https://kubernetes.io/docs/concepts/overview/components/

All kubernetes objects are identified by an unique name and an unique id (uid). And the objects are defined in manifest files (in YAML or JSON format). And those files define a desired state for the object, like name and container image. 

more: https://www.youtube.com/watch?v=90kZRyPcRZw&t=462s

### ETCD 
 ETCD is a reliable, distributed, key-value based store. 
 
 reference: https://etcd.io/docs/
 
 reference: https://kubernetes.io/docs/tasks/administer-cluster/configure-upgrade-etcd/
 
 the ETCD dababase keeps information with regard to: nodes, pods, configs, secrets, accounts, bindings, roles and more. 
 
## kubectl command

**kubectl** is the kubernets command line tool.

https://kubernetes.io/docs/reference/kubectl/cheatsheet/  <- REALLY HAVE A LOOT AT THIS!

It is the command used to communicate with the kubernetes cluster, with the kube-API server, so the kubectl commands are transformed in APIs calls.

Before anything the kubectl must be configured with the location and credentials of a given kubernetes cluster.  The configuration is  in a file in the home directory $HOME/.kube/config. The config file has the cluster name and the cluster credentials.  To edit this use the command: --kubeconfig

If you want to view the configuration, just use the command:  'kubectl config view'.

Or to get the cluster info,and the services running in it,  use the command: 'kubectl cluster-info'

Sintaxis

``` kubectl [command] [type] [name] [flags] ```

 - **Commands**: get, describe, logs, exec …
 - **Type**: pods, deployments, nodes …


For example:

``` kubectl get pods -- get a list and info about the pods. ```

```kubectl describe pod <pod_name> -- get detailed info about a given pod. ```

**NOTE**: 

 it is recomended to apply the alias:
 
 ```
 alias k=kubectl
 ```
 
 and also set the autocompletion:
 
 ```
 source < (kubectl completion bash)
 ```
 
 or also: 
 
```
alias k=kubectl                         # will already be pre-configured

export do="--dry-run=client -o yaml"    # k get pod x $do 

export now="--force --grace-period 0"   # k delete pod x $now
 ```
 
 and to make vim use 2 spaces for a tab edit ~/.vimrc to contain:

```
set tabstop=2
set expandtab
set shiftwidth=2
```

 
## Kubernetes object model

In Kubernetes objects, represent different persistent entities, that represent the containerized apps that are running and in which node.

Resources consumption
Policies reated to the applications, like restart/upgrade, fault tolerances, …
For each object, we declare the intent in the _**spec**_ section. Tye _**spec**_ section describes the desired object state. kubernetes manages the _**status**_ section for the objects, where it records the actual state of the objects. At any given point in time, kubernetes tries to match the object current state to the desired state. 

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
 
## shortcuts names

 - po for Pods
 - rs for ReplicaSets
 - deploy for Deployments
 - svc for Services
 - ns for namespaces
 - netpol for network policies
 - pv for PersistentVolumes
 - pvc for PersistentVolumeClaims
 - sa for Service accounts
 - cm for ConfigMaps
 - ds for deamonSet
 - csr certificatesigningrequests
 
## Pods

A Pod, is the minimun unit of work in Kuberntetes. It is a group of containers that share storage and networking (all the containers share memory volumes and share the same IP).

And a Pod can have one or more application containers (like docker or others). In case of more than one container, those will share resources. Each pod has an unique IP address. In case of several containers within a Pod, those will share the network namespace, including IP address and ports, and they can communicate through the local host. A Pod can also define a set of storage  volumes to be shared among its containers. 

reference: https://kubernetes.io/docs/concepts/workloads/pods/

A pod can have different status, the status is the point it its lifecicle. 

- pending: the scheduler is looking in which node put the pod.
- ContainerCreating: the applications for the pod are retrieved and the application starts. 
- running: the application in the pod is runnning.

Pod conditions tell us more about a pod status. 

- Podscheduled
- Initialized
- ContainersReady
- Ready

### Example of a Pod configuration file

```
apiVersion: v1
kind: Pod
metadata:
  name: nginx-pod
  labels:
    app: nginx
spec:
  containers:
  - name: nginx
    image: nginx:1.15.12
    ports:
    - containerPort: 80
```

the field **apiVersion** just points to the api version we want to connect to.

the field **kind** specifies the type of object.

The field **metadata** defines basic object information like name and labels.

#### Static Pods

  The kubelet can be configured to read pod's definitions files from given directory. The kubelet will read that directory and handle the creation of those pods, and also keep them alive (restart the pods) in case they crash. The pods defined in this way, are kwnown as **static-pods**. 
  
  The static-pods are managed by the node's kubelet, son even in case the control-plane fails, or the api-server is not working, those pods are still being managed for the node's kubelet.
  
  reference: https://kubernetes.io/docs/tasks/configure-pod-container/static-pod/

### Labels

Labels are pairs of key and value identifiers. Labels are used to identify and select objects. So Labels do not provide uniqueness. Controllers use labels to group togethers in a set decoupled objects, instead fo idetifing them by names.

### Label Selectors

There are two types of label selectors: equality-based ( = , ==, != ) and set-based selectors ( in, notin, exists, does not exist).

Labels and selectors, is a method to define sets of pods. 
 
### Namespaces

A cluster resources can be divided using **namespaces**. The name of resources created inside a given namespace is unique, but no across namespaces. 

k8s generates four default namespaces: kube-system, kube-public, kube-node-lease and default. 

- default: contains objects created by admins and developers.
- kube-system: contains objects created by k8s system, mostly the control plane agents. Here there are containers for the inner workings of k8s, like the networking solutions... 
- kube-public: Here, resoureces that should be available to all users are located. This is a special namespace which is unsecured and readable, used to expose information publically. 
- kube-node-lease: contains the node lease objects, for node heartbeat data.  

It is possible to create custom namespaces, for example one named 'dev" for development, and other 'prod' for production pourpouses.

Also in namespaces is possible to define their own resource limits, so each namespace can have different quotas. 

### Replication Controller

 A replication controller allows to have several instances of a pod, so in case a pod dies, a new one can replace it. Thus allowing to have a high availability service.
 
 A replication controller can help also, when we want to have several pods, sharing work between them. 
 
 A replication controller will monitor the specified pods, and in case any would fail, it would replace it by a new one. 
 
 
### ReplicaSet Controllers

A replica set controller is the replication controller evolution. 

A ReplicaSet controller ensures that a population of Pods, all identical, are running at the same time.

A ReplicaSet can be used to monitor a group of Pods, that are already running, and in case those are not created, the replicaset can create them. the role of the replicaset is to monitor the pods, and if any were to fail, replace them by new ones. The way to identity the pods to monitor is by means of matching labels (with the matchLabel filter), defined in the definition of the Replica set.

Replication Controllers perform a similar role to the combination of ReplicaSets and Deployments, but their use is no longer recommended. Because Deployments provide a helpful "front end" to ReplicaSets.

### Deployment Controllers

Deployments let you do declarative updates to ReplicaSets and Pods. In fact, Deployments manage their own ReplicaSets to achieve the declarative goals you prescribe, so you will most commonly work with Deployment objects.

Deployments let you create, update, roll back, and scale Pods, using ReplicaSets as needed to do so. For example, when you perform a rolling upgrade of a Deployment, the Deployment object creates a second ReplicaSet, and then increases the number of Pods in the new ReplicaSet as it decreases the number of Pods in its original ReplicaSet.  Deployments are better suited to state-less applications like web front-end.

reference: https://kubernetes.io/docs/concepts/workloads/controllers/deployment/

Replication Controllers perform a similar role to the combination of ReplicaSets and Deployments, but their use is no longer recommended. Because Deployments provide a helpful "front end" to ReplicaSets. In the need to deploy applications that maintain local state, StatefulSet is a better option. 
 
### StatefulSet

A StatefulSet is similar to a Deployment in that the Pods use the same container spec. The Pods created through Deployment are not given persistent identities, however; by contrast, Pods created using StatefulSet have unique persistent identities with stable network identity and persistent disk storage. So for persistent storage, the StatefulSet is the best option, defining a network storage. In A StatetufSet, the ordern in which the pods are created is also defined, this doesn't happen in a Deployment.

StatefulSet is better use when the instances are needed to come up in a given order, and/or the instances need a stable name or network address. Watch out when defining a StatefulSet, because you have to define a Service name (headless Service)

A headless service is a Service that doesnt do load balancing, but uses a DNS request for each pod. 
https://kubernetes.io/docs/concepts/services-networking/service/#headless-services

https://kubernetes.io/docs/concepts/workloads/controllers/statefulset/
https://kubernetes.io/docs/tutorials/stateful-application/basic-stateful-set/

### DaemonSet
If you need to run certain Pods on all the nodes within the cluster or on a selection of nodes, use DaemonSet. DaemonSet ensures that a specific Pod is always running on all or some subset of the nodes. If new nodes are added, DaemonSet will automatically set up Pods in those nodes with the required specification. The word "daemon" is a computer science term meaning a non-interactive process that provides useful services to other processes in the background.

A Kubernetes cluster might use a DaemonSet to ensure that a logging agent (like fluentd) is running on all nodes in the cluster. DeamonSets are useful, if you want to have logging and auditing processes in all the nodes of your cluster, or if you want to have hardware monitoring services.

### Job controller
The Job controller creates one or more Pods required to run a task. When the task is completed, Job will then terminate all those Pods. A related controller is CronJob, which runs Pods on a time-based schedule. Jobs run a task up to its completion, rather than a desired state. 

### Example of a Deployment's configuration file

This is an example of a deployment's configuration in yaml format.

```
apiVersion: apps/v1
kind: Deployment
metadata: 
  name: nginx-deploy
  labels:
    app: nginx
spec:
 replicas: 3
 selector: 
   matchLabels:
     app: nginx
   spec:
     containers:
     - name: nginx
       image: nginx: 1.15.13
       ports: 
       - containerPort: 80
```

the field **apiVersion** just points to the api version we want to connect to.

the field **kind** specifies the type of object.

The field **metadata** defines basic object information like name and labels.

the spec.template field defines the pod's templates we want.

Once the object is deployed, the system will add the field **status** to this file.

### Configuration Maps

ConfigMaps are objects that keep configuration definitions of **enviromental variables** to be used in a Pod.

the data in the config map, is simply given as a list of key-value pairs.

```
DB_HOST: redis
DB_USER: root
```
reference: https://kubernetes.io/docs/concepts/configuration/configmap/

reference: https://kubernetes.io/docs/tasks/configure-pod-container/configure-pod-configmap/

### Secrets

Secrets objects used to store sensitive information, like passwords, keys or personal data... and are stored in a hashed format (although not encripted!)

ref: https://kubernetes.io/docs/tasks/inject-data-application/distribute-credentials-secure/

### Security contexts

Some secure settings can be define at the container run engine level or at the pod level. If configured at the pod level, those settings will be defined for all the containers within the pod. If defined in both places, the container and the pod, the pod settings will override the container settings.

### Service Accounts

There are two types of accounts in kubernetes, user accounts and service accounts. Service accounts are for **service programs**, like prometheus or jenkins. 

To create a service account

```
kubectl create serviceaccount my-service-account
```

to get the service accounts

```
kubectl get serviceaccount
```
When a service account is created, it creates on token that would be used by a application to access. This token is stored as a secret object. This secret is linked to the service account. 

```
kubectl describe serviceaccount my-service-account
```

**NOTE**: For every namespace create a service account a service account named "default" is automatically created. And when a new pod is created the default service account, and its token are automatically mounted into that pod as a volume mount. 

To list the service accounts:

```
kubectl list serviceaccount
```

### Taints ant tolerations

Tains and tolerations are means to **restrict** Pods to run in certain Nodes. A node may define a given taint, and only pods that define toleartion to that taint can run in that node. 

ref: https://thenewstack.io/strategies-for-kubernetes-pod-placement-and-scheduling/

### Node Selector

You can add a label to a node, and define a label in the pods, you want to run into that node.

To label a certain node:

```
kubectl label nodes <node-name> <label-key>=<label-value>
```
and in the pod definition:

```
apiVersion: apps/v1
kind: Deployment
metadata: 
  name: nginx-deploy
spec:
  containers:
   - name: nginx
     image: nginx: 1.15.13
     
  nodeSelector:
     <label-key>: <label-value>
```

### Node Affinity

reference:  https://kubernetes.io/docs/tasks/configure-pod-container/assign-pods-nodes-using-node-affinity/

Node affinity allow us more complex capabilities to set a Pod placement in the nodes. 

```
apiVersion: apps/v1
kind: Deployment
metadata: 
  name: nginx-deploy
spec:
  containers:
   - name: nginx
     image: nginx: 1.15.13
  affinity:
      nodeAffinity:
          requiredDuringSchedulingIgnoreDuringExecution:
              nodeSelectorTerms:
              - matchExpressions:
                - key: <label-key>
                  operator: In  #or: NotIn, Exists ...
                  values:
                  - <label-value-1>
                  - <label-value-2>
```

other reference: https://thenewstack.io/strategies-for-kubernetes-pod-placement-and-scheduling/

### links:

https://kubernetes.io/

https://minikube.sigs.k8s.io/docs/start/

minikube is local Kubernetes, focusing on making it easy to learn and develop for Kubernetes.

https://cloud.google.com/kubernetes-engine/docs/tutorials/hello-app

https://cloud.google.com/code/docs/vscode/yaml-editing

https://cloud.google.com/sdk/gcloud

https://helm.sh/docs/intro/

https://istio.io/  - Connect, secure, control, and observe services.

https://cloud.google.com/kubernetes-engine/

https://github.com/dysinger/learn-minikube

## Kubernetes network model

The kubernetes network model, sets:

- every pod gets its own IP address
- containers within a pod share the same IP address and can communicate freely between them
- Pods can communicate with all the other pods in the cluster using the pod's IP addresses (without NAT) 
- Pods isolation, or restriction between pod's communication is defined by using network policies. 

Kubernetes has a simple basic network connectivity implementation, so it is common to use thrid party implementations (Calico, Cilium, Weave net, flannel ...) 
that follow the CNI (container network interface)  [ https://betterprogramming.pub/about-kubernetes-cni-plugins-f0bcd60b5629 ]

“CNI (Container Network Interface), a Cloud Native Computing Foundation project, consists of a specification and libraries for writing plugins to configure network interfaces in Linux containers, along with a number of supported plugins. CNI concerns itself only with network connectivity of containers and removing allocated resources when the container is deleted.”

the main types of CNI plugins are:

- network plugins, are responsible to connect the pod to the network 
- IPAM (IP Address Manager) which are resoponsible for allocatin pod IP addresses. 


## Services

Services are the process that expose a set of pods to the outside of the cluster. 

Rationale: The pods in a cluster have IPs that are ephemeral, if a pod is terminated and a new pod is created, this new pod doesn't really need to have the same IP.
To overcome this situation, the Service abstraction is provided. Given a set of pods, defined by labes or selectors, those can be addresses by means of a Service. 

reference: https://kubernetes.io/docs/concepts/services-networking/service/

There are different types of services available:

- **NodePort**: The service makes an internal pod accesible on a given port of the node.
- **ClusterIP**: The service creates a virtual IP inside the cluster to enable communications between different services. For example from between front-end and backe end servers.
- **LoadBalancer**: The service provideas a load balancer, in supported cloud provides (google, aws, azure...)


### kube-proxy

kube-proxy is a daemon in all the worker nodes, that monitorices the master node server api, to check for the addition or removal of services. Each kube-proxy, handles the ip-tables, to manage the traffic for each ClusterIP and fordward it to the suitable Service endpoint. 

### Service discovery

There are two ways to discover a service:

- enviromental variables: when a Pod starts the kubelet daemon running in that node defines a set of enviromental variables that defines the active services. Be careful with this method, due if a Service is created after the Pod, this service will not be identifed.

- DNS: kubernetes has an add-on for DNS, which creates a DNS record for each service. This is the recomended solution.

reference: https://kubernetes.io/docs/concepts/services-networking/service/#discovering-services

### Services types:

reference: https://kubernetes.io/docs/concepts/services-networking/service/#publishing-services-service-types

**NodePort**: A service can map a port in the node, to a port of the pod. The port in the pod, is the **TargetPort**, the port from the service that points to the target port, is the **Port**. Inside the Service, it has its own address, known as the ClusterIP of the service. And then we have the external port of the node, that is used to access from outside the node, and that is known as the **NodePort** (these nodeports, are defined by default in the range: 30000-32767).

```
#service-definition.yml
apiVersion: v1
kind: Service
metadata:
    name: my-service
spec:
    type: NodePort
    ports: 
       - targetPort: 80
         port: 80
         nodePort: 30007
    selector:
       app: my-app
       key: my_key_value
```

summing up there are 3 ports involved

- **target port** the port in the pod, to which the communication is targeted.
- the port in the service itself, refered simply as the: **port**. From it the communication is directed to the target port.
- the port in the node, which is used to access externally, it is the **NodePort**

```
 outside -> [NodePort] ->(Service) -> [Port] -> [Target Port] (Node)
```

to create the service:

```
kubectl create -f service-definition.yml
```

to list the services:

```
kubectl get services
```

**ClusterIP**:

```
#service-definition.yml
apiVersion: v1
kind: Service
metadata:
    name: my-service
spec:
    type: ClusterIP
    ports: 
       - targetPort: 80 #the port where the application is exposed
         port: 80 #the port where the service is exposed.
    selector:
       app: my-app
       key: my_key_value
```

### Example of a Service configuration file:

```
apiVersion: v1
kind: Service
metadata: 
  name: front-end-svc
spec:
  selector: 
    app: frontend
  ports:
  - protocol: TCP
    port: 80
    targetPort: 5000
```

## Ingress

Ingress allows users access the application using a single external url, that can be configured to run throught different services of the cluster. Althought the ingress must still be published as a service.

An Ingress has two main components

 - ingress controller
 - ingress resources

To define an ingress you have to define a **ingress controller**, like:

https://www.nginx.com/

http://www.haproxy.org/

https://doc.traefik.io/traefik/

https://projectcontour.io/

https://istio.io/

An ingress controller must be deployed. For example, an nginx, and it can be deployed, just as any other deployment.

Also, in addition to the ingress controller, we have to define a set of rules, related as **ingress resources**.

An ingress resource, will define rules, like routing all the traffic to a single application, or direct the traffic to different applications based on the url or the domain name. 


## Cluster Networking needed Ports

Some networking configurations must be met.

Each node (master/s and workers) must have a **unique** host name. Beware, if there is a deployment based on cloning! 

Certain ports must be also open:

- Master, must accept connections in 6443 for kube-API
- kubelet is on port 10250
- kube-scheduler needs port 10251 open.
- kube-controller-manager needs port 10252 open
- the working nodes, expose services in the ports in the range: 30000-32767
- ETCD server in on port 2379
- ETCD clients in on port 2380

reference: https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/install-kubeadm/#check-required-ports

## Network policies

By default all pods have access to the rest of the pods, but this can be restricted with the use of network policies (for security reasons maybe ...)

https://kubernetes.io/docs/concepts/services-networking/network-policies/

https://kubernetes.io/docs/tasks/administer-cluster/declare-network-policy/

**Make sure you've configured a network provider with network policy support. There are a number of network providers that support NetworkPolicy**, including:

- Calico - https://docs.projectcalico.org/getting-started/kubernetes/
- Cilium - https://docs.cilium.io/en/stable/intro/
- Kube-router - https://github.com/cloudnativelabs/kube-router
- Romana - https://github.com/romana/romana/wiki/Romana-policies
- Weave Net - https://www.weave.works/docs/net/latest/kubernetes/kube-addon/#npc


```
apiVersion: networking.k8s.io/v1
kind: NetworkPolicy
metadata: 
   name: db-policy
spec:
   podSelector:
      matchLabels:
         role: DataBase
   policyTypes:
   - Ingress
   ingress:
   - from: 
     - podSelector:
       matchLabels:
          name: api-pod
   ports:
   - protocol: TCP
     port: 3309
```

Solutions that support network policies:

https://www.kube-router.io/

https://docs.projectcalico.org/getting-started/kubernetes/

https://romana.io/

https://kubernetes.io/docs/tasks/administer-cluster/network-policy-provider/weave-network-policy/

### a curated list of network policies

ref: https://github.com/ahmetb/kubernetes-network-policy-recipes


## Volumes

https://kubernetes.io/docs/concepts/storage/volumes/

Volumes can be of temporal (ephemeral) or persistent nature.

Ephemeral Volumes are created and destroyed with the pod they belong to.


### Volumes
For example a pod definition with a NFS volume:

```
apiVersion: v1
kind: Pod
metadata:
 name: web
spec:
containers:
 - name: web
   image: nginx
   volumeMounts:    # here we mount the volume in the pod
   - mountPath: /mnt/vol
     name: nfs
volumes:         # this is the volume resource
- name: nfs
  server:10.1.1.2
     path: "/"
     readOnly: false
 ```
 
 Or a definition of a volue, as folder from the node:
 
 ```
 ...
 volumeMounts:    # here we mount the volume in the pod
 - mountPath: /opt
   name: data-volume
volumes:         # this is the volume resource in the node
- name: data-volume
  hostPath:
    path: data
    type: Directory
```

 
 Secrets and ConfigMaps are other example of ephemeral volumes.
 
 Other example is the: emptyDir volume is simply an empty directory that allows the 
containers within the Pod to read and write to and from it. It’s 
created when a Pod is assigned to a node, and it exists as long as 
the Pod exists. However, it’ll be deleted if the Pod is removed from 
a node for any reason. So don’t use emptyDir volumes for data of 
lasting value. Applications usually use emptyDir for short-term 
purposes.

https://kubernetes.io/docs/concepts/storage/volumes/#emptydir

### Persistent Volumes & Persistent Volume Claims

https://kubernetes.io/docs/concepts/storage/persistent-volumes/

https://kubernetes.io/docs/tasks/configure-pod-container/configure-persistent-volume-storage/

A persistent volume has a livecycle that is not attached to the pod that is using it. Persistent storage makes it possible to deal with failures and 
allow for dynamic rescheduling of  components without loss of data. 

A **persistent volume (PV)** is pool of storage volumes configured by an administrator. Those persistent volumes are requested to be used by a **Persisten Volume Claims (PVC)** in the pods that need them.

Application developers can claim and use provisioned storage using PersistentVolumeClaims without creating and 
maintaining storage volumes directly. This enforces the separation of roles (microservices).  It’s the job of administrators to make persistent volumes 
available, and the job of developers to use those volumes in applications. The two job roles can work independently (decoupled) of each other.

PersistentVolumes provide a level of abstraction that lets you decouple storage administration from application configuration.

PersistentVolumeClaims are requests  made by Pods to use PersistentVolumes. Within a PersistentVolumeClaim object, 
you define a Volume size, access mode, and StorageClass. What’s a StorageClass? It’s a set of storage characteristics that you’ve given a name to.

A Pod uses this PersistentVolumeClaim to request a PersistentVolume. If a PersistentVolume matches all the requirements defined in a PersistentVolumeClaim, the 
PersistentVolumeClaim is bound to that PersistentVolume. 

example of a pod with a PVC:

```
apiVersion: v1
kind: Pod
metadata:
 name: demo-pod
spec:
 containers:
  - name: demo-container
    image: gcr.io/hello-app:1.0
 volumeMounts:
  - mountPath: /demo-pod
    name: pd-volume
 volumes:
 - name: pd-volume
   PersistentVolumeClaim:
   claimName: pd-volume-claim
```

and the persistant volume claim:

```
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
 name: pd-volume-claim
spec:
storageClassName: “standard"
 accessModes: 
- ReadWriteOnce: 
 resources:
requests: 
storage: 100G
```
and the persistant volume:

```
apiVersion: v1
kind: PersistentVolume
metadata: 
    name: pv-vol1
spec:
   accessModes:
       - ReadWriteOnce
   capacity:
       storage: 100G
   getPersistentDisk:
       pdName: pd-disk
       fsType: ext4
```
### types of persistent volumes

There are a lot...

- awsElasticBlockStore - AWS Elastic Block Store (EBS)
- azureDisk - Azure Disk
- azureFile - Azure File
- cephfs - CephFS volume
- cinder - Cinder (OpenStack block storage) (deprecated)
- csi - Container Storage Interface (CSI)
- fc - Fibre Channel (FC) storage
- flexVolume - FlexVolume
- flocker - Flocker storage
- gcePersistentDisk - GCE Persistent Disk
- glusterfs - Glusterfs volume
- hostPath - HostPath volume (for single node testing only; WILL NOT WORK in a multi-node cluster; consider using local volume instead)
- iscsi - iSCSI (SCSI over IP) storage
- local - local storage devices mounted on nodes.
- nfs - Network File System (NFS) storage
- photonPersistentDisk - Photon controller persistent disk. (This volume type no longer works since the removal of the corresponding cloud provider.)
- portworxVolume - Portworx volume
- quobyte - Quobyte volume
- rbd - Rados Block Device (RBD) volume
- scaleIO - ScaleIO volume (deprecated)
- storageos - StorageOS volume
- vsphereVolume - vSphere VMDK volume


## Dynamic Volume Provisioning & Storage classes

https://kubernetes.io/docs/concepts/storage/dynamic-provisioning/

With storage classes you can provison a volume when a claim is made in a pod, that is known as dynamic volume provisioning.

With dynamic provision:

example of a pod with a PVC:

```
apiVersion: v1
kind: Pod
metadata:
  name: demo-pod
spec:
  containers:
   - name: demo-container
     image: gcr.io/hello-app:1.0
     volumeMounts:
     - mountPath: /demo-pod
       name: pd-volume
  volumes:
  - name: pd-volume
  PersistentVolumeClaim:
    claimName: pd-volume-claim
```

and the persistant volume claim:

```
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
 name: pd-volume-claim
spec:
 accessModes: 
- ReadWriteOnce: 
storageClassName: google-storage
 resources:
     requests: 
       storage: 500Mi
```

and the persistant volume:

```
#sc-definition.yaml
apiVersion: storage.k8s.io/v1
kind: StorageClass
metadata: 
    name: google-storage
provisioner: kubernetes.io/gce-pd
```

## CLUSTER MONITORIG

The cluster should be monitored, and we should be able to get the information about how many nodes are running,
cpus, memory usage, performance, networking statuses ...  there are many options to monitor all this parameters, like:

- https://github.com/kubernetes-sigs/metrics-server

- https://prometheus.io/

- https://www.elastic.co/what-is/elk-stack


ref : https://thenewstack.io/12-critical-kubernetes-health-conditions-you-need-to-monitor/

12 health conditions to monitor:

- cpu utilization
- Disk usage
- memory usage
- number of processes running
- network availability
- jobs failures
- peristent volumes failures
- pod pending delays
- stateful sets not ready
- DaemonsSets not ready

topic autoscalling: https://learnk8s.io/kubernetes-autoscaling-strategies

<hr>

## KUBERNETES SECURITY

reference: https://kubernetes.io/docs/concepts/security/overview/

a cluster security can be structured in four levels (4 C's of cloud native security)
- cloud
- cluster
- container
- code

Kubernetes security is based on the topics:

- Cluster setup: that is cluster configuration and setup in a secure way
- Cluster hardening: techniques that increase a cluster security
- System Hardening: protection of the operating system and infraestructures
- Minimizing microservices vulnerabilities: techniques to secure microservices applications
- Supply chain security: ensuring that the code an applications used in the cluster don't became a thread to the cluster
- Monitoring, loggging and runtime security: detection and diagnosis of potential security breaks.

### Cluster setup

#### Network policies
Network policies are used to restrict communication between pods. Remember that for having network policies plugins must be used. This is important because if a pod is compromised, from there, other pods can be compromised. 

An example for deny all network communications is at: https://kubernetes.io/docs/concepts/services-networking/network-policies/#allow-all-ingress-traffic

```
---
apiVersion: networking.k8s.io/v1
kind: NetworkPolicy
metadata:
  name: allow-all-ingress
spec:
  podSelector: {} # the selector {}, implies selecting all the pods in the given namespace!!
  ingress:
  - {}
  policyTypes:
  - Ingress
```

Network policies can be added, so with a given deny-all network policy but with other
specific network policy that allows communication between two pods, those two pods, 
would be able to communicate. 

#### Securing node enpoints

K8s uses some ports for communications. Be aware those need to be proctected

Control plane listening ports (for kubeadm defaults)

| POrts | User |
| ----------- | ----------- |
| 6443 | k8s api server |
| 2379-2380 | etcd |
| 10250 | kuberlet API |
| 10251 | kube-scheduler |
| 10252 | kube-controller-manager |

and for the worker nodes:

| POrts | User |
| ----------- | ----------- |
| 10250 | kubelet api |
| 300000-32767 | nodeport services |


#### Ingress with TLS

An ingress manage access from outside the cluster. They can work on top of services.

reference: https://kubernetes.io/docs/concepts/services-networking/ingress/#tls

to quickly create the certificates you can use:

```
openssl req -nodes -ew -x509 -keyout tls-ingres.key -out tls-ingress.crt -subj "/CN-ingress.test"
```

#### CIS benchmakrs

CIS stands for Center of Internet Security, its goal is increase internet security.

It is possible to get CIS benchmarks for different systems. 

A tool to run security benchmarks, is Kube-bench: https://github.com/aquasecurity/kube-bench

#### Tips for dockerfiles

- Don't use root user. 
- Don't open not needed ports

#### k8s security primitives

 - hosts: the access to the hosts must be secured, root user disabled, password access disabled, only ssh key based acesss available. 

The most basic point of access is the kube-apiserver, so it has to be hardened, two main points: 
 - authentification : Who can access?
 - authoritation: What can they do?

All the communications with kube-apiserver is done with TLS (which is an encrypted protocol) 

In the cluster, by default, all the pods, can communicate with the other pods, but that can be restringed by means of defining network policies. 

#### Authentification

there are two main users
- users: admins, developers
- programs, applications... (services accouts)

all users access is managed by the kube-apiservers, for examply by using kubectl. 

A list with all the users, and paswords, can be given to the cluster with the option to the kube-apiserver: --basic-auth-file=<file-of-users> 
 
Other option is instead of a file with the users details, is possible to use a static file with token, with the option: --token-auth-file=<file-token>

More links:
 - admission controllers: https://kubernetes.io/docs/reference/access-authn-authz/admission-controllers/

 

#### Threat detection
 
 Falco (https://falco.org/) , the open-source cloud-native runtime security project, is the de facto Kubernetes threat detection engine.

NOTE: Other tools you might have to be familar with are sysdig (https://github.com/draios/sysdig)  or tracee (https://github.com/aquasecurity/tracee)
 
 kube-bench is a tool that checks whether Kubernetes is deployed securely by running the checks documented in the CIS Kubernetes Benchmark. 
 
 ref: https://github.com/aquasecurity/kube-bench
 
 also ref: https://kubernetes.io/docs/tutorials/security/apparmor/
 
 <br> <br> <br>
 
![kubernetes dificulty](https://github.com/sergiocollado/potpourri/blob/master/image/kubernetes_difficulty.jpg)
 
  <br> <br> <br>
  <br> <br> <br>
 
 <hr>
 
# HOW TO's

## Howto start with a cluster
 
 To retrieve general information from a cluster your are not used to, use:
 
 ```
 k8s@terminal:~$ kubectl cluster-info
 
 k8s@terminal:~$ kubectl get node -o wide
 
 k8s@terminal:~$ kubectl config view
 
 k8s@terminal:~$ kubectl config view --raw
 
 k8s@terminal:~$ kubectl get ns
 
 k8s@terminal:~$ kubectl get all --all-namespaces
 ```
 
## How to get a shell to a runnnig contaniner

ref: https://kubernetes.io/docs/tasks/debug-application-cluster/get-shell-running-container/

```
kubectl exec --stdin --tty <your-pod> -- /bin/bash
```
 
```
kubectl exec -it <your-container> -- /bin/sh # or any other terminal
```

## Howto labels

To add labels, the command 'kubeclt label ...' is used:

```
 kubectl label [--overwrite] (-f FILENAME | TYPE NAME) KEY_1=VAL_1 ...KEY_N=VAL_N [--resource-version=version] [options]
```

It is recommended to use labels in a way that describes the application, so they can be queried.

Recommended labels: https://kubernetes.io/docs/concepts/overview/working-with-objects/common-labels/
 
For example to add a label to a given node:
 
```
kubectl label node cluster1-worker1 security=apparmor
```


## Howto Pods

A yaml file that defines a pod, would be like:

```
apiVersion: v1
kind: Pod
metadata:
   name: myapp
   labels:
      app: myapp-pod
      type: back-end
spec:
   containers:
       -name: nginx-container
        image: nginx
        command: ["echo"]
        args:["Hello World!"]
        ports:   #optional
            - containerPort: 8080
        env:     #optional - to define enviroment variables
            -name: APP_COLOR
             value: blue
            -name: THEME_COLOR
             valueFrom:
                configMapKeyRe
            -name: USER
             valueFrom:
                secretkeyRef
          
```
As any yaml definition file for Kubernetes it has 4 main parts:

- apiVersion
- kind
- metadata
- spec


to create the Pod, use the command:

```
kubectl create -f pod-defintion.yml
```

to verify that the pod has been created, use:

```
kubectl get pods

```

to get the pods with a given label use:

```
kubectl get pods --selector label_key=label-value
```

for example:
```
kubectl get pods --selector app=myapp-pod
```

to get more detailed info use:

```
kubectl describe pod myapp-pod 
```

it you want to copy a pod's definition into a file, use:

```
kubectl get pod <pod-name> -o yaml > pod-defintion.yml
```

To edit a pod's properties use:

```
kubectl edit pod <pod-name>
```

example: https://www.youtube.com/watch?v=DFEOdnYw1WY

To set pods resources, see: https://kubernetes.io/docs/concepts/configuration/manage-resources-containers/

## Howto Configuration Maps

ConfigMaps are objects that keep a configuration definition of **enviromental variables** to be used in a Pod.

the data in the config map, is simply given as a list of key-value pairs.

```
APP_THEME_COLOR: BLUE
APP_MODE: PROD
```

to create a configMap in an imperative way:

```
kubectl create configmap <config-name> --from-literal=<key>=<value>
```
example:
```
kubectl create configmap \
   my_config --from-literal=APP_THEME_COLOR=BLUE
             --from-literal=APP_MODE=PROD
```

or to create it from a file:

```
kubectl create configmap <config-name> --from-file=<path-to-file>
```
example:
```
kubectl create configmap \
    app-config --from-file=app_config.propierties

```

to create a configmap in a declarative way, you need to create a definition file

```
#configmap.yml definition
apiVersion: v1
kind: ConfigMap
metadata:
    name: app-config
data: 
    APP_THEME_COLOR: BLUE
    APP_MODE: PROD
```

and then use the create command:

```
kubectl create -f configmap.yml
```

to get the configmaps:

```
kubectl get configmaps
```

to inspect the config maps:

```
kubectl describe configmaps
```

To pass the config map to a Pod definition:

```
apiVersion: v1
kind: Pod
metadata:
  name: nginx-pod
  labels:
    app: nginx
spec:
  containers:
  - name: nginx
    image: nginx:1.15.12
    ports:
        - containerPort: 80
    envFrom:
        - configMapRef:    # here we inject the config map into the pod definition.
            name: app-config
```

```
#configmap.yaml definition
apiVersion: v1
kind: ConfigMap
metadata:
    name: app-config
data: 
    APP_THEME_COLOR: BLUE
    APP_MODE: PROD
```

reference: https://kubernetes.io/docs/tasks/configure-pod-container/configure-pod-configmap/


### Howto Secrets

Secrets objects used to store sensitive information, like passwords, keys or personal data... and are stored in a hashed format (although not encripted!)

to create a secret imperatively:

```
kubectl create secret generic <secret-name> --from literal=<key>=<value>
```

example:


```
kubectl create secret generic 
      app-secret --from literal=DB_HOST=redis \
                 --from literal=DB_USER=root  \
                 --from literal=DB_PASSWORD=password
```

or for creating it imperatively from a file:

```
kubectl create secret generic <secret-name> --from-file=<path-to-file>
```
example:

```
kubectl create secret generic app-secret --from-file=app_secret.propierties
```

to create a secret declaratively:

```
#secret-data.yaml
apiVersion: v1
kind: Secret
metadata: 
    name: app-secret
data: 
    DB_HOST: 2astasefq   # the secret must be written in encripted format.
    DB_USER: 45t6yuki
    DB_PASSWORD: p7ytgfcdew
```
and command:

```
kubectl create -f secret.data.yaml
```

To encode the strings, in a linux machine use:

```
echo -m 'password' | base64
> p7ytgfcdew
```
to decode the previous encoding:

```
echo -n 'p7ytgfcdew' | base64 --decode
> password
```

to list the secrets, use the:

```
kubectl get secrets 
```

for more details:

```
kubectl describe secrets
```

this will not show the secrets values, but if you want it use:

```
kubectl get secret app-secret -o yaml
```

To configure a secret within a pod:

```
apiVersion: v1
kind: Pod
metadata:
  name: nginx-pod
  labels:
    app: nginx
spec:
  containers:
  - name: nginx
    image: nginx:1.15.12
    ports:
        - containerPort: 80
    envFrom:
        - configMapRef:    # here we inject the config map into the pod definition.
            name: app-config
        - secretRef:       # here we inject the secret into the pod definition.
            name: app-secret
```

To define a Secret into a Pod, there are three ways:

As enviroment variables: 
```
envFrom: 
  - secretRef:
       name: my-secret
```

Or as a single enviroment variables:
```
env: 
  - name: Secret-password
    valueFrom: 
       secretKeyRef:
          name: my-secret
          key: Password
```

Or mount the secrete as a volume in the pod:

```
volumes:
- name: my-secret-volume
  secret:
    secret-name: my-secret
```

reference: https://kubernetes.io/docs/tasks/inject-data-application/distribute-credentials-secure/#configure-all-key-value-pairs-in-a-secret-as-container-environment-variables


### Howto Security contexts

Some secure settings can be define at the container run engine level or at the pod level. If configured at the pod level, those settings will be defined for all the containers within the pod. If defined in both places, the container and the pod, the pod settings will override the container settings.

To add the Security Context at the container level, add it in the spec of the container.

```
apiVersion: v1
kind: Pod
metadata:
  name: web-pod
  labels:
    app: front-end
spec:
  containers:
  - name: ubuntu
    image: ubuntu
    command: ["sleep", "3600"]
    securityContext:
      runAsUser: 1000
      capabilities:
          add: ["MAC_ADMIN"]
```

To add the security context add the POD level, add it ad the specs of the po

```
apiVersion: v1
kind: Pod
metadata:
  name: web-pod
  labels:
    app: front-end
securityContext:
  runAsUser: 1000
spec:
  containers:
  - name: ubuntu
    image: ubuntu
    command: ["sleep", "3600"]
```

 Other good idea, is limit the posibility of the container to change files in the system, and only use
 the /tmp directory, for that use:
 
 ```
 ...
       containers:
      - image: busybox:1.32.0
        name: busybox
        securityContext:                  
          readOnlyRootFilesystem: true    
        volumeMounts:                     
        - mountPath: /tmp                 
          name: temp-vol                 
      volumes:                          
      - name: temp-vol             
        emptyDir: {}        
 ...
 ```
 
 
### Howto: taints ant tolerations

Tains and tolerations are means to restrict Pods to run in certain Nodes. A node may define a given taint, and only pods that define toleRACtion to that taint can run in that node. 

To define a taint:

```
kubectl taint nodes <node-name>  <key>=<value>:<taint-effect>
```

there are three taint effects: NoSchedule, PreferNoSchedule, NoExectute.

Taints are defined in Nodes, and tolerations are defined in Pods

To define a toleration in a pod: 

```
apiVersion: v1
kind: Pod
metadata:
  name: nginx-pod
  labels:
    app: nginx
spec:
  containers:
  - name: nginx
    image: nginx:1.15.12
    ports:
    - containerPort: 80
  tolerations:
  - key: "app"
    operator: "Equal"
    value: "blue"
    effect: "NoSchedule"
    #watchout! the values must be defined with " ".
```

### Howto readiness and liveness probes.

to check if an application is ready we can define different tests (or probes) to check if an app is running. Maybe with an HTTP test, or TCP test, or maybe executing a command within the container that runs a custom scritp that checks if the app is ready. 

```
apiVersion: v1
kind: Pod
metadata:
  name: nginx-pod
  labels:
    app: nginx
spec:
  containers:
  - name: nginx
    image: nginx:1.15.12
    ports:
    - containerPort: 8080
    readinessProbe:
      httpGet:
         path: /api/ready
         port: 8080
      initialDelaySeconds: 10
      periodSeconds: 15
      failureThreshold: 8
```

for a tcp probe:

```
    readinessProbe:
       tcpSocket:
           port: 3306
```

for a script probe:

```
    readinessProbe:
        exec: 
           command:
           - cat
           - /app/is_it_ready
```


extra options:

```
      initialDelaySeconds: 10
      periodSeconds: 15
      failureThreshold: 8
```

A livenes probe can check if an application is running as expected. And it can test periodically if the application within the container is "healthy", in case the test fails the the container is considered "unheathy" and destroyed.  The test, can be a http test, or a tcp test, or run a command that do the test. A liveness probe is defined similar to the readiness probe. 

```
apiVersion: v1
kind: Pod
metadata:
  name: nginx-pod
  labels:
    app: nginx
spec:
  containers:
  - name: nginx
    image: nginx:1.15.12
    ports:
    - containerPort: 8080
    livenessProbe:
      httpGet:
         path: /api/ready
         port: 8080
      initialDelaySeconds: 10
      periodSeconds: 15
      failureThreshold: 8
```

ref : https://thenewstack.io/12-critical-kubernetes-health-conditions-you-need-to-monitor/

12 health conditions to monitor:

- cpu utilization
- Disk usage
- memory usage
- number of processes running
- network availability
- jobs failures
- peristent volumes failures
- pod pending delays
- stateful sets not ready
- DaemonsSets not ready
- crash loops
 
### Howto Multi-container Pods.

To define several containers in a pod:

```
apiVersion: v1
kind: Pod
metadata:
  name: nginx-pod
  labels:
    app: nginx
spec:
  containers:
  - name: nginx
    image: nginx:1.15.12
    ports:
    - containerPort: 8080
  - name: log-agent
    image: log-agent
```

This is known as the sidecar pattern, but there are other patterns as the ambassador or the adapter.

### Howto Static Pods

  The kubelet can be configured to read pod's definitions files from given directory. The kubelet will read that directory and handle the creation of those pods, and also keep them alive (restart the pods) in case they crash. The pods defined in this way, are kwnown as **static-pods**. 
  
  The static-pods are managed by the node's kubelet, son even in case the control-plane fails, or the api-server is not working, those pods are still being managed for the node's kubelet.
  
  To define the static-pod configure the kubelet on the node to use this directory by running it with --pod-manifest-path=/etc/kubelet.d/ argument.
  
  Other way is to provide a configuration file, with the --config=kubeconfig.yaml option. And define the static-pod in that file: staticpodPath:<the directory>.
 
  reference: https://kubernetes.io/docs/tasks/configure-pod-container/static-pod/

## Howto Namespaces

To get the namespaces

```
kubectl get namespaces
```

To get the pods in a given namespace:

```
kubectl get pods --namespace=kube-system
```

To display the pods in all the namespaces

```
kubectl get pods --all-namespaces -o wide
```
 
Instead of '--all-namespaces', it can be used: '-A'
 
 
To display all the objects in a given namespace

```
kubectl get all -namespace <mynamespace>
```

To create a pod in a given namespace:

```
kubectl create -f mypod-def.yaml --namespace=dev
```

or define it in the definition file, like:

```
apiVersion: v1
kind: Pod
metadata:
  name: nginx-pod
  namespace: dev
  labels:
    app: nginx
spec:
  containers:
  - name: nginx
    image: nginx:1.15.12
```

a new namespace can be created with a definition file:

```
#definition file of 'dev' namespace.
apiVersion: v1
kind: Namespace
metadata:
   name: dev
```
and: 

```
kubectl create -f namespace-dev.yaml
```

or imperatively:

```
kubectl create namespace dev
```

by default, we start in the default namespace, but if we want to move to another namespace:

```
kubectl config set-context $(kubectl config current-context)  --namespace=dev
```

to get all the existing namespaces

```
kubectl get namespace
```

or in short

```
k get ns
```

to manage resources in a given namespace, a resource quota can be defined:

```
apiVersion: v1
kind: ResourceQuota
metadata:
    name: compute-quota
    namespace: dev
spec:
  hard
    pods: "15"
    requests.cpu: "5"
    requests.memory: 5Gi
    limits.cpu: "15"
    limits.memory: 15Gi
```
to get for example all the pods in a given namespace, the option --namespace can be used

```
kubectl -get pods --namespace=kube-system
``` 
reference: https://kubernetes.io/docs/tasks/administer-cluster/manage-resources/cpu-default-namespace/


## Howto Replica Controller

reference: https://kubernetes.io/docs/concepts/workloads/controllers/replicationcontroller/

A sample replica controller definition file is: 

```
# rc-definition.yml
apiVersion: v1
kind: ReplicationController
metadata:
    name: myapp-rc
    labels: 
        app: myapp
        type: front_end
specs:
    template:
    # template, will be the template to the pods to replicate
    # so the info below match the metadata and specs of a pod definition
        metadata:
            name: myapp-pod
            type: front-end
        spec:
            containers:
            - name: nginx-container
              image: nginx
              command: ["sleep"] #to run commands when creating the pod (optional)
              args: ["10"] #arguments to the commands (optional)
    replicas: 3
    # this is the desired number of replicas
```

to create a replication controller command:

```
kubectl create -f rc-definition.yml
```

to check the replication controller:

```
kubectl get replicationcontroller
```

to check the pods run by the replication controller:

```
kubectl get pods
```

## Howto Replica Set

reference: https://kubernetes.io/docs/concepts/workloads/controllers/replicaset/

A example file that defines a replica set:

```
# replicaset-definition.yml
apiVersion: apps/v1    #WATCHOUT: the correct version for a rs is the apps/v1
kind: ReplicationController
metadata:
    name: myapp-replicaset
    labels: 
        app: myapp
        type: front_end
specs:
    replicas: 3
    selector: 
        matchLabels
            type: front-end  #!this label has to match with the label in the pods. (see below)
    template:
    # template, will be the template to the pods to replicate
    # so the info below match the metadata and specs of a pod definition
        metadata:
            name: myapp-pod
            type: front-end  #! this label has to mathc with the sleector label of the replica-set. (see previous comment)
        spec:
            containers:
            - name: nginx-container
              image: nginx
    
```

A ReplicaSet can be used to monitor a group of Pods, that are already running, and in case those are not created, the replicaset can create them. the role of the replicaset is to monitor the pods, and if any were to fail, replace them by new ones. The way to identity the pods to monitor is by means of matching labels (with the matchLabel filter), defined in the definition of the Replica set.

to create a replica set, run:

```
kubectl create -f replicaset-definition.yml
```

to get the created replicas:

```
kubectl get replicaset
```

to see the pods run by the replica set:

```
kubectls get pods 
```

to scale a replica set, we would need to update the desired number of replicas in the definition file, in the 'replicas: ' tag. then run the replace command:

```
kubectl replace -f replicaset-definition.yml
```
other way to scale a replica set, is to run the 'scale' command: 

```
kubectl scale --replicas=6 -f replicaset-definition.yml
```

another way to use the scale command is instead of using the file, using the controller type, and the replica set defined name:

```
kubectl scale --replicas=6 replicaset myapp-replicaset
```

but be aware, that in this way the defined file will not be updated.

to delete a replica set, just use the 'delete' command:

```
kubectl delete replicaset myapp-replicaset
```

example: https://www.youtube.com/watch?v=Y2SA7sCtKSs&feature=youtu.be


## Howto Deployments

A sample definition file for a deployment would be:

```
# deployment-definition.yml
apiVersion: app/v1
#WATCHOUT: the correct version for a deployment is the app/v1
kind: Deployment
metadata:
    name: myapp-deployment
    labels: 
        app: myapp
        type: front_end
specs:
    template:
    # template, will be the template to the pods to replicate
    # so the info below match the metadata and specs of a pod definition
        metadata:
            name: myapp-pod
            type: front-end
        spec:
            containers:
            - name: nginx-container
              image: nginx
    replicas: 3
    selector: 
        matchLabels
            type: front-end
```


Commands to create deployments:

**Declaratively**:

```
 kubectl create -f <deployment_file.yaml>
 ```
 
to update the deployment:
```
 kubectl apply -f <deployment_file.yaml>
 ```

**Imperatively**:

For this no definition file is needed. The needed replica set and pods are automatically created. 
```
kubectl run <deployment_name> \
  --image  <image>:<tag>
  --replicas N \
  --labels <key>=<value> \ c
  --port  XX \
  --generator deployment/apps.v1 \
  --save-config
```

To inspect the deployment:

```kubectl get deployment <deployment_name>```

Or to get it in yaml format:

```kubectl get deployment <deployment_name> -o yaml > thisdeployment.yaml ``` 

Or to get even more information

 ```kubectl describe deployment <deployment-name> ```

For manually scaling a deployment.

 ```kubectl scale deployment <deployment_name> --replicas=N ```

example : 

  ```kubectl scale --replicas=3 deployment nginx-deployment```

Also, you can perform autoscaling 

 ```kubectl autoscale deployment <deployment_name>  --min=N --	max=M --cpu-percentaje=P ```

To define a deploy period to perform another scale action:

--horizontal-pod-autoscaler-downscale-delay
 
 To expose a deployment with a service
 
 ```
 # Create a service for an nginx deployment, which serves on port 80 and connects to the containers on port 8000
  kubectl expose deployment nginx --port=80 --target-port=8000
 ```

## Howto Rollout

A rollout is to launch a new software version. So for example, go from sw release 1 to sw release 2. 

A deployment's rollout is triggered if and only if the deployment's Pod template (that is, .spec.template) is changed,

To check the rollout status:

```
kubectl rollout status deployment.v1.apps/nginx-deployment
```

To view the rollout history:

```
kubectl rollout history deployment nginx-deployment
```

there are 2 deployment stragegies:

**Recreation**: replace at one all the running version and launch instead all the new versions. the disadvantage is that at one momenet we have to take down all the sw, and the application is down up to it is replaced.

**Rolling update**: one by one, the old versions are taken down and replaced by the new versions. This is the better approach as the application is always running.

## Howto Update deployments


To update a deployment, we just need to edit the definition of the deployment and apply it with the command:

```kubectl apply -f <deployment_file> ```

Or 

 ```kubectl set image deployment <deployment-name> <image> <image>=<tag> ```

Or 

 ```kubectl edit deployment /<deployment_name> ```
 
## Howto rollback deployments

To rollback a deployment

To the previous revision:

```
kubectl rollout undo deployment <deployment_name>
```

To a given revision number:

```
kubectl rollout undo deployment <deployment_name> --to-revision=X
```

or
```
kubectl rollout history deployment <deployment_name> --revision=X
```

To pause the rollout (maybe to workout some issue)

```
kubectl rollout pause deployment <deployment_name>
```

To resume it:
```
kubectl rollout resume deployment <deployment_name>
```

Or to check out the roll out status.

```
kubectl rollout status deployment <deployment_name>
```

One you are done, with the deployment you can delete it

```
kubectl delete deployment <deployment_name>
```

## Howto namespaces

A sample file to define a namespace would be:

```
#namespace-dev.yml
appiVersion: v1
kind: Namespace
metadata:
    name: dev
```

to create the namespace:

```
kubectl create -f namespace-dev.yml
```

or faster:

```
kubectl create namespace dev
```

## Howto resource quota:

reference: https://kubernetes.io/docs/concepts/configuration/manage-resources-containers/

to limit resource in a namespace you use a resource quota, to define one:

```
#compute-quota.yml
apiVersion: v1
kind: ResourceQuota
metadata:
    name: compute-quota
    namespace: dev
spec:
    hard:
        pods: "15"
        requests.cpu: "4"
        requests.memory: 5Gi
        limits.cpu: "10"
        limits.memory: 10Gi
```

to create it:

```
kubectl create -f compute-quota.yaml
```

The resource quota can be also specified in the Pod definition:

```
apiVersion: v1
kind: Pod
metadata:
  name: nginx-pod
  labels:
    app: nginx
spec:
  containers:
  - name: nginx
    image: nginx:1.15.12
    ports:
    - containerPort: 80
    resources:
        requests:
            memory: "1Gi"
            cpu: 1
        limits: 
            memory: "2Gi"
            cpu: 2
```


## Howto Jobs and CronJobs

The Job controller creates one or more Pods required to run a task. When the task is completed, Job will then terminate all those Pods. A related controller is CronJob, which runs Pods on a time-based schedule. Jobs run a task up to its completion, rather than a desired state. 

There are two main jobs definitions: **parallel** and **non-parallel**.
 
Non-parallel jobs cretate one pod at a time, and that pod, will be recreated if it doesn’t finish the job successfully. The condition to be successful is to finish the job, or that the job has run a given number of times. 

Parallel jobs are those that work on parallel, where multiple pods are scheduled to work on the same job at the same time. They also have a completion count to satisfy. They are used when jobs have to be done more than once. A second type of parallel jobs are jobs with worker queues, in this each pod, work on several items from a queue, and then exits when there are no more items.  

To create a non-parallel job:

```kubectl apply -f <job-file>```

Or using the run command:

```kubectl run <job-file> pi --image perl --restart Never -- perl -Mbignum bpi -wle “print bpi(2000)” ```

To inspect jobs 

``` kubectl describe job <job-name> ```

``` kubectl get pod -L <job-name=my-app-job> ```

“-L” is the label selector.

To scale jobs:

```kubectl scale job <job_name> --replicas <value> ``` 

To delete a job:

```kubectl delete -f <job_name>```

```kubectl delete job <job_name>```
 
Or if retain a job is needed, use the cascade flag set to false:

```kubectl delete job <job_name> --cascade false ```
 
To schedule a job and run it periodically, CronJobs are used.

CronJobs use the required schedule field, which accepts a time in the Unix standard crontab format. All CronJob times are in UTC:
 - The first value indicates the minute (between 0 and 59).
 - The second value indicates the hour (between 0 and 23).
 - The third value indicates the day of the month (between 1 and 31).
 - The fourth value indicates the month (between 1 and 12).
 - The fifth value indicates the day of the week (between 0 and 6).
 - The schedule field also accepts * and ? as wildcard values. Combining / with ranges specifies that the task should repeat at a regular interval. In the example, */1 * * * * indicates that the task should repeat every minute of every day of every month. 

To define a job with a file:

```
#job definition - job.yml
apiVersion: batch/v1
kind: Job
metadata:
  name: my-job
spec:
  completions: 8
  parallelism: 4
  template:
     spec:
        containers:
          - name: my-job
            image: my-job-image
            command ['./launch_job']
          
        restartPolicy: Never
```
 
To define a CronJob file:

```
#Cronjob definition - cron-job.yml
apiVersion: batch/v1beta1
kind: CronJob
metadata:
  name: my-cron-job
spec:
  schedule: "*/1 * * * *"
  jobtemplate:
     spec:
        containers:
          - name: my-cron-job
            image: my-cron-job-image
          
        restartPolicy: Never
```
to create the cron-job

```
kubectl create -f cron-job.yml
```

## Pod Networking

In the kubernetes model, each pod is assigned a single IP address. And the containers in that pod, contain the same ip space, including that IP address. 
**Services** give pods stable IP addresses. A kubernetes service is an object that creates a dynamic collection of IP addresses, called endpoints, that belog to pods, that match the services label selector. 
STORAGES ABSTRACTIONS
**Volumes** are the method by which you attach storage to a Pod.
Some Volumes are ephemeral, meaning they have the same life span as the pod they are attached to. Other volumes are persistent, meaning they can outlive a Pod. 
 
reference for policy recipes: https://github.com/ahmetb/kubernetes-network-policy-recipes
 
# Authentication, authorization and admission control

To access and manage kubernetes there are three stages:

- authentication: logs a user.
- authorization: authorizes the requests API.
- admission control: software modules that can handle requests based on extra information.

 
## HowTo Ingress

Ingress allows users access the application using a single external url, that can be configured to run throught different services of the cluster. Althought the ingress must still be published as a service.

An Ingress has two main components

 - ingress controller
 - ingress resources

To define an ingress you have to define a **ingress controller**, like:

https://www.nginx.com/

http://www.haproxy.org/

https://doc.traefik.io/traefik/

https://projectcontour.io/

https://istio.io/

An ingress controller must be deployed. For example, an nginx, and it can be deployed, just as any other deployment.

```
apiVersion: extensions/v1beta
kind: Deployment
metadata: 
  name: nginx-ingress-controller
spec:
  replicas: 1
  selector:
      matchLabels:
         name: nginx-ingress
  template:
      metadata: 
         Labels: 
            name: nginx-ingress
      spec:
         containers:
             - name: nginx-ingress-controller
               image: quay.io/kubernetes-ingress-controller/nginx-ingress-controller:0.21.0 
               # above is defined a custom build of nginx for being an ingress controller for k8s
         args:
             - /nginx-ingress-controller  #command to start the nginx controller.
             - --configmap=$(POD_NAMESPACE)/nginx-config  #recommended to add a config map.
             # with the definition of a config map, you can define for example variables for
             # nginx, like the log paths, keeps alive, secure protocols settings, timeouts
             # and with this you can decouple those parameters from the container image. 
         env:
            # Envirmental variables that define the pod's name and the namespace are needed
             - name: POD_NAME
               valueFrom:
                  fieldRef:
                     fieldPath: metadata.name
             - name:
               valueFrom:
                  fieldRef:
                     fieldPath: metadata.namespace
        ports:
             - name: http
               containerPort: 80
             - name: https
               containerPort: 443
```

Then a service must be defined to publish the ingress controller

```
appVersion: v1
kind: Service
metadata:
    name: nginx-ingress
spec: 
    type: NodePort
    ports:
    - port: 80
      targetPort: 80
      protocol: TCP
      name: http
    - port: 443
      targetPort: 443
      protocol: TCP
      name: https
    selector:
      name: nginx-ingress
```

A service account with the required permissions, also needs to be created:

```
apiVersion: v1
kind: ServiceAccount
metadata: 
    name: nginx-ingress-serviceaccount
    # ....
```

Also,in addition to the ingress controller, we have to define a set of rules, related as **ingress resources**.

An ingress resource, will define rules, like routing all the traffic to a single application, or direct the traffic to different applications based on the url or the domain name. 

The ingress resource is defined with a k8s definition file (.yaml). It define rules to route traffic

```
# ingress-rule.yaml
apiVersion: extensions/v1beta1
kind: Ingress
metadata: 
    name: ingress-rule
spec:
    backend:
         serviceName: rule-service # service name
         servicePort: 80
```

To route the traffic according to URL:

```
# ingress-url-rule.yaml
apiVersion: extensions/v1beta1
kind: Ingress
metadata: 
    name: ingress-rule
spec:
    rules:
    - http: 
         paths:   # paths is an array of different items
         - path:  /main-topic
             backend:
                serviceName: main-topic-service # service name
                servicePort: 80
         - path: /second-topic
                serviceName: second-topic-service # service name
                servicePort: 80
```

Or to make rules based on domain names:

```
# ingress-domain-name-rule.yaml
apiVersion: extensions/v1beta1
kind: Ingress
metadata: 
    name: ingress-rule
spec:
    rules:
    - host: domainName1.com
       http: 
         paths:   # paths is an array of different items
           - backend:
                serviceName: domainName_1_service# service name
                servicePort: 80
     - host: domainName2.com
        http: 
         paths:   # paths is an array of different items
           - backend:
                serviceName: domainName_2_service # service name
                servicePort: 80  
```

## How to create an user

ref: https://discuss.kubernetes.io/t/how-to-create-user-in-kubernetes-cluster-and-give-it-access/9101/3

first create the CSR (certificate signed request)

```
openssl genrsa -out newUser.key 2048
openssl req -new -key newUser.key -out user1.csr
```

The admin should approve the csr:

```
openssl x509 -req -in user1.csr -CA /etc/kubernetes/pki/ca.crt -CAkey /etc/kubernetes/pki/ca.key -CAcreateserial -out newUser.crt -days 500
```

next create the role or cluster role

then create the role-bindings

use it:

```
kubectl config set-credentials newUser --client-certificate=/root/newUser.crt --client-key=newUser.key
```

```
kubectl config set-context newUser-context --cluster=kubernetes --namespace=test-namespace --user=newUser
```

### Howto: Nodes
 
 To get the cluster info
 
 ```
 kubectl cluster-info
 ```
 
 To get the more info about nodes
 
 ```
 kubectl get nodes -o wide
 ```
 
 the '-o wide' is for getting extra info, like the node's IP, OS images ...
 
 ```
k8s@terminal:~$ kk get node -o wide
NAME               STATUS   ROLES                  AGE   VERSION   INTERNAL-IP      EXTERNAL-IP   OS-IMAGE             KERNEL-VERSION     CONTAINER-RUNTIME
cluster1-master1   Ready    control-plane,master   90d   v1.23.1   192.168.100.11   <none>        Ubuntu 20.04.3 LTS   5.4.0-81-generic   containerd://1.5.5
cluster1-worker1   Ready    <none>                 90d   v1.23.1   192.168.100.12   <none>        Ubuntu 20.04.3 LTS   5.4.0-81-generic   containerd://1.5.5
cluster1-worker2   Ready    <none>                 90d   v1.23.1   192.168.100.13   <none>        Ubuntu 20.04.3 LTS   5.4.0-81-generic   containerd://1.5.5 
```
 
 to get the nodes with their labels
 
 ```
 kubectl get nodes --show-labels
 ```
 
 To add a label to a node:
 
 ```
 kubectl label -h # to get examples
 kubectl label node cluster1-worker1 security=apparmor
 ```


## kubernetes recovery and backups

reference: https://kubernetes.io/docs/tasks/administer-cluster/configure-upgrade-etcd/#backing-up-an-etcd-cluster

reference: Disaster Recovery for your Kubernetes Clusters [I] - Andy Goldstein & Steve Kriss, Heptio : https://www.youtube.com/watch?v=qRPNuT080Hk

refernce: https://github.com/etcd-io/etcd/blob/master/Documentation/op-guide/recovery.md

autoscaling: https://learnk8s.io/kubernetes-autoscaling-strategies
 

## Howto: build a Kubernetes cluster

https://github.com/kelseyhightower/kubernetes-the-hard-way
 
https://github.com/robertojrojas/kubernetes-the-hard-way-raspberry-pi

https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/install-kubeadm/
 
https://www.youtube.com/watch?v=uUupRagM7m0&list=PL2We04F3Y_41jYdadX55fdJplDvgNGENo&index=1
 
https://github.com/mmumshad/kubernetes-the-hard-way
 
 
## Howto: debug pods
 
In need to debug the container application container use Crictl and Nerdctl and debug the issue quickly
 
ref: https://github.com/kubernetes-sigs/cri-tools/blob/master/docs/crictl.md
 

## Howto: know running config of api-server
 
ssh the master node, 
 
 ```
 ps aux | grep kube-apiserver
 ```
 
## Howto: kubernetes dashboard
 
 ref: https://github.com/kubernetes/dashboard/tree/master/docs
 
## Howto: etcd
 
For handling etcd directly, there is need for identifcation, and easy way to get it is checking into the kube-apiserver.yaml, 
 for what it is using:
 
 ```
cat /etc/kubernetes/manifests/kube-apiserver.yaml | grep etcd
    - --etcd-cafile=/etc/kubernetes/pki/etcd/ca.crt
    - --etcd-certfile=/etc/kubernetes/pki/apiserver-etcd-client.crt
    - --etcd-keyfile=/etc/kubernetes/pki/apiserver-etcd-client.key
    - --etcd-servers=https://127.0.0.1:2379 # optional since we're on same node****
 ```
 Now you can use it in your command for etcd.
 
 So, to read directly a secret mysecret, in a namespace mynamespace it would be: 
 
 ```
 user@cluster-master:~# ETCDCTL_API=3 etcdctl \
--cert /etc/kubernetes/pki/apiserver-etcd-client.crt \
--key /etc/kubernetes/pki/apiserver-etcd-client.key \
--cacert /etc/kubernetes/pki/etcd/ca.crt get /registry/secrets/mynamespace/mysecret
 
 ```
 
 
## Howto: Update Cluster OS

For a given node you drain all its workloads, so it's workload is migrated (killed and recreated) to other nodes in the cluster, for this use the command:

```
kubectl drain node-i
```

With this the node is marked as unschedulable, meaning no works can be scheduled in it, until stated otherwise.

At this point the node can be taken down and updated. 

Once launched again the node can be maked as schedulabe again, with:

```
kubectl uncordon node-i
```
### troubleshooting working nodes

https://kubernetes.io/docs/tasks/debug-application-cluster/debug-cluster/

I would try:

```
>ssh <worker>

>ps -ef | grep kubelet

>systemctl status kubelet.service -l

>journalctl -u kubelet -f

>systemctl daemon-reload

>systemctl restart kubelet
```


## Playgrounds:

MINIKUBE. - 
Minikube is a single node local kubernetes cluster - with this you can create an all-in-one kubernetes setup.
 
https://labs.play-with-k8s.com/

https://cloud.google.com/community/tutorials/developing-services-with-k8s

https://kubernetes.io/docs/tutorials/kubernetes-basics/create-cluster/cluster-intro/

https://www.katacoda.com/courses/kubernetes/playground

https://kodekloud.com/p/game-of-pods


links: 

https://github.com/kubernetes/community

https://www.youtube.com/watch?v=X48VuDVv0do

https://github.com/dysinger/learn-minikube

https://github.com/lucassha/CKAD-resources

https://medium.com/bb-tutorials-and-thoughts/practice-enough-with-these-questions-for-the-ckad-exam-2f42d1228552

https://kubernetes.io/docs/reference/kubectl/cheatsheet/

https://github.com/dysinger/learn-minikube
 
https://github.com/dgkanatsios/CKAD-exercises

https://www.linkedin.com/pulse/my-ckad-exam-experience-atharva-chauthaiwale/

https://codeburst.io/resource-creation-tips-for-the-kubernetes-cka-ckd-certification-exam-740b70a13f97

https://www.nginx.com/

http://www.haproxy.org/

https://doc.traefik.io/traefik/

https://www.kube-router.io/

https://docs.projectcalico.org/getting-started/kubernetes/

https://romana.io/

https://kubernetes.io/docs/tasks/administer-cluster/network-policy-provider/weave-network-policy/

https://www.gluster.org/

https://flocker.readthedocs.io/en/latest/kubernetes-integra

about Helm: https://www.youtube.com/watch?v=-ykwb1d0DXU

https://www.youtube.com/watch?v=90kZRyPcRZw&t=462s

https://www.youtube.com/watch?v=X48VuDVv0do

https://www.youtube.com/watch?v=fy8SHvNZGeE

https://github.com/ContainerSolutions/kubernetes-examples

https://github.com/kubernauts/practical-kubernetes-problems

https://kubernetesbyexample.com/

https://github.com/NodyHub/docker-k8s-resources/tree/master/k8s-pods

autoscaling: https://learnk8s.io/kubernetes-autoscaling-strategies
 
## More advanced topics: 
 
- Five Technical Challenges to Optimize Kubernetes for 5G Deployments: https://platform9.com/blog/five-technical-challenges-to-optimize-kubernetes-for-5g-deployments/
- **Kubernetes Networking Intro and Deep-Dive - Bowei Du & Tim Hockin, Google**  https://youtu.be/tq9ng_Nz9j8
- **Kernel-bypass techniques for high-speed network packet processing** https://youtu.be/MpjlWt7fvrw
- **DPDK deep-dive** https://youtu.be/VJ8CVN3oXMw
 
Understanding kubernetes by breaking it down: https://youtu.be/90kZRyPcRZw?list=RDCMUCvqbFHwN-nwalWPjPUKpvTA
 
 
