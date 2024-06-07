int secs = 0;
int minutes = 0;
int hours = 0;
long interval = 1000;
long previous = 0;
long current = millis();
bool ESTADO_LED = LOW;


void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if ((current - previous) > 1000) {
    previous = current;
    ESTADO_LED = !ESTADO_LED;
    digitalWrite(13, ESTADO_LED);
    relogio();
  }
  current = millis();
}

void relogio() {

  secs += 1;
  if (secs > 59) {
    minutes += 1;
    secs = 0;
  }
  if (minutes > 59) {
    hours += 1;
    minutes = 0;
  }
  if (hours > 23) {
    hours = 0;
  }
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(secs);
}
