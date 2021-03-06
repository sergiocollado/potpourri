# Notes on BabylonJS

main reference: www.doc.babylonjs.com </br>
tutorials: http://doc.babylonjs.com/tutorials/cameras </br>
playground: http://www.babylonjs-playground.com/?1

It uses GPU

babylon.js

download from github.

Or you have to define the script:

```javascript
	<script src="https://cdn.babylonjs.com/babylon.js"></script>
```

we define in js, a 'namespace', so, we define:


```javascritp
var M3D;
```

and if it has been already defined, we use it

```javascript
var M3D = M3D ...
```

or if it hasn't been defined we use an empty object

```javascript
var M3D = M3D || {};
```

with this the code will have a limited scope in the code enviroment.

for babilon.js, we need a canvas object, so we have to define one:

```html
<div style="position:relative;"> 
	<canvas  id="mycanvas" width="1400" height="900" style="position:
	absolute; left:100px; width:100%; top:30px">
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
    
    //create a second sphere: 
    var sphere2 = new BABYLON.Mesh.CreateSpehere('Sphere1',16,2,scene);
    sphere2.position = new BABYLON.Vector3(3,3,3);
    
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

```javascript
camera.attachControl(canvas) 
```
You use 'setTarget' to define where the camera faces.

```javascript
var box = BABYLON.Mesh.CreateBox('box', 1, scene);
box.position =  new  BABYLON.Vector3(7,2,-5);
box.scaling.y = 2;

var ciclinder =  BABYLON.Mesh.CreateCylinderx('cyl', 5, 1, 3, 16, scene);

var lines = BABYLON.Mesh.CreateLines('lines', [
			new BABYLON.Vector3(0,5,0),
			new BABYLON.Vector3(1,5,0),
			new BABYLON.Vector3(0,5,2),
			new BABYLON.Vector3(2,2,0),
			new BABYLON.Vector3(1,5,-5),
			], scene);

//in case the nav window is resized, we handle it with:

addEventListener('resize',function(){
	engine.resize();
	});
```
You can create other basic shapes apart from the sphere, as example:

```javascript
var box = BABYLON.Mesh.CreateBox('box',1,scene);
box.position = new BABYLON.Vector3(10,2,-5);

var cylinder = BABYLON.Mesh.CreateCylinder('cyl',5,1,3,5,scene);

var sphere = BABYLON.Mesh.CreateSphere('spher1',16,4,scene);

var lines = BABYLON.Mesh.CreateLines('lines', [ new BABYLON.Vector3(0,5,0),
						new BABYLON.Vector3(0,5,0),
						new BABYLON.Vector3(0,5,0) ], scene);
						
//listen for resize event
window.addEventListener('resize',function() {
  engine.resize();
});
```
if I wanted to scalate a mesh in an axis, I would code it as:

```javascript
box.position.y = 3;
```

the scaling ocours outwards, and centered in the middle, so it grows up and down.

You can do it also with a vector:

```javascript
sphere.scaling = new BABYLON.Vector(1,1,3);
``` 

Rotations are also possible, you specify them in degrees

```javascript
box.rotation.x = 45
```
You can also create materials

```javascript
var sphereMaterial = new BABYLON.StandardMaterial('sphereMat',scene);

sphere.material = sphereMaterial;

sphereMaterial.diffuseColor = new BABYLON.Color3(0,0,1) //rgb(0-1.0);
sphereMaterial.alpha = 0.5;
```

for founding textures you can go to: www.texturelib.com

```javascript

var grass = new BABYLON.Texture('img/grass.png','scene');
grass.diffuseTexture.uScale = 2;
grass.diffuseTexture.vScale = 5;

ground.material = grass
```


Colors and textures have other properties as well:
 - **specularColor** specular color (how light is reflected in the object)
 - **specularPower** specular power reflection (how much light reflect)
 
```javascript
grass.specularColor = new BABILON.Color3(0,0,0); //no refection
```
 
Or you can make objects, sources of light, coding it as:

```javascript
var emissiveMaterial = new BABYLON.Material('emmissiveMat', scene);
emissiveMaterial.emissiveColor = new BABYLON.Color3(0,0,1);
```
 
 
 cilinder.material = emissiveMaterial
 
 

## Loading 3D models

It is possible to import 3d models. As example:

The source code of the loaders is here: https://github.com/BabylonJS/Babylon.js/tree/master/loaders/src

```html
<!DOCTYPE html>
<html>
  <head>
	<meta http-equiv="Content-Type" content="text/html" charset="utf-8"/>
    <title>Babylon - 3D objects</title>
	
	<script src="https://cdn.babylonjs.com/babylon.js"></script>
	<script src="babylon.objFileLoader.min.js"></script> 
	
	<script>
	var M3D = M3D || {};
	
	M3D.init = function () {
  
    //get canvas
    var canvas = document.getElementById('mycanvas');
    
    //create Babilon.js engine object
    var engine = new BABYLON.Engine(canvas, true);
    
	engine.loadingUIText = "Robot design by Sergio G. Collado";
	engine.loadingUIBackgroundColor = "lightblue";
	
    //create scene:
    var scene = new BABYLON.Scene(engine);
	scene.clearColor = BABYLON.Color3.Random(); //sets a random background color.
	scene.ambientColor = new BABYLON.Color3(0.3, 0.3, 0.3);
    
	
    //add camera - the camera is the object that allows you to view the scene. Your view depends then on the camera position.
    //var camera = new BABYLON.FreeCamera('Freecamera', new BABYLON.Vector3(0,3,0),scene);
    //attach control to the camera
	//camera.attachControl(canvas);
	
	//Adding an Arc Rotate Camera
	// Parameters : name, alpha, beta, radius, target, scene
    var camera = new BABYLON.ArcRotateCamera("Camera", 0, 2, 20, BABYLON.Vector3.Zero(), scene);
    camera.attachControl(canvas, false);
	scene.activeCamera.alpha += .01;
	//to add touch capabilities, you should add: “hand.js”.
 	
    //enviroment light from above. 'HemisphericLight' is a sort of general, natural ambient light.
    var light = new BABYLON.HemisphericLight('light', new BABYLON.Vector3(0,50,0),scene); 
    
	//load 3d model- the class AssetsManager is used for import meshes into a scene or load text and binary files.
	//ref: https://doc.babylonjs.com/tutorials/how_to_use_assetsmanager
	
	BABYLON.OBJFileLoader.OPTIMIZE_WITH_UV = true;
	
	var loader = new BABYLON.AssetsManager(scene);

	
	BABYLON.SceneLoader.Load( "", "robotv22.obj", engine, function (newScene) { 
	   // ref: https://doc.babylonjs.com/extensions/obj
	});
	
	var robotMesh = loader.addMeshTask("robot", "", "", "robotv22.obj");
	
	/*BABYLON.SceneLoader.ImportMesh("", "robotv22.obj", scene, function (meshes) { 
	 console.log("ImportMesh");// ...
	});*/
	
	robotMesh.onSuccess = function (task) {
		task.loadedMeshes[0].position = BABYLON.Vector3.Zero();
		camera.setTarget(task.loadedMeshes[0].position);
		task.loadedMeshes[0].recomputeNormals();
		console.log("loaded OBJ oks");
	};
	
	robotMesh.onError = function (e) {
		var mymesh=e.loadedMeshes[0];
		mymesh.position = BABYLON.Vector3.Zero();
		mymesh.sideOrientation = BABYLON.Mesh.FRONTSIDE;
		//mymesh.rotation.y = Math.PI/2;
		mymesh.position.y -= 100;
		camera.setTarget(mymesh, true, true);
		camera.radius = 150;
		camera.keysUp = '38';
		camera.keysDown = '40';
	
		console.log("error loading Meshes");
		console.log(e);
		mycamera = camera;
		console.log("error loading Meshes");
		console.log(e);
	};
	
	loader.onTaskError = function(e){
	console.log("Loader Error");
	console.log(e);
	}
	
	loader.onTaskSuccess = function(a){
	console.log("Loader OK");
	console.log(a);
	}
	
	loader.onFinish = function() {
		//focus camera on 3d model
		//camera.setTarget();

	   //render
		engine.runRenderLoop(function(){
		  scene.render();
		});
	};
	
	// Move the light with the camera
    scene.registerBeforeRender(function () {
       // light.position = camera.position;
    });

	loader.load();
	
	
	/*
    //create something to see - objects are defined under 'Mesh', you need to define if its made of triangles, and how many.
    var sphere = BABYLON.Mesh.CreateSphere('sphere1',16,2,scene);
    // 16, is the segment of the sphere.
    // 2, is the radius
    
    sphere.position.y=1;
    sphere.position = new BABYLON.Vector3(0,0,0);
    
    //create ground
    var ground = BABYLON.Mesh.CreateGround('ground', 20,20, 2, scene);
    
    //create a sphere: 
    var sphere2 = new BABYLON.Mesh.CreateSphere('Sphere1',16,2,scene); 	
    sphere2.position = new BABYLON.Vector3(3,3,3);
	
	*/
	  
	return scene;
}

	//listen for load of DOM
	window.addEventListener('DOMContentLoaded', function (){
		M3D.init();
	});

	//listen for resize event
	window.addEventListener('resize',function() {
		engine.resize();
	});
		 
    </script>
	
  </head>
  
  <body>
    <p style="color: blue;"> Demo of Babylon.js</p>
	<div style="position:relative;"> 
		<canvas  id="mycanvas" width="1400" height="900" style="position:
		absolute; left:100px; width:100%; top:30px">
		Canvas not supported; please update your browser.
		</canvas>
	</div>
  </body>
  
</html>
```

			
