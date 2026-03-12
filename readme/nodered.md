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

i després a **Administrar paleta**

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
<br/>
<br/>
<br/>

---

* ## Telegram Bot:
<img width="843" height="237" alt="image" src="https://github.com/user-attachments/assets/a7eb5026-00f2-46ca-9e35-ae5c4ab4b6af" />

Dins de un fluxe tindrem que afegir:
 * 2 mqtt in
 * 3 function
 * 1 sender
 * 1 reciver
<br/>
<br/>

* #### Insta·lar paleta de Telegram Bot a Node-Red
Anem al **menú**, 

<img width="44" height="30" alt="image" src="https://github.com/user-attachments/assets/42c9bb4c-34c6-497a-871a-2a02b73ad03c" />

i després a **Administrar paleta**

<img width="165" height="28" alt="image" src="https://github.com/user-attachments/assets/fd99d578-0cd2-4913-bd33-6cdb36f3d927" />

Anem al cercador a l'apartat de **Instalar**, i cerquem ***Telegram***

<img width="675" height="80" alt="image" src="https://github.com/user-attachments/assets/a07d65cb-4273-4a8c-bfc3-f3982a64672e" />
<br/>

* #### Configuració de les dades de ado/pot:
Aprofitem el mqtt in creat al fluxe 1

<img width="548" height="51" alt="image" src="https://github.com/user-attachments/assets/6a22eef6-1b50-47e2-9089-ea474c45e5de" />  

<img width="757" height="218" alt="image" src="https://github.com/user-attachments/assets/d58f9262-c2c2-4424-98bf-ff0437f6003e" />

<img width="545" height="158" alt="image" src="https://github.com/user-attachments/assets/96dd0619-a97b-4322-aead-896395aadc00" />
<br/>
<br/>

Afegim un node function, el connectem al mqtt in de ado/pot i l'editem per preparar les dades per al bot, fem doble clic sobre el function i posem el següent codic
El nostre codic:
```
global.set("pot", msg.payload);
return null;
```
<img width="768" height="212" alt="image" src="https://github.com/user-attachments/assets/edb146fe-10eb-4df6-a36e-778e7812175a" />
<br/>
<br/>

* #### Configuració de les dades de ado/ph:
Aprofitem el mqtt in creat al fluxe 2

<img width="553" height="49" alt="image" src="https://github.com/user-attachments/assets/3d88e5ad-dddb-4269-a48c-d358b32f0708" />
<br/>
<br/>

Afegim un node function, el connectem al mqtt in de ado/ph i l'editem per preparar les dades per al bot, fem doble clic sobre el function i posem el següent codic
El nostre codic:
```
global.set("ph", msg.payload);
return null;
```
<img width="585" height="213" alt="image" src="https://github.com/user-attachments/assets/a2e728f9-55d3-490b-baf5-5b983068b04b" />
<br/>
<br/>

* #### Configuració del bot a telegram:
Anem al nostre compte de telegram i busquem al cercador BotFather:

<img width="459" height="87" alt="image" src="https://github.com/user-attachments/assets/baa865a7-9ab4-46fb-91ff-49ee5c96ef8b" />

Entrem al chat i posem **/newbot**

<img width="183" height="57" alt="image" src="https://github.com/user-attachments/assets/68e23e18-7818-40d8-93e8-aa7f90adb7cc" />

Despres ens demanara un nom per al bot

<img width="881" height="122" alt="image" src="https://github.com/user-attachments/assets/748331a8-50c8-4523-952b-4d7d780ae8b0" />

I per últim un username per al bot

<img width="884" height="127" alt="image" src="https://github.com/user-attachments/assets/60e02a48-b81f-4a5b-8485-4c4aa05d252f" />

I per finalitzar tenim que copiar el token que ens dona, que es la "id" del bot
<br/>

* #### Configuració del bot a Node-Red:
Afegim un node de **Telegram Reciver**, agregat de la paleta Telegram Bot anteriorement i li fem doble clic, i clicarem al **"+"**

<img width="545" height="54" alt="image" src="https://github.com/user-attachments/assets/e77e354c-08b8-4328-b25f-f2511bc1147c" />

Després posarem el nom del bot i el token que hem copiat antes

<img width="773" height="119" alt="image" src="https://github.com/user-attachments/assets/8f9b4d1b-ea94-43f5-82bb-cc85e74be1ea" />

Connectem un node function al reciver i posem el següent, per preparar les respostes al chat
```
let texto = msg.payload.content.toLowerCase();

if (texto.includes("pot")) {
    let pot = global.get("pot") || "No disponible";
    
    msg.payload.content = " Pot actual: " + pot + " V";
    return msg;
}

if (texto.includes("ph")) {
    let ph = global.get("ph") || "No disponible";
    
    msg.payload.content = " pH actual: " + ph;
    return msg;
}

return null;
```

<img width="766" height="538" alt="image" src="https://github.com/user-attachments/assets/630463f9-998d-4f42-a2ac-1597716d98b6" />
<br/>

I per últim ho connectem a un **Telegram Sender** i posem el bot creat anteriorment

<img width="552" height="120" alt="image" src="https://github.com/user-attachments/assets/09242d3a-9384-4c07-8482-b0716d9cb3e5" />
<br/>
<br/>

* #### Comprovació del bot a Telegram:
Busquem el nostre bot a telegram, o obrim el enllaç que ens dona BotFather

<img width="469" height="99" alt="image" src="https://github.com/user-attachments/assets/94bd4be0-0bc6-4384-a815-bf95cb220e3f" />
<br/>

I després escrivim al chat el que volem saber, dacord amb la configuració dels function, per exemple cuan io escric ***pot*** ens diu els valors del potenciometre

<img width="886" height="106" alt="image" src="https://github.com/user-attachments/assets/19604e0c-8cef-405c-bcbe-028c231875eb" />

o del pH

<img width="896" height="110" alt="image" src="https://github.com/user-attachments/assets/f8e405fc-0f32-4514-bccf-9af8058441ca" />



















