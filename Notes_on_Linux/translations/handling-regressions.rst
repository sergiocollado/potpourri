.. SPDX-License-Identifier: (GPL-2.0+ OR CC-BY-4.0)
.. See the bottom of this file for additional redistribution information.

Handling regressions
++++++++++++++++++++

*We don't cause regressions* -- this document describes what this "first rule of
Linux kernel development" means in practice for developers. It complements
Documentation/admin-guide/reporting-regressions.rst, which covers the topic from a
user's point of view; if you never read that text, go and at least skim over it
before continuing here.


Gestionando regresiones
+++++++++++++++++++++++

*No causamos regresiones* -- este documento describe la que es la "primera regla
del desarrollo del kernel de Linux" implica en la práctica para los desarrolladores. 
Y complementa la documentación: Documentation/admin-guide/reporting-regressions.rst,
que cubre el tema dessde el punto de vista de un usuario; si nunca ha leido ese texto, 
realice al menos una lectura rápida del mismo antes de continuar. 


The important bits (aka "The TL;DR")
====================================

Las partes importanes
=====================

#. Ensure subscribers of the `regression mailing list <https://lore.kernel.org/regressions/>`_
   (regressions@lists.linux.dev) quickly become aware of any new regression
   report:

    * When receiving a mailed report that did not CC the list, bring it into the
      loop by immediately sending at least a brief "Reply-all" with the list
      CCed.

    * Forward or bounce any reports submitted in bug trackers to the list.

#.  Asegurarse que los suscriptores a la lista `regression mailing list <https://lore.kernel.org/regressions/>`_
    (regressions@lists.linux.dev)  son conocedores con rapidez de cualquier
    nuevo reporte de regresion:
    
    * Cuando se reciba un correo que no incluyó a la lista, incluyala en el bucle 
    de correos, mandando un breve "Reply-all" con la lista en CC. 
    
    * Mande o rebote cualquier reporte originado en gestores de bugs a la lista. 

#. Make the Linux kernel regression tracking bot "regzbot" track the issue (this
   is optional, but recommended):

    * For mailed reports, check if the reporter included a line like ``#regzbot
      introduced v5.13..v5.14-rc1``. If not, send a reply (with the regressions
      list in CC) containing a paragraph like the following, which tells regzbot
      when the issue started to happen::

       #regzbot ^introduced 1f2e3d4c5b6a

    * When forwarding reports from a bug tracker to the regressions list (see
      above), include a paragraph like the following::

       #regzbot introduced: v5.13..v5.14-rc1
       #regzbot from: Some N. Ice Human <some.human@example.com>
       #regzbot monitor: http://some.bugtracker.example.com/ticket?id=123456789

#. Hacer que el bot del kernel de Linux "regzbot" realize seguimento del incidente
   (esto es opcional, pero recomendado).
   
    * Para reportes enviados por correo, verificar si contiene alguna linea como  
      ``#regzbot introduced v5.13..v5.14-rc1``. Si no, mandar una respuesta (con la
      lista de regresiones en CC) que contenga un parrafo como el siguiente, lo que 
      le indica a regzbot cuando empezó a suceder el incidente::
      
       #regzbot ^introduced 1f2e3d4c5b6a

    * Cuando se mandar reportes desde un gestor de incidentes a la lista de regresiones
      (ver más arriba), incluir un parrafo como el siguiente::

       #regzbot introduced: v5.13..v5.14-rc1
       #regzbot from: Some N. Ice Human <some.human@example.com>
       #regzbot monitor: http://some.bugtracker.example.com/ticket?id=123456789

#. When submitting fixes for regressions, add "Link:" tags to the patch
   description pointing to all places where the issue was reported, as
   mandated by Documentation/process/submitting-patches.rst and
   :ref:`Documentation/process/5.Posting.rst <development_posting>`.
   
#. Cuando se manden fixes para las regressiones, añadir etiquets "Link:" a 
   la descripcion, apuntado a todos los sitios donde se informó de incidente, 
   como se indica en el documento: Documentation/process/submitting-patches.rst  y
   :ref:`Documentation/process/5.Posting.rst <development_posting>`.

#. Try to fix regressions quickly once the culprit has been identified; fixes
   for most regressions should be merged within two weeks, but some need to be
   resolved within two or three days.
   
#. Intentar arreglar las regresiones rápidamente una vez la causa haya sido identificada;
   las correcciones para la mayor parte de las regresiones deberian ser integradas en menos 
   de dos semanas, pero algunas pueden resolverse en dos o tres días. 


All the details on Linux kernel regressions relevant for developers
===================================================================

Todos los detalles importantes para desarrolladers en la regresiones de kernel de Linux
=======================================================================================


The important basics in more detail
-----------------------------------

Puntos básicos importantes más en detalle
-----------------------------------------


What to do when receiving regression reports
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qué hacer cuando se recibe un aviso de regresion.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ensure the Linux kernel's regression tracker and others subscribers of the
`regression mailing list <https://lore.kernel.org/regressions/>`_
(regressions@lists.linux.dev) become aware of any newly reported regression:

 * When you receive a report by mail that did not CC the list, immediately bring
   it into the loop by sending at least a brief "Reply-all" with the list CCed;
   try to ensure it gets CCed again in case you reply to a reply that omitted
   the list.

 * If a report submitted in a bug tracker hits your Inbox, forward or bounce it
   to the list. Consider checking the list archives beforehand, if the reporter
   already forwarded the report as instructed by
   Documentation/admin-guide/reporting-issues.rst.
   
Asegurar que el programa de gestion de regresiones del kernel de Linux y los
suscritos a la lista de correo `regression mailing list <https://lore.kernel.org/regressions/>`_
(regressions@lists.linux.dev) son conocedores the cualquier nuevo informe de regresion: 

 * Cuando se recive un informe por email que no tienen en CC la lista, inmediatamente
   meterla en el la cadena de emails mandado al menos un breve "Reply-all" con la lista en CC;
   Intentar asegurar que la lista es añadida en CC de nuevo en caso de que alguna
   repuesta la omita de la lista. 
   
 * Si un informe enviado a un gestor de defectos, llega a su correo, reenvielo o 
   rebotelo a la lista. Cosidere verificar los archivos de la lista de antemano, si 
   la persona que lo ha informado, lo ha enviado anteriormente, como se indica en 
   Documentation/admin-guide/reporting-issues.rst.
 

When doing either, consider making the Linux kernel regression tracking bot
"regzbot" immediately start tracking the issue:

 * For mailed reports, check if the reporter included a "regzbot command" like
   ``#regzbot introduced 1f2e3d4c5b6a``. If not, send a reply (with the
   regressions list in CC) with a paragraph like the following:::

       #regzbot ^introduced: v5.13..v5.14-rc1

   This tells regzbot the version range in which the issue started to happen;
   you can specify a range using commit-ids as well or state a single commit-id
   in case the reporter bisected the culprit.

   Note the caret (^) before the "introduced": it tells regzbot to treat the
   parent mail (the one you reply to) as the initial report for the regression
   you want to see tracked; that's important, as regzbot will later look out
   for patches with "Link:" tags pointing to the report in the archives on
   lore.kernel.org.
   

Cuando se realice cualquiera de las acciones anteriores, considerar inmediatamente
iniciar el seguimiento de la regresion con "regzbot" el gestor de regresiones del kernel de Linux.

 * Para los informes enviados por email, verificar si se ha incluido un commando a "regzbot", como
   ``#regzbot introduced 1f2e3d4c5b6a``. Si no es asi, envie una respuesta (con la lista
   de regressiones en CC) con un parrafo como el siguiente:: 

       #regzbot ^introduced: v5.13..v5.14-rc1

   Esto indica a regzbot el rango de versiones en el cual es defecto comenzó a suceder;
   Puede especificar un rango usando los identificadores de los commits así como
   un único commit, en caso el informate haya identificado el commit causante con 'bisect'.
   
   Tenga en cuenta que el acento circunflejo (^) antes de "introduced": Esto indica a 
   regzbot, que debe tratar el email padre (el que ha sido respondido) como el informe
   inicial para la regresion que quiere ser seguida. Esto es importante, ya que regzbot
   buscará más tarde parches con etiquetas "Link:" que apunten al al informe ne los
   archivos de lore.kernel.org. 
   
  

 * When forwarding a regressions reported to a bug tracker, include a paragraph
   with these regzbot commands::

       #regzbot introduced: 1f2e3d4c5b6a
       #regzbot from: Some N. Ice Human <some.human@example.com>
       #regzbot monitor: http://some.bugtracker.example.com/ticket?id=123456789

   Regzbot will then automatically associate patches with the report that
   contain "Link:" tags pointing to your mail or the mentioned ticket.
   
   
 * Cuando mande informes de regresiones a un gestor de defectos, incluya un 
   parrafo con los siguientes comandos a regzbot::
   
       #regzbot introduced: 1f2e3d4c5b6a
       #regzbot from: Some N. Ice Human <some.human@example.com>
       #regzbot monitor: http://some.bugtracker.example.com/ticket?id=123456789
     
   Regzbot asociará automaticamente parches con el informe que contengan las
   etiquetas "Link:" apuntando a su email o el ticket indicado. 
   
   

What's important when fixing regressions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Qué es imporate cuando se arreglan regresiones
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


You don't need to do anything special when submitting fixes for regression, just
remember to do what Documentation/process/submitting-patches.rst,
:ref:`Documentation/process/5.Posting.rst <development_posting>`, and
Documentation/process/stable-kernel-rules.rst already explain in more detail:

 * Point to all places where the issue was reported using "Link:" tags::

       Link: https://lore.kernel.org/r/30th.anniversary.repost@klaava.Helsinki.FI/
       Link: https://bugzilla.kernel.org/show_bug.cgi?id=1234567890

 * Add a "Fixes:" tag to specify the commit causing the regression.

 * If the culprit was merged in an earlier development cycle, explicitly mark
   the fix for backporting using the ``Cc: stable@vger.kernel.org`` tag.


No se necesita hacer nada especial cuando se mandan las correcciones para las
regresiones unicamente recordar lo que se explica en los documentos: 
Documentation/process/submitting-patches.rst,
:ref:`Documentation/process/5.Posting.rst <development_posting>`, y 
Documentation/process/stable-kernel-rules.rst 

 * Apuntar a todos los lugares donde el incidente se reportó usando la etiqueta "Link:" ::

       Link: https://lore.kernel.org/r/30th.anniversary.repost@klaava.Helsinki.FI/
       Link: https://bugzilla.kernel.org/show_bug.cgi?id=1234567890

 * Añadir la etiqueta "Fixes:" para indicar el commit causante de la regresion.
 
 * Si el culpable ha sido mergeado en un ciclo de desarrollo anterior, marcar
   explicitamente el fix para retroimportarlo usando la etiqueta ``Cc: stable@vger.kernel.org`` tag.
 


All this is expected from you and important when it comes to regression, as
these tags are of great value for everyone (you included) that might be looking
into the issue weeks, months, or years later. These tags are also crucial for
tools and scripts used by other kernel developers or Linux distributions; one of
these tools is regzbot, which heavily relies on the "Link:" tags to associate
reports for regression with changes resolving them.

Todo esto se espera y es importante en una regresión, ya que estas etiquetas son
de gran valor para todos (incluido usted) que pueda estar mirando en ese incidente
semanas, meses o años después. Estas etiquetas son tambień cruciales para las
herramientas y scripts usados por otros desarrolladores del kernel o distribuiciones
de Linux; una de esas herramientas es regzbot, el cual depende mucho de las etiquetas
"Link:" para asociar los informes por regresiones con los cambios que las 
resuelven.


Prioritize work on fixing regressions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Priorizacion del trabajo en arreglar regresiones
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You should fix any reported regression as quickly as possible, to provide
affected users with a solution in a timely manner and prevent more users from
running into the issue; nevertheless developers need to take enough time and
care to ensure regression fixes do not cause additional damage.

In the end though, developers should give their best to prevent users from
running into situations where a regression leaves them only three options: "run
a kernel with a regression that seriously impacts usage", "continue running an
outdated and thus potentially insecure kernel version for more than two weeks
after a regression's culprit was identified", and "downgrade to a still
supported kernel series that lack required features".

Se deberian arreglar y reportar regresiones tan rápido como sea posible, para
proveer a los usuarios afectados con una solución en el tiempo y prevenir 
que más usuarios del incidente; de todos modos los desarrolladores necesitan 
dedicar el tiempo suficiente y asegurar correcciones que no causen problemas
adicionales. 

Al final de todos modos, los desarrolladores deberian hacer lo posible parra
evitar a los usuarios situaciones donde una regresión les deje solo tres 
opciones: "ejecutar el kernel con una regresión que afecta seriamente al uso",
"continuar ejecutando una versión desfasada y potencialmente insegura del
kernel por más de dos semanas después de que el causante de una regresión 
fuese identificado", y "rebajarse a una versión soportada del kernel que no
tenga las funcionalidades requeridas".



How to realize this depends a lot on the situation. Here are a few rules of
thumb for you, in order or importance:

Cómo se ejecuta esto depende mucho de la situación. A continuación se presentan
unas reglas generales, en orden de importancia:


 * Prioritize work on handling regression reports and fixing regression over all
   other Linux kernel work, unless the latter concerns acute security issues or
   bugs causing data loss or damage.
   
 * Priorizar el trabajo en la gestión de los informes de la regresión y 
   arreglar la regressión por encima de cualquier otro trabajo en el kernel
   de Linux, a menos que lo último afecte profundamente a efectos de 
   seguridad, o cause errorer en los que haya pérdida o daño de datos. 

 * Always consider reverting the culprit commits and reapplying them later
   together with necessary fixes, as this might be the least dangerous and
   quickest way to fix a regression.
   
 * Considerar siempre revertir los commits reponsables y re-aplicarlos después,
   junto con las correciiones necesarias, ya que esto puede la forma
   menos peligrosa y más rápida de arreglar la regresión.

 * Developers should handle regressions in all supported kernel series, but are
   free to delegate the work to the stable team, if the issue probably at no
   point in time occurred with mainline.
   
 * Los desarrolladores deberian gestionar la regresión en todos los kernels
   soportados de la serie, pero son libres de delegar el trabajo al equipo 
   permanente el incidente no hubiese ocurrido en la linea principal. 

 * Try to resolve any regressions introduced in the current development before
   its end. If you fear a fix might be too risky to apply only days before a new
   mainline release, let Linus decide: submit the fix separately to him as soon
   as possible with the explanation of the situation. He then can make a call
   and postpone the release if necessary, for example if multiple such changes
   show up in his inbox.
   
 * Intentar resolver cualquier regressión que apareciera en el ciclo de
   desarrollo antes de que este acabe. Si se teme que una corrección pudiera
   ser demasiado arriesgada para aplicarla días antes de una liberación de
   la linea principal de desarrollo, dejar decidir a Linus: mandele la 
   corrección a el de forma separada, tan pronto como sea posible con 
   una explicación de la situación. El podrá decidir, y posponer la 
   liberación si fuese necesario, por ejemplo si apareciesen multiples 
   cambios como ese. 

 * Address regressions in stable, longterm, or proper mainline releases with
   more urgency than regressions in mainline pre-releases. That changes after
   the release of the fifth pre-release, aka "-rc5": mainline then becomes as
   important, to ensure all the improvements and fixes are ideally tested
   together for at least one week before Linus releases a new mainline version.
   
 * Gestione las regresiones en la rama estable, de largo termino, o la 
   propia rama principal de las versiones, con más urgencia que la regresiones
   en las pre-liberacioens. Esto cambia despues de la liberación de la 
   quinta pre-liberación, aka "-rc5": la rama principal entonces se vuelve
   más importante, asegurar que todas las mejoras y correciones son idealmente
   testeados juntos por al menos una semana antes de que Linux libere la
   nueva versión en la rama principal. 

 * Fix regressions within two or three days, if they are critical for some
   reason -- for example, if the issue is likely to affect many users of the
   kernel series in question on all or certain architectures. Note, this
   includes mainline, as issues like compile errors otherwise might prevent many
   testers or continuous integration systems from testing the series.

 * Aim to fix regressions within one week after the culprit was identified, if
   the issue was introduced in either:

    * a recent stable/longterm release

    * the development cycle of the latest proper mainline release
    
 * Intentae arreglar regresiones en un intervalo de una semana después de que
   se ha identificado el responsable, si el incidente fue introducido en 
   alguno de los siguientes casos:
   
    * una version estable/largo-plazo reciente
    
    * en el último ciclo de desarrollo de la rama principal

   In the latter case (say Linux v5.14), try to address regressions even
   quicker, if the stable series for the predecessor (v5.13) will be abandoned
   soon or already was stamped "End-of-Life" (EOL) -- this usually happens about
   three to four weeks after a new mainline release.
   
   En el último caso (por ejemplo v5.14), intentar gestionar las regresiones
   incluso más rápido, si la versión estable precedente (v5.13) ha de ser
   abandonada pronto o ya se ha etiquetado como de final de vida (EOL de 
   las siglas en inglés End-of-Life) -- esto sucede usualmente sobre
   tres o cuatro semanas después de una liberación de una versión en la 
   rama principal. 

 * Try to fix all other regressions within two weeks after the culprit was
   found. Two or three additional weeks are acceptable for performance
   regressions and other issues which are annoying, but don't prevent anyone
   from running Linux (unless it's an issue in the current development cycle,
   as those should ideally be addressed before the release). A few weeks in
   total are acceptable if a regression can only be fixed with a risky change
   and at the same time is affecting only a few users; as much time is
   also okay if the regression is already present in the second newest longterm
   kernel series.
   
 * Intentar arreglar cualquier otra regresión en un periodo de dos semanas
   después de que el culpable haya sido identificado. Dos o tres semanas
   adicionales son aceptables para regresiones de rendimiento y otros 
   incidentes que son molestos, pero no bloquean a nadie la ejecución de 
   Linux (a menos que se un incidente en el ciclo de desarrollo actual, en 
   ese caso se deberia gestionar antes de la liberación de la versión). Unas
   semanas son aceptables si la regresión únicamente puede ser arreglada 
   con un cambio arriesgado y al mismo tiempo únicamente afecta a unos pocos
   usuarios; tabién está bien si se usa tanto tiempo como fuera
   necesario si la regressión está presente en la segunda versión más nueva de 
   largo plazo del kernel.

Note: The aforementioned time frames for resolving regressions are meant to
include getting the fix tested, reviewed, and merged into mainline, ideally with
the fix being in linux-next at least briefly. This leads to delays you need to
account for.

Nota: Los intervalos de tiempo mencionados anteriormente para la resolución 
de las regresiones, incluyen la verificación de esta, revisión e inclusión 
en la rama principal, idealmente con la correción incluida en la rama 
"linux-next" al menos brevemente. Esto conllevará retrasos que también se tienen
tener en cuenta. 

Subsystem maintainers are expected to assist in reaching those periods by doing
timely reviews and quick handling of accepted patches. They thus might have to
send git-pull requests earlier or more often than usual; depending on the fix,
it might even be acceptable to skip testing in linux-next. Especially fixes for
regressions in stable and longterm kernels need to be handled quickly, as fixes
need to be merged in mainline before they can be backported to older series.

Se espera que los mantenedores de los subsistemas, ayuden en conseguir esos
tiempos, haciendo revisiones con protitud y gestionando con rapidez los parches
aceptados. Esto puede resultar en tener que mandar peticiones de git-pull 
antes o de forma más frecuente que lo normal; dependiendo del arreglo, 
podria incluso ser acceptabe saltarse la verificación en linux-next. Especialmente
para las correcciones en las ramas de los kernels estable y de largo plazo
necesitan ser gestinadas rápidamente, y las correcciones necesitan ser 
incluidas en la rama principal antes de que puedan ser retroincludias a las
series precedentes. 


More aspects regarding regressions developers should be aware of
----------------------------------------------------------------

Más aspectos sobre regresiones que los desarrolladores deben saber
------------------------------------------------------------------


How to deal with changes where a risk of regression is known
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Cómo tratar con cambios donde se sabe que hay riesgo de regresión
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Evaluate how big the risk of regressions is, for example by performing a code
search in Linux distributions and Git forges. Also consider asking other
developers or projects likely to be affected to evaluate or even test the
proposed change; if problems surface, maybe some solution acceptable for all
can be found.

Evaluar cómo de grande es el reisgo de una regresión, por ejemplo realizando
una búsqueda en las distribuciiones de linux y en Git forges. Considerar 
también preguntar a otros desarrolladores o proyectos que pudieran ser 
afectados para evaluar o incluso testear el cambio propuesto; si apareciesen 
problemas, quizás se pudiera encontrar una solución aceptable para todos.


If the risk of regressions in the end seems to be relatively small, go ahead
with the change, but let all involved parties know about the risk. Hence, make
sure your patch description makes this aspect obvious. Once the change is
merged, tell the Linux kernel's regression tracker and the regressions mailing
list about the risk, so everyone has the change on the radar in case reports
trickle in. Depending on the risk, you also might want to ask the subsystem
maintainer to mention the issue in his mainline pull request.

Si al final, el riesgo de la regressión parece ser relativamente pequeño, 
entonces adelante con el cambio, pero siempre informar a todas las partes involucradas
del posible riesgo. Por tanto, asegurarse que el la descripción del parche, 
se hace explicito este hecho. Una vez el cambio ha sido integrado, informar
al gestor de regressiones de Linux y a las listas de correo de regressiones 
sobre el riesgo, de manera que cualquiera que tenga el cambio en el radar, 
en el caso de que aparezcan reportes. Dependiendo del riesgo, quizás se 
quiera preguntar al mantenedor del subsistema, que mencione el hecho en su 
linea principal de desarrollo. 



What else is there to known about regressions?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

¿Qué más hay que saber sobre regresiones?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Check out Documentation/admin-guide/reporting-regressions.rst, it covers a lot
of other aspects you want might want to be aware of:

 * the purpose of the "no regressions rule"

 * what issues actually qualify as regression

 * who's in charge for finding the root cause of a regression

 * how to handle tricky situations, e.g. when a regression is caused by a
   security fix or when fixing a regression might cause another one
     
   
Repasar la documentación Documentation/admin-guide/reporting-regressions.rst, 
esta cubre otros aspectos a tener a encuenta y conocer:
 
 * la finalidad de la "regla de no regresión"
 
 * que incidentes no se califican como regresión
 
 * quien es el responsable de identificar la causa raíz de una regresión
 
 * como gestionar situaciones difíciles, como por ejemplo cuando una 
   regresión es causada por una corrección de seguridad o cuando una 
   regresión causa otra

Whom to ask for advice when it comes to regressions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A quién preguntar por consejo cuando se trata de regresiones
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Send a mail to the regressions mailing list (regressions@lists.linux.dev) while
CCing the Linux kernel's regression tracker (regressions@leemhuis.info); if the
issue might better be dealt with in private, feel free to omit the list.

Mandar un emal a la lista de correo de regresiones (regressions@lists.linux.dev)
y CC al seguidor de regressiones del kernel de Linux (regressions@leemhuis.info);
Si el incidente pudiera ser mejor gestionarlo en privado, puede omitirse la lista.


More about regression tracking and regzbot
------------------------------------------

Más sobre la gestión de regresiones con regzbot
-----------------------------------------------

Why the Linux kernel has a regression tracker, and why is regzbot used?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

¿Porqué el kernel de Linux tiene un gestor de regresiones, y porqué se usa regzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Rules like "no regressions" need someone to ensure they are followed, otherwise
they are broken either accidentally or on purpose. History has shown this to be
true for the Linux kernel as well. That's why Thorsten Leemhuis volunteered to
keep an eye on things as the Linux kernel's regression tracker, who's
occasionally helped by other people. Neither of them are paid to do this,
that's why regression tracking is done on a best effort basis.

Reglas como "no regresiones" necesitan asegurar que se cumplen, de otro modo
se romperían acidentalmente o a propósito. La historia ha mostrado que esto es
verdád también para el kernel de Linux. Esto es por lo que Thorsten Leemhuis
se ofreció como voluntiario para dar una solución a esto, con el gestor de 
regresiones del kernel de Linux. A nadie se le paga por hacer esto, y esa
es la razón por la gestion de regresiones es un servicio con el "mejor esfuerzo". 

Earlier attempts to manually track regressions have shown it's an exhausting and
frustrating work, which is why they were abandoned after a while. To prevent
this from happening again, Thorsten developed regzbot to facilitate the work,
with the long term goal to automate regression tracking as much as possible for
everyone involved.

Intentos anteriores de gestionar manualmente las regresiones han demostrado que
es una tarea extenuante y frustrante, y por esa razón se dejaron de hacer
despúes de un tiempo. Para evitar que volviese a suceder esto, Thorsten
desarrollo regbot para facilitar el trabajo, con el obejtivo a largo plazo de
automatizar la gestion de regresiones tanto como fuese posible para cualquiera
que estuviese involucrado.

How does regression tracking work with regzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

¿Cómo funciona el seguimiento de regresiones con regzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The bot watches for replies to reports of tracked regressions. Additionally,
it's looking out for posted or committed patches referencing such reports
with "Link:" tags; replies to such patch postings are tracked as well.
Combined this data provides good insights into the current state of the fixing
process.

El bot espera a las respuestas de los informes de las regresiones indentificadas.
Adiconalmente mira si se han publicado o enviado parches que hagan referencia a
esos informes lon la etiqueta: "Link:"; respuestas a esos parches también se 
siguen. Combinando esta información, también proporciona una buena imagen del 
estado actual del proceso de corrección. 

Regzbot tries to do its job with as little overhead as possible for both
reporters and developers. In fact, only reporters are burdened with an extra
duty: they need to tell regzbot about the regression report using the ``#regzbot
introduced`` command outlined above; if they don't do that, someone else can
take care of that using ``#regzbot ^introduced``.

Regzbot intenta hacer todo este trabajo con tan poco retraso como sea posible
para tanto la gente que lo reporta como los desarrolladores. De hecho, solo 
los informantes son requeridos para una tarea adicional: necesitan informar
a regzbot con el comando ``#regzbot introduced`` indicado anteriormente; si 
no hacen esto, alguien más puede hacerlo usando ``#regzbot ^introduced``.

For developers there normally is no extra work involved, they just need to make
sure to do something that was expected long before regzbot came to light: add
"Link:" tags to the patch description pointing to all reports about the issue
fixed.

Para desarrolladores normalmente no hay un trabajo adicional que realizar, 
únicamente necesitan asegurarse una cosa, que ya se hacia mucho antes de que 
regzbot apareciera: añadir las etiquetas "Link:" a la descripción del parche
apuntando a todos los informes sobre el error corregido.

Do I have to use regzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~

¿Tengo que usar regzbot?
~~~~~~~~~~~~~~~~~~~~~~~~

It's in the interest of everyone if you do, as kernel maintainers like Linus
Torvalds partly rely on regzbot's tracking in their work -- for example when
deciding to release a new version or extend the development phase. For this they
need to be aware of all unfixed regression; to do that, Linus is known to look
into the weekly reports sent by regzbot.

Hacerlo es por el bien de todo el mundo, como los mantenedores del kernel,
como Linus Torvalds dependen parcialmente en regzbot para seguir su trabajo --
por ejemplo cuando deciden liberar una nueva version o ampliar la fase de 
desarrollo. Pra esto necesitan conocer todas las regresiones que están sin 
corregir; para esto, es conocido que Linux mira los informes semanales que
manda regzbot. 


Do I have to tell regzbot about every regression I stumble upon?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ideally yes: we are all humans and easily forget problems when something more
important unexpectedly comes up -- for example a bigger problem in the Linux
kernel or something in real life that's keeping us away from keyboards for a
while. Hence, it's best to tell regzbot about every regression, except when you
immediately write a fix and commit it to a tree regularly merged to the affected
kernel series.


¿He de informar a regzbot cada regresión que encuentre? 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Idealmente sí: todos somos humanos y olvidamos fácilmente los problemas cuando
algo más importante aparece inesperadamente -- por ejemplo un problema mayor
en el kernel de Linux o algo en la vida real que nos mantenga alejados de los
teclados por un tiempo. Por eso es mejor informar a regzbot sobre cada
regresión, excepto cuando inmediatamente escribimos un parche y los mandamos
al árbol de desarrollo en el que se integran habitualmente a la serie del kernel. 


How to see which regressions regzbot tracks currently?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Check `regzbot's web-interface <https://linux-regtracking.leemhuis.info/regzbot/>`_
for the latest info; alternatively, `search for the latest regression report
<https://lore.kernel.org/lkml/?q=%22Linux+regressions+report%22+f%3Aregzbot>`_,
which regzbot normally sends out once a week on Sunday evening (UTC), which is a
few hours before Linus usually publishes new (pre-)releases.

¿Cómo ver qué regresiones esta siguiendo regbot actualmente?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Verifique el `interfaz web de regzbot <https://linux-regtracking.leemhuis.info/regzbot/>`_
para ver la última información; o `busque el último informe de regresiones
<https://lore.kernel.org/lkml/?q=%22Linux+regressions+report%22+f%3Aregzbot>`_,
el cual suele ser enviado por regzbot una vez a la semana el domingo por la noche (UTC),
lo cual es unas horas antes de que Linus normalmete anuncie las "(pre-)releases".

What places is regzbot monitoring?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Regzbot is watching the most important Linux mailing lists as well as the git
repositories of linux-next, mainline, and stable/longterm.

¿Qué sítios supervisa regzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Regzbot supervisa las listas de corro más importantes de Linux, como también
las de los repositorios linux-next, mainline y stable/longterm.



What kind of issues are supposed to be tracked by regzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The bot is meant to track regressions, hence please don't involve regzbot for
regular issues. But it's okay for the Linux kernel's regression tracker if you
use regzbot to track severe issues, like reports about hangs, corrupted data,
or internal errors (Panic, Oops, BUG(), warning, ...).

¿Qué tipos de incidentes han de ser monitorizados por regzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
El bot debe hacer seguimiento de las regresiones, y por tanto por favor, 
no involucre a regzbot para incidencias normales. Pero es correcto para
el gestor de incidencias de kernel de Linux, monitorizar incidentes
graves, como informes sobre cuelgues, corrupción de datos o errores
internos (Panic, Oops, BUG(), warning, ...).


Can I add regressions found by CI systems to regzbot's tracking?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Feel free to do so, if the particular regression likely has impact on practical
use cases and thus might be noticed by users; hence, please don't involve
regzbot for theoretical regressions unlikely to show themselves in real world
usage.

¿Puedo añadir una regression detectada por un sistema de CI al seguimiento de regzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sientase libre de hacero, si la regresión en concreto puede tener un impacto en 
casos de uso práctiocs y por tanto ser detectado por los usuarios; Así, por favor
no involucre a regzbot en regresiones teóricas que dificilmente pudieran 
manifestarse en un uso real. 


How to interact with regzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

¿Cómo interactuar con regzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By using a 'regzbot command' in a direct or indirect reply to the mail with the
regression report. These commands need to be in their own paragraph (IOW: they
need to be separated from the rest of the mail using blank lines).

Usando el comando 'regzbot' en una respuesta directa o indirecta al correo con
el informe de regresión. Ese comando necesita estar en su propio párrafo (debe
estar separado del resto del text usando lineas en blanco):


One such command is ``#regzbot introduced <version or commit>``, which makes
regzbot consider your mail as a regressions report added to the tracking, as
already described above; ``#regzbot ^introduced <version or commit>`` is another
such command, which makes regzbot consider the parent mail as a report for a
regression which it starts to track.

Por ejemplo ``#regzbot introduced <version or commit>``, que hace que regzbot
considere el correo como un informe de regressión que se ha de añadir al seguimiento,
como se ha descrito anteriormente; ``#regzbot ^introduced <version or commit>`` es
otro ejemplo del comando, el cual indica a regzbot que considere el email 
anterior como el informe de una regressión que se ha de comenzar a monitorizar. 

Once one of those two commands has been utilized, other regzbot commands can be
used in direct or indirect replies to the report. You can write them below one
of the `introduced` commands or in replies to the mail that used one of them
or itself is a reply to that mail:

Una vez uno de esos dos comandos se ha utilizado, se pueden usar otros comandos
regzbot en respuestas directas o indirectas al infomre. Puede escribirlos debajo
de uno de los comandos anteriormente usados o en las respuestas al correo en el
que se uso como respuesta a ese correo: 

 * Set or update the title::

       #regzbot title: foo
       
 * Definir o actualizar el título::       
 
       #regzbot title: foo

 * Monitor a discussion or bugzilla.kernel.org ticket where additions aspects of
   the issue or a fix are discussed -- for example the posting of a patch fixing
   the regression::

       #regzbot monitor: https://lore.kernel.org/all/30th.anniversary.repost@klaava.Helsinki.FI/

   Monitoring only works for lore.kernel.org and bugzilla.kernel.org; regzbot
   will consider all messages in that thread or ticket as related to the fixing
   process.

 * Monitorizar una discusión o un tiquet de bugzilla.kernel.org donde aspectos
 adicionales del incidente o de la corrección se están comentando -- por ejemplo
 presentar un parche que corrige la regresión::

       #regzbot monitor: https://lore.kernel.org/all/30th.anniversary.repost@klaava.Helsinki.FI/
       
  Monitorizar solamente funciona para lore.kernel.org y bugzilla.kernel.org; regzbot
  considerará todos los mensajes en ese hilo o el tiquet como relacionados al 
  proceso de corrección.      
     
 * Point to a place with further details of interest, like a mailing list post
   or a ticket in a bug tracker that are slightly related, but about a different
   topic::

       #regzbot link: https://bugzilla.kernel.org/show_bug.cgi?id=123456789

 * Indicar a un lugar donde más detalles de interes, como un mensaje en una lista
 de correo o un tiquet en un gestor de incidencias que pueden estar levemente relacionados, 
 pero con un tema diferente::
 
       #regzbot link: https://bugzilla.kernel.org/show_bug.cgi?id=123456789
       
       
 * Mark a regression as fixed by a commit that is heading upstream or already
   landed::

       #regzbot fixed-by: 1f2e3d4c5d
       
 * Anotar una regression como corregida por un commit quee se ha mandado aguas arriba 
 o se ha publicado::
 
        #regzbot fixed-by: 1f2e3d4c5d

 * Mark a regression as a duplicate of another one already tracked by regzbot::

       #regzbot dup-of: https://lore.kernel.org/all/30th.anniversary.repost@klaava.Helsinki.FI/
       
 * Anotar una regresión como un duplicado de otra que ya es seguida por regzbot::
 
        #regzbot dup-of: https://lore.kernel.org/all/30th.anniversary.repost@klaava.Helsinki.FI/

 * Mark a regression as invalid::

       #regzbot invalid: wasn't a regression, problem has always existed
       
 * Anotar una regressión como invalida::
 
       #regzbot invalid: wasn't a regression, problem has always existed
       
       

Is there more to tell about regzbot and its commands?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

More detailed and up-to-date information about the Linux
kernel's regression tracking bot can be found on its
`project page <https://gitlab.com/knurd42/regzbot>`_, which among others
contains a `getting started guide <https://gitlab.com/knurd42/regzbot/-/blob/main/docs/getting_started.md>`_
and `reference documentation <https://gitlab.com/knurd42/regzbot/-/blob/main/docs/reference.md>`_
which both cover more details than the above section.

¿Algo más que decir sobre regzbot y sus comandos?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Hay información más detallada y actualizada sobre el bot de seguimiento de
regresiones del kernel de Linux en: `project page <https://gitlab.com/knurd42/regzbot>`_,
y entre otros contiene una  `guia de inicio <https://gitlab.com/knurd42/regzbot/-/blob/main/docs/getting_started.md>`_
y `documentación de referencia <https://gitlab.com/knurd42/regzbot/-/blob/main/docs/reference.md>`_
ambos contienen más detalles que las secciones anteriores. 


Quotes from Linus about regression
----------------------------------

Citas de Linus sobre regresiones
--------------------------------


Find below a few real life examples of how Linus Torvalds expects regressions to
be handled:

Debajo se encuentran unos ejemplos reales de como Linus Torvalds espera que se gestionen
las regresiones:

 * From `2017-10-26 (1/2)
   <https://lore.kernel.org/lkml/CA+55aFwiiQYJ+YoLKCXjN_beDVfu38mg=Ggg5LFOcqHE8Qi7Zw@mail.gmail.com/>`_::

       If you break existing user space setups THAT IS A REGRESSION.

       It's not ok to say "but we'll fix the user space setup".

       Really. NOT OK.

       [...]

       The first rule is:

        - we don't cause regressions

       and the corollary is that when regressions *do* occur, we admit to
       them and fix them, instead of blaming user space.

       The fact that you have apparently been denying the regression now for
       three weeks means that I will revert, and I will stop pulling apparmor
       requests until the people involved understand how kernel development
       is done.

 * De 2017-10-26 (1/2)
   <https://lore.kernel.org/lkml/CA+55aFwiiQYJ+YoLKCXjN_beDVfu38mg=Ggg5LFOcqHE8Qi7Zw@mail.gmail.com/>`_::

     Si romopes la configuracion de los espacios de usuaro ESO ES UNA REGRESIÓN.

     No esta bien decir "pero nosotros arreglaremos la configuración del espacio de usuario". 

     Realmente. NO ESTÁ BIEN. 

     [...]

     La primera regla es: 

     - no causamos regresiones

     y el corolario es que cuando una regressión pasa, lo admitimos y lo 
     arreglamos, en vez de echar la culpa al espacio de usuario.

     El hecho de que aparentemente se haya negado la regresión durante
     tres semanas, significa que lo revertiré y dejaré de integrar peticiones
     de apparmor hasta que la gente involucrada entienda como se hace
     el desarrollo del kernel. 


 * From `2017-10-26 (2/2)
   <https://lore.kernel.org/lkml/CA+55aFxW7NMAMvYhkvz1UPbUTUJewRt6Yb51QAx5RtrWOwjebg@mail.gmail.com/>`_::

       People should basically always feel like they can update their kernel
       and simply not have to worry about it.

       I refuse to introduce "you can only update the kernel if you also
       update that other program" kind of limitations. If the kernel used to
       work for you, the rule is that it continues to work for you.

       There have been exceptions, but they are few and far between, and they
       generally have some major and fundamental reasons for having happened,
       that were basically entirely unavoidable, and people _tried_hard_ to
       avoid them. Maybe we can't practically support the hardware any more
       after it is decades old and nobody uses it with modern kernels any
       more. Maybe there's a serious security issue with how we did things,
       and people actually depended on that fundamentally broken model. Maybe
       there was some fundamental other breakage that just _had_ to have a
       flag day for very core and fundamental reasons.

       And notice that this is very much about *breaking* peoples environments.

       Behavioral changes happen, and maybe we don't even support some
       feature any more. There's a number of fields in /proc/<pid>/stat that
       are printed out as zeroes, simply because they don't even *exist* in
       the kernel any more, or because showing them was a mistake (typically
       an information leak). But the numbers got replaced by zeroes, so that
       the code that used to parse the fields still works. The user might not
       see everything they used to see, and so behavior is clearly different,
       but things still _work_, even if they might no longer show sensitive
       (or no longer relevant) information.

       But if something actually breaks, then the change must get fixed or
       reverted. And it gets fixed in the *kernel*. Not by saying "well, fix
       your user space then". It was a kernel change that exposed the
       problem, it needs to be the kernel that corrects for it, because we
       have a "upgrade in place" model. We don't have a "upgrade with new
       user space".

       And I seriously will refuse to take code from people who do not
       understand and honor this very simple rule.

       This rule is also not going to change.

       And yes, I realize that the kernel is "special" in this respect. I'm
       proud of it.

       I have seen, and can point to, lots of projects that go "We need to
       break that use case in order to make progress" or "you relied on
       undocumented behavior, it sucks to be you" or "there's a better way to
       do what you want to do, and you have to change to that new better
       way", and I simply don't think that's acceptable outside of very early
       alpha releases that have experimental users that know what they signed
       up for. The kernel hasn't been in that situation for the last two
       decades.

       We do API breakage _inside_ the kernel all the time. We will fix
       internal problems by saying "you now need to do XYZ", but then it's
       about internal kernel API's, and the people who do that then also
       obviously have to fix up all the in-kernel users of that API. Nobody
       can say "I now broke the API you used, and now _you_ need to fix it
       up". Whoever broke something gets to fix it too.

       And we simply do not break user space.

 * De `2017-10-26 (2/2)
   <https://lore.kernel.org/lkml/CA+55aFxW7NMAMvYhkvz1UPbUTUJewRt6Yb51QAx5RtrWOwjebg@mail.gmail.com/>`_::

       La gente deberia sentirse libre de actualizar su kernel y simplemente
       no preocuparse por ello.

       Me niego a imponer una limitación del tipo "solo puede actualizar
       el kernel si actualiza otro programa". Si el kernel trabaja para tí,
       la regla es que continue trabajando para tí. 

       Ha habido algunas excepciones, pero son pocas y separadas entre sí, y generalmente
       tienen una razón fundamental para haber sucedido, que era básicamente
       inevitable, y la gente intentó evitarlas por todos los medios. Quizás no podamos
       mantener el hardware más, depués de que han pasado décadas y nadie los usa
       con kernel modernos. Quizás haya un problema de seguridad serio con cómo
       hicimos las cosas, y la gente dependa de un modelo fundamentalmente roto. 
       Quizás haya algun otro roto fundamental, que tenga que tener una _flag_ 
       y por razones internas y fundamentales. 

       Y notesé que esto trata sobre *romper* los entornos de la gente.

       Behavioral changes happen, and maybe we don't even support some
       feature any more. There's a number of fields in /proc/<pid>/stat that
       are printed out as zeroes, simply because they don't even *exist* in
       the kernel any more, or because showing them was a mistake (typically
       an information leak). But the numbers got replaced by zeroes, so that
       the code that used to parse the fields still works. The user might not
       see everything they used to see, and so behavior is clearly different,
       but things still _work_, even if they might no longer show sensitive
       (or no longer relevant) information.

       Cambios de comportamiento pasan, y quizás no se mantengan algunas
       funcionalidades más. Hay un número de campos en /proc/<pid>/stat que
       se imprimen como ceros, simplemente porque ni siquiera existen ya en 
       kernel, o porque mostrarlos era un error (típica una fuga de 
       información). Pero los números se sustituyeron por ceros, asi que
       el código que se usaba para parsar esos campos todavia existe. El 
       usuario puede no ver todo lo que podía ver antes, y por eso el comportamiento
       es claramente diferente, pero las cosas todavía _funcionan_, incluso si
       no se puede mostrar información sensible (o que no es ya importante).

       But if something actually breaks, then the change must get fixed or
       reverted. And it gets fixed in the *kernel*. Not by saying "well, fix
       your user space then". It was a kernel change that exposed the
       problem, it needs to be the kernel that corrects for it, because we
       have a "upgrade in place" model. We don't have a "upgrade with new
       user space".

       Pero si algo realmente se rompe, entonces el cambio debe de arreglarse
       o revertirse. Y se arregla en el *kernel*. No diciendo "bueno, arreglaremos
       tu espacio de usuario". Ha sido un cambio en el kernel el que creo
       el problema, entonces ha de ser el kernel el que lo corrija, porque 
       tenemos un modelo de "actualización". Pero no tenemos una "actualización
       con el nuevo espacio de usuario". 
       
       Y yo seriamente me negaré a coger código de gente que no entiende y 
       honre esta sencilla regla.

       Y esta regla no va a cambiar. 

       Y sí, me doy cuenta que el kernel es "especial" en este respecto. Y 
       estoy orgulloso de ello.

       Y he visto, y puedo señalar, muchos proyectos que dicen "Tenemos que  
       romper ese caso de uso para poder hacer progresos" o "estabas basandote
       en comportamientos no documentados, debe ser duro ser tú" o "hay una forma
       mejor de hacer lo que quiees hacer, y tienes que cambiar a esa nueva forma",
       y yo simplmente no pienso que eso sea aceptable fuera de una fase alfa muy 
       temprana que tenga usuarios experimentales que saben a lo que se han apuntado.
       El kernel no ha estado en esta situción en las dos últimas décadas. 

       Nosotros rompemos la API _dentro_ del kernel todo el tiempo. Y arreglaremos
       los problemas internos diciendo "tú ahora necesitas hacer XYZ", pero 
       entonces es sobre la API interna del kernel y la gente que hace esto 
       entonces tendrá obviamente que arreglar todos los usos de esa API del 
       kernel. Nadie puede decir "ahora, yo he roto la API que usas, y ahora
       tú necesitas arreglarlo". Quién rompa algo, lo arregla también. 

       Y nosotros, simplemente, no rompemos el espacio de usuario. 

 * De `2020-05-21
   <https://lore.kernel.org/all/CAHk-=wiVi7mSrsMP=fLXQrXK_UimybW=ziLOwSzFTtoXUacWVQ@mail.gmail.com/>`_::

       The rules about regressions have never been about any kind of
       documented behavior, or where the code lives.

       Las reglas sobre regresiones nunca han sido sobre ningún tipo de 
       comportamiento documentado, o dónde está situado el código.

       The rules about regressions are always about "breaks user workflow".

       Las reglas sobre regresiones son siempre sobre "roturas en el
       flujo de trabajo del usuario".

       Users are literally the _only_ thing that matters.

       Los usuarios son literalmente la _única_ cosa que importa.

       No amount of "you shouldn't have used this" or "that behavior was
       undefined, it's your own fault your app broke" or "that used to work
       simply because of a kernel bug" is at all relevant.

       Argumentaciones como "no deberia haber usado esto" o "ese comportamiento
       es indefinido, es su su culpa que su aplicación no funcione" o 
       "eso solia funcionar únicamente por un bug del kernel" son 
       irrelevantes.

       Now, reality is never entirely black-and-white. So we've had things
       like "serious security issue" etc that just forces us to make changes
       that may break user space. But even then the rule is that we don't
       really have other options that would allow things to continue.

       Ahora, la realidad nunca es blanca o negra. Así hemos tenido situaciones
       como "un serio incidente de seguridad" etc que solamente nos fuerza
       a hacer cambios que pueden romper el espacio de usuario. Pero incluso
       entonces la regla es que realmente no hay otras opciones para que
       las cosas sigan funcionando. 

       And obviously, if users take years to even notice that something
       broke, or if we have sane ways to work around the breakage that
       doesn't make for too much trouble for users (ie "ok, there are a
       handful of users, and they can use a kernel command line to work
       around it" kind of things) we've also been a bit less strict.

       Y obiamente, is los usuarios tardan años en darse cuenta que algo
       se ha roto, o si hay formas adecuadas para sortear la rotura que
       no causen muchos problemas para los usuarios (por ejemplo: "hay un
       puñado de usuarios, y estos pueden usar la linea de comandos del 
       kernel para evitarlos"; ese tipo de casos), en esos casos se ha sido
       un poco menos estricto.

       But no, "that was documented to be broken" (whether it's because the
       code was in staging or because the man-page said something else) is
       irrelevant. If staging code is so useful that people end up using it,
       that means that it's basically regular kernel code with a flag saying
       "please clean this up".

       Pero no, "eso que está documentado que está roto" (si es dado a que
       el código estába en preparación o porque el manual dice otra cosa) eso 
       es irrelevante. Si preparar el código es tan útil que la gente, 
       acaba usandlo, esto implica que básicamente es código del kernel con 
       una señal diciendo "por favor limpiar esto". 

       The other side of the coin is that people who talk about "API
       stability" are entirely wrong. API's don't matter either. You can make
       any changes to an API you like - as long as nobody notices.

       El otro lado de la moneda es que la getne que habla sobre "estabilidad
       de las APIs" están totalmente equivocados. Las APIs tampoco importan.
       Se puede hacer cualquier cambio que se quiera a una API ... siempre y 
       cuando nadie se de cuenta.

       Again, the regression rule is not about documentation, not about
       API's, and not about the phase of the moon.

       De nuevo, la regla de las regresiones no trata sobre la documentacion, 
       tampoco sobre las APIs y tampoco sobre las fases de la Luna. 

       It's entirely about "we caused problems for user space that used to work".

       Únicamente trata sobre "hemos causado problemas al espacio de usuario que
       antes funcionaba". 

 * De `2017-11-05
   <https://lore.kernel.org/all/CA+55aFzUvbGjD8nQ-+3oiMBx14c_6zOj2n7KLN3UsJ-qsd4Dcw@mail.gmail.com/>`_::

       And our regression rule has never been "behavior doesn't change".
       That would mean that we could never make any changes at all.

       Y nuestra regla sobre las regresiones nunca ha sido "el comportamiento
       no cambia". Eso podria significar que nunca podríamos hacer ningún
       cambio.

       For example, we do things like add new error handling etc all the
       time, which we then sometimes even add tests for in our kselftest
       directory.

       Por ejemplo, hacemos cosas como añadir una nueva gestión de 
       errores etc todo el tiempo, con lo cual a veces incluso añadimos
       tests en el directorio de kselftest.

       So clearly behavior changes all the time and we don't consider that a
       regression per se.

       Así que claramente cambia el comportamiento todo el timepo y 
       nosotros no consideramos eso una regressión per se.

       The rule for a regression for the kernel is that some real user
       workflow breaks. Not some test. Not a "look, I used to be able to do
       X, now I can't".

       La regla para regresiones para el kernel es para cuando se
       rompe algo en el espacio de usuario. No en algún test. No en
       "mira, antes podía hacer X, y ahora no puedo". 

 * De `2018-08-03
   <https://lore.kernel.org/all/CA+55aFwWZX=CXmWDTkDGb36kf12XmTehmQjbiMPCqCRG2hi9kw@mail.gmail.com/>`_::

       YOU ARE MISSING THE #1 KERNEL RULE.

       ESTÁS OLVIDANDO LA REGLA #1 DEL KERNEL.

       We do not regress, and we do not regress exactly because your are 100% wrong.

       No hacemos regresiones, y no hacemos regresiones porque estás 100% equivocado.

       And the reason you state for your opinion is in fact exactly *WHY* you
       are wrong.

       Y la razón que apuntas en tú opinion es exactamente *PORQUÉ* estás equivocado.

       Your "good reasons" are pure and utter garbage.

       Tus "buenas razones" son honradas y pura basura. 

       The whole point of "we do not regress" is so that people can upgrade
       the kernel and never have to worry about it.

       El punto de "no hacemos regresiones" es que la gente pueda actualizar
       el kernel y nunca han de preocuparse por ello. 

       > Kernel had a bug which has been fixed

       > El kernel tiene un bug que ha de ser arreglado

       That is *ENTIRELY* immaterial.

       Eso es *ENTERAMENTE* insustancial. 

       Guys, whether something was buggy or not DOES NOT MATTER.

       Chicos, si algo estaba roto o no NO IMPORTA.

       Why?

       Porqué?

       Bugs happen. That's a fact of life. Arguing that "we had to break
       something because we were fixing a bug" is completely insane. We fix
       tens of bugs every single day, thinking that "fixing a bug" means that
       we can break something is simply NOT TRUE.

       Los errores pasan. Eso es una hecho de la vida. Discutir que
       "tenemos que romper algo porque estábamos arreglando un error" es
       una locura. Arreglamos decenas de errores cada dia, pensando que 
       "arreglando un bug" significa que podemos romper otra cosa es algo 
       que simplemente NO ES VERDAD.

       So bugs simply aren't even relevant to the discussion. They happen,
       they get found, they get fixed, and it has nothing to do with "we
       break users".

       Así que los bugs no son realmente relevantes para la discusión. Estos
       suceden y se detectan, se arreglan, y no tienen nada que ver con 
       "rompemos a los usuarios".

       Because the only thing that matters IS THE USER.

       Porque la única cosa que impora ES EL USUARIO.

       How hard is that to understand?

       ¿Cómo de complicado es eso de comprender?

       Anybody who uses "but it was buggy" as an argument is entirely missing
       the point. As far as the USER was concerned, it wasn't buggy - it
       worked for him/her.

       Cualquier porsona que use "pero no funcionaba correctamente" es
       un argumento no tiene la razón. Con respecto al USUARIO, no era
       erroneo - funcionaba para él/ella. 

       Maybe it worked *because* the user had taken the bug into account,
       maybe it worked because the user didn't notice - again, it doesn't
       matter. It worked for the user.

       Quizás funcionaba *porque* el usuario habia tenido el bug en cuenta, 
       y quizás funcionaba porque el usuario no lo había notado - de nuevo
       no importa. Funcionaba para el usuario. 

       Breaking a user workflow for a "bug" is absolutely the WORST reason
       for breakage you can imagine.

       Romper el flujo del trabajo de un usuario, debido a un "bug" es la
       PEOR razón que se pueda usar. 

       It's basically saying "I took something that worked, and I broke it,
       but now it's better". Do you not see how f*cking insane that statement
       is?

       Es básicamente decir "He cogido algo que funcionaba, y lo he roto,
       pero ahora es mejor". ¿No ves que un argumento como este es j*didamente 
       absurdo?

       And without users, your program is not a program, it's a pointless
       piece of code that you might as well throw away.

       y sin usuarios, tu programa no es un programa, es una pieza de 
       código sin finalidad que puedes perfectamente tirár a la basura.

       Seriously. This is *why* the #1 rule for kernel development is "we
       don't break users". Because "I fixed a bug" is absolutely NOT AN
       ARGUMENT if that bug fix broke a user setup. You actually introduced a
       MUCH BIGGER bug by "fixing" something that the user clearly didn't
       even care about.

       Seriamente. Esto es *porque* la regla #1 para el desarrollo del 
       kernel es "no rompemos el espacio de usuario". Porque "He arreglado
       un error" PARA NADA ES UN ARGUMENTO si esa correción del código
       rompe el espacio de usuario.

       And dammit, we upgrade the kernel ALL THE TIME without upgrading any
       other programs at all. It is absolutely required, because flag-days
       and dependencies are horribly bad.

       si actualizamos el kernel TODO EL TIEMPO, sin actualizar ningún otro
       programa en absoluto. Y esto es absolutamente necesario, porque 
       las dependecias son terribles. 

       And it is also required simply because I as a kernel developer do not
       upgrade random other tools that I don't even care about as I develop
       the kernel, and I want any of my users to feel safe doing the same
       time.

       Y esto es necesario simplemente porque yo como desarrollador del
       kernel no actualizo al azar otras herramientas que ni si quiera me
       importan como desarrollador del kernel, y yo quiero que mis usuarios
       se sientas a salvo haciendo lo mismo. 

       So no. Your rule is COMPLETELY wrong. If you cannot upgrade a kernel
       without upgrading some other random binary, then we have a problem.

       Así que no. Tu regla está COMPLETAMENTE equivocada. Si no puedes
       actualizar el kernel sin actualizar otro binario al azar, entonces
       tenemos un problema. 

 * De `2021-06-05
   <https://lore.kernel.org/all/CAHk-=wiUVqHN76YUwhkjZzwTdjMMJf_zN4+u7vEJjmEGh3recw@mail.gmail.com/>`_::

       THERE ARE NO VALID ARGUMENTS FOR REGRESSIONS.

       NO HAY ARGUMENTOS VÁLIDOS PARA UNA REGRESIÓN. 

       Honestly, security people need to understand that "not working" is not
       a success case of security. It's a failure case.

       Honestamente, la gente se seguridad necesita entender que "no funciona"
       no es una caso de exito sobre seguridad. Es un caso de fallo.

       Yes, "not working" may be secure. But security in that case is *pointless*.

       Si, "no funciona" puede ser seguro. Pero en este caso es totalmente inutil.

 * De `2011-05-06 (1/3)
   <https://lore.kernel.org/all/BANLkTim9YvResB+PwRp7QTK-a5VNg2PvmQ@mail.gmail.com/>`_::

       Binary compatibility is more important.

       La compatibilidad de binarios es más importante. 

       And if binaries don't use the interface to parse the format (or just
       parse it wrongly - see the fairly recent example of adding uuid's to
       /proc/self/mountinfo), then it's a regression.

       Y si los binarios no usan el interface para parsear el formato
       (o justamente lo parsea incorrectamente - como el reciente ejemplo
       de añadir uuid al /proc/self/mountinfo), entonces es una regresión.

       And regressions get reverted, unless there are security issues or
       similar that makes us go "Oh Gods, we really have to break things".

       Y las regresiones se revierten, a menos que haya problemas de 
       seguridad o similares que nos hagan decir "Dios mío, realmente
       tenemos que romper las cosas". 

       I don't understand why this simple logic is so hard for some kernel
       developers to understand. Reality matters. Your personal wishes matter
       NOT AT ALL.

       No entinedo porqué esta simple lógica es tan dificil para algunos
       desarrolladores del kernel. La realidad importa. Sus deseos personales
       NO IMPORTAN NADA. 

       If you made an interface that can be used without parsing the
       interface description, then we're stuck with the interface. Theory
       simply doesn't matter.

       Si se crea un interface que puede usarse sin parsear la 
       descripción del interface, entonces estaḿos atascados en el interface.
       La teoría simplemente no importa. 

       You could help fix the tools, and try to avoid the compatibility
       issues that way. There aren't that many of them.

       Podrias alludar a arreglar las herramientas, e intentar evitar los
       errores de compatibilidad de ese modo. No hay tampoco tantos de esos. 

   De `2011-05-06 (2/3)
   <https://lore.kernel.org/all/BANLkTi=KVXjKR82sqsz4gwjr+E0vtqCmvA@mail.gmail.com/>`_::

       it's clearly NOT an internal tracepoint. By definition. It's being
       used by powertop.

       Esto es claramente NO es un tracepoint enterno. Por definicions. Y está
       siendo usado por powertop.

   De `2011-05-06 (3/3)
   <https://lore.kernel.org/all/BANLkTinazaXRdGovYL7rRVp+j6HbJ7pzhg@mail.gmail.com/>`_::

       We have programs that use that ABI and thus it's a regression if they break.

       Tenemos programas que usan esa ABI y si eso se rompe eso es una regresión.

 * De `2012-07-06 <https://lore.kernel.org/all/CA+55aFwnLJ+0sjx92EGREGTWOx84wwKaraSzpTNJwPVV8edw8g@mail.gmail.com/>`_::

       > Now this got me wondering if Debian _unstable_ actually qualifies as a
       > standard distro userspace.

       > Ahora esto me ha dejado preguntandome si Debian _inestable_ realmente califica
       > como espacio de usuario estandar.

       Oh, if the kernel breaks some standard user space, that counts. Tons
       of people run Debian unstable

       Oh, si el kernel rompe algun espacio de usuario estandar, eso cuenta. 
       Muchisima gente usa Debian inestable.

 * De `2019-09-15
   <https://lore.kernel.org/lkml/CAHk-=wiP4K8DRJWsCo=20hn_6054xBamGKF2kPgUzpB5aMaofA@mail.gmail.com/>`_::

       One _particularly_ last-minute revert is the top-most commit (ignoring
       the version change itself) done just before the release, and while
       it's very annoying, it's perhaps also instructive.

       What's instructive about it is that I reverted a commit that wasn't
       actually buggy. In fact, it was doing exactly what it set out to do,
       and did it very well. In fact it did it _so_ well that the much
       improved IO patterns it caused then ended up revealing a user-visible
       regression due to a real bug in a completely unrelated area.

       The actual details of that regression are not the reason I point that
       revert out as instructive, though. It's more that it's an instructive
       example of what counts as a regression, and what the whole "no
       regressions" kernel rule means. The reverted commit didn't change any
       API's, and it didn't introduce any new bugs. But it ended up exposing
       another problem, and as such caused a kernel upgrade to fail for a
       user. So it got reverted.

       The point here being that we revert based on user-reported _behavior_,
       not based on some "it changes the ABI" or "it caused a bug" concept.
       The problem was really pre-existing, and it just didn't happen to
       trigger before. The better IO patterns introduced by the change just
       happened to expose an old bug, and people had grown to depend on the
       previously benign behavior of that old issue.

       And never fear, we'll re-introduce the fix that improved on the IO
       patterns once we've decided just how to handle the fact that we had a
       bad interaction with an interface that people had then just happened
       to rely on incidental behavior for before. It's just that we'll have
       to hash through how to do that (there are no less than three different
       patches by three different developers being discussed, and there might
       be more coming...). In the meantime, I reverted the thing that exposed
       the problem to users for this release, even if I hope it will be
       re-introduced (perhaps even backported as a stable patch) once we have
       consensus about the issue it exposed.

       Take-away from the whole thing: it's not about whether you change the
       kernel-userspace ABI, or fix a bug, or about whether the old code
       "should never have worked in the first place". It's about whether
       something breaks existing users' workflow.

       Anyway, that was my little aside on the whole regression thing.  Since
       it's that "first rule of kernel programming", I felt it is perhaps
       worth just bringing it up every once in a while

..
   end-of-content
..
   This text is available under GPL-2.0+ or CC-BY-4.0, as stated at the top
   of the file. If you want to distribute this text under CC-BY-4.0 only,
   please use "The Linux kernel developers" for author attribution and link
   this as source:
   https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/plain/Documentation/process/handling-regressions.rst
..
   Note: Only the content of this RST file as found in the Linux kernel sources
   is available under CC-BY-4.0, as versions of this text that were processed
   (for example by the kernel's build system) might contain content taken from
   files which use a more restrictive license.
