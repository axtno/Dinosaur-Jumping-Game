/*
  Dynosore Game: Taking inspiration from the Google Dinosaur Game, this project
  aims to utilize the LCD and the ELEGOO to display the game while two buttons take
  input from the user which tells the dinosaur to jump or duck under obstacles.

*/

#include <LiquidCrystal.h>        // add or include all libraries to connect the LCD to the ELEGOO
// set each pin number for the inputs and outputs
int jumpButtonPin = 2;   
int duckButtonPin = 13;
int Vo = 11;
float pressLength = 0;
int startPress = 2000;
const int rs = 3, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
int dinox = 1;
int dinoy;
int cactusx;
int cactusy = 1;
int a=16;

// convert dinosaur and obstacle images into byte arrays to display on LCD
  //Run position 1 and jump
  byte dinorunoneandjump[8] = {B00110, B00101, B00111, B00110, B10111, B11110, B01110, B01010};

  //Run position 2
  byte dinoruntwo[8] = {B00110, B00101, B00111, B00110, B10111, B11110, B01110, B00101};

  //Crouch position
  byte dinocrouch[8] = {B00000, B00000, B00110, B00101, B00110, B10111, B01110, B00110};

  //Cloud
  byte cloud[8] = {B00000, B00000, B00000, B00000, B00000, B00100, B01110, B11111};

  //Cactus
  byte cactus[8]= {B00100, B10101, B10101, B10101, B01110, B00100, B00100, B00000};

  //Clear box
  byte empty[8]= {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000};


void setup() {
  // put your setup code here, to run once:
  // under setup, start serial monitor, declare inputs and outputs
  analogWrite(Vo,100);  // changes contrast so you can see pixels
  pinMode(jumpButtonPin,INPUT_PULLUP);  // left button
  pinMode(duckButtonPin,INPUT_PULLUP);  // right button
  Serial.begin(9600);                   // start serial communication at at baud rate of 9600
  lcd.begin(16,2);                      // initialize interface LCD 16 col, 2 rows
  lcd.clear();                            // clears LCD screen
  //intro screen
  /*lcd.setCursor(0,0);                   //top left
  lcd.print("Hold Left Button");              //will print text to LCD
  lcd.setCursor(0,1);                   //bottom left
  lcd.print("For 2 Sec");         //will print text to LCD
  delay(2500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Then Release");
  lcd.setCursor(0,1);
  lcd.print("To Start");
  lcd.createChar(0,dinorunoneandjump);
*/


  lcd.createChar(0,dinorunoneandjump);
  lcd.createChar(1,dinoruntwo);
  lcd.createChar(2,dinocrouch);
  lcd.createChar(3,cloud);
  lcd.createChar(4,cactus);
  lcd.createChar(5,empty);
}
void jump(){
  if (millis()%80==0){
    if((digitalRead(jumpButtonPin)) == LOW && (digitalRead(jumpButtonPin) == LOW)){
      lcd.setCursor(1,0);
      lcd.write(byte(5));
      lcd.setCursor(1,1);
      lcd.write(byte(0));
      dinoy=1;
    }
    if((digitalRead(jumpButtonPin)) == HIGH){
     lcd.setCursor(1,1);
     lcd.write(byte(5));
     lcd.setCursor(1,0);
     lcd.write(byte(0)); 
     dinoy=0;
    }
  }
}

void cactusm(){
    lcd.setCursor(a,1);
    lcd.write(byte(4));
    if (0<=a<=16){
      if (millis()%400==0){ //if 400 ms has passed
        lcd.setCursor(a-1,1);
        lcd.write(byte(4));
        cactusx=a-1;
        lcd.setCursor(a,1);
        lcd.write(byte(5));
        a-=1;
      }
    }
    if (a<0){
      a=16;
    }
}

/*void cloudm(){
    lcd.setCursor(a,0);
    lcd.write(byte(3));
    if (0<=a<=16){
      if (millis()%400==0){ //if 400 ms has passed
        lcd.setCursor(a-1,0);
        lcd.write(byte(3));
        lcd.setCursor(a,0);
        lcd.write(byte(5));
        a-=1;
      }
    }
    if (a<0){
      a=16;
    }
}*/

void loop() {
  // put your main code here, to run repeatedly:
 /* while (digitalRead(jumpButtonPin) == HIGH){ //while the button is pressed
    delay(100); //wait 100 ms
    pressLength = pressLength + 100; //add 100 to pressLength value
    Serial.println(pressLength); //print to serial monitor the press length
    Serial.println(digitalRead(jumpButtonPin)); //print to serial monitor if the button is being pressed or not (0 or 1)
  }
    Serial.println(digitalRead(jumpButtonPin));
  if (pressLength>startPress){ //if button is pressed longer than 2000 ms */
  jump();
 // }
  cactusm();
  if (cactusx==dinox && cactusy==dinoy){
    end();
  }
  
}

void end(){
  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print("Game Over");
  delay(100000);
}

