#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid     = "pgiiotwcs";   //replace with your own SSID
const char* password = "628118gh";    //replace with your own password
const char* host = "api.pushingbox.com";
//===================================injected code====================================================
int d,h,i;
int f = 0;

const long utcOffsetInSeconds = 19620;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
//===================================================================================================
int RLY = 4;
int LED_BUILTIN = 5;
double data;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++==
void setup()

 {
//===============================================================
  pinMode(RLY,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  //============================================================
  Serial.begin(115200);

  delay(50);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
 {
    delay(500);
    Serial.print(".waiting for the network.");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    f=0;
    Serial.print(".stand by flushmode loop stated.");

    for ( f ; f <= 30; f++)//****(flush clsoing time 17=1020
{
        Serial.println("FLUSH COUNTS OFLIE MODE ");
        Serial.println(f);
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(RLY, HIGH);//***active low

      //  f = f + 1; //flush count incrementing
        Serial.println("system flush for 10 sec ");
        delay(10000);//flush for 10 second  ////****(10000
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(RLY, LOW);
        Serial.println("system flush wait 20 sec ");
        delay(20000);// flush off for 50 second/////****(50000

}

 }

  Serial.println("**");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

//  pinMode(A0, INPUT);
 //  pinMode(RLY, OUTPUT);
  // pinMode(LED_BUILTIN, OUTPUT);
//====================================================================
   Serial.println ( "." );
   //Serial.println("wifi connected");
     Serial.println("system online");
     Serial.println("system connected to pNeuton Dynamics Server");
     timeClient.begin();
     //========================================================================
     //===========================================================================
   //  server.handleClient();
     timeClient.update();
     f=0;//flush reset after data push
     Serial.print(daysOfTheWeek[timeClient.getDay()]);
     Serial.print(",");
     Serial.print(timeClient.getHours());
     Serial.print(":");
     Serial.print(timeClient.getMinutes());
     Serial.print(":");
     Serial.println(timeClient.getSeconds());

   d = (timeClient.getDay());          //variable read block---------------------------

   h = (timeClient.getHours());
   //h=15;
   i=h*60;//*******mineuts conversion

   Serial.print("day number =");
   Serial.println(d);
   Serial.print("hour number =");
   Serial.println(h);
   Serial.print("hours in min number =");
   Serial.println(i);


   delay(1000);

      //server.handleClient();
      timeClient.update();
      f=0;//flush reset after data push
      Serial.print(daysOfTheWeek[timeClient.getDay()]);
      Serial.print(",");
      Serial.print(timeClient.getHours());
      Serial.print(":");
      Serial.print(timeClient.getMinutes());
      Serial.print(":");
      Serial.println(timeClient.getSeconds());

    d = (timeClient.getDay());          //variable read block---------------------------

    h = (timeClient.getHours());
    //h=15;
    i=h*60;//*******mineuts conversion

    Serial.print("day number =");
    Serial.println(d);
    Serial.print("hour number =");
    Serial.println(h);
    Serial.print("hours in min number =");
    Serial.println(i);

    delay(1000);

}


void loop() //LOOP BLOCK

{






{
  //======================================--------------------------------------------------------------------------------====================================

 if (d==8||d==0)

 {

  Serial.println("system halted for Sunday rechecking day in 1 hr");
  delay(3600000);// sunday recheck delay every hour 60*60*1000

 }

 else

{
 if (h>=8&&h<16)//*****8am-5pm / 1700 hours
  {
for ( i ; i <= 945; i++)//****(flush clsoing time 17=1020

  {


 Serial.println(i);
 digitalWrite(LED_BUILTIN, LOW);
 digitalWrite(RLY, HIGH);//***active low

 f = f + 1; //flush count incrementing
 Serial.println("system flush for 10 sec ");
 delay(10000);//flush for 10 second  ////****(10000
 digitalWrite(LED_BUILTIN, HIGH);
 digitalWrite(RLY, LOW);
 Serial.println("system flush wait 50 sec ");
 delay(50000);// flush off for 50 second/////****(50000

  }

 Serial.println("loop over");
 delay(1000);
 Serial.println("total number of flush for 10 sec today ");
 Serial.print(f);



delay(10000); //88888888888888888888888888888888888888888888888 emove it test delay
  }

 else

   {
     Serial.println("system stand by (non office hours)loop initate service loop rechecking in 30 min");
     delay(1800000);//loop re initate service 30 min delay 18,00,000
   }


 }

//----------------------------------------------------------------------------------------

//=============================================================================

  //==========================================================================
 //if(digitalRead(RLY) == 0)
 {
    delay(1000);
    data = f; //analogRead(150);  //A0
    Serial.println("connecting to ");
    Serial.println(host);



    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }

    // We now create a URI for the request
    String url = "/pushingbox?";
    url += "devid=";
    url += "v751A0CBED750631";
    url += "&data="+String(data);

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
    Serial.print("Data Sent!");
  }

  Serial.println();
  Serial.println("closing connection and waiting");

  }
  digitalWrite(LED_BUILTIN, HIGH);
  delay(30000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);

}

}
