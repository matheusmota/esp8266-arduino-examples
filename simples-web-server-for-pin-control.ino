#include <ESP8266WiFi.h>

const char* ssid = "ssid";
const char* password = "passwd";

int pin2 = 2; 
int pin3 = 3; 
int pin4 = 4; 
int pin5 = 5; 
WiFiServer server(80);

void setup() {
  
        Serial.begin(115200);
        delay(10);
        
        pinMode(pin2, OUTPUT);
        pinMode(pin3, OUTPUT);        
        pinMode(pin4, OUTPUT);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        
        // Connect to WiFi network
        Serial.println();
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(ssid);
        
        WiFi.begin(ssid, password);
        
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("");
        Serial.println("WiFi connected");
        
        // Start the server
        server.begin();
        Serial.println("Server started");
        
        // Print the IP address
        Serial.print("Use this URL to connect: ");
        Serial.print("http://");
        Serial.print(WiFi.localIP());
        Serial.println("/");

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
        
        if (request.indexOf("/pin/2/100") != -1) {
          digitalWrite(pin2, LOW);
        }
        if (request.indexOf("/pin/2/0") != -1) {
          digitalWrite(pin2, HIGH);
        }
        
        if (request.indexOf("/pin/3/100") != -1) {
          digitalWrite(pin3, LOW);
        }
        if (request.indexOf("/pin/3/0") != -1) {
          digitalWrite(pin3, HIGH);
        }       
        
        if (request.indexOf("/pin/4/100") != -1) {
          digitalWrite(pin4, LOW);
        }
        if (request.indexOf("/pin/4/0") != -1) {
          digitalWrite(pin4, HIGH);
        }        
        // Set ledPin according to the request
        //digitalWrite(ledPin, value);
        
        // Return the response
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println(""); // do not forget this one
        client.println("<!DOCTYPE HTML>");
        client.println("<html>");
        
        
        client.println("<br><br>");
        client.println("Click <a href=\"/pin/2/100\">here</a> turn the device on pin 2 100<br>");
        client.println("Click <a href=\"/pin/2/0\">here</a>   turn the device on pin 2 0<br>");
        client.println("Click <a href=\"/pin/3/100\">here</a> turn the device on pin 3 100<br>");
        client.println("Click <a href=\"/pin/3/0\">here</a>   turn the device on pin 3 0<br>");
        client.println("Click <a href=\"/pin/4/100\">here</a> turn the device on pin 4 100<br>");
        client.println("Click <a href=\"/pin/4/0\">here</a>   turn the device on pin 4 0<br>");
        client.println("</html>");
        
        delay(1);
        Serial.println("Client disonnected");
        Serial.println("");

}
