#include <SPI.h>  //Se incluye la libreria SPI.h
#include <nRF24L01.h> //Se incluye la libreria nRF24L01.h
#include <RF24.h> //Se incluye la libreria RF24.h

#define buttonPin1 2 //Boton izquierda
#define buttonPin2 3 //Boton arriba
#define buttonPin3 4 //Boton derecha
#define buttonPin4 5 //Boton abajo

int buttonState1 = 0; //Estado del boton 1
int buttonState2 = 0; //Estado del boton 2
int buttonState3 = 0; //Estado del boton 3
int buttonState4 = 0; //Estado del boton 4
RF24 radio(9, 8); // pines CE y CSN respectivamente

const byte address[6] = "00002"; //Direccion para la comunicacion entre modulos

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP); //entrada con resistencia interna modo pullup activada
  pinMode(buttonPin2, INPUT_PULLUP); //entrada con resistencia interna modo pullup activada
  pinMode(buttonPin3, INPUT_PULLUP); //entrada con resistencia interna modo pullup activada
  pinMode(buttonPin4, INPUT_PULLUP); //entrada con resistencia interna modo pullup activada
  Serial.begin(9600); //Inicializa a 9600 baudios
  radio.begin();  //Inicializa la libreria de radio
  radio.openWritingPipe(address); //Busca la direccion de comunicacion establecida en modo transmisor
  radio.setPALevel(RF24_PA_MIN);  //Potencia de transmision (minimo)
  radio.stopListening(); //Establece el modulo como transmisor
}
void loop() {
  buttonState1 = digitalRead(buttonPin1); //Lectura del valor del boton de izquierda
  buttonState2 = digitalRead(buttonPin2); //Lectura del valor del boton de arriba
  buttonState3 = digitalRead(buttonPin3); //Lectura del valor del boton de derecha
  buttonState4 = digitalRead(buttonPin4); //Lectura del valor del boton de abajo

  if (buttonState1 == 1)  //Si no se presiona el boton de izquierda
  {
    buttonState1 = 1;
  }
  else  if (buttonState1 == 0) //Si se presiona el boton de izquierda
  {
    buttonState1 = 0;
  }
  
  if (buttonState2 == 1)  //Si no se presiona el boton de arriba
  {
    buttonState2 = 3;
  }
  else  if (buttonState2 == 0) //Si se presiona el boton de arriba
  {
    buttonState2 = 2;
  }

  if (buttonState3 == 1)  //Si no se presiona el boton de derecha
  {
    buttonState3 = 5;
  }
  else  if (buttonState3 == 0) //Si se presiona el boton de derecha
  {
    buttonState3 = 4;
  }

   if (buttonState4 == 1)  //Si no se presiona el boton de abajo
  {
    buttonState4 = 7;
  }
  else  if (buttonState4 == 0) //Si se presiona el boton de abajo
  {
    buttonState4 = 6;
  }
  
  Serial.print(buttonState1); //Imprime en monitor serial el valor del boton de izquierda
  Serial.print("\t"); //separacion
  Serial.print(buttonState2); //Imprime en monitor serial el valor del boton de arriba
  Serial.print("\t"); //separacion
  Serial.print(buttonState3); //Imprime en monitor serial el valor del boton de derecha
  Serial.print("\t"); //separacion
  Serial.print(buttonState4); //Imprime en monitor serial el valor del boton de abajo
  Serial.print("\t"); //separacion
  
  radio.write(&buttonState1, sizeof(buttonState1)); //Manda el valor del boton de izquierda, estableciendo el tamaño en bytes de la variable
  radio.write(&buttonState2, sizeof(buttonState2)); //Manda el valor del boton de arriba, estableciendo el tamaño en bytes de la variable
  radio.write(&buttonState3, sizeof(buttonState3)); //Manda el valor del boton de derecha, estableciendo el tamaño en bytes de la variable
  radio.write(&buttonState4, sizeof(buttonState4)); //Manda el valor del boton de abajo, estableciendo el tamaño en bytes de la variable

}
