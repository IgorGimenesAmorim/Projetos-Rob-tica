//v4

#include <LiquidCrystal.h>
LiquidCrystal lcd {10, 9, 8, 3, 2, 1, 0};

double pulso_baixo = 0.0;
double pulso_alto = 0.0;
double periodo = 0.0;
double RPM = 0.0;
double alimentacao = 0.0;
double motor = 0.0;
double duty = 0.0;
double sensor = 0.0;
double resist_motor = 8.0;
double potencia = 0.0;
double torque = 0.0;
int trava = 0;

void setup() {
   lcd.begin(16,2);
   lcd.clear();
   lcd.setCursor (0,0);
}

void loop() {
   pulso_alto = pulseIn(11, LOW); //(le o periodo em baixa (ativo) - o circuito funciona de forma inversa)
   if (pulso_alto < 1.0){ // se o pulso e muito baixo, na realidade o motor nao ira girar (o simulador nao descreve conforme a realidade)
     if (trava == 0){
       RPM = 0;
       torque = 0;
       lcd.print ("RPM: ");
       lcd.print (RPM);
       lcd.setCursor (0,1);
       lcd.setCursor (0,0);
       trava = 1;
     }
   }
   else {
     pulso_baixo = pulseIn(11, HIGH); //(le o periodo em alta (inativo) - o circuito funciona de forma inversa)
     periodo = pulso_alto + pulso_baixo; //calcula o periodo do sinal
     alimentacao = analogRead(0)*(5.0/1023.0); //tensao de alimentacao do circuito (valor conformado para o arduino ler)
     alimentacao = alimentacao / (1000.0/(1000.0+3900.0)); //tensao de alimentacao do circuito (real)
     sensor = analogRead(1)*(5.0/1023.0); //tensao na saida para o motor (valor conformado para o arduino ler)
     sensor = sensor / (100.0/(100.0+200.0)); //tensao na saida para o motor (real)
     if (sensor > motor){
       motor = sensor; //salvando informacao de tensao do motor
     }
     else {
       motor = motor;
     }
     duty = pulso_alto / periodo * 100.0; //calculando duty cycle atual
     RPM = (motor / alimentacao) * duty; //calculando RPM
     RPM = RPM*4630.0;
     potencia = (motor*motor)/resist_motor;
     torque = potencia / RPM ; //calculando o torque
     lcd.print ("RPM: ");
     lcd.print (RPM);
     lcd.setCursor (0,1);
     delay(200);
     lcd.clear();
     lcd.setCursor (0,0);
     trava = 0;
   }
}