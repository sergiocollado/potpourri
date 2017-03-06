
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

###Rectangles: 

>`<rect x="60" y="10" rx="10" ry="10" width="30" height="30"/>`

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

> `<circle cx="25" cy="75" r="20"/>`

**r** </br>
The radius of the circle.</br>
**cx** </br>
The x position of the center of the circle.</br>
**cy** </br>
The y position of the center of the circle. </br>




