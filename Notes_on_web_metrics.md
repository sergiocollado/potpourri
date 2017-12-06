# Notes on web metrics


iF HELP IS NEEDED GO TO THE FOLLOWING LINKS:

https://caniuse.com/




I wanted my [website](https://sergiocollado.github.io/) indexed at google, so i found this reference:

http://webapps.stackexchange.com/questions/66799/how-can-i-have-a-public-searchable-github-account

You can actually request an indexing at: https://www.google.com/webmasters/tools/submit-url

Then I found about the google's webmaster site:  http://www.google.com/webmasters/

It recommended me, to do the following actions:

1- add website versions, that is: www http https </br>
2- select your preferred version </br>
3- select your target country </br>
4- share access with co-workers </br>
5- submit a filesite map </br>

One of the tasks to do is to generate a site-map. The main reference for doing this kind of file is at: https://www.sitemaps.org/protocol.html

To conform a robot.txt, that is a file to inform also the webcrawlers, you have to reference to: http://www.robotstxt.org/ </br>
Robots database [:link:](http://www.robotstxt.org/db.html)
Also [:link:](https://www.quora.com/What-is-the-best-open-source-web-crawler-and-why)
and: [Google's Search Optimization Starting Guide](https://static.googleusercontent.com/media/www.google.com/es//webmasters/docs/search-engine-optimization-starter-guide.pdf)

For Validating CSS, use this tool: http://jigsaw.w3.org/css-validator/#validate_by_uri+with_options

Also use:  http://validator.w3.org/#validate_by_uri+with_options

It can be also downloaded;  http://jigsaw.w3.org/css-validator/DOWNLOAD.html

Also: http://www.html-tidy.org/

You can also use the following tools:

- [jsbin](http://jsbin.com/?html,output)
- [thimble](https://thimble.mozilla.org/)
- [JSfiddle](https://jsfiddle.net/)


Also check the meta-tags: http://www.metatags.org/meta_name_robots

# Styling and CSS

## display

'display' propierty - it indicates how an element will be displayed. - Its the most important propierty for controlling the layout.

Allowed values are: 

- none: the element is not displayed, and its space is not reserved also. as example the <script> is display:none. This is opposed for example to the propierty: visibility:hidden, in which the element is not displayed, but it space is reserverd.
- block: the element starts always in a new line. Common cases are \<div\> \<h1\> \<h2\> ... \<header\> \<footer\> \<p\> \<section\>.
- inline: the element doesn't start in a new line, and only takes as much space as required, common cases are <a> <span> <img>.
- inline-block: displays the element as an inline-block containter
- list-item: behaves as an \<li\> element.
- run-in: behaves as an inline or block, depending on the context.
- flex: [CSS3] element displayed as a block-level flex container.
- inline-flex [CSS3] the element is displayed as an inline-level flex container.

Also for position an element at the center of something, many times is resolved with just: `margin:auto`

##  box-sizing:

values are:
- content-box: specifies the size of the box, but it doen't include border, padding or margin. It only defines the content.
- border-box: specifies the size (width and height) and includes content, padding, and border, but not the margin!

Is recomended the use of the 'box-sizing:border-box' 
<hr>
<br>
<br>

## Media Queries

Media queries is a method for presenting different elements depending on the capabilities of the viewer device.

Media queries can identify:
 - width and height of the view port.
 - width and height of the device.
 - orientation (if applicable, as in tables and phones: portrait or landscape mode)
 - resolution
 
 Media queries are a smart way to control the apearance of a web site, on diferent devices.
 
### Media Queries basic sintaxis

A media querie (MQ) consist on one or more expressions, that can be evaluated to either TRUE or FALSE.

```CSS
@media  [not][only] mediatype and ( expression ) {

  ... <!-- here goes the CSS definition -->
}
```

#### Media types

| Value  | Description | 
| :---         |     :---:      |  
| all   | used for all media devices   |    
|  print  |  used for printers  |    
|  screen  |  used for screen devices  |    
|  speech  |  used for screen readers  |    
    

### example 

```CSS

@media screen and (max-width: 699px) and (min-width: 520px), (min-width: 1151px) {
    #nav li a {
        padding-left: 30px;
        background: url(email-icon.png) left center no-repeat;
    }
}

```



## FlexBox

Defines a flexible box in CSS3, this a container that resizes itself according to the screen size. It make easiest to re-adapt the
layout of a webpage, for diferent view sizes.

Flexboxes are made of: 
  - a parent element
  - two or more child elements.
  
  
### Parent element (Flexbox)
Flex containers (the parent). It becames a flex container, declaring the propierty display as: 'diplay:flex'.
It can also have defined the following propierties:
  
As an html example:
```html
<div id=flex_parent style="display:flex">
	<div> Child 1 </div>
	<div> Child 2 </div>
	<div> Child 3 </div>
</div>
```

as example for CSS3:

```CSS
.flex_parent {
	display:flex;
}
```
so in the html code, it will be used as:

```html
<div id=flex_parent class="flex_parent">
	<div> Child 1 </div>
	<div> Child 2 </div>
	<div> Child 3 </div>
</div>
```

| Propierty  | explanation | possible values |
| :---         |     :---:      |  :---      |
| flex-direction   | defines in what direction the <br> container will stack the items    |column<br>column-reverse<br>row (default)<br>row reverse    |
| flex-wrap     | defines if, and how the<br> childrens will wrap | nowrap(default)<br>wrap<br>wrap-reverse      |
| flex-flow   | is a shortcut to set <br> flex-direction and flex-wrap | flex-direction + flex-wrap  |
| justify-content     | sets the alineation of the items      |  center<br>flex-start(default)<br>flex-end<br>space-around<br>space-between     |
| align-items   | aligns items in the opposite direction that the justify-content direction     | baseline<br>center<br>flex-start<br>flex-end<br>stretch(default)    |
| align-content     | aligns the children rows       | center<br>flex-start<br>flex-end<br>space-around<br>space-between<br>stretch(default)    |

So a good definition could be:

```CSS
.flex_parent {
   display: flex;
   flex-direction: row-reverse;
   flex-wrap: wrap;
   justify-content: space-around;
   align-items: baseline;
   align-content:space-around;
}
```



### Child elements (flex items)
Children elements of a flex parent container, inmediatry turn into flexible items.
Their propierties are:
 
| Propierty  | explanation | possible values |
| :---         |     :---:      |  :---      |
| order   |  sorts the items in the specified oreder  |  integer (0 default) |
| flex-grown    | specifies how much that item will grow relative to the rest of the flex items |  Number (0 default)   |
| flex-shrink   | specifies how much that item will schrink relative to the rest of the flex items | Number (1 default) |
| flex-basics     |  specifies the width and height of a flex item  | default: auto    |
| flex  |  is a shortform for _flex-grow_, _flex-schrink_ and _flex-basics_  |  default: 0 1 auto   |
| align-self     | overwrites the default aligment from the parent flex container  | auto(default)<br>baseline<br>center<br>flex-start<br>flex-end<br>stretch    |
  
 
 
	 - display: flex --> rendered as flex block.
 	 - display: flex-inline --> rendered as a flex inline block
	 
 - Flex items: those are the elements inside the flex container, normally arranged in a row.
 
<br>
<br>
<hr>
<br>
<br>

# RWD -Responsive Web Design - picture tag 

The \<picture\> tag, allows you to present different images sources according to a media query.
so the \<pictures\> tag, needs at two other tags at least: \<src\> and \<img\>
 - \<img\> is for backwards compatibility, for those browsers  that don't support the \<pictures\> tag
 - \<src\> will indcate what source to get, according to a media query.
 
The \<src\> tag, will have the following attributes:
- srcset : url of the source
- media : media query to apply
- sizes : a width descriptor.
- type : the MIME type.

Example:

```html
<picture>
  <source media="(min-width: 650px)" srcset="img_medium_car.jpg">
  <source media="(min-width: 465px)" srcset="img_small_car.jpg">
  <img src="img_car.jpg" alt="car" style="width:auto;">
</picture>
```

<br>
<br>
<hr>
<hr>
<br>
<br>

# jQuery

jQuery is a javascript library that simplifies the sintaxis and add funticonality.

You can add this library from a CDN, with:

```javascript 
<script src=""https://ajax.googleapis.com/ajax/libs/jquery-x.y.z.min.js"></script>
```

## syntaxis

To work with this, the structure, is first select an element, and then indacte an action; it is done in this way:

```javascript
$(selector).action();
```

for example to make an action at the document load, it is expressed as:

```javascript
$(document).ready( function() { 
	alert("Hello Wold!");
	});
```

## selectors

This are as follows:

```javascript
$("identifier")
```

so to select all the paragraphs in a documento, it would be done like:

```javascript
$("p")
```

To select a certain element with a given **id**, it would be expressed as:

```javascript
$("#my_element_id")
```

so if we want to hide that element when a button is clicked, it would be defined as:

```javascript
$(document).ready( function() {
    $("button").click( function () {
       $("#my_element_id").hide();
    )};
 )};
```

# events

Events are user actions, as for example:

document/window events: load, ready, resize, scroll, unload.
form events: submit, change, focus, blur.
keyboard events: keypress, keydown, keyup
mouse: mouseenter, mouseleave, hover ....

...

events, are defined as described above:


```javascript
$(selector).action();
```



there is also the `on` event, that allows you to define actions, for several events:

```javascript
$("#my_element").on( {
	focus: function() {
		$(this).css("color", "lightblue");
		},
	blur: function() {
		$(this).css("color", "gray");
		},
	hover: function() {
		$(this).css("font-size", "1.2em");
		}
	});
```

## Callbacks

Callbacks are functions, that are passed as parmeters to other funtions, for example, I will perform an acction with a function `foo` but it will perform a certain filtering with another function that will be passed to it, lets say: function `filter_1` but, there can be 
other situations, that will requiere to perform function `foo` but this time, based on another function `filter_2`... so, then,
the point is to invoque the family of function `filter_x`, as a parameter of functionoo `foo`.

these calls can be passed with  or without parameters:

without parameters:

```javascript
$.get( "my_web", my_callback_1);
```

this code, will execute the function my_callback_1().

with parameters:

```javascript
$.get( "my_web", function () {
 my_callback_1(param1, param2);
});
```
<br>
Reference: [:link:](https://learn.jquery.com/about-jquery/how-jquery-works/)
<br>
<hr>
<br>
## Ajax no-cache request

```javascript
    var dname = %name of the file location.
    var xhttp = (window.XMLHttpRequest) ? new XMLHttpRequest() : new ActiveXObject("Microsoft.XMLHTTP");
    xhttp.open("GET",dname,false); //true: async ; false:sync.
	xhttp.onreadystatechange = function() {
    if (xhttp.readyState == 4 && xhttp.status == 200)
	{
		console.log("load XML OK: " + dname);
		return xhttp.responseXML;
	}
	else if (xhttp.readyState == 4 && xhttp.status == 404)
	{
		console.log("XML NOT FOUND 404: " + dname);
		alert("XML NOT FOUND 404: " + dname);
	}
    };	
    xhttp.setRequestHeader('Pragma','no-cache');
    xhttp.setRequestHeader('Cache-Control','no-cache, no-store, must-revalidate');
    xhttp.setRequestHeader('Expires','Wed, 21 Oct 2015 07:28:00 GMT'); //date in the past.
    xhttp.send();	
    return xhttp.responseXML; 
 ```
<hr>

## jQuery no-cache request


```javascritp
jQueryGET(dname){
	var result = "";

	$.ajax({
        url: dname,
        type: "GET",
        dataType: 'xml',
	cache: false,  //this is for control the browser cache.
        async: false, //false is for sync calls
	headers: { 'pragma':'no-cache',
		   'Cache-Control':'no-cache, no-store, must-revalidate',
		   'Expires':'Wed, 21 Oct 2015 07:28:00 GMT',
		   },
        success: function(xmldata){
		if(!xmldata) {console.log("AnSwer wrong!"); }
            	console.log("file " + dname + " loaded OK");
		result = xmldata;
        },
        error: function(jqXHR,Status, error_string){
            console.log ("file " + dname + " loaded KO");
			console.log ("STATUS: " + Status);
			console.log ("Error: " + error_string);
        }
    });
    
    return result;
}
``` 

Reference: https://stackoverflow.com/questions/5316697/jquery-return-data-after-ajax-call-success

<hr>

## JS-vanilla for Scripting at \<head\> for dynamically adding CSS and JS files

```javascript
//this file is to force a cache-burst, and so force the server to no use cache for those files.
var file_name = "";
var init_file; 
var rand_num = Math.floor(100000*Math.random()+1);  //adding "?%random_number", we mislead the server.

/*
file_name = 'whateverlib.js';
init_file = document.createElement("SCRIPT");
init_file.setAttribute("src",  file_name + "?" + rand_num );
document.head.appendChild(init_file);*/

function Load_head_script_cache_burst(filename){
var add_script =  document.createElement("SCRIPT");
add_script.setAttribute("src",  file_name + "?" + rand_num );
document.head.appendChild(add_script);
return;
};
```
<hr>

## jQuery for Scripting at \<head\> for dynamically adding JS files

```javascript
//ref: https://api.jquery.com/jQuery.getScript/
$.getScript('lib1.js').then(
		$.getScript('lib2.js')).then(
		$.getScript('lib3.js')).then(
		$.getScript('lib4.js')).then(
		$.getScript("lib5.js")).then(
		$.getScript("lib6.js")).then(
		$.getScript("lib7.js")).then(
		$.getScript("lib8.js"));
```


# Element queries

Element queries are similar to media queries, but, it allows you to apply stiles depending on the propierties of its element, and for example give different styles accordint to its width, it number of children, ....

EQCSS is a JavaScript library developed by Tommy Hodgins. 

Elements queries are an expansion to CSS, so you have to include its scritp:
```html
https://cdnjs.cloudflare.com/ajax/libs/eqcss/1.7.0/EQCSS.min.js
```

<hr>
<br>

