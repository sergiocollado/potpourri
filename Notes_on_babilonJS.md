# Notes on BabylonJS

IT uses GPU

babylon.js

download from github.

we define in js, a 'namespace', so, we define:

var = My3Dnamespace

and if it has been allready defined, we use it

var My3Dnamespace = My3Dnamespace ...

or if it hasn't been defined we use an empty object

VAR My3Dnamespace = My3Dnamespace || {};

var M3D = My3Dnamespacace;

with this the code will have a limited scope in the code enviroment.

for babilon.js, we need a canvas object, so we have to define one:

```html
<div style="position:relative;"> 
	<canvas  id="theCanvas" width="1400" height="900" style="position: absolute; left:100px; width:100%; top:30px">
	Canvas not supported; please update your browser.
	</canvas>
</div>
```

we need to create an initialization function:


```javascript
M3D.init = function () {
  
    //get canvas
    var canvas = document.getElementById('mycanvas');
    
    //create Babilon.js engine object
    var engine = new BABYLON.Engine(canvas, true);
    
    //create scene:
    var scene = new BABYLON.Scene(engine);
    
    //add camera - the camera is the object that allows you to view the scene. Your view depends then on the camera position.
    var camera = new BABYLON.FreeCamera('Freecamera', new BABYLON.Vector3(0,2,-15),scene);
    
    //enviroment light from above. 'HemisphericLight' is a sort of general, natural ambient light.
    var light = new BABYLON.HemisphericLight('light1', new BABYLON.Vector3(0,1,0),scene); 
    
    //create something to see - objects are defined under 'Mesh', you need to define if its made of triangles, and how many.
    var sphere = BABYLON.Mesh.CreateSphere('sphere1',16,2,scene);
    // 16, is the segment of the sphere.
    // 2, is the radius
    
    sphere.position.y=1;
    shere.position = new BABYLON.Vector3(0,0,0);
    
    //create ground
    var ground = BABYLON.Mesh.CreateGround('ground', 20,20, 2, scene);
    
    //create a sphere: 
    var sphere = new BABILON.Mesh.CreateSpehere('Sphere1',16,2,scene);
    scene2.position = new BABILON.Vector3(3,3,3):
    //render
    engine.runRenderLoop(function(){
      scene.render();
      });
}
```
But we will load it, just when all the content is loaded. So we have to listen for the event 

```html
<script> window.addEventListener('DOMContentLoaded', function (){
         M3D.init();
         });
         </script>
```


we would like to control the camera:

camera.attachControl(canvas) 

You use 'setTarget' to define where the camera faces.

var box = BABILON.Mesh.CreateBox('box', 1, scene);
box.position =  new  BABYLON.Vector3(7,2,-5);
box.scaling.y = 2;

var ciclinder =  BABILON.Mesh.CreateCylinderx('cyl', 5, 1, 3, 16, scene);

var lines = BABILONS.Mesh.CreateLines('lines', [
			new BABILON.Vector3(0,5,0),
			new BABILON.Vector3(1,5,0),
			new BABILON.Vector3(0,5,2),
			new BABILON.Vector3(2,2,0),
			new BABILON.Vector3(1,5,-5),
			], scene);
			
addEventListener('resize',function(){
	engine.resize();
	});
			
			
