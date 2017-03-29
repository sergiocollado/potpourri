# Notes on Node.js

Node.js is a server-side framework, used to create intensive web applications (steamming, video, VoiP...), and is build on the Google's Chrome Javascript V8 engine. Node.js runs over a runtime environment.

The lead web reference for Node.js is: **https://nodejs.org** <br>
There are also available reference guides: [:link:](https://nodejs.org/en/docs/guides/)

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

```Bash
export PATH=$PATH:/usr/local/nodejs/bin
```

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
there is another very used module called Express, you can load it wit:


```javascript
var express=require('express');
```

or for example of an IoT application you may want to use:

```javascript
var http=require('mqtt');
```

## Creating a server


### Getting requests

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

If we want to implement a server that always respond with an OK, then we would code:

```javascript
http.createServer(function(requested, response) {
 //Send the HTTP header
 //HTTP Status: Alles gut: 200 OK
 //Content Type: text/plain
 
 //send the response body as "Hello World"
 //listen(8081) means it listening to the 8081 port.
 response.end('Hello World!\n');
 }.listen(8081);
 
 //print log message in the console.
 console.log('Server running at http://127.0.01:8081/');
 //or an alert
 alert('Server running at http://127.0.01:8081/');
 ```
When a request arrives to the server then it outputs the programmed response.

For processing the request you will need to process the method and the url. Also you may need the headers and user-agent:

```javascript
var method = request.method;
var url = request.url;
var headers= request.headers;
var userAgent = headers['user-agent'];
```

If some headers are repeated, then their values are overwritten or joined together as comma-separated strings, depending on the header. In that case you can use `rawHeaders`.

When receiving a **'POST'** OR **'GET'** request, needs a bit more of precission. The 'request' object implements the `RedableSteam`, this stream can be listened or piped. So you can parse the stream data listening to the stream `data` and `end` events. So the best action is to collect all the 'data' into an array, and at the 'end' event to stringfy it.

```javascript
var body = [];
request.on('data', function(chunk) {
  body.push(chunk);
}).on('end', function() {
  body = Buffer.concat(body).toString();
  // at this point, `body` has the entire request body stored in it as a string
});
```

Have in mind, that the `request` is an `ReadableStream` and is also an `EventEmitter`, and it emits an 'error', and in case you don't listen for it, that can cause the program to crash. So its recommended to handle that 'error' even in the case, you don't do anything, and just log it, and move on.

```javascript
request.on('error', function(err) {
  // This prints the error message and stack trace to `stderr`.
  console.error(err.stack);
});
```

### Answering requests


The `response` is an instance of `ServerResponse`that is an `WritableStream`. The default response code will be always 200 (OK), unless you modify it, for it you use the `statusCode` property.

```javascript
response.statusCode = 404; // resorce wasn't found
```

Headers, are set with the `SetHeader`:

```javascript
response.setHeader('Content-Type', 'application/json');
```

With the `statusCode` and `SetHeader` you set 'implicit headers', and you rely on Node.js to send the headers at the proper time. You can also 'explicity' set those headers writing them into the response stream with the method `writeHead`:

```javascript
response.writeHead(200, {
  'Content-Type': 'application/json',
  'X-Powered-By': 'bacon'
});
```
For the body of the response, you can use normal write methods for a stream:

```javascript
response.write('<html>');
response.write('<body>');
response.write('<h1>Hello, World!</h1>');
response.write('</body>');
response.write('</html>');
response.end();
```
or write it all at once, like:

```javascript
response.end('<html><body><h1>Hello, World!</h1></body></html>');
```

Watch out! because as it happened with the `request`, the `response` is an eventEmitter, an it also launch an `error` so you should handle it. 

### Summing it up

 If we put all the above together:


```javascript 
var http = require('http');

http.createServer(function(request, response) {

  var headers = request.headers;
  var method = request.method;
  var url = request.url;
  
  response.statusCode = 200; //ok
      
  var body = [];
  
  request.on('error', function(err) {
    console.error(err);
    response.statusCode = 400; //Bad request
    response.end();
  }).on('data', function(chunk) {
    body.push(chunk);
  }).on('end', function() {
  
    body = Buffer.concat(body).toString();
    
    // At this point, we have the headers, method, url and body, and can now
    // do whatever we need to in order to respond to this request.

    response.on('error', function(err) {
      console.error(err); //to stderror
      response.statusCode = 404; //error on request.
    });


    //response.statusCode = 200; //ok
    response.setHeader('Content-Type', 'application/json');
    // you can write it, all at once with:
    // response.writeHead(200, {'Content-Type': 'application/json'})

    var responseBody = {
      headers: headers,
      method: method,
      url: url,
      body: body
    };

    response.write(JSON.stringify(responseBody));
    response.end();
    // you can write it, all at once with:
    // response.end(JSON.stringify(responseBody))

  });
}).listen(8080);
```

Remember that **`request`** is a `ReadableStream` and **`response`** is a `WritableStream`, so you can get advantage of **pipes** if you need them.


 












