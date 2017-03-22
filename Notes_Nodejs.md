# Notes on Node.js

Node.js is a server-side framework, used to create intensive web applications (steamming, video, VoiP...), and is build on the Google's Chrome Javascript V8 engine. Node.js runs over a runtime environment.

The lead web reference for Node.js is: **https://nodejs.org**

## Important features are:

- Asincrhonous and event-driven.
- Non blocking.
- Single threaded, but easily scalable.
- No buffering- Node.js doesn't buffer any data.
- Ligthweight and efficient.

## Node.js is best used in the following applications:

- I/O applications
- Data streamming applications
- Data Intensive Real-Time applications (DIRT)
- JSON API based applications.
- Single page applications.

## Node.js is best not used in:

 - CPU intensive applications.

## Installation

Its reference website is: https://nodejs.org/

From there you can download the last package- recomended the LTS(Long Term Support) release.

In MS Windows, you just have to downloade the: nod-vx.xx.x-x64.msi run it, and follow the instructions.

In Linux, you have:
 + Check you have the building tools: 'apt-get install build-essential'
 + Get the source code, for example from its web:
 
```Bash
cd /temp
wget http://nodejs.org/dist/vx.xx.x/node-vx.xx.x-linux-x64.tar.gz
tar xvfz node-vx.xx.x-linux-64.tar.gz
mkdir -p /usr/local/nodejs
mv node-vx.xx.x-linux-x64/ /usr/local/nodejs
```
and set the enviromental variable:

````Bash
export PATH=$PATH:/usr/locla/nodejs/bin
```` 

 + Compile it:
 
 ```Bash
   - './configure'
   - 'make'
   - 'make install'
```

# Starting:

## Parts of an node.js applications

 + **import required modules** -- We need to import the `http` module.
 + **create a server** -- a server objecto, that listen to client's requests (like a brownser).
 + **read request and respond** - return response according to request. 
 
## Import required modules:

To use a http server and client you need to define it with 'require(\'http'\)'
The code-word 'require' is used to load module (sort of libraries).

```javascript
var http=require('http');
```

for example of an IoT application you may want to use:

```javascript
var http=require('mqtt');
```

## Creating a server:

To create a server, you use the method `createServer()`

```javascript
var http=require('http');
var server=http.createServer(function(request,response)
{
 //data process goes here.
});
```
If you want to implement as an event listener, you can do it like:

```javascript
var server=http.createServer();
server.on('request',function(request,respon){
//data process goes here.
});
```

If we want to implementt a server that always respond with an OK, then we would code:

```javascript
http.createServer(function(requested, response) {
 //Send the HTTP header
 //HTTP Status: Allles gut: 200 OK
 //Content Type: text/plain
 
 //send the response body as "Hello World"
 response.end('Hello World!\n');
 }.listen(8081);
 
 //print alive message in the console.
 console.log('Server running at http://127.0.01:8081/');
 ```
 


