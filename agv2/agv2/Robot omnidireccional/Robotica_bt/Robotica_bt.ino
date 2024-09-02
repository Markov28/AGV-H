#include "BluetoothSerial.h"

BluetoothSerial BT;


uint8_t Init = 0;

//uint8_t Dirs [4];
int16_t PWMs[8] = {0,0,0,0,0,0,0,0};
//char dir;
int i = 0;
bool lecturaTerminada = false;

// PWMs Motores Delanteros Derecha
const int mot_ti = 23;
const int dir_mti_A = 22;
const int dir_mti_B = 21;
// Delanteros Izquierda
const int mot_td = 18;
const int dir_mtd_A = 16;
const int dir_mtd_B = 17;
// Trasero Izquierda
const int mot_dd = 26;
const int dir_mdd_A = 25;
const int dir_mdd_B = 33;
// delant izq
const int mot_di = 13;
const int dir_mdi_A = 14;
const int dir_mdi_B = 12;


void setup() {
  // put your setup code here, to run once:
  BT.begin("RobotMain");
  Serial.begin(115200);
  pinMode(2, OUTPUT);

    //Setup sentidos
  pinMode(dir_mdd_A, OUTPUT);
  pinMode(dir_mdd_B, OUTPUT);
  
  pinMode(dir_mdi_A, OUTPUT);
  pinMode(dir_mdi_B, OUTPUT);
  
  pinMode(dir_mtd_A, OUTPUT);
  pinMode(dir_mtd_B, OUTPUT);
  
  pinMode(dir_mti_A, OUTPUT);  
  pinMode(dir_mti_B, OUTPUT);
}

void loop() {

  if (BT.available() > 0) {
    //Serial.print(BT.read());
              
        if (i < 8){
          PWMs[i] = BT.read();
          i++;
        }   
        if(i == 8){
           // Init = 0;
          i = 0;
          lecturaTerminada = true;  
      }
  }
  
   
  if(lecturaTerminada == true){
    if(PWMs[4] == 1){ //Gira rueda dI sentido horario 1
      digitalWrite(dir_mdi_A, LOW);
      digitalWrite(dir_mdi_B, HIGH); 
    }else{
      digitalWrite(dir_mdi_A, HIGH);
      digitalWrite(dir_mdi_B, LOW);  
    }
    if(PWMs[5] == 1){ //Gira rueda dd sentido horario2
      digitalWrite(dir_mdi_A, LOW);
      digitalWrite(dir_mdi_B, HIGH); 
    }else{
      digitalWrite(dir_mdi_A, HIGH);
      digitalWrite(dir_mdi_B, LOW);  
    }
    if(PWMs[6] == 1){ //Gira rueda ti sentido horario3
      digitalWrite(dir_mdi_A, LOW);
      digitalWrite(dir_mdi_B, HIGH); 
    }else{
      digitalWrite(dir_mdi_A, HIGH);
      digitalWrite(dir_mdi_B, LOW);  
    }
    if(PWMs[7] == 1){ //Gira rueda td sentido horario4
      digitalWrite(dir_mdi_A, LOW);
      digitalWrite(dir_mdi_B, HIGH); 
    }else{
      digitalWrite(dir_mdi_A, HIGH);
      digitalWrite(dir_mdi_B, LOW);  
    }
    
    analogWrite(mot_di, PWMs[0]);
    analogWrite(mot_dd, PWMs[1]);
    analogWrite(mot_ti, PWMs[2]);
    analogWrite(mot_td, PWMs[3]);

    lecturaTerminada = false;
    Serial.println(PWMs[0]);
    Serial.println(PWMs[1]);
    Serial.println(PWMs[2]);
    Serial.println(PWMs[3]);
    Serial.println(PWMs[4]);
    Serial.println(PWMs[5]);
    Serial.println(PWMs[6]);
    Serial.println(PWMs[7]);
    Serial.println("--------");
    //for(int i=1;i<10;i++)
      //Serial.println(PWMs[i]);
  } 

  
}
