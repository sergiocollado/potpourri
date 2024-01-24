# Notes on SSL/TLS

- Intro: https://youtu.be/VcV4T8cL3xw

## Fundamentals

Most of the internet is based on using the protocols:
 - HTML: Hyper Text Markup Language (web sites)
 - HTTP: Hyper Text Transfer Protocol (retrieve web sites) https://datatracker.ietf.org/doc/html/rfc2616

Sometimes you want to send private information through internet (like passwords). For that we can use SSL/TLS. 

 - HTTPS: this is HTML transferred with HTTP protected by a SSL/TLS tunnel.

### What is SSL and TLS?

- reference: https://youtu.be/aCDgFH1i2B0

SSL stands for Secure Socket Layer, and is the protocol that Netscape proposed in 1994. 

TLS stands for Transport Layer Security, in 1999 the IETF got the maintenance of SSL, and the protocol was renamed as TLS. 

Both terms are diferent versions of the same protocol. Actually there are different versions of SSL and TLS. 

TLS RFC: https://datatracker.ietf.org/doc/html/rfc8446

### How SSL/TLS protects the communications?

- reference: https://youtu.be/WfR3ZAP96mQ?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY
- reference: https://youtu.be/VcV4T8cL3xw

- Confidenciality: Data is only accessible to the legit parties, it should be ineligible to not legit parties. (Encryption)
- Integrity: Data cannot be modified between legites parties. It doesn't protect tampering with the data or data modification, but provideds mechanisms of detection in case the comunications has been tampered with. (Hashing)
- Authentication: The legit parties identities are validated. (PKI - Public Key Infratestructure)

Usually when these 3 properties appear, we comment on: Anti-Replay and Non-repudiation

- reference: https://youtu.be/26lZ-akbfrQ?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY

- Anti-replay: repeat a message, to maliciously try to reply the communication. This is avoided, by adding a number that indicates the message sequence. That way, anti-replay is prevented. In TLS, that sequence
number is build in the integrity+authentification mechanism.

- Non-repudiation: Repudiate is to refuse a message. Non-repudiation is a mechanism that avoids a receiver to repudiate a message. Non-repudiation is also achieved by means of integrity and authentification.

### SSL/TLS main components

- reference: https://youtu.be/C7Y4UEBJ0Og?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY
- reference: https://www.youtube.com/watch?v=Jefr7wFLu3M&list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY&index=12

- Client: initiates the SSL/TLS handshake. The client is only optionally authenticated with a certificate, it is not mandatory and the client authentification with certificates is done rarely.
- Server: receives the SSL/TLS handshake. The server is always authenticated with a certificate. 
- Certificate Authority (CA): CA is the entity that issues certificates, and it is trusted by the client and the server. If the client trust the CA, and the CA provides a certificate to the server, then the client trust the server. Five organization certificate most of the internet: IdentTrust (owns Let's Encrypt), DigiCert, Sectigo (Comodo), GoDaddy, GlobalSign

For having server and client both authenticated with a certificate, mutual TLS or mTLS is used.

 - reference: https://w3techs.com/technologies/overview/ssl_certificate

### PKI 

- reference: https://www.youtube.com/watch?v=Jefr7wFLu3M&list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY&index=12

### SSL/TLS versions

- reference: https://youtu.be/_KgZNF8nQvE?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY
- reference: https://youtu.be/fk0-UqwVNqY?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY

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
- reference: https://cryptobook.nakov.com/
- reference: https://www.youtube.com/watch?v=_TixdHlCMu4&list=PL7d8iOq_0_CWAfs_z4oQnCuVc6yr7W5Fp

### Hashing 

- reference: https://youtu.be/HHQ2QP_upGM?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY
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

### Data Integrity

- reference: https://youtu.be/doN3lzzNEIM?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY

Hashing is used to provide data integrity.

So when a message is send, is is computed by a hashing algorithm and a digest would be generated. Then, both the message and digest would be send, and the receiver
would calculate independently the digest again, and compare it with the provided digest. 

This has a weak point: the issue with this implementation, is that a man in the middle attack, would be able to recalculate a digest, from a modified messages. This proves, that 
simply hashing a message something else must be done: Both parties must agree on a secret key, then, the sender can combine the secret key with the digest to generate a new digest. 

This usage of digest + secret key, provides the properties of: Integrity + Authentification. 

This concept of (Message + secret key), is known as **MAC: Message Authentification Code**. The industry standard for creating a MAC is named HMAC (Hashed Based Message Authentification Code RFC 2104). 

- reference: https://en.wikipedia.org/wiki/HMAC

### Encryption 

- reference: https://youtu.be/o_g-M7UBqI8?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY

Encryption is for having confidentiality, meaning only the intended receiver can interpret the messages. 

Simple encryption: get an input text or message and transforms it into a ciphered text. The downside of the simple encryption, is that it doesn't scale, you cannot use the same encryption scheme with all the different message recipients, otherwise all the recipients would be able to decrypt the messages for other recipients. It would be needed a new encription algorithm for every new intended recipient, and every encription algorithm should be kept secret, and it could not be a public known algorithm. 

As oposed to simple encryption, is the **key based encryption**, which uses known vetted algorithms with a secret key. As different secret keys are used for each user, the ciphered text is different for every user. 

There are two types of key based encryption:
- symmetric encryption: encrypt and decrypt using the same keys.
  - is faster that asymmetric encryption
  - cypher text is almost the same size as the plain original text
  - the key for the encryption must be shared, so it is less secure that asymetric encryption.
  - ideally used for buld big data communications
- asymmetric encryption: encrytp and decrypt using different keys. Asymmetric encryption are based non-reversible mathematic operations. One of the keys in known as the **public key** and the other as **private key**.
  - is slower than symmetric encryption.
  - it has cipher expansion, so the encrypted text is larger than the original plain text.
  - the privat key is never shared, so it is more secure than symmetric encription.
  - ideally used for limited size communications. 

- reference: https://www.freecodecamp.org/news/encryption-explained-in-plain-english/
- reference: comparition symmetric vs asymmetric encryption: https://youtu.be/o_g-M7UBqI8

#### List of symmetric encryption algorithms

- 3DES
- AES
- ChaCha20 

#### List of asymmetric encryption algorithms

- DSA
- RSA 
- Diffie-Hellman : https://youtu.be/NmM9HA2MQGI
- ECDSA
- ECDH

## Public and private keys

- reference: https://youtu.be/_zyKvPvh808?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY

Asymmetric encrytpion uses 2 keys, public and private keys to work. 


### How SSL/TLS uses encryption

- reference: https://youtu.be/aCDgFH1i2B0?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY

SSL/TLS has to comply with: 
- Confidenciality: Data is only accessible to the client and server. Encription
- Integrity: Data is not modified between client and server. Hashing (MAC Message Authentification Code) 
- Authentication: client/server are who they say they are. PKI.

 Asymmetric encription is used for an initial key exchange, so it is possible for the client and server continue the communication with symmetric encription. 

 Note: In Linux you can generate asymmetric keys with the command `ssh-keygen`.

 The CA (Certificate Authority) is an entity that is trusted by the client, and the CA generates a certificate, and that certificate has a link to a given set of asymmetric key pair to an identity. And the certificate is signed by the CA, so we have authentication for the certificate itself, and can be sure it has be unmodified. So as it is authenticated and unmodified the secret keys derived form the certificate are authenticaed. 

 These three actors: client, server and certificate authority are what is known as PKI: Public Key Infraestructure. 

### PKI 

- refernece: https://youtu.be/Jefr7wFLu3M?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY

 ### RSA

 - reference: https://youtu.be/Pq8gNbvfaoM?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY
 - reference: https://manansingh.github.io/Cryptolab-Offline/c14-rsa.html
 - reference: how it works: https://youtu.be/qph77bTKJTM
 - reference: https://www.infoworld.com/article/3650488/understand-the-rsa-encryption-algorithm.html

RSA stands for Rivest, Shamir and Adleman, which are the last name of the creators of the algorithm (1977)

RSA is the most common asymetric enchription algorithm, RSA creates a pair of keys, one to encrypt and the other to decrypt. 

Other encryption algorityhms are DH/DSA.

### Diffie-Hellman (DH)

- reference: https://youtu.be/KXq065YrpiU?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY

The Diffie-Hellman protocol is an asymetric encryption algorithm which allows two parties to share a secret over an
unsecure communication medium. The shared secret never is send over the insecure medium. 

- reference: https://www.securecoding.com/blog/diffie-hellman-key-exchange/
- reference: https://cryptobook.nakov.com/key-exchange/diffie-hellman-key-exchange

### Digital Signature Algorithm  (DSA)

- reference: https://www.youtube.com/watch?v=iS1nK4G6EtA
- reference: https://en.wikipedia.org/wiki/Digital_Signature_Algorithm
- reference: https://www.youtube.com/watch?v=ANsg4wIQFn4

DSA is other encryption mechanism, but can only be used for signatures. 

DSA has only two operations:
 - signature generation
 - signature verification

A note on caution about using random numbers, if you repeat the random number, it is possible to break the 
encryption. To prevent this use for example the RFC 6979 how to generate random numbers deterministically based on the message.


## x509 certificates and keys

1. The certificate authority (CA) is the corner stone of the TLS/SSL process.
   - CA has a public key and private key.
   - CA has a self-signed certificate
2. A server want a certificate
3. The server generates a public and private key.
4. Then the server generates a certificate signing request (CSR).
   - CSR contains the server's public key
   - CSR is signed by server's private key
5. The server gives the signed CSR to the certificate autority (CA).
6. The CA inspects and validates information in CSR
7. The CA creates a certificate using information from the CSR, particullary the public key of the server submited on the CSR.
8. The CA signs the certificate using its CA's private key.
9. The certificate is given to the server.
10. The server can provide now its certificate to prove its identity.


### What is a certificate?

The contents of a certificate is defined by the x.509 standard  

- reference: https://en.wikipedia.org/wiki/X.509#Structure_of_a_certificate
- reference: https://datatracker.ietf.org/doc/html/rfc5280

A certificate has 3 sections:
- certificate data:
     - version
     - serial number
     - signature algorithm
     - validity
     - subject and issuer
     - public key
     - extensions.
- signature algorithm
- signature 

#### Version
this is the version of the x509 specification:
 - 0x0 - x509 Version 1 - no longer in use
 - 0x1 - x509 version 2 - rarely used (avoid if possible)
 - 0x2 - x509 version 3 - most typical for today's certificates

The x509 version 3 adds certificates extension, which are optional fields taht add features to SSL/TLS certificates.

#### Serial number
Is a 20 bytes (106 bits), that uniquely identificates a certifiace issued by a given CA.
This number is used to look up the validity of a certificate.

This serial number is used for validation, so a request is made to the CA 
to validate if ther certificate with that serial number is valid.


The validity of this serial number is done by two protocols:
 - CRL - certificate revocation list
 - OCSP - online certifiacte status protocol


#### Signature Algorithm.

This is the algorithm used to generate the signature of the certificate.

It is made by two elements:
 - Hashing algorithm.
 - Asymmetric encryption which generated the keys.

#### Validity

Validity specifies the dates in which the certificate is valid.

It is specified with two values:
- Not Before
- Not After

#### Subject and Issuer

The Subject field will identify the identity of the server. 

The issuer, identifies the CA that signed the certificate.

Remember that certificate autorities also have ceritifactes, and that the CA sign their own certificates.

When a certificate has the same subject ans issuer, that is known as self-signed certificate.

The content of the Subject ans issuer, is specified in which is known as Distinguised Name (DN) format. This is
just a hierarquy of atribute-value pairs (LDAP-RFC 4519 attribute definitions). 
For example: 
 - CN Common Name
 - OU Organizational Unit
 - O Organization
 - L locality/city
 - ST State
 - C country

The most relevant one is CN, the common name, because it must exists in the Subject and Issuer. And the 
browsers verify CN against the URL used.

CN can include a wildcard (*) on the certificate. For example `CN=\.google.com` . This allows to protect
the subdomains, like: `maps.google.com`, or `mail.google.com`, but not `us.mail.google.com` Also, it doesn't protect `google.com`







   

  

