# 🦾 Robot Control via Electromyographic (EMG) Signals

Ce projet, réalisé dans le cadre de la deuxième année d'ingénieur à l'**ENSEA (Cergy)**, porte sur la conception et la réalisation d'un capteur électromyographique (EMG) complet et l'activation d'un robot par ces signaux. L'objectif est de capturer l'activité électrique des muscles du bras pour permettre, à terme, le contrôle du robot.

## 📌 Présentation du Projet
Le système permet de détecter les signaux bioélectriques de très faible amplitudes émis lors d'une contraction musculaire, de les traiter analogiquement pour les rendre exploitables, puis de les numériser via un microcontrôleur **ESP32**.

### 🛠 Caractéristiques
* **Cible :** Muscles du bras (biceps et ceux de l'avant-bras).
* **Signal d'entrée :** Amplitude de $10\mu\text{V}$ à $5\text{mV}$, fréquence de 10 Hz à 500 Hz.
* **Traitement Analogique :** * Amplification d'instrumentation (Gain élevé).
    * Filtrage passe-bande (élimination du bruit 50 Hz et des hautes fréquences).
    * Redressement et lissage du signal (enveloppe du signal).
* **Numérisation :** ADC de l'ESP32 (échantillonnage et traitement logiciel).

---

## 🏗 Architecture du capteur EMG

Le projet est actuellement divisé en plusieurs blocs:

1.  **Étage de Pré-amplification :** Utilisation d'un amplificateur d'instrumentation pour extraire le signal différentiel des électrodes.
2.  **Filtrage Actif :** Nettoyage du signal pour ne garder que la bande utile de l'EMG.
3.  **Redresseur de précision :** Conversion du signal alternatif en signal continu (enveloppe de contraction).
4.  **Adaptation de tension :** Ajustement du signal (initialement ±15V en simulation) vers une plage 0-3.3V compatible avec l'ESP32.

---
## 🤖 Cahine d'information Capteur --> Robot

Pour piloter le robot, l'information circule à travers les étapes suivantes :

1. **Acquisition :** Captation des micro-tensions sur la peau via les électrodes.
2. **Traitement Analogique :** Traitement via le capteur EMG.
3. **Numérisation :** L'ESP32 convertit le signal analogique en données numériques via son ADC.
4. **Interprétation :** Analyse du seuil de tension pour détecter une contraction ou un relâchement.
5. **Communication :** Envoi des commandes via Bluetooth/Wi-Fi vers le système de contrôle du robot.
6. **Actionnement  :** Le robot exécute le mouvement correspondant (ex: fermeture de la pince).

---
## 🚀 État d'avancement à la mi-parcours (S7)

* ✅ **Étude théorique :** Analyse des signaux EMG et définition des besoins d'amplification.
* ✅ **Choix des composants :** Passage sur des AOP type TL08x pour la réalisation physique.
* ✅ **Conception d'un prototype:** Saisie de schéma et assignation des empreintes (SOIC-8 / 0805) sur KiCad pour soudure au four.
* 🔲 **Poursuite du projet :** Finition du prototype, réalisation du PCB, tests réels avec électrodes et développement du code de traitement sur l'ESP32 (filtres numériques, Bluetooth/Wi-Fi).

---

## 📋 Travail effectué lors du S8
* **Simulation complète du captuer EMG**: Pour palier aux dysfonctionnement du prototype, on a simuler entierment le composant jusqu'à avoir le comportment voulu.
* **Réalisation du PCB**: le capteur et une carte de commande pour assebler tous les éléments
* **Travail informatique**: écriture de code afin de faire bouger le robot en fonction des mouvement (ouverture de la main, contration du muscle).
  
---

## 🔝Evolution de ce projet et axes de développement

  
---

## 📦 Technologies utilisées
* **CAO Électronique :** LTspice, Niryo, KiCad 9.0.
* **Matériel :** ESP32, MyoWear, composants actifs (AOP TL081) et passifs.
* **Langages :** C (Arduino IDE / PlatformIO), ROS\ROS2, Python.

---
