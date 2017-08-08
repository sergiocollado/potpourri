# Notes on web metrics

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


You can also use the following tools:

- [jsbin](http://jsbin.com/?html,output)
- [thimble](https://thimble.mozilla.org/)


Also check the meta-tags: http://www.metatags.org/meta_name_robots

# Styling and CSS

## display

'display' propierty - it indicates how an element will be displayed. - Its the most important propierty for controlling the layout.

values are: 

- block: the element starts always in a new line. Common cases are \<div\> \<h1\> \<h2\> ... \<header\> \<footer\> \<p\> \<section\>.
- inline: the element doesn't start in a new line, and only takes as much space as required, common cases are <a> <span> <img>.
- none: the element is not displayed, and its space is not reserved also. as example the <script> is display:none. This is opposed for example to the propierty: visibility:hidden, in which the element is not displayed, but it space is reserverd.
- inline-block: displays the element as an inline-block containter
- list-item: behaves as an <li> element.
- run-in: behaves as an inline or block, depending on the context.
- flex: [CSS3] element displayed as a block-level flex container.
- inline-flex [CSS3] the element is displayed as an inline-level flex container.

Also for position an element at the center of something, many times is resolved with just: `margin:auto`

##  box-sizing:

values are:
- content-box: specifies the size of the box, but it doen't include border, padding or margin. It only defines the content.
- border-box: specifies the size (width and height) and includes content, padding, and border, but not the margin!




## Ajax no-cache call

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

## jQuery no-cache call


```javascritp
jQueryGET(dname){
	var result = "";

	$.ajax({
        url: dname,
        tySpe: "GET",
        dataType: 'xml',
		cache: false, 
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

