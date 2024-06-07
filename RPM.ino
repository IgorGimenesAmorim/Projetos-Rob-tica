#include <LiquidCrystal.h>
LiquidCrystal lcd(10, 9, 8, 3, 2, 1, 0);

double pulso_baixo = 0.0;
double pulso_alto = 0.0;
double periodo = 0.0;
double RPM = 0.0;
double duty = 0.0;
int trava = 0;

void setup() {
   lcd.begin(16,2);
   lcd.clear();
   lcd.setCursor(0,0);
}

void loop() {
   pulso_alto = pulseIn(11, LOW); // Lê o período em baixa (ativo) - o circuito funciona de forma inversa
   if (pulso_alto < 1.0) { // Se o pulso é muito baixo, na realidade o motor não irá girar (o simulador não descreve conforme a realidade)
     if (trava == 0) {
       RPM = 0;
       lcd.print("RPM: ");
       lcd.print(RPM);
       lcd.setCursor(0,1);
       trava = 1;
     }
   } else {
     pulso_baixo = pulseIn(11, HIGH); // Lê o período em alta (inativo) - o circuito funciona de forma inversa
     periodo = pulso_alto + pulso_baixo; // Calcula o período do sinal
     duty = pulso_alto / periodo * 100.0; // Calculando duty cycle atual
     
     // Aqui você pode ajustar o cálculo do RPM com base no duty cycle conforme necessário
     // Esta é uma representação simplificada que você pode querer calibrar com dados reais
     RPM = duty * 5; // Exemplo simplificado de cálculo de RPM baseado no duty cycle
     
     lcd.print("RPM: ");
     lcd.print(RPM);
     delay(200);
     lcd.clear();
     lcd.setCursor(0,0);
     trava = 0;
   }
}