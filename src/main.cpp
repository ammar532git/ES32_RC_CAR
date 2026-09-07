#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Define Motor Pins (Connected to L298N)
#define IN1 14 // Left Motor Forward
#define IN2 12 // Left Motor Backward
#define IN3 26 // Right Motor Forward
#define IN4 27 // Right Motor Backward

// Define Enable Pins (Replaces the missing ENA/ENB jumper caps)
#define ENA 32 // Left Motor Enable
#define ENB 33 // Right Motor Enable

WebServer server(80);

// Compact HTML/JS for the Mobile Web App
String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'>"
"<style>.btn{width:80px;height:80px;margin:5px;font-size:18px;border-radius:10px;background:#eee;}</style></head>"
"<body style='background:#222;color:#fff;'><center><h2>RC Control</h2>"
"<table>"
"<tr><td></td><td><button class='btn' ontouchstart='c(\"/F\")' ontouchend='c(\"/S\")'>FWD</button></td><td></td></tr>"
"<tr><td><button class='btn' ontouchstart='c(\"/L\")' ontouchend='c(\"/S\")'>LEFT</button></td>"
"<td><button class='btn' ontouchstart='c(\"/S\")'>STOP</button></td>"
"<td><button class='btn' ontouchstart='c(\"/R\")' ontouchend='c(\"/S\")'>RIGHT</button></td></tr>"
"<tr><td><button class='btn' ontouchstart='c(\"/BL\")' ontouchend='c(\"/S\")'>B-LFT</button></td>"
"<td><button class='btn' ontouchstart='c(\"/B\")' ontouchend='c(\"/S\")'>BWD</button></td>"
"<td><button class='btn' ontouchstart='c(\"/BR\")' ontouchend='c(\"/S\")'>B-RGT</button></td></tr>"
"</table>"
"<script>function c(url){fetch(url);}</script></center></body></html>";

// Function to stop all motors
void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  server.send(200, "text/plain", "Stopped");
}

void setup() {
  // Configure pins as outputs
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  
  // Configure the new Enable pins
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  
  // Turn the motors ON permanently by sending HIGH to ENA/ENB
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  
  // Ensure motors are off at startup
  stopMotors();

  // Start Wi-Fi Access Point
  WiFi.softAP("ESP32_RC_Car", "12345678");

  // Route setup for web server
  server.on("/", []() { server.send(200, "text/html", html); });
  
  server.on("/S", stopMotors); // Stop
  
  server.on("/F", []() { // Forward
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    server.send(200);
  });
  
  server.on("/B", []() { // Backward
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    server.send(200);
  });
  
  server.on("/L", []() { // Turn Left
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    server.send(200);
  });
  
  server.on("/R", []() { // Turn Right
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    server.send(200);
  });
  
  server.on("/BL", []() { // Arc reverse left
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    server.send(200);
  });
  
  server.on("/BR", []() { // Arc reverse right
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    server.send(200);
  });

  // Start the server
  server.begin();
}

void loop() {
  // Listen for incoming client requests
  server.handleClient();
}