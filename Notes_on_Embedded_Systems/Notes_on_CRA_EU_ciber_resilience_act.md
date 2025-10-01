The Cyber Resilience Act (CRA) is a new European Union law that sets cybersecurity requirements for digital products. 
Even if you’re not based in the EU, the CRA may still apply if your software reaches the EU market.

The law introduces strict rules across the product lifecycle and includes significant penalties for non-compliance. 
Key provisions take effect in June 2026, with full enforcement in December 2027, giving organizations limited time to prepare.

references: 
 - https://digital-strategy.ec.europa.eu/en/policies/cyber-resilience-act
 - https://www.european-cyber-resilience-act.com/
 - https://eur-lex.europa.eu/eli/reg/2024/2847/oj
 - https://github.com/ossf/wg-globalcyberpolicy/tree/main/documents/CRA
 - https://www.cyberresilienceact.eu/the-cra-explained/
 - https://www.theregister.com/2025/09/30/cyber_reiliance_act_opinion_column/

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

OOs steward: a legal person NOT a manufacturer who "systematically" (provides) support on a sUstaIned basis for the development of specific OSS PDE intended for commercial activities that ensures the viability of those products.

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
- Various vulnerability reporting & handling (usually +5 years)
- Create technical documentation
- Designate vulnerability single point-of-contact
- Info for users
- Assess conformity
- Must report vulnerabilities & incidents


### Risk management and cybersecurity requirements

PDEs has to be desing and developed and produced with a continous eye on risks. 

Annexs I and II.

1- Risk identification
2- Risk analysis (likelyhood and impact)
3- Determine applicatibility of security controls
4- Determine how the security controls ae implemented
5- Design/Develop/Produce in a risk proportionate manner
6- Apply vulnerability handling requirements

PDEs shall be designed, developed and produced (to ensure) appropiate levels of cybersecurity based on risks

On the basis of the cybersecurity risk assesments PDEs shall:
 - Have no known exploitable vulnerabilities
 - Have a secure 'by default' configurations, unless ... taylor made PDE. (you cannot have a PDE with a default user: Admin and psw: Admin, except maybe in a 'testing' mode).
 - Ensure ... vulnerabilities security updates
 - Ensure that the PDE implements security as defined by: confidentiality, integrity and availability
    - confidentiality: only authorized users can read information
    - integrity: only authorized users can write information
    - availability: authroized users can continue to use the system, even when an adversary is trying to prevent it.
 - limit attack surfaces
 - reduce the impact of an incident
 - recording and monitoring
 - [enable] users to securely remove/transfer all the data and settings.

### Information and instructions to the user

- Manufacture name, postal/email addresses, website.
- Point of contact for reporting vulnerabilities and coordinated vulnerabilities disclosure policy
- PDE name/id
- Intended PDE purpose
- Circumstance/s which may lead to significant cybersecurity risks
- Internet address for EU declaration of conformity
- Technical security support offered and end-date
- Detailed instructions (may provide an internet address for them)
- SBOM location if manufacturer makes it available



### Vulnerabilities handling requirements for manufacturers

- Identify and document vulnerabilities and components in DPEs
- Address and remediate vulnerabilities without delay (in relation to the risk)
- Apply effective and regular tests and reviews of the security of the PDEs
- Share and publicly disclose information when security update available
- Enforce a policy on coordinated vulnerability disclosure
- Facilitate (information sharing) about potential vulnerabilities in their PDEs and its 3rd party components
- Provide mechanims to securely distribute updates for PDEs
- Disseminate without delay available security updates, free of charge. Update must be available for 10 years and while PDE is supported.


### Reporting vulnerabilities and incidents

Reference: European vulnerability database: CIRCL vulnerability-lookup: https://vulnerability.circl.lu/

Reference: Article 14

- Manufacturers must notify designated CSIRT and ENISA of any **actively exploited vulenerability** in PDE that it becomes aware of: 
  - early warning less than 24 hours, general info less than 72 hours
  - final report less than 14 days after correction/mitigation available)
- Must also notify for a **severe incident**:
  - early warning less than 24 hours, incident notification less than 72 hours, final report less than 1 month
  - What is a **severe incident?**: incident is an event compromising data or service. Its severe if it:
     - can negatively affect (availability, authenticity, integrity, confidentiality of sensitive or important data or functions
     - can lead to introduction/execution of malicious code in PDE or user network
- Manufacturer must inform impacted users (or all users) after becoming aware of an actively exploited vulnerability or a severe
incident "in a timely manner"
- Who and how report is described in Article [14(7)]


Anyone can report a vulnerability/cyber thread/incident to a designated CSIRT or ENISA
- CSIRT informs manufacturer without delay, ensures anonymity of notifieer
- ENISA to create a single reporting platform



## Adapting an organization to meet CRA requirementes

  - Development process
  - Risk management (product, dev process)
  - Conformity assesement
  - Vulnerability management & incident reporting
  - Software update availability
  - Documentation & availability
  - Coordinate CRA clarifications in your industry
  - Supplier management / upstream contribution obligation


## Aditional resources

 - Regulation (EU) 2024/2847 Cyber Resilience Act (CRA): https://eur-lex.europa.eu/eli/reg/2024/2847/oj
 - Blue Guide, (EU) 2022/C 247/01: https://eur-lex.europa.eu/legal-content/%20EN/TXT/?uri=CELEX%3A52022XC0629%2804%29
 - Legislative Acts related to CRA: https://webgate.ec.europa.eu/regdel/#/legislativeActs/1274?lang=en
 - Standardization for the CRA: https://cyberstand.eu/events/standardisation-cyber-resilience-act
 - PSIRT Obligations Checklist: https://github.com/ossf/wg-globalcyberpolicy/blob/main/documents/CRA/checklists/PSIRT_Obligations_Checklist.md
 -  TR-03183: https://www.bsi.bund.de/dok/TR-03183-en
 -  TR-03185: https://www.bsi.bund.de/dok/TR-03185-en
 -  The Regulators Are Coming: One Year On: https://archive.fosdem.org/2024/schedule/event/fosdem-2024-3683-the-regulators-are-coming-one-year-on/
 -  ORC WG FAQ: https://github.com/orcwg/cra-hub/blob/main/faq.md
 -  OpenSSF CRA info: https://openssf.org/public-policy/eu-cyber-resilience-act/


## Reporting vulnerabilites and incidents

 - OpenSSF Global Cyber Policy WG: https://github.com/ossf/wg-globalcyberpolicy/discussions
 - CRA (Regulation (EU) 2024/2847): https://eur-lex.europa.eu/eli/reg/2024/2847/oj



## Questions

### 1 Which of the following does the CRA apply to? correct

- Pure website with no mobile application                                           x 
- Non-commercial software                                                           n
- Software where support contracts are offered for profit                           x
- Internet-connected toy for sale                                                   x
- free Mobile application to access the application maker’s for-profit service      x

### 2 Which of the following is true about standards and the CRA? correct 

- Some CRA-related standards are mandatory, that is, they must be followed to meet the CRA. 
- All CRA-related standards will provide a presumption of conformity.
- Some CRA-related standards are in development that will, if complied with, provide a presumption of conformity. X correct
- Compliance with standards never provides a presumption of conformity.


### 3 Which of the following is NOT a requirement on OSS stewards?  correct

- Emplace & document a cybersecurity policy to foster development of a secure PDE, handle vulnerabilities, foster voluntary reporting of vulnerabilities
- Cooperate with the market surveillance authorities to mitigate risks
- Report on actively exploited vulnerabilities & severe incidents
- Attach a CE mark to any OSS update X correct

### 4 Which have the strictest compliance assessment requirements? correct

 - Default
 - Important class I
 - Important class II
 - Critical X correct

### 5 All of the CRA requirements begin fully applying to manufacturers beginning in what year? correct

 - 2024
 - 2025 
 - 2026
 - 2027 X Correct

### 6 Select all answers that apply. What information must be provided to PDE users according to the CRA: correct

 - Manufacturer name, postal/email address, and website                                             n
 - Point of contact for reporting vulnerabilities & coordinated vulnerability disclosure policy     x
 - Intended PDE purpose                                                                             n
 - Internet address for the EU declaration of conformity                                            x
 - Detailed technical documentation                                                                 n

### 7 Once a manufacturer becomes aware of an actively exploited vulnerability, the manufacturer must provide early warning notification to a designated CSIRT & ENISA within: correct

 - 24 hours X correct
 - 72 hours
 - 14 days
 - 1 month

### 8 Select all answers that apply. PDEs must be designed, developed, and produced [to ensure] an appropriate level of cybersecurity based on the risks. Which of the following are specific requirements, where relevant? correct

 - have a secure by default configuration, unless it’s a tailor-made PDE                                                   X
 - ensure all components have no vulnerabilities regardless of whether or not the components are exploitable in the PDE    n
 - limit attack surfaces                                                                                                   X
 - take steps to reduce the impact of an incident                                                                          x



### 9 Select all answers that apply. Which of the following can be done by an OSS contributor or OSS project and still be non-commercial:

 - Contribute some code, without pay, to some other OSS project                                                                X x x x x x x x
 - Perform regular releases of an OSS project                                                                                  X x x x x x x x
 - Receive donations without intent to make a profit                                                                           n x x x x x x x
 - Charge for support services beyond their actual costs                                                                       n n n n x x x x
 - Require personal data for reasons other than for improving the security, compatibility or interoperability of the software  n n n x n x x n
 - Provide a software platform through which you monetize other services                                                       n n x n n n x n

### 10 Select all answers that apply. Which of the following are required by the CRA related to vulnerabilities: Correct

 - An SBOM in a machine-readable format covering at least the top-level dependencies      x
 - Address and remediate vulnerabilities without delay, in relation to their risks        x
 - Provide mechanisms to securely distribute updates for PDEs                             x
 - Disseminate without delay available security updates, free of charge                   x
 - Ensure that there are no vulnerabilities in a PDE                                      n









