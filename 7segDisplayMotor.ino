#include "SevSeg.h"

// Definindo os pinos para os motores
#define motorDF 3  
#define motorDT 2 
#define motorEF 45  
#define motorET 46  

// Definindo os pinos para os sensores
#define sensorEsquerdo A1 
#define sensorDireito A0  

// Definindo o valor de limiar, o branco geralmente fica abaixo de 100
#define limiar 180

// Definindo a velocidade máxima do motor, pode variar com o PID, bateria, etc
#define maxVelocidade 60

SevSeg sevseg1, sevseg2; // Variáveis para controlar cada um dos displays

void setup() {
  // Iniciando os pinos dos motores
  pinMode(motorDF, OUTPUT);
  pinMode(motorEF, OUTPUT);
  pinMode(motorDT, OUTPUT);
  pinMode(motorET, OUTPUT);

  // Configurando os displays de 7 segmentos
  byte numDigits1 = 4;
  byte digitPins1[] = {10, 11, 12, 13};
  byte segmentPins1[] = {22, 24, 4, 5, 6, 7, 8};
  sevseg1.begin(COMMON_ANODE, numDigits1, digitPins1, segmentPins1);
  sevseg1.setBrightness(60);

  byte numDigits2 = 4;
  byte digitPins2[] = {50, 51, 52, 53};
  byte segmentPins2[] = {39, 38, 40, 41, 42, 43, 44};
  sevseg2.begin(COMMON_ANODE, numDigits2, digitPins2, segmentPins2);
  sevseg2.setBrightness(60);
}

void loop() {
  // Lendo os valores dos sensores
  int valEsquerdo = analogRead(sensorEsquerdo);
  int valDireito = analogRead(sensorDireito);

  // Atualizando os displays com os valores lidos
  sevseg1.setNumber(valEsquerdo, 0);
  sevseg1.refreshDisplay();

  sevseg2.setNumber(valDireito, 0);
  sevseg2.refreshDisplay();

  // Seguindo a linha branca
  if (valEsquerdo < limiar && valDireito < limiar) {
    // Ambos os sensores estão sobre a linha branca - mova para frente
    analogWrite(motorDF, maxVelocidade);
    analogWrite(motorEF, maxVelocidade);
    analogWrite(motorDT, 0);
    analogWrite(motorET, 0);
  }
  else if (valDireito > limiar && valEsquerdo > limiar) {
    // Condição para ir pra frente quando tudo preto
    analogWrite(motorDF, maxVelocidade);
    analogWrite(motorEF, maxVelocidade);
    analogWrite(motorDT, 0);
    analogWrite(motorET, 0);
  }  
  else if (valEsquerdo > limiar) {
    // Apenas o sensor esquerdo está sobre a linha branca - vire à direita
    analogWrite(motorDT, 0);
    analogWrite(motorDF, 0); // Desligar o motor oposto
    analogWrite(motorEF, maxVelocidade);
    analogWrite(motorET, 0);
  }
  else if (valDireito > limiar) {
    // Apenas o sensor direito está sobre a linha branca - vire à esquerda
    analogWrite(motorET, 0);
    analogWrite(motorEF, 0); // Desligar o motor oposto
    analogWrite(motorDF, maxVelocidade);
    analogWrite(motorDT, 0);
  }
}
