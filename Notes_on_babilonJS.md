# Notes on WebGL

IT uses GPU

babilon.js

download from github.

we define in js, a 'namespace', so, we define:

var = My3Dnamespace

and if it has been allready defined, we use it

var My3Dnamespace = My3Dnamespace ...

or if it hasn't been defined we use an empty object

VAR My3Dnamespace = My3Dnamespace || {};

var M3D = My3Dnamespacace;

with this the code will have a limited scope in the code enviroment.

for babilon.js, we need a canvas object.

we need to create an initialization function:



M3D.init = function () {
  
    //get canvas
    var canvas = document.getElementById('mycanvas');
    
    //create Babilon.js engine object
    var engine = new BABYLON.Engine(canvas, true);
    
    //create scene:
    var scene = new BABYLON.Scene(engine);
    
    




