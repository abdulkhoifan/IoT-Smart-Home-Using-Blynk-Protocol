#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
BlynkTimer timer;
Servo servo1, servo2;

#define servopin1 4
#define servopin2 5
#define BLYNK_TEMPLATE_ID "TMPL6P_T4JcGi"
#define BLYNK_TEMPLATE_NAME "Home Sensor"
#define BLYNK_AUTH_TOKEN "BmRjClUScIb4FkRznYNngvvUGWL0dlQo"


char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Abdul Khoifan"; // Enter WIFI Name Here
char pass[] = "alhamdulillah"; // Enter WIFI Password Here
 
 
int mq2 = A0; // smoke sensor is connected with the analog pin A0 
int data = 0; 

BLYNK_WRITE(V3){
  servo1.write(param.asInt());
}
BLYNK_WRITE(V4){
  servo2.write(param.asInt());
}



void setup() 
{
  Serial.begin(115200);
  servo1.attach(servopin1);
  servo2.attach(servopin2);
  
  WiFi.begin(ssid, pass);
  Blynk.config(auth);
  timer.setInterval(1000L, getSendData);
}
 
void loop() 
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
}
 
void getSendData()
{
data = analogRead(mq2); 
  Blynk.virtualWrite(V2, data);
  Serial.println(data);
 
  if (data > 200 )
  {
    Blynk.logEvent("Smoke Detected!"); 
    Serial.println("Smoke Detected");
  }
 
}
