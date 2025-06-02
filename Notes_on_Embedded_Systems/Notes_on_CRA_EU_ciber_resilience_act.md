The Cyber Resilience Act (CRA) is a new European Union law that sets cybersecurity requirements for digital products. 
Even if you’re not based in the EU, the CRA may still apply if your software reaches the EU market.

The law introduces strict rules across the product lifecycle and includes significant penalties for non-compliance. 
Key provisions take effect in June 2026, with full enforcement in December 2027, giving organizations limited time to prepare.

references: 
 - https://digital-strategy.ec.europa.eu/en/policies/cyber-resilience-act
 - https://www.european-cyber-resilience-act.com/
 - https://eur-lex.europa.eu/eli/reg/2024/2847/oj
 - https://github.com/ossf/wg-globalcyberpolicy/tree/main/documents/CRA

Ciber Resilience Act (CRA) is European Union (EU) regulation 2024/2847:
 - entered in force in 10 December 2024
 - 130 recitals (justifications), 71 articles, 8 annexes, overall over 52000 words

### CRA establish general requirements for 
 - Making products with digital elements(PDE) available on the EU market.
 - Risk management, desing, development and production of PDEs for cybersecurity
 - vulnerability reporting, severe incident reporting and vulnerability handling

### Timeline:
 - 10 Dec 2024: entered into force
 - 11 June 2026: articles 35 to 51: goverments ready, assesement bodies in place
 - 11 Sept 2026: manufacturers must report
 - 11 Dec 2027: entire regulation fully applies

### CRA purpose and motivations: 

Cyberatacks represent a matter of public interest as they have critical impact
 - not only on the EU economy.
 - but also in democracy as well as consumer safety and health.

Aims for the development of secure products and digital elements [PDEs] by ensuring that hardware and software products are placed on the market
 - with fewer vulnerabilities
 - manufacturers take seriulsy throught a product lifecycle

Aims to enable users to take cibersecurity into account when selecting and using PDEs.

references:
 - https://www.dataprotection.ie/en/news-media/latest-news/irish-data-protection-commission-fines-tiktok-eu530-million-and-orders-corrective-measures-following
 - https://gizmodo.com/backdoors-in-huawei-equipment-discovered-by-vodaphone-i-1834408368

### CRA scope 

 - Impacts many organizations
 - CRA focus: cybersecurity of any "product with digital elements" (PDE)
 - Non included: Non-commercial, websites, services without product
 - Applies to PDEs if made available on EU market
    - If purpose/foreseeable use has data connection (common!)
    - some specialty cases with their own regulation excluded (e.g. medical devices, motor vehicles)
 - Digital technology - including software is global.
 - Impact of Open source (OSS) significally reduced from initial proposal. Open source is non-commercial, so it is not included :)

### Key terms 

 - PDE "product with digital elements"
 - making available on the market: the supply of a PDE in the EU
 - market surveillance: ensure the products comply with legistlation and protection of the public
 - market surveillance authority: and authority designated to do market surveillance
 - designated computer security incident response team (CSIRT): computer emergency response team

### Roles

 - PDE "product with digital elements"

 - Open-source software (OSS) steward: A person that provides suport of PDE in software that qualifies as OSS.
 - OSS develop
 - Manufacturer: A legal person that manufactures PDE
 - Importer: A legal person stablish in EU that places in the market a PDE stablish outside of EU
 - Distributor: Someone other that a manufactureer or an importer that makes a PED abailable in the EU.

### Products categories

- Divides "products with digital elements" (PDEs), including software, into:
    - Important class I & class II (annex III) - e.g. browsers, password managers, operating systems.
    - Critical (annex IV) - e.g. smart cards
    - Default
- "High risk AI systems" specially covered in article 12
- Important/critical/high risk AI have aditional requirements
- Electronic Health Record (EHR) systems to be included via amendement
- Only the most top-level element is relevant to category

What are important class I: 
 - Identity managment and privilege access management
 - standalone and embedded browsers
 - password managers
 - software that searches for removes or quarantines malicious software
 - VPNs
 - network management systems
 - security information and event management (SIEM)
 - boot managements
 - public key infrastructure and digital certificate issuance software
 - physical and virtual network interfaces
 - operating systems
 - routers, modems for internet and switches
 - microprocessors with security related functionalities
 - microcontrollerts wiyth security related functionalities
 - ASICs and FPGAs with security related functionalities
 - Smart home general purpose virtual assistants
 - smart home products with security functionalities
 - internet connected toys with social or location tracking
 - person wearable products for health monitoring or intended for children

What are important class II:
 - hypervisors and container runtime systems
 - firewalls, intrusion detection and prevention systems
 - tamper-resistant microprocessors/microcontrollers

what are Critical: 
 - Hardware devices with security boxes
 - smart meter gateways / adevanced security devices, incl for secure cryptoprocessing
 - smartcards or similar

#### Requirements of OSS stedwareds

OOs steward: a legal person NOT a manufacturer who "systematically" (provides) support on a systaned basis for the development of specific OSS PDE intended for commercial activities that ensures the viability of those products.

- Emplace and document a cybersecurity policy to foster development of a secure PDE, handle vulnerabilities, foster voluntary reporting of vulnerabilities.
- Cooperate with the market surveillance authorities to mitigate the risk.
- Report on actively exploited vulnerabilities and severe incidents. 

 - https://github.com/ossf/wg-globalcyberpolicy/blob/main/documents/CRA/checklists/OSS_Stewards_Obligations_Checklist.md

### Manufacturers

The manufacturer of a PDE the product must essential cybersecurity requirements. This obligations must be verified by a conformity assesment procedure, and formalized in a document. 

- Design, develop & produce essential cybersecurity requirements
- Assess cybersecurity risks, apply througthout lifecycle
- Document/update cybersecurity risk assesments
- Exercise due diligence when integrating 3rd party components including OSS
- If component vulnerability found, report to component mantainer
- various vulnerability reporting & handling
- create technical documentation
- designate vulnerability single point-of-contact
- info for users
- assess conformity
- must report vulnerabilities & incidents




