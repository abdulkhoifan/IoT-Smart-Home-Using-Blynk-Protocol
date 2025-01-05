char ssid[] = "Abdul Khoifan";
char pass[] = "alhamdulillah";

bool fetch_blynk_state1 = false;
bool fetch_blynk_state2 = false;
bool fetch_blynk_state3 = false;
bool fetch_blynk_state4 = false;

#include <ESP8266WiFi.h>        
#include <BlynkSimpleEsp8266.h>

//#define BLYNK_TEMPLATE_ID ""
//#define BLYNK_TEMPLATE_NAME ""

#define BLYNK_TEMPLATE_ID "TMPL6xsyzAweM"
#define BLYNK_TEMPLATE_NAME "Switch"
#define BLYNK_AUTH_TOKEN "ByFyNM-lbl1YcBraKU5EO1CY6b4kRa7N"

// define the GPIO connected with Relays and switches
#define RelayPin1 0  //GPIO-0
#define RelayPin2 1  //GPIO-1
#define RelayPin3 2  //GPIO-2
#define RelayPin4 3  //GPIO-3

//Change the virtual pins according the rooms
#define VPIN_BUTTON_1    V0
#define VPIN_BUTTON_2    V1
#define VPIN_BUTTON_3    V2
#define VPIN_BUTTON_4    V3

// Relay State
bool toggleState_1 = LOW; //remember the toggle state for relay
bool toggleState_2 = LOW; //remember the toggle state for relay
bool toggleState_3 = LOW; //remember the toggle state for relay
bool toggleState_4 = LOW; //remember the toggle state for relay


char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

// When App button is pushed - switch the state

BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, !toggleState_1);
}
BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  digitalWrite(RelayPin2, !toggleState_2);
}
BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  digitalWrite(RelayPin3, !toggleState_3);
}
BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  digitalWrite(RelayPin4, !toggleState_4);
}


BLYNK_CONNECTED() {
  // Request the latest state from the server
  if (fetch_blynk_state1){
    Blynk.syncVirtual(VPIN_BUTTON_1);
  }
  else if(fetch_blynk_state2)
  {
   Blynk.syncVirtual(VPIN_BUTTON_2);
  }
    else if(fetch_blynk_state3)
  {
   Blynk.syncVirtual(VPIN_BUTTON_3);
  }
    else if(fetch_blynk_state4)
  {
   Blynk.syncVirtual(VPIN_BUTTON_4);
  }
  
  else{
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
    Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
    Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
    Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, !toggleState_1);
  digitalWrite(RelayPin2, !toggleState_2);
  digitalWrite(RelayPin3, !toggleState_3);
  digitalWrite(RelayPin4, !toggleState_4);
  WiFi.begin(ssid, pass);
  Blynk.config(auth);
  delay(1000);
  
  if (!fetch_blynk_state1){
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  }
  if (!fetch_blynk_state2){
    Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  }
  if (!fetch_blynk_state3){
    Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  }
  if (!fetch_blynk_state4){
    Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
  } 
}

void loop()
{  
  Blynk.run();
  timer.run();
  
  if (!Blynk.connected()) {
    toggleState_1 = LOW;
    digitalWrite(RelayPin1, !toggleState_1);
    toggleState_2 = LOW;
    digitalWrite(RelayPin2, !toggleState_2);
    toggleState_3 = LOW;
    digitalWrite(RelayPin3, !toggleState_3);
    toggleState_4 = LOW;
    digitalWrite(RelayPin4, !toggleState_4);
  }
}
