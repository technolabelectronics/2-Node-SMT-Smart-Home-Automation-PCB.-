
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;


#define DEBUG_SW 0


#define Switch1 34
#define Relay1 23

#define Switch2 35
#define Relay2 22


#define LED1 13
#define LED2 12




int MODE = 0;


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "technolab fibre";
char pass[] = "air88918";

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = " kwGKZIfU_BhkS5eLQXxQ_ZRRUAw5w4vB";


int Flag1 = 0;
int Flag2 = 0;


BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(Relay1, pinValue);
  // process received value
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable
  digitalWrite(Relay2, pinValue);
  // process received value
}




void with_internet()
{
  if (digitalRead(Switch1) == LOW)
  {
    if (Flag1 == 0 )
    {
      digitalWrite(Relay1, LOW);
      if (DEBUG_SW) Serial.println("Relay1- ON");
      Blynk.virtualWrite(V1, 0);
      Flag1 = 1;
    }
    if (DEBUG_SW) Serial.println(" -ON");

  }
  if (digitalRead(Switch1) == HIGH )
  {
    if (Flag1 == 1)
    {
      digitalWrite(Relay1, HIGH);
      if (DEBUG_SW) Serial.println("Relay1 OFF");
      Blynk.virtualWrite(V1, 1);
      Flag1 = 0;
    }
    if (DEBUG_SW)Serial.println(" OFF");
  }


  if (digitalRead(Switch2) == LOW)
  {
    if (Flag2 == 0 )
    {
      digitalWrite(Relay2, LOW);
      if (DEBUG_SW)  Serial.println("Relay2- ON");
      Blynk.virtualWrite(V2, 0);
      Flag2 = 1;
    }
    if (DEBUG_SW) Serial.println("Switch2 -ON");

  }
  if (digitalRead(Switch2) == HIGH )
  {
    if (Flag2 == 1)
    {
      digitalWrite(Relay2, HIGH);
      if (DEBUG_SW) Serial.println("Relay2 OFF");
      Blynk.virtualWrite(V2, 1);
      Flag2 = 0;
    }
    if (DEBUG_SW)Serial.println("Switch2 OFF");
    //delay(200);
  }
}

void without_internet()
{

  digitalWrite(Relay1, digitalRead(Switch1));
  digitalWrite(Relay2, digitalRead(Switch2));
 

}


void checkBlynk() { // called every 3 seconds by SimpleTimer

  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    MODE = 1;
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    
  }
  if (isconnected == true) {
    MODE = 0;
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
   
  }
}

void setup()
{
  // Debug console
  if (DEBUG_SW) Serial.begin(9600);
  pinMode(Switch1, INPUT);
  pinMode(Relay1, OUTPUT);

  pinMode(Switch2, INPUT);
  pinMode(Relay2, OUTPUT);




  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
 

  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED2, HIGH);
  delay(200);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  
  delay(500);

  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED2, HIGH);
  delay(200);
 

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
 
  //pinMode(MODE, INPUT);
  WiFi.begin(ssid, pass);
  timer.setInterval(3000L, checkBlynk); // check if connected to Blynk server every 3 seconds
  Blynk.config(auth);//, ssid, pass);

}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    if (DEBUG_SW) Serial.println("Not Connected");
  }
  else
  {
    if (DEBUG_SW) Serial.println(" Connected");
    Blynk.run();
  }

  timer.run(); // Initiates SimpleTimer
  if (MODE == 0)
    with_internet();
  else
    without_internet();
}
