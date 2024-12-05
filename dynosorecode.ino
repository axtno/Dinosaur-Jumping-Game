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

// display the images to LCD, and display a line to represent the ground
// define the dimensions of the screen and dimensions of the objects, and height of the jump and duck of dino
// create functions that will move the obstacles and the dinosaur under a loop (runs until collision)
// read button input and declare what the input will do for the dinosaur
// create a jump function for one of the inputs (first button)
// create a duck function for another input (second button)
// create an if function for if the dinosaur and the obstacle touch (pixels are a certain distance apart)
// create a function that displays the score for each obstacle jumped/ducked over
// create a game over window screen that displays final score
// if a collision happens, display game over window and final score
// clear display and reset to intro screen after 10 seconds

void setup() {
  // put your setup code here, to run once:
  // under setup, start serial monitor, declare inputs and outputs
  analogWrite(Vo,100);  // changes contrast so you can see pixels
  pinMode(jumpButtonPin,INPUT_PULLUP);  // left button
  pinMode(duckButtonPin,INPUT_PULLUP);  // right button
  Serial.begin(9600);                   // for button communication?
  lcd.begin(16,2);                      // initialize interface LCD 16 col, 2 rows
  lcd.clear();                            // clears LCD screen
  //intro screen
  lcd.setCursor(0,0);                   //top left
  lcd.print("Hold Left Button");              //will print text to LCD
  lcd.setCursor(0,1);                   //bottom left
  lcd.print("For 2 Sec");         //will print text to LCD
  delay(2500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Then Release");
  lcd.setCursor(0,1);
  lcd.print("To Start");
 
  /*
  lcd.createChar(0,dinorunoneandjump);
  lcd.createChar(1,dinoruntwo);
  lcd.createChar(2,dinocrouch);
  lcd.createChar(3,cloud);
  lcd.createChar(4,cactus);
  */
}


void loop() {
  // put your main code here, to run repeatedly:
  while (digitalRead(jumpButtonPin) == HIGH){ 
    delay(100); 
    pressLength = pressLength + 100;   
    Serial.println(pressLength);
    Serial.println(digitalRead(jumpButtonPin));   
  }
    Serial.println(digitalRead(jumpButtonPin));

  if (pressLength>startPress){ //if button is pressed longer than 2000 ms */
    lcd.clear(); //clear lcd screen
    ccmoving();
  }



  /*
lcd.setCursor(1,1);
lcd.write(byte(0));
lcd.setCursor(4,1);
lcd.write(byte(1));
lcd.setCursor(8,1);
lcd.write(byte(2));
lcd.setCursor(11,0);
lcd.write(byte(3));
lcd.setCursor(14,1);
lcd.write(byte(4));
*/

}

//cloud and cactus moving animation
//cloud and cactus moving animation

void ccmoving() {
  int cloudorcact = random(1,3);
  if (cloudorcact==1){
      cactusmoving();
  }
  
  else if (cloudorcact==2){
      cloudmoving();
  }
}

void cloudmoving() {
  lcd.createChar(3,cloud);
  lcd.createChar(5,empty);
  int a;
  for (a=16;a>=0;a-=1){
    lcd.setCursor(a,0); // 0 is top
    lcd.write(byte(3));
    delay(300);
    lcd.setCursor(a,0);
    lcd.write(byte(5));

  }
}
void cactusmoving() {
  lcd.createChar(4,cactus);
  lcd.createChar(5,empty);
  int a;
  for (a=16;a>=0;a-=1){
    lcd.setCursor(a,1); // 1 is bottom
    lcd.write(byte(4));
    delay(300);
    lcd.setCursor(a,1);
    lcd.write(byte(5)); 
  }
}