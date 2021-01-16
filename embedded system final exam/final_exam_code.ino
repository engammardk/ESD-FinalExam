/*
 * AMMAR AHMED DOKHAN 
 * 1612863
 FINAL EXAM FOR EMBEDDED SYSTEM 
 
 A MEMORY GAME CODE 
 
 */




#include <Wire.h> // adding this library for serial communication through I2C protocol 
#include <LiquidCrystal_I2C.h> // adding library for lcd 
#include <Tone.h> // adding library for different tone to be produced in the speaker
#include <SoftwareSerial.h> // adding this library for bluetooth communication
#include <Servo.h> // adding this library for servo motor 

LiquidCrystal_I2C lcd(0x27,16,2); // create object lcd
Servo myservo; // create object myservo for servo motor
SoftwareSerial BT(0, 1); // create object BT for bluetooth module
char a; // stores incoming character from other device which is other phone
Tone speakerpin; //create object speakerpin

int starttune[] = {NOTE_E4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G4}; // use start tune array size 6 
int note[] = {NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4}; //use array note size 6 to play difirent notes
int duration[] = {100, 100, 100, 300, 100, 300}; // use duration array to be used as delay size 6
int duration2[] = {100, 200, 100, 200, 100, 400}; // use duration2 array to be used as delay size 6
int button[] = {2, 3, 4, 5}; // use inputpins array size 4 for the 4 input push buttons
int ledpin[] = {8, 9, 10, 11};  // use LED pins array size 4 for the 4 output leds
int turn = 0;  // to turn counter
int buttonstate = 0;  // to check button state 
int randomArray[50]; // random array size 50 to store up to 50 inputs 
int inputArray[50]; // input array size to accept up to 50 inputs
int highscore = 0;  // initialize high score to 0 
int MyScore; // declare score  variable 
int servoRepetition = 0 ; // initialize variable to 0 
int pos = 0; // initialize variable pos to 0 for the servo
 

void setup() 
{
    myservo.attach(6);// state servo motor tp pin number 6 
    BT.begin(9600); // set the data rate for the SoftwareSerial port
 lcd.backlight(); // to display back light
  lcd.init(); // to initilalize the lcd
 lcd.clear(); // clear lcd
  lcd.setCursor(0, 0); //locate the text in culomn o row o which is left top
 lcd.print("High Score: 0");// print high score is 0
 lcd.setCursor(0, 1); //locate the text in culomn o row 1 which is bottom left
 lcd.print("Your Score: 0"); // print your score is 0
 

  speakerpin.begin(12); // state speaker pin to be  12

  for(int x=0; x<4; x++)  // state output led pins as output using for loop
  {
    pinMode(ledpin[x], OUTPUT);
  }
  
  for(int x=0; x<4; x++) // state input buttons pins as input using for loop
  {
    pinMode(button[x],INPUT); 
    digitalWrite(button[x], HIGH);  // enable internal pullup which make the pin initially high;
  }

  randomSeed(analogRead(0)); //using and adding function randomSeed to generate "more randomness" with the randomArray for the output function

  
  for (int thisNote = 0; thisNote < 6; thisNote ++) 
  
  /* this loop is attached to void set up to displayed only once and it is used to display the initial notes and 
  lights to look more interesting as a game  */
  
  {
     
     speakerpin.play(starttune[thisNote]); // to play the notes 
   
     if (thisNote==0 || thisNote==2)
     {
       digitalWrite(ledpin[0], HIGH); 
     }
     if (thisNote==1 || thisNote==3 )
     {
       digitalWrite(ledpin[1], HIGH);
     }
     if (thisNote==4 || thisNote==5)
     {
       digitalWrite(ledpin[2], HIGH);
     }  
     if (thisNote==6)
     {   
       digitalWrite(ledpin[3], HIGH);
     }
     delay(duration2[thisNote]); // ussed for delay in the duration2 array 
     // stop for the next note:
     speakerpin.stop();   // stop for the next note:
     // turn off all leds
     digitalWrite(ledpin[0], LOW);
     digitalWrite(ledpin[1], LOW);
     digitalWrite(ledpin[2], LOW);
     digitalWrite(ledpin[3], LOW);
     delay(25);
    }
  delay(1000);
 Serial.begin(9600);
}

 
void loop() // starting the loop
{   

  if ( highscore <4 ) // this condition is added at the beginning to stop excuting if users managed and completed successfully 5 rounds and then he can get the reward  
  {
    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
  
    for (int thisNote = 0; thisNote < 6; thisNote ++) // this nested loop to play the notes
    {
    
     speakerpin.play(note[thisNote]);  //to play the next note:
     
     delay(duration[thisNote]);  //to hold the note:
     
     speakerpin.stop(); // to stop for the next note:
     delay(25);
    }
    
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    delay(1000);
  
    for (int y=turn; y <= turn; y++) // this other nested for loop is used to generate random led light using varaiable turn
    
    { //Limited by the turn variable
      Serial.println(""); //Some serial output to follow along
      Serial.print("Turn: ");
      Serial.print(y);
      Serial.println("");
      lcd.clear(); // clear the lcd
      MyScore=y; // store the value y in function Myscore
     lcd.setCursor(0, 1);  // it is used to reposition the text where the first is culomn and the second is row 
     lcd.print("Your Score: "); //print the message Your Score: in bottom left of lcd
     lcd.setCursor(12, 1); // reposition the nex text to be in culomn 12 row 1 
     lcd.print(MyScore); // print the value in variable Mystore
     
   if(MyScore > highscore)
   { // check for the score if it is higher than high score 
    
      highscore = y; //store the new high score in variable highscore
   }
 lcd.setCursor(0, 0); // locate the next text in culomn o row 0 which is left top
 lcd.print("High Score: " + (String)(highscore)); //display the value of high score
 Serial.print(y);
 Serial.println("");
 delay(1000);
      randomArray[y] = random(1, 5); // using random function min 1 max 5 , 5 is not included and assign it to the randomArray[y], y is being the turn count
      for (int x=0; x <= turn; x++)
      {
        Serial.print(randomArray[x]); // print the randomarray 
      
        for(int y=0; y<4; y++)
        {
      
          if (randomArray[x] == 1 && ledpin[y] == 8)   //if statements to display the stored values in the array
          {
            digitalWrite(ledpin[y], HIGH); // turn ledpin high based on y nested loop value 
            speakerpin.play(NOTE_G3, 100); // play note for 100 ms
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }

          if (randomArray[x] == 2 && ledpin[y] == 9) 
          {
            digitalWrite(ledpin[y], HIGH);
            speakerpin.play(NOTE_A3, 100);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }
  
          if (randomArray[x] == 3 && ledpin[y] == 10) 
          {
            digitalWrite(ledpin[y], HIGH);
            speakerpin.play(NOTE_B3, 100);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }

          if (randomArray[x] == 4 && ledpin[y] == 11) 
          {
            digitalWrite(ledpin[y], HIGH);
            speakerpin.play(NOTE_C4, 100);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }
        }
      }
    }
     
    input();
  }
  
  else // when user reached 5 rounds successfully
  { 
    lcd.clear ();
     lcd.setCursor(0, 0);  // place the text in the beginning of first row
     lcd.print("Congrats!send 1"); //print the message "CONGRATS! press no 1"
      lcd.setCursor(0, 1);  // place the text in the middle of second row
     lcd.print("To get ur gift"); //print the message "To get ur gift ^_^" 
     digitalWrite(ledpin[0], HIGH);
     digitalWrite(ledpin[1], HIGH);
     digitalWrite(ledpin[2], HIGH);
     digitalWrite(ledpin[3], HIGH);
  
    for (int thisNote = 0; thisNote < 6; thisNote ++) // loop to play the notes
    {
     speakerpin.play(note[thisNote]);  //to play the next note:
     
     delay(duration[thisNote]);  //to hold the note:
     
     speakerpin.stop(); // to stop for the next note:
     delay(25);
    }
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    delay(1000);
     if (BT.available()) // if text arrived in from BT serial
                    
    {
    a=(BT.read()); //read the data from the phone and then store it in varaiable a 
    if (a=='1')
    {
     for (servoRepetition = 0 ; servoRepetition <1 ; servoRepetition++) // to run the servo for 1 time
    {

    for (pos = 0; pos<= 90; pos+=1) //move servo to postion 90 degree to move the slider crank mechanism to push the dessert
    {
      myservo.write(pos);
      delay(50);
    }
    for ( pos=90; pos>= 0 ; pos -=1) // move servo back to original position 
    {
      myservo.write(pos);
      delay(50);
      
    }
    }
    }
    }
  
    
  } // end of else statment when user reached 5 right rounds and got the reward 


  
} // end of void loop
 
 
void input() { //Function for allowing user input and checking input against the generated array

  for (int x=0; x <= turn;)
  {                           //Statement controlled by turn count

    for(int y=0; y<4; y++)
    {
      
      buttonstate = digitalRead(button[y]);
    
      if (buttonstate == LOW && button[y] == 2)
      { //Checking for button push
        digitalWrite(ledpin[0], HIGH);
        speakerpin.play(NOTE_G3, 100);
        delay(200);
        digitalWrite(ledpin[0], LOW);
        inputArray[x] = 1;
        delay(250);
        Serial.print(" ");
        Serial.print(1);
        if (inputArray[x] != randomArray[x]) { //Checks value input by user and checks it against
          fail();                              //the value in the same spot on the generated array
        }                                      //The fail function is called if it does not match
        x++;
      }
       if (buttonstate == LOW && button[y] == 3)
      {
        digitalWrite(ledpin[1], HIGH);
        speakerpin.play(NOTE_A3, 100);
        delay(200);
        digitalWrite(ledpin[1], LOW);
        inputArray[x] = 2;
        delay(250);
        Serial.print(" ");
        Serial.print(2);
        if (inputArray[x] != randomArray[x]) { //Checks value input by user and checks it against
          fail();                              //the value in the same spot on the generated array
        }                                      //The fail function is called if it does not match
        
        x++;
      }

      if (buttonstate == LOW && button[y] == 4)
      {
        digitalWrite(ledpin[2], HIGH);
        speakerpin.play(NOTE_B3, 100);
        delay(200);
        digitalWrite(ledpin[2], LOW);
        inputArray[x] = 3;
        delay(250);
        Serial.print(" ");
        Serial.print(3);
        if (inputArray[x] != randomArray[x])  { //Checks value input by user and checks it against
          fail();                              //the value in the same spot on the generated array
        }                                      //The fail function is called if it does not match
        
        x++;
      }

      if (buttonstate == LOW && button[y] == 5)
      {
        digitalWrite(ledpin[3], HIGH);
        speakerpin.play(NOTE_C4, 100);
        delay(200);
        digitalWrite(ledpin[3], LOW);
        inputArray[x] = 4;
        delay(250);
        Serial.print(" ");
        Serial.print(4);
        if (inputArray[x] != randomArray[x])  { //Checks value input by user and checks it against
          fail();                              //the value in the same spot on the generated array
        }                                      //The fail function is called if it does not match
         
        x++;
      }
    }
  }
  delay(500);
  turn++; //Increments the turn count, also the last action before starting the output function over again
}



void fail() {                   //Function used if the player fails to match the sequence
 
  for (int y=0; y<=3; y++)
  {                          //Flashes lights for failure
    
    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
    speakerpin.play(NOTE_G2, 300);
    delay(200);
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    speakerpin.play(NOTE_C2, 300);
    delay(200);
    lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Game Over");
 }
 delay(2000);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("High: " + (String) (highscore));
 // Serial.print(y);
 // Serial.println("");
 lcd.setCursor(9, 0);
 lcd.print("You: ");
 lcd.setCursor(14, 0);
 lcd.print(MyScore);
 // if(y > highscore) {
 // highscore = y;
 // }
 lcd.setCursor(0, 1);
 lcd.print("<-Press to play again!");
 {

 while (digitalRead(button[0]) > 0 &&digitalRead(button[1]) > 0 && digitalRead(button[2]) > 0 && digitalRead(button[3]) > 0 ){  // buttonstate = digitalRead(button[y]);
digitalWrite(ledpin[0], HIGH);
digitalWrite(ledpin[1], HIGH);
digitalWrite(ledpin[2], HIGH);
digitalWrite(ledpin[3], HIGH);
delay(100);
digitalWrite(ledpin[0], LOW);
digitalWrite(ledpin[1], LOW);
digitalWrite(ledpin[2], LOW);
digitalWrite(ledpin[3], LOW);
delay(100);
 }
 delay(1000);
  
  turn = -1; //Resets turn value so the game starts over without need for a reset button
  
}
}
