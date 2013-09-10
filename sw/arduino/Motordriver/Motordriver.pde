/* 

Motordriver stress tester 
by Geir Turtum

*/

int IntPerSec = 4000;
int NrOfInts = 4000;
int Running = 1;

int LoopDelay = 22; //uS to get through the loop
int DelayUs = (1000000/IntPerSec)-LoopDelay;


const int TestPin = 2; 

const int FreqPin = 9; //Toggle for every change on the Hall sensors
const int HallA =  10;
const int HallB =  11; 
const int HallC =  12; 

//Rotorvinkel 0, 60, 120, 180, 240, 300 grader(CCW)
int HallAOut[] = {0, 0, 0, 1, 1, 1};
int HallBOut[] = {1, 1, 0, 0, 0, 1};
int HallCOut[] = {0, 1, 1, 1, 0, 0};

int HallArrLen = 6;
int index=0;
int FreqPinState = LOW;

void setup()
{
  //Setup GPIO
  pinMode(TestPin, OUTPUT);
  pinMode(FreqPin, OUTPUT); 
  pinMode(HallA, OUTPUT); 
  pinMode(HallB, OUTPUT); 
  pinMode(HallC, OUTPUT); 
  
  digitalWrite(TestPin, LOW);
  
  //Setup Serial com
  Serial.begin(9600); 
  
  Serial.println("Motordriver stress tester");
  Serial.print("IntPerSec: ");
  Serial.println(IntPerSec, DEC);
  Serial.print("DelayUs: ");
  Serial.println(DelayUs, DEC);
  Serial.print("NrOfInts: ");
  Serial.println(NrOfInts, DEC);
  
}

void loop()
{
  Serial.println("Stopped");
  //Wait for serial input to start
  while(Serial.available()==0);
  Serial.read();
  Serial.println("Running...");
  
  for(int i=0; i<NrOfInts; i++){
    if(DelayUs <= 16383){ //delayMicroseconds not accurate if above
      delayMicroseconds(DelayUs);
    }else{  
      delay(DelayUs/1000); //delayMs
    }
    
    FreqPinState = ~FreqPinState;
    digitalWrite(FreqPin, FreqPinState);
    digitalWrite(HallA, HallAOut[index]);
    digitalWrite(HallB, HallBOut[index]);
    digitalWrite(HallC, HallCOut[index]);
    
    if(index >= (HallArrLen-1)){
      index = 0;
    }else{
      index++;
    }
    
  }
  

}

