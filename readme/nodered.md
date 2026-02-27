# :bar_chart: *Node-RED*
---
## Proces per a insta·lar Node-RED: 
---
El primer que tendriem que fer seria **actualitzar** el sistema amb:  
```bash
sudo apt update && sudo apt upgrade  
```
Seguidament de instal·lar el **nodejs** amb:  
```bash
sudo apt install -y nodejs  
```
Per comprovar podriem mirar la versió instal·lada de node i de npm amb:  
```bash
node -v   
```
i  
```bash
npm -v  
``` 
**Instal·lem Node-Red** amb:   
```bash
npm install -g --unsafe-perm node-red  
```
També el **Node-Red-Admin** amb:  
```bash
npm install -g --unsafe-perm node-red-admin  
```
Comprovem l'estat amb:  
```bash
node-red  
```
#### OPCIONAL: 
Si volem utlitzar el node-red com un servei tindriem que fer la següent configuració:  
Creem un fitxer a la següent direcció:  
```bash
sudo nano /etc/systemd/system/nodered.service  
```
Posem el següent text:  
```bash 
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
``` 
Per seguir fariem:  
```bash
sudo systemctl daemon-reload  
sudo systemctl enable nodered.service  
sudo systemctl start nodered.service  
```  
Per comprobar si funciona:  
```bash
sudo systemctl status nodered.service  
```
Per accedir a la pagina web del nostre node-red l'unic que tindriem que fer es, accedir per un **client amb navegador web que estigui amb connexió amb el nostre servidor** i posar el següent al buscar d'adreçes:  
```bash  
http://la.nostra.ip:1880  
```  
en el meu cas:  
  
http://192.168.223.50:1880  
  
Ja tendirem el nostre servei Node-Red funcionant!!

<img width="958" height="456" alt="image" src="https://github.com/user-attachments/assets/2abc36a3-ebcd-4f30-bda2-feb455f93495" />

---
## Fluxos principals Node-RED: 
---
* ### Llegir dades i crear un fitxer .json de ado/pot

<img width="714" height="231" alt="image" src="https://github.com/user-attachments/assets/13f997f6-c95b-402c-a3f8-2c8d6c941bd4" />

Dins de un fluxe tindrem que afegir:
 * 1 mqtt in
 * 1 debug
 * 1 function
 * 1 escribir archivo (file)

Configuració del mqtt in:  

Farem dos clics sobre el node mqtt in per editar-lo, afegirem un nou servidor clicant al "+", i aqui tindriem que afegir la ip del servidor mqtt o si es el mateix servidor que aon esta el node-red, podriem ficar **localhost**

<img width="548" height="51" alt="image" src="https://github.com/user-attachments/assets/6a22eef6-1b50-47e2-9089-ea474c45e5de" />














