# Notes on SSL/TLS

- Intro: https://youtu.be/VcV4T8cL3xw
- https://www.cloudflare.com/learning/ssl/transport-layer-security-tls/

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

- reference: https://youtu.be/Jefr7wFLu3M?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY

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

#### Public Key
It is present as tow values:
 - Modulus  ( N (P*Q))
 - Exponent (E)

For eliptic curves certificates, the values are:
 - Public key
 - Curve

#### Extensions

Extensions only exists on x509 v3 (version 3). 

Extesions are optional fields that add features and restrictions to certificates.

### Inspecting a certificate

For this `openssl` will be used.

`openssl s_client` is an utility that will instruct openssl to act as an ssl client. 
So, it will connect to a website and retrieve its certificate.

`openssl s_client --connect redit.com:443`

the answer is in base-64 encoded. 

to check the certificate, we can use 

```
openssl x50 -in mycert
```

This will report the base-64 version, for getting the text output, use:

```
openssl x50 -in mycert -text
```

To not retrive the base-64 version:

```
openssl x50 -in mycert -text noout
```


### Certificate extensions

- reference: https://www.ibm.com/docs/en/external-auth-server/2.4.3?topic=securing-x509-extensions
- reference: https://access.redhat.com/documentation/en-us/red_hat_certificate_system/9/html/administration_guide/standard_x.509_v3_certificate_extensions

Remember extensions only exist on x509 version 3. 

Extensions are optional fields that add features and restrictions. 

#### Extensions: Key Usage & Extended Key usages

Set usages/limits for excription keys. 
For example: 
 - if you can use the encryption keys to encrypt data. Encripting data with the asymemtric keys is not very efficient, so normally these are used to stablish symmetric keys.
 - if you can use the encryption keys to sign certificates.
 - if you can use the encryption keys to verify signatures.
 - if you can use the encryption keys to verify CRL signatures.

The Key usage extension, tipically is limited by purpouses.

The Extended Key Usage is limiting by protocol and/or role.

The reacionale of this usages limitation, is to limit the domain of usage of certificate and keys, so if that key/cert is compromised, this only compromises certaing usages. 
   
### Extensions: Basic constrains 
  
The basic constrains extension will determine wether the subject of the certificate is certificate authority or an end-entity (a server certificate as X.com). 

The rationale behind this constrain is that CA certificates can be issuers to other certificates, whereas end-entity certificates **cannot** be issuers to others certificates. 

### Name constrain extension

The Name constrain extension limits the signing to a specific domain. Tipically this is used by corporate CA. This way a corporate certificate cannot sign any domain out of the corportation control. 

### Key identifier extensions

This extensions include: 
 - Unique identifiers for Public Key

There are 2 extensions:
 - Subject key identifier
 - Authority key identifier - the issuing entity.

These extensions are used for: 
 - Track keys across certificates
   - Certificates have a validity date, so that means that certificates expire. When the cert expires, a new cert is requested from CA, that new certificate will have a new unique serial number, but there is nothing mandating that the new certificate have a new pair of asymmetric keys. You can continue to use the same set of asymmetric keys for the renewed certificate. With the subject key identifier extension, is possible to track a particular key across many iterations of the certificate
   - Other user case, is to identify which specific key signed a given certificate. For example, many CA have multiple key-pairs, and rotate through the keys when issuing certificates. The Authority key identifier, allows to identify those keys used to sign a certificate.
  
 In a self sign certificate the Subject key identifier is the same as the authority key identifier. 

### Subject alternative name extension

This extension allows a single certificate to protect several domains. In a certificate inside the subject field, is the common name (CN) - (the common name what the brownser is going to compare with the address bar, to ensure the correctness of the certificate). So until wild card where added to the certificate, there was one certificate per domain. The wild card certs allows multiple subdomains for a single domain. 

The Subject alternative name, or SAN, allows to protect multiple domains. 

### CLR distribution point extension

CLR stands for Certificate Revocation List. It is just a list with all the revoked certificates by the CA. 

This list is maintained by the CA. The CLR extension is providing the URI to that list. 

### Authority Information Access extension

This extension provides the place for CA to provide the information to whoever may be using the certificates that they issued. 

This extension provides two fields: 
 - Issuer's certificate
 - OCSP location

Issuer's certificate: a link to get the issuer's certifite. That is useful, because to verify a signature it is needed CA public key, so in case the user doens't have it, this field can be used to retrieve it. 

OCSP location: This field indicate the location for the OCSP responder. OCSP stands for Online Certificates Status Protocol, which is a more efficient way to check revocated certificates than the CRL list. 

### CT extension

Stands for Certificate Transparency extension. 

     
### What is a private key file?

Inside a private key file, there are serie of mathematical values used for asymmetric encryption: 
- Modulus (N : product (P*Q))
- Public exponent (E : Public key)
- Private exponent (D : Private key)
- Prime 1 (P)
- Prime 2 (Q)
- Exponent 1
- Exponent 2
- Coefficient

For reading an private key file, use an interpreter: 

```bash
openssl rsa -in <Private_key_file.key> --noout -text
```

To extract only the modulus:
```bash
openssl rsa -in <Private_key_file.key> --noout -modulus
```

The Modulus, also exists on the certificate, check it with:

```bash
openssl x509 -in <certicate.cert> --onout -text
```
to extract only the modulus:
```bash
openssl x509 -in <certicate.cert> --onout -modulus
```

### What is a CSR?

A Certifiate Signature Request (CSR) is comprised of 3 elements: 
 - a certificate request info, with:
     - version
     - subject DN
     - Public key
     - attributes
 - signature algorithm
 - signature

The CSR is created by the server to create the signature. So the siganture is created by created a hash with all the certifcate request info, and signed with the server private key. That is the signature. 

#### Version:

It`s only value today is 0x0, CSR version 1.  

#### Subject DN: 

Subject Distigish Name: It contains the distigish name that identifies attributes correlating with the subject: C=, ST=, L=, OU=, CN=...

The content of the Subject ans issuer, is specified in which is known as Distinguised Name (DN) format. This is
just a hierarquy of atribute-value pairs (LDAP-RFC 4519 attribute definitions). 
For example: 
 - CN Common Name
 - OU Organizational Unit
 - O Organization
 - L locality/city
 - ST State
 - C country

The most relevant one is **CN**, the common name, because it must exists in the Subject and Issuer. And the 
browsers verify CN against the URL used.

CN can include a wildcard (*) on the certificate. For example `CN=\.google.com` . This allows to protect
the subdomains, like: `maps.google.com`, or `mail.google.com`, but not `us.mail.google.com` Also, it doesn't protect `google.com`

The CA imports this information into the Certificate. The CA includes its own DN as the certificate's issuer. 

#### Public key

The public key is presented as two values: modulus and exponent

#### Attributes

Optional, aditional CSR features are added. 

 - Extension request attribute:
     - The server adds extesions for the ensuing certificate: Subject key Identifier, S.A.N.(subject alternative name), etc...
  
 - Challenge password: when the CSR is provided, the challenge password is provided to the CA. And later on, if any administrative action has to be taken on the certificate, the challenge password has to provided. The goal is to limit who can take administrative actions on a particular certificate, to only whoever first requested that certificate in first place. This challange password system is considered legacy system nowadays. Today if the CA wants to identify you, it has a web portal where you can login with user/password and identify yourself and make the request to revoque the certificate if you want to. 

There may be other attributes, but those were the most common. 

- a0:00 in the CSR Attributes field indicates no attribute requested.

### File formats

Certificates and keys are kept in files, usually 4 file formats are used:

- DER
- PEM
- PFX/PKCS#12
- PKCS#7

#### DER

 - reference: https://letsencrypt.org/docs/a-warm-welcome-to-asn1-and-der/

DER stands for Distingished Encoding Rules. It is the format of the certificate on the wire, meaning, as it is being transfered from server to client. So it is a binary format. So it cannot be open with a text editor. So it is not tipically used for exchanging files. 

Tipicall extensions are: .der, .cert, .crt, .csr

Note, that the file extension is not sufficient to identify the file format.  

#### PEM

 - reference: https://en.wikipedia.org/wiki/Privacy-Enhanced_Mail
 - reference: https://datatracker.ietf.org/doc/html/rfc7468

PEM stands for Privacy Enhaced Mail. 

It is a base64 encoded version of the DER format. Every 6 bits are translated into a character, in the following way:

| binary   |  Value  |
| -------- | ------- |
| 00-25    | A-Z     |
| 26-51    | a-z     |
| 52-61    | 0-0     | 
| 62       |   +     |
| 63       |   /     | 
|(padding) |   =     |

This makes the certificate very easy to copy/paste, and can be open with a text editor.

It has the indicators: 

```
----- BEGIN CERTIFICATE--------
```

```
------ BEGIN PRIVATE KEY -------
```

```
---- BEGIN CERTIFICATE REQUEST ----
```

Those headers is how you can identify a PEM file. 

PEM formated files, usually use the extensions: .pem, .cert, .crt, .key, .csr

#### PFX/PKCS#12

PFX stands for Personal inFormation eXchange

PKCS#12  stands for Public-Key Cryptography Standard # 12

Nowadays both standards are the same one. It is teh PKCS#12 standard, but it usually is refered as a PFX file. 

It contains a certificate and a matching key. And optionally any chain certificates that are necesary.

PFX filesa are binary encoded, so it is not possible to read them in a text editor. 

PFX files use the extensions: .pfx, .p12, .pkcs12.

####  PKCS#7

PKCS#7  stands for Public-Key Cryptography Standard # 7

It is a base64 encoded file. It can be opened in a text editor file, and it is recognizable the label `---- BEGIN PKCS7 ----`.

Contains Certificates and/or Chains only - but no keys, only certificates. 

The files use the extensions: .pkcs7, .p7b, .p7c. 


## Security thought certificates

### Overview, review PKI

- reference: PKI: https://youtu.be/Jefr7wFLu3M?list=PLIFyRwBY_4bTwRX__Zn4-letrtpSj1mzY

1. The certificate authority (CA) is the corner stone of the TLS/SSL process.
   - CA has a public key and private key.
   - CA has a self-signed certificate
2. A server wants to adquire a certificate
3. The server generates a public and private key.
4. Then the server generates a Certificate Signing Request (CSR).
   - CSR contains the server's public key
   - CSR is signed by server's private key
5. The server gives the signed CSR to the certificate autority (CA).
6. The CA inspects and validates information in CSR
7. The CA creates a certificate using information from the CSR, particullary the public key of the server submited on the CSR.
8. The CA signs the certificate using its CA's private key.
9. The certificate is given to the server.
10. The server can provide now its certificate to prove its identity.
11. The clients wants to connect to the  server securely.
    - The client (ie web browsers) already has the CA certificates installed.
12. The client requests the server's certificate
    - The client validates that the certificate is legitimate. (usting the public key of the CA)
    - The client validates that the server truly owns the certificate. (making sure the public key provided in the certificate the server has the private key)
13. The clients validates Server's certificate in the SSL/TLS handshake.
14. SSL/TLS Handshake produces session keys:
    - symmetric encription (for confidentiality)
    - message authentification code MAC (for integrity and authentification)
15. Session keys, form a secure tunnel to protect the communication.


   
All this validation happens in what is know as TLS handshake. 

### Certificate validation

When a client receives a certificate from a server, there are two things that the client, needs to validate:
 - Is the certificate valid?
    - A certificate is just text into a file. How can the client known that the contents can be trusted?
 - Is the server the owner of the certificate?
    - the certificates are publically available out there, so how can the client confirm that the server is the true owner?
  
#### Is the certificate valid? 

It starts with the CA (certificate authority) which is who creates the certificate in the first place. 

The certificate has 3 sections: 
 - certificate data
 - signature algorithm
 - signature

The CA (certificate authority) creates the certificate, and then creates a hash with the certificate data. Runs the certificate through a standard hashing algorithm, and then encrytp that hash. The result of this is the signature, the third part of the certificate. 

Now the client comes into play, remember that the client already has the CA certificate, so the client already has the CA public key. That public key can be used to validate any signature from the CA. 

Next the client connects to the server, and obtains the server certificate. So the client decrypts the signature portion of the certificate provided by the server, using the CA public key (result 1). Then the client calculates the hash of the content of the certificate data (result 2). If both values are thge same (result 1 == result 2), that implies that the certificate has not change since the CA created it. Wich means that if the CA is trusted, the the certificate is trusted. 

This is the process for the RSA encrytpion algorithm, the process is similar for the DSA encryption algorithm. 

For the DSA algorithm, the client is going to run the certificate data through the DSA signature generationa algorithm (that requires the CA private key), the result of that is the signature. The client then runs the signature verification on the signature of the certificate (with the CA public key), the result is 1 (valid) or 0. 

Once the certificate has been validated, then the rest of the fields can be validated: expiration dates, URLs match the Common Name ... Or if the certificate is revoked. ...
