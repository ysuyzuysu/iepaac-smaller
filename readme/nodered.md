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
* ## Llegir dades i crear un fitxer .json de ado/pot

<img width="714" height="231" alt="image" src="https://github.com/user-attachments/assets/13f997f6-c95b-402c-a3f8-2c8d6c941bd4" />

Dins de un fluxe tindrem que afegir:
 * 1 mqtt in
 * 1 debug
 * 1 function
 * 1 escribir archivo (file)
<br/>
<br/>
  

* #### Configuració del mqtt in:
Farem dos clics sobre el node mqtt in per editar-lo, afegirem un nou servidor clicant al "+"  
<img width="548" height="51" alt="image" src="https://github.com/user-attachments/assets/6a22eef6-1b50-47e2-9089-ea474c45e5de" />  

Aqui tindriem que afegir la **ip del servidor mqtt** o si es el mateix servidor que aon esta el node-red, podriem ficar **localhost**
<img width="757" height="218" alt="image" src="https://github.com/user-attachments/assets/d58f9262-c2c2-4424-98bf-ff0437f6003e" />

Per finalitzar este node, tenim que afegir el tema al que volem que estigue escoltant, en el meu cas **ado/pot**
<img width="545" height="158" alt="image" src="https://github.com/user-attachments/assets/96dd0619-a97b-4322-aead-896395aadc00" />
<br/>
<br/>
<br/>

* #### Configuració del debug:

Farem dos clics sobre un node debug per a configurar-lo, sols tenim que ficar que envie el missatge per panatalla en **msg.payload**
<img width="547" height="103" alt="image" src="https://github.com/user-attachments/assets/b7852702-d7ae-4022-af63-f34b3a97f8e6" />
<br/>
<br/>
<br/>

* #### Configuració del Function:

Farem dos clics sobre el node function que serveix per a **definir quin format tindran les dades** al nostre .json
El nostre codic:
```
let data = {
    timestamp: new Date().toISOString(),
    topic: msg.topic,
    payload: msg.payload
};

msg.payload = JSON.stringify(data) + "\n";
return msg;
```
<img width="771" height="334" alt="image" src="https://github.com/user-attachments/assets/51f32ca4-4249-4e8c-841e-a2c8d88c6401" />
<br/>
<br/>
<br/>

* #### Configuració del .json:

Al fer dos clics a un node de **Escribir archivo**, entrem a la configuració i posem la ruta del nostre archiu on volem que en guarde l'informació, si no l'hem creat li podem dir que el cree i important posar **Ajuntar al archivo** perque sino s'esborrara cada cop. També posar que cada cop **s'ajunte a una nova linea /n**

<img width="605" height="247" alt="image" src="https://github.com/user-attachments/assets/e79944be-794a-428e-9a2c-6208a68fd44f" />
<br/>
<br/>
<br/>
<br/>

---

* ## Llegir dades i crear un fitxer .json de ado/ph

<img width="635" height="181" alt="image" src="https://github.com/user-attachments/assets/027773e2-9c9f-44a3-8192-e532900dc6a0" />

Dins de un fluxe tindrem que afegir:
 * 1 mqtt in
 * 1 debug
 * 1 function
 * 1 escribir archivo (file)

Per a aquest fluxe, sols tindrem que canviar dos configuracions molt sencilles, aixi que primer que tot, copiarem tot el fluxe anterior.
<br/>
<br/>


* #### Configuració del mqtt in:

En aquest node, sols cambiarem el tema ado/pot per **ado/ph**

<img width="553" height="49" alt="image" src="https://github.com/user-attachments/assets/3d88e5ad-dddb-4269-a48c-d358b32f0708" />
<br/>
<br/>
<br/>

* #### Configuració del .json:

En aquest node, canviarem sols la **ruta del archiu**, o el nom del archiu

<img width="288" height="56" alt="image" src="https://github.com/user-attachments/assets/99b6bb0a-6870-470f-ac7a-dd331e9cb48a" />
<br/>
<br/>
<br/>
<br/>

---

* ## Dashboard web de Node-Red

<img width="535" height="174" alt="image" src="https://github.com/user-attachments/assets/6a515e39-5831-47e7-a9d4-b4e0c58fc85f" />

Dins de un fluxe tindrem que afegir:
 * 2 mqtt in
 * 2 budge
<br/>
<br/>

* #### Insta·lar paleta de Dashboard a Node-Red
Anem al **menú**, 

<img width="44" height="30" alt="image" src="https://github.com/user-attachments/assets/42c9bb4c-34c6-497a-871a-2a02b73ad03c" />

i després a **Administrar paleta***

<img width="165" height="28" alt="image" src="https://github.com/user-attachments/assets/fd99d578-0cd2-4913-bd33-6cdb36f3d927" />

Anem al cercador a l'apartat de **Instalar**, i cerquem ***Dashboard***

<img width="690" height="238" alt="image" src="https://github.com/user-attachments/assets/91d07152-6ac4-4615-becc-e57c19292821" />
<br/>
<br/>
<br/>


* #### Configuració del Dashboard de ado/pot:
Aprofitem el mqtt in creat al fluxe 1

<img width="548" height="51" alt="image" src="https://github.com/user-attachments/assets/6a22eef6-1b50-47e2-9089-ea474c45e5de" />  

<img width="757" height="218" alt="image" src="https://github.com/user-attachments/assets/d58f9262-c2c2-4424-98bf-ff0437f6003e" />

<img width="545" height="158" alt="image" src="https://github.com/user-attachments/assets/96dd0619-a97b-4322-aead-896395aadc00" />
<br/>
<br/>

Afegim un node **Gauge** i fem doble clic, verem que a la dreta del tot de Group surt un simbol de **+**, li fem clic

<img width="605" height="215" alt="image" src="https://github.com/user-attachments/assets/d7bf8a59-1f37-4548-a3ec-ebe438d2181f" />
<br/>

Després a la dreta del tot de Tab, li tornem a donar al **+**

<img width="574" height="117" alt="image" src="https://github.com/user-attachments/assets/6771b010-3b47-46b7-8547-5400ee8abde3" />
<br/>

Li posem el nom que volguessim

<img width="569" height="119" alt="image" src="https://github.com/user-attachments/assets/eb682e4e-b3a9-41c7-b398-ceb36bf6387b" />
<br/>

Li fiquem un nom i seleccionem el Tab creat anteriorment

<img width="561" height="123" alt="image" src="https://github.com/user-attachments/assets/fd3128a2-7a48-412a-ab77-64108f04ac5f" />
<br/>

I per últim seleccionem el Group que hem creat anteriorment, i el configurem com volem, el nom, valors, etc

<img width="569" height="558" alt="image" src="https://github.com/user-attachments/assets/ca18b22f-e026-4e7a-bdaa-194da147aeb7" />













