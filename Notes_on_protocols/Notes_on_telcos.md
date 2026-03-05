 - https://www.xataka.com/servicios/mi-vecino-tiene-datos-yo-no-que-caida-telecomunicaciones-fue-desigual-durante-apagon-espana
 - https://www.xataka.com/basics/omv-que-que-se-diferencia-operadores-tradicionales
 - https://madridsecreto.co/cobertura-falla-apagon-madrid/
 - https://www.20minutos.es/tecnologia/actualidad/apagon-corte-luz-espana-por-que-falla-cobertura-movil-5704679/
 - https://www.20minutos.es/tecnologia/actualidad/apagon-espana-2025-red-movil-operadoras-vodafone-telefonica-masorange-operadoras-5704831/
 - https://maldita.es/malditatecnologia/20250429/telecomunicaciones-internet-cobertura-movil-apagon/
 - https://www.adslzone.net/noticias/operadores/apagon-operadoras-esperando-volver/
 - https://theobjective.com/economia/telecomunicaciones/2025-04-28/solo-algunas-personas-tienen-internet/
 - https://gigs.com/blog
 - https://gigs.com/blog/what-is-telecom-as-a-service
 - https://gigs.com/blog/mno-mvna-mvne-and-mvno-whats-the-difference
 - https://gigs.com/blog/untangling-oss-bss
 - https://gigs.com/blog/what-is-bss-in-telecom
 - https://gigs.com/blog/embedded-connectivity
 - https://gigs.com/blog/telecom-billing-software
 - https://gigs.com/blog/mobile-network-operator-mno
 - https://gigs.com/blog/white-label-mvno-startup-guide
 - https://gigs.com/blog/mvno-business-model
 - https://gigs.com/blog/mno-mvna-mvne-and-mvno-whats-the-difference
 - https://gigs.com/blog/mobile-virtual-network-aggregator-mvna
 - https://gigs.com/blog/white-label-mvno-startup-guide
 - https://gigs.com/blog/how-to-start-your-mvno-the-smart-way-2
 - what is a rating group: https://www.linkedin.com/pulse/what-rating-group-ggsn-gamma-analytics-0rdnc
 - diameter protocol course introduction: https://www.youtube.com/playlist?list=PLO7rrzYzv_zgVnNQPP_F95AN0nrLtSeGx
 - 5g data session end to end deep dive: https://medium.com/@anand.hv123/5g-data-session-an-end-to-end-call-flow-deep-dive-ac896df596e6

Interesting repos:

 - https://github.com/calee0219/awesome-5g - A curated list of awesome 5G frameworks, libraries, software and resources.
 - https://github.com/ravens/awesome-telco - This list provides resources spanning the entire mobile network stack—from SIM cards to core network functions
 - https://github.com/freeDiameter/freeDiameter
 - https://github.com/5GOpenUPF/openupf
 - https://github.com/shotsan/5G-Repo - Extensive Information on 5G Networks.
 - https://github.com/open5Gcube/open5Gcube - open5Gcube is a Modular Framework for Mobile Network Laboratories. It builds and manages open-source mobile network stacks
 - https://github.com/aligungr/UERANSIM - open source state-of-the-art 5G UE and RAN (gNodeB) simulator.
 - https://github.com/free5gc/free5gc - The free5GC is an open-source project for 5th generation (5G) mobile core networks. Written in Golang.
 - https://hub.docker.com/r/gradiant/open5gshttps://hub.docker.com/r/gradiant/open5gs - 
 - https://open5gs.org/
 - https://github.com/jdegre/5GC_APIs
 - https://github.com/sigscale/ocs - SigScale Online Charging System (OCS)
 - https://github.com/cgrates/cgrates - Real-time Online/Offline Charging System (OCS) for Telecom & ISP environments
 - https://github.com/Oros42/IMSI-catcher
 - https://github.com/open5gs/open5gs
 - https://github.com/open-5g/open-5g.github.io
 - https://github.com/Borjis131/docker-open5gs
 - https://github.com/open5gs
 - OpenAPI Specification Files for 3GPP 5G Core Network: https://jdegre.github.io/parser.html



 The terms Gy and Ro typically refer to reference points and interfaces within the Diameter protocol framework used for real-time online charging in telecommunications networks (LTE and IMS). [1, 2] 
Gy and Ro Interfaces

* Ro Interface: A general 3GPP reference point for communication between a Charging Trigger Function (CTF)—such as a CSCF in IMS—and the Online Charging System (OCS).
* Gy Interface: A specific instance of the Ro reference point used specifically in the packet-switched (PS) domain. It connects the Policy and Charging Enforcement Function (PCEF) (e.g., a PDN Gateway or GGSN) to the OCS. [1, 2, 3] 

Common Procedures and Protocols
Both interfaces share functional procedures to manage credit and charging in real-time: [3, 4, 5] 

* Charging Mechanisms:
* Immediate Event Charging (IEC): Direct debiting for a specific event.
   * Event Charging with Unit Reservation (ECUR): Reserving units for a specific event before final debiting.
   * Session Charging with Unit Reservation (SCUR): Ongoing credit management for the duration of a session (e.g., a data session or call).
* Diameter Messages: They utilize standard Diameter Credit-Control Application (DCCA) messages, primarily CCR (Credit-Control-Request) and CCA (Credit-Control-Answer).
* User Handling: Includes procedures for User-Data-Update, Subscriber-Notification, and User-Data-Pull to synchronize subscriber status with charging limits. [1, 6, 7, 8, 9] 

Would you like more technical details on the Diameter AVP (Attribute-Value Pair) structures for these interfaces, or are you looking for gyroscope sensor wiring? [15] 

[1] [https://www.gl.com](https://www.gl.com/newsletter/diameter-protocol-simulator-gy-ro-interface-newsletter.html)
[2] [https://stackoverflow.com](https://stackoverflow.com/questions/23868221/what-is-the-difference-between-diameter-gy-and-ro-interface)
[3] [https://www.mobius-software.com](https://www.mobius-software.com/documentation/Mobius+Diameter/Ro+%2528application+id%253A+3%2529#:~:text=The%20Ro%20interface%20is%20used%20to%20facilitate,charging%20events%20and%20credit%20control%20in%20real%2Dtime.)
[4] [https://docs.oracle.com](https://docs.oracle.com/cd/F27846_01/docs.85/PCA/online-charging-gy-ro-reference-point.html#:~:text=The%20Ro%20reference%20point%20supports%20interaction%20between,by%20Ro%20within%20the%20common%20charging%20architecture.)
[5] [https://www.gl.com](https://www.gl.com/press-release/diameter-protocol-simulator-gy-ro-interface-press-release.html#:~:text=Mr.%20Vadaila%20further%20explained%2C%20%E2%80%9CBoth%20Gy%20and,PCEF%20%28e.g.%2C%20PDN%20GW%29%20and%20the%20OCS.)
[6] [https://www.gl.com](https://www.gl.com/press-release/diameter-protocol-simulator-gy-ro-interface-press-release.html)
[7] [https://docs.oracle.com](https://docs.oracle.com/cd/E13153_01/wlcp/wlss40/diameter/diameterro.html#:~:text=Credit%20Authorization%20with%20Direct%20Debiting%20For%20direct,account%20immediately%20after%20completing%20the%20credit%20authorization.)
[8] [https://docs.oracle.com](https://docs.oracle.com/cd/E15523_01/doc.1111/e15461/diameter_4.htm#:~:text=Both%20charging%20events%20are%20session%2Dbased%2C%20and%20require,units%20to%20the%20OCF%20upon%20service%20termination.)
[9] [https://www.scribd.com](https://www.scribd.com/document/318706878/Lte-and-Beyond-gy#:~:text=Event%20Charging%20with%20Unit%20Reservation%20%28ECUR%29%20used,charging%20needs%20separate%20reserve%20and%20commit%20actions.)

The primary specification for the Ro interface is [3GPP TS 32.299](https://www.3gpp.org/dynareport/32299.htm). [1, 2, 3] 
This technical specification, titled "Telecommunication management; Charging management; Diameter charging applications," defines the detailed protocols and message flows for both online (Ro) and offline (Rf) charging within 3GPP networks. [2, 4, 5] 
Key Technical References

* 3GPP TS 32.299: The main document specifying the Diameter-based online charging application used by the Ro interface.
* IETF RFC 4006: The Ro interface is based on the [Diameter Credit-Control Application (DCCA)](https://www.ietf.org/rfc/rfc4006.txt), though 3GPP TS 32.299 limits and extends this to meet specific telecom requirements.
* 3GPP TS 32.240: An "umbrella" specification that provides the overall charging architecture and principles for the entire 3GPP charging framework.
* 3GPP TS 32.296: Defines the Online Charging System (OCS) internal applications and interfaces. [1, 4, 6, 7, 8, 9] 

Implementation Details

* Application ID: The Ro application uses Diameter Application ID 4 (Credit-Control).
* Core Messages: It primarily utilizes CCR (Credit-Control-Request) and CCA (Credit-Control-Answer) messages to manage sessions and events.
* Deployment: It is typically used between a Charging Trigger Function (CTF), such as an IMS Call Session Control Function (CSCF), and the Online Charging Function (OCF) within the OCS. [1, 10, 11, 12, 13] 

Are you looking for specific AVP (Attribute-Value Pair) definitions within the TS 32.299 spec, or do you need help simulating Ro interface traffic?

[1] [https://docs.oracle.com](https://docs.oracle.com/en/industries/communications/converged-application-server/8.2/diameter/overview-ro-interface-support.html)
[2] [https://www.arib.or.jp](https://www.arib.or.jp/english/html/overview/doc/STD-T63v11_00/5_Appendix/Rel9/32/32299-9k0.pdf)
[3] [https://www.3gpp.org](https://www.3gpp.org/dynareport/32299.htm)
[4] [https://www.tech-invite.com](https://www.tech-invite.com/3m32/toc/tinv-3gpp-32-299_a.html)
[5] [https://www.arib.or.jp](https://www.arib.or.jp/english/html/overview/doc/STD-T63V9_21/5_Appendix/Rel6/32/32299-6c0.pdf)
[6] [https://www.3gpp.org](https://www.3gpp.org/ftp/tsg_sa/wg5_tm/TSGS5_128/SA_86/32240-g10.doc#:~:text=A%20set%20of%20TSs%20in%20the%20TS,is%20outlined%20in%20the%20following%20figure%201.1:)
[7] [https://docs.oracle.com](https://docs.oracle.com/en/industries/communications/converged-application-server/8.2/diameter/overview-ro-interface-support.html)
[8] [https://docs.oracle.com](https://docs.oracle.com/cd/E29542_01/doc.1111/e15461/diameter_4.htm)
[9] [https://www.etsi.org](https://www.etsi.org/deliver/etsi_ts/132200_132299/132296/12.03.00_60/ts_132296v120300p.pdf)
[10] [https://docs.oracle.com](https://docs.oracle.com/cd/E17645_01/doc.50/e17648/dia_diameter_ro.htm)
[11] [https://docs.oracle.com](https://docs.oracle.com/cd/E13153_01/wlcp/wlss40/diameter/diameterro.html)
[12] [https://docs.oracle.com](https://docs.oracle.com/cd/E29542_01/doc.1111/e15461/diameter_4.htm)
[13] [https://www.gl.com](https://www.gl.com/newsletter/diameter-protocol-simulator-gy-ro-interface-newsletter.html)


That is a very common way to distinguish them in practice, though technically it's more about where the trigger happens in the network architecture.
While both interfaces use the same underlying Diameter protocol (defined in 3GPP TS 32.299), they serve different parts of the network:
1. Gy Interface (Data / Packet Core)
The Gy interface is primarily used for Data (Packet Switched domain).

* Location: It sits between the PCEF (Policy and Charging Enforcement Function), usually located in the PGW (PDN Gateway) or GGSN, and the OCS (Online Charging System).
* Purpose: It monitors data volume (MBs), time, or specific service events as the user browses the web or uses apps.
* Key Focus: Volume-based and Time-based charging.

2. Ro Interface (Voice & Services / IMS)
The Ro interface is primarily used for Voice and IMS services.

* Location: It sits between the CTF (Charging Trigger Function) in the IMS core (like the S-CSCF or AS - Application Server) and the OCS.
* Purpose: It handles charging for VoLTE calls, SMS over IMS, and supplementary services (like call forwarding).
* Key Focus: Duration-based charging (minutes) and Event-based charging (per SMS).

------------------------------
Comparison Summary

| Feature | Gy Interface | Ro Interface |
|---|---|---|
| Primary Use Case | Mobile Data / Internet | VoLTE / IMS Voice / SMS |
| Network Node | PGW / GGSN (PCEF) | CSCF / AS (IMS) |
| Charging Metric | Volume (MB/GB) or Time | Duration (Seconds/Minutes) or Events |
| Protocol Base | Diameter (RFC 4006) | Diameter (RFC 4006) |

A simple way to remember it:

* Gy = Gateway (PGW) / GPRS (Legacy data).
* Ro = Real-time operations for IMS services.

Would you like to see a breakdown of the specific AVPs (Attribute-Value Pairs) that differ between a data session on Gy and a voice call on Ro?


