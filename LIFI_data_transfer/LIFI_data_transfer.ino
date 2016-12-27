//Data rates of upto 3500 bits/second
//Algorithm 
//Write 150 to the led
//Determine a value that the LED can't exceed
//Determine a value that the LED can't go below
//To transfer, write 255 to the LED if the value is 1 or write a 0 to transfer a 0.
//At the receiver, if the value of the LED is lowering then it's a zero. If it's increasing, it's a 1. 
//If it goes below the minimum value, then reset the LED to 150 and resend the data. Same if it exceeds the maximum value
// the analog reading from the sensor divider
double photocellReading;    
// connect Red LED to pin 11 (PWM pin)
int LEDpin = 11; 
//Used to minimize and maximize how how or low the brightness of the light can go. To know more, you can read the github page:             
int maxVal = 0;
int minVal = 0;
int lastVal =0;
int currentVal=0;
//Temp storing of the photocell data
int photocellPin = 0; 
//Value read from the photocell when sync is done 
int firstReading = 0;
//Only transfer the data once
int set = 0;



void setup() {
   // serial 9600 baud
   Serial.begin(9600);
}

void setUpTransferRates(void){

  //start by writing 150 to the LED
  analogWrite(LEDpin, 150);
  delay(200);
  //filter out the light in the room
  photocellReading = analogRead(photocellPin)- firstReading;
  //the led can't be brighter than this
  maxVal = photocellReading+(photocellReading/4);
  //the led can't be dimmer than this
  minVal = photocellReading-(photocellReading/4);
  //current value of the led
  currentVal = photocellReading;
  //set to a 1 so it doesn't run again
  set= 1;
}

//transmit a bit
void transmit(int val){    
  if (val == 0){
    //write a 0 to the led
    analogWrite(LEDpin, 0);
  }else if (val == 1){
    //write a 255 to the led
    analogWrite(LEDpin, 255);
  }
}

//receiver 
void recieve(){
  //record the current value
  currentVal = analogRead(photocellPin)- firstReading;
  while(1){
        //if the value of the led is greater or equal to the max value reset it to a value of 150
        //if the value of the led is less than or equal to the min value reset it to a value of 150  
        //if the value of the led is less than the current val by at least 2, a 0 was transferred
        //if the value of the led is more than the current val by at least 2, a 1 was transferred
        photocellReading = analogRead(photocellPin)- firstReading;
        if(photocellReading>=maxVal){
          reset();
        }else if(photocellReading<=minVal){
          reset();
        }else{
          if ((currentVal-photocellReading)>=2){
              analogWrite(LEDpin, 255);
            break;
          }else if((currentVal-photocellReading)<=-2){
              analogWrite(LEDpin,0);
            break;
          }
        }
      }
}

//reset the led and re-transfer the data 
//use the lastVal to resend the data
void reset(void){
   analogWrite(LEDpin, 150);
   delay(30);
   transmit(lastVal);
   currentVal = analogRead(photocellPin)- firstReading;
}

void loop() {
  //send the data once
  if(set==0){
   //set up the tranfer (you can do this more often to adjust for the light conditions)
   setUpTransferRates();

     //transfer 4000 bits of data
     for(int i=0; i<2000;i++){
      lastVal=1;
      transmit(1);
      recieve();
      lastVal=0;
      transmit(0);
      recieve();
   }
   
   analogWrite(LEDpin, 0);
  }

  delay(1000);
}
