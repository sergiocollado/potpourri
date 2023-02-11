.. SPDX-License-Identifier: GPL-2.0

.. _deprecated:

=====================================================================
Deprecated Interfaces, Language Features, Attributes, and Conventions
=====================================================================

============================================================================
Interfaces obsoletos, características del lenguaje, atributos y convenciones
============================================================================

In a perfect world, it would be possible to convert all instances of
some deprecated API into the new API and entirely remove the old API in
a single development cycle. However, due to the size of the kernel, the
maintainership hierarchy, and timing, it's not always feasible to do these
kinds of conversions at once. This means that new instances may sneak into
the kernel while old ones are being removed, only making the amount of
work to remove the API grow. In order to educate developers about what
has been deprecated and why, this list has been created as a place to
point when uses of deprecated things are proposed for inclusion in the
kernel.

En un mundo perfecto, sería posible convertir todas las instacias de
alguna API obsoleta en una nueva API y quitar la API anterior en un
único ciclo de desarrollo. Desafortunadamente debido al tamaño del kernel,
la jerarquia de mantenimiento, y el tiempo, no siempre es posible hacer
estos cambios de una única vez. Esto significa que las nuevas
instancias han de ir creandose en el kernel, mientras que las antiguas
se quitan, haciendo que la cantidad de trabajo para limpiar las APIs
crezca. Para informar a los desarrolladores sobre qué ha sido declarado
obsoleto y porqué, ha sido creada esta lista como un lugar donde se
indicar cuando los usos obsoletos son propuestos para incluir en el
kernel.

__deprecated
------------
While this attribute does visually mark an interface as deprecated,
it `does not produce warnings during builds any more
<https://git.kernel.org/linus/771c035372a036f83353eef46dbb829780330234>`_
because one of the standing goals of the kernel is to build without
warnings and no one was actually doing anything to remove these deprecated
interfaces. While using `__deprecated` is nice to note an old API in
a header file, it isn't the full solution. Such interfaces must either
be fully removed from the kernel, or added to this file to discourage
others from using them in the future.

__deprecated
------------
Mientras que este atributo señala visualmete que un interface ha sido
declarado obsoleto, este `no produce más avisos durante las compilaciones
<https://git.kernel.org/linus/771c035372a036f83353eef46dbb829780330234>`_
porque uno de los objetivos del kernel es que compile sin avisos, y
nadie ha hecho nada para quitar estos interfaces obsoletos. Mientras
que usar `__deprecated` es sencillo para anotar una API obsoleta en
un archivo de cabecera, no es la solución completa. Dichos interfaces
deben o bien ser quitados por completo, o añadidos a este archivo para
desanimar a otros a usarla en el futuro.


BUG() and BUG_ON()
------------------
Use WARN() and WARN_ON() instead, and handle the "impossible"
error condition as gracefully as possible. While the BUG()-family
of APIs were originally designed to act as an "impossible situation"
assert and to kill a kernel thread "safely", they turn out to just be
too risky. (e.g. "In what order do locks need to be released? Have
various states been restored?") Very commonly, using BUG() will
destabilize a system or entirely break it, which makes it impossible
to debug or even get viable crash reports. Linus has `very strong
<https://lore.kernel.org/lkml/CA+55aFy6jNLsywVYdGp83AMrXBo_P-pkjkphPGrO=82SPKCpLQ@mail.gmail.com/>`_
feelings `about this
<https://lore.kernel.org/lkml/CAHk-=whDHsbK3HTOpTF=ue_o04onRwTEaK_ZoJp_fjbqq4+=Jw@mail.gmail.com/>`_.


BUG() y BUG_ON()
----------------
Usar WARN() y WARN_ON() en su lugar, y gestionar las condiciones de
error "imposibles" tan elegantemente como se pueda. Mientras que
la familia de funciones BUG() fueron originalmente diseñadas
para actuar como una "situación imposible", confirmar y disponer de
un hilo del kernel de forma "segura", estas funciones han resultado
ser demasiado arriesgadas. (e.g. "¿en qué orden se necesitan liberar
los locks? ¿Se han restaruado sus estados?). La popular función
BUG() desestabilizará el sistema o lo romperá totalmente, lo cual
hace imposible depurarlo o incluso generar reportes de crash.
Linus tiene una `opinión muy fuerte
<https://lore.kernel.org/lkml/CA+55aFy6jNLsywVYdGp83AMrXBo_P-pkjkphPGrO=82SPKCpLQ@mail.gmail.com/>`_
y sentimientos `sobre esto
<https://lore.kernel.org/lkml/CAHk-=whDHsbK3HTOpTF=ue_o04onRwTEaK_ZoJp_fjbqq4+=Jw@mail.gmail.com/>`_.


Note that the WARN()-family should only be used for "expected to
be unreachable" situations. If you want to warn about "reachable
but undesirable" situations, please use the pr_warn()-family of
functions. System owners may have set the *panic_on_warn* sysctl,
to make sure their systems do not continue running in the face of
"unreachable" conditions. (For example, see commits like `this one
<https://git.kernel.org/linus/d4689846881d160a4d12a514e991a740bcb5d65a>`_.)


Nótese que la familia de funciones WARN() únicamente debería ser usada
en situaciónes que se "esperan no sen alcanzables". Si se quiere
avisar sobre situaciones "alcanzables pero no deseadas", úsese la
familia de funciones pr_warn(). Los responsables del sistema pueden
haber definido *panic_on_warn* sysctl para asegurarse que sus
sistemas no continuan ejecutandose en presencia del condiciones
"no alcanzables". (Por ejemplo, vease commits como `este
<https://git.kernel.org/linus/d4689846881d160a4d12a514e991a740bcb5d65a>`_.)

open-coded arithmetic in allocator arguments
--------------------------------------------
Dynamic size calculations (especially multiplication) should not be
performed in memory allocator (or similar) function arguments due to the
risk of them overflowing. This could lead to values wrapping around and a
smaller allocation being made than the caller was expecting. Using those
allocations could lead to linear overflows of heap memory and other
misbehaviors. (One exception to this is literal values where the compiler
can warn if they might overflow. However, the preferred way in these
cases is to refactor the code as suggested below to avoid the open-coded
arithmetic.)

operaciones aritméticas en los argumentos de reserva de memoria
---------------------------------------------------------------
Los cálculos dinámicos de tamaño (especialmente multiplicaciones) no
deberian realizarse en los argumentos de reserva de memoria (o
similares) debido al riesgo de desbordamiento. Esto puede llevar
a valores rotando y que se realicen reservas de memoria menores
que las que se esperaban. El uso de esas reservas puede llevar a
desbordamientos en el 'heap' de memoria y otros malfuncionamientos.
(Una exepción a esto son los valores literales donde el compilador
si puede avisar si estos puede desbordarse. De todos modos, el método
recomendado en estos caso es reescribir el código como se sugiere
a continuación para evirar las operaciónes aritméticas en la
reserva de memoria.)



For example, do not use ``count * size`` as an argument, as in::

	foo = kmalloc(count * size, GFP_KERNEL);

Instead, the 2-factor form of the allocator should be used::

	foo = kmalloc_array(count, size, GFP_KERNEL);
	
Por ejemplo, no usar `count * size`` como argumento, como en::

	foo = kmalloc(count * size, GFP_KERNEL);

En vez de eso, usar la reserva con dos argumentos::

        foo = kmalloc_array(count, size, GFP_KERNEL);
	

Specifically, kmalloc() can be replaced with kmalloc_array(), and
kzalloc() can be replaced with kcalloc().

Especificamente, kmalloc() puede ser sustituido con kmalloc_array(),
kzalloc() puede ser sustituido con kcalloc().

If no 2-factor form is available, the saturate-on-overflow helpers should
be used::

	bar = vmalloc(array_size(count, size));

Si no existen funciones con dos argumentos, usar las funciones que se
saturan, en caso de desbordamiento :

        bar = vmalloc(array_size(count, size));


Another common case to avoid is calculating the size of a structure with
a trailing array of others structures, as in::

	header = kzalloc(sizeof(*header) + count * sizeof(*header->item),
			 GFP_KERNEL);

Otro cáso común a evitar es calcular el tamaño de una estructura com
la suma de otras estructuras, como en::

	header = kzalloc(sizeof(*header) + count * sizeof(*header->item),
			 GFP_KERNEL);
       
Instead, use the helper::

	header = kzalloc(struct_size(header, item, count), GFP_KERNEL);
	
En vez de eso usar::

	header = kzalloc(struct_size(header, item, count), GFP_KERNEL);

.. note:: If you are using struct_size() on a structure containing a zero-length
        or a one-element array as a trailing array member, please refactor such
        array usage and switch to a `flexible array member
        <#zero-length-and-one-element-arrays>`_ instead.

.. nota:: Si se usa struct_size() en una estructura que contiene un elemento 
        de longitud cero o un array de un único elemento como un array miembro,
        por favor reescrivir ese uso y cambiar a un `miembro array flexible 
        <#zero-length-and-one-element-arrays>`_ 

For other calculations, please compose the use of the size_mul(),
size_add(), and size_sub() helpers. For example, in the case of::

	foo = krealloc(current_size + chunk_size * (count - 3), GFP_KERNEL);
	
Para otros cálculos, por favor use las funciones de ayuda: size_mul(),
size_add(), and size_sub(). Por ejemplo, en el caso de::

	foo = krealloc(current_size + chunk_size * (count - 3), GFP_KERNEL);

Instead, use the helpers::

	foo = krealloc(size_add(current_size,
				size_mul(chunk_size,
					 size_sub(count, 3))), GFP_KERNEL);

Re-escribase, como::

	foo = krealloc(size_add(current_size,
				size_mul(chunk_size,
					 size_sub(count, 3))), GFP_KERNEL);					 
					

For more details, also see array3_size() and flex_array_size(),
as well as the related check_mul_overflow(), check_add_overflow(),
check_sub_overflow(), and check_shl_overflow() family of functions.

Para más detales, mire también array3_size() y flex_array_size(),
com también la familia de funciones relacionadas check_mul_overflow(), 
check_add_overflow(), check_sub_overflow(), y check_shl_overflow(). 


simple_strtol(), simple_strtoll(), simple_strtoul(), simple_strtoull()
----------------------------------------------------------------------
The simple_strtol(), simple_strtoll(),
simple_strtoul(), and simple_strtoull() functions
explicitly ignore overflows, which may lead to unexpected results
in callers. The respective kstrtol(), kstrtoll(),
kstrtoul(), and kstrtoull() functions tend to be the
correct replacements, though note that those require the string to be
NUL or newline terminated.


simple_strtol(), simple_strtoll(), simple_strtoul(), simple_strtoull()
----------------------------------------------------------------------
Las funciones: simple_strtol(), simple_strtoll(),
simple_strtoul(), y simple_strtoull() explícitamente ignoran
los desbordamientos, lo que puede llevar a resultados inesperados
por las funciones que las llaman. Las funciones respectivas
kstrtol(), kstrtoll(), kstrtoul(), and kstrtoull() tienden a
ser reemplazos correctos, aunque notese que necesitarán que la
cadena de caracters termine en NUL o en el caracter de línea nueva.


strcpy()
--------
strcpy() performs no bounds checking on the destination buffer. This
could result in linear overflows beyond the end of the buffer, leading to
all kinds of misbehaviors. While `CONFIG_FORTIFY_SOURCE=y` and various
compiler flags help reduce the risk of using this function, there is
no good reason to add new uses of this function. The safe replacement
is strscpy(), though care must be given to any cases where the return
value of strcpy() was used, since strscpy() does not return a pointer to
the destination, but rather a count of non-NUL bytes copied (or negative
errno when it truncates).

strcpy()
--------
strcpy() no realiza verificaciones de los límites del buffer de
destino. Esto puede resultar en desbordamientos lineals más allá
del fin del buffer, causando todo tipo de errores. Mientras
`CONFIG_FORTIFY_SOURCE=y` otras varias opciones de compilación
reducen el reisgo de usar esta función, no hay ninguna buena
razón para añadir nuevos usos de esta. El remplazo seguro es la
función strscpy(), aunque se ha de tener cuidado con cualquier
caso en el el valor retornado por strcpy() sea usado, ya que
strscpy() no devuelve un puntero a el destino, sino el número de
caracteres no nulos compiados (o el valor negativo de errno
cuando se trunca la cadena de caracteres).


strncpy() on NUL-terminated strings
-----------------------------------
Use of strncpy() does not guarantee that the destination buffer will
be NUL terminated. This can lead to various linear read overflows and
other misbehavior due to the missing termination. It also NUL-pads
the destination buffer if the source contents are shorter than the
destination buffer size, which may be a needless performance penalty
for callers using only NUL-terminated strings.


strncpy() en cadenas de caracteres terminadas en NUL
----------------------------------------------------
El uso de strncpy() no garantiza que el buffer de destino esté
terminado en NUL. Esto puede causar varios errores de desbordamiento
en lectura y otros típos de malfuncionamienos debido a que falta
la terminación en NUL. Esta función también termina la cadena de
caracteres en NUL en el buffer de destino si la cadena de origen
es más corta que el buffer de destino, lo cual puede ser una 
penalización innecesaria para funciones usen esta función con 
cadenas de caracters que si están terminadas en NUL.


When the destination is required to be NUL-terminated, the replacement is
strscpy(), though care must be given to any cases where the return value
of strncpy() was used, since strscpy() does not return a pointer to the
destination, but rather a count of non-NUL bytes copied (or negative
errno when it truncates). Any cases still needing NUL-padding should
instead use strscpy_pad().

Cuando se necesita que la cadena de destino sea terminada en NUL, 
el mejor reemplazo es usar la función strscpy(), aunque se ha de tener
cuidado en los casos en los que el valor de strncpy() fuera usado, ya que 
strscpy() no devuelve un puntero al destino, sino el número de 
caracteres no nulos copiados (o el valor negativo de errno 
cuando se trunca la cadena de caracteres). Cualquier caso restante
que necesitase todavia ser terminado en el caracter nulo, deberia
usar strscpy_pad().


If a caller is using non-NUL-terminated strings, strtomem() should be
used, and the destinations should be marked with the `__nonstring
<https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html>`_
attribute to avoid future compiler warnings. For cases still needing
NUL-padding, strtomem_pad() can be used.


Si una funcón usa cadenas de caracteres que no necesitan terminar en
NUL, debería usarse strtomem(), y el destino deberia señalarse con 
el atributo `__nonstring
<https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html>`_
para evitar avisos futuros en el compilador. Para casos que todavia
necesiten cadenas de caracteres que se rellenen al final con el
caracterer NUL, usar strtomem_pad().


strlcpy()
---------
strlcpy() reads the entire source buffer first (since the return value
is meant to match that of strlen()). This read may exceed the destination
size limit. This is both inefficient and can lead to linear read overflows
if a source string is not NUL-terminated. The safe replacement is strscpy(),
though care must be given to any cases where the return value of strlcpy()
is used, since strscpy() will return negative errno values when it truncates.

strlcpy()
---------
strlcpy() primero lee por completo el buffer de origen (ya que el
valor devuelto intenta ser el mismo que el de strlen()). Esta lectura
puede sobrepasar el límite de tamaño del destino. Esto ineficiente y 
puede causar desbordamientos de lectura si la cadena de origen no esta
terminada en el caracer NUL. El reemplazo seguro de esta función es
strscpy(), pero se ha de tener cuidado que en los casos en lso que se
usase el valor devuelto de strlcpy(), ya que strscpy() devolverá
valores negativos de erno cuando se produzcan truncados. 


%p format specifier
-------------------
Traditionally, using "%p" in format strings would lead to regular address
exposure flaws in dmesg, proc, sysfs, etc. Instead of leaving these to
be exploitable, all "%p" uses in the kernel are being printed as a hashed
value, rendering them unusable for addressing. New uses of "%p" should not
be added to the kernel. For text addresses, using "%pS" is likely better,
as it produces the more useful symbol name instead. For nearly everything
else, just do not add "%p" at all.


Especificación de formato %p
----------------------------
Tradicionalmente,el uso the "%p" en el formato de cadenas de caracteres
resultaria en exponer esas direcciónes en dmesg, proc, sysfs, etc. En vez
de dejar que sean una vulnerabilidad, todos los "%p" que se usan en el
kernel se imprimen como un hash, haciendolos efectivamente inutilizables
para usarlos como direcciónes de memoria. Nuevos usos de "%p" no deberian
ser añadididos al kernel. Para textos de direcciones, usar "%pS" es 
mejor, ya que resulta en el nombre del symbolo. Para prácticamente el 
resto de casos, mejor no usar "%p" en absoluto.


Paraphrasing Linus's current `guidance <https://lore.kernel.org/lkml/CA+55aFwQEd_d40g4mUCSsVRZzrFPUJt74vc6PPpb675hYNXcKw@mail.gmail.com/>`_:

Parafraseando las actuales `direcciones de Linus <https://lore.kernel.org/lkml/CA+55aFwQEd_d40g4mUCSsVRZzrFPUJt74vc6PPpb675hYNXcKw@mail.gmail.com/>`_:

- If the hashed "%p" value is pointless, ask yourself whether the pointer
  itself is important. Maybe it should be removed entirely?
- If you really think the true pointer value is important, why is some
  system state or user privilege level considered "special"? If you think
  you can justify it (in comments and commit log) well enough to stand
  up to Linus's scrutiny, maybe you can use "%px", along with making sure
  you have sensible permissions.
  
- Si el valor hasheado "%p" no tienen ningúna finalidad, preguntarse si el
  puntero es realmente importante. ¿Quizás se podria quitar totalmente?
- Si realmente se piensa que el valor del puntero es importante, ¿porqué
  algún estado del sistema o nivel de privilegio de usuario es considerado
  "especial"? Si piensa que puede justificarse (en comentarios y mensajes
  del commit), de forma suficientoe como para pasar el escrutinio de Linux, 
  quizás pueda usar el "%p", a la vez que se asegura que tiene los permisos
  correspondientes.

If you are debugging something where "%p" hashing is causing problems,
you can temporarily boot with the debug flag "`no_hash_pointers
<https://git.kernel.org/linus/5ead723a20e0447bc7db33dc3070b420e5f80aa6>`_".

Si está depurando algo donde el "%p" hasheado está causando problemas,
se puede arrancar temporalmente con la opción de depuración "`no_hash_pointers
<https://git.kernel.org/linus/5ead723a20e0447bc7db33dc3070b420e5f80aa6>`_".

Variable Length Arrays (VLAs)
-----------------------------
Using stack VLAs produces much worse machine code than statically
sized stack arrays. While these non-trivial `performance issues
<https://git.kernel.org/linus/02361bc77888>`_ are reason enough to
eliminate VLAs, they are also a security risk. Dynamic growth of a stack
array may exceed the remaining memory in the stack segment. This could
lead to a crash, possible overwriting sensitive contents at the end of the
stack (when built without `CONFIG_THREAD_INFO_IN_TASK=y`), or overwriting
memory adjacent to the stack (when built without `CONFIG_VMAP_STACK=y`)

Arrays de longitud variable (VLAs)
----------------------------------
Usando VLA en la stack produce un código mucho peor que los arrays
de tamaño estático. Mientras que estos errores no triviales de `rendimiento
<https://git.kernel.org/linus/02361bc77888>`_  son razón suficiente
para no usar VLAs, esto además son un riesgo de seguridad. El crecimiento
dinámico del array en la pila, puede excedder la memoria restante en 
el segmento de la pila. Esto podria llevara a un cras, posible sobre-escritura
de contenido sensible al final de la pila (cuando se construye sin 
`CONFIG_THREAD_INFO_IN_TASK=y`), o sobre-escritura de la memoria adjacente
a la pila (when se construye sin `CONFIG_VMAP_STACK=y`).



Implicit switch case fall-through
---------------------------------
The C language allows switch cases to fall through to the next case
when a "break" statement is missing at the end of a case. This, however,
introduces ambiguity in the code, as it's not always clear if the missing
break is intentional or a bug. For example, it's not obvious just from
looking at the code if `STATE_ONE` is intentionally designed to fall
through into `STATE_TWO`::

	switch (value) {
	case STATE_ONE:
		do_something();
	case STATE_TWO:
		do_other();
		break;
	default:
		WARN("unknown state");
	}
	
Switch case fall-through implícito
---------------------------------	
El lenguaje C permite a las sentencias 'switch' saltar de un caso
al siguete caso cuando la sentencia de ruptura "break" no aparece
al final del caso. Esto, intoduce ambiguedad en el código, ya que 
no siempre está claro si el 'break' que falta es intencionado o 
un olvido. Por ejemplo, no es obvio solamente mirando al código si 
`STATE_ONE` está escrito para intecionadamente saltar en `STATE_TWO`::
	
	switch (value) {
	case STATE_ONE:
		do_something();
	case STATE_TWO:
		do_other();
		break;
	default:
		WARN("unknown state");
	}
		
	

As there have been a long list of flaws `due to missing "break" statements
<https://cwe.mitre.org/data/definitions/484.html>`_, we no longer allow
implicit fall-through. In order to identify intentional fall-through
cases, we have adopted a pseudo-keyword macro "fallthrough" which
expands to gcc's extension `__attribute__((__fallthrough__))
<https://gcc.gnu.org/onlinedocs/gcc/Statement-Attributes.html>`_.
(When the C17/C18  `[[fallthrough]]` syntax is more commonly supported by
C compilers, static analyzers, and IDEs, we can switch to using that syntax
for the macro pseudo-keyword.)

Ya que ha habido una larga lista de defectos `debidos a declaraciones de "break"
que faltan <https://cwe.mitre.org/data/definitions/484.html>`_, no se 
permiten 'fall-through' implícitos. Para identificar 'fall-through' 
intencionados, se ha adoptado la pseudo-palabra-clave macro "falltrhrough",
que expande las extensiones de gcc `__attribute__((__fallthrough__))
<https://gcc.gnu.org/onlinedocs/gcc/Statement-Attributes.html>`_. 
(Cuando la sintaxis de C17/c18 `[[fallthrough]]` sea más comunmente 
soportadas por los compiladores de C, analizadores estáticos, e IDEs, 
se puede cambiar a usar esa sintaxis para esa pseudo-palabra-clave.
	

All switch/case blocks must end in one of:

* break;
* fallthrough;
* continue;
* goto <label>;
* return [expression];

Todos los bloques switch/case deben acabar en uno de:

* break;
* fallthrough;
* continue;
* goto <label>;
* return [expression];


Zero-length and one-element arrays
----------------------------------
There is a regular need in the kernel to provide a way to declare having
a dynamically sized set of trailing elements in a structure. Kernel code
should always use `"flexible array members" <https://en.wikipedia.org/wiki/Flexible_array_member>`_
for these cases. The older style of one-element or zero-length arrays should
no longer be used.


Arrays de longitud cero y un elemento
------------------------------------

Hay una necesidad habitual en el kernel de proveer una forma para declarar
un grupo de elementos cosecutivos de tamaño dinámico en una estrucutra.
El código del kernel deberia usar siempre `"miembros array flexible" <https://en.wikipedia.org/wiki/Flexible_array_member>`_
en estos casos. El estilo anterior de arrays de un elemento o de longitud 
cero, no deben usarse más. 

In older C code, dynamically sized trailing elements were done by specifying
a one-element array at the end of a structure::

        struct something {
                size_t count;
                struct foo items[1];
        };

En código C más antiguo, elementos seguidos de tamaño dinámico eran creados
especificando una array de un único elemento al final de una estructura::

        struct something {
                size_t count;
                struct foo items[1];
        };


This led to fragile size calculations via sizeof() (which would need to
remove the size of the single trailing element to get a correct size of
the "header"). A `GNU C extension <https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html>`_
was introduced to allow for zero-length arrays, to avoid these kinds of
size problems::

        struct something {
                size_t count;
                struct foo items[0];
        };
        
Esto llevó a resultados incorrectos en llos cálculos de tamaño mediate
sizeof() (el cual hubiera necesitado eliminar el tamaño del último elemento
para tener un tamaño correcto de la "cabecera"). Una  `extensión de GNU C
<https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html>`_ se empezó a usar
para permitir los arrays de longitud cero, para evitar estos tipos de problemas
de tamaño::

        struct something {
                size_t count;
                struct foo items[0];
        };

But this led to other problems, and didn't solve some problems shared by
both styles, like not being able to detect when such an array is accidentally
being used _not_ at the end of a structure (which could happen directly, or
when such a struct was in unions, structs of structs, etc).

Pero esto llevó a otros problemas, y no solucionó algunos otros problemas
compartidos por ambos estios, como no ser capaz de detectar cuando ese array
es accidentamente usado _no_ al final de la estructura (lo que podia pasar 
directamente, o cuando dicha estrucutura era usadoa en uniones, estructuras
de esytructuras, etc).


C99 introduced "flexible array members", which lacks a numeric size for
the array declaration entirely::

        struct something {
                size_t count;
                struct foo items[];
        };
        
C99 introdujo "los arrays miembros flexibles", los cuales carecen de un 
tamaño numerico en su declaración del array::

        struct something {
                size_t count;
                struct foo items[];
        };
        

This is the way the kernel expects dynamically sized trailing elements
to be declared. It allows the compiler to generate errors when the
flexible array does not occur last in the structure, which helps to prevent
some kind of `undefined behavior
<https://git.kernel.org/linus/76497732932f15e7323dc805e8ea8dc11bb587cf>`_
bugs from being inadvertently introduced to the codebase. It also allows
the compiler to correctly analyze array sizes (via sizeof(),
`CONFIG_FORTIFY_SOURCE`, and `CONFIG_UBSAN_BOUNDS`). For instance,
there is no mechanism that warns us that the following application of the
sizeof() operator to a zero-length array always results in zero::

        struct something {
                size_t count;
                struct foo items[0];
        };

        struct something *instance;

        instance = kmalloc(struct_size(instance, items, count), GFP_KERNEL);
        instance->count = count;

        size = sizeof(instance->items) * instance->count;
        memcpy(instance->items, source, size);
        

Este es la forma en la que el kernel espera que se declaren los elementos de 
tamaño dinámico concatenados. Esto permite al compilador generar errores, cuando
el array flexible no es declarado en el último lugar de la estructura, lo que
ayuda a prevenir errores en la código del tipo `comportamiento indefinido
<https://git.kernel.org/linus/76497732932f15e7323dc805e8ea8dc11bb587cf>`_. Esto
también permite al compilador analizar correctamente los tamaños de los arrays 
(via sizeof(), `CONFIG_FORTIFY_SOURCE`, y `CONFIG_UBSAN_BOUNDS`). Por ejemplo,
si no hay un mecansiimo que avise que el siguiente uso de sizeof() en un array
de longitud zero, siempre resulta en cero::

        struct something {
                size_t count;
                struct foo items[0];
        };

        struct something *instance;

        instance = kmalloc(struct_size(instance, items, count), GFP_KERNEL);
        instance->count = count;

        size = sizeof(instance->items) * instance->count;
        memcpy(instance->items, source, size);  
               

At the last line of code above, ``zero`` turns out to be ``zero``, when one might
have thought it represents the total size in bytes of the dynamic memory recently
allocated for the trailing array ``items``. Here are a couple examples of this
issue: `link 1
<https://git.kernel.org/linus/f2cd32a443da694ac4e28fbf4ac6f9d5cc63a539>`_,
`link 2
<https://git.kernel.org/linus/ab91c2a89f86be2898cee208d492816ec238b2cf>`_.
Instead, `flexible array members have incomplete type, and so the sizeof()
operator may not be applied <https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html>`_,
so any misuse of such operators will be immediately noticed at build time.


En la última línea del código anterior, ``zero`` vale ``cero``, cuando uno 
podría esperar que resepresetna el tamaño total en bytes de la memoria dinámica
reservada para el array consecutivo ``items``. Aquí hay un pare de ejemplos más
sobre este tema:  `link 1
<https://git.kernel.org/linus/f2cd32a443da694ac4e28fbf4ac6f9d5cc63a539>`_,
`link 2
<https://git.kernel.org/linus/ab91c2a89f86be2898cee208d492816ec238b2cf>`_.
En vez, `array miembros flexibles tienen un type incompleto, y no se ha de
aplicar el operador sizeof()<https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html>`_,
asi cual quier mal uso de dichos operadores será detectado inmediatamente en el
momento de compilación. 


With respect to one-element arrays, one has to be acutely aware that `such arrays
occupy at least as much space as a single object of the type
<https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html>`_,
hence they contribute to the size of the enclosing structure. This is prone
to error every time people want to calculate the total size of dynamic memory
to allocate for a structure containing an array of this kind as a member::

        struct something {
                size_t count;
                struct foo items[1];
        };

        struct something *instance;

        instance = kmalloc(struct_size(instance, items, count - 1), GFP_KERNEL);
        instance->count = count;

        size = sizeof(instance->items) * instance->count;
        memcpy(instance->items, source, size);
        
        
Con respecto a los arrays de un único elemento, se ha de ser consciente de que
`dichos arrays ocupan al mennos tanto espacio como un único objeto del tipo 
https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html>`_, de ahi que estos 
contribuyan al tamaño de la estructura que los contiene. Esto es proclive a 
errores cada vez que se quiere calcular el tamaño total de la memoria dinámica
para reserbar una estructura que contenga un array de este tipo como su miembro::

        struct something {
                size_t count;
                struct foo items[1];
        };

        struct something *instance;

        instance = kmalloc(struct_size(instance, items, count - 1), GFP_KERNEL);
        instance->count = count;

        size = sizeof(instance->items) * instance->count;
        memcpy(instance->items, source, size);



In the example above, we had to remember to calculate ``count - 1`` when using
the struct_size() helper, otherwise we would have --unintentionally-- allocated
memory for one too many ``items`` objects. The cleanest and least error-prone way
to implement this is through the use of a `flexible array member`, together with
struct_size() and flex_array_size() helpers::

        struct something {
                size_t count;
                struct foo items[];
        };

        struct something *instance;

        instance = kmalloc(struct_size(instance, items, count), GFP_KERNEL);
        instance->count = count;

        memcpy(instance->items, source, flex_array_size(instance, items, instance->count));


En el ejemplo anterior, hemos de recordar calcular ``count - 1``, cuando se usa
la función de ayuda struct_size(), de otro modo estariamos 
--desintencionadamente--reservando memoria para un  ``items`` de más. La forma
más clara y menos proclive a erroes es implementar esto mediante el uso de
`array miembro flexible`, junto con las funciones de ayuda: struct_size() y
flex_array_size()::

        struct something {
                size_t count;
                struct foo items[];
        };

        struct something *instance;

        instance = kmalloc(struct_size(instance, items, count), GFP_KERNEL);
        instance->count = count;

        memcpy(instance->items, source, flex_array_size(instance, items, instance->count));
