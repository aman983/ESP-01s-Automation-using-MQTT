#include <Arduino.h>
#include<ESP8266WiFi.h>
#include<PubSubClient.h>

const char* ssid = "put ssid here"; //Wifi ssid and Password 
const char* password = "Put pass here"; 

const char *mqtt_broker = "mqtt.eclipseprojects.io"; // mqtt broker address and port number
const int mqtt_port = 1883;

const uint8_t Relay1 = 2; // Relay Gpio
const uint8_t Relay2 = 0;

WiFiClient esp;
PubSubClient client(esp);

/* Firmware version -> 0.1         *
*  Made by Aman Shaikh             *
*  contact -> amanshaikhw@gmail.com*/

/*------------------------------------------------------------------\
|                         Function roles                            |        
|-------------------------------------------------------------------|
|                                                                   |
| Connectify --> connects the device to wifi                        |
|                                                                   |
| action --> modify this to take action when a                      |
|             a specified message is published                      |
|             on a patricular topic.                                |
|                                                                   |
| callback --> Gets the message information from the topic          |
|                                                                   |
| sublist --> Add topics to listen to                               |
|                                                                   |
| reconnect --> As name suggests reconnects when disconnected       |
|                                                                   |
| setup --> connect to wifi                                         |
|            connect to mqtt broker                                 |
|            Set callback function                                  |
|                                                                   |
| loop --> check for connection status and reconnect if disconnected| 
\------------------------------------------------------------------*/
void connectify(const char* network,const char* pass){
  int times=0;
  Serial.println("connecting to ");
  Serial.print(network);
  Serial.println("----------------------------------------------------");
  WiFi.begin(network,pass);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    times+=1;
  }
  Serial.println("----------------------------------------------------");
  Serial.println("Connecting tries = ");
  Serial.println(times);
  Serial.println("----------------------------------------------------");
  Serial.println("IP address ----> ");
  Serial.println(WiFi.localIP());

}

void action(String topic,String message){
  if(topic == "Relay"){
    if(message == "1on"){
      digitalWrite(Relay1,LOW);
    }
    else if(message == "1off"){
      digitalWrite(Relay1,HIGH);
    }

    if(message == "2on"){
      digitalWrite(Relay2,LOW);
    }
    else if(message == "2off"){
      digitalWrite(Relay2,HIGH);
    }

  }

}

void callback(String topic, byte* message, unsigned int length) {
  
  Serial.println("--------------");
  Serial.print(topic);
  Serial.println("");
  Serial.println("Message: ");
  String messageInfo;
  
  for ( int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageInfo += (char)message[i];
  }

  action(topic,messageInfo);
  Serial.println("");
}

void sublist(){
  client.subscribe("Relay"); 
}

void reconnect() {
 
  // Loop until we're reconnected
  while (!client.connected()) {
   
    Serial.println("Attempting MQTT connection...");
    
    
    if (client.connect("esp")) {
      Serial.println("connected");  
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more Relay1s in this example)
    
      sublist();// add here the function to sub
    
    } else {
      Serial.print("failed to connect, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {

  Serial.begin(115200);
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  digitalWrite(Relay1,HIGH);
  digitalWrite(Relay2,HIGH);
  connectify(ssid,password);
  client.setServer(mqtt_broker,mqtt_port);
  client.setCallback(callback);

}

void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop()){
  client.connect("esp");
  }

}

