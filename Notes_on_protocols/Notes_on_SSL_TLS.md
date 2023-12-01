
# Intro

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

Usually when these 3 properties appear, we comment on: Anti-Replay and Non-repudiation

- Anti-replay: repeat a message, to maliciously try to reply the communication. This is avoided, by adding a number that indicates the message sequence. That way, anti-replay is prevented. In TLS, that sequence
number is build in the integrity+authentification mechanism.

- Non-repudiation: Repudiate is to refuse a message. Non-repudiation is a mechanism that avoids a receiver to repudiate a message. Non-repudiation is also achieved by means of integrity and authentification.

### SSL/TLS main components

- Client: initiates the SSL/TLS handshake. The client is only optionally authenticated with a certificate, it is not mandatory and the client authentification with certificates is done rarely.
- Server: receives the SSL/TLS handshake. The server is always authenticated with a certificate. 
- Certificate Authority (CA): CA is the entity that issues certificates, and it is trusted by the client and the server. If the client trust the CA, and the CA provides a certificate to the server, then the client trust the server. Five organization certificate most of the internet: IdentTrust (owns Let's Encrypt), DigiCert, Sectigo (Comodo), GoDaddy, GlobalSign

For having server and client both authenticated with a certificate, mutual TLS or mTLS is used.

reference: https://w3techs.com/technologies/overview/ssl_certificate

### SSL/TLS versions

There are many versions of SSL/TLS. As tech and attacks have evolved the protocols have evolved also. 

Everyone uses TLS, but is common to refere to it to SSL. 

SSL v3.0 was deprecated because of the poodle attack: https://www.acunetix.com/blog/web-security-zone/what-is-poodle-attack/

 - SSL v1.0 developed by Netscape in 1994, but never was publicy released, and was quite full of flaws
 - SSL v2.0 developed by Netscape in 1995, total redesign, but was also full of flaws.
 - SSL v3.0 developed by Netscape in 1996, and it was a complete redesign, and was secure. It introduced the concept of certificate chains. Use of RSA and Diffie-Hellman key exchanges protocols. RFC 6101: https://datatracker.ietf.org/doc/html/rfc6101

Netscape give ownership of the protocol to the IETF (Internet Engineering Task Force)

 - TLS v1.0 . In 1999, introduces HMAC, and requires support for extra key exchanges. Main attack "Beast attack"
   - TLS v.1.1 in 2006, rfc 4346
 - TLS v2.0 . In 2008, rfc 5246, added AEAD ciphers. (Authenticated Encryption with Associated Data).
 - TLS v3.0 . In 2018, rfc 8446 (https://datatracker.ietf.org/doc/html/rfc8446). It has big changes with respect to the previous versions. 

## Cryptography 

- reference: https://crypto.stanford.edu/~dabo/courses/OnlineCrypto/

### Hashing 

- reference: https://en.wikipedia.org/wiki/Cryptographic_hash_function

Hashing is a mathematical algorithm that takes as an input a message of arbitrary length and produces as an output (digest) a "fingerprint" of the original message. 

The desired properties of hashing are: 
- infeaseable to produce a given digest
- imposible to extract the original message
- slight changes on the input produce drastic differences on the output
- the resulting digest is fixed size

Collisions: A collision is when two messages have the same hash digest. Unfortunatelly those are unavoidable as a byproduct of the fixed width. 
  
The most common hashing algorithms are: 
- md5 (128 bits)
- SHA/SHA1 (160 bits)
- SHA2 family
  

