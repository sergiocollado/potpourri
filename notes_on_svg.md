
#NOTES SVG: Scalable Vector Graphics

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

Paths, are the most flexible components of svg, in it you can draw lines, arcs, curves ...
Paths, are defined by commands or directives (d). For example M 10 10, means go to point (10,10). The commands can be issued in two
forms:
 · Uppercase letters: they use absolute coordinates. The origin of the coordenate systems is the top-left point.
 · Lowercase letters: they use relative coordinates from the last point


####Line commands












