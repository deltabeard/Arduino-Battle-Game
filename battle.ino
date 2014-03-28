#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Initialising Display
Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 7, 12, 10);

// Initialising funduino joystick shield
byte up_button = 2;
byte down_button = 4;
byte left_button = 5;
byte right_button = 3;
byte start_button = 6;
byte select_button = 7;
byte analog_button = 8;
byte x_axis = A0;
byte y_axis = A1;
byte buttons[] = {up_button, down_button, left_button, right_button, start_button, select_button, analog_button};

//Variables
byte menu_item = 0;
byte battle_menu = 0;
String heroname = "Wizard";
int heroHP = 200;
boolean defence = false;

int enemyHP = 100;


// Bitmaps
const unsigned char PROGMEM Wizard_Sprite [] = {
0x03, 0xC0, 0x3C, 0x3C, 0x44, 0x22, 0x30, 0x0C, 0x1F, 0xF8, 0xED, 0xB7, 0x87, 0xE1, 0x83, 0xC1,
0x44, 0xA2, 0x44, 0xA2, 0x2F, 0xF6, 0x3A, 0x5C, 
};


void setup() {
  //Initialise the Joystick shield
  for (int i; i < 7; i++)
  {
   pinMode(buttons[i], INPUT);
   digitalWrite(buttons[i], HIGH);
  }
  display.begin();
  display.setContrast(50);
  display.display(); // Show splashscreen
  delay(1000);
  display.clearDisplay();  // Clears screen and buffer

}

void loop() {
  mainmenu();
}


void mainmenu() {
  // Reset variables
  heroHP = 200;
  enemyHP = 100;
  menu_item = 0;
  battle_menu = 0;
  
  display.clearDisplay();   // clears the screen and buffer
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Menu:");
  display.println("A-Fight");
  // Additional menu items may be added.
  // display.println("B-Digital Ctrl");
  display.display();
  while(menu_item == 0) {
    if(digitalRead(up_button) == 0) {
      menu_item = 1;
      fight();
    }
    if(digitalRead(right_button) == 0) {
      menu_item = 2;
      // usingbuttons();
    }
  }
}

void fight() {
  while(menu_item == 1) {
  display.clearDisplay();
  // User
  display.drawBitmap(0, 36, Wizard_Sprite, 16, 12, BLACK);
  display.setCursor(17,40);
  display.print(heroname);
  display.print(heroHP);
  
  // Foe
  display.drawBitmap(68, 0, Wizard_Sprite, 16, 12, BLACK);
  display.setCursor(0,0);
  display.print("Enemy");
  display.println(enemyHP);
  
  delay(1000);
  
  display.setCursor(0,16);
  display.println("A:Attack");
  display.println("B:Defend");
  display.display();
  
  
  while(battle_menu == 0) {
    if(digitalRead(up_button) == 0) {
      enemyHP = enemyHP - 40;
      battle_menu = 1;
    } else if(digitalRead(right_button) == 0) {
      defence = true;
      battle_menu = 2;
    }
    
  }
  
  battle_menu = 0;
  
  // Check if enemy HP <= 0
  if(enemyHP < 1) {
    winner();
  }
  
  // enemy attacks
  if(defence == true) {
    heroHP = heroHP - 20;
  } else {
    heroHP = heroHP - 30;
  }
  
  // reset defence
  defence = false;
  
  // check if user HP <= 0
  if(heroHP < 1) {
    loser();
  }

 }
}

void winner() {
  display.clearDisplay();
  display.println("You Win");
  display.display();
  delay(5000);
  mainmenu();
}

void loser() {
  display.clearDisplay();
  display.println("You Lose");
  display.display();
  delay(5000);
  mainmenu();
}

