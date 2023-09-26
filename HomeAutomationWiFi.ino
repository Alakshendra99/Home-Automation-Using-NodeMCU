#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi-Credentials
const char* ssid = "Winternet Is Coming:";
const char* password = "IDon'tKnow!";

ESP8266WebServer server(80);
  int btn1 = 1;
  int btn2 = 1;
  int btn3 = 1;
  int btn4 = 1;
  
void setup() {
  //Setting-up-the-pins-and-serial-monitor.
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  pinMode(12,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(15,OUTPUT);
  //For-safety-reason-start-everything-from-low.
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  digitalWrite(14,LOW);
  digitalWrite(15,LOW);

  Serial.println("Connecting To - ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());
  
  server.on("/",handle_index);
  server.on("/LEDON",handle_LEDON);
  server.on("/LEDOFF",handle_LEDOFF);
  server.on("/TUBEON",handle_TUBEON);
  server.on("/TUBEOFF",handle_TUBEOFF);
  server.on("/FANON",handle_FANON);
  server.on("/FANOFF",handle_FANOFF);
  server.on("/MISCON",handle_MISCON);
  server.on("/MISCOFF",handle_MISCOFF);
  server.onNotFound(handle_404);
  server.begin();
  Serial.println("HTTP Server Operational");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  server.handleClient();
  digitalWrite(LED_BUILTIN,LOW);
  delay(100);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(100);
}


// handle_functions-for-different-web-pages
void handle_index() {
  server.send(200, "text/html", SendHTML());
}

// Function-for-LED-LIGHT-operation.
void handle_LEDON() {
  Serial.println("LED LIGHT - ON");
  digitalWrite(12,LOW);
  btn1 = 1;
  server.send(200, "text/html", SendHTML());
}
void handle_LEDOFF() {
  Serial.println("LED LIGHT - OFF");
  digitalWrite(12,HIGH);
  btn1 = 0;
  server.send(200, "text/html", SendHTML());
}

// Function-for-TUBELIGHT-operation.
void handle_TUBEON() {
  Serial.println("TUBELIGHT - ON");
  digitalWrite(13,LOW);
  btn2 = 1;
  server.send(200, "text/html", SendHTML());
}
void handle_TUBEOFF() {
  Serial.println("TUBELIGHT - OFF");
  digitalWrite(13,HIGH);
  btn2 = 0;
  server.send(200, "text/html", SendHTML());
}

// Function-for-FAN-operation.
void handle_FANON() {
  Serial.println("FAN - ON");
  digitalWrite(14,LOW);
  btn3 = 1;
  server.send(200, "text/html", SendHTML());
}
void handle_FANOFF() {
  Serial.println("FAN - OFF");
  digitalWrite(14,HIGH);
  btn3 = 0;
  server.send(200, "text/html", SendHTML());
}

// Function-for-MISC-operation.
void handle_MISCON() {
  Serial.println("MISC - ON");
  digitalWrite(15,LOW);
  btn4 = 1;
  server.send(200, "text/html", SendHTML());
}
void handle_MISCOFF() {
  Serial.println("MISC - OFF");
  digitalWrite(15,HIGH);
  btn4 = 0;
  server.send(200, "text/html", SendHTML());
}
void handle_404() {
  server.send(404, "text/plain", "NOT FOUND. HAVE A NICE DAY.");
}
// Function-sending-the-webpage.
String SendHTML () {
  String html = "<!DOCTYPE html><html>\n";
  html += "<head><title>Dashboard</title><style>.back{background-color:#297F87}.App{font:bold;font-size:20;font-family:Baskerville,'Palatino Linotype',Palatino,'Century Schoolbook L','Times New Roman','serif'}.panel{background-color:#FF6B6B;padding-top:2%;padding-bottom:2%}.disp{background-color:#FFF;padding-top:2%;padding-bottom:10%}.dash{padding-top:7%;padding-bottom:3%;font-family:'Gill Sans','Gill Sans MT','Myriad Pro','DejaVu Sans Condensed',Helvetica,Arial,'sans-serif';font-size:50;color:white}.credit{padding:1% 1% 1% 1%;background-color:white}</style><link href='https://cdn.jsdelivr.net/npm/bootstrap@5.1.1/dist/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-F3w7mX95PdgyTmZZMECAngseQB83DfGTowi0iMjiWaeVhAn4FJkqJByhZMI3AhiU' crossorigin='anonymous'></head>";
  html += "<body class='back'><div class='dash'><h1 align='center'>Dashboard</h2></div><div class='row'><div class='col-lg-3 col-sm-12 col-md-6 panel'><div class='disp'><div align='center'><p class='App'>LED LIGHT</p></div><div align='center'>";
  if (btn1==1){
    html += "<a href='/LEDOFF'><button class='cent btn btn-outline-danger'>OFF</button></a>";
  } else {
    html += "<a href='/LEDON'><button class='cent btn btn-outline-success'>ON</button></a>";
  }
  html += "</div></div></div><div class='col-lg-3 col-sm-12 col-md-6 panel'><div class='disp'><div align='center'><p class='App'>TUBELIGHT</p></div><div align='center'>";
  if (btn2==1){
    html += "<a href='/TUBEOFF'><button class='cent btn btn-outline-danger'>OFF</button></a>";
  } else {
    html += "<a href='/TUBEON'><button class='cent btn btn-outline-success'>ON</button></a>";
  }
  html += "</div></div></div><div class='col-lg-3 col-sm-12 col-md-6 panel'><div class='disp'><div align='center'><p class='App'>FAN</p></div><div align='center'>";
  if (btn3==1){
    html += "<a href='/FANOFF'><button class='cent btn btn-outline-danger'>OFF</button></a>";
  } else {
    html += "<a href='/FANON'><button class='cent btn btn-outline-success'>ON</button></a>";
  }
  html += "</div></div></div><div class='col-lg-3 col-sm-12 col-md-6 panel'><div class='disp'><div align='center'><p class='App'>MISC</p></div><div align='center'>";
  if (btn4==1){
    html += "<a href='/MISCOFF'><button class='cent btn btn-outline-danger'>OFF</button></a>";
  } else {
    html += "<a href='/MISCON'><button class='cent btn btn-outline-success'>ON</button></a>";
  }
  html += "</div></div></div></div><div class='credit' align='center'>Made By Alakshendra Singh</div><hr> <script src='https://cdn.jsdelivr.net/npm/bootstrap@5.1.1/dist/js/bootstrap.bundle.min.js' integrity='sha384-/bQdsTh/da6pkI1MST/rWKFNjaCP5gBSY4sEBT38Q/9RBh9AH40zEOg7Hlq2THRZ' crossorigin='anonymous'></script> </body></html>";
  return html;
}
