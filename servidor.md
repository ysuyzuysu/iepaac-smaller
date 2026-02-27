## Servidor MQTT i Node-RED

### Configuració i adreçes:
- IP del servidor: 192.168.223.50  
- Node-RED: http://192.168.223.50:1880
- Mosquitto:
    - IP del servidor: 192.168.223.50
    - Port: 1883
    - Canal principal: ado
        - Canal pH: ph
        - Canal potenciometre: pot
- Influxdb: http://192.168.223.50:8086
 
### Materials:
- Raspberry Pi 5 amb Ubuntu Server 24.04
- Un client per fer probes

---

### Proces per a insta·lar MQTT:
El primer que tendriem que fer seria actualitzar el sistema amb:  
sudo apt update && sudo apt upgrade  
  
A continuació tindriem que tenir el sistema amb una IP fixa, com per exemple, en el meu cas la .50  
  
Seguidament tendriem que instal·lar el Mosquitto i el Mosquitto-Clients:  
sudo apt install mosquitto mosquitto-clients -y  
  
Comprobem que el servei esta actiu i no dona cap error:  
sudo systemctl status mosquitto  
  
Ja tendiriem el MQTT instal·lat, la primera configuració seria al fitxer:  
/etc/mosquitto/conf.d/default.conf  
  
Dins d'aquest fitxer tindriem que afegir el següent:  
listener 1883  
protocol mqtt  
allow_anonymous true  
  
I reinciem el servei:  
sudo systemctl restart mosquitto  

Ja tindriem instal·lat el mosquitto, per comprobar la seva connexió obrim el client i instal·lem els clients de mosquitto:  
sudo apt install mosquitto-client  
  
Cuan ja el tenim instal·lat al client, ens subsribim a un canal, com si fos un servidor de Discord:  
mosquitto_sub -h la.nostra.ip -p 1883 -t canal  
en el meu cas:  
mosquitto_sub -h 192.168.223.50 -p 1883 -t ado  
I ja estariem subsrits.  
  
Tornem al servidor Ubuntu i fem la prova creant un missatge al canal que s'ha subscrit el client:  
mosquitto_pub -h la.nostra.ip -p 1883 -t canal -m "missatge"  
en el meu cas:  
mosquitto_pub -h 192.168.223.50 -p 1883 -t ado -m "hola"  
  
I ja tendriem el servidor MQTT amb les proves fetes!!  
  
---
  
### Proces per a insta·lar Node-RED:  
El primer que tendriem que fer seria actualitzar el sistema amb:  
sudo apt update && sudo apt upgrade  
  
Seguidament de instal·lar el nodejs amb:  
sudo apt install -y nodejs  
  
Per comprovar podriem mirar la versió instal·lada de node i de npm amb:  
node -v   
i  
npm -v  
  
Instal·lem Node-Red amb:   
npm install -g --unsafe-perm node-red  
I també el Node-Red-Admin amb:  
npm install -g --unsafe-perm node-red-admin  
  
I comprovem l'estat amb:  
node-red  
  
OPCIONAL: Si volem utlitzar el node-red com un servei tindriem que fer la següent configuració:  
Creem un fitxer a la següent direcció:  
sudo nano /etc/systemd/system/nodered.service  
  
I posem el següent text:  
  
[Unit]  
Description=Node-RED  
After=network.target  
  
[Service]  
ExecStart=/usr/bin/env node-red  
WorkingDirectory=/home/ado (aqui posarieu el vostre usuario en compte de ado)  
User=ado (aqui posarieu el vostre usuario en compte de ado)  
Group=ado (aqui posarieu el vostre usuario en compte de ado)  
Restart=on-failure  
KillSignal=SIGNIT  
  
[Install]  
WantedBy=multi-user.target  
  
Per seguir fariem:  
sudo systemctl daemon-reload  
sudo systemctl enable nodered.service  
sudo systemctl start nodered.service  
  
I per comprobar si funciona:  
sudo systemctl status nodered.service  
  
Per accedir a la pagina web del nostre node-red l'unic que tindriem que fer es, accedir per un client amb navegador web que estigui amb connexió amb el nostre servidor i posar el següent al buscar d'adreçes:  
  
http://la.nostra.ip:1880  
  
en el meu cas:  
  
http://192.168.223.50:1880  
  
I ja tendirem el nostre servei Node-Red funcionant!!

<img width="1916" height="912" alt="image" src="https://github.com/user-attachments/assets/2abc36a3-ebcd-4f30-bda2-feb455f93495" />


### Proces per a insta·lar Influxdb: 
Token:
PsI5qkcST2aQDvXlFru7pysFGo86BN87FNjFK-hTPmZKyuE4GiMgmSNxJNFKz3euQrXzOlr5LJDw-m19N4osPg==

