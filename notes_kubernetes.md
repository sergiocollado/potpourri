

# Preface

In a Virtual Machine, an hypervisor is the sw layer that detaches the dependencies of an operating system with its undelingin hardware and allows several virtual machines to share that same hardware. This is know as virtualization, 

Anyway for an application all its dependencies from the sw and os, are there. Also running several applications in a single VM, has another issue, applications that share dependencies are not isolated one of each other applications, and the resources of one application can estarve another application. 

One way to overcome these issues is to implement abstraction at the application level and its dependencies. So the trick is to virtualize the user space. That is what containers are, isolated user spaces, that run application code. Containers are much lighter than VM because they don't replicate the operating system. And can be created and destroyed very fast, because they only need to handle the processes needed for the application, and not all the OS kernel. 

Another advantage is that containers make very easy to build applications that use the microservices design pattern, that are loosely coupled, fine grained components and with modular design, this allows an easy scale, and upgrade of components of the applications without changing the application as a whole. 

An application and its dependencies, are called an image.  Software is needed to build the images, for example: Docker. **Docker** is an open source project that allows you to run applications in containers. Although it doesn’t have a way to orchestrate those applications. 

**Kubernetes** is an application for deploying containerized applications.  Kubernetes is a solution for container management and orchestations. The apps in them need to communicate over the network. Also, needs to be some network mechanism that makes it possible for the containers to find each other. 

Kubernetes handles the deployment, scaling, load balancing, monitoring and logging of containerized applications. 

Some of its features are:

 - Automatically schedules containers based on resources
 - Self-healing. Replaces and reschedules containers from failed nodes.
 - Horizontal scaling: - scales automatically or manually.
 - Service discovery
 - Load balancing 
 - Automated rollbacks and rollaoust
 - Configuration managements
 - Storage orchestration
 - Batch execution.

# How do Kubernetes works?

Each thing Kubernetes manages is viewed as an object. And it’s attributes and states can be changed. Kubernetes works with declarative management, so the expected state of each object has to be defined. And kubernetes, will handle how to have that object in that declared state.

Kuberneters objects have two elements. An object spec, that defines the desired object state. And the object status is just the current state of each object, provided by the Kubernetes control plane.  The Kubernetes control plane are the different system processes that collaborate to make a cluster work. 

The basic object for the kubernetes model is known as a **Pod**. Those are the smallest deployable kubernetes objects. A pod is the environment, in which the containers live. 

A Pod, is a group of containers that share storage and networking (all the containers share memory volumes and share the same IP).

And a Pod can have one or more application containers (like docker or others). In case of more than one container, those will share resources. Each pod has an unique IP address. In case of several containers within a Pod, those will share the network namespace, including IP address and ports, and they can communicate through the local host. A Pod can also define a set of storage  volumes to be shared among its containers. 

reference: https://kubernetes.io/docs/concepts/workloads/pods/

For working with kubernetes, we work through the kube-API server. This component will allow us to declare commands to view or change the state of the cluster. 

kubctl command - connect to kubeAPI server. Is the kuberntetes Command Line interface client. To manage the cluster and its applications. 

ETCD is the cluster database and it stores the state of the cluster. 

Kube-scheduler. It schedules pods into the nodes. 

Kube-controller. It monitors the state of the cluster. When the current state of the cluster doesn’t match the desired state, it will try to get to the desired state. 

Kube-cloud manager manages controllers that interact with underlying cloud providers. 

Kubelet, is the agent of Kubernetes, in each node. 

Kube-proxy  handles network connectivity among the pods in the cluster.

KuberAdm, that can automate much of the initial setup of a cluster.


All kubernetes objects are identified by an unique name and an unique id (uid). And the objects are defined in manifest files (in YAML or JSON format). And those files define a desired state for the object, like name and container image. 


## Kubernetes object model

In Kubernetes objects, represent different persistent entities, that represent:
The containerized apps that are running and in which node.
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
 
 
### Labels

Labels are pairs of key and value identifiers. Labels are used to identify and select objects. So Labels do not provide uniqueness. Controllers use labels to group togethers in a set decoupled objects, intead fo idetifing them by names.

### Label Selectors

there are two types of label selectors: equality-based ( = , ==, != ) and set-based selectors ( in, notin, exists, does not exist).
 
### Namespaces

A cluster resources can be divided using **namespaces**. The name of resources created inside a given namespace is unique, but no across namespaces. 

k8s generates four default namespaces: kube-system, kube-public, kube-node-lease and default. 

- default: contains objects created by admins and developers.
- kube-system: contains objects created by k8s system, mostly the control plane agents.
- kube-public: special namespace which is unsecured and readable, used to expose information publically.
- kube-node-lease: contains the node lease objects, for node heartbeat data.  

### ReplicaSet Controllers

A ReplicaSet controller ensures that a population of Pods, all identical, are running at the same time.

### Deployment Controllers

Deployments let you do declarative updates to ReplicaSets and Pods. In fact, Deployments manage their own ReplicaSets to achieve the declarative goals you prescribe, so you will most commonly work with Deployment objects.

Deployments let you create, update, roll back, and scale Pods, using ReplicaSets as needed to do so. For example, when you perform a rolling upgrade of a Deployment, the Deployment object creates a second ReplicaSet, and then increases the number of Pods in the new ReplicaSet as it decreases the number of Pods in its original ReplicaSet.  Deployments are better suited to state-less applications like web front-end.

reference: https://kubernetes.io/docs/concepts/workloads/controllers/deployment/

Replication Controllers perform a similar role to the combination of ReplicaSets and Deployments, but their use is no longer recommended. Because Deployments provide a helpful "front end" to ReplicaSets.
In the need to deploy applications that maintain local state, StatefulSet is a better option. A StatefulSet is similar to a Deployment in that the Pods use the same container spec. The Pods created through Deployment are not given persistent identities, however; by contrast, Pods created using StatefulSet have unique persistent identities with stable network identity and persistent disk storage. So for persistent storage, the StatefulSet is the best option, defining a network storage. 
If you need to run certain Pods on all the nodes within the cluster or on a selection of nodes, use DaemonSet. DaemonSet ensures that a specific Pod is always running on all or some subset of the nodes. If new nodes are added, DaemonSet will automatically set up Pods in those nodes with the required specification. The word "daemon" is a computer science term meaning a non-interactive process that provides useful services to other processes in the background. A Kubernetes cluster might use a DaemonSet to ensure that a logging agent like fluentd is running on all nodes in the cluster. DeamonSets are useful, if you want to have logging and auditing processes in all the nodes of your cluster. 
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

## kubectl command

https://kubernetes.io/docs/reference/kubectl/cheatsheet/

It is the command used to communicate with the kubernetes cluster, with the kube-API server, so the kubectl commands are transformed in APIs calls.

Before anything the kubectl must be configured with the location and credentials of a given kubernetes cluster.  The configuration is  in a file in the home directory $HOME/.kube/config. The config file has the cluster name and the cluster credentials.  To edit this use the command: --kubeconfig

If you want to view the configuration, just use the command:  'kubectl config view.

Or to get the cluster info,and the services running in it,  use the command: 'kubectl cluster-info'

Sintaxis

``` kubectl [command] [type] [name] [flags] ```

 - **Commands**: get, describe, logs, exec …
 - **Type**: pods, deployments, nodes …


For example:

``` kubectl get pods -- get a list and info about the pods. ```

```kubectl describe pod <pod_name> -- get detailed info about a given pod. ```

## Services

Services are the process that expose a set of pods to the outside of the cluster. 

Rationale: The pods in a cluster have IPs that are ephemeral, if a pod is terminated and a new pod is created, this new pod doesn't really need to have the same IP.
To overcome this situation, the Service abstraction is provided. Given a set of pods, defined by labes or selectors, those can be addresses by means of a Service. 

reference: https://kubernetes.io/docs/concepts/services-networking/service/

## kube-proxy

kube-proxy is a daemon in all the worker nodes, that monitorices the master node server api, to check for the addition or removal of services. Each kube-proxy, handles the ip-tables, to manage the traffic for each ClusterIP and fordward it to the suitable Service endpoint. 

## Service discovery

There are two ways to discover a service:

- enviromental variables: when a Pod starts the kubelet daemon running in that node defines a set of enviromental variables that defines the active services. Be careful with this method, due if a Service is created after the Pod, this service will not be identifed.
- DNS: kubernetes has an add-on for DNS, which creates a DNS record for each service. This is the recomended solution.

reference: https://kubernetes.io/docs/concepts/services-networking/service/#discovering-services

## Services types:


reference: https://kubernetes.io/docs/concepts/services-networking/service/#publishing-services-service-types

## Example of a Service configuration file:

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

<hr>
# HOW TO's

## howto Pods

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
```

to create the Pod, use the command:

```
kubectl create -f pod-defintion.yml
```

to verify that the pod has been created, use:

```
kubectl get pods
```

to get more detailed info use:

```
kubectl describe pod myapp-pod 
```


## howto Deployments

Commands to create deployments:

**Declaratively**:

```
 kubectl apply -f <deployment_file.yaml>
 ```

**Imperatively**:

```
kubectl run <deployment_name> \
  --image  <image>:<tag>
  --replicas N \
  --labels <key>=<value> \
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

ejample : 

  ```kubectl scale --replicas=3 deployment nginx-deployment```

Also, you can perform autoscaling 

 ```kubectl autoscale deployment <deployment_name>  --min=N --	max=M --cpu-percentaje=P ```

To define a deploy period to perform another scale action:

--horizontal-pod-autoscaler-downscale-delay

## Howto Rollout

A deployment's rollout is triggered if and only if the deployment's Pod template (that is, .spec.template) is changed,

To check the rollout status:

```
kubectl rollout status deployment.v1.apps/nginx-deployment
```

To view the rollout history:

```
kubectl rollout history deployment nginx-deployment
```


## Howto Update deployments


To update a deployment:

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

To a given revision number

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


## Jobs

The Job controller creates one or more Pods required to run a task. When the task is completed, Job will then terminate all those Pods. A related controller is CronJob, which runs Pods on a time-based schedule. Jobs run a task up to its completion, rather than a desired state. 
There are two main jobs definitions, parallel and non-parallel.
 
Non-parallel jobs cretate one pod at a time, and that pod, will be recreated if it doesn’t finish the job successfully. The condition to be successful is to finish the job, or that the job has run a given number of times. 
Parallel jobs are those that work on parallel, where multiple pods are scheduled to work on the same job at the same time. They also have a completion count to satisfy. They are used when jobs have to be done more than once. A second type of parallel jobs are jobs with worker queues, in this each pod, work on several items from a queue, and then exits when there are no more items.  
To create a non-parallel job:

```kubectl apply -f <job-file>```

Or using the run command:
‘’’ kubectl run <job-file> pi --image perl --restart Never -- perl -Mbignum bpi -wle “print bpi(2000)” ‘’’ 
To inspect jobs 
‘’’’ kubectl describe job <job-name> ‘’’
‘’’ kubectl get pod -L <job-name=my-app-job>
“-L” is the label selector.
To scale jobs.
‘’’ kubectl scale job <job_name> --replicas <value> ‘’’
To delete a job
‘’’Kubectl delete -f <job_name>’’’ 
‘’’ kubectl delete job <job_name>’’’ 
 
Or if retain a job is needed, use the cascade flag set to false
‘’’ kubectl delete job <job_name> --cascade false ‘’’ 
 
To schedule a job, CronJobs are used.
CronJobs use the required schedule field, which accepts a time in the Unix standard crontab format. All CronJob times are in UTC:
The first value indicates the minute (between 0 and 59).
The second value indicates the hour (between 0 and 23).
The third value indicates the day of the month (between 1 and 31).
The fourth value indicates the month (between 1 and 12).
The fifth value indicates the day of the week (between 0 and 6).
The schedule field also accepts * and ? as wildcard values. Combining / with ranges specifies that the task should repeat at a regular interval. In the example, */1 * * * * indicates that the task should repeat every minute of every day of every month.
 
 
 
 
## Pod Networking

In the kubernetes model, each pod is assigned a single IP address. And the containers in that pod, contain the same ip space, including that IP address. 
**Services** give pods stable IP addresses. A kubernetes service is an object that creates a dynamic collection of IP addresses, called endpoints, that belog to pods, that match the services label selector. 
STORAGES ABSTRACTIONS
**Volumes** are the method by which you attach storage to a Pod.
Some Volumes are ephemeral, meaning they have the same life span as the pod they are attached to. Other volumes are persistent, meaning they can outlive a Pod. 
 
 
 
# Authentication, authorization and admission control

To access and manage kubernetes there are three stages:

- authentication: logs a user.
- authorization: authorizes the requests API.
- admission control: software modules that can handle requests based on extra information.

 
MINIKUBE. - 
Minikube is a single node local kubernetes cluster - with this you can create an all-in-one kubernetes setup.
 

tutorials:

https://kubernetes.io/docs/tutorials/kubernetes-basics/create-cluster/cluster-intro/

https://github.com/dysinger/learn-minikube

https://medium.com/bb-tutorials-and-thoughts/practice-enough-with-these-questions-for-the-ckad-exam-2f42d1228552

https://kubernetes.io/docs/reference/kubectl/cheatsheet/
 
