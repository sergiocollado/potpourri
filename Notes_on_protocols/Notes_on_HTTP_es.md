
# Basics of network protocols

A network protocol is build up in different communications layers, from the transmission media (wires, air, fiber optic ...)  to the top application level (email, http, html, ...) . 

The lowest layer is known as the link layer (media/physical), and sets the rules to that communication level (as 0V in the wire is a logic 0, 5V in the layer is a logic 1, ...). 

Next is the Internet layer, that follows the IP (Internet Protocol), this gathers the data into data packages, and by different possible methods routes the data, through the network, to its destination (the destination IP address). 

Then is the transport layer, this layer TCP (transport control protocol) adds robustness to the communication, it adds methods to check the data integrity (as CRC), also verifies that the data has reached its destination, and in the proper order. 

Above it is the application layer, that provides an interface to different functions: web pages (http), email (IMAP), data (FTP), ...


# Fundamentos del protocolo HTTP:

HTTP, de sus siglas en inglés: "Hypertext Transfer Protocol"; es el nombre de un protocolo el cual nos permite realizar la petición de datos y recursos, como pueden ser documentos HTML. Es la base de cualquier intercambio de datos en la Web, y un protocolo de estructura cliente-servidor, esto quiere decir que una petición de datos es iniciada, por el agente que recibirá los datos; normalmente un navegador Web. Así una página web completa, resulta de la unión de distintos sub-documentos recibidos, como por ejemplo un documento que especifique la maquetación de la página web (CSS), el texto, las imágenes, vídeos, scripts ...    

Clientes y servidores se comunican intercambiando mensajes individuales (en contraposición a las comunicaciones que utilizan flujos de datos). Los mensajes que envía el cliente, normalmente un navegador Web, se llaman peticiones, y los mensajes con los que el servidor, se llaman respuestas.

Diseñado a principios de la década de 1990, HTTP es un protocolo ampliable, que ha ido evolucionando con el tiempo. Es lo que se conoce como un protocolo de la capa de aplicación, y se trasmite sobre el protocolo TCP, o el protocolo encriptado TLS, aunque teoricamente podría usarse cualquier otro protocolo fiable. Gracias a que es un protocolo capaz de ampliarse, se usa no solo para transmitir documentos de hipertexto (HTML), si no que además, se usa para transmitir imagenes o videos, o enviar datos o contenido a los servidores, como en el caso de los formularios de datos. HTTP puede incluso ser utilizado para transmitir partes de documentos, y actualizar paginas Web en el acto.

## Arquitectura de los sistemas basados en HTTP

HTTP es un protocolo basado en el principio de [cliente-servidor](https://es.wikipedia.org/wiki/Cliente-servidor): las peticiones son enviadas por una entidad, el agente del usuario (o un proxy a petición de uno). La mayoria de las veces el agente de usuario (cliente) es un navegador Web, pero podria ser cualquier otro programa, como por ejemplo un programa-robot, que explora la Web, para adquirir datos de su estructura y contenido para uso de un buscador de Internet.

Cada petición individual se envía a un servidor, el cuál la gestiona y responde. Entre cada petición (cliente) y respuesta (servidor), hay varios intermediarios, normálmente denominados proxies, los cuales realizan distintas funciones, como gateways o caches. 

En realidad, hay más intermediarios entre un navegador y el servidor que gestiona su petición: hay otros tipos de dispositivos: como routers, modems ... Es gracias al diseño estructurado en capas de la Web, que estos intermediarios, son transparentes al navegador y al servidor, ya que HTTP se apoya en los protocolos de red y transporte. HTTP es un protocolo de aplicación, y por tanto se apoya sobre los anteriores. Aunque para diagnosticar problemas en redes de comunicación, las capas inferiores son irrelevantes para la definición del protocolo HTTP. 

## Cliente: el agente del usuario

El agente del usuario, es cualquier herramienta que actue en representación del usuario. Esta función es realizada en la mayor parte de los casos por un navegador Web; hay excepciones, como el caso de programas especificamente usados por desarrolladores para depurar sus aplicaciones.

## El servidor Web

Al otro lado del canal de comunicación, está el servidor, el cual "sirve" los datos que ha pedido el cliente.Un servidor conceptualmente es una unica entidad, aunque puede estar formado por varios elementos, que se reparten la carga de peticiones, (load balancing), u otros programas, que gestionan otros computadores (como cache, bases de datos, servidores de correo electrónico, ...), y que generan parte o todo el documento que ha sido pedido. 

Un servidor no tiene que ser necesariamente un único equipo físico, aunque si que varios servidores pueden estar funcionando en un único computador. En el estandar HTTP/1.1, pueden incluso compartir la misma dirección de IP.

## Proxies

Entre el cliente y el servidor, además existen distintos dispositivos que gestionan los mensajes HTTP. Dada la arquitectura en capas de la Web, la mayoria de estos dispositivos solamente gestionan estos mensajes en los niveles de protocolo inferiores: trasnporte, red o capa física, siendo así trasparentes para la capa de comunicaciones de aplicación del HTTP, además esto aumenta el rendimiento de la comuicación. Aquellos dispositivos, que sí operan procesando la capa de aplicación son conocidos como proxies. Estos pueden ser transparentes, o no (modificando las peticiones que pasan por ellos), y realizan varias funciones: 

- caching (la cache puede ser pública o privaca, como la cache de un navegador) 
- filtrado (como un antivirus, o control parental, ... )
- balanceo de carga de peticiones (para permitir a varios servidores responder a la carga total de peticiones que reciben)
- autentificacion (para el control al acceso de recursos y datos)
- registro de eventos (para tener un histórico de los eventos que se producen)

# Caracteristicas clave del protocolo HTTP

## HTTP es sencillo

Incluso con el incremento de complejidad, que se produjo en el desarrollo de la versión del protocolo HTTP/2, en la que se encapsularon los mensajes, HTTP esta pensado y desarrollado para ser leido y facilmente interpretado por las personas, haciendo de esta manera más facil la depuración de errores, y reduciendo la curva de aprendizaje para las personan que empiezan a trabajar con él.

## HTTP es extensible

Presentadas en la versión HTTP/1.0, las cabeceras de HTTP, han hecho que este protocolo sea fácil de ampliar y de experimentar con él. Funcionalidades nuevas pueden desarrollarse, sin más que un cliente y su servidor, comprendan la mísma semantica sobre las cabeceras de HTTP.

## HTTP es un protocolo con sesiones, pero sin estados

HTTP es un protocolo sin estado, es decir: no guarda ningún dato entre dos peticiones en la mísma sesión. Esto plante la problemática, en casó de que los usuarios requieran interactuar con determinadas páginas Web, de forma ordenada y coherente, por ejemplo, para el uso de "cestas de la compra" en páginas que utilizan en comercio electrónico. Pero mientras HTTP ciertamente es un protocolo sin estado, el uso de HTTP cookies, si permite guardar datos con respecto a la sesion de comunicación . Usando la capacidad de ampliación del protocolo HTTP, las cookies permiten crer un contexto común para cada sesión de comunicación.

## HTTP y conexiones

Una conexión se gestiona al nivel de la capa de trasnporte, y por tanto queda fuera del alcance del protocolo HTTP. Aún con este factor, HTTP no necesita que el protocolo que lo sustenta mantenga una conexión continua entre los participantes en la comunicación, solamente necesita que sea un protocolo fiable, o que no pierda mensajes (como mínimo, en todo caso, un protocolo que sea capaz de detectar que se ha pedido un mensaje y reporte un error). De los dos protocolos más comunes en Internet, TCP es fiable, mientras que UDP, no lo es. Por lo tanto HTTP, se apoya en el uso del protocolo TPC, que está orientado a conexión, aunque una conexión continua, no es necesaria siempre. 

La versión del protocolo HTTP/1.0 habría una conexión TPC por cada peticion/respuesta intercabiada, presentando esto dos grandes inconvenientes: abrir y crar una conexion, requiere varias rondas de mensajes, y por lo tanto resultaba lento, esto sería más eficiente si se mandaran varios mensajes.

Para atenuar estos inconvenientes, la versión del protocolo HTTP/1.1 presentó el 'pipelining'  y las conexiones persistentes: el protocolo TPC que lo trasnmitia en la capa inferior se podia controlar parcialmente, mediante la cabecera 'Conection'. La version del protocolo HTTP/2 va más allá y multiplexa mensajes sobre un única conexión, siendo así una comunicaición más eficiente.

Todavia se sigue desarrollando para conseguir una protocolo de trasnporte más conveniente para el HTTP. Por ejemplo Google está experimentado con QUIC, que se apoya en el protocolo UDP y presenta mejoras en la fiabilidad y eficiencia de la comunicación. 


# ¿Qué se puede controlar con HTTP?
La característica del protocolo HTTP, de ser ampliable, ha permitido que durante su desarrollo, se hayan implementado más funciones pde control y funcionalidad sobre la Web: cache o métodos de identificación o autentificación fueron temas que se abordaron pronto en su historia. Al contrario la relajación de la restricción de origen solo se ha abordado en los años de la década de 2010.

Se presenta a continuación una lista con los elementos que se pueden controlar con el protocolo HTTP:

## Cache
El como se almacenan los documentos en la cache, puede ser especificado por HTTP. El servidor puede indicar a los proxies, y clientes, que quiere almacenar y durante cuanto tiempo. Aunque el cliente, también puede indicar a los proxies de cache intermedios que ignoren el documento almacenado.

## Flexibilidad del requisito de origen
Para prevenir invasiones de la privacidad de los usuarios, los navegadores Web, solamente permiten a páginas del mismo origen, compartir la información o datos. Esto es una complicación para el servidor, asi que mediante cabeceras HTTP, se puede flexibilizar o relajar esta división entre cliente y servidor

## Autentificación
Hay páginas Web, que pueden estar protegidas, de manera que solo los usuarios autorizados puedan acceder. HTTP provee de servicios básicos de autentificación, por ejemplo mediante el uso de cabeceras como:  WWW-Authenticate, o estableciendo una sesión especifica mediante el uso de  HTTP cookies. 

## Proxies y  tunneling
Servidores y/o clientes pueden estar en intranets y esconder asi su verdadera dirección IP a otros. Las peticiones HTTP, utilizan los proxies para acceder  a ellos. Pero no todos los proxies son HTTP proxies. El protocolo SOCKS, por ejemplo, opera a un nivel más bajo. Otros protocolos, como el FTP, pueden ser servidos mediante estos proxies.

## Sesiones
El uso de HTTP cookies, permite relacionar peticiones con el estado del servidor. Esto define las sesiones, a pesar de que por definición el protocolo HTTP, es un protocolo sin estado. Esto es muy útil, no solo para aplicaciones de comercio electrónico, sino también para cualquier sitio que permita configuración al usuario.

## Flujo de HTTP
Cuando el cliente quiere comunicarse con el servidor, tanto si es directamente con él, o a través de un proxy intermedio, realiza los siguientes pasos:

- Abre una conexión TPC: la conexión TPC se usará para hacer una petición, o varias, y recibir la respuesta. El cliente pude abrir una conexión nueva, reusar una existente, o abrir varias a la vez hacia el servidor.
- Hacer una petición HTTP: Los mensajes HTTP (previos a HTTP/2) son legibles en texto plano. A partir de la versión del protocolo     HTTP/2, los mensajes se encapsulan en franjas, haciendo que no sean directamente interpretables, aunque el principio de operación es el  mismo.
- Leer la respuesta enviada por el servidor.
- Cierre o  reciclado de la conexión para futuras peticiones.

Si está activado el HTTP pipelining, varias peticiones pueden enviarse sin tener que esperar que la primera respuesta haya sido satisfecha. Este procedimiento es difícil de implementar en las redes de computadores actuales, donde se mezclan software antiguos y modernos. Así que el HTTP pipelining  ha sido substituido en HTTP/2 por el multiplexado de varias peticiones en una sola trama.

# Mensajes HTTP
En las versiones del protocolo HTTP/1.1 y anteriores los mensajes eran de formato texto y eran totalmente comprensibles directamente por una persona. En HTTP/2, los mensajes tenían un formato binario y las trama permitían la compresión de las cabeceras y su multiplexación. Así pues incuso si solamente parte del mensaje original en HTTP se envía en este formato, la sematica de cada mensaje es la misma y el cliente puede formar el mensaje original en HTTP/1.1. Luego es posible interpretar los mensajes HTTP/2, en el formato de HTTP/1.1.

Existen dos tipos de mensajes HTTP: peticiones y respuestas, cada uno sigue su propio formato.

## Peticiones

Una petición de HTTP, está formado  por los siguientes campos:

- Un método HTTP,  normalmente pueden ser un verbo, como: GET, POST o un nombre como: OPTIONS o HEAD, que defina la operación que el cliente quiera realizar. El objetivo de un cliente, suele ser una petición de recursos, usando GET, o presentar un valor de un formulario HTML, usando POST, aunque en otras ocasiones puede hacer otros tipos de peticiones. 
- La dirección del recurso pedido; la URL del recurso, sin los elementos obvios por el contexto, como pueden ser: sin el  protocolo (http://),  el dominio (aquí developer.mozilla.org), o el puerto TCP (aquí el 80). 
- La versión del protocolo HTTP.
- Cabeceras HTTP opcionales, que pueden aportar información adicional a los servidores.
- O un cuerpo de mensaje, en algún método, como puede ser POST, en el cual envía la información para el servidor.

## Respuestas

Las respuestas están formadas por los siguentes campos:

- La versión del protocolo HTTP que están usando.
- Un código de estado, indicando si la petición ha sido exitosa, o no, y debido a que.
- Un mensaje de estado, una breve descriptión del código de estado. 
- Cabeceras HTTP, como las de las peticiones.
- Opcionalmente, el recurso que se ha pedido.

# Resumen

El protocólo HTTP es un protocolo ampliable y facil de usar. Su estructura cliente-servidor, junto con la capacidad para usar cabeceras, permite a este protolo evolucionar con las nuevas y futuras aplicaciones en Internet.

Aunque la versión del protocolo HTTP/2 añade algo de complejidad, al utilizar un formato en binario, esto aumenta su rendimiento, y la estructura y semantica de los mensajes es la misma desde la versión HTTP/1.0. El flujo de comunicaciones en una sesión es sencillo y puede ser facilmente estudiado e investigado con un simple monitor de mensajes HTTP.


# Desarrollo de HTTP


HTTP es el protocolo en el que se basa la Web. Fue inventado por Tim Berners-Lee entre los años 1989-1991, HTTP ha visto muchos cambios, manteniendo la mayor parte de su simplicidad y desarrollando su flexibilidad. HTTP ha evolucionado, desde un protocolo destinado al intercambio de archivos en un entorno de un laboratorio semi-seguro, al actual laberinto de Internet, sirviendo ahora para el intercambio de imágenes, vídeos en alta resolución y en 3D.
Invención de la World Wide Web

En 1989, mientras trabajaba en el CERN, Tim Berners-Lee escribió una propuesta para desarrollar un sistema de hipertexto sobre Internet. Inicialmente lo llamó: 'Mesh' (malla, en inglés), y posteriormente se renombró como World Wide Web (red mundial), durante su implementación en 1990. Desarrollado sobre los protocolos existentes TCP e IP, está basado en cuatro bloques:
Un formato de texto para representar documentos de hyper-texto: HyperText Markup Language (HTML).
Un protocolo sencillo para el intercambio de esos documentos,  en inglés: HypertText Transfer Protocol (HTTP).
Un cliente que muestre (e incluso pueda editar) esos documentos. El primer navegador Web, llamado: WorldWideWeb.
Un servidor para dar acceso a los documentos, una versión temprana: httpd.

Estos cuatro bloques fundamentales se finalizaron para finales de 1990, y los primeros servidores estaban ya funcionando fuera del CERN a principios del 1991. El 6 de Agosto de 1991, el post de Tim Berners-Lee, se considera actualmente como el inicio oficial de la Web como proyecto público. 

La versión del protocolo HTTP usada en aquel momento, era realmente muy sencilla, posteriormente pasó a HTTP/0.9, referido algunas veces, como el protocolo de una sola línea.

## HTTP/0.9 – El protocolo de una sola línea

La versión inicial de HTTP, no tenía número de versión; aunque posteriormente se la denominó como 0.9 para distingirla de las versiones siguientes. HTTP/0.9 es un protocolo extremadamente sencillo: una petición consiste simplemente en una única linea, que comienza por el único método posible GET, seguido por la dirección del recurso a pedir (no la URL, ya que tanto el protocolo, el servidor y el puerto, no son necesarios una vez ya se ha conectado al servidor).

```
> GET /mypage.html
```

La respuesta también es muy sencilla: solamente consiste el archivo pedido.

```
> \<HTML\>
> A very simple HTML page
> \<\/HTML\>
```

Al contrario que sus posteriores evoluciones, el protocolo HTTP/0.9 no usa cabeceras HTTP, con lo cual únicamente es posible transmitir archivos HTML, y ningún otro tipo de archivos. Tampoco habia información del estado ni códigos de error: en el caso un problema, el archivo HTML pedido, era devuelto con una descripción del problema dentro de él, para que una persona pudiera analizarlo.


## HTTP/1.0 – Desarrollando extensibilidad

La versión HTTP/0.9 era ciertamente limitada y tanto los navegadores como los servidores, pronto ampliaron el protocolo para que fuera más flexible.

La versión del protocolo se envia con cada petición: HTTP/1.0 se añade a la línea de la petición GET.

Se envía también un código de estado al comienzo de la respuesta, permitiendo así que el navegador pueda responder al exito o fracaso de la petición realizada, y actuar en consecuencia (como actualizar el archivo o usar la caché local de algún modo).

El concepto de cabeceras de HTTP, se presentó tanto para las peticiones como para las respuestas, permitiendo la trasmisión de metadata y conformando un protocolo muy versatil y ampliable. 

Con el uso de las cabeceras de HTTP, se pudieron transmitir otros documentos además de HTML, mediante la cabecera "Content-Type".


Los mensajes HTTP, son los medios por los cuales se intercambian datos entre servidores y clientes. Hay dos tipos de mensajes: peticiones, enviadas por el cliente al servidor, para pedir el inicio de una acción; y respuestas, que son la respuesta del servidor. 

Los mensajes HTTP están compuestos de texto, codificado en ASCII, y pueden comprender múltiples lineas. En HTTP/1.1, y versiones previas del protocolo, estos mensajes eran enviados de forma abierta a través de la conexión. En HTTP/2.0 los mensajes, que anteriormente eran legibles directamente, se conforman mediante tramas binarias codificadas para aumentar la optimización y rendimiento de la transmisión.

Los desarrolladores de páginas Web, o administradores de sitios Web, desarrolladores... raramente codifican directamente estos mensajes HTTP. Normalmente especifican estos mensajes HTTP, mediante archivos de configuración (para proxies, y servidores), APIs (para navegadores) y otros medios.


El mecanismo de tramas binarias de HTTP/2 ha sido diseñado para que no necesite ninguna modificación de las APIs o archivos de configuración utilizados: es totalmente transparente para el usuario.

Las peticiones y respuestas HTTP, comparten una estructura similar, compuesta de:

Una línea de inicio ('start-line' en inglés) describiendo la petición a ser implementada, o su estado, sea de exito o fracaso. Esta línea de comienzo, es siempre una única línea. 
Un grupo opcional de cabeceras HTTP, indicando la petición o describiendo el cuerpo ('body' en inglés) que se incluye en el mensaje. 
Una línea vacía ('empty-line' en inglés) indicando toda la meta-información ha sido enviada.
Un campo de cuerpo de mensaje opcional ('body' en inglés) que lleva los datos asociados con la petición (como contenido de un formulario HTML), o los archivos o documentos asociados a una respuesta (como una página HTML, o un archivo de audio, video ... ) . La presencia del cuerpo y su tamaño es indicada en la línea de inicio y las cabeceras HTTP.
La línea de inicio y las cabeceras HTTP, del mensaje, son conocidas como la cabeza de la peticiones, mientras que su contenido en datos se conoce como el cuerpo del mensaje.



# Peticiones HTTP

Linea de inicio
Las peticiones HTTP son mensajes enviados por un cliente, para iniciar una acción en el servidor. Su línea de inicio está formada por tres elementos: 

Un método HTTP, un verbo como: "GET", "PUT" o "POST" o un nombre como: "HEAD" o  "OPTIONS", que describan la acción que se pide sea realizada. Por ejemplo, GET indica que un archivo ha de ser enviado hacia el cliente, o POST indica que hay datos que van a ser enviados hacia el servidor (creando o modificando un recurso, o gnerando un documento temporal para ser enviado).
El objetivo de una petición, normalmente es una URL, o la dirección completa del protocolo, puerto y dominio también sulen ser epecificados por el contexto de la petición. El formato del objetivo de la petición varia según los distintos métodos HTTP. Puede ser:

Una dirección absoluta, seguida de a '?' y un texto de consulta. Este es el formato más comun, conocido como el formato original ('origin form' en inglés), se usa en los métodos GET, POST, HEAD, y OPTIONS . 

```
POST / HTTP 1.1
GET /background.png HTTP/1.0
HEAD /test.html?query=alibaba HTTP/1.1
OPTIONS /anypage.html HTTP/1.0
Una URL completa; conocido como el formato absoluto, usado mayormente con GET cuando se conecta a un proxy. 
GET http://developer.mozilla.org/en-US/docs/Web/HTTP/Messages HTTP/1.1
```

El componente de autoriade de una URL, formado por el nombre del domínio y opcionalmente el puerto (el puerto precedido por el simbolo ':' ), se denomina a este formato como el formato de autoridad. Unicamente se usa con  CONNECT cuando se establece un tunel HTTP.

CONNECT developer.mozilla.org:80 HTTP/1.1
El formato de asterisco, se utliza un asterisco ('*')  junto con las opciones: OPTIONS , representando al servidor entero en conjunto.  
OPTIONS * HTTP/1.1
la versión de HTTP, la cual define la estructura de los mensajes, actuando como indicador, de la versión que espera que se use para la respuesta.T
Cabeceras
Las cabeceras HTTP  de una petición siguen la misma estructura que la de una cabecera HTTP. Una cadena de caracteres, que no diferencia mayusculas ni minusculas, seguida por dos puntos  (':')  y un valor cuya estructura depende de la cabecera. La cabecera completa, incluido el valor, ha de ser formada en una única linea, y pude ser bastante larga. 

Hay bastantes cabeceras posibles. Estas se pueden clasificar en varios grupos: 

 - Cabeceras generales, ('Request headers' en inglés), como Via,  afectan al mensaje como una unidad completa.
 - Cabeceras de petición, ('General headers' en inglés), como User-Agent, {{HTTPHeader("Accept-Type")}}, modifican la petición especificandola en mayor detalle ( como: Accept-Language, o dándole un contexto, como:  {{HTTPHeader("Referer")}}, o restringiendola condicionalmente, como: "If-None".
 - Cabeceras de entidad, ('Entity headers' en ingles), como Content-Length las cuales se aplican al cuerpo de la petición. Por supuesto, esta cabecera no necesitaser transmitida si el mensaje no tiene cuerpo ('body' en inglés). 


Cuerpo
La parte final de la petición el el cuerpo. No todas las peticiones llevan uno: las peticiones que reclaman datos, como GET, HEAD, DELETE, o OPTIONS, normalmente, no necesitan ningún cuerpo. Algunas peticiones pueden mandar peticiones al servidor con el fin de actualizarlo: como es el caso con la petición POST  (que contiene datos de un formulario HTML). 

Una típica sesión de HTTP
En los protocolos basados en el modelo cliente-servidor, como es el caso del HTTP, una sesión consta de tres fases:

El cliente establece una conexión TCP (o la conexión correspondiente si la capa de transporte corresponde a otro protocolo).
El cliente manda su petición, y espera por la respuesta. 
El servidor procesa la petición, y responde con un código de estado y los datos correspondientes.
A partir del protocolo HTTP/1.1 la conexión, no se cierra al finalizar la tercera fase, y el cliente puede continuar realizando peticiones. Esto significa que la segunda y tercera fase, pueden repetirse cualquier número de veces.

# Estableciendo una conexión

En un protocolo cliente servidor, es siempre el cliente el que establece la conexión. Iniciar una conexión en HTTP, implica iniciar una conexión en el protocolo correspondiente a la capa de comunicación subyacente, que normalmente es TCP. 

En TCP el puerto por defecto, para un servidor HTTP en un computador, es el puerto 80. Se pueden usar otros puertos como el 800 o el 8080. La URL de la página pedida contiene tanto el nombre del dominio, como el número de puerto, aunque este puede ser omitido, si se trata del puerto 80.  Vease la referencia de Identificación derecurson en la Web para más detalles.

Nota: El modelo cliente-servidor no permite que el servidor mande datos al cliente sin una petición explicita. Como solución parcial a esteproblema, los desarrolladores web, usan varias técnicas, como hacer un ping al servidor periodicamente, mediante {{domxref("XMLHTTPRequest")}}, {{domxref("Fetch")}} APIs, o usar la HTML  WebSockets API o protocolos similares.
Mandando una petición

Una vez la conexión está establecida, el cliente, puede mandar una petición de datos (normalente es un navegador, u otra cosa, como un 'crawler', un sistema de indexación automático de páginas web). La  petición de datos de un cliente HTTP, consiste en directivas de texto, separadas mediante CRLF (retorno de carro, y cambio de linea), y se divide en tres partes:

- La primera parte, consiste en una linea, que contiene un método, seguido de sus parámetros:
  - la dirección del documento pedido: por ejemplo su URL completa, sin indicar el protocolo o el nombre del dominio.
  - la versión del protocolo HTTP
- La siguente parte, está formada por un bloque de líneas consecutivas, que represetan las cabeceras de la petición HTTP, y dan información al servidor, sobre que tipo de datos es apropiado (como qué lenguaje usar, o el tipo MIME a usar), u otros datos que modifiquen su comportamiento (como que no envie la respuesta si ya está cacheada). Estas cabeceras HTTP forman un bloque que acaba con una línea en blanco. 
- La parte final es un bloque de datos opcional, que puede contener más datos para ser usados por el método POST.

En los protocolos basados en el modelo cliente-servidor, como es el caso del HTTP, una sesión consta de tres fases:

El cliente establece una conexión TCP (o la conexión correspondiente si la capa de transporte corresponde a otro protocolo).
El cliente manda su petición, y espera por la respuesta. 
El servidor procesa la petición, y responde con un código de estado y los datos correspondientes.
A partir del protocolo HTTP/1.1 la conexión, no se cierra al finalizar la tercera fase, y el cliente puede continuar realizando peticiones. Esto significa que la segunda y tercera fase, pueden repetirse cualquier número de veces.

## Estableciendo una conexión

En un protocolo cliente servidor, es siempre el cliente el que establece la conexión. Iniciar una conexión en HTTP, implica iniciar una conexión en el protocolo correspondiente a la capa de comunicación subyacente, que normalmente es TCP. 

En TCP el puerto por defecto, para un servidor HTTP en un computador, es el puerto 80. Se pueden usar otros puertos como el 8000 o el 8080. La URL de la página pedida contiene tanto el nombre del dominio, como el número de puerto, aunque este puede ser omitido, si se trata del puerto 80.  Véase la referencia de Identificación de recursos en la Web para más detalles.

Nota: El modelo cliente-servidor no permite que el servidor mande datos al cliente sin una petición explicita. Como solución parcial a este problema, los desarrolladores web, usan varias técnicas, como hacer un ping al servidor periódicamente, mediante XMLHTTPRequest, Fetch APIs, o usar la HTML  WebSockets API o protocolos similares.
Mandando una petición

Una vez la conexión está establecida, el cliente, puede mandar una petición de datos (normalmente es un navegador, u otra cosa, como una 'araña' ( o 'crawler' en inglés) o un 'robot web', un sistema de indexación automático de páginas web). La  petición de datos de un cliente HTTP, consiste en directivas de texto, separadas mediante CRLF (retorno de carro, y cambio de linea), y se divide en tres partes:

La primera parte, consiste en una linea, que contiene un método, seguido de sus parámetros:
la dirección del documento pedido: por ejemplo su URL completa, sin indicar el protocolo o el nombre del dominio.
la versión del protocolo HTTP
La siguiente parte, está formada por un bloque de líneas consecutivas, que representan las cabeceras de la petición HTTP, y dan información al servidor, sobre que tipo de datos es apropiado (como qué lenguaje usar, o el tipo MIME a usar), u otros datos que modifiquen su comportamiento (como que no envié la respuesta si ya está cacheada). Estas cabeceras HTTP forman un bloque que acaba con una línea en blanco. 
La parte final es un bloque de datos opcional, que puede contener más datos para ser usados por el método POST.
Ejemplo de peticiones
Si queremos una página web, como por ejemplo: http://developer.mozilla.org/, y además le indicamos al servidor que se preferiría la página en Francés, si fuera posible:

```
GET / HTTP/1.1
Host: developer.mozilla.org
Accept-Language: fr
```

Observe la línea vacía al final, que separa el bloque de datos, del bloque de cabecera. Como no existe el campo Content-Length en la cabecera de HTTP, el bloque de datos está vacío, y ahí está el fin de la cabecera, permitiendo al servidor procesar la petición en el momento que recibe la línea vacía.

Otro ejemplo, en el caso del envío de los datos de un formulario, la trama es:

```
POST /contact_form.php HTTP/1.1
Host: developer.mozilla.org
Content-Length: 64
Content-Type: application/x-www-form-urlencoded
name=Juan%20Garcia&request=Envieme%20uno%20de%20sus%20catalogos
```

## Métodos de peticiones
HTTP define un conjunto de métodos de peticiones  en los que se indican las acciones que se piden realizar al recibir un conjunto de datos. A pesar de que pueden referirse como 'nombres', estos métodos de petición, son denominados a veces como 'verbos' de HTTP.  La peticiones más comunes son  GET y POST:

El método GET hace una petición de un recurso específico. Las peticiones con GET unicamente hacen peticiones de datos.
El método POST envía datos al servidor de manera que este pueda cambiar su estado. Este es el método usado normalmente para enviar los datos de un  formulario HTML.
Estructura de la respuesta del servidor

Después de que el agente de usuario envía su petición, el servidor web lo procesa, y a continuación responde. De forma similar a la petición del servidor, la respuesta del servidor está formada por directivas de texto, separadas por el carácter CRLF, y divida en tres bloques.

La primera línea, es la línea de estado, que consiste en una confirmación del la versión de HTTP utilizado, y seguido por el estado de la petición (y una breve descripción de este, en formato de texto, que pueda ser leído por personas). 
Las líneas siguientes representan cabeceras de HTTP concretas, dando al cliente información sobre los datos enviado( por ejemplo, sy tipo, su tamaño, algoritmos de compresión utilizados, y sugerencias para el cacheo). Al igual que las cabeceras HTTP de la petición de un cliente, las cabeceras HTTP del servidor, finalizan con una línea vacía.
El bloque final, es el bloque que puede contener opcionalmente los datos.
Ejemplos de respuestas
La respuesta correcta de una página web, es como sigue: 

```
HTTP/1.1 200 OK
Date: Sat, 09 Oct 2010 14:28:02 GMT
Server: Apache
Last-Modified: Tue, 01 Dec 2009 20:18:22 GMT
ETag: "51142bc1-7449-479b075b2891b"
Accept-Ranges: bytes
Content-Length: 29769
Content-Type: text/html

<!DOCTYPE html... (aquí estarían los 29769 bytes de la página web pedida)
La respuesta para la petición de datos que han sido movidos permanentemente, sería: 
```
