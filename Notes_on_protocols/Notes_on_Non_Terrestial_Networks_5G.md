# Notes on 5G NTN (Non Terrestial Networks)

NTN - Non-terrestial networks refers to satellite and space networks which play a complementing role in 5G terrestial networks

The standards for cellular and satellite interconnection, started in 3gpp release 14, and the  first standard was stated in relase 16. Nevertheless there were companies doing their onw
communication ssytems without attending to the standards (SpaceX) 

3GPP Release 16 served as the foundational feasibility study and architectural definition phase for 5G Non-Terrestrial Networks (NTN), documented under 3GPP TR 38.821 (https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3525)
It established how satellite (GEO, LEO, MEO) and aerial platforms integrate into 5G core and radio access networks before normative specifications were finalized in Release 17

Reference: https://www.rohde-schwarz.com/es/soluciones/satellite-testing/landingpages/white-paper-5g-ntn-takes-flight-technical-overview-of-5g-non-terrestrial-networks_255919.html

## GEO, MEO and LEO

### GEO (Geosynchronous Equatorial Orbit)

 - GSO: Geostationary orbit 
 - GEO: Geosynchronous equatorial orbit, it is a cicular oribit with constatn altitude (35786km) and 
        following the direction of Earth's rotation
		
 GEO features: 
 - High footprint (200-3500km), that implies they have a low throughput
 - They are far from Earth, that implies the hayve high latency (> 440 ms) 
 - Costly to launch
 - They operate in permanent position, so the UE antenna doesn`t need any special technique to compensate for rotation
 - Mainly they are one-direction user cases, mainly downlink (navigation, meterorology)
 - Number of satellites is 3
 - Number of handovers is none 
 
### MEO (Medium Earth Orbit)
 
MEO stands for Medium Earth Orbit, it is acircular orbit between 2000 and 35786 km altitude.

MEO features: 
 - High footprint (150-1500km), so relatively low throuhoput
 - Far from Earth, so high latency (> 240ms)
 - Hard to launch, so high cost
 - Non-fixed poistio, so it needs to compensae for rotation of the UE antenna 
 - user cases, navigation or meteorology
 - number of satellites: 8-20
 - number of handovers: low
 
 ### LEO (Low Earth Orbit)
 
  - Low Earth Orbit is a circular orbit between 300 Km to 2000 Km. 
  - Low footpring (20-1000Km) -> Hight Througput
  - Low to Earth -> Low Latency (circa 40 ms)
  - Easy to launch, and thus because it is low coset
  - No fix position, tha timplies that it is needed rotation for the UE antenna.
  - Bi-directional user cases: High Data Rate, 5G NTN
  - Number of satellites: > 40
  - Number of handovers: high
  
  About the LEO satellites: 
   - they can focus in different places, thanks to bean forming
   - Fixed or steerable beams with respect to the earch surface (https://www.mdpi.com/2076-3417/13/6/3480)
   - the are small, ...about the size of a washer machine.
   - low cose, around 1 million $ each one-direction
   - Easy to produce


## Key features an challenges

 -Mainly LOs(line of sight) scenarios
 - Larger propagatiion delays
 - extreme doppler shifts (use larger subcarriers spacing, precompensation by ephemeries knowledge, OTFS delays doppler channels)
 - additional attenuations
 - Earth movements
 - Inter-satellite links and networking
 - Elevation angle and elliptical beam coverage
 - Inter-constellation management and interference
 - Terminals, sendind data quit QoS in UL (upload)
 - MobilitY of nodes and terminals
 - Regulatory and security aspects
 
 ### Spectrum for NTN 
 
 NTN Rel 17 provides in 
 
 
