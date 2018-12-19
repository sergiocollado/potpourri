
https://github.com/sergiocollado/LKMPG/blob/master/4.9.11/LKMPG-4.9.11.org

GUÍA DE PROGRAMACIÓN DE MÓDULOS DEL KERNEL DE LINUX

PRESENTACIÓN

Esta guía de programación de módulos del kernel de linux es un libro libre, y se puede reproducir y/o modificar bajo los términos y condiciones de Open Software License, version 3.0.

Este texto se distribuye con el propósito de ser útil, pero sin ninguna garantía, e incluso sin la garantía de mercantibilidad o adecuación para un propósito particular.

El autor anima a la amplia distribución de este texto para uso personal o comercial, siempre que la especificación de copyright se mantenga intacta y se ajuste a lo indicado en la licencia Open Software License. Resumiendo, se puede copiar y distribuir este texto sin coste alguno o por beneficio. No se requieren permisos explícitos del autor para la reproducción de este texto en ningún medio, físico, electrónico o digital.

Los trabajos derivados y traducciones de este texto, se deben estar bajo la licencia Open Software License, y la especificación del copyright original ha de permanecer intacta. Si se añade nuevo contenido al texto, se debe aportar el código fuente para posibles revisiones. Por favor disponga de las revisiones y actualizaciones disponibles directamente al gestor de la documentación, Peter Jay Salzman <p@dirac.org>. Esto permitirá incluir todas las actualizaciones y proveer de versiones consistentes para la comunidad Linux.

Si se publica o distribuye este libro de manera comercial, donaciones, royalties, y/o copias impresas son gratamente aceptadas por el autor y el proyecto de documentación del Linux,  Linux Documentation Project (LDP). Esta contribución muestra su apoyo para el software libre y LDP. Cualquier pregunta o duda, por favor, contacte con la dirección anteriormente indicada.

AUTORIA:

La guía de programación de módulos del kernel de linux, en inglés: “The Linux Kernel Module Programming Guide”, fue originalmente escrita para el kernel 2.2 por Ori Pomerantz. Posteriormente, Ori careció del tiempo para mantener el documento. Después de todo el kernel de Linux, es un blanco móvil. Peter Jay Salzman asumió el mantenimiento y actualización para el kernel 2.4. Con el tiempo Peter tampoco pudo continuar con el desarrollo del kernel 2.6. Así que Michael Burian tomó el relevo y co-mantuvo el documento para el kernel 2.6. Bob Mottram actualizó los ejemplos para el kernel 3.8 y posteriores. Añadió el capítulo sobre Sysfy y actualizó  y/o modificó otros capítulos.

NOTAS Y VERSIONES:

El kernel de Linux está en constante desarrollo. Así que siempre ha estado presente la pregunta de si LKMPG debería retirar información anticuada o mantenerla por motivos históricos. Michael Burian, decidió crear una nueva rama del LKMPG para cada nueva versión estable del kernel. Así que LKMPG 4.9.x está destinado al kernel 4.9.x de Linux y LKMPG 2.6.x está dirigida al kernel 2.6 de Linux. No se intenta mantener la información histórica. Cualquier persona interesada en esto debería leer la versión adecuada de LKMPG.

El código fuente y comentarios deberían servir para la mayoría de arquitecturas, pero no se puede afirmar con certeza. Una excepción clara es el capítulo de Interruptores, que solo es válido para la arquitectura x86.

RECONOCIMIENTOS:

Las siguientes personas han contribuido con correcciones o propuestas interesantes: Ignacio Martin, David Porter, Daniele Paolo Scarpazza, Dimo Velev, Francois Audeon, Horst Schirmeier, Bob Mottram and Roman Lakeev.

