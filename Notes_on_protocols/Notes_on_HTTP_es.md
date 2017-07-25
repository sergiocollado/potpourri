
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

> GET /mypage.html

La respuesta también es muy sencilla: solamente consiste el archivo pedido.

> \<HTML\>
> A very simple HTML page
> \<\/HTML\>

Al contrario que sus posteriores evoluciones, el protocolo HTTP/0.9 no usa cabeceras HTTP, con lo cual únicamente es posible transmitir archivos HTML, y ningún otro tipo de archivos. Tampoco habia información del estado ni códigos de error: en el caso un problema, el archivo HTML pedido, era devuelto con una descripción del problema dentro de él, para que una persona pudiera analizarlo.


## HTTP/1.0 – Desarrollando extensibilidad

La versión HTTP/0.9 era ciertamente limitada y tanto los navegadores como los servidores, pronto ampliaron el protocolo para que fuera más flexible.

La versión del protocolo se envia con cada petición: HTTP/1.0 se añade a la línea de la petición GET.

Se envía también un código de estado al comienzo de la respuesta, permitiendo así que el navegador pueda responder al exito o fracaso de la petición realizada, y actuar en consecuencia (como actualizar el archivo o usar la caché local de algún modo).

El concepto de cabeceras de HTTP, se presentó tanto para las peticiones como para las respuestas, permitiendo la trasmisión de metadata y conformando un protocolo muy versatil y ampliable. 

Con el uso de las cabeceras de HTTP, se pudieron transmitir otros documentos además de HTML, mediante la cabecera "Content-Type".






