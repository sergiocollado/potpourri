
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

- Anty-replay: repeat a message, to maliciously try to reply the communication. This is avoided, by adding a number that indicates the message sequence. That way, anti-replay is prevented. In TLS, that sequence
number is build in the integrity+authentification mechanism.

- Non-repudiation: Repudiate is to refuse a message. Non-repudiation is a mechanism that avoids a receiver to repudiate a message. Non-repudiation is also achieved by means of integrity and authentification.

### SSL/TLS main components

- Client: initiates the SSL/TLS handshake. The client is only optionally authenticated with a certificate, it is not mandatory and the client authentification with certificates is done rarely.
- Server: receives the SSL/TLS handshake. The server is always authenticated with a certificate. 
- Certificate Authority (CA): CA is the entity that issues certificates, and it is trusted by the client and the server. If the client trust the CA, and the CA provides a certificate to the server, then the client trust the server. Five organization certificate most of the internet: IdentTrust (owns Let's Encrypt), DigiCert, Sectigo (Comodo), GoDaddy, GlobalSign

For having server and client both authenticated with a certificate, mutual TLS or mTLS is used.

reference: https://w3techs.com/technologies/overview/ssl_certificate



