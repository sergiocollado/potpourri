
FOREWORD:
· This are my personal notes, on the AWS Cloud. The aim of this docuent,is to clarify my ideas, by means
of writting them down, and have a resource where quickly find answers to my doubts, based on my experience. 

Short Introductory videos: https://aws.amazon.com/es/training/intro_series/

https://www.aws.training/LearningLibrary?tab=digital_courses

# [AWS](https://aws.amazon.com/)

Amazon Web Services.

AWS free tier: https://aws.amazon.com/free/

# INDEX

 - [S3 - Simple Storage Service](s3 - simple storage service.)
 - [CLOUD FRONT](CLOUD FRONT)


# AWS S3 
# Simple Storage Service.

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

## ACCESS CONTROL:

Objects, also have types of access control:

 - IAM policies  (http://docs.aws.amazon.com/IAM/latest/UserGuide/introduction.html)
 - Bucket policies
 - ACLs(Access Control Lists) - AWS console
 - Query string autentification - gives expiring acess.
 - AWS management console. (sign in: https://console.aws.amazon.com/s3.)
 
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
 
## STORING POLICIES:

There are three ways to store policies:

 - **Standard** ( "11 9's") - that means that if you have 1 million files stored there, you will loose one, every 10.000 years.
  - It comes at greatest cost, but is the default.
  
 - **Reduced Redundancy Storage (RRS)** - is ("4 9s") - that is 99.99% durability over a given year- it means that if you have 10000 files there, you'll probable lose one every year.
  - It cost is reduced about 20% / Great for reproducible assets
  - RRS, can trigger notifications, on "object missing". </br>
  
 - **Glaciar** it has ("11 9's), but is great draw back is queued retrieval -you cannot get it back in real time- 
  - But is cost is about the 10% of the standard option - which make a great choise for archivals, and back-ups.
  - Ref: http://docs.aws.amazon.com/amazonglacier/latest/dev/introduction.html </br>
   
   
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
   
   
### AWS free usage tier
As part of the AWS Free Usage Tier, you can get started with Amazon S3 for free. Upon sign-up, new AWS customers receive 5 GB of Amazon S3 standard storage, 20,000 Get Requests, 2,000 Put Requests, and 15GB of data transfer out each month for one year.
   
   
## AMAZON ELASTIC CLOUD COMPUTING aka: EC2

It is a service that allows to provision virtual severs on demand. Each virtual server requested in known as a EC2 instance. anything you can do with a traditional server can be done with a EC2 instance. EC2 instances are flexible, and can be configured acconrding the needs. they support a variety of OS, like linux or windows. to select a given operating system, we choose a AMI (Amazon Machine Image). It is possible to launch one or several AMIs and create serveral instances with the same configuration. It is possible to set the image type, size, memory and netwoking capabilities, even the underling hardware. Also the configuration can be done programatically and automated. 

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

### DESCRIPTION:
- Resources of static website assests: Images, CSS, JS, HTML, JSON.
- Distributions: products, documents, data.
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
 
When a final user access to a CDN (Content Delivery Network) URL, CloudFront directs the user to the closes edje, so it serves
the data faster.
This is a pulling mechanism, so if the closes edje to a client, doesn't have the required data, that edje request the data to the
the origin edge, and pull that data down local, so next time a client request the data in that location, it will already stored 
in the closest edje, and serviced faster.
 
  
 
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
   

INTRODUCTION TO VPC(Virtual Private Cloud):
===========================================

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
 
 
Introduction to SNS(Simple Notification Service):
=================================================

SNS(Simple Notification Service) is used to send internal notifications inside AWS: 
-from an application or an user.
-to an application or an user.

Its very useful for notification, alerting, logging, and monitoring.

SNS, have API & AWS_console support. So you can programmatically launch actions, and subscribe/unsubscribe from lists.

Is based in a Push system, (contrary to a Pull system), so subscribers , get notifications when they are producced.
 
SNS setup:
==========

- First, you create, what is call: a Topic. -think of it as a mailbox or email alias.
- then, you add subscribers.
- subscribers, have to confirm (http, email, or SQS(Amazon Simple Qeue Service) with permissions).
- then you send messages to the Topic, and the subscribers, will receive the message.

SNS subscriber types:
=====================

- http/s: any http/s endpoint, doesn't matter if it belongs to AWS or not. this is really usefull for programmatically consume notifications.
- emai/email-JSON: good for humans/ programmatically consumption.
- SMS: good for humans- really good for ALERTS.
- SQS: good for logging, and automation. [ref: https://aws.amazon.com/sqs/]

SNS best practices:
===================

- Subscribe to a 2nd SQS service for http/sms/email notificqations; this allows workers, to get notifications from SQS(Amazon Simple
Qeue Service) and logg the processes- if the primary subscriber, dont receive the message, you have a copy with the SQS, and can be
inmediatly re-processed by workers, or for logging.

Introduction to SES(Simple Email Service):
==========================================

SES(Simple Email Service) allows to send emails, to external users of AWS.
Useful for bulk/marketing emails.

PLEASE: check/comply with CAN-SPAM Compliance.

SNS vs SES:
===========

-SNS emails/subscriptions must be confirmed.
-SNS only supports plain text.
-SNS cannot customize emails per customer.

SES best practices:
===================

- Send emails directly from EC2 servers: It's best to create a EC2 role with SES capability.
-You can directly launch that server into that role, and send over the SMPT relay- its also recommended to use SMPT, but not the API.
-Comply with the CAN-SPAM rules.
-Use SPF, Sender ID, and DKIM.

INTRODUCTION TO SQS(Simple Qeue Service):
=========================================

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
   
INTRODUCTION to IAM(Identity and Access Management):
====================================================

IAM, control access to AWS resources. each user gets it own set of cryptographic keys. It sets the users privileges to control actions.
Accesses can be time controlled: permanent or short term.

IAM, enables EC2 roles, that means, that EC2 instances, can get roles.

It can handle MFA(Multy Factor Authentification). FOBs cost something, and there is also a virtual FOB for Android&iOS.

It also have STS(Security Token Service), is somewhat similar to Kerberos, in the sense it can expire AWS resource access.

Best Practices: 

-Once you created the Master account, create an IAM_root_account, to access your thing, this is actually a safe/falloff
measurement.
-Create master accounts, for the groups: Production, Dev, Test.

More info:
http://docs.aws.amazon.com/IAM/latest/UserGuide/introduction.html
http://aws.typepad.com/aws/2011/08/aws-identity-and-access-management-now-with-identify-federation.html

INTRODUCTION TO ROUTE53:
========================

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
 
# CERTIFICATIONS:

The first certification is the:

## AWS Certified Developer - Associate:
Its a certification that evaluates the expertise in developing and manteining applications in the AWS platform.

- Understandin of core AWS services, use, best practices, and basic architecures
- AWS S3, DinamoDB, SQS, SNS, SWS, EB, CF.
- Choose the apropiate AWS services for a given application.
- Kwnoledge AWS SDKs to interact with AWS services with you application
- Profincy in deploying, developing and designing cloud based services of AWS.
- Writing code that optimices performance of AWS services
- Code-level application security( IAM, credentials, encription, ...)


# AWS S3 APIs

Amazon S3 is designed to be languaje neutral, and to be used with the supported interfaces to store and retrieve objects.


 
 # AWS LEX
  AWS LEX is a service to build chat bots, also known as conversational interfaces, that use natural language processing, deep learning and ASP (advanced speech recognition).
 
 https://docs.aws.amazon.com/lex/latest/dg/what-is.html
 
 
 # AWS CLOUDFRONT
 
 AWS Cloudfront is the AWS service for CDN (Content Delivery Networks). AWS Cloundfront can retrieve data from S3 buckets, or EC2, OR ELB , and serve its data from its data centers known as "edge locations", that are all around the world. So Cloudfront can serve cached data to user all around, and this can even be more cost effective that directly serving the data from S3 buckets
 
  Cloudfront also can improve our security as it uses features as OAI (Original Access Identity), so it restrict uderlying data through use only through Cloudfront operations, this includes protection from several exploits, safeguards, as AWS WAF, a web application firewall, and AWS Shield, a sevice that protects against DDoS attacks
 
 # AWS API GATEWAY
 AWS API Gateway is a service to create, pubilsh, mantain, and monitor APIs. This allows an API that will work as the "front door" cffro applications for your back-end services, as Elastic compute clouds EC2, aws lambda or web applications
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

 
 
 
 
 
    





