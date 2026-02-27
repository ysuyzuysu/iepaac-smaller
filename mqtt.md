## Servidor MQTT

### Configuració i adreçes:
- IP del servidor: 192.168.223.50  
- Node-RED: http://192.168.223.50:1880
- Mosquitto:
    - IP del servidor: 192.168.223.50
    - Port: 1883
    - Canal principal: ado
        - Canal pH: ph
        - Canal potenciometre: pot
 
### Materials:
- Raspberry Pi 5 amb Ubuntu Server 24.04
- Un client per fer probes

---

### Proces per a insta·lar MQTT:
El primer que tendriem que fer seria actualitzar el sistema amb:  
```bash
sudo apt update && sudo apt upgrade  
```
A continuació tindriem que tenir el sistema amb una IP fixa, com per exemple, en el meu cas la .50  
  
Seguidament tendriem que instal·lar el Mosquitto i el Mosquitto-Clients:  
```bash
sudo apt install mosquitto mosquitto-clients -y  
```
Comprobem que el servei esta actiu i no dona cap error:  
```bash
sudo systemctl status mosquitto  
```
Ja tendiriem el MQTT instal·lat, la primera configuració seria al fitxer:  
```bash
/etc/mosquitto/conf.d/default.conf  
```
Dins d'aquest fitxer tindriem que afegir el següent:  
```bash
listener 1883  
protocol mqtt  
allow_anonymous true  
```  
Reinciem el servei:  
```bash
sudo systemctl restart mosquitto  
```
Ja tindriem instal·lat el mosquitto, per comprobar la seva connexió obrim el client i instal·lem els clients de mosquitto:  
```bash
sudo apt install mosquitto-client  
```
Cuan ja el tenim instal·lat al client, ens subsribim a un canal, com si fos un servidor de Discord:  
```bash
mosquitto_sub -h la.nostra.ip -p 1883 -t canal  
```
en el meu cas:  
mosquitto_sub -h 192.168.223.50 -p 1883 -t ado  
Ja estariem subsrits.  
  
Tornem al servidor Ubuntu i fem la prova creant un missatge al canal que s'ha subscrit el client:  
```bash
mosquitto_pub -h la.nostra.ip -p 1883 -t canal -m "missatge"  
```
en el meu cas:  
mosquitto_pub -h 192.168.223.50 -p 1883 -t ado -m "hola"  
  
Ja tendriem el servidor MQTT amb les proves fetes!!  
  
---






