

//CONECTION SDA

//CONECTION SCL

bool w1Neg,w2Neg,w3Neg,w4Neg;
bool band1=false;
int16_t w1=0,w2=0,w3=0,w4=0;

//#include <SoftwareSerial.h>
#include "BluetoothSerial.h"
#include <Wire.h>
BluetoothSerial BT;
byte i2c_rcv; 
//unsigned long time_start;

//Motor delantero derecha
const int motor_dd_dir = 4, motor_dd_step = 5; 

//Motor delantero izquierda
const int motor_di_dir = 13, motor_di_step = 27; 

//Motor trasero derecha
const int motor_td_dir = 16, motor_td_step = 17; 

//Motor trasero izquierda
const int motor_ti_dir = 25, motor_ti_step = 26; 

void setup()
{
  Wire.begin(); // join I2C bus as the master
  BT.begin("MAESTRO");

  Serial.begin(9600);
  //XIAO 1
  // pinMode(dir1,OUTPUT);
  // pinMode(dir2,OUTPUT);
  // pinMode(dir3,OUTPUT);
  // pinMode(dir4,OUTPUT);

  pinMode(motor_dd_dir,OUTPUT);
  pinMode(motor_dd_step,OUTPUT);
  pinMode(motor_di_dir,OUTPUT);
  pinMode(motor_di_step,OUTPUT);
  pinMode(motor_td_dir,OUTPUT);
  pinMode(motor_td_step,OUTPUT);
  pinMode(motor_ti_dir,OUTPUT);
  pinMode(motor_ti_step,OUTPUT);



}
// void clearBluetoothBuffer() {
//   while (BT.available()) {
//     BT.read(); // Lee y descarta los datos del búfer
//   }
// }
//Copy code
unsigned long lastStepTime = 0; // Variable para almacenar el tiempo del último paso del motor
unsigned long stepInterval = 1; // Intervalo entre pasos (en microsegundos), ajusta según la velocidad deseada del motor
int stepsRemaining = 1600; // Número de pasos restantes para completar una revolución

char comando = 's';
int vel = 130;
void moveMotor(int stepPin, int dirPin, bool dir, int wn) {
  unsigned long currentTime = micros(); // Obtener el tiempo actual en microsegundos

  if (currentTime - lastStepTime >= stepInterval) { // Verificar si ha pasado el tiempo suficiente desde el último paso
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(wn); // Ajusta este valor según la velocidad deseada del motor
    digitalWrite(stepPin, LOW);
    delayMicroseconds(wn); // Ajusta este valor según la velocidad deseada del motor

    lastStepTime = currentTime; // Actualizar el tiempo del último paso
    stepsRemaining--; // Decrementar el número de pasos restantes
  }

  // Establecer la dirección después de mover los pasos
  digitalWrite(dirPin, dir);

  if (stepsRemaining <= 0) {
    digitalWrite(stepPin, LOW); // Detener el movimiento del motor cuando se completan los 800 pasos
  }
}
void loop()
{  

  if(BT.available()>0){
    comando = BT.read();
    switch(comando){
      case 'a':
        digitalWrite(motor_dd_dir,HIGH);
        digitalWrite(motor_di_dir,LOW);
        digitalWrite(motor_td_dir,HIGH);
        digitalWrite(motor_td_dir,LOW);
      break;
      case 'b':
        digitalWrite(motor_dd_dir,LOW);
        digitalWrite(motor_di_dir,HIGH);
        digitalWrite(motor_td_dir,LOW);
        digitalWrite(motor_td_dir,HIGH);
      break;
      case 'd':
        digitalWrite(motor_dd_dir,HIGH);
        digitalWrite(motor_di_dir,HIGH);
        digitalWrite(motor_td_dir,LOW);
        digitalWrite(motor_td_dir,LOW);
      break;
      case 'i':
        digitalWrite(motor_dd_dir,LOW);
        digitalWrite(motor_di_dir,LOW);
        digitalWrite(motor_td_dir,HIGH);
        digitalWrite(motor_td_dir,HIGH);
      break;
      case 's':
        digitalWrite(motor_dd_step,LOW); 
        digitalWrite(motor_di_step,LOW); 
        digitalWrite(motor_td_step,LOW); 
        digitalWrite(motor_ti_step,LOW); 
      break;

    }
    if(comando!='s'){
      for(int x = 0; x < 100; x++) {          
        digitalWrite(motor_dd_step,HIGH);   
        delayMicroseconds(vel);
        digitalWrite(motor_dd_step,LOW);   
        delayMicroseconds(vel);
        digitalWrite(motor_di_step,HIGH);   
        delayMicroseconds(vel);
        digitalWrite(motor_di_step,LOW);   
        delayMicroseconds(vel);
        digitalWrite(motor_td_step,HIGH);   
        delayMicroseconds(vel);
        digitalWrite(motor_td_step,LOW);   
        delayMicroseconds(vel);
        digitalWrite(motor_ti_step,HIGH);   
        delayMicroseconds(vel);
        digitalWrite(motor_ti_step,LOW);   
        delayMicroseconds(vel);
      }
    }
    Serial.print(comando);
    
    
  }
   
}

