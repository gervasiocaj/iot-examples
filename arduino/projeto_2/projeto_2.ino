#include <SoftwareSerial.h>

String leitura;
int temperature;
SoftwareSerial mySerial(10, 11); // RX, TX

boolean estadoLum;
#define lumBuzzer 2
#define lumLedRed 4
#define lumLedGreen 3

void setup() {
  Serial.begin(9600);
  mySerial.begin(4800);
  estadoLum = false;
}

void loop() {
  if (terminalDisponivel()) {
    leitura = lerTerminal();
    escreverTerminal(leitura);
    if (leitura == "TMP") {
      escreverTerminal("Requisitando temperatura...");
      escreverSecundario(leitura);
    } else if (leitura == "LDR") {
      escreverTerminal("Requisitando luminosidade...");
      escreverSecundario(leitura);
      estadoLum = true;
    } else if (leitura == "NLDR") {
      escreverTerminal("Desligando luminosidade...");
      escreverSecundario(leitura);
      estadoLum = false;
    } else {
      escreverTerminal("Nao entendi...");
      escreverTerminal(leitura);
    }
  }

  if (secundarioDisponivel()) {
    leitura = lerSecundario();
   
    escreverTerminal("___________");
    escreverTerminal(leitura);
    escreverTerminal("___________");

    if (leitura == "TMP") {
    
      temperature = lerSecundario().toInt();
      escreverSecundario("TMP_LED");
      if (temperature <= 18) {
        escreverSecundario("GREEN");
      } else if (temperature >= 19 && temperature <= 22) {
        escreverSecundario("YELLOW");
      } else if(temperature > 22) {
        escreverSecundario("RED");
      }
      
    } else if (leitura == "TMP_DONE") {
      
      escreverTerminal(String(temperature) + "°C");
      escreverTerminal(String(32 + (temperature * 1.8)) + "°F");
      escreverTerminal(String(temperature + 273.15) + "°K");
      
    } else if (leitura == "LDR_DATA") {
      int luminosidade = lerSecundario().toInt();
      if (luminosidade > 500) {
        // escuro
        digitalWrite(lumLedRed, HIGH);
        digitalWrite(lumLedGreen, LOW);
        digitalWrite(lumBuzzer, HIGH);
      } else {
        // claro
        digitalWrite(lumLedRed, LOW);
        digitalWrite(lumLedGreen, HIGH);
        digitalWrite(lumBuzzer, LOW);
      }
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
