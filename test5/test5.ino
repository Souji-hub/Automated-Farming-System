#include <Stepper.h>
const int stepsPerRevolutionX = 48;
const int stepsPerRevolutionY = 200;
Stepper myStepperX(stepsPerRevolution, 8, 9, 10, 11);
Stepper myStepperY(stepsPerRevolution, 3, 4, 5,6);
#define pumprelay 33
#define moisturesensor A9

 const int xlen=700, ylen=400, alen= 350, blen = 200 ;
  int row = ylen/blen;
  int  colm = xlen/alen ;
float x = 0,y = 0;
const float distanceperrev = 1 ;
bool sensoroutput;
 

void setup() {
  
  // put your setup code here, to run once:
   myStepperX.setSpeed(60);
   myStepperY.setSpeed(60);
   pinMode(pumprelay, OUTPUT);
   pinMode(moisturesensor, INPUT);
   digitalWrite(pumprelay,LOW);
   
   //can be changed acc. to x and y
    Serial.begin(9600);
    Serial.println("Welcome to Farmbot");
    delay(500);
    

}

void loop() {
  // put your main code here, to run repeatedly:
    reset();
  // reset to ref point
  sensoroutput = digitalRead(moisturesensor);
  if (sensoroutput = HIGH)
  {
    Serial.println("Moisture level LOW");
    automated();
    }
  else 
  {
    manual();
    activity();
    }
        
// reset to ref point
    reset();
// stepper.release
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW); 
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW); 
}

void automated()
{
 
  for(int r =1;r<=row; r++)
      {
        for( int c =1; c<=colm; c++)
        {
         y = (c-1)*alen + (alen/2);
         x = (r-1) *blen +(blen/2);
     int revsx = x/distanceperrev;
     int revsy = y/distanceperrev;  

        for(int i=1;i<=revsx;i++)
    {
   myStepperX.step(stepsPerRevolutionX);
    }
     for(int i=1;i<=revsy;i++)
    {
   myStepperY.step(stepsPerRevolutionY);
       digitalWrite(pumprelay,HIGH);
       delay(500);
       digitalWrite(pumprelay,LOW);
    }
    for(int i=1;i<=revsy;i++)
    {
      
   myStepperY.step(-stepsPerRevolutionY);
    }
        
        }
      }
  }

void activity()
{
   
  P:  Serial.println("enter your activity");
  if(Serial.available()){
    char remotecommand =  Serial.read();
      if (remotecommand == 'P'){
          digitalWrite(pumprelay,HIGH);
          delay(500); 
      }
      else 
      {
        Serial.println("invalid activity");
        goto P;
        }
    
  }}

 void manual()
 {
     Q: Serial.println("Enter your grid no.");
      if(Serial.available()){
      int r = Serial.read();
      int c = Serial.read();

      if(r<=row && c<=colm)
      {
         y = (c-1)*alen + (alen/2);
    x = (r-1) *blen +(blen/2);
     int revsx = x/distanceperrev;
     int revsy = y/distanceperrev;  

        for(int i=1;i<=revsx;i++)
    {
   myStepperX.step(stepsPerRevolutionX);
    }
     for(int i=1;i<=revsy;i++)
    {
   myStepperY.step(stepsPerRevolutionY);
    }
        }
      else
      {
        Serial.println("The grid doesnot exist");
        goto Q;
        } 
   
    
  delay(500);
  }}

void reset()
{
   for ( int i = 1; i<= xlen; i++)
        {
           myStepperX.step(-stepsPerRevolutionX);
          }
  for (int j = 1; j<= ylen; j++)
  {
           myStepperY.step(-stepsPerRevolutionY);
    }
  }
