#include "SevSeg.h"

// Definindo os pinos pra os motores
#define motorDF 9  // INT3 DF
#define motorEF 11 // INT1 EF
#define motorDT 8  // INT4 DT
#define motorET 7  // INT2 ET

// Definindo os pinos pra os sensores
#define sensorEsquerdo A1 // A1
#define sensorDireito A0  // A0

// Definindo o valor de limiar, o branco geralmente fica abaixo de 150
#define limiar 150

// Definindo a velocidade máxima do motor, depende da carga da bateria, curvas e dos valores de PID
#define maxVelocidade 45

// Definindo as constantes do PID, devem ser testadas empiricamente
#define Kp 0.5
#define Ki 0.1
#define Kd 0.01

SevSeg sevseg1, sevseg2; // Definindo as variaveis pra controlar cada um dos displays

float integralError = 0;
float lastError = 0;

void setup() {
  // Iniciando os pinos dos motores
  pinMode(motorDF, OUTPUT);
  pinMode(motorEF, OUTPUT);
  pinMode(motorDT, OUTPUT);
  pinMode(motorET, OUTPUT);

  // Configurando os displays de 7 segmentos
  byte numDigits1 = 4;
  byte digitPins1[] = {22, 23, 24, 25}; // Pinos pra os dígitos do primeiro display
  byte segmentPins1[] = {26, 27, 28, 29, 30, 31, 32, 33}; // Pinos pra os segmentos do primeiro display
  sevseg1.begin(COMMON_CATHODE, numDigits1, digitPins1, segmentPins1);
  sevseg1.setBrightness(90);

  byte numDigits2 = 4;
  byte digitPins2[] = {34, 35, 36, 37}; // Pinos pra os dígitos do segundo display
  byte segmentPins2[] = {38, 39, 40, 41, 42, 43, 44, 45}; // Pinos pra os segmentos do segundo display
  sevseg2.begin(COMMON_CATHODE, numDigits2, digitPins2, segmentPins2);
  sevseg2.setBrightness(90);
}

void loop() {
  // Aqui ta lendo os valores dos sensores
  int valEsquerdo = analogRead(sensorEsquerdo);
  int valDireito = analogRead(sensorDireito);

  // Atualizando os displays com os valores lidos
  sevseg1.setNumber(valEsquerdo, 0);
  sevseg1.refreshDisplay();
  sevseg2.setNumber(valDireito, 0);
  sevseg2.refreshDisplay();

  float error = valDireito - valEsquerdo;
  integralError += error;
  float derivativeError = error - lastError;
  float PIDvalue = Kp * error + Ki * integralError + Kd * derivativeError;

  int velocidadeMotorEsquerdo = constrain(maxVelocidade - PIDvalue, 0, maxVelocidade);
  int velocidadeMotorDireito = constrain(maxVelocidade + PIDvalue, 0, maxVelocidade);

  if (valEsquerdo < limiar && valDireito < limiar) {
    analogWrite(motorDF, velocidadeMotorDireito);
    analogWrite(motorEF, velocidadeMotorEsquerdo);
  } 
  else if (valEsquerdo > limiar) {
    analogWrite(motorDT, 10);
    analogWrite(motorEF, velocidadeMotorEsquerdo);
  }
  else if (valDireito > limiar) {
    analogWrite(motorET, 10);
    analogWrite(motorDF, velocidadeMotorDireito);
  }
  else {
    analogWrite(motorDF, maxVelocidade);
    analogWrite(motorEF, maxVelocidade);
  }

  lastError = error; // Armazenando o erro pra próxima iteração
}
