# Notes on SS7

 - reference: https://web.archive.org/web/20150722061655/http://www.informit.com/library/library.aspx?b=Signaling_System_No_7
 - reference: https://www.itu.int/ITU-T/recommendations/rec.aspx?rec=15042

Signalling system No. 7 (SS7) is a stack of signalling protocols, which was initially developed by ITU (CCITT) in the 1980s. Since then, SS7 standards have become a
generic stack which is widely applied in public switched telephone networks (PSTNs) all over the world. With the growth of mobile telecommunications and the appearance
of the mobile application part (MAP) and Camel application part (CAP) protocols, SS7 stack became suitable for public land mobile networks (PLMNs), e.g., 2G, 3G networks.
Later, SS7 migrated to the signalling transport or SIGTRAN stack developed by the Internet Engineering Task Force (IETF) which allows operators to set
up interconnection of SS7-based networks over Internet protocol (IP) networks. Furthermore, the SS7 logic migrated to Diameter signalling protocol which is
currently widely used for interconnection of IP multimedia subsystem (IMS)-based networks, including 4G (VoLTE/ViLTE).

At the development stage, SS7 was designed to be managed by operators with the understanding that anyone connected to the SS7 network was considered trustworthy. 
With the current network environment, including interconnection over the Internet, SS7-based networks have become vulnerable and can be easily attacked. Moreover,
the latest move to Diameter protocol has not solved any of the basic vulnerabilities found in SS7.

Presently, there have been multiple cases where SS7 vulnerabilities have been used for different hackers' attacks. Amongst well-known attacks on SS7 networks 
include telephone spam, spoofing numbers, location tracking, subscriber fraud, intercept calls and messages, denial of service (DoS), infiltration attacks,
routing attacks, etc.

The goal of Recommendation ITU-T Q.3062 is to define the signalling requirements for authentication of signalling messages, in order for operators to be able 
to verify the authenticity of signalling exchanges based on an accepted trust anchor. This Recommendation includes codes and signalling procedures based on Recommendation ITU-T Q.3057.

Other references:
 - https://www.mcmsnj.net/cms/lib07/nj01911694/centricity/domain/134/ss7_protocol_overview.pdf
 - https://www.patton.com/whitepapers/intro_to_ss7_tutorial.pdf
 - https://www.synway.net/Download/Brochure/SS7_Datasheet.pdf
 - https://www.etsi.org/deliver/etsi_i_ets/300300_300399/30037401/01_60/ets_30037401e01p.pdf
 - https://www.etsi.org/deliver/etsi_en/301100_301199/30114005/01.01.01_20/en_30114005v010101c.pdf
