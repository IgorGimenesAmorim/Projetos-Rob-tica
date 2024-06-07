//                           Universidade Estadual de Maringá
//                          Departamento de Engenharia Química
//                              Curso: Engenharia Elétrica
// Disciplina: Projeto de Sistemas Microcontrolados Professor: Luiz Carlos Campana Sperandio
//              Intregrantes: Brendow Hatschbach da Silva   RA:125513
//                            Gustavo Kauã dos Reis            124814
//                                    04/09/2023



//Incluiu-se as bibliotecas utilizadas no projeto
#include <dht11.h> //Biblioteca do DHT11
#include "SevSeg.h" //Biblioteca do Display de 7 Segmentos;

//Definiu-se variaveis e suas respectivas portas conectadas aos componentes utilizados no projeto
#define sensor 2 //Variavel do DHT11 conectado à porta digital 2;
#define botao A5 //Variavel do botao conectado à porta analogica A5;
#define vermelho A0 //Variavel do Led Vermelho conectado à porta analogica A0;
#define amarelo A1 //Variavel do Led Amarelo conectado à porta analogica A1;
#define verde A2 //Variavel do Led Verde conectado à porta analogica A2;

//Inicializou-se as bibliotecas
SevSeg sevseg;
dht11 DHT11;

//Criou-se as variaveis utilizadas ao longo do código
unsigned long tempoInicial = 0;
unsigned long intervaloAtraso = 1000;
int CONTADOR = 0;
int BT_ATUAL = 0;
int BT_ANTERIOR = 0;
int celsius = 0;
int farenheit = 0;
int kelvin = 0; 


void setup()
{
  byte numDigits = 4; //Parte da biblioteca SevSeg, onde definiu-se o número de digitos utilizados no Display;
  byte digitPins[] = {6, 5, 4, 3}; //Parte da biblioteca SevSeg, onde definiu-se as portas digitais conectadas aos Digitos de 1-4;
  byte segmentPins[] = {13, 12, 11, 10, 9, 8, 7}; //Parte da biblioteca SevSeg, onde definiu-se as portas digitais conectadas aos Segmentos do Display de A-G;
  bool resistorsOnSegments = true; //Parte da biblioteca SevSeg, onde definiu-se queexiste um resistor conectado para cada segmneto do Display;
  bool updateWithDelaysIn = true; 
  byte hardwareConfig = COMMON_CATHODE; //Parte da biblioteca SevSeg, onde definiu-se o Display como Catodo comum;
  bool leadingZeros = false; //Parte da biblioteca SevSeg, onde definiu-se que não se coloque 0 à esquerda do número;
  bool disableDecPoint = true; //Parte da biblioteca SevSeg, onde se desligou o ponto decimal;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelaysIn, leadingZeros, disableDecPoint); //Parte da biblioteca SevSeg, onde todas as informações acima são definidas no Display; 

  //Configuração dos pinos de entrada e saída
  pinMode(botao, INPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  //Configuraçao do estados dos pinos dos LEDs conectados
  digitalWrite(vermelho, HIGH);
  digitalWrite(amarelo, LOW);
  digitalWrite(verde, LOW);

  tempoInicial = millis();
}


void loop() {
  unsigned long tempoAtual = millis();
  
  //Função que define um delay de 1 segundo entre as leituras do sensor DHT; 
  if(tempoAtual - tempoInicial >= intervaloAtraso){
    DHT11.read(sensor); //Função da biblioteca do DHT11 responsável por fazer a leitura dos valroes do sensor;
    tempoInicial = tempoAtual;
  }
  
  
  celsius = (int)DHT11.temperature; //Aloca o valor de temperatura lida do DHT na variavel celsius;
  farenheit = (celsius * 1.8) + 32; //Converte celsius para farenheit;
  kelvin = celsius + 273; //Converte celsius para Kelvin;
   


  BT_ATUAL = digitalRead(botao);
  
  //Função de leitura de ativação do botão;
  if(BT_ATUAL == 1 && BT_ANTERIOR == 0){
    CONTADOR++; //Incrementa +1 para a variavel Contador toda vez que o botão é ativado;
  }
  BT_ANTERIOR = BT_ATUAL;
  
  //Função que se executa quando o Contador for igual a 0
  if(CONTADOR == 0){
    digitalWrite(vermelho, HIGH); //Liga-se o Led Vermelho;
    digitalWrite(verde, LOW); //Apaga-se o Verde;
    sevseg.setNumber(celsius); //Função que define o valor exibido no Display, Além disso passa o valor de Temperatura em Celsius para o Display;
  }
  //Função que se executa quando o Contador for igual a 1
  if(CONTADOR == 1){
    digitalWrite(amarelo, HIGH); //Liga-se o Led Amarelo;
    digitalWrite(vermelho, LOW); //Apaga-se o Led Vermelho;
    sevseg.setNumber(farenheit); //Passa o valor de Temperatura em Farenheit para o Display;
  }
  //Função que se executa quando o Contador for igual a 2
  if(CONTADOR == 2){
    digitalWrite(verde, HIGH); //Liga-se o Led Verde;
    digitalWrite(amarelo, LOW); //Apaga-se o Led Amarelo;
    sevseg.setNumber(kelvin); //Passa o valor de Temperatura em Kelvin para o Display;
  }
  //Função que se executa quando o Contador for maior ou igual a 3
  if(CONTADOR >= 3){
    CONTADOR = 0; //Contador volta para 0;
  }
  sevseg.refreshDisplay(); //Atualiza o Display de 7 Segmentos;
}


