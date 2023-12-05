
# Notes on SSL/TLS

## Fundamentals

Most of the internet is based on using the protocols:
 - HTML: Hyper Text Markup Language (web sites)
 - HTTP: Hyper Text Transfer Protocol (retrieve web sites) https://datatracker.ietf.org/doc/html/rfc2616

Sometimes you want to send private information through internet (like passwords). For that we can use SSL/TLS. 

 - HTTPS: this is HTML transferred with HTTP protected by a SSL/TLS tunnel.

### What is SSL and TLS?

- refernece: https://youtu.be/aCDgFH1i2B0

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

### Data Integrity

Hashing is used to provide data integrity.

So when a message is send, is is computed by a hashing algorithm and a digest would be generated. Then, both the message and digest would be send, and the receiver
would calculate independently the digest again, and compare it with the provided digest. 

This has a weak point: the issue with this implementation, is that a man in the middle attack, would be able to recalculate a digest, from a modified messages. This proves, that 
simply hashing a message something else must be done: Both parties must agree on a secret key, then, the sender can combine the secret key with the digest to generate a new digest. 

This usage of digest + secret key, provides the properties of: Integrity + Authentification. 

This concept of (Message + secret key), is known as **MAC: Message Authentification Code**. The industry standard for creating a MAC is named HMAC (Hashed Based Message Authentification Code RFC 2104). 

- reference: https://en.wikipedia.org/wiki/HMAC

### Encryption 

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

Asymmetric encrytpion uses 2 keys, public and private keys to work. 

- reference: https://youtu.be/_zyKvPvh808?si=ZCCHzJVRzENrvPdb

### How SSL/TLS uses encryption

SSL/TLS has to comply with: 
- Confidenciality: Data is only accessible to the client and server. Encription
- Integrity: Data is not modified between client and server. Hashing (MAC Message Authentification Code) 
- Authentication: client/server are who they say they are. PKI.

 Asymmetric encription is used for an initial key exchange, so it is possible for the client and server continue the communication with symmetric encription. 

 Note: In Linux you can generate asymmetric keys with the command `ssh-keygen`.

 The CA (Certificate Authority) is an entity that is trusted by the client, and the CA generates a certificate, and that certificate has a link to a given set of asymmetric key pair to an identity. And the certificate is signed by the CA, so we have authentication for the certificate itself, and can be sure it has be unmodified. So as it is authenticated and unmodified the secret keys derived form the certificate are authenticaed. 

 These three actors: client, server and certificate authority are what is known as PKI: Public Key Infraestructure. 

 

  





  

