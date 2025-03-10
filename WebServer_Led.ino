#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-AP";  
const char* password = "1234";      

WebServer server(80);  // Cria o servidor na porta 80

#define LED 2  // Pino do LED

// Página principal do servidor
void handleRoot() {
    String html = "<h1>Controle de LED com ESP32</h1>";
    html += "<p><a href='/on'><button style='font-size:20px;'>Ligar LED</button></a></p>";
    html += "<p><a href='/off'><button style='font-size:20px;'>Desligar LED</button></a></p>";
    server.send(200, "text/html", html);
}


void handleLEDOn() {
    digitalWrite(LED, HIGH);
}


void handleLEDOff() {
    digitalWrite(LED, LOW);
}

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(115200);

    // Configurar ESP32 como Access Point (AP)
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("ESP32 IP: ");
    Serial.println(IP);

    // Definir rotas do servidor
    server.on("/", handleRoot);
    server.on("/on", handleLEDOn);
    server.on("/off", handleLEDOff);
    server.begin();
    Serial.println("Servidor iniciado...");
}

void loop() {
    server.handleClient(); // Mantém o servidor ativo
}
