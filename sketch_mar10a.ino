#include <WiFi.h>

// --- CONFIGURATION RÉSEAU ---
const char* ssid = "NIRYONED1";
const char* password = "niryorobot";
const char* host = "10.10.10.10";
const int port = 5005;

IPAddress local_IP(10, 10, 10, 60);
IPAddress gateway(10, 10, 10, 10);
IPAddress subnet(255, 255, 255, 0);

const int EMG_PIN = 34;

// --- PARAMÈTRES (À ajuster en regardant le graphique) ---
int SEUIL_ACTION = 2500; // Le pic pour déclencher l'action
int SEUIL_REPOS = 1500;  // Le niveau où on considère le muscle détendu

// --- VARIABLES D'ÉTAT ---
bool pinceFermee = false;        // L'état actuel de la pince
bool contractionEnCours = false; // Le "verrou" anti-répétition

void setup() {
    Serial.begin(115200);
    analogReadResolution(12);

    // Connexion WiFi
    WiFi.config(local_IP, gateway, subnet);
    WiFi.mode(WIFI_STA);
    WiFi.setMinSecurity(WIFI_AUTH_WPA_PSK);
    WiFi.begin(ssid, password);

    // Attente de la connexion (Le traceur série ignorera ces points)
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n✅ Connecté ! Robot + Graphique activés.");
}

void loop() {
    WiFiClient client;
    int emgValue = analogRead(EMG_PIN);

    // ==========================================
    // 1. LOGIQUE DE DÉCISION & ENVOI AU ROBOT
    // ==========================================
    
    // Détection d'un nouveau pic d'effort
    if (emgValue > SEUIL_ACTION && !contractionEnCours) {
        contractionEnCours = true; // On verrouille
        
        pinceFermee = !pinceFermee; // On inverse l'état de la pince

        // Envoi de l'ordre au robot
        if (client.connect(host, port)) {
            if (pinceFermee) {
                client.print("CLOSE");
            } else {
                client.print("OPEN");
            }
            client.stop();
        }
        // Grosse pause pour le robot. 
        // Note: Le graphique va "figer" pendant une demi-seconde ici, c'est normal !
        delay(500); 
    }
    
    // Détection du relâchement total du muscle
    else if (emgValue < SEUIL_REPOS && contractionEnCours) {
        contractionEnCours = false; // On déverrouille le système
        delay(50);
    }


    // ==========================================
    // 2. AFFICHAGE POUR LE TRACEUR SÉRIE
    // ==========================================
    
    // On crée une valeur (0 ou 4000) pour voir l'état de la pince sur l'écran
    int etatPinceGraphique = pinceFermee ? 4000 : 0;

    // Format strict pour le Traceur Série : "Nom:Valeur, Nom:Valeur"
    Serial.print("Signal_Brut:");
    Serial.print(emgValue);
    Serial.print(",");
    
    Serial.print("Seuil_Action:");
    Serial.print(SEUIL_ACTION);
    Serial.print(",");
    
    Serial.print("Seuil_Repos:");
    Serial.print(SEUIL_REPOS);
    Serial.print(",");
    
    Serial.print("ETAT_PINCE:");
    Serial.println(etatPinceGraphique);

    delay(20); // Lecture à 50Hz pour un graphique fluide
}