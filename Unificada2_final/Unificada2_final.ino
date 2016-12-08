#include <Servo.h>

#define pinServo1 4
#define pinServo2 5
#define pinLED  2  //pino do LED da água
#define pinNXT  A0


Servo servo1, servo2, servo3; 
int pos1 = 100; // posiçao final do servo com amostra 1 
int pos2 = 100; // posição final do servo com amostra 2
int pos;
double lastMillis = 0;
char ch;
bool trava = false;


void setup() {
 
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);//indica tensão 0

  pos = 0;
  
  servo1.attach(pinServo1); //pinServo1 = 4
  servo2.attach(pinServo2); //pinServo2 = 5
  pinMode(pinLED,OUTPUT); //led indicativo de água
   
  servo1.write(pos);// seta posição inicial no servo1
  servo2.write(pos);// seta posição inicial no servo2

  //readNXT(sensorValue);
  //moveServo1();
  //moveServo2();

}

void moveServo1(){ //funcao para movimentar servo1
  for (pos = 0; pos <= pos1; pos += 1) { //roda o servo1 180 graus com incrementos de 1
      servo1.write(pos);
      delay(15);
  }
  delay(3000);
  servo1.write(0);
  delay(3000);
}

void moveServo2(){ //funcao para movimentar servo2
  for (pos = 0; pos <= pos2; pos += 1) { //roda o servo2 180 graus com incrementos de 1
      servo2.write(pos);
      delay(15);
  }
  delay(3000);
  servo2.write(0);
  delay(3000);
}

void water(){ //funcao para regar
  if(trava){
    if(millis() - lastMillis < 2000){ //Liga o LED por 2 segundos
      digitalWrite(pinLED, HIGH);
    }
    else if(millis() - lastMillis <10000){ // Desliga o LED por 8 segundos
      digitalWrite(pinLED, LOW);
    }
    else{ //zera o contador e volta pra primeira opção
      lastMillis = millis();
    }   
  }
  else{ 
    digitalWrite(pinLED, LOW);
  }
}

float readNXT(int sensor){ //funcao para ler sinal do NXT 
  float voltage = sensor*(5.0/1023.0);
  delay(100);
  Serial.println(voltage);
  return voltage;
}

void loop() {
  // put your main code here, to run repeatedly:
  float volt;
  volt = readNXT(analogRead(pinNXT));
  Serial.println(volt);

  if (volt != 0)  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  
  if (volt > 4 && !trava){
     moveServo1();
     moveServo2();
     trava = true;
  }
  else if (volt < 3){
     trava = false;
  }
  
  water();
}
