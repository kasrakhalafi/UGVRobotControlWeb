#include <ESP8266WiFi.h>

const char* ssid = "ENTER YOUR SSID HERE";
const char* password = "ENTER YOUR PASSWORD HERE";

WiFiServer server(80);

int output_pin = 2;

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
  }
//  Serial.println("");
//  Serial.println("WiFi connected");

  server.begin();
//  Serial.println("Server started");
//  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

//  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  //Serial.println(req);
  client.flush();

  if (req.indexOf("W") != -1) {
    Serial.print("w\n");
  }
  
  else if (req.indexOf("/E") != -1) {
    Serial.print("e\n");
  }
  
else if (req.indexOf("/Q") != -1) {
  Serial.print("q\n");
  }
  
  else if (req.indexOf("/D") != -1) {
    Serial.print("d\n");
  }

  else if (req.indexOf("/S") != -1) {
    Serial.print("s\n");
  }

  else if (req.indexOf("/A") != -1) {
    Serial.print("a\n");
  }

  client.flush();


  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  s += "<head>";
  s += "<script src=\"https://code.jquery.com/jquery-2.1.3.min.js\"></script>";
  //s += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  s += "<link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\">";
  s += "<style media=\"screen\">";
  s += "body{";
  s += "  background-color:#abebc6;";
  s += "}";
  s += "</style>";
  s += "</head>";
  s += "<body>";
  s += "<h1>Please Push one of these buttons</h1>";
  s += "<br></br>";
  s += "<br></br>";
  s += "<button class=\"w3-bar-item w3-button w3-pink \"  style=\"width:33%\" onclick=\"leftup()\">Move Left</button>";
  s += "<button class=\"w3-bar-item w3-button w3-teal\" style=\"width:33%\" onclick=\"forward()\">Move Forward</button>";
  s += "<button class=\"w3-bar-item w3-button w3-red\" style=\"width:33%\" onclick=\"rightup()\">Move Right</button>";
  s += "<br></br>";
  s += "<br></br>";
  s += "<br></br>";
  s += "<button class=\"w3-bar-item w3-button w3-red\"  style=\"width:33%\" onclick=\"left()\">Turn Left</button>";
  s += "<button class=\"w3-bar-item w3-button w3-teal\" style=\"width:33%\" onclick=\"down()\">Move Reverse</button>";
  s += "<button class=\"w3-bar-item w3-button w3-pink\" style=\"width:33%\" onclick=\"right()\">Turn Right</button>";

  s += "</body>";
  s += "<script>function leftup() {$.post(\"/Q\");}</script>";
  s += "<script>function forward() {$.get(\"/W\");}</script>";
  s += "<script>function rightup() {$.get(\"/E\");}</script>";
  s += "<script>function left() {$.get(\"/A\");}</script>";
  s += "<script>function down() {$.get(\"/S\");}</script>";
  s += "<script>function right() {$.get(\"/D\");}</script>";


  client.print(s);
  delay(1);
//  Serial.println("Client disconnected");
}
