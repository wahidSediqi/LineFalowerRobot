# Line Follower Robot Prosjekt konsept 3
# programmet ligger i src mappe.
## Oversikt

Denne README gir en oversikt over et Line Follower Robot-prosjekt som bruker en Arduino Mega, en H-bro L298N motor
driver, to motorer, en 8-kanals sensor-array og et 9V batteri for å forsyne motorstyringen med strøm. Prosjektet er
avhengig av Pololu QTR Reflectance Sensors-biblioteket for programmering av linjefølgende oppførsel.


## Prosjekt Komponenter

- **Arduino Mega**: Hjernen bak prosjektet, brukt for å kontrollere motorer og behandle sensordata.

- **H-Bro L298N Motor Driver**: Denne motorstyringen tillater todireksjonskontroll av to likestrømsmotorer, og gir
  muligheten til å bevege roboten fremover, bakover, til venstre og til høyre.

- **To Motorer**: Robotens bevegelse oppnås gjennom disse to likestrømsmotorene. Retningen og hastigheten til motorene
  kontrolleres av Arduino og motorstyringen.

- **8-Kanal Sensor Array**: Disse sensorene brukes til å oppdage posisjonen til en linje på bakken. De gjør det mulig
  for roboten å følge en forhåndsdefinert bane ved å lese og behandle dataene fra sensorene.

- **9V Batteri**: Dette batteriet gir strøm til motorstyringen og sikrer at motorerne har en separat strømkilde fra
  Arduino for å forhindre spenningsstigninger.

- **Pololu QTR Reflectance Sensors Library**: Dette biblioteket gir nødvendige funksjoner og verktøy for samhandling med
  og kalibrering av refleksjonssensorene. Det gjør at roboten kan ta beslutninger basert på sensordata, slik at den kan
  følge linjer nøyaktig.

## Hvordan Roboten Fungerer

1. **Sensor Kalibrering**: Før roboten kan følge linjer, må den kalibrere sensorene for å skille mellom linjen og
   bakgrunnen. Dette gjøres vanligvis i begynnelsen av hver kjøring.

2. **Behandling av Sensordata**: Arduino leser data fra 8-kanals sensor-array og behandler dem for å fastslå linjens
   posisjon. Ved å sammenligne sensormålingene kan roboten justere retningen sin for å holde seg på linjen.

3. **Motor Kontroll**: Basert på sensordata sender Arduino kommandoer til H-bro L298N motorstyringen for å kontrollere
   motorerne. Den justerer motorhastigheten og retningen for å holde roboten på linjen.

4. **Tilbakekoplingsløkke**: Roboten gjentar kontinuerlig prosessen med å lese sensordata, behandle dem og kontrollere
   motorerne, og oppretter dermed en tilbakekoplingsløkke som gjør at den kan følge linjen autonomt.

## Prosjektoppsett

1. **Maskinvaretilkoblinger**: Sørg for at motorerne, sensor-arrayen, Arduino Mega og H-bro L298N motor driver er riktig
   tilkoblet i henhold til ditt prosjekts skjema.

2. **Arduino IDE**: Forsikre deg om at du har Arduino IDE installert på datamaskinen din.

3. **Installasjon av Bibliotek**: Installer Pololu QTR Reflectance Sensors-biblioteket i Arduino IDE.

4. **Opplasting av Kode**: Last opp Arduino-koden (skisse) til Arduino Mega. Denne koden bør inkludere nødvendige
   funksjoner for å lese sensordata, behandle dem og kontrollere motorerne.

5. **Sensor Kalibrering**: Før du starter roboten, følg kalibreringsprosedyren i koden for å sette sensortersklene for
   ditt spesifikke miljø.

6. **Slå på Strøm**: Slå på roboten ved å koble 9V-batteriet til motorstyringen. Forsikre deg om at Arduino også er
   tilkoblet strøm.

7. **Testing**: Plasser roboten på en linje eller bane du vil at den skal følge, og observer oppførselen. Gjør
   eventuelle nødvendige justeringer i koden for å forbedre nøyaktigheten i linjefølgingen.

## Programvare og Designverktøy

1. **Programvare**: Prosjektet ble programmert ved hjelp av Platform IO i Clion IDE.

2. **3D-Design**: 3D-tegningene ble opprettet ved hjelp av Fusion 360.

3. **Koblingsdiagram**: Koblingsdiagrammet ble opprettet ved hjelp av Tinkercad og circuito.io.

## Feilsøking

Hvis roboten ikke følger linjen riktig, kan det være nødvendig å justere sensor kalibreringen, finjustere motorstyringen
eller gjøre endringer i koden for å passe ditt miljø og dine krav.

## Ressurser

- [Pololu QTR Reflectance Sensors Library](https://github.com/pololu/qtr-sensors-arduino#arduino-library-for-the-pololu-qtr-reflectance-sensors)

- [Arduino Offisiell Nettside](https://store.arduino.cc/products/arduino-mega-2560-rev3?queryID=undefined)

- [Platform IO](https://platformio.org/)

## kontakt informasjon

- Wahid Sediqi
- wahidas@stud.ntnu.no
