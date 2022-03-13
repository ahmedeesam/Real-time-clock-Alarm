#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <string.h>
 SoftwareSerial mySerial(D0, D1); // RX, TX

const char* ssid = "Orange-DE9B";
const char* password = "BBY7NQ07BJ7";

const char* mqtt_server = "192.168.1.106";

char st1[] = "start";
char st2[] = "stop";
char st3[] = "on";
char st4[] = "off";
char st5[] = "time";
char hours[2], minutes[2], day[2];
int i,n;

WiFiClient EspClient;
PubSubClient client(EspClient);

void recieve_string(char *b){
 char d;
 //Serial.println("wait for len");

 while(Serial.available() == 0);
 d = Serial.read();
 
 //Serial.println(d);
 //Serial.println("wait for st");
 for (unsigned char z = 0;z <= (d-1);z++)
     {
      while(Serial.available() == 0);
       b[z] = Serial.read();
      //Serial.println(b[z]);
     }
 //Serial.println("end of receiving");
 b[d] = '\0';
}

void send_string(char *a ,char c)
{
  mySerial.write(c);
  delay(50);
  for(char z=0;z <= (c-1);z++)
  {
  mySerial.write(a[z]);
  Serial.write(a[z]);
  }
}

void send_BitSeries(char *a ,char c)
{
  for(char z=0;z <= (c-1);z++)
  {
  mySerial.write(a[z]);
  Serial.write(a[z]);
  }
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if(topic=="Room/Lamp/time/start")
  {
    if(messageTemp == "clear")
      {
        hours[0] = '0';
        hours[1] = '0';
        minutes[0] = '0';
        minutes[1] = '0';
        day[0] = '0';
        day[1] = '0';  

        send_string(st1 , 5); //send "start"
        delay(100);
        send_BitSeries(hours , 2);
        delay(200);
        send_BitSeries(minutes , 2);
        delay(300);
        send_BitSeries(day , 2);
        Serial.println();
      }
      else
      {
        hours[0] = message[0];
        hours[1] = message[1];
        minutes[0] = message[3];
        minutes[1] = message[4];
        day[0] = message[5];
        day[1] = message[6];  

        send_string(st1 , 5); //send "start"
        delay(100);
        send_BitSeries(hours , 2);
        delay(200);
        send_BitSeries(minutes , 2);
        delay(300);
        send_BitSeries(day , 2);
        Serial.println();
      }

  }
  
 else if(topic=="Room/Lamp/time/end")
  {
    if(messageTemp == "clear")
      {
        hours[0] = '0';
        hours[1] = '0';
        minutes[0] = '0';
        minutes[1] = '0';
        day[0] = '0';
        day[1] = '0';  

        send_string(st2 , 4); //send "stop"
        delay(100);
        send_BitSeries(hours , 2);
        delay(200);
        send_BitSeries(minutes , 2);
        delay(300);
        send_BitSeries(day , 2);
        Serial.println();
      }
      else
      {
        hours[0] = message[0];
        hours[1] = message[1];
        minutes[0] = message[3];
        minutes[1] = message[4];
        day[0] = message[5];
        day[1] = message[6];  

        send_string(st2 , 4); //send "stop"
        delay(100);
        send_BitSeries(hours , 2);
        delay(200);
        send_BitSeries(minutes , 2);
        delay(300);
        send_BitSeries(day , 2);
        Serial.println();
      }    
  }
  else if(topic=="Room/Lamp/control")
  {
    //send_string(st2 , 7);  
    if(messageTemp == "on")
    {
      send_string(st3 , 2);
    }
    else if(messageTemp == "off")
    {
      send_string(st4 , 3);
    }
  }
  else if(topic == "RTC/time")
  {
    hours[0] = message[0];
    hours[1] = message[1];
    minutes[0] = message[3];
    minutes[1] = message[4];
    day[0] = message[5];
    day[1] = message[6];  

    send_string(st5 , 4); //send "time"
    delay(300);
    send_BitSeries(hours , 2);
    delay(100);
    send_BitSeries(minutes , 2);
    delay(1500);
    send_BitSeries(day , 2);
    Serial.println();
  }
  /*else if(topic == "RTC/date")
  {

  }*/
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
     if (client.connect("ESP8266bath")) {
      Serial.println("connected");  
      client.subscribe("Room/Lamp/control");
      client.subscribe("Room/Lamp/time/start");
      client.subscribe("Room/Lamp/time/end");
      client.subscribe("RTC/time");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop() {
 if (!client.connected()) {
    reconnect();
  }
  
  if(!client.loop())
  {
    client.connect("ESP8266bath1");
  }
  
 /* recieve_string(received);
  
  if ((strcmp(received , st1)) == 0)
    {
      client.publish("bathroom/first", st1); 
    } 
  else if((strcmp(received , st2)) == 0)
    {
      client.publish("bathroom/first", st2);
    }
    */
  }

     /* for(unsigned char i =0;i <= 6;i++)
    {
      //if((i >= 0) && (i < 2))
      if(i == 0)
      {
        hours[i] = message[i];
      }
      else if(i == 1)
      {
        hours[i] = message[i];
      }
      else if((i >= 3) && (i < 5))
      {
        minutes[i] = message[i];
      }
      else if((i >= 5) && (i < 7))
      {
        day[i] = message[i];
      }
    }*/
