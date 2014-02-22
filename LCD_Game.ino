#include <SimpleTimer.h>
#include <LiquidCrystal.h>

SimpleTimer timer;

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte fullChar[8] = {
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111
};

byte clearChar[8] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};

byte monsterChar[8] = {
        B00000,
        B01110,
        B01010,
        B11111,
        B11111,
        B11111,
        B11111,
        B10101
};

byte shipRightChar[8] = {
        B00000,
        B01000,
        B00100,
        B00110,
        B10111,
        B00110,
        B00100,
        B01000
};

byte shipLeftChar[8] = {
        B00000,
        B00010,
        B00100,
        B01100,
        B11101,
        B01100,
        B00100,
        B00010
};

int lcd_key     = 0;
int prev_lcd_key     = 0;
int last_lcd_key = 0;
int adc_key_in  = 0;
int shipMoveCharacter = 3;
int prevShipMoveCharacter = 3;

int monstersTimer;

boolean startGame = false;
boolean gameOver = false;
boolean showResetMessage = false;
boolean startScreen = true;

int playerX = 0;
int playerY = 0;

int randomMovement = 0;

int secondsPassed = 0;
int score = 0;
int startScore = 0;

int monsters[3][2] = {0};
int numberOfMonsters = 2;

int keyPresses = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define CLEAR 0
#define FULL 1
#define MONSTER 2
#define SHIP_RIGHT 3
#define SHIP_LEFT 4

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 100)  return btnUP; 
 if (adc_key_in < 300)  return btnDOWN; 
 if (adc_key_in < 500)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  

 return btnNONE;  // when all others fail, return this...
}

void showDifficultyChooser() {
  lcd.setCursor(3,1);
  lcd.print("<");
  lcd.setCursor(12,1);
  lcd.print(">");
    lcd.setCursor(5,1);
  if(numberOfMonsters == 1) {
    lcd.print(" easy ");
  } else if(numberOfMonsters == 2) {
    lcd.setCursor(5,1);
    lcd.print("medium");
  } else if(numberOfMonsters == 3) {
    lcd.print(" hard ");
  } 
}

void setup()
{  
  monstersTimer = timer.setInterval(500, moveMonsters);
  
  lcd.createChar(CLEAR, clearChar);
  lcd.createChar(FULL, fullChar);
  lcd.createChar(MONSTER, monsterChar);
  lcd.createChar(SHIP_RIGHT, shipRightChar);
  lcd.createChar(SHIP_LEFT, shipLeftChar);
  lcd.begin(16, 2);              // start the library
  Serial.begin(9600);
  
  for(int i=0;i<numberOfMonsters;i++) {
     monsters[i][1] = random(0,2);
     monsters[i][0] = random(0,17);
  }
  
  lcd.setCursor(2,0);
  lcd.print("RENE FROGGER");
  showDifficultyChooser();
}

void moveMonsters() {
  if(!gameOver) {
    for(int i=0;i<numberOfMonsters;i++) {
        // Clear old positions
       lcd.setCursor(monsters[i][0],monsters[i][1]);
       lcd.write((byte)CLEAR);
      
       randomMovement = random(0,4);
       // Calculate new position
       if(randomMovement == btnDOWN) {
        monsters[i][1] += 1; 
       }
       if(randomMovement == btnUP) {
        monsters[i][1] -= 1;
       }
       
       if(randomMovement == btnRIGHT) {
        monsters[i][0] += 1; 
       }
       if(randomMovement == btnLEFT) {
        monsters[i][0] -= 1;
       }
       
       if(monsters[i][1] > 1) monsters[i][1] = 1;
       if(monsters[i][1] < 0) monsters[i][1] = 0;
       
       if(monsters[i][0] > 15) monsters[i][0] = 15;
       if(monsters[i][0] < 0) monsters[i][0] = 0;
    }
  }
}
 
void endGame() {
     timer.disable(monstersTimer);
     gameOver = true;  
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("                 ");
     lcd.setCursor(0,1);
     lcd.print("                 ");
     if(score == 0) {
       lcd.setCursor(4,0);
       lcd.print("GAME OVER");
     } else {
       lcd.setCursor(2,0);
       lcd.print("YOU MADE IT!");
     }
     if(score<100) {
       lcd.setCursor(1,1);
     } else if(score>99) {
       lcd.setCursor(0,1);
     }
     
     if(score<10000) {
       lcd.print("Your score: ");         
     } else {
       lcd.print("Your score ");
     }
 
     lcd.print(score);
 }
 
void loop() {
 lcd_key = read_LCD_buttons();  // read the buttons  
 if(!gameOver && lcd_key == btnSELECT) {
   startScreen = false;
   lcd.clear();
   startGame = true;
 }
 if(startScreen && lcd_key != btnNONE && lcd_key != prev_lcd_key) {
   if(lcd_key == btnLEFT) {
     numberOfMonsters -= 1;
     if(numberOfMonsters < 1) {
        numberOfMonsters = 1; 
     }
   } else if(lcd_key == btnRIGHT) {
     numberOfMonsters += 1;
     if(numberOfMonsters > 2) {
        numberOfMonsters = 3; 
     }
   }
   showDifficultyChooser();
 }
 if(startGame) {
   timer.run();
   if(!gameOver) {
     secondsPassed = millis()/1000;
     startScore = 100;
     score = startScore - (keyPresses + secondsPassed);
     
     if(lcd_key != prev_lcd_key) {
       keyPresses += 1;
       // Clear old positions
       lcd.setCursor(playerX,playerY);
       lcd.write((byte)CLEAR);
       
       // Calculate new position
       if(lcd_key == btnDOWN) {
          playerY += 1; 
       }
       if(lcd_key == btnUP) {
          playerY -= 1;
       }
       
       if(lcd_key == btnRIGHT) {
          shipMoveCharacter = SHIP_RIGHT;
          if(shipMoveCharacter == prevShipMoveCharacter) {
            playerX += 1; 
          }
       }
       if(lcd_key == btnLEFT) {
          shipMoveCharacter = SHIP_LEFT;
          if(shipMoveCharacter == prevShipMoveCharacter) {
            playerX -= 1;
          }
       }
       
       if(playerY > 1) playerY = 1;
       if(playerY < 0) playerY = 0;
       
       if(playerX > 15) playerX = 15;
       if(playerX < 0) playerX = 0;
       
       if(playerX == 15) {
          endGame();
       }
       
       if(!gameOver) {
         // Fill new position of player
         lcd.setCursor(playerX,playerY);
         lcd.write((byte)shipMoveCharacter);
       }
     }
     
     if(!gameOver) {
       for(int i;i<numberOfMonsters;i++) {   
         lcd.setCursor(monsters[i][0],monsters[i][1]);
         lcd.write((byte)MONSTER);
         
         if(monsters[i][0] == playerX && monsters[i][1] == playerY) {
           if(lcd_key == btnSELECT) {
               lcd.setCursor(monsters[i][0], monsters[i][1]);
               lcd.write((byte)CLEAR);
           } else {
             score = 0;
             endGame();
             break;
           }
         }
       }
     }
     
     prevShipMoveCharacter = shipMoveCharacter;
   }
   prev_lcd_key = lcd_key;
   last_lcd_key = lcd_key;
 }
 Serial.println(gameOver);
 if(gameOver && lcd_key != btnNONE && last_lcd_key != prev_lcd_key) {
   lcd.clear();
   showResetMessage = true;
 }
 if(startScreen) {
    prev_lcd_key = lcd_key;
 }
 if(showResetMessage) {
    lcd.setCursor(2,0);
    lcd.print("Press RST to");
    lcd.setCursor(2,1);
    lcd.print("play again!");
 }
}
