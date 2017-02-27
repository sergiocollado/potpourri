
#Notes on Node.js

Node.js is a server-side framework, used to create intensive web applications (steamming, video, VoiP...), and is build on the Google's Chrome
Javascript V8 engine. Node.js runs over a runtime environment.

##Important features are:
- Asincrhonous and event-driven.
- Non blocking.
- Single threaded, but easily scalable.
- No buffering- Node.js doesn't buffer any data.
- Ligthweight and efficient.

##Node.js is best used in the following applications:

- I/O applications
- Data streamming applications
- Data Intensive Real-Time applications (DIRT)
- JSON API based applications.
- Single page applications.

##Node.js is best not used in:

 - CPU intensive applications.

##Installation

Its reference website is: https://nodejs.org/

From there you can download the last package- recomended the LTS(Long Term Support) release.

In MS Windows, you just have to downloade the: nod-vx.xx.x-x64.msi

In Linux, you have:
 + Check you have the building tools: 'apt-get install build-essential'
 + Get the source code, for example from its web: 'wget http://nodejs.org/dist/vx.xx.x/node-vx.xx.tar.gz
 + uncompress it.
 + Compile it:
   -  './configure'
   - 'make'
   - 'make install'


