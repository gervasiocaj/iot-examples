#include <Thermistor.h>
#include <SoftwareSerial.h>
 
#define ledRed 2
#define ledYellow 3
#define ledGreen 4

#define TEN_SECONDS 10000
 
Thermistor temp(A0);
SoftwareSerial mySerial(10, 11); // RX, TX

String leitura;
int temperature;

long timeoutRed, timeoutYellow, timeoutGreen;

void setup() {
  Serial.begin(9600);
  mySerial.begin(4800);

  timeoutRed = 0;
  timeoutYellow = 0;
  timeoutGreen = 0;
 
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
}
 
void loop() {
  if (secundarioDisponivel()) {
    leitura = lerSecundario();
    delay(1);
    escreverTerminal("Recebido: ");
    escreverTerminal(leitura);
    
    if (leitura == "TMP") {
      
      escreverTerminal("entendi, enviando temperatura...");
      escreverSecundario("TMP");
      escreverSecundario(String(temp.getTemp()));
      
    } else if (leitura == "TMP_LED") {

      leitura = lerSecundario();
      if (leitura == "GREEN") {
        digitalWrite(ledGreen, HIGH);
        timeoutGreen = millis() + TEN_SECONDS;
      } else if (leitura == "YELLOW") {
        digitalWrite(ledYellow, HIGH);
        timeoutYellow = millis() + TEN_SECONDS;
      } else if (leitura == "RED") {
        digitalWrite(ledRed, HIGH);
        timeoutRed = millis() + TEN_SECONDS;
      }
      escreverSecundario("TMP_DONE");
      
    } else {
      
      escreverTerminal("nao entendi: ");
      escreverTerminal(leitura);
      
    }
  }
  if (timeoutGreen < millis()) {
    digitalWrite(ledGreen, LOW);
  }
  if (timeoutYellow < millis()) {
    digitalWrite(ledYellow, LOW);
  }
  if (timeoutRed < millis()) {
    digitalWrite(ledRed, LOW);
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
  return mySerial.readStringUntil('\r');
}

void escreverTerminal(String dados) {
  Serial.println(dados);
}

void escreverSecundario(String dados) {
  mySerial.println(dados);
}
