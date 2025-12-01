#include <SPI.h>  //Se incluye la libreria SPI.h
#include <nRF24L01.h> //Se incluye la libreria nRF24L01.h
#include <RF24.h> //Se incluye la libreria RF24.h

#define izqA 3 //Avanza llanta izquierda
#define izqB 5 //Retroceso llanta izquierda
#define derA 6 //Avanza llanta derecha
#define derB 10 //Retroceso llanta derecha
int vel = 255; // Velocidad de los motores (0-255)
int paro = 0;  //Determina cuando se deja de presionar un boton

int buttonState = 0; //Señal captada del modulo NRF24L01

RF24 radio(9, 8); // pines CE y CSN respectivamente
const byte address[6] = "00002"; //Direccion para la comunicacion entre modulos

void setup() {
  Serial.begin(9600); //Inicializa a 9600 baudios
  
  pinMode(derA, OUTPUT); //Salida digital PWM de avanza llanta izquierda
  pinMode(derB, OUTPUT); //Salida digital PWM de retroceso llanta izquierda
  pinMode(izqA, OUTPUT); //Salida digital PWM de avanza llanta derecha
  pinMode(izqB, OUTPUT); //Salida digital PWM de retroceso llanta derecha

  radio.begin();  //Inicializa la libreria de radio
  radio.openReadingPipe(0, address);  //Busca la direccion de comunicacion establecida en modo receptor
  radio.setPALevel(RF24_PA_MIN);  //Potencia de transmision (minimo)
}
void loop() {
  radio.startListening(); //Establece el modulo como receptor
  while (!radio.available()); //Mientras la comunicación reciba una señal entrante del modulo
  radio.read(&buttonState, sizeof(buttonState)); //Lee la señal recibida y la almacena
  Serial.println(buttonState);  //Muestra en monitor serial el valor recibido


  
   if (buttonState == 0 && paro == 0) { //Si el boton de izquierda esta presionado
    analogWrite(izqB, vel); //Retrocede la llanta izquierda
    analogWrite(derA, vel); //Avanza la llanta derecha
    paro = 1;
  } else if (buttonState == 1 && paro == 1){  //Si el boton de izquierda se deja de presionar
    analogWrite(izqB, 0); //Se detiene la llanta izquierda retroceso
    analogWrite(derA, 0); //Se detiene la llanta derecha avance
    paro = 0;
  }

   if (buttonState == 2 && paro == 0) { //Si el boton de arriba esta presionado
  analogWrite(izqA, vel); //Izquierda Avanza
    analogWrite(derA, vel); //Derecha Avanza
    paro = 2;
  } else if (buttonState == 3 && paro == 2){  //Si el boton de arriba se deja de presionar
    analogWrite(izqA, 0); //Se detiene la llanta izquierda avance
    analogWrite(derA, 0); //Se detiene la llanta derecha avance
    paro = 0;
  }

     if (buttonState == 4 && paro == 0) { //Si el boton de derecha esta presionado
    analogWrite(izqA, vel); //Izquierda Avanza
    analogWrite(derB, vel); //Derecha Retrocede
    paro = 3;
  } else if (buttonState == 5 && paro == 3){  //Si el boton de derecha se deja de presionar
    analogWrite(izqA, 0); //Se detiene la llanta izquierda avance
    analogWrite(derB, 0); //Se detiene la llanta derecha retroceso
    paro = 0;
  }

    if (buttonState == 6 && paro == 0) {  //Si el boton de abajo esta presionado
    analogWrite(izqB, vel); //Izquierda retrocede
    analogWrite(derB, vel); //Derecha retrocede
    paro = 4;
  } else if (buttonState == 7 && paro == 4){  //Si el boton de abajo se deja de presionar
    analogWrite(izqB, 0); //Se detiene la llanta izquierda retroceso
    analogWrite(derB, 0); //Se detiene la llanta derecha retroceso
    paro = 0;
  }
}
