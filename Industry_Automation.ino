#include <ESP8266WiFi.h>
WiFiClient client; // It creates a client that can connect to a specified port.
WiFiServer server(80);  // Creates a server that listens incoming data from a spectified port. Here port is 80.


const char* ssid = "SantoshKumar";   
const char* password = ""; 


String  data =""; //Data from app


int Relay1 = 12;    //D6
int Relay2 = 16;    //D0
int Relay3 = 4;     //D2
int Relay4 = 5;     //D1


void setup()
{
  
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT); 
  pinMode(Relay3, OUTPUT);  
  pinMode(Relay4, OUTPUT);

  digitalWrite(Relay1,LOW);
  digitalWrite(Relay2,LOW);
  digitalWrite(Relay3,LOW);
  digitalWrite(Relay4,LOW);
  
  
  Serial.begin(115200);  // Wifi communication
  connectWiFi();
  server.begin(); //Server Begins 
}

void loop()
{
     
    client = server.available();  //Checks if the server is connected or not
    if (!client) return; 
    data = checkClient ();
Serial.println(data);


    
    if (data == "m1on") // Main Program
    { 
      digitalWrite(Relay1,HIGH);
      }
    
    else if (data == "m1off")
    {
      digitalWrite(Relay1,LOW);
      }

    else if (data == "m2on")
    {
      digitalWrite(Relay2,HIGH);
      }
      
    else if (data == "m2off")
    {
      digitalWrite(Relay2,LOW);
      }
      
    else if (data == "l1on")
    {
      digitalWrite(Relay3,HIGH);
      }
      
    else if (data == "l1off")
    {
      digitalWrite(Relay3,LOW);
      }
      
    else if (data == "l2on")
    {
      digitalWrite(Relay4,HIGH);
      }
      
    else if (data == "l2off")
    {
      digitalWrite(Relay4,LOW);
      }
      
} 

void connectWiFi()  // connecting to wifi
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}

String checkClient (void) //Receiving the data from app
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
