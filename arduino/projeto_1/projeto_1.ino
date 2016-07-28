#include <Thermistor.h>
#include <SoftwareSerial.h>
 
#define tmpLedRed 2
#define tmpLedYellow 3
#define tmpLedGreen 4

#define tmpSensor A0
#define lumSensor A1

#define TWO_SECONDS 2000
#define TEN_SECONDS 10000
 
Thermistor temp(tmpSensor);
SoftwareSerial mySerial(10, 11); // RX, TX

String leitura;
int temperature;

long timeoutRed, timeoutYellow, timeoutGreen, timeoutLdr;

void setup() {
  Serial.begin(9600);
  mySerial.begin(4800);

  timeoutRed = 0;
  timeoutYellow = 0;
  timeoutGreen = 0;
  timeoutLdr = 0;
 
  pinMode(tmpLedRed, OUTPUT);
  pinMode(tmpLedGreen, OUTPUT);
  pinMode(tmpLedYellow, OUTPUT);
}
 
void loop() {
  if (secundarioDisponivel()) {
    leitura = lerSecundario();
    
    escreverTerminal("__________");
    escreverTerminal(leitura);
    escreverTerminal("__________");
    
    if (leitura == "TMP") {
      
      escreverTerminal("entendi, enviando temperatura...");
      escreverSecundario("TMP");
      escreverSecundario(String(temp.getTemp()));
      
    } else if (leitura == "TMP_LED") {

      leitura = lerSecundario();
      escreverTerminal("Alterar para: " + leitura);
      
      if (leitura == "GREEN") {
        digitalWrite(tmpLedGreen, HIGH);
        timeoutGreen = millis() + TEN_SECONDS;
      } else if (leitura == "YELLOW") {
        digitalWrite(tmpLedYellow, HIGH);
        timeoutYellow = millis() + TEN_SECONDS;
      } else if (leitura == "RED") {
        digitalWrite(tmpLedRed, HIGH);
        timeoutRed = millis() + TEN_SECONDS;
      }
      escreverSecundario("TMP_DONE");
    
    } else {
      
      escreverTerminal("nao entendi: ");
      escreverTerminal(leitura);
      
    }
  }
  if (timeoutGreen < millis()) {
    digitalWrite(tmpLedGreen, LOW);
  }
  if (timeoutYellow < millis()) {
    digitalWrite(tmpLedYellow, LOW);
  }
  if (timeoutRed < millis()) {
    digitalWrite(tmpLedRed, LOW);
  }
  if (timeoutLdr < millis()) {
      escreverTerminal("Enviando luminosidade...");
      escreverSecundario("LDR_DATA");
      escreverSecundario(String(analogRead(lumSensor)));
      timeoutLdr = millis() + TWO_SECONDS;
  }
}

boolean terminalDisponivel() {
  return Serial.available();
}

boolean secundarioDisponivel() {
  return mySerial.available();
}

String lerTerminal() {
  return Serial.readString();
}

String lerSecundario() {
  String a = mySerial.readStringUntil('\r');
  a.trim();
  return a;
}

void escreverTerminal(String dados) {
  Serial.println(dados);
}

void escreverSecundario(String dados) {
  mySerial.println(dados);
}
