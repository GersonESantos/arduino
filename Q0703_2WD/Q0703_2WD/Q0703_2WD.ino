/*
     CÓDIGO:	Q0703
     AUTOR:		BrincandoComIdeias
     ACOMPANHE:	https://www.youtube.com/brincandocomideias ; https://www.instagram.com/canalbrincandocomideias/
     APRENDA:	https://cursodearduino.net/ ; https://cursoderobotica.net
     COMPRE:	https://www.arducore.com.br/
     SKETCH:  2WD com controle PS2
     DATA:		25/09/2021
*/

// INCLUSÃO DE BIBLIOTECAS
#include <PS2X_lib.h>

// DEFINIÇÕES DE PINOS
#define pinFarolE 8
#define pinFarolD 7
#define pinPiscaE A0
#define pinPiscaD A3
#define pinFreioE A1
#define pinFreioD A2

#define dirFrente 5
#define dirTras   3
#define esqFrente 9
#define esqTras   6

// DEFINIÇÕES
#define FRENTE 1
#define PARADO 0
#define TRAS  -1

#define velocidadeE 100
#define velocidadeD 110

// INSTANCIANDO OBJETOS
PS2X ps2x;

// DECLARAÇÃO DE FUNÇÕES 
void configuraControle();
void configuraLeds();
void controlaLeds();

// DECLARAÇÃO DE VARIÁVEIS
bool piscaE, piscaD;
bool freio, farol;

void setup() {
  Serial.begin(9600);

  configuraLeds();
  configuraControle();

  // CONFIGURAÇÃO DOS PINOS DA PONTE-H
  pinMode(dirFrente, OUTPUT);
  pinMode(dirTras,   OUTPUT);
  pinMode(esqFrente, OUTPUT);
  pinMode(esqTras,   OUTPUT);

  // DEIXANDO OS MOTORES PARADOS
  digitalWrite(dirFrente, LOW);
  digitalWrite(dirTras,   LOW);
  digitalWrite(esqFrente, LOW);
  digitalWrite(esqTras,   LOW);

}

void loop() {
  ps2x.read_gamepad();

  if (ps2x.Button(PSB_PAD_UP)) { // ANDAR PRA FRENTE
    // MOTOR DIREITO PARA FRENTE
    analogWrite(dirFrente,  velocidadeD);
    analogWrite(dirTras,    LOW);

    // MOTOR ESQUERDO PARA FRENTE
    analogWrite(esqFrente,  velocidadeE);
    analogWrite(esqTras,    LOW);

  } else if (ps2x.Button(PSB_PAD_RIGHT)) { // VIRAR PRA DIREITA
    // MOTOR DIREITO PARA TRAS
    analogWrite(dirFrente,  LOW);
    analogWrite(dirTras,    velocidadeD);

    // MOTOR ESQUERDO PARA FRENTE
    analogWrite(esqFrente,  velocidadeE);
    analogWrite(esqTras,    LOW);

  } else if (ps2x.Button(PSB_PAD_LEFT)) { // VIRAR PRA ESQUERDA
    // MOTOR DIREITO PARA FRENTE
    analogWrite(dirFrente,  velocidadeD);
    analogWrite(dirTras,    LOW);

    // MOTOR ESQUERDO PARA TRAS
    analogWrite(esqFrente,  LOW);
    analogWrite(esqTras,    velocidadeE);

  } else if (ps2x.Button(PSB_PAD_DOWN)) { // ANDAR PRA TRAS
    // MOTOR DIREITO PARA TRAS
    analogWrite(dirFrente,  LOW);
    analogWrite(dirTras,    velocidadeE);

    // MOTOR ESQUERDO PARA TRAS
    analogWrite(esqFrente,  LOW);
    analogWrite(esqTras,    velocidadeD);

  } else { // FICAR PARADO
    digitalWrite(dirFrente, LOW);
    digitalWrite(dirTras,   LOW);
    digitalWrite(esqFrente, LOW);
    digitalWrite(esqTras,   LOW);
  }

  controlaLeds();
  delay(50);
}

// IMPLEMENTO DE FUNÇÕES
void configuraControle() {
  int erroControle = ps2x.config_gamepad(13, 11, 10, 12, true, true);
  if (!erroControle) {
    Serial.println("Controle encontrado GersonES");
  } else {
    Serial.println("Controle não encontrado");
    while (erroControle) {
      erro();
      if (bitRead(millis(), 11)) erroControle = ps2x.config_gamepad(13, 11, 10, 12, true, true);
    }
  }
}
void configuraLeds() {
  pinMode(pinFarolE, OUTPUT);
  pinMode(pinFarolD, OUTPUT);
  pinMode(pinPiscaE, OUTPUT);
  pinMode(pinPiscaD, OUTPUT);
  pinMode(pinFreioE, OUTPUT);
  pinMode(pinFreioD, OUTPUT);

  digitalWrite(pinFarolE, LOW);
  digitalWrite(pinFarolD, LOW);
  digitalWrite(pinPiscaE, LOW);
  digitalWrite(pinPiscaD, LOW);
  digitalWrite(pinFreioE, LOW);
  digitalWrite(pinFreioD, LOW);
}

void controlaLeds() {
  if (ps2x.NewButtonState()) {
    if (ps2x.ButtonPressed(PSB_PINK)) {
      piscaE = !piscaE;
    }
    if (ps2x.ButtonPressed(PSB_RED)) {
      piscaD = !piscaD;
    }
    if (ps2x.ButtonPressed(PSB_BLUE)) {
      freio = !freio;
    }
    if (ps2x.ButtonPressed(PSB_GREEN)) {
      farol = !farol;
    }
  }

  if (piscaE) digitalWrite(pinPiscaE, bitRead(millis(), 9));
  else digitalWrite(pinPiscaE, LOW);

  if (piscaD) digitalWrite(pinPiscaD, bitRead(millis(), 9));
  else digitalWrite(pinPiscaD, LOW);

  if (farol) {
    digitalWrite(pinFarolE, HIGH);
    digitalWrite(pinFarolD, HIGH);
  }
  else {
    digitalWrite(pinFarolE, LOW);
    digitalWrite(pinFarolD, LOW);
  }

  if (freio) {
    digitalWrite(pinFreioE, HIGH);
    digitalWrite(pinFreioD, HIGH);
  }
  else {
    digitalWrite(pinFreioE, LOW);
    digitalWrite(pinFreioD, LOW);
  }
}

void erro() {
  digitalWrite(pinFarolE, bitRead(millis(), 7));
  digitalWrite(pinFarolD, bitRead(millis(), 7));
  digitalWrite(pinPiscaE, bitRead(millis(), 7));
  digitalWrite(pinPiscaD, bitRead(millis(), 7));
  digitalWrite(pinFreioE, bitRead(millis(), 7));
  digitalWrite(pinFreioD, bitRead(millis(), 7));
}
