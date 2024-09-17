# COMMENT-FABRIQUER-UN-EFFAROUCHEUR-DFTA141 : https://youtu.be/kzmnxiJcb9Q
Ce dispositif est basé principalement sur l’emploi d’un capteur PIR (capteur infrarouge pyrométrique), dans notre cas il s’agit du HC-SR501. Il doit être alimenté en 5V et il possède une sortie passant au niveau HIGH lorsqu’il a détecté la présence d’une personne ou d’un animal.
Cet effaroucheur est un dispositif très simple monté sur une petite plaquette électronique.
Il est absolument inoffensif. Au départ je l’avais conçu pour dissuader un petit écureuil qui voulait s’approprier les tomates du potager de mon épouse.
Ce dispositif est basé principalement sur l’emploi d’un capteur PIR (capteur infrarouge pyrométrique), dans notre cas il s’agit du HC-SR501. Il doit être alimenté en 5V et il possède une sortie passant au niveau HIGH (3.3V) lorsqu’il a détecté la présence d’une personne ou d’un animal.

Analyse du schéma :
Le Seeeduino XIAO (U1) reçoit la sortie du PIR sur sa borne7 (A6/D6). Si les conditions sont présentes cad D4 et D6 à l’état HIGH, il enclenchera le scénario « NEOPIXEL» des LEDs adressables .
Si de plus D6, D3 et D4 sont à l’état HIGH, il enclenchera en supplément le bruiteur AD9833 (U3) dont le signal est amplifié par un amplificateur de classe D PAM8403 (U2) pour actionner un Haut-parleur.
Une LDR (résistance diminuant avec la luminosité) LDR03 permettra de bloquer automatiquement le bruiteur en cas de pénombre (la nuit par exemple), mais cette fonction de détection de pénombre peut être forcée par la position inhibition sur J1.
Nota : si l’on souhaite que la pénombre ne doive pas bloquer le bruiteur, il suffira de court circuiter cette résistance. Un emplacement a été ajouté dans ce but sur le PCB (cet emplacement possède des PADS de diamètre de 1,2mm pouvant être mis à profit pour y placer des fils permettant de déporter la LDR).
Le bruiteur (U3) peut également être bloqué par sa fonction inhibition sur J2, de même les leds adressables par J3.
Le système peut être alimenté soit en +5V via le bornier J5, le bornier J6 est monté en parallèle et permet de réalimenter un dispositif annexe. Mais ce dispositif peut être également alimenté par via une prise micro USB à droite du PAM803 (U2). 
NOTA : ATTENTION : en cas d’alimentation par un POWER BANK il est possible qu’il se coupe automatiquement en cas de la non utilisation du système. Pour contrecarrer cela il faudra créer une consommation supplémentaire par exemple via le bornier J6. 
Le capteur PIR est connecté via J9 (connecteur JST 3 broches).
Les LEDs adressables (Barette, Ring ou matrice) sont connectées via J10 (connecteur JST 4 broches dont seules 3 sont nécessaires).
Le Haut-parleur est connecté par un bornier à vis J4. Le volume peut être ajusté par RV1.
Un connecteur J8 (JST 2 broches) est mis à disposition afin de pouvoir envoyer le signal audio (aval au potentiomètre de volume) du BRUITEUR vers un ampli de puissance plutôt que sur le PAM8403.
Idem pour J7 mais amont au potentiomètre de volume (RV1).
