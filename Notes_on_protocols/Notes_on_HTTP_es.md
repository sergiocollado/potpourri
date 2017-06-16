
# Fundamentos del protocolo HTTP:

HTTP, de sus siglas en inglés: "Hypertext Transfer Protocol"; es el nombre de un protocolo el cual nos permite realizar la petición de datos y recursos, como pueden ser documentos HTML. Es la base de cualquier intercambio de datos en la Web, y un protocolo de estructura cliente-servidor, esto quiere decir que una petición de datos es iniciada, por el agente que recibirá los datos; normalmente un navegador Web. Así una página web completa, resulta de la unión de distintos sub-documentos recibidos, como por ejemplo un documento que especifique la maquetación de la página web (CSS), el texto, las imágenes, vídeos, scripts ...    

Clientes y servidores se comunican intercambiando mensajes individuales (en contraposición a las comunicaciones que utilizan flujos de datos). Los mensajes que envía el cliente, normalmente un navegador Web, se llaman peticiones, y los mensajes con los que el servidor, se llaman respuestas.

Diseñado a principios de la década de 1990, HTTP es un protocolo ampliable, que ha ido evolucionando con el tiempo. Es lo que se conoce como un protocolo de la capa de aplicación, y se trasmite sobre el protocolo TCP, o el protocolo encriptado TLS, aunque teoricamente podría usarse cualquier otro protocolo fiable. Gracias a que es un protocolo capaz de ampliarse, se usa no solo para transmitir documentos de hipertexto (HTML), si no que además, se usa para transmitir imagenes o videos, o enviar datos o contenido a los servidores, como en el caso de los formularios de datos. HTTP puede incluso ser utilizado para transmitir partes de documentos, y actualizar paginas Web en el acto.

## Arquitectura de los sistemas basados en HTTP

HTTP es un protocolo basado en el principio de [cliente-servidor](https://es.wikipedia.org/wiki/Cliente-servidor): las peticiones son enviadas por una entidad, el agente del usuario (o un proxy a petición de uno). La mayoria de las veces el agente de usuario (cliente) es un navegador Web, pero podria ser cualquier otro programa, como por ejemplo un programa-robot, que explora la Web, para adquirir datos de su estructura y contenido para uso de un buscador de Internet.

Cada petición individual se envía a un servidor, el cuál la gestiona y responde. Entre cada petición (cliente) y respuesta (servidor), hay varios intermediarios, normálmente denominados proxies, los cuales realizan distintas funciones, como gateways o caches. 

En realidad, hay más intermediarios entre un navegador y el servidor que gestiona su petición: hay otros tipos de dispositivos: como routers, modems ... Es gracias al diseño estructurado en capas de la Web, que estos intermediarios, son transparentes al navegador y al servidor, ya que HTTP se apoya en los protocolos de red y transporte. HTTP es un protocolo de aplicación, y por tanto se apoya sobre los anteriores. Aunque para diagnosticar problemas en redes de comunicación, las capas inferiores son irrelevantes para la definición del protocolo HTTP. 

## Cliente: el agente del usuario

El agente del usuario, es cualquier herramienta que actue en representación del usuario. Esta función es realizada en la mayor parte de los casos por un navegador Web; hay excepciones, como el caso de programas especificamente usados por desarrolladores para debuggar sus aplicaciones.

## El servidor Web

Al otro lado del canal de comunicación, está el servidor, el cual "sirve" los datos que ha pedido el cliente.Un servidor conceptualmente es una unica entidad, aunque puede estar formado por varios elementos, que se reparten la carga de peticiones, (load balancing), u otros programas, que gestionan otros computadores (como cache, bases de datos, servidores de correo electrónico, ...), y que generan parte o todo el documento que ha sido pedido. 

Un servidor no tiene que ser necesariamente un único equipo físico, aunque si que varios servidores pueden estar funcionando en un único computador. En el estandar HTTP/1.1 y {{HTTPHeader("Host")}} , pueden incluso compartir la misma dirección de IP.

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


