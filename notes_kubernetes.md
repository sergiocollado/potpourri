

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

It is possible to create custom namespaces, for example one named 'dev" for development, and other 'prod' for production purpouses.

### Replication Controller

 A replication controller allow us to have several instances of a pod, so in case a pod dies, a new one can replace it. Thus allowing us to have a high availability service.
 
 A replication controller can help us also, when we want to have several pods, sharing work between them. 
 
 A replication controller will monitor the specified pods, and in case any would fail, it would replace it by a new one. 
 
 
### ReplicaSet Controllers

A replica set controller is the replication controller evolution. 

A ReplicaSet controller ensures that a population of Pods, all identical, are running at the same time.

A ReplicaSet can be used to monitor a group of Pods, that are already running, and in case those are not created, the replicaset can create them. the role of the replicaset is to monitor the pods, and if any were to fail, replace them by new ones. The way to identity the pods to monitor is by means of matching labels (with the matchLabel filter), defined in the definition of the Replica set.

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

### Security contexts

Some secure settings can be define at the container run engine level or at the pod level. If configured at the pod level, those settings will be defined for all the containers within the pod. If defined in both places, the container and the pod, the pod settings will override the container settings.

### Service Accounts

There are two types of accounts in kubernetes, user accounts and service accounts. Service accounts are for service programs, like prometheus or jenkins. 

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

it you want to copy a pod's definition into a file, use:

```
kubectl get pod <pod-name> -o yaml > pod-defintion.yml
```

To edit a pod's properties use:

```
kubectl edit pod <pod-name>
```

## howto Configuration Maps

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
#configmap.yml definition
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
kubectl create secret generic <secre-name> --from literal=<key>=<value>
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
kubectl create -f secret.data.yml
```

```
#secret-data.yml
apiVersion: v1
kind: Secret
metadata: 
    name: app-secret
data: 
    DB_HOST: 2astasefq   # the secret must be written in encripted format.
    DB_USER: 45t6yuki
    DB_PASSWORD: p7ytgfcdew
```

to encode the strings, in a linux machine use:

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

### Security contexts

Some secure settings can be define at the container run engine level or at the pod level. If configured at the pod level, those settings will be defined for all the containers within the pod. If defined in both places, the container and the pod, the pod settings will override the container settings.


to add the Security Context at the container level, add it in the spec of the container.

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

to add the security context add the POD level, add it ad the specs of the pod

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


## howto Replica Controller


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


## howto Replica Set

A example file that defines a replica controller.

```
# replicaset-definition.yml
apiVersion: app/v1
#WATCHOUT: the correct version for a rs is the app/v1
kind: ReplicationController
metadata:
    name: myapp-replicaset
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
another way to scale a replica set, is to run the 'scale' command: 

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

## howto Deployments

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

https://labs.play-with-k8s.com/

https://kubernetes.io/docs/tutorials/kubernetes-basics/create-cluster/cluster-intro/

https://github.com/dysinger/learn-minikube

https://medium.com/bb-tutorials-and-thoughts/practice-enough-with-these-questions-for-the-ckad-exam-2f42d1228552

https://kubernetes.io/docs/reference/kubectl/cheatsheet/
 
