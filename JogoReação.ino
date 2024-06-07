#include <NewPing.h>

#define TRIGGER_PIN  A0
#define ECHO_PIN     A1
#define MAX_DISTANCE 100  // Máxima distância em cm que o sensor deve ler
#define GREEN_LED    8
#define RED_LED      9

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

unsigned long reactionStart;  // Momento que o LED vermelho é aceso
bool waitingForReaction = false; // Estado para saber se estamos esperando uma reação

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, HIGH); // Inicialmente, o LED verde está aceso
  digitalWrite(RED_LED, LOW);
  Serial.begin(9600);
}

void loop() {
  // Aguarda um tempo aleatório com o LED verde aceso
  if (!waitingForReaction) {
    delay(random(2000, 5000)); // Espera um tempo aleatório entre 2 e 5 segundos
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    reactionStart = millis();
    waitingForReaction = true;
  }

  // Monitora a reação do jogador
  else if (waitingForReaction) {
    if (millis() - reactionStart < 500) {  // Verifica se estamos dentro do intervalo de reação
      if (sonar.ping_cm() < 50) {  // Mão detectada a menos de 50 cm
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        waitingForReaction = false;  // Reseta o estado do jogo
      }
    } else {
      // Tempo excedido sem reação adequada
      blinkRedLED();
      digitalWrite(GREEN_LED, HIGH);  // Volta a acender o LED verde após o piscar
      waitingForReaction = false;  // Reseta o estado do jogo
    }
  }
}

void blinkRedLED() {
  digitalWrite(RED_LED, HIGH);
  delay(300);
  digitalWrite(RED_LED, LOW);
  delay(300);
  digitalWrite(RED_LED, HIGH);
  delay(300);
  digitalWrite(RED_LED, LOW);
  delay(300);
  digitalWrite(RED_LED, HIGH);
  delay(300);
  digitalWrite(RED_LED, LOW);
}
