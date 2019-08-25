#include <ESP8266WiFi.h>
 
const char* ssid = "ssid_name";//replace with your ssid
const char* password = "**********";//replace with your password
 
int ledPin = D13;
WiFiServer server(80);//port 8080
 
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");//creates a loading kinda animation
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> Turn relay ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> Turn relay OFF<br>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
