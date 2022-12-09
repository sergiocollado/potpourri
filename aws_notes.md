## FOREWORD:

These are my personal notes, on the AWS Cloud. The aim of this document,is to clarify my ideas, by means
of writting them down, and have a resource where quickly find answers to my doubts, based on my experience. 

reference: https://docs.aws.amazon.com/

Short Introductory videos: https://aws.amazon.com/es/training/intro_series/

and: https://www.aws.training/LearningLibrary

also:  https://aws.amazon.com/getting-started/

and also: https://www.aws.training/LearningLibrary?tab=digital_courses

To create architecture diagrams, use: https://app.diagrams.net/

AWS architecture examples: https://aws.amazon.com/architecture/reference-architecture-diagrams

# [AWS](https://aws.amazon.com/)

Amazon Web Services.

AWS free tier: https://aws.amazon.com/free/


## Regions and availability zones (AZ)

AWS has different locations around the world, where it locates its servers. Inside each region, there are several availability zones,
in different locations, with different power supplies, facilities ... 


## AWS IAM (Identity and Access Management) and policies


IAM provides the right users, the right access, the right resources at the right time.

https://docs.aws.amazon.com/IAM/latest/UserGuide/introduction.html

there are two concepts that need to be clarified:
- Authentication: the act of validating that an user is who they say they are.
- Authorization: the process of giving users permissions to access a given resource or service

https://docs.aws.amazon.com/IAM/latest/UserGuide/intro-structure.html#intro-structure-authentication

IAM identities are three:
- users (represents an user or an application)
- groups (a collection of IAM users. A group is a way to attach policies to multiple users at one time)
- roles (roles are assumed, doesnpt really belong to an user or application. An IAM user can assume a role to temporarily take on different permissions for a specific task.)

https://docs.aws.amazon.com/IAM/latest/UserGuide/id.html

ARN: amazon resouce name

```
arn:<partition=aws>:<service>:<region>:<account_id>:<resource_id>
arn:<partition=aws>:<service>:<region>:<account_id>:<resource_type>/<resouce_id>
arn:<partition=aws>:<service>:<region>:<account_id>:<resource_id>:<resource_id>
```

### Policies 

These identites are matched with identities policies .

IAM policies allow acess to resources and be as granular as desired.  Different resources can be addresed with the ARN (Amazon Resource Name) 

There two types of policies: identity policies and resources policies.

policies are defined by three mandatory elements
- effect: specifies if the effect results in an "Allow", or and explicit "Deny" or and implicit deny in case nothing is explicitly defined.
- action: specifies the speciffic activities that are allowed or denied (each service have different actions -consult documentation)
- resource: speficies the object or objects that the policy refers to. It is spefied with the ARN

https://docs.aws.amazon.com/IAM/latest/UserGuide/reference_policies_elements_effect.html

https://docs.aws.amazon.com/IAM/latest/UserGuide/reference_policies_elements_action.html

https://docs.aws.amazon.com/IAM/latest/UserGuide/reference_policies_elements_resource.html

```
{
  "Version": "2012-10-17",
  "Statement": {
    "Effect": "Allow",
    "Action": "ec2:RunInstances",
    "Resource": "*"
   }  
}
```

and other optional elements:
- principal specifies the principal (who) that is allowed to access to the resource
- condition: specify conditions when the policy is in effect.

https://docs.aws.amazon.com/IAM/latest/UserGuide/reference_policies_elements_principal.html

https://docs.aws.amazon.com/IAM/latest/UserGuide/reference_policies_elements_condition.html

https://docs.aws.amazon.com/IAM/latest/UserGuide/access_policies.html

an example policy:

```
{
  "Version": "2012-10-17",
  "Statement": {
    "Effect": "Allow",
    "Principal": {"AWS": "arn:aws:iam::1234532349534:root"}
    "Action": "ec2:RunInstances",
    "Resource": "*",
    "Condition": {
         "StringLikeIfExists": {
          "ec2:InstanceType": [
             "t1.*",
             "t2.*",
             "m3.*"
     ]}}
   }  
}
```

remember: `EPARC
- E effect
- P principal
- A action
- R resource
- C condition


Also, there are resource-based policies and identity-based policies. and there are two types of identity-based policies: managed and in-lined policies.

Inline policies are created and embedded into IAM users, groups or roles. they use to be created when the identity is created and deleted when the identity is deleted.

Managed policies are policies that you can attach to users, groups and roles. Within the managed policies there are two types: AWS managed policies and custom managed policies.

Remember always to use the principle of the least privilege.

roles are used to delegate access. In order to delegate permissions, it is needed to grant permitions through what is called a trust policy. A trust policy specifies 
which trusted account members, or principals are allowed to assume the roles (it is really a resource policy as it is attached to a resource). Also it is needed the 
permissions policy attached to the identity, allowing the identity to assume the role, (sts:AssumeRole), the way the role is assumed is through the AWS Security Token Service (STS). 

https://docs.aws.amazon.com/IAM/latest/UserGuide/id_roles.html

an example of a trust policy is:

```
{
  "Version": "2012-10-17",
  "Statement": {
     "Effect": "Allow",
     "Principal": {
        "AWS": "arn:aws:iam::12345677654:root"   #account identifier
     },
     "Action": "sts:AssumeRole",
     "Condition": {}
  }
}
```

Roles are important because they are more secure, due roles, only provide short-term credentials. Roles are designted to delegate access to users and applications, and if needed this access can be easily revoqued. Also roles are reusable. Roles enforces the least previleges policy control. 

https://docs.aws.amazon.com/IAM/latest/UserGuide/id_roles_terms-and-concepts.html

https://docs.aws.amazon.com/IAM/latest/UserGuide/id_roles_create.html

https://docs.aws.amazon.com/IAM/latest/UserGuide/id_roles_use_switch-role-console.html

https://docs.aws.amazon.com/IAM/latest/UserGuide/id_roles_use_switch-role-ec2.html

https://docs.aws.amazon.com/IAM/latest/UserGuide/reference_aws-services-that-work-with-iam.html

https://aws.amazon.com/identity/federation/

IAM roles are especially important in the following scenarios: 

Providing access to services like Amazon EC2 that need access to other AWS services.
Providing access to users in other AWS accounts access to resources in your AWS account. 
Providing access to identities that are stored externally through a corporate identity provider or a social media website. 
https://docs.aws.amazon.com/IAM/latest/UserGuide/id_roles_common-scenarios.html


The AWS Security Token Service (STS) is a web service that enables you to request temporary, limited-privilege credentials for AWS Identity and Access Management (IAM) users or for users that you authenticate (federated users).

https://docs.aws.amazon.com/IAM/latest/UserGuide/id_credentials_temp.html

You may also want more information about the Assume Role API call

https://docs.aws.amazon.com/STS/latest/APIReference/API_AssumeRole.html


IAM, control access to AWS resources. Each IAM identity gets it own set of cryptographic keys. It sets the users privileges to control actions.
Accesses can be time controlled: permanent or short term.

IAM, enables EC2 roles, that means, that EC2 instances, can get roles.

It can handle MFA(Multy Factor Authentification). FOBs cost something, and there is also a virtual FOB for Android&iOS.

It also have STS(Security Token Service), is somewhat similar to Kerberos, in the sense it can expire AWS resource access.


Policies examples:

1st example:

```
{
  "Version": "2012-10-17",
  "Statement": [
    {
       "Sid": "ListObjectsInBucket",
       "Action": [
          "s3:ListBucket"
          ],
        "Effect": "Allow",
        "Resource": "arn:aws:s3:::socilamediabucket1"
    },
    {
       "Sid": "ObjectActions",
       "Action": [
          "s3:*Object"
          ],
   
   "Effect": "Allow",
        "Resource": "arn:aws:s3:::socilamediabucket1/*"
    }
  ]
}
```


2nd example:


```
{
  "Version": "2012-10-17",
  "Statement": [
    {
       "Sid": "StartStopIfTags",
       "Action": [
          "ec2:DescribeTags",
          "ec2:StartInstances",
          "ec2:StopInstances"
        ],
        "Effect": "Allow",
        "Resource": "arn:aws:ec2:us-east-2:123546344567:instance/*",
        "Condition": {
           "StringEquals":  {
              "ec2:ResourceTag/": "Project": "DataAnalytics"
           }
        }
    }
  ]
}
```


More info:

http://docs.aws.amazon.com/IAM/latest/UserGuide/introduction.html

http://aws.typepad.com/aws/2011/08/aws-identity-and-access-management-now-with-identify-federation.html

### AWS SSO (Single Sign On access) - 
 to manage user permissions in all the owned aws accounts, in a service named AWS Organizations. 
 
https://aws.amazon.com/single-sign-on/

### AWS Cloud Trail: 
  to monitor resources activities. 
  
  https://docs.aws.amazon.com/awscloudtrail/latest/userguide/cloudtrail-user-guide.html
  
  https://docs.aws.amazon.com/IAM/latest/UserGuide/reference_policies_examples_iam-credential-report.html

# TODO: review trust policies and passRole ... 

### Best Practices: 

-Once you created the Master account, create an IAM_root_account, to access your thing, this is actually a safe/falloff
measurement.
-Create master accounts, for the groups: Production, Dev, Test. Never use the root user.
- Use roles whenever possible.
- Remove old credentials (password and access keys, check them in the credentials report)
- Use IAM access analyzer.


# AWS S3: Simple Storage Service.

references:
- http://docs.aws.amazon.com/AmazonS3/latest/gsg/GetStartedWithS3.html
- https://aws.amazon.com/es/documentation/s3/
- http://docs.aws.amazon.com/AmazonS3/latest/dev/Welcome.html

## INTRODUCTION TO S3(Simple Store Service):

In S3 (Simple Storage Service) you can put any data file. They are organiced in "Buckets".
- Bucket names are globally unique, so you have to take one with a name non taken yet.

Buckets, are the containers for storing your objects (files), and all the objects, must be
stored in a Bucket. 

If you have the an object named: 'pics/sergio.jpg', and is stored in the bucket 'Haway_holidays',
then you can address it with the URL: 'http://Haway_holidays.s3.amazonaws.com/pics/sergio.jpg'.

You can configure also a Buckets, so every time an object is added, an unique ID is generated and
assigned to the object.

You can have one, or more buckets, for each bucket you can manage its groupaccess, 
thus enable users, and rights to upload, delete, change ... also you will have access
to the logs of those buckets. 
You can control the geographic zone, where AWS will store the buckets and its contents.

Watch out, because each bucket name must be unique in AWS, and once you create it, 
you can not change the name. Its recomended that buckets comply with DNS naming
convections

By default, buckets are private, you have to edit the privileges if you need to.

You can choose a geographical region where AWS S3, will store your Buckets. You
should use a region, to optimize latency.

## Different S3 tiers storeing policies

 - S3 standard - ( "11 9's") - that means that if you have 1 million files stored there, you will loose one, every 10.000 years.It comes at greatest cost, but is the default.
 - S3-IA - Infrequent Access
 - S3- One zone IA - Infrequent Access
 - S3 Intellingent tiering
 - S3 Glacier
 - S3 Glacier Deep Archive

## S3 secutiy and encryption

you can set bucket policies and acess control:

 - encryption in transit: with SSL/TLS 

Encryption at rest: 
 - SS3-S3: S3 managed keys
 - SSE- KMS: key managed service keys 
 - SSE-C: server side encryption with customer keys

Client side encription: user encrypts the files previous to upload them.

## ACCESS CONTROL:

Objects, also have types of access control:

 - IAM policies  (http://docs.aws.amazon.com/IAM/latest/UserGuide/introduction.html)
 - Bucket policies
 - ACLs(Access Control Lists) - AWS console
 - Query string autentification - gives expiring acess.
 - AWS management console. (sign in: https://console.aws.amazon.com/s3.)

S3 buckets can be configured to create acess logs, wich will log all request made to the S3 bucket. This can be send to another bucket, even another bucket in another accout.

### POLICIES
Bucket policies, provide a centraliced access control to buckets and objects based on a variety of conditions.
For example it can create a policie that gives a user write access:

 - To a certain bucket.
 - From certain account's network
 - During certains hours per day.
 - From an accounts custom application (as identified by a user agent string)

Unlike ACL(access control lists), that only grant permissions to a given object, policies can grant/deny
permisions across all (or a subset) of objects within a bucket.

Policies are defined in the access policy languaje.
 
More info about Buckets: http://docs.aws.amazon.com/AmazonS3/latest/dev/UsingBucketPolicies.html </br>
More info about ACLs: http://docs.aws.amazon.com/AmazonS3/latest/dev/S3_ACLs_UsingACLs.html </br>
 
The bucket also saves some information about the files: type, creation date, ... (meta data)
More info in: http://docs.aws.amazon.com/AmazonS3/latest/dev/UsingMetadata.html
   
## PRICING:

https://aws.amazon.com/s3/pricing/
http://calculator.s3.amazonaws.com/index.html

Starts around 0.0X$ per GB/month for "standard" S3 - the fee gets cheaper, if you use more.

### Bandwith:

 - IN: FREE
 - OUT: Same Region: free
 - Out of region: Starts at 0.0X$ GB/month.
 - REQUEST al also costy: (PUT, GET, POST, LIST) - Starts at 0.00xx/1000 request.
   
Just have in mind, that data trasnsfer inside your region is **FREE!!!**
   
## Encryption S3

- Encryption in transit, with is achieved with SSL/TLS
- SSE-S3: Encription at rest (server side), achieved with s3 managed keys- SSE- S3 (SSE: server side encryption) Aws manages the encryption keys.
- SSE-KMS: AWS key manage service: AWS and client manage keys together: SSE-KMS
- SSE-C: Server Side encryption with customer provided keys: SSE-C
- Client side encryption. the client encrypts the file previously to its upload. 
   
 
## S3 WORM (write once read many) 
 
A **service Object lock**, is used to store objecto wit WORM and it can prevent objects to be deleted or modified by an ammount of time or indefinetly. This can help to meet regulatory requirements, or protection agaist deletion.

there are modes

- governance mode: it allows some special permissions to alter retention's object, or delete the object if necesary
- complient mode: a proctected object version can't be alterede, overwritten or deleted by any user, during the retention period. 

lock objects can be individual objectso or applied across a whole bucket. 

### Athena

https://docs.aws.amazon.com/athena/index.html

Is a service that lets you make sql queries to data in S3. it is serveles and price is per query. so it almost transform S3 in a database. 

Amazon Athena is an interactive query service that makes it easy to analyze data in Amazon S3 using standard SQL. Athena is serverless, so there is no infrastructure to setup or manage, and you pay only for the queries you run. To get started, simply point to your data in S3, define the schema, and start querying using standard SQL.

### Macie

https://docs.aws.amazon.com/macie/index.html

PII (Personal Identifiable Information) 

Mathie is a ML and NLP service to recognice in the storage PII or other sensitive data. It can be used to analize CloudTrail for suspicious activity or for compliance with PII, or/and preventing ID theft.

Amazon Macie is a fully managed data security and data privacy service that uses machine learning and pattern matching to discover, classify, and help you protect your sensitive data in Amazon S3.

### AWS Storage Gateway 

It is a physical or virtual appliance that can be used to cache S3 locally at a customer's site.

### AWS S3 FAQ
https://aws.amazon.com/s3/faqs/


# AMAZON ELASTIC CLOUD COMPUTING aka EC2

It is a service that allows to provision virtual severs on demand. Each virtual server requested in known as a EC2 instance. anything you can do with a traditional server can be done with a EC2 instance. EC2 instances are flexible, and can be configured acconrding the needs. they support a variety of OS, like linux or windows. to select a given operating system, we choose a AMI (Amazon Machine Image). It is possible to launch one or several AMIs and create serveral instances with the same configuration. It is possible to set the image type, size, memory and netwoking capabilities, even the underling hardware. Also the configuration can be done programatically and automated. 

EC2 service allows you to:

 - launch virtual machines in the cloud(EC2)- Elastic Cloud Computing
 - Storing data in virtual data drives (EBS)
 - Distributing load between machines (ELB) Elastic Load Balancing 
 - Scaling services using auto-scaling  groups(ASG)Auto Scaling Group
 
 for reference on the types of ec2 instances, check: 
 
 https://aws.amazon.com/ec2/instance-types/
 
 ### EC2 pricing models
 
  - On demand: fixed rate, and no commitments.
  - Reserved: provides a capacity reserve, with a discout. commintement 1 or 3 years.
      - standard reserved instances
      - convertible reserved instances
      - scheduled reserverd instances
  - On spot instances: its spare capacity that can be used. but the instance can be retrieved by AWS.
  - Dedicades hosts: dedicated physical servers, and you can use your own sw lincenses. Useful for regulatory requirements, that dont support multi-tenant virtualization.


### EC2 instances types
 
 //TODO.
 
 - **F1**  FPGA
 - **I3**  Hight Speed Storage
 - **G3**  Graphics Intensive
 - **H1**  High disk throuput
 - **T3**  Lowest cost, general purpose
 - **D2**  Dense storage 


### EC2 Security groups

A security group acts as a virtual firewall for your EC2 instances to control incoming and outgoing traffic. Inbound rules control the incoming traffic to your instance, and outbound rules control the outgoing traffic from your instance. When you launch an instance, you can specify one or more security groups.

All inbound traffic is blocked by default, outbound traffic is allowed.

And with security groups there is no way to blacklist a given port or a given IP. you need NACL for that.

reference: https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-security-groups.html

### EBS Elastic Block Storage

EBS (Elasting  Block Storage) provides storage for EC2

five types:

- **gp2, gp3**: General purpose (ssd). balance price and performace. Gp3 is x4 faster than gp2
- **io1, io2**: Provisioned IOPS (ssd). Optimized for great ammout of input/output operations. max 64000 IOPS -for databases & mission crítical applications
- **st1**: Throupout optimized hard disk drive (no ssd). max 500 IOPS - designed for throughput-intensive workloads. (big data, data warehouses ...)
- **sc1**: cold hard disk drive. lowest cost.  MAX 250 IOPS. 
- **standard**: magnetic. MAX 20-400 IOPs 


## Networking with EC2:

### ENI: Elastic Network Interface
 Elastic Network interface is a virtual network card - for basic day-to-day networking. 
### EN: Enhaced Networking
 Enhaced networking. Uses a single root i/o virtualization (SR-IOV),  to provide high networking capabilities on supported instance types. It vary speeds bewteen 10Gbps to 100 Gbps. 
### EFA: Elastic Fabric Adapter
 Elastic Fabric Adapter: a network device that you can attach to a EC2 intance, to accelerate high performance computing (HPC) and machine learning applications. 
 
## Optimiziong EC2 with placement groups

There are three types of placement groups
 - Cluster - grouping of instances in a same availability zone. Indicated for applications with low network latency and/or hight throughtput. (because the instances are closer)
 - Spread - Indivudal critical EC2 instances are spreaded in diferent hardware, so this is recommented when there are a small number of critical instances (it is more reliabably in case of hardware failure)
 - Partition - multipell EC2 instances have its own set of racks. So each rack has its own network and power source. This also makes the application more reliable in case of hardware failure.


## ELB (Elastic Load Balancer) 

there is 3 types of load balancer

- classic load balancer (CLB) (deprecated)
- Aplication Load Balancer (ALB) - these evaluate the layer 7, that is they work at HTTP level.They dont see directly the client IP and port, those are in the x-fordward-for-proto header.
- Network Load Balancer (NLB) - these work at layer 4, that is TCP. they are high performance, much better that the ALB. they see directly the client IP. 

You can set the load balancer as Internal(private) or External (public: internet-facing) 

Load Balancer also have health checks that allows to identify problems. 


## AUTO SCALING GROUPS (ASG)

this is a mechanism to scale computing instances, they can scale out (add instances) or scale in (remove instances.
Also add them to a load balancer.

to define a ASG, we need: 

- AMI + instace type
- EC2 user data
- EBS volumes
- Security Groups
- SSH Key Pair
- Min size, Max size, and initial instaces
- working network and subnets
- load balancer information 
- Scaling policies (CloudWatch alarms)

a very interesting feature, is that when an ASG(auto scaling group) works with a LB (load balancer) in case the load balancer health check detects an unhealthy instance that one can be terminated by the ASG and a new one launched. 

## EBS (Elastic Block Storage)

EBS (Elastic Block Storage) is a network drive to attach to the instances when they drive. 
it can be detached from one EC2 instance and attached to another.

They are defined by sotorage capacity and IOPS input output per second.

There are different types of EBS: GP2, GP3, IO1, STI, SCI

It is possible to get EBS snapshots, this is usefull for backups, or volume migrations.

Also is possible to use encrypted EBS volumes.
 

## ADVANCED FEATURES OF S3

 S3 also allows for:
 
  - light, static, website hosting.
  - Object squeduled expiration.
  - Encryption Options
  - Versioning
  - Logging
  - "Direct from browser" upload to s3
  - Multipart files upload
  - Requested pays
  - BitTorrent Support
   
- Simple static website hosting: You can rename to a domain you own  (Easy CNAMEd).
- Index, and Error documents support.
- key prefix routing rules.
- Oject expiration squeduling -live cicle management- 
- Encription options (SSE, SSL, or your own) [SSE: Server Side Encription]
- Versioning. Once is On, it can never can go back to Off, so you will be storing all your development. ##
- Logging: you can get IP, operations, dates, . Can be On/Off anytime. Watch out! store the logs, in another Bucket!
- Direct on brownser upload: You can grant users to directly upload to your bucket uses IAM/STS services to generate a url for

The bucket object. 5GB limitation on file size. ref -> http://aws.amazon.com/articles/1434
If you want to upload more than 5GB, you have to use multi-part files upload, that is just limited to SDK(Java, iOs,PHP, Ruby); 
the client chuncks the file into pieces. Loads each piece separately. Client closes file. S3 reassembles the file. This also allows
stop/star partial uploads. With this method the max file size is 5TB.

ref: http://docs.aws.amazon.com/AmazonS3/latest/dev/uploadobjusingmpu.html
 - Request payment. always if the client is a AWS registered partner/customer.
 - Bittorret support (P2P protocoll) max file size 5GB- ref: http://docs.aws.amazon.com/AmazonS3/latest/dev/S3Torrent.html
 
 
## First steps: 
 
The best is to migrate all static content to S3 (images, CSS, Javascript, HTML, etc...)- this relieves the load on your
EBS, so it can do more important tasks, with this, the cost of the EBS, is much more lower, and gets more performance.
   
The second step, is set up Glacier for archival, Control access, set up Livecicle policies, Investigate advanced users: 
like Website hosting, direct to S3 uploads.
 
log in main server server:

```bash
|___|  __|_  )
|_|   (     /
|___| ___||___|

<< sudo su -
cd /var/local/src

Gon ; s3tools.org/download
333
--íntasll from the commmand, get the link

 wget http:.... (he link copied proivied)
 
 >> mv download s3cmd.trg
 
  tax -xcvzf s3cmd.tgz
  
  cd s3cmd-1.5.0-alphay/
  
  Less install
  
  easte isnt way to install is : python .py instals
 
  s3cmd-1.5.0-alpha1
  ```
  
  we have provide the keys> using > credential needed, > access credenctials "Aceess Keys´2"
    
  intall the keys. 
  
  w3cdmd --help 
  s3cmd [feature] --help 

## RELATED SERVICES

S3 can be used with other AWS services:

- Elastic Compute Cloud: this service provides virtual compute resources in the cloud. Ref: https://aws.amazon.com/ec2/
- EMR: this service provides easy and cost effective processing of vast amounts of data. It uses hadoop framework running  on EC2 and S3
- AWS Import/Export: is a mail (not e-mail, it means mail, and actual envelop!)-  storage device, as RAID drive (Redundant Array of Independent Disks) so it can be uploaded in AWS. Ref: http://docs.aws.amazon.com/AWSImportExport/latest/DG/whatisdisk.html


# CLOUD FRONT
  
## INTRODUCTION to CLOUD FRONT:

Cloud Front is a CDN - Content Delivery Network.
It uses locations close to end user (Edges).
Other populars CDNs are Akamai, Level 3.

https://aws.amazon.com/cloudfront/

### DESCRIPTION:
- Resources of static website assests: Images, CSS, JS, HTML, JSON.
- Distributions: products, documents, data.
    - web distributinon
    - rtcp distributions: video streaming

- Streaming: audio, video.
    Streaming uses propietary protocols, unlike http. Cloud Front uses Adobe/macromedia RTMP (Real Time Messaging Protocol), also the is
    an encrypted version: RTMPE (Real Time Messaging Protocol Encrypted)
    
This is natively integrated in AWS, you can specify S3 Buckets as origins. Its interface is very easy, also supports standard http/s
also streaming with RTMP/E, and is very cost effective: Contents are only cached, at edges, when there is a user request, and you can 
free that chache, on demand or on squedule.
 
 Data can be "expired":
 - On squedule
 - On demand.
 
 
## HOW TO SET A CLOUDFRONT:
 
 First you have to define a "Distribution":
    - you have to specify if this will be HTTP, or Streaming.
    - Set an 'origin': any web-accesible web server will do: private server, EC2 or S3.
    - You can also specify: 
              - TTL (Time To Live)- this defines how often Cloud Front is going to check for a new version of the file.
              - Path matches; this specifies what parts of your origin web server are going to be cached.
              - Logging; allows log request to Cloud Front.
              
At this time you have created a distribution domain, you can easily rename using CNAMEd "vanity URLs" - this is useful in cases as
Websites (CSS, JS, images references) or Applications (media players, web, mobile, or desktop apps).
 
FINAL USER ACCESS:
==================
 
When a final user access to a CDN (Content Delivery Network) URL, CloudFront directs the user to the closes edge, so it serves
the data faster.
This is a pulling mechanism, so if the closes edje to a client, doesn't have the required data, that edje request the data to the
the origin edge, and pull that data down local, so next time a client request the data in that location, it will already stored 
in the closest edje, and serviced faster.
 
### sign urls vs cookies

To restrict the access to cloud front use signed urls for single urls, or for several urls use cookies. 
 
INTRODUCTION TO ELASTIC CACHE:
==============================

- Elastic Cache is an in memory caching mechanism.
- Is 100% Under the hood.
 - 100% API compliant: User get, set, incr, decr, stats, the same way you do in mem cache.
- More properly is mem cache cluster.


what is memcache/d ?
--------------------
 
Is a very popular, open source in-memory chache. very fast reads and writes. Because results came from memory not form disk.
takes the burden from the back end resources and free them for more important work.
This can be:
    - Databases.
    - Disk heads.
    - CPUs.
    
 The extra 'd' stands for deamon.
 
 Anithing that is expensive to create and/or nood be in real time. as:
    - Database query queues.
    - Large disk of files of the disk.
    - Computational expensive operations.
 Or if you want sombething to be extremely fast, as:
    - User sessions.
    - Product catalogs.
    
· Memcache is actually a key-value store.
Actually NoSQL is a memcache database.
- The access method is a key - which returns the value. It has no "query" capabilites other than key lookup.

ElasticCache is really a Memchache Cluster; is a distributed collection of cache nodes. This nodes are unfortunately abailable
only in AZ. And that AZ can be a single qualifier, especially if you are using it for ussing sessions.

Customers need multi-AZ HA (high Avaliability) must roll on their on.

Cache nodes are used on their on.

Cache nodes are used-specified types - Very much like EC2 instance types. they can be even been wreap with security groups, and can
buy "capacity reservations". the are also resizable, which cna be doed, by addign / removing larger nodes.

To set an Elastic Cache, you have to choose an AZ. choose a node type, and the number of nodes. Launch the cluster, Connect your
application by pointng to the Elastic Cache endpoint. Then benchmark and resize if necesary. Once capacity is kown purchase reservations
to save money. 

Expiring keys is controlled via  the elastic ElasticCache API, (memcache commands):
This can be done:
  - squedule 
  - on demand.
  
Elastic Cache, has an hourly charge: Reseverd or On demand. See "Pricingz model for EC2" for reference.

There is also Bandwidth charges
   - Free inside the AZ.
   - And $0.1 GB, in and aout accross AZs.
   

INTRODUCTION TO VPC (Virtual Private Cloud):
============================================

VPC stands for Virtual Private Cloud. VPC allows a logical isolation between your resources: From other constumers, and from internal 
divisions or application tiers.
It gives you control over:
 - adress spaces.
 - subnets.
 - Route tables & NATs (Netword Address Translations)
 - Network gateways (VPN and Internet).
 - Ingress and Engress security groups.
 - Multiple NICs (Elastic Network Interfaces or ENIs) on VPC EC2s.
 - Dedicated Hardware (with EC2 only).
 
Control over route tables & NATs
 A route table, sets what traffic goes down which line. - Depends on sender and target - 
 
NATs (Network Adress Trasnlation)- Lets machines "hide" on private network, but still be able to get out of the network. 
AWS provides a NAT instance for that porpouse.

VPC, also gives you control over Gateways; an Internet Gateway (IG), allows VPC resources to access Internet, is the only way for 
the resources to connect to Internet. It can be connected/disconnected programmatically.- For example when you want to deploy patches
in your EC2 isntances, you can put down you IG, pull down your patches, and then reconnect.

There is also a VPN Gateway (VPG)- this is a Harware solution that mates with on-premise VPN. Your on-prem must obey Border Gateway 
protocol o "BGP", most of the VPN appliances do. This can be used to treat VPC as an extension of corporate. This comes with an 
additionally hourly cost. 

Software VPN is also possible. You can use OpenVPN (free) is a popular solution.

VPC allows a logical isolation of your resources:
 - from other customers.
 - from internal divisions/application tiers. Many time when you are developing applications, the security applications require that
 the database is in a separate subnet. VPC allows for this, while amazon classic does not.
 
 VPC allows control over address spaces:
 - Provision an entire "B" Class of IP if you like (255.255.x.x) or "/16" - 65.000 ips
 - Any adress space provided in VPC will be available in subnets.
 - VPC adresses don't change when EC2 bounced.
 - Public-facing IPs still need to be Internet routable.
  + Can use Elastic IP.
  + You must route through Internet Gateway.
  
VPC(Virtual Private Cloud) allows control over subnets
 - Subnets provisioned in single AZ.
 - Can have 200 subnets, per VPC.
 - In VPC, think of subnets as AZs.
   · Autoscaling groups can span VPC subnets.
 - The Minimun size of a subnet must be a /28 (14 IP adresses)
 - The Maximun size = size of the VPC.
 - When sharing with the outside network (like bursting from corporate) watch out for IP conflicts.
 
VPC(Virtual Private Cloud) also gives you control over route tables or NATs (Network Adress Translation)
 - Route table: "what traffic goes down which line" - depends on sender and target.
NAT(Network Adress Translation) lets machines "hide" on private network, but still be able to get out fo network.
AWS provides a NAT instance for this pourpouse.
 
VPC(Virtual Private Cloud) gaves you control over network gateways.
 - Internet gateways (IG): Allows VPC resources to access the internet.
 - And is the only way for this resources to access the internet.
 - Can be connected/disconnected programatically (for example when you are doing patch updates on your EC2 servers, you can connect
your IG, pull down your patches, and then disconnect your IG.)
 
There is also a VPN Gateway or VPG: this is a hardware VPN solution which matches with on-premise VPN. Your On-prem must obey BGP, or
Border Gate Protocol (router protocol)
 
A software VPN(Virtual Private Cloud) is also possible. "OpenVPN" is a popular solution.
 
VPN(Virtual Private Cloud) also gives you control over ingress and egress security groups. This is only for EC2, but you can control 
both inbound (as EC2 Classic), and outbound. This can be used, for example, to allow EC2, to access a package repository, but don't 
access anywhere else on the internet.
 
Additionally, network access control lists(NACLs) can allow or deny traffic in/out of your subnet.
 
VPC(Virtual Private Cloud) can control over multiple NICs (Network Interface Cards) -while a single EC2, can have now more than one
NIC card; this depends on the instance type - this is known as ENI(Elastic Network Interface). They can be added/removed from a running
intance and they come at no additional cost.
 
VPC(Virtual Private Cloud) have the option to run in dedicated hardware - this reserves the entire physical server for a single tenancy,
althoug is very costly. 
 
A very good point of AWS VPC, is that it allows compliance with very strict regulations as HIPPA, SOX, et cetera.
 
 
VPC cons:
=========

VPC(Virtual Private Cloud) comes with several shortcomings:
 - only select resources can be launch on VPC: currently this includes ELB, with support to balance web/app tier, only in the VPC.
 - EC2, and EBS, Autoscaling.
 - RDS(Relational Database Service).
 - ElasticCache.
 - Provides not any broadcast or multicast support- the same as EC2_classic.
 -You should launch all your desired resources, all of them toghether, either inside or outside of your VPC(Virtual Private Cloud).

If you try to put part in, and part out, you will have a network lag, that will slow down your app.
 -You can only have 5 VPC per account and per Region
 -You can only have 200 subnets per VPC. Subnets, can only be single AZ.
 -You can only have 1 IG(Internet Gateway) per VPC.

 
 VPC setup:
 ==========
 
 - First, you should choose a reasonable IP range, that don't conflict with corporate.
 - Choose, the AZ you are going to want.
 - Create the subnets.
 - Create routetables, NACLs (Network Access Control List)
 - Launch assets into VPC.
 - You can connect and IG(Internet Gateway) with the VPG(Virtula Private Cloud Gateway)- think about programmatically connetc/disconnect
 the IG.
 
 
## AWS SNS(Simple Notification Service):

Reference: https://docs.aws.amazon.com/sns/latest/dg/welcome.html

SNS(Simple Notification Service) is used to send internal notifications inside AWS: 
-from an application or an user.
-to an application or an user.

Its very useful for notification, alerting, logging, and monitoring.

SNS, have API & AWS_console support. So you can programmatically launch actions, and subscribe/unsubscribe from lists.

Is based in a Push system, (contrary to a Pull system), so subscribers , get notifications when they are producced.
 
#### SNS setup:

- First, you create, what is call: a Topic. -think of it as a mailbox or email alias.
- Then, you add subscribers.
- Subscribers, have to confirm (http, email, or SQS(Amazon Simple Qeue Service) with permissions).
- Then you send messages to the Topic, and the subscribers, will receive the message.

#### SNS subscriber types:

- http/s: any http/s endpoint, doesn't matter if it belongs to AWS or not. this is really usefull for programmatically consume notifications.
- emai/email-JSON: good for humans/ programmatically consumption.
- SMS: good for humans- really good for ALERTS.
- SQS: good for logging, and automation. [ref: https://aws.amazon.com/sqs/]

#### SNS best practices:

- Subscribe to a 2nd SQS service for http/sms/email notifications; this allows workers, to get notifications from SQS(Amazon Simple Qeue Service) and log the processes- if the primary subscriber, don't receive the message, you have a copy with the SQS, and can be inmediatly re-processed by workers, or for logging.

Note, that SNS is push-based service, while SQS is a polling based service! 

### AWS SES(Simple Email Service):

SES(Simple Email Service) allows to send emails, to external users of AWS. Useful for bulk/marketing emails.

PLEASE: check/comply with CAN-SPAM Compliance.

#### SNS vs SES:

-SNS emails/subscriptions must be confirmed.
-SNS only supports plain text.
-SNS cannot customize emails per customer.

#### SES best practices:

 - Send emails directly from EC2 servers: It's best to create a EC2 role with SES capability.
 - You can directly launch that server into that role, and send over the SMPT relay- its also recommended to use SMPT, but not the API.
 - Comply with the CAN-SPAM rules.
 - Use SPF, Sender ID, and DKIM.

### AWS SQS(Simple Qeue Service):

- You can work with qeues, it check calls and posts. You can batch process the work.
- Qeues or "posting notes" are efficient and scalable systems.
   ·multiple outside callers can leave a message.
   ·multiple workers can process though a message list.
-Technically is defined as a "Loose Coupled" system -check/google about it-
-This allows to scale in each tier- this is allows to SOA(Software Oriented Arquitecture).

SQS(Simple Qeue Service):
-Its have no limit to the number of messages in a qeue or the number of qeues.
-Each SQS, can serve a different listener: database, processor, ...
-SNS(Simple Notification System) can resort to SQS, and it recomended to use SQS to reconciliate http listeners.
-SQS, usually is used with SNS(Simple Notification Service), as a 2nd bucket for transitory messages.
-It have time-up support.
-It have API & AWS_console support (you can automate it).

SQS cons:
-Its "Pull" based.
-the order of messages is not guaranteed, -and you can end up with more than once delivery.- so the workers, need to be able, to
run the same process/data process twice, and put out the same result (idempotent)- so you should consider SWF(Simple Work Flow), 
that delivers exactly one delivery, if you have sensitive transactions/process (like finantial transactions)-
-a message could sit in your qeue for ever, so you should periodically run a qeue dry, meaning flush the qeue, that is: take all 
messages out of the qeue.
-it need explicit delete orders to the message. The SQS, doesnt know if the workers do something useful with the messages, so 
it actually needs someone tells it to delete the messages.
-As said first, is a "Pull" based systems, so messages are in the qeue until workers, pull it (and delete it), or the time-up runs.

SQS setup:
-Create a qeue.
-Create workers.
-Make workers to poll the qeue.
-Workers must delete the message from the qeue explicitly.
-Old messages will fall off the qeue.

SQS vs. SWF:
-SWF is actually a full ent-to-end workflow engine.
-SWF guarantees exactly one delivery.
-SWF provides advanced features as: signaling, logging, markers, et cetera.

SQS user cases:
-SQS should be used as the interface between the layers of your app.
·for example:
   - AWS order processing.
   - machine to machine messaging.
   
### Introduction to API Gateway

Reference: https://docs.aws.amazon.com/apigateway/latest/developerguide/welcome.html

IT IS A FRONT-DOOR FOR YOUR APPLICATIONS!!

 AWS API Gateway is a service to create, publish, mantain, and monitor APIs. This allows an API that will work as the "front door" for applications for your back-end services, as Elastic compute clouds EC2, aws lambda or web applications. 
 
 API Gateway creates RESTful APIs that:
  - Are HTTP-based.
  - Enable stateless client-server communication.
  - Implement standard HTTP methods such as GET, POST, PUT, PATCH, and DELETE.
 
From the security point of view, use WAF (Web Applitacion Firewall) to protect your endpoints. 

### AWS BATCH

reference: https://docs.aws.amazon.com/batch/latest/userguide/what-is-batch.html

AWS Batch helps you to run batch computing workloads on the AWS Cloud. Batch computing is a common way for developers, scientists, and engineers to access large amounts of compute resources. AWS Batch removes the undifferentiated heavy lifting of configuring and managing the required infrastructure, similar to traditional batch computing software. This service can efficiently provision resources in response to jobs submitted in order to eliminate capacity constraints, reduce compute costs, and deliver results quickly.

The workloads run in EC2 or Fargate (Fargate is recommended as it scales better). EC2 may be a better opiton, for example, when you need a certain AMI, or forme thatn 4 vCPU or if you need an GPU or Arm-based Graviont. , or anything needing more than 30 GiB of memory, or in there is a large number of jogbs. 

Somtimes is better to use AWS lambda. AWS lambda has an 15 minutes time limit. So for long-time jobs, is better to use AWS Batchs. Also lambda, has limited disk space. For custom run-times is better AWS Batch.

### AWS MQ (Message Queue)

Amazon MQ is a managed message broker service that makes it easy to migrate to a message broker in the cloud. A message broker allows software applications and components to communicate using various programming languages, operating systems, and formal messaging protocols. Currently, Amazon MQ supports Apache ActiveMQ and RabbitMQ engine types.

This is is relevant in case you need to migrate an appication, and you are using message queues. Also Amazon MQ requires private networking, like VPC, while SQS and SNS are publicly accessible by default. 

### AWS step functions

reference: https://docs.aws.amazon.com/step-functions/latest/dg/welcome.html

AWS Step Functions is a serverless orchestration service that lets you integrate with AWS Lambda functions and other AWS services to build business-critical applications. Through Step Functions' graphical console, you see your application’s workflow as a series of event-driven steps.

Step Functions is based on state machines and tasks. A state machine is a workflow. A task is a state in a workflow that represents a single unit of work that another AWS service performs. Each step in a workflow is a state.

With Step Functions' built-in controls, you examine the state of each step in your workflow to make sure that your application runs in order and as expected. Depending on your use case, you can have Step Functions call AWS services, such as Lambda, to perform tasks. You can create workflows that process and publish machine learning models. You can have Step Functions control AWS services, such as AWS Glue, to create extract, transform, and load (ETL) workflows. You also can create long-running, automated workflows for applications that require human interaction.

There is two exection types: 
- Standard workforws: which are good for long-time runing, auditable executiions.
- Express workflows: which are good for high-event-rate executions.

## INTRODUCTION TO ROUTE53:

Route53, is the Amanzons distributed DNS for AWS.

It supports all major record types
 -A (address record)
 -AAAA (IPv6 address record)
 -CNAME (Canonical name record)
 -MX (Mail Exchange Record)
 -NS (Name Server)
 -PTR (pointer record)
 -SOA (Start of authority record)
 -SPF (Sender Policy framework)
 -SVR (service locator)
 -TXT (text record)


## SERVERLESS ARCHITECTURE

Serverless allows you to execute code, in response of an event, an letting AWS handle it. You only  pay for the provisioned resources and the lenght of the runtime. 

### Lamda

reference: https://docs.aws.amazon.com/lambda/?icmpid=docs_homepage_serverless

With AWS Lambda, you can run code without provisioning or managing servers. You pay only for the compute time that you consume—there's no charge when your code isn't running. You can run code for virtually any type of application or backend service—all with zero administration. Just upload your code and Lambda takes care of everything required to run and scale your code with high availability. You can set up your code to automatically trigger from other AWS services or call it directly from any web or mobile app.

For writing a lambda there are several points to take care of:
- **Runtime**: need to select from an available runtime or birng your own. This is the enviroment your code will run in. 
- **Permissions**: If your lambda function needs to make an AWS API call, you will need to attach a role. 
- **Networking**: Optionally define the VPC, subnet and security groups your functions are part of.
- **Resources**: Define the amout of memory that will be neede, and how much CPU and RAM gets. (remeber max time 15 minutes! and max 10 GiB of RAM!)
- **Trigger**: which is the event that will fire the lambda function.

Note: Lambda excss in running samll and lightweigth functions. (ideal for microservices)

### AWS Serverless Application Repository

reference https://aws.amazon.com/serverless/serverlessrepo/
 
The AWS Serverless Application Repository is a managed repository for serverless applications. It enables teams, organizations, and individual developers to store and share reusable applications, and easily assemble and deploy serverless architectures in powerful new ways. Using the Serverless Application Repository, you don't need to clone, build, package, or publish source code to AWS before deploying it. Instead, you can use pre-built applications from the Serverless Application Repository in your serverless architectures, helping you and your teams reduce duplicated work, ensure organizational best practices, and get to market faster. Integration with AWS Identity and Access Management (IAM) provides resource-level control of each application, enabling you to publicly share applications with everyone or privately share them with specific AWS accounts. To share an application you've built, publish it to the AWS Serverless Application Repository.

### Containers

A containter is a standard unit of software that packages up code and all its dependencies, so the applications runs quickly and reliably from one computing environment to another. 

The difference with a virtual machine is that a contanier don't have the duplication of the operation system. 

The usual workflow is: <br>
Dockerfile -> build and Image -> store (upload) the image into a Registry -> Download the image from a registry & run a continer, copyiing the image created.


### Running containers in ECS (Elastic Container Service) or EKS (Elastic Kubernetes Service)

Amazon Elastic Container Service (Amazon ECS) is a highly scalable, fast, container management service that makes it easy to run, stop, and manage Docker containers on a cluster of Amazon EC2 instances.

reference: https://docs.aws.amazon.com/ecs/ <br>
reference: https://docs.aws.amazon.com/AmazonECS/latest/developerguide/Welcome.html <br>

- ECS can manage lots of containers. It will allocate it and keep them online. 
- ELB integration: containers iwll be properly registered with the load balancers as they come online and offline.
- Role integration: containers can have individual roles attached to them, making security easy. 
- Easy to use: very easy to setup and scale.

For a solution more cross-platform appropiate, use then Kubernetes (K8s), its AWS version is named EKS (Elastic Kubernetes Service) 

Comparation between ECS and EKS: 

- ECS is easier to use. AWS is bet used when you don't want to depend entirelly on AWS.

### AWS EKS Anywhere

reference: https://anywhere.eks.amazonaws.com/docs/

EKS Anywhere provides a means of managing Kubernetes clusters using the same operational excellence and practices that Amazon Web Services uses for its Amazon Elastic Kubernetes Service (Amazon EKS). Based on EKS Distro, EKS Anywhere adds methods for deploying, using, and managing Kubernetes clusters that run in your own data centers. Its goal is to include full lifecycle management of multiple Kubernetes clusters that are capable of operating completely independently of any AWS services.
The tenets of the EKS Anywhere project are:

- Simple: Make using a Kubernetes distribution simple and boring (reliable and secure).
- Opinionated Modularity: Provide opinionated defaults about the best components to include with Kubernetes, but give customers the ability to swap them out
- Open: Provide open source tooling backed, validated and maintained by Amazon
- Ubiquitous: Enable customers and partners to integrate a Kubernetes distribution in the most common tooling.
- Stand Alone: Provided for use anywhere without AWS dependencies

Better with AWS: Enable AWS customers to easily adopt additional AWS services

### AWS Fargate

reference: https://docs.aws.amazon.com/AmazonECS/latest/userguide/what-is-fargate.html

AWS Fargate is a technology that you can use with Amazon ECS to run containers without having to manage servers or clusters of Amazon EC2 instances. With Fargate, you no longer have to provision, configure, or scale clusters of virtual machines to run containers. This removes the need to choose server types, decide when to scale your clusters, or optimize cluster packing.

When you run your Amazon ECS tasks and services with the Fargate launch type or a Fargate capacity provider, you package your application in containers, specify the Operating System, CPU and memory requirements, define networking and IAM policies, and launch the application. Each Fargate task has its own isolation boundary and does not share the underlying kernel, CPU resources, memory resources, or elastic network interface with another task.

It works for both ECS and EKS. Fargate is more of a feature of ECS or EKS

EC2 is better to be used in long running applications. Fargate is better when containers don't need to run all the time. But for short code that can be encapsulated in a fucntion lambda is better. 

### EventBridge (CloudWatch events)

reference: https://docs.aws.amazon.com/eventbridge/

Amazon EventBridge is a serverless event bus service that makes it easy to connect your applications with data from a variety of sources. EventBridge delivers a stream of real-time data from your own applications, software-as-a-service (SaaS) applications, and AWS services and routes that data to targets such as AWS Lambda. You can set up routing rules to determine where to send your data to build application architectures that react in real time to all of your data sources. EventBridge enables you to build event-driven architectures that are loosely coupled and distributed.

- **Define patterns**: ther  rule to be invoked based on an event happening or scheduled
- **Select event bus**: and AWS-based envet or custom event=
- **Select target**: What happens when the event is received? a lambda function, or post to an SQS queu, or send an email?

EventBridge (Cloudwatch events) is the fastest way to respond to an AWS event. Also it is the main glue to really build your serverless application, as it can repsond to any AWS API call. 

### Storing custom docker images in Amazon ECR (Elastic Container Registriy)

reference: https://docs.aws.amazon.com/AmazonECR/latest/userguide/what-is-ecr.html

Amazon Elastic Container Registry (Amazon ECR) is a fully managed Docker container registry that makes it easy for developers to store, manage, and deploy Docker container images.

Amazon Elastic Container Registry (Amazon ECR) is an AWS managed container image registry service that is secure, scalable, and reliable. Amazon ECR supports private repositories with resource-based permissions using AWS IAM. This is so that specified users or Amazon EC2 instances can access your container repositories and images. You can use your preferred CLI to push, pull, and manage Docker images, Open Container Initiative (OCI) images, and OCI compatible artifacts.

Amazon ECR Public, is a similar service, but for pubilc image repositories. 

### AWS Aurora Serverless

reference: https://docs.aws.amazon.com/AmazonRDS/latest/AuroraUserGuide/Concepts.Aurora_Fea_Regions_DB-eng.Feature.ServerlessV1.html

Aurora Serverless is an on-demand, auto-scaling feature designed to be a cost-effective approach to running intermittent or unpredictable workloads on Amazon Aurora. It automatically starts up, shuts down, and scales capacity up or down, as needed by your applications, using a single DB instance in each cluster.

### AWS X ray

reference: https://docs.aws.amazon.com/xray/?icmpid=docs_homepage_devtools

AWS X-Ray makes it easy for developers to analyze the behavior of their distributed applications by providing request tracing, exception collection, and profiling capabilities.  

It is a service that collects application data about the resquests and responses of your applications. 

It integrates wit many services as EC2 Lambda, and API gateway. 

### AWS AppSync

reference: https://docs.aws.amazon.com/appsync/?icmpid=docs_homepage_serverless

AWS AppSync is an enterprise-level, fully managed GraphQL service with real-time data synchronization and offline programming features.



## SECURITY

### Attacks

#### DDos

A Distributed Denial of Service (DDoS) attack is an attack that attemps to make your sistem or applications unavailable to the end users.

This can be achieved by several mechanims, suche sync floods, large packets floods, or sending massive number of messages with botnets.

#### Layer 4 attack: SYN flood

A layer 4 DDoS attack, also known as SYN fllod attack. It works at the transport layer (layer 4) of TCP. It flood the system wit SYN request, causing a great lost of resources (In the 3-way handshake)

#### Aplification/Reflection attacks

Attacks like: NTP, SSDP, NDS, CharGEN, SNMP attacks ...

This is where an attacker  may send a third-party server (such an NTP(network time protocol) server) a request sugin a spoofed IP address. 

#### Layer 7 attack

A layer 7 attack occurs where a web server receives a flood of GET or POST requests usually from a botnet or similar. 

### AWS CloudTrail and how to log AWS API calls

reference: https://docs.aws.amazon.com/cloudtrail/?icmpid=docs_homepage_mgmtgov

With AWS CloudTrail, you can monitor your AWS deployments in the cloud by getting a history of AWS API calls for your account, including API calls made by using the AWS Management Console, the AWS SDKs, the command line tools, and higher-level AWS services. You can also identify which users and accounts called AWS APIs for services that support CloudTrail, the source IP address from which the calls were made, and when the calls occurred. You can integrate CloudTrail into applications using the API, automate trail creation for your organization, check the status of your trails, and control how administrators turn CloudTrail logging on and off.


### Protecting applications with AWS Shield.

reference: https://docs.aws.amazon.com/shield/?icmpid=docs_homepage_security

AWS provides two levels of protection against DDoS attacks: AWS Shield Standard and AWS Shield Advanced. AWS Shield Standard is automatically included at no extra cost beyond what you already pay for AWS WAF and your other AWS services. For added protection against DDoS attacks, AWS offers AWS Shield Advanced. AWS Shield Advanced provides expanded DDoS attack protection for your Amazon EC2 instances, Elastic Load Balancing load balancers, Amazon CloudFront distributions, and Amazon Route 53 hosted zones.

It handles layer 3 and 4.

### AWS WAF (Web Application Firewall)

reference: https://docs.aws.amazon.com/waf/?icmpid=docs_homepage_security

AWS WAF is a web application firewall that lets you monitor web requests that are forwarded to Amazon CloudFront distributions or an Application Load Balancer. You can also use AWS WAF to block or allow requests based on conditions that you specify, such as the IP addresses that requests originate from or values in the requests.

It handles layer 7. So in need to block layer 7 DDoS attacks or SQL injection and cross-site scripting, use WAF. Also in need to block access to specific countries or IP addresses use WAF.

#### related services

For additional protection against distributed denial of service (DDoS) attacks, AWS also offers AWS Shield Advanced. AWS Shield Advanced provides expanded DDoS attack protection for your Amazon CloudFront distributions, Amazon Route 53 hosted zones, and Elastic Load Balancing load balancers. AWS Shield Advanced incurs additional charges (about $3000 per month).

AWS Firewall Manager simplifies your AWS WAF administration and maintenance tasks across multiple accounts and resources. With AWS Firewall Manager, you set up your firewall rules just once. The service automatically applies your rules across your accounts and resources, even as you add new resources.


### AWS GuardDuty 

reference: https://docs.aws.amazon.com/guardduty/?icmpid=docs_homepage_security

Thread detection based on AI.

Amazon GuardDuty is a continuous security monitoring service. Amazon GuardDuty can help to identify unexpected and potentially unauthorized or malicious activity in your AWS environment. 


### AWS Firewall manager

reference: https://docs.aws.amazon.com/firewall-manager/?icmpid=docs_homepage_security

AWS Firewall Manager simplifies your AWS WAF administration and maintenance tasks across multiple accounts and resources. With AWS Firewall Manager, you set up your firewall rules just once. The service automatically applies your rules across your accounts and resources, even as you add new resources.


#### related services

AWS WAF is a web application firewall that lets you monitor web requests that are forwarded to Amazon CloudFront distributions or an Application Load Balancer. You can also use AWS WAF to block or allow requests based on conditions that you specify, such as the IP addresses that requests originate from or values in the requests.

For additional protection against distributed denial of service (DDoS) attacks, AWS also offers AWS Shield Advanced. AWS Shield Advanced provides expanded DDoS attack protection for your Amazon CloudFront distributions, Amazon Route 53 hosted zones, and Elastic Load Balancing load balancers. AWS Shield Advanced incurs additional charges.

### Macie: Monitoring S3 buckets with Macie

reference: https://docs.aws.amazon.com/macie/latest/user/what-is-macie.html <br>
reference: https://docs.aws.amazon.com/macie/latest/user/monitoring-s3.html <br>
video: https://youtu.be/CenD1dq3xj8

Amazon Macie is a fully managed data security and data privacy service that uses machine learning and pattern matching to help you discover, monitor, and protect sensitive data in your AWS environment.

NOTE: it is great for HIPAA and GDPR compliance!! 

NOTE: Macie can create alerts to send to EventBridge, and integrate it with your event management system. !!

Macie automates the discovery of sensitive data, such as personally identifiable information (PII) and financial data, to provide you with a better understanding of the data that your organization stores in Amazon Simple Storage Service (Amazon S3). Macie also provides you with an inventory of your S3 buckets, and it automatically evaluates and monitors those buckets for security and access control. Within minutes, Macie can identify and report overly permissive or unencrypted buckets for your organization.

If Macie detects sensitive data or potential issues with the security or privacy of your data, it creates detailed findings for you to review and remediate as necessary. You can review and analyze these findings directly in Macie, or monitor and process them by using other services, applications, and systems.

When you enable Amazon Macie for your AWS account, Macie automatically generates and begins maintaining a complete inventory of your Amazon Simple Storage Service (Amazon S3) buckets in the current AWS Region. Macie also begins monitoring and evaluating the buckets for security and access control. If Macie detects an event that reduces the security or privacy of an S3 bucket, Macie creates a policy finding for you to review and remediate as necessary.

To also monitor S3 buckets for the presence of sensitive data, you can create and run sensitive data discovery jobs that analyze bucket objects on a daily, weekly, or monthly basis. If you do this and Macie detects sensitive data in an object, Macie creates a sensitive data finding to notify you of the sensitive data that Macie found.

In addition to findings, Macie provides constant visibility into the security and privacy of your Amazon S3 data. To assess the security posture of your data and determine where to take action, you can use the Summary dashboard on the console. This dashboard provides a snapshot of aggregated statistics for your Amazon S3 data. The statistics include data for key security metrics such as the number of buckets that are publicly accessible, don’t encrypt new objects by default, or are shared with other AWS accounts. The dashboard also displays groups of aggregated findings data for your account—for example, the names of 1–5 buckets that have the most findings for the preceding seven days. You can drill down on each statistic to view its supporting data. If you prefer to query the statistics programmatically, you can use the Amazon S3 Data Source Statistics resource of the Amazon Macie API.

### AWS Inspector

reference: https://docs.aws.amazon.com/inspector/latest/user/what-is-inspector.html

Amazon Inspector is a vulnerability management service that continuously scans your AWS workloads for vulnerabilities. Amazon Inspector automatically discovers and scans Amazon EC2 instances and container images residing in Amazon Elastic Container Registry (Amazon ECR) for software vulnerabilities and unintended network exposure.

When a software vulnerability or network issue is discovered, Amazon Inspector creates a finding. A finding describes the vulnerability, identifies the affected resource, rates the severity of the vulnerability, and provides remediation guidance. Details of a finding for your account can be analyzed in multiple ways using the Amazon Inspector console, or you can view and process your findings through other AWS services

### AWS KMS (Key Management Service)

reference: https://docs.aws.amazon.com/kms/

AWS Key Management Service (AWS KMS) is an encryption and key management service scaled for the cloud. AWS KMS keys and functionality are used by other AWS services, and you can use them to protect data in your own applications that use AWS.

CMK i s the Customer Master Key, it is a logical representation of a master key. The CMK includes metadata, such the key ID, creation date, description, and key state. 

HSM is Hardware Security Module, it is a device that safeguards and manages digital keys and performs encrypiton and decryption functions. They include crypto processors. 

#### KMS vs Cloud HSM

KMS: 
 - Shared tenancy of the underlying hardware
 - Automatic key rotation
 - Automatig key generation

CloudHSM: 
 - Dedicated HSM to you
 - Full control of underlying hardware
 - Full control of users, groups, keys ...
 - No automatic key rotation

### AWS Secret Manager

reference: https://docs.aws.amazon.com/secretsmanager/?icmpid=docs_homepage_security

AWS Secrets Manager helps you to securely encrypt, store, and retrieve credentials for your databases and other services. Instead of hardcoding credentials in your apps, you can make calls to Secrets Manager to retrieve your credentials whenever needed. Secrets Manager helps you protect access to your IT resources and data by enabling you to rotate and manage access to your secrets.


### AWS Systems Manager Parameter Store

reference: https://docs.aws.amazon.com/systems-manager/latest/userguide/systems-manager-parameter-store.html

Parameter Store, a capability of AWS Systems Manager, provides secure, hierarchical storage for configuration data management and secrets management. You can store data such as passwords, database strings, Amazon Machine Image (AMI) IDs, and license codes as parameter values. You can store values as plain text or encrypted data. You can reference Systems Manager parameters in your scripts, commands, SSM documents, and configuration and automation workflows by using the unique name that you specified when you created the parameter. To get started with Parameter Store, open the Systems Manager console. In the navigation pane, choose Parameter Store.

Parameter Store is also integrated with Secrets Manager. You can retrieve Secrets Manager secrets when using other AWS services that already support references to Parameter Store parameters. 

NOTE: Parameter Store, is free. But has a limit of 10000 parameters, and don't have key rotation. !!!

### Sharing S3 objects with presigned URLs

reference: https://docs.aws.amazon.com/AmazonS3/latest/userguide/using-presigned-url.html

All objects and buckets are private by default. However, you can use a presigned URL to optionally share objects or allow your customers/users to upload objects to buckets without AWS security credentials or permissions.

You can use presigned URLs to generate a URL that can be used to access your Amazon S3 buckets. When you create a presigned URL, you associate it with a specific action. You can share the URL, and anyone with access to it can perform the action embedded in the URL as if they were the original signing user. The URL will expire and no longer work when it reaches its expiration time.


### AWS Certificate Manager

reference: https://docs.aws.amazon.com/acm/?icmpid=docs_homepage_crypto <br>
video: https://youtu.be/bWPTq8z1vFY

AWS Certificate Manager (ACM) helps you to provision, manage, and renew publicly trusted TLS certificates on AWS based websites.

Note: It is a free service,  And automatically renew SSL certificates and rotate the old ones, with new certifiacats with supported AWS services. 

### AWS Audit Manager

reference: https://docs.aws.amazon.com/audit-manager/?icmpid=docs_homepage_security

AWS Audit Manager helps you continuously audit your AWS usage to simplify how you manage risk and compliance with regulations and industry standards. AWS Audit Manager makes it easier to evaluate whether your policies, procedures, and activities—also known as controls—are operating as intended. The service offers prebuilt frameworks with controls that are mapped to well-known industry standards and regulations, full customization of frameworks and controls, and automated collection and organization of evidence as designed by each control requirement.

Note, if you are in need of continuous audit for complingin with HIPPA or GPRD, use this service.

### AWS Artifact

reference: https://docs.aws.amazon.com/artifact/?icmpid=docs_homepage_security

AWS Artifact is a web service that enables you to download AWS security and compliance documents such as ISO certifications and SOC (Service Orgainzation Control) reports, PCI (Payment Card Industry), GDPR, HIPAA ...

### AWS Cognito

reference: https://docs.aws.amazon.com/cognito/?icmpid=docs_homepage_security
video: https://www.youtube.com/watch?v=8a0vtkWJIA4

It is an authentication engine.

Amazon Cognito handles user authentication and authorization for your web and mobile apps. With user pools, you can easily and securely add sign-up and sign-in functionality to your apps. With identity pools (federated identities), your apps can get temporary credentials that grant users access to specific AWS resources, whether the users are anonymous or are signed in.

The two main components of Cognito are user pools and identinty pools.

User pools are directories of users that provide sign-up and sign-in options for your application.

Identity pools allow to give the users access to other AWS services. 

### AWS Detective

reference: https://docs.aws.amazon.com/detective/?icmpid=docs_homepage_security
video: https://www.youtube.com/watch?v=Rz8MvzPfTZA

Amazon Detective makes it easy to analyze, investigate, and quickly identify the root cause of security findings or suspicious activities. Detective automatically collects log data from your AWS resources and uses machine learning, statistical analysis, and graph theory to help you visualize and conduct faster and more efficient security investigations.

Note: Don't confuse inspector wich is an automated vulnerability management service that continuasly scans EC2 and  container workloads for software vulnerabilities with Detective which anayzes the root cause of an event. 


### AWS Network firewall

reference: https://docs.aws.amazon.com/network-firewall/?icmpid=docs_homepage_security

AWS Network Firewall is a stateful, managed, network firewall and intrusion detection and prevention service for your virtual private cloud (VPC).

### AWS Security Hub

reference: https://docs.aws.amazon.com/securityhub/?icmpid=docs_homepage_security

AWS Security Hub provides you with a comprehensive view of the security state of your AWS resources. Security Hub collects security data from across AWS accounts and services, and helps you analyze your security trends to identify and prioritize the security issues across your AWS environment.

## FRONT-END WEB AND MOBILE

### AWS Amplify

reference: https://docs.aws.amazon.com/amplify/?icmpid=docs_homepage_fewebmobile <br>
video: https://youtu.be/uRbGMZ9oPjw

Use AWS Amplify to develop and deploy cloud-powered mobile and web apps. The Amplify Framework is a comprehensive set of SDKs, libraries, tools, and documentation for client app development. Amplify provides a continuous delivery and hosting service for web applications.

### AWS Device Farm 

reference: https://docs.aws.amazon.com/devicefarm/?icmpid=docs_homepage_fewebmobile

AWS Device Farm is an app testing service that enables you to test your iOS, Android and Fire OS apps on real, physical phones and tablets that are hosted by AWS. The service allows you to upload your own tests or use built-in, script-free compatibility tests.

### AWS Pinpoint 

reference: https://docs.aws.amazon.com/pinpoint/?icmpid=docs_homepage_fewebmobile

Amazon Pinpoint helps you engage your customers by sending them email, SMS and voice messages, and push notifications. You can use Amazon Pinpoint to send targeted messages (such as promotions and retention campaigns), as well as transactional messages (such as order confirmations and password reset messages).


## MEDIA

### AWS Elastic Transcoder

reference: https://docs.aws.amazon.com/elastic-transcoder/?icmpid=docs_homepage_mediasvcs

Amazon Elastic Transcoder lets you convert media files that you have stored in Amazon S3 into media files in the formats required by consumer playback devices. For example, you can convert large, high-quality digital media files into formats that users can play back on mobile devices, tablets, web browsers, and connected televisions.

### AWS Kinesis

reference: https://docs.aws.amazon.com/kinesis/?icmpid=docs_homepage_analytics

Capture, process, and store video streams for analytics and machine learning.


## AUTOMATION

Automation is interesting because manual operations are more prone to errors, also usually is faster. 

### AWS CloudFormation

reference: https://docs.aws.amazon.com/cloudformation/?icmpid=docs_homepage_mgmtgov

AWS CloudFormation enables you to create and provision AWS infrastructure deployments predictably and repeatedly. It helps you leverage AWS products such as Amazon EC2, Amazon Elastic Block Store, Amazon SNS, Elastic Load Balancing, and Auto Scaling to build highly reliable, highly scalable, cost-effective applications in the cloud without worrying about creating and configuring the underlying AWS infrastructure. AWS CloudFormation enables you to use a template file to create and delete a collection of resources together as a single unit (a stack).

### AWS Beanstalk

reference: https://docs.aws.amazon.com/elastic-beanstalk/?icmpid=docs_homepage_compute

!¡ It is like a PaaS wizard for apps.

With AWS Elastic Beanstalk, you can quickly deploy and manage applications in the AWS Cloud without worrying about the infrastructure that runs those applications. AWS Elastic Beanstalk reduces management complexity without restricting choice or control. You simply upload your application, and AWS Elastic Beanstalk automatically handles the details of capacity provisioning, load balancing, scaling, and application health monitoring.

### AWS Systems Manager

reference: https://docs.aws.amazon.com/systems-manager/?icmpid=docs_homepage_mgmtgov

AWS Systems Manager gives you visibility and control of your infrastructure on AWS. Systems Manager provides a unified user interface so you can view operational data from multiple AWS services and enables you to automate operational tasks across your AWS resources.

## CACHING 

There are 4 caching solutions
- CloudFront
- ElasticChache
- DAX Dinamo DB Accelerator
- Global Accelerator 

### AWS CloudFront
 
reference: https://docs.aws.amazon.com/cloudfront/?icmpid=docs_homepage_networking

NOTE!! CloudFront is the only option to add HTTPS to a static web site served from S3.

 AWS Cloudfront is the AWS service for CDN (Content Delivery Networks). AWS Cloundfront can retrieve data from S3 buckets, or EC2, OR ELB , and serve its data from its data centers known as "edge locations", that are all around the world. So Cloudfront can serve cached data to user all around, and this can even be more cost effective that directly serving the data from S3 buckets
 
  Cloudfront also can improve our security as it uses features as OAI (Original Access Identity), so it restrict uderlying data through use only through Cloudfront operations, this includes protection from several exploits, safeguards, as AWS WAF, a web application firewall, and AWS Shield, a sevice that protects against DDoS attacks
 
### AWS ElasticCache

refence: https://docs.aws.amazon.com/elasticache/?icmpid=docs_homepage_databases 

NOTE!! Use when you need a "in-memory database"!! (redis & DynamoDB)

Amazon ElastiCache makes it easy to set up, manage, and scale distributed in-memory cache environments in the AWS Cloud. It provides a high performance, resizable, and cost-effective in-memory cache, while removing complexity associated with deploying and managing a distributed cache environment. ElastiCache works with both the Redis and Memcached engines; to see which works best for you, see the Comparing Memcached and Redis topic in either user guide.

### Global Accelerator

reference: https://docs.aws.amazon.com/global-accelerator/?icmpid=docs_homepage_networking

Note!!: IP caching!!

Global Accelerator is a netowriking service that sends user's traffic throught AWS'S global network infraestructure. It can increase performance and help deal with IP caching.

AWS Global Accelerator is a network layer service in which you create accelerators to improve the security, availability, and performance of your applications for local and global users. Depending on the type of accelerator that you choose, you can gain additional benefits, such as improving availability or mapping users to specific destination endpoints.

## DATA MIGRATION

reference: https://aws.amazon.com/snowball/resources/ <br>
video: https://youtu.be/6nKH0ceFkiQ

### Snow

reference: https://docs.aws.amazon.com/snowball/latest/snowcone-guide/snowcone-what-is-snowcone.html

reference: snowedge : https://docs.aws.amazon.com/snowball/latest/developer-guide/whatisedge.html

### Storage Gateway

reference: https://docs.aws.amazon.com/storagegateway/latest/APIReference/Welcome.html

AWS Storage Gateway is the service that connects an on-premises software appliance with cloud-based storage to provide seamless and secure integration between an organization's on-premises IT environment and the AWS storage infrastructure. The service enables you to securely upload data to the AWS Cloud for cost effective backup and rapid disaster recovery.

This can be very effective for a data migration into AWS cloud, or for a long-term pairing of a local architecture with AWS.

#### File gateway

reference: https://docs.aws.amazon.com/filegateway/latest/files3/what-is-file-s3.html

Amazon S3 File Gateway –Amazon S3 File Gateway supports a file interface into Amazon Simple Storage Service (Amazon S3) and combines a service and a virtual software appliance. By using this combination, you can store and retrieve objects in Amazon S3 using industry-standard file protocols such as Network File System (NFS) and Server Message Block (SMB). The software appliance, or gateway, is deployed into your on-premises environment as a virtual machine (VM) running on VMware ESXi, Microsoft Hyper-V, or Linux Kernel-based Virtual Machine (KVM) hypervisor. The gateway provides access to objects in S3 as files or file share mount points. 

### AWS DataSync

reference: https://docs.aws.amazon.com/datasync/latest/userguide/what-is-datasync.html <br>
video: https://youtu.be/_qhTF-gB-JE

AWS DataSync is an online data transfer service that simplifies, automates, and accelerates moving data between storage systems and services.

This service is more oritented to one-time migration from on-premise storate to the AWS cloud. On the oder hand Storage Gateway is more oriented for the cases in which it is desired to have an hybrid architecture with on-premise storage and cloud storage.

### AWS Database Migration Service

reference: https://docs.aws.amazon.com/dms/latest/userguide/Welcome.html

AWS Database Migration Service (AWS DMS) is a cloud service that makes it easy to migrate relational databases, data warehouses, NoSQL databases, and other types of data stores. You can use AWS DMS to migrate your data into the AWS Cloud or between combinations of cloud and on-premises setups.

With AWS DMS, you can perform one-time migrations, and you can replicate ongoing changes to keep sources and targets in sync. If you want to migrate to a different database engine, you can use the AWS Schema Conversion Tool (AWS SCT) to translate your database schema to the new platform. You then use AWS DMS to migrate the data. Because AWS DMS is a part of the AWS Cloud, you get the cost efficiency, speed to market, security, and flexibility that AWS services offer.

At a basic level, AWS DMS is a server in the AWS Cloud that runs replication software. You create a source and target connection to tell AWS DMS where to extract from and load to. Then you schedule a task that runs on this server to move your data. AWS DMS creates the tables and associated primary keys if they don't exist on the target. You can precreate the target tables yourself if you prefer. Or you can use AWS Schema Conversion Tool (AWS SCT) to create some or all of the target tables, indexes, views, triggers, and so on. 


## BIG DATA

### Redshift

reference: https://docs.aws.amazon.com/redshift/

Amazon Redshift is a fast, fully managed, petabyte-scale data warehouse service that makes it simple and cost-effective to efficiently analyze all your data using your existing business intelligence tools. It is optimized for datasets ranging from a few hundred gigabytes to a petabyte or more and costs less than $1,000 per terabyte per year, a tenth the cost of most traditional data warehousing solutions.

### AWS ELASTIC MAP REDUCE (EMP)

reference: https://docs.aws.amazon.com/emr/?icmpid=docs_homepage_analytics

Amazon EMR is a web service that makes it easy to process vast amounts of data efficiently using Apache Hadoop and services offered by Amazon Web Services. 

### AWS KINESIS

reference: https://docs.aws.amazon.com/emr/latest/ReleaseGuide/emr-kinesis.html <br>
user cases: https://aws.amazon.com/emr/#Use_cases

Amazon EMR clusters can read and process Amazon Kinesis streams directly, using familiar tools in the Hadoop ecosystem such as Hive, Pig, MapReduce, the Hadoop Streaming API, and Cascading. You can also join real-time data from Amazon Kinesis with existing data on Amazon S3, Amazon DynamoDB, and HDFS in a running cluster. You can directly load the data from Amazon EMR to Amazon S3 or DynamoDB for post-processing activities.

There are 2 major types:
 - Data streams: real-time streaming for ingesting data
 - Data firehose: data transfer tool to get information to S3, Redshift, ElasticSearch ... close to real-time

 ### AWS Quicksight
 
 reference: https://docs.aws.amazon.com/quicksight/
 
 Amazon QuickSight is a fast business analytics service to build visualizations, perform ad hoc analysis, and quickly get business insights from your data. Amazon QuickSight seamlessly discovers AWS data sources, enables organizations to scale to hundreds of thousands of users, and delivers fast and responsive query performance by using the Amazon QuickSight Super-fast, Parallel, In-Memory, Calculation Engine (SPICE).
 
### AWS Athena & Glue

reference: https://docs.aws.amazon.com/athena/

kind of serverless SQL <br>

Amazon Athena is an interactive query service that makes it easy to analyze data in Amazon S3 using standard SQL. Athena is serverless, so there is no infrastructure to setup or manage, and you pay only for the queries you run. To get started, simply point to your data in S3, define the schema, and start querying using standard SQL.

reference: https://docs.aws.amazon.com/glue/

kind of serverless ETL (Extract, Translform, Load) <br>

 AWS Glue is a scalable, serverless data integration service that makes it easy to discover, prepare, and combine data for analytics, machine learning, and application development.
 
 The usual way to handle it is:
 
 ```
 S3 -> AWS Glue crawlers -> AWS Glue Data Catalog -> Amazon Athena -> Amazon QuickShight
 ```

### AWS Data pipeline

reference: https://docs.aws.amazon.com/data-pipeline/?icmpid=docs_homepage_analytics

To automate data-driven workflows and automate it. <br>

AWS Data Pipeline is a web service that you can use to automate the movement and transformation of data. With AWS Data Pipeline, you can define data-driven workflows, so that tasks can be dependent on the successful completion of previous tasks.

### AWS MSK (Managed Streamming for Apache Kafka)

reference: https://docs.aws.amazon.com/msk/index.html

Amazon Managed Streaming for Apache Kafka (Amazon MSK) is a fully managed service that makes it easy for you to build and run applications that use Apache Kafka to process streaming data. It is serverless!! 

### AWS OpenSearch service

reference: https://docs.aws.amazon.com/opensearch-service/?icmpid=docs_homepage_analytics

Amazon OpenSearch Service is a managed service that makes it easy to deploy, operate, and scale OpenSearch, a popular open-source search and analytics engine. OpenSearch Service also offers security options, high availability, data durability, and direct access to the OpenSearch API.


## GOVERNANCE

### AWS Organizations

reference: https://docs.aws.amazon.com/organizations/?icmpid=docs_homepage_mgmtgov

AWS Organizations is an account management service that enables you to consolidate multiple AWS accounts into an organization that you create and centrally manage. AWS Organizations includes account management and consolidated billing capabilities that enable you to better meet the budgetary, security, and compliance needs of your business. As an administrator of an organization, you can create accounts in your organization and invite existing accounts to join the organization.

AWS Organizations is a free governance tool, taht allows to create an manage multiple AWS accoutns from a single location rather than jumping from account to account. 

 - Its a best practice to create a speciffic account dedicated to logging. CloudTrail suppors logs aggregation. Then logs can be centralized into one account.
 - It is possible to easily create and destroy new AWS accounts through an API. 
 - Reserved Instances (RI) can be shared across all accounts. 
 - Billing management: You will have a centralized account for billing.
 - Services Control Policies (SCP) these policies can create limits to what users can do (even the root account!!).
 
### AWS RAM (Resource Access Manager)

reference: https://docs.aws.amazon.com/ARG/?icmpid=docs_homepage_security

The AWS RAM is a free service that allows you to share AWS resoruces with other accounts within your organization. AWS RAM allows you to easily share resources rather thatn having to create duplicate copies in your different accounts. 

You can share: 
 - VPC subnets
 - transit gateways 
 - License manager
 - route 53 resolver
 - dedicated hosts
 - ... 

### AWS Config

reference: https://docs.aws.amazon.com/config/latest/developerguide/WhatIsConfig.html

AWS Config provides a detailed view of the configuration of AWS resources in your AWS account. This includes how the resources are related to one another and how they were configured in the past so that you can see how the configurations and relationships change over time.

### AWS Directory Service

reference: https://docs.aws.amazon.com/directoryservice/latest/admin-guide/what_is.html

AWS Directory Service provides multiple ways to use Microsoft Active Directory (AD) with other AWS services. Directories store information about users, groups, and devices, and administrators use them to manage access to information and resources. AWS Directory Service provides multiple directory choices for customers who want to use existing Microsoft AD or Lightweight Directory Access Protocol (LDAP)–aware applications in the cloud. It also offers those same choices to developers who need a directory to manage users, groups, devices, and access.

### AWS Cost Management & Cost Explorer

reference: https://docs.aws.amazon.com/cost-management/latest/userguide/what-is-costmanagement.html

AWS Cost Explorer is a feature that you can use to visualize your cost data for further analysis. Using it, you can filter graphs by several different values. This includes Availability Zone, AWS service, and AWS Region, It also includes other specifics such as custom cost allocation tag, Amazon EC2 instance type, and purchase option. If you use consolidated billing, you can also filter by member account. In addition, you can see a forecast of future costs based on your historical cost data.

### AWS Budgets

reference: https://docs.aws.amazon.com/cost-management/latest/userguide/budgets-managing-costs.html

You can use AWS Budgets to track and take action on your AWS costs and usage. You can use AWS Budgets to monitor your aggregate utilization and coverage metrics for your Reserved Instances (RIs) or Savings Plans.  If you're new to AWS Budgets, see Best practices for AWS Budgets.

 - View your billing information
 - Create Amazon CloudWatch alarms
 - Create Amazon Simple Notification Service (Amazon SNS) notifications

There are 4 different types of budgets to create:

- Cost budges: how much is the expending?
- Usage Budgets: how much is used?
- Reservation Budgets: how efiicient are the RIs?
- Saving plangs budgets

### AWS Cost and usage report (AWS CUR)

reference: https://docs.aws.amazon.com/cur/latest/userguide/what-is-cur.html

The AWS Cost and Usage Reports (AWS CUR) contains the most comprehensive set of cost and usage data available. You can use Cost and Usage Reports to publish your AWS billing reports to an Amazon Simple Storage Service (Amazon S3) bucket that you own. You can receive reports that break down your costs by the hour, day, or month, by product or product resource, or by tags that you define yourself. AWS updates the report in your bucket once a day in comma-separated value (CSV) format. Y

AWS Cost and Usage Reports tracks your AWS usage and provides estimated charges associated with your account. Each report contains line items for each unique combination of AWS products, usage type, and operation that you use in your AWS account. You can customize the AWS Cost and Usage Reports to aggregate the information either by the hour, day, or month.

AWS Cost and Usage Reports can do the following:

    - Deliver report files to your Amazon S3 bucket
    - Update the report up to three times a day
    - Create, retrieve, and delete your reports using the AWS CUR API Reference

### AWS Savings plans

reference: https://docs.aws.amazon.com/savingsplans/?icmpid=docs_homepage_cloudfin

Savings Plans is a flexible pricing model that helps you save a significant percentage on Amazon EC2 and Fargate usage. Savings Plans provide low prices on EC2 and Fargate in exchange for a commitment to a consistent amount of usage for a one-year or three-year term.

### AWS Trusted Advisor

reference: https://docs.aws.amazon.com/awssupport/latest/user/trusted-advisor.html

Trusted Advisor draws upon best practices learned from serving hundreds of thousands of AWS customers. Trusted Advisor inspects your AWS environment, and then makes recommendations when opportunities exist to save money, improve system availability and performance, or help close security gaps. 

### AWS Control Tower

reference: https://docs.aws.amazon.com/controltower/?icmpid=docs_homepage_mgmtgov

AWS Control Tower is a service that enables you to enforce and manage governance rules for security, operations, and compliance at scale across all your organizations and accounts in the AWS Cloud.

### AWS License manager

reference: https://docs.aws.amazon.com/license-manager/?icmpid=docs_homepage_mgmtgov

AWS License Manager streamlines the process of bringing software vendor licenses to the AWS Cloud. As you build out cloud infrastructure on AWS, you can save costs by repurposing your existing license inventory for use with cloud resources. License Manager reduces the risk of licensing overages and penalties with inventory tracking that is tied directly to AWS resources.

### AWS Health

reference: https://docs.aws.amazon.com/health/?icmpid=docs_homepage_mgmtgov

AWS Health provides personalized information about events that can affect your AWS infrastructure, guides you through scheduled changes, and accelerates the troubleshooting of issues that affect your AWS resources and accounts.

### AWS Service Catalog

references: https://docs.aws.amazon.com/servicecatalog/?icmpid=docs_homepage_mgmtgov

AWS Service Catalog enables IT administrators to create, manage, and distribute portfolios of approved products to end users, who can then access the products they need in a personalized portal. Typical products include servers, databases, websites, or applications that are deployed using AWS resources (for example, an Amazon EC2 instance or an Amazon RDS database). You can control which users have access to specific products to enforce compliance with organizational business standards, manage product lifecycles, and help users find and launch products with confidence.

### AWS Proton

reference: https://docs.aws.amazon.com/proton/?icmpid=docs_homepage_mgmtgov

AWS Proton creates and manages standardized infrastructure and deployment tooling for developers and their serverless and container-based applications.

### AWS Well architecture tool

reference: https://docs.aws.amazon.com/wellarchitected/?icmpid=docs_homepage_mgmtgov

Use the AWS Well-Architected Tool to review your workloads against current Amazon Web Services architectural best practices. The AWS Well-Architected Tool measures the workload and provides recommendations on how to improve your architecture.







# REFERENCES:
https://aws.amazon.com/es/documentation/s3/ </br>
https://aws.amazon.com/certification/faqs/ </br>
https://aws.amazon.com/articles/ </br>
https://aws.amazon.com/es/documentation/ </br>
https://aws.amazon.com/sqs/ </br>
https://aws.amazon.com/en/training/path-developing/ </br>
https://aws.amazon.com/training/intro_series/ </br>
https://aws.amazon.com/es/training/intro_series/ </br>
http://docs.aws.amazon.com/IAM/latest/UserGuide/introduction.html </br>
https://www.youtube.com/user/AmazonWebServices </br>


# AWS S3 APIs

Amazon S3 is designed to be languaje neutral, and to be used with the supported interfaces to store and retrieve objects.


 # AWS LEX
  AWS LEX is a service to build chat bots, also known as conversational interfaces, that use natural language processing, deep learning and ASP (advanced speech recognition).
 
 https://docs.aws.amazon.com/lex/latest/dg/what-is.html
 
 
