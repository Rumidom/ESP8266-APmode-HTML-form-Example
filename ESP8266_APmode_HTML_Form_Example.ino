// Libraries
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


// WiFi network
const char* ssid     = "ESPTEST";
const char* password = "12345678";


ESP8266WebServer server ( 80 );



void handleRoot() {

String html = "<!DOCTYPE html>";

html += "<html> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
html += "<body> <h2>Formulario</h2>";
html += "<p> A penas um teste</p>";
html += "<form method=\"get\" action=\"/save\">";
html += "SSID:<br>";
html += "<input type=\"text\" name=\"SSID\" value=\"Mickey\"> <br> ";
html += "Senha:<br> ";
html += "<input type=\"text\" name=\"Senha\" value=\"Mouse\"> <br>";
html += "<br>";
html += "<input type=\"submit\" value=\"Enviar\"> </form> </body> </html>";


server.send ( 200, "text/html", html );  

}


void handleSave() {
  if (server.arg("SSID")!= ""){
    Serial.println("SSID: " + server.arg("SSID"));
  }

  if (server.arg("Senha")!= ""){
    Serial.println("Senha: " + server.arg("Senha"));
  }

String html = "<!DOCTYPE html>";
html += "<html> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
html += " <body>";
html += "<p> Formulario Enviado </p>";
html += "</body> </html>";


   server.send ( 200, "text/html", html );  

}


void setup() {

  // Start serial
  Serial.begin(115200);
  delay(10);

  WiFi.softAP(ssid, password);
 
  Serial.println();
  Serial.print("Server IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Server MAC address: ");
  Serial.println(WiFi.softAPmacAddress());

  server.on ( "/", handleRoot );
  server.on ("/save", handleSave);

  server.begin();
  Serial.println ( "HTTP server started" );


}

void loop() {
  server.handleClient();
}
