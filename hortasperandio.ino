#include <DHT.h>
#include <Adafruit_Sensor.h>

#define pinoDHT A0
#define sensorUmidade A1
#define tipoDHT DHT22
#define ledVermelho 8
#define ledAmarelo 9
#define ledVerde 10
#define pinoRele 7 

float temperatura = 0;
float umidadeAr = 0;
int umidadeTerra = 0;

DHT dht(pinoDHT, tipoDHT);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(pinoRele, OUTPUT);
}

void loop() {
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVerde, LOW);
  temperatura = dht.readTemperature();
  umidadeAr = dht.readHumidity();
  umidadeTerra = analogRead(sensorUmidade);
  Serial.println(temperatura + String(",") + umidadeAr + String(",") + umidadeTerra);

  if (umidadeTerra < 400) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(pinoRele, HIGH); 
  } else {
    digitalWrite(pinoRele, LOW); 
  }

  if (umidadeTerra > 800) {
    digitalWrite(ledVermelho, HIGH);
  } else if (umidadeTerra > 400 && umidadeTerra <= 800) {
    digitalWrite(ledAmarelo, HIGH);
  }
  
  delay(500);
}
