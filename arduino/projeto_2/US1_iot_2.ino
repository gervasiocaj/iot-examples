#include <SoftwareSerial.h>

String leitura;
float temperature;
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(4800);
}

void loop() {
  if (terminalDisponivel()) {
    leitura = lerTerminal();
    if (leitura == "TMP") {
      escreverTerminal("enviando requisicao de temperatura...");
      escreverSecundario(leitura);
    } else {
      escreverTerminal("nao entendi requisicao");
    }
  }
  
  if (secundarioDisponivel()) {
    leitura = lerSecundario();
    if (leitura == "TMP") {
      temperature = atof()
    /*if (temperature <= 18) {
      mySerial.print('GREEN');
    } else if(temperature >= 19 && temperature <= 22) {
      mySerial.print('YELLOW');
    } else if(temperature > 22) {
      mySerial.print('GREEN');
    } else {*/
      escreverTerminal(leitura);
    //}
  }
}

boolean terminalDisponivel() {
  return Serial.available();
}

boolean secundarioDisponivel() {
  return mySerial.available();
}

String lerTerminal() {
  Serial.readString();
}

String lerSecundario() {
  mySerial.readString();
}

void escreverTerminal(String dados) {
  Serial.println(dados);
}

void escreverSecundario(String dados) {
  mySerial.print(dados);
}
