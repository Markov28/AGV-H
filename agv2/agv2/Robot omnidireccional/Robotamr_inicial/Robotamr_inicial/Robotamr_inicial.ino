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
  BT.begin("Robot1");
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
  // put your main code here, to run repeatedly:
  /*if(BT.available() > 0)
  {
    char datos = BT.read();
    Serial.print(datos);
    if(datos == '1'){
      digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(5000);    
    }else
    digitalWrite(2, LOW);
  }*/

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
    if(PWMs[4] == 1){ //Gira rueda dI sentido horario
      digitalWrite(dir_mdi_A, LOW);
      digitalWrite(dir_mdi_B, HIGH); 
    }else{
      digitalWrite(dir_mdi_A, HIGH);
      digitalWrite(dir_mdi_B, LOW);   
    }
    if(PWMs[5] == 1){ //Gira rueda dd sentido horario
      digitalWrite(dir_mdd_A, LOW);
      digitalWrite(dir_mdd_B, HIGH); 
    }else{
      digitalWrite(dir_mdd_A, HIGH);
      digitalWrite(dir_mdd_B, LOW);   
    }
    if(PWMs[6] == 1){ //Gira rueda ti sentido horario
      digitalWrite(dir_mti_A, LOW);
      digitalWrite(dir_mti_B, HIGH); 
    }else{
      digitalWrite(dir_mti_A, HIGH);
      digitalWrite(dir_mti_B, LOW);   
    }
    if(PWMs[7] == 1){ //Gira rueda td sentido horario
      digitalWrite(dir_mtd_A, LOW);
      digitalWrite(dir_mtd_B, HIGH); 
    }else{
      digitalWrite(dir_mtd_A, HIGH);
      digitalWrite(dir_mtd_B, LOW);   
    }

    analogWrite(mot_di, PWMs[0]);
    analogWrite(mot_dd, PWMs[1]);
    analogWrite(mot_ti, PWMs[2]);
    analogWrite(mot_td, PWMs[3]);

    lecturaTerminada = false;
    for(int i=0;i<9;i++)
      Serial.println(PWMs[i]);
  } 
    /**if(PWMs[0] == 1){ //MOVIMIENTO EN +X
      digitalWrite(dir_mdd_A, HIGH);
      digitalWrite(dir_mdd_B, LOW);
      digitalWrite(dir_mdi_A, LOW);
      digitalWrite(dir_mdi_B, HIGH);
      digitalWrite(dir_mtd_A, LOW);
      digitalWrite(dir_mtd_B, HIGH);
      digitalWrite(dir_mti_A, HIGH);
      digitalWrite(dir_mti_B, LOW);
      
      analogWrite(mot_dd , PWMs[1]);
      analogWrite(mot_di , PWMs[1]);
      analogWrite(mot_td , PWMs[1]);
      analogWrite(mot_ti , PWMs[1]);
    }**/
  
}
