// creato da JURY CAIULO

#include <LedControl.h>
#include <IRremote.h>

int stato = 0;

#define TRIG_PIN 4
#define ECHO_PIN 5

const byte IR_RECEIVE_PIN = 2;

LedControl lc=LedControl(12,11,10,1);

decode_results results;
unsigned long delaytime=600;

  byte G[8]={ B00111100,B01000000,B01000010,B01000100,B01001000,B01010011,B01000010,B00111110};
  byte P[8]={ B00000000,B01000110,B01100110,B01110110,B01111110,B01110110,B01100110,B01000110};

void setup() {
  Serial.begin(9600);
  
  pinMode(7, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  digitalWrite(TRIG_PIN, LOW);

  lc.shutdown(0,false);
  lc.setIntensity(0,5);
  lc.clearDisplay(0);
  
  for(int r =0; r<8; r++){
  lc.setRow(0, r, G[r]);
  delay(100);
}
}

void loop() { 

 digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long tempo = pulseIn(ECHO_PIN, HIGH);
  float distanza = 0.03438 * tempo / 2;

if(digitalRead(7) == LOW){
 stato=1;
}

switch (stato) {
    case 0:
    if (IrReceiver.decode())
   {
      String ir_code = String(IrReceiver.decodedIRData.command, HEX);
      Serial.println(ir_code);

      IrReceiver.resume();
      
      if(ir_code == "40"){
  digitalWrite(3, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
      }
      
  if(ir_code == "45"){
  digitalWrite(3, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  }
  
  if(ir_code == "15"){
  stato=1;
  }
  
  if(ir_code == "7"){
  digitalWrite(3, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  }
  
  if(ir_code == "9"){
  digitalWrite(3, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
   }
   
   if(ir_code == "19"){
  digitalWrite(3, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
      }
   }
    break; 
    case 1:
     
  lc.clearDisplay(0);
  for(int r =0; r<8; r++){
  lc.setRow(0, r, P[r]);

  }
  digitalWrite(3, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);

if(distanza <= 10){
  stato=2;
}

    break; 
    case 2:
   ostacolo();
if(distanza > 10){
  stato=1;
}
  }
}

void ostacolo(){
  Serial.println("OSTACOLO!");
  digitalWrite(3, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(2000);
  digitalWrite(3, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(6500);
  stato=1;
}
