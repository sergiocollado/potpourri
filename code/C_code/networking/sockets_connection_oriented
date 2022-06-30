  TCP -connection oriented communication
  +------------------------------------+


  SERVER                      CLIENT


+----------+
| socket() |
+----+-----+
     |
+----v-----+
| bind()   |
+----+-----+
     |
+----v-----+
| listen() |                
+----+-----+
     |
+----v-----+               +----------+
| accept() |               | socket() |
+----+-----+               +----+-----+
     |        CONECTION         |
     v        NEGOCIATION  +----v-----+
 -blocks-  <------------>  | connect()|
                           +----+-----+
     +                          |
+----v----+   DATA         +----v-----+
| read()  | <--------------+ write()  |
+----+----+                +----+-----+
     |                          |
+----v----+       DATA     +----v-----+
| write() +------------->  | read()   |
+----+----+                +----+-----+
     |                          |
+----v----+                +----v-----+
| read()  |                | close()  |
+----+----+                +----------+
     |
+----v----+
| close() |
+---------+


//ref: https://pubs.opengroup.org/onlinepubs/009695399/functions/socket.html
//https://www.gnu.org/software/libc/manual/html_node/Sockets.html
