#include <LiquidCrystal.h>
LiquidCrystal lcd(10, 9, 8, 5, 4, 3, 2);

// Definição dos pinos
const int pwmPin = 6; // Pino do PWM conectado ao motor
const int potPin = A2; // Pino do potenciômetro

void setup() {
  // Inicia o LCD
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(pwmPin, OUTPUT); // Define o pino do PWM como saída
}

void loop() {
  int potValue = analogRead(potPin); // Lê o valor do potenciômetro
  int pwmValue = map(potValue, 0, 1023, 0, 255); // Mapeia o valor para o range do PWM
  analogWrite(pwmPin, pwmValue); // Gera o PWM no pino 13

  // Calcula o duty cycle em porcentagem
  float dutyCycle = (pwmValue / 255.0) * 100;
  // Estima o RPM baseado no duty cycle - A relação precisa ser ajustada conforme o seu motor
  float estimatedRPM = dutyCycle * 4; // Exemplo de cálculo, ajuste conforme necessário

  // Mostra as informações no LCD
  lcd.setCursor(0, 0);
  lcd.print("RPM: ");
  lcd.print(estimatedRPM);
  lcd.setCursor(0, 1);
  lcd.print("Duty: ");
  lcd.print(dutyCycle);
  lcd.print("%");
  
  delay(200); // Pequeno atraso para a atualização dos valores
  lcd.clear(); // Limpa o LCD para a próxima escrita
}