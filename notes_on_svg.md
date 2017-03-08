
#NOTES SVG: Scalable Vector Graphics

#### **Foreword** </br>
This are my personal notes on the svg specs, and are heavily based in the best resource:
https://developer.mozilla.org/en-US/docs/Web/SVG/Tutorial


An example of svg definition- the center of coordinates is top-left.

```html
<svg version="1.1"
     baseProfile="full"
     width="300" height="200"
     xmlns="http://www.w3.org/2000/svg">

  <rect width="100%" height="100%" fill="red" />

  <circle cx="150" cy="100" r="80" fill="green" />

  <text x="150" y="125" font-size="60" text-anchor="middle" fill="white">SVG</text>

</svg>
```

The tag `<svg>` is the root tag.

The background is set with: `<rect width="100%" height="100%" fill="red" />`

We draw a circle with: `<circle cx="150" cy="100" r="80" fill="blue" />`

We write a text with: `<text x="150" y="125" font-size="60" text-anchor="middle" fill="white">S</text>`

##BASIC SHAPES

Different tags, define diferent shapes and take different atributes.
Remember that the center of coordenates is top-left, and increases from left to right and from top to bottom.


###Line

```svg
<line x1="10" x2="50" y1="110" y2="150"/>
```
**x1** </br>
The x position of point 1. </br>
**y1** </br>
The y position of point 1. </br>
**x2** </br>
The x position of point 2. </br>
**y2** </br>
The y position of point 2. </br>


###Polyline

Polylines are groups of connected straight lines. Since that list can get quite long, all the points are included in one attribute:

```svg
<polyline points="60 110, 65 120, 70 115, 75 130, 80 125, 85 140, 90 135, 95 150, 100 145"/>
```

**points** </br>
A list of points, each number separated by a space, comma, EOL, or a line feed character. Each point must contain two numbers, an x coordinate and a y coordinate. So the list (0,0), (1,1) and (2,2) could be written: "0 0, 1 1, 2 2".


###Rectangles: 

```svg
`<rect x="60" y="10" rx="10" ry="10" width="30" height="30"/>`
```

**x** <br \>
The x position of the top left corner of the rectangle. <br \>
**y**<br \>
The y position of the top left corner of the rectangle.<br \>
**width**<br \>
The width of the rectangle<br \>
**height**<br \>
The height of the rectangle<br \>
**rx**<br \>
The x radius of the corners of the rectangle<br \>
**ry**<br \>
The y radius of the corners of the rectangle<br \>


###Circle:

```svg
<circle cx="25" cy="75" r="20"/>`
```

**r** </br>
The radius of the circle.</br>
**cx** </br>
The x position of the center of the circle.</br>
**cy** </br>
The y position of the center of the circle. </br>


###Ellipse
```svg
<ellipse cx="75" cy="75" rx="20" ry="5"/>
```
**rx** </br>
The x radius of the ellipse. </br>
**ry** </br>
The y radius of the ellipse. </br>
**cx** </br>
The x position of the center of the ellipse. </br>
**cy** </br>
The y position of the center of the ellipse. </br>



###Polygon

```svg
<polygon points="50 160, 55 180, 70 180, 60 190, 65 205, 50 195, 35 205, 40 190, 30 180, 45 180"/>
```

**points**
A list of points, each number separated by a space, comma, EOL, or a line feed character. Each point must contain two numbers, an x coordinate and a y coordinate. So the list (0,0), (1,1) and (2,2) could be written: "0 0, 1 1, 2 2". The drawing then closes the path, so a final straight line would be drawn from (2,2) to (0,0).

###Paths

Paths, are the most flexible components of svg, with them you can draw lines, arcs, curves ...
Paths, are defined by commands or directives (d). For example M 10 10, means go to point (10,10). The commands can be issued in two
forms:
 · Uppercase letters: they use absolute coordinates. The origin of the coordenate systems is the top-left point.
 · Lowercase letters: they use relative coordinates from the last point


####Line commands

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
```svg
<path d="M10 10 H 90 V 90 H 10 Z"/>
```
· In relative coordinates:
```svg
<path d="M10 10 h 80 v 80 h -80 Z"
```










