#include<SoftwareSerial.h>

#define    afull        3
#define    athree4      4
#define    ahalf        5
#define    aone4        6
#define    aempty       7
#define    motor       13
int state = 0, full = 0, three4 = 0, half = 0, one4 = 0, empty = 0;

SoftwareSerial BTSerial(10,11);           //TX |RX

void setup() {

  pinMode(afull, INPUT);
  pinMode(athree4, INPUT);
  pinMode(ahalf, INPUT);
  pinMode(aone4, INPUT);
  pinMode(aempty, INPUT);
  pinMode(motor, OUTPUT);
  
  void setmotor();

  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.println("water");
  BTSerial.println("water");
}

void loop() {

  full = digitalRead(afull);
  three4 = digitalRead(athree4);
  half = digitalRead(ahalf);
  one4 = digitalRead(aone4);
  empty = digitalRead(aempty);


    if(empty == HIGH && one4 == HIGH && half == HIGH && three4 == HIGH && full == HIGH)
    {
      state = 1;                                                                // WATER BELOW EMPTY
      setmotor(state);
      Serial.println("WATER BELOW EMPTY");
      BTSerial.println("*b0% \t \t Motor ON \n* *A0*");
      delay(500);
    }

    
    if(empty == LOW && one4 == HIGH && half == HIGH && three4 == HIGH && full == HIGH)
    {
      setmotor(state);                                                          //WATER IS BELOW 1/4
      Serial.println("WATER IS BELOW 1/4");
      BTSerial.print("*bBelow 25% \t \t* *A25*");
      if (state == 1)
      BTSerial.println("*bMOTOR ON \n*");
      else
      BTSerial.println("*bMOTOR OFF \n*");
      delay(500);
    }

    
    if(empty == LOW && one4 == LOW && half == HIGH && three4 == HIGH && full == HIGH)
    {
      setmotor(state);                                                          //WATER IS BELOW HALF
      Serial.println("WATER IS BELOW HALF");
      BTSerial.print("*bBelow 50% \t \t* *A50*");
        if (state == 1)
      BTSerial.println("*bMOTOR ON \n*");
      else
      BTSerial.println("*bMOTOR OFF \n*");
      delay(500);
    }

    
    if(empty == LOW && one4 == LOW && half == LOW && three4 == HIGH && full == HIGH)
    {
      setmotor(state);                                                          //WATER IS BELOW 3/4
      Serial.println("WATER IS BELOW 3/4");
      BTSerial.print("*bBelow 75% \t \t* *A75*");
        if (state == 1)
      BTSerial.println("*bMOTOR ON \n*");
      else
      BTSerial.println("*bMOTOR OFF \n*"); 
      delay(500);
    }


    if(empty == LOW && one4 == LOW && half == LOW && three4 == LOW && full == HIGH)
    {
      setmotor(state);                                                          //WATER IS BELOW FULL
      Serial.println("WATER IS BELOW FULL");
      BTSerial.print("*bAbove 75% \t \t* *A85*");
        if (state == 1)
      BTSerial.println("*bMOTOR ON \n*");
      else
      BTSerial.println("*bMOTOR OFF \n*");
      delay(500);
    }


    if(empty == LOW && one4 == LOW && half == LOW && three4 == LOW && full == LOW)
    {
      state = 0;
      setmotor(state);                                                          //WATER IS FULL
      Serial.println("WATER IS FULL");
      BTSerial.println("*b100% \t \t MOTOR OFF \n* *A100*");
      delay(500);
    }
}

void setmotor(int state)
{
  if (state == 1)
      {
        digitalWrite(motor, HIGH); 
      }
      else
      {
        digitalWrite(motor, LOW); 
      }
}

