#include <Thermistor.h>
#include <SoftwareSerial.h>
 
#define ledRed 2
#define ledYellow 3
#define ledGreen 4
 
Thermistor temp(A0);
SoftwareSerial mySerial(10, 11); // RX, TX

String leitura;
int temperature;

void setup() {
  Serial.begin(9600);
  mySerial.begin(4800);
 
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
      escreverSecundario(temp.getTemp());
      
    } else if (leitura == "TMP_LED") {
      
      if (leitura == "GREEN") {
        digitalWrite(ledGreen, HIGH);
      } else if (leitura == "YELLOW") {
        digitalWrite(ledYellow, HIGH);
      } else if (leitura == "RED") {
        digitalWrite(ledRed, HIGH);
      }
      escreverSecundario("TMP_DONE");
      
    } else {
      
      escreverTerminal("nao entendi: ");
      escreverTerminal(leitura);
      
    }
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
  mySerial.print(dados);
}
