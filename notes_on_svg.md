
#### **Foreword** 

This are my personal notes on the svg specs, and are heavily based in the best resource:
[Mozilla Development Network](https://developer.mozilla.org/en-US/docs/Web/SVG/Tutorial)

and others:

- online svg text editor: https://www.freecodeformat.com/svg-editor.php
- The lead reference for SVGs is: [ref SVG11](https://www.w3.org/TR/SVG11/)
- also check: [google svgweb](https://code.google.com/archive/p/svgweb/) 
- comparation between SVG and canvas: [link](https://www.sitepoint.com/canvas-vs-svg-choosing-the-right-tool-for-the-job/)
- upcomming standard SVG 2: [ref SVG2](https://svgwg.org/svg2-draft/Overview.html)
- candidate release svg2 [link](https://www.w3.org/TR/SVG2/)
- best progamm evaaa: https://inkscape.org/
- svg testing: https://github.com/w3c/svgwg/wiki/Testing
- more no svg testing: http://codinginparadise.org/projects/svgweb/tests/
- the SVG working group: https://www.w3.org/Graphics/SVG/
- more about it: https://inkscape.org/en/develop/about-svg/
- super examples: http://codinginparadise.org/projects/svgweb/samples/demo.html?name=undefined&svg.render.forceflash=false
- other nice one: http://codinginparadise.org/projects/svgweb/docs/QuickStart.html
- another: http://srufaculty.sru.edu/david.dailey/svg/SVGAnimations.htm
- really fine stuff: http://srufaculty.sru.edu/david.dailey/svg/createElementBrowser.html
- svg authoring guidelines: https://jwatt.org/svg/authoring/
- svg test demo:  https://jwatt.org/svg/demos/path-tester.xml
- web based svg editor: http://www.drawsvg.org/drawsvg.html
- other: https://www.janvas.com/v6.1/janvas_app_6.1_public/index.html
- other: http://editor.method.ac/



# NOTES SVG: Scalable Vector Graphics

An example of svg definition- the center of coordinates is top-left.

```html
<svg version="1.1"
     baseProfile="full"
     width="300" height="200"
     xmlns="http://www.w3.org/2000/svg">
  <rect width="100%" height="100%" fill="ligthblue" />
  <circle cx="150" cy="100" r="80" fill="yellow" stroke="orange" />
  <text x="150" y="120" font-size="40" text-anchor="middle" fill="blue">SVG</text>
</svg>
```

The tag `<svg>` is the root tag, and the definition of an SVG element

the `version="1.1"` defines the version of the SVG standard

the `width="300" height="200"`defines the size of the SVG drawing.

Then follows the actual drawing (remember that the center of coordenates is at the top-left)

The background is set with: `<rect width="100%" height="100%" fill="ligthblue" />`

We draw a circle with: `<circle cx="150" cy="100" r="80" fill="yellow" />`

We write a text with: `<text x="150" y="125" font-size="60" text-anchor="middle" fill="white">SVG</text>`


![first_example_svg](https://rawgit.com/sergiocollado/potpourri/master/image/svg_001.svg?sanitize=true)


From this example we can draw some conclusions: 

1. the figures are rendered as they are defined. First at the bottom, and the last at the top of the image.
2. **fill** fills the interior of its graphical element
3. **stroke** paints the aoutline of its graphical element.
4. Colors have short-names according to CSS3; as example:
 - black
 - silver
 - gray
 - white
 - maroon
 - red
 - fuchsia
 - green 
 - lime
 - olive
 - navy
 - blue
 - lightblue
 - teal
 - aqua
 
 and many more.
 
 For a exact definition of a color is used:
 
 RGB, RGBa

```
em { color: rgb(255,0,0) }      /* integer range 0 - 255 */
em { color: rgba(255,0,0,1)     /* the same, with explicit opacity of 1 */
em { color: rgb(100%,0%,0%) }   /* float range 0.0% - 100.0% */
em { color: rgba(100%,0%,0%,1) } /* the same, with explicit opacity of 1 */
p { color: rgba(0,0,255,0.5) }        /* semi-transparent solid blue */
p { color: rgba(100%, 50%, 0%, 0.1) } /* very transparent solid orange */
```

 HSL, HSLa
```
* { color: hsl(0, 100%, 50%) }   /* red */
* { color: hsl(120, 100%, 50%) } /* lime */ 
* { color: hsl(120, 100%, 25%) } /* dark green */ 
* { color: hsl(120, 100%, 75%) } /* light green */ 
* { color: hsl(120, 75%, 75%) }  /* pastel green, and so on */
em { color: hsl(120, 100%, 50%) }     /* green */
em { color: hsla(120, 100%, 50%, 1) } /* the same, with explicit opacity of 1 */
p { color: hsla(240, 100%, 50%, 0.5) } /* semi-transparent solid blue */
p { color: hsla(30, 100%, 50%, 0.1) }  /* very transparent solid orange */
```

5. Is required to include the following three attributes on the root <svg> tag in your SVG documents:

```xml
<svg xmlns="http://www.w3.org/2000/svg"
     xmlns:xlink="http://www.w3.org/1999/xlink"
     xmlns:ev="http://www.w3.org/2001/xml-events">
```
     
[reference](https://www.w3.org/TR/css-color-3/)

## BASIC SHAPES

Different tags, define diferent shapes and take different atributes.
Remember that the center of coordenates is top-left, and increases from left to right and from top to bottom.


### Line

```xml
<line x1="10" x2="50" y1="110" y2="150"/>
```


| Line |    |
| ---  | --- |
|  **x1**   | The x position of point 1.     |
|  **y1**   | The y position of point 1.    |
|  **x2**   | The x position of point 2.     |
|  **y2**   | The y position of point 2.     |


### Polyline

Polylines are groups of connected straight lines. Since that list can get quite long, all the points are included in one attribute:

```xml
<polyline points="60 110, 65 120, 70 115, 75 130, 80 125, 85 140, 90 135, 95 150, 100 145"/>
```

**points** - A list of points, each number separated by a space, comma, EOL, or a line feed character. Each point must contain two numbers, an x coordinate and a y coordinate. So the list (0,0), (1,1) and (2,2) could be written: "0 0, 1 1, 2 2".


### Rectangles: 

```xml
<svg version="1.1"
     baseProfile="full"
     width="300" height="200"
     xmlns="http://www.w3.org/2000/svg">
  <rect width="100%" height="100%" r1="10" ry="30" fill="lightblue" />
</svg>
```


| Rectangle |    |
| --- | --- |
|**x**		| The x position of the top left corner of the rectangle. |
|**y** 		| The y position of the top left corner of the rectangle.|
|**width** 	| The width of the rectangle. |
|**height** 	| The height of the rectangle. |
|**rx** 	| The x radius of the corners of the rectangle. |
|**ry** 	| The y radius of the corners of the rectangle. |
|**fill** 	| The filling of the rectangle. |


![svg rectangle example](https://rawgit.com/sergiocollado/potpourri/master/image/svg_002_rectangle.svg)

ref: (https://www.w3.org/TR/SVG/shapes.html#RectElement)

### Circle:

```xml
<circle cx="25" cy="75" r="20" />
```

| Circle |    |
| --- | --- |
|**r** | The radius of the circle.|
|**cx** | The x position of the center of the circle.|
|**cy** | The y position of the center of the circle.|


### Ellipse

```xml
<ellipse cx="75" cy="75" rx="20" ry="5"/>
```


| Ellipse |    |
| --- | --- |
|**rx**		| The x radius of the ellipse. |
|**ry** 	| The y radius of the ellipse.|
|**cx** 	| The x position of the center of the ellipse. |
|**cy** 	| The y position of the center of the ellipse. |


### Polygon

```xml
<polygon points="50 160, 55 180, 70 180, 60 190, 65 205, 50 195, 35 205, 40 190, 30 180, 45 180"/>
```

**points**
A list of points, each number separated by a space, comma, EOL, or a line feed character. Each point must contain two numbers, an x coordinate and a y coordinate. So the list (0,0), (1,1) and (2,2) could be written: "0 0, 1 1, 2 2". The drawing then closes the path, so a final straight line would be drawn from (2,2) to (0,0).

### Paths

Paths, are the most flexible components of svg, with them you can draw lines, arcs, curves ...
Paths, are defined by commands or directives (d). For example M 10 10, means go to point (10,10). The commands can be issued in two
forms:
 · Uppercase letters: they use absolute coordinates. The origin of the coordenate systems is the top-left point.
 · Lowercase letters: they use relative coordinates from the last point


#### Line commands

There are five commands, that move in lines:

 - **'Move to'**: declared with the **'M'** or **'m'**,it doesn't draw anything, it just moves the drawing pointer.It is 
 used at the beginnig of the paths to set the starting point.
 - **'Line to'**: declared with the **'L'** or **'l'**, it draws a line from the current position to the new position.
 - **'Horizontal line'**: declared with the **'H'** or **'h'**, it draws a horizontal line. It just have one parameter (x).
 - **'Vertical line'**: declared with the **'V'** or **'v'**, it draws a vertical line. It just have one parameter (y).
 - **'Back to origin'**: declared with the **'Z'** or **'z'**, there is no difference between upper or lower case. Usually is placed at the end of the path, if it is needed to be closed. It doen't have parameters.
 
<!-- TODO: put examples-->

An example of path:

· In absolute coordenates:

```xml
<path d="M10 10 H 90 V 90 H 10 Z"/>
```
· In relative coordinates:

```xml
<path d="M10 10 h 80 v 80 h -80 Z"
```

Example:

```xml
<svg version="1.1"
     baseProfile="full"
     width="100" height="100"
     xmlns="http://www.w3.org/2000/svg">
 <rect width="100%" height="100%" stroke="yellow" fill="transparent" />
  <path d="M 0 50 h 10 l 7.5 15 l 15 -30 l 15 30 l 15 -30 l 15 30 
	l 7.5 -15 h15" stroke="black" fill="transparent" />
</svg>
```

Another Example - npn transistor

```xml
<svg version="1.1"
     baseProfile="full"
     width="80" height="100"
     xmlns="http://www.w3.org/2000/svg">
 <rect width="100%" height="100%" stroke="yellow" fill="lightblue" />
 <circle cx="40" cy="50" r="35" stroke="black" fill="transparent" />
 <path d="M 0 50 h 30 m 0 -20 v 40 m 0 -5 l 20 20 l -10 -15 l
	-5 5 l 15 10 v 15 M 30 35 l 20 -20  v -20" stroke="black" fill="transparent" />
</svg>
```

And other example - pnp transistor

```xml
<svg version="1.1"
     baseProfile="full"
     width="80" height="100"
     xmlns="http://www.w3.org/2000/svg">
 <rect width="100%" height="100%" stroke="yellow" fill="lightblue" />
<circle cx="40" cy="50" r="35" stroke="black" fill="transparent" />
 <path d="M 0 50 h 30 m 0 -20 v 40 m 0 -5 l 20 20v 15 M 30 35 l 10 -15 l 5 5 l -15 10 l 20 -20  v -20" stroke="black" fill="transparent" />
</svg>
```

#### Curve commands

#### Cubic Benzier Curve

C x1 y1 x2 y2 x y

**x1 y1** <br>
first control point </br>
**x2 y2** <br>
second control point </br>
**x y** <br>
end point of the curve </br>

```xml
<svg width="190" height="160" xmlns="http://www.w3.org/2000/svg">
    <path d="M10 10 C 20 20, 40 20, 50 10" stroke="black" fill="transparent"/>
</svg>
```

Also you can use the **S** command to concatenate benzier curves- but the **S** command must always follow another **C** or **S** command. It just means that the last control point of the previous curve,  will be the first control point of the following curve.

**S x2 y2 x y**


```xml
<svg width="190" height="160" xmlns="http://www.w3.org/2000/svg">
  <path d="M10 80 C 40 10, 65 10, 95 80 S 150 150, 180 80" stroke="black" fill="transparent"/>
</svg>
```

##### Cuadratic Benzier Curve

Q x1 y1 x y 

**x1 y1** <br>
Control point that determines the slope of the curve at the starting and ending point. </br>
**x y** <br>
End point of the curve. <br>


```xml
<svg width="190" height="160" xmlns="http://www.w3.org/2000/svg">
  <path d="M10 80 Q 95 10 180 80" stroke="black" fill="transparent"/>
</svg>
```

You can also concatenate cuadratic benzier curves, with the **T** command.

T x y

**x y** <br>
Takes the slope of the previous curve, and **(x, y)** is the end point.

```xml
<svg width="190" height="160" xmlns="http://www.w3.org/2000/svg">
  <path d="M10 80 Q 52.5 10, 95 80 T 180 80" stroke="black" fill="transparent"/>
</svg>
```

##### Arcs

Arcs are sections of ellipses or circles. For a given x-radius and y-radius, there are two ellipses that connects any given two points, 
for each ellipse there are two paths for connect those two points. So there are four possibilities.


**A rx ry x-axis-rotation large-arc-flag sweep-flag x y**


```xml
<svg width="325" height="325" xmlns="http://www.w3.org/2000/svg">
  <path d="M80 80
           A 45 45, 0, 0, 0, 125 125
           L 125 80 Z" fill="green"/>
  <path d="M230 80
           A 45 45, 0, 1, 0, 275 125
           L 275 80 Z" fill="red"/>
  <path d="M80 230
           A 45 45, 0, 0, 1, 125 275
           L 125 230 Z" fill="purple"/>
  <path d="M230 230
           A 45 45, 0, 1, 1, 275 275
           L 275 230 Z" fill="blue"/>
</svg>
```

### Grouping of elements

The ‘g’ element is a container element for grouping together related graphics elements.

A group of elements, as well as individual objects, can be given a name using the ‘id’ attribute. Named groups are needed for several purposes such as animation and re-usable objects.

An example:

```xml
<?xml version="1.0" standalone="no"?>
<svg xmlns="http://www.w3.org/2000/svg"
     version="1.1" width="5cm" height="5cm">
  <desc>Two groups, each of two rectangles</desc>
  <g id="group1" fill="red">
    <rect x="1cm" y="1cm" width="1cm" height="1cm"/>
    <rect x="3cm" y="1cm" width="1cm" height="1cm"/>
  </g>
  <g id="group2" fill="blue">
    <rect x="1cm" y="3cm" width="1cm" height="1cm"/>
    <rect x="3cm" y="3cm" width="1cm" height="1cm"/>
  </g>

  <!-- Show outline of viewport using 'rect' element -->
  <rect x=".01cm" y=".01cm" width="4.98cm" height="4.98cm"
        fill="none" stroke="blue" stroke-width=".02cm"/>
</svg>
```

A ‘g’ element can contain other ‘g’ elements nested within it, to an arbitrary depth.


hr 

# JAVASCRIPT FOR CREATING SVGs:

With the DOM2, the following funtions are available:

 - createAttributeNS
 - createElementNS
 - getAttributeNodeNS
 - getAttributeNS
 - getElementsByTagNameNS (also added to Element)
 - getNamedItemNS
 - hasAttributeNS
 - removeAttributeNS
 - removeNamedItemNS
 - setAttributeNS
 - setAttributeNodeNS
 - setNamedItemNS
 
 


## CREATING SVGs

If you want to creatre a new element, you can always use: `document.createElement` function. SVG, uses namespaces, so you'll have to
use 'document.createElementsNS' function.

references: </br>
- document.createElement    [:link:](https://developer.mozilla.org/en-US/docs/Web/API/Document/createElement) </br>
- document.createElementNS  [:link:](https://developer.mozilla.org/en-US/docs/Web/API/Document/createElementNS) </br>
- http://srufaculty.sru.edu/david.dailey/svg/createElementBrowser.html

An example is the following code:

```javascript
//Get svg element
var svg = document.getElementsByTagName('svg')[0]; 

//Create a path in SVG's namespace
var SvgElement = document.createElementNS("http://www.w3.org/2000/svg", 'path'); 

//Set path's data
SvgElement.setAttributeNS(null,"d","M 0 0 L 10 10"); 

//Set stroke width
SvgElement.style.strokeWidth = "5px"; 

//append to the svg.
svg.appendChild(SvgElement);
``` 
And this code will produce something like this:

```svg
<svg>
 <path d="M 0 0 L 10 10" style="stroke: #000; stroke-width: 5px;" />
</svg>
```

## ADDING TEXTS

Adding text is tricky, because the text is an sub child node. So then you have to create it, and explicitly add it as a child of the text element:

```javascript
var txtElem = document.createElementNS("http://www.w3.org/2000/svg", "text");
 
txtElem.setAttributeNS(null,"x",100);
txtElem.setAttributeNS(null,"y",100);
txtElem.setAttributeNS(null,"font-size",12);

var helloTxt = document.createTextNode("Hello World!");

txtElem.appendChild(helloTxt)
 
document.documentElement.appendChild(txtElem);
```

### REMOVING NODES

You just have to use the function:`removeChild()` <br>

```javascript
document.documentElement.removeChild(txtElem);
```

### RETRIEVING ATRIBUTES

To retrieve the value of the 'x' attribute on an SVG 'rect' element you must write:

```javascript
getAttributeNS(null, 'x');
```

## EXAMPLE OF CREATING A SVG PROGRAMMATICALY


Authors should provide a ‘metadata’ child element to the outermost svg element within a stand-alone SVG document. The ‘metadata’ child element to an ‘svg’ element serves the purposes of identifying document-level metadata.

As an example:
```html
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8"/>
    <title>SVG programming</title>
	<link rel="stylesheet" href="mystyles.css" type="text/css">
	<script type="text/javascript">
	function myFunction() 
	{
	var root = document.getElementById('element');
	console.log( "root: " + root);
	
	var elem = document.createElementNS('http://www.w3.org/2000/svg','svg'); 
	
	elem.setAttributeNS(null,'version','1.1');
	elem.setAttributeNS(null,'id','SVGsergio');	
	elem.setAttributeNS(null,"x",'50');
	elem.setAttributeNS(null,"y",'50');
	elem.setAttributeNS(null,"width",'50%');
	elem.setAttributeNS(null,"height",'50%');
	elem.setAttributeNS(null,'baseProfile','1.1');
	<!-- WRONG: - elem.setAttributeNS(null,'xlink:href','http://www.w3.org/2000/svg'); -->
	elem.setAttributeNS(null,'Metadata',
		'<rdf:RDF  xmlns:rdf = "http://www.w3.org/1999/02/22-rdf-syntax-ns#"  xmlns:rdfs = "http://www.w3.org/2000/01/rdf-schema#"xmlns:dc = "http://purl.org/dc/elements/1.1/" >  <rdf:Description dc:format="image/svg+xml" > creator> Sergio González Collado<\/dc:creator> <\/rdf:Description> <\/rdf:RDF>');
		
	root.appendChild(elem);
	
	console.log("svg created: " + document.getElementById('SVGsergio'));	
	}
	
	<!-- in the console you can check this, with -->
	<!-- 
	var x = document.getElementById('SVGsergio');
	console.log(x);
	-->
	</script>
	
  </head>
  <body>
		<h1>SVG creation test</h1>
		<div id='element'>
			<!-- the created svg, will be placed here -->
		</div>
		<button type="button" onclick="myFunction()">Try it</button>

  </body>
</html>
```

another example of svg creation with js

```javascript
//from svg.js
var ns = 'http://www.w3.org/2000/svg'
var div = document.getElementById('drawing') 
var svg = document.createElementNS(ns, 'svg')
svg.setAttributeNS(null, 'width', '100%')
svg.setAttributeNS(null, 'height', '100%')
div.appendChild(svg)
var rect = document.createElementNS(ns, 'rect')
rect.setAttributeNS(null, 'width', 100)
rect.setAttributeNS(null, 'height', 100)
rect.setAttributeNS(null, 'fill', '#f06')
svg.appendChild(rect)
```
More on the ref: http://codinginparadise.org/projects/svgweb/docs/QuickStart.html

Also check: http://srufaculty.sru.edu/david.dailey/svg/createElementBrowser.html

also a js library: SVG.js


## Most common svg attributes are:

**version** = "<number>"
Indicates the SVG language version to which this document fragment conforms.
In SVG 1.0 [SVG10], this attribute was fixed to the value '1.0'. For SVG 1.1, the attribute should have the value '1.1'.

**baseProfile** = profile-name
Describes the minimum SVG language profile that the author believes is necessary to correctly render the content. The attribute does not specify any processing restrictions; It can be considered metadata. For example, the value of the attribute could be used by an authoring tool to warn the user when they are modifying the document beyond the scope of the specified base profile. Each SVG profile should define the text that is appropriate for this attribute.
If the attribute is not specified, the effect is as if a value of 'none' were specified.

**x** = "<coordinate>"
(Has no meaning or effect on outermost svg elements.)
The x-axis coordinate of one corner of the rectangular region into which an embedded ‘svg’ element is placed.
If the attribute is not specified, the effect is as if a value of '0' were specified.

**y** = "<coordinate>"
(Has no meaning or effect on outermost svg elements.)
The y-axis coordinate of one corner of the rectangular region into which an embedded ‘svg’ element is placed.
If the attribute is not specified, the effect is as if a value of '0' were specified.

**width** = "<length>"
For outermost svg elements, the intrinsic width of the SVG document fragment. For embedded ‘svg’ elements, the width of the rectangular region into which the ‘svg’ element is placed.
A negative value is an error. A value of zero disables rendering of the element.
If the attribute is not specified, the effect is as if a value of '100%' were specified.

**height** = "<length>"
For outermost svg elements, the intrinsic height of the SVG document fragment. For embedded ‘svg’ elements, the height of the rectangular region into which the ‘svg’ element is placed.
A negative value is an error. A value of zero disables rendering of the element.
If the attribute is not specified, the effect is as if a value of '100%' were specified.

**preserveAspectRatio** = "[defer] <align> [<meetOrSlice>]"

**contentScriptType** = "content-type"

**contentStyleType** = "content-type"

**zoomAndPan** = "disable | magnify"



TODO: </br>

- new standard comming: https://www.w3.org/TR/2016/CR-SVG2-20160915/ </br>
- its github: https://github.com/w3c/svgwg/
 
 
 >> https://www.w3.org/TR/SVG/struct.html <<
 
 
- [] https://www.w3.org/TR/SVG11/interact.html </br>
- [] https://www.w3.org/TR/SVG11/linking.html  </br>
- [] https://www.w3.org/TR/SVG11/animate.html  </br>
- [] https://www.w3.org/TR/SVG/script.html#ScriptElement </br>
- [] [DOM standard](https://dom.spec.whatwg.org/#dom-document-createelementns) </br>
- [] https://www.w3.org/TR/SVG/struct.html#InterfaceSVGSVGElemen </br>
- [] http://stackoverflow.com/questions/6701705/programmatically-creating-an-svg-image-element-with-javascript </br>
- [] http://stackoverflow.com/questions/2753732/how-to-access-svg-elements-with-javascript?rq=1 </br>
- [] http://stackoverflow.com/questions/21800271/svg-display-text-description-on-click </br>
- [] https://developer.mozilla.org/en-US/docs/Web/SVG/Element/desc </br>
- [] https://developer.mozilla.org/en-US/docs/Web/API
- [] About metadatas -> https://www.w3.org/TR/SVG11/metadata.html#InterfaceSVGMetadataElement
- [] Comparation between SVG and canvas: https://www.sitepoint.com/canvas-vs-svg-choosing-the-right-tool-for-the-job/
- [] Inkscape galleries: http://wiki.inkscape.org/wiki/index.php/Galleries
- https://inkscape.org/en/gallery/
- Wiki Inkscape: http://wiki.inkscape.org/wiki/index.php/Inkscape
- book: https://es.scribd.com/doc/58271695/Learn-SVG
- Animation examples: http://srufaculty.sru.edu/david.dailey/svg/SVGAnimations.htm#JSAnim
- more awesome examples: http://srufaculty.sru.edu/david.dailey/art.html
- http://srufaculty.sru.edu/david.dailey/svg/bucketful.htm
- really good tutorial: http://tutorials.jenkov.com/svg/index.html
- super examples: http://codinginparadise.org/projects/svgweb/samples/demo.html?name=undefined&svg.render.forceflash=false
- notes on quick start and scripting svg's: http://codinginparadise.org/projects/svgweb/docs/QuickStart.html
- cool examlple of bubble-menus: http://starkravingfinkle.org/projects/demo/svg-bubblemenu-in-html.xml





