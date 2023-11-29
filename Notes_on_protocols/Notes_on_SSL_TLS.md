
#Intro

Most of the internet is based on using the protocols:
 - HTML: Hyper Text Markup Language (web sites)
 - HTTP: Hyper Text Transfer Protocol (retrieve web sites) https://datatracker.ietf.org/doc/html/rfc2616

Sometimes you want to send private information through internet (like passwords). For that we can use SSL/TLS. 

 - HTTPS: this is HTML transferred with HTTP protected by a SSL/TLS tunnel.

### What is SSL and TLS?

SSL stands for Secure Socket Layer, and is the protocol that Netscape proposed in 1994. 

TLS stands for Transport Layer Security, in 1999 the IETF got the maintenance of SSL, and the protocol was renamed as TLS. 

Both terms are diferent versions of the same protocol. Actually there are different versions of SSL and TLS. 

TLS RFC: https://datatracker.ietf.org/doc/html/rfc8446

### How SSL/TLS protects the communications?

- Confidenciality: Data is only accessible to the legit parties, it should be ineligible to not legit parties. (Encryption)
- Integrity: Data cannot be modified between legites parties. It doesn't protect tampering with the data or data modification, but provideds mechanisms of detection in case the comunications has been tampered with. (Hashing)
- Authentication: The legit parties identities are validated. (PKI - Public Key Infratestructure)
