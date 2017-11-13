const int buttonPinDot = 12;     // the number of the pushbutton pin
const int ledPinDot =  13;      // the number of the LED pin

const int buttonPinLin = 11;
const int ledPinLin = 10;

const int buttonPinEnd = 9;


// variables will change:
int buttonStateDot = 0;         // variable for reading the pushbutton status
int buttonStateLin = 0;
int buttonStateEnd = 0;

int lastButtonStateDot = 0;
int lastButtonStateLin = 0;
int lastButtonStateEnd = 0;

int dot = 1;
int line = 2;
int End = 0;

int myValue[] = {0,0,0,0};
int calculator[] = {1000,100,10,1};
int myMessage = 0;
int arrayPosition = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPinDot, OUTPUT);
  pinMode(ledPinLin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPinDot, INPUT);
  pinMode(buttonPinLin, INPUT);
  pinMode(buttonPinEnd, INPUT);

  Serial.begin(9600);
}

// check if the pushbutton is pressed. If it is, the buttonState is HIGH:
void loop(){

//read the state of the button pins
   buttonStateDot = digitalRead(buttonPinDot);
   buttonStateLin = digitalRead(buttonPinLin);
   buttonStateEnd = digitalRead(buttonPinEnd);
   
//when the end button is pressed, end =3, end the following loop
   if(buttonStateEnd != lastButtonStateEnd){
    if(buttonStateEnd == HIGH){
      End = 3;
//      Serial.write(End);
//      digitalWrite(ledPinEnd, HIGH);
    }else{
//      digitalWrite(ledPinEnd, LOW);
    }
    delay(1);
  }
  lastButtonStateEnd = buttonStateEnd;

//when the End is not equel with 3, do the loop
if( End == 0 && arrayPosition<4 ){  
    if(buttonStateDot != lastButtonStateDot){
      if(buttonStateDot == HIGH){
//        Serial.write(dot);
        digitalWrite(ledPinDot, HIGH);
        myValue[arrayPosition] = dot;
        arrayPosition =arrayPosition +1;
        }else{
        digitalWrite(ledPinDot, LOW);
        }
       delay(1);
     }
    lastButtonStateDot = buttonStateDot;
  
    if(buttonStateLin != lastButtonStateLin){
      if(buttonStateLin == HIGH){
//        Serial.write(line);
//      digitalWrite(ledPinLin, HIGH);
        myValue[arrayPosition] = line;
        arrayPosition =arrayPosition +1;
        }else{
//      digitalWrite(ledPinLin, LOW);
        }
       delay(1);
      }
    lastButtonStateLin = buttonStateLin;  
  }else if(End = 3 || arrayPosition >=4){
//    int i;
//    for( i=0; i<4; i = i+1 ){
////    Serial.print(myValue[i]);
//      myMessage = myMessage + myValue[i]*calculator[i];      
//      }

    alphabet();
    } 
 delay(10);    // slight delay to stabilize the ADC
}

void alphabet(){//based on the myValue array to check which character it should be

//Here is to debug
  Serial.print("You did it ! The message is ");
  int i;
  for( i=0; i<4; i = i+1 ){
    Serial.print(myValue[i]);
  }


if( myValue[0] == 1){/*The firs position is dot*/
  if(myValue[1] == 1){/*The 2ns position is dot*/
     if(myValue[2] == 1){/*The 3ns position is dot*/
      if(myValue[3] == 1){/*The 4ns position is dot  ....  H  */
        Serial.write(8);
      }
      if(myValue[3] == 2){/*The 4ns position is dash   ...-  V */
        Serial.write(22);
      }
      if(myValue[3] == 0){/*The 4ns position is empty   ...  S */
        Serial.write(19);
      }
     }
     if(myValue[2] == 2){/*The 3ns position is dash*/
      if(myValue[3] == 1){/*The 4ns position is dot   ..-.   F */
        Serial.write(6);
      }
      if(myValue[3] == 2){/*The 4ns position is dash    ..--   */
        ////////////////No Character Fit!
      }
      if(myValue[3] == 0){/*The 4ns position is empty    ..-   U*/
        Serial.write(21);
      }
     }else if(myValue[2] == 0){/*The 3ns position is empty  .. I*/
      Serial.write(9);
     }
  }
  if(myValue[1] == 2){/*The 2nd position is dash*/
    if(myValue[2] == 1){/*The 3ns position is dot*/
      if(myValue[3] == 1){/*The 4ns position is dot   .-..   L*/
        Serial.write(12);
      }
      if(myValue[3] == 2){/*The 4ns position is dash   .-.-   */
        ////////////////No Character Fit!
      }
      if(myValue[3] == 0){/*The 4ns position is empty   .-.   R*/
        Serial.write(18);
      }
     }
     if(myValue[2] == 2){/*The 3ns position is dash*/
      if(myValue[3] == 1){/*The 4ns position is dot .--.  P*/
        Serial.write(16);
      }
      if(myValue[3] == 2){/*The 4ns position is dash   .---   J*/
        Serial.write(10);
      }
      if(myValue[3] == 0){/*The 4ns position is empty  .--   W*/
        Serial.write(23);
      }
     }else if(myValue[2] == 0){/*The 3ns position is empty  .-  A */
      Serial.write(1);
     }
  }else if(myValue[1] == 0){/*The 2nd position is empty  .  E */
    Serial.write(5);
  }    
}else if (myValue[0] ==2 ){/*The firs position is dash*/
    if(myValue[1] == 1){/*The 2ns position is dot*/
     if(myValue[2] == 1){/*The 3ns position is dot*/
      if(myValue[3] == 1){/*The 4ns position is dot   -...   B*/
        Serial.write(2);
      }
      if(myValue[3] == 2){/*The 4ns position is dash  -..-  X*/
        Serial.write(24);
      }
      if(myValue[3] == 0){/*The 4ns position is empty  -..  D*/
        Serial.write(4);
      }
     }
     if(myValue[2] == 2){/*The 3ns position is dash*/
      if(myValue[3] == 1){/*The 4ns position is dot   -.-.  C*/
        Serial.write(3);
      }
      if(myValue[3] == 2){/*The 4ns position is dash  -.--  Y*/
        Serial.write(25);
      }
      if(myValue[3] == 0){/*The 4ns position is empty  -.-  K*/
        Serial.write(11);
      }
     }else if(myValue[2] == 0){/*The 3ns position is empty  -.  N*/
      Serial.write(14);
     }
  }
  if(myValue[1] == 2){/*The 2nd position is dash*/
    if(myValue[2] == 1){/*The 3ns position is dot*/
      if(myValue[3] == 1){/*The 4ns position is dot  --..  Z*/
        Serial.write(26);
      }
      if(myValue[3] == 2){/*The 4ns position is dash   --.-   Q*/
        Serial.write(17);
      }
      if(myValue[3] == 0){/*The 4ns position is empty  --.   G*/
        Serial.write(7);
      }
     }
     if(myValue[2] == 2){/*The 3ns position is dash*/
      if(myValue[3] == 1){/*The 4ns position is dot   ---.  */
        ////////////////No Character Fit!
      }
      if(myValue[3] == 2){/*The 4ns position is dash   ----*/
        ////////////////No Character Fit!
      }
      if(myValue[3] == 0){/*The 4ns position is empty   ---  O*/
        Serial.write(15);
      }
     }else if(myValue[2] == 0){/*The 3ns position is empty  --  M*/
      Serial.write(13);
     }
  }else if(myValue[1] == 0){/*The 2nd position is empty  -  T*/
    Serial.write(20);
  } 
}/*Here is end of the huge if statement*/ 
  delay(5);
  clearUp();
}/*Here is end of the alphabet()*/ 

void clearUp(){
    End = 0;
    arrayPosition = 0; 
//      Serial.print("You did it ! The message is ");
    int i;
    for( i=0; i<4; i = i+1 ){
      myValue[i] = 0;
    }
     
}

