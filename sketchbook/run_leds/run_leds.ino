/*
 * тест
 */

int pin_0 = 2;
int pin_1 = 3;
int pin_2 = 4;
int pin_3 = 5;
int pin_4 = 6;
int pin_5 = 7;
int pin_6 = 8;
int pin_7 = 9;

int x = 0;

uint8_t buf[8][8] = {
   1,1,1,1,1,1,1,1,
   1,1,0,0,0,0,0,1,
   1,0,1,0,0,0,0,1,
   1,0,0,1,0,0,0,1,
   1,0,0,0,1,0,0,1,
   1,0,0,0,0,1,0,1,
   1,0,0,0,0,0,1,1,
   1,1,1,1,1,1,1,1 
};

void setup() {
  pinMode(pin_0,  OUTPUT);
  pinMode(pin_1,  OUTPUT);
  pinMode(pin_2,  OUTPUT);
  pinMode(pin_3,  OUTPUT);
  pinMode(pin_4,  OUTPUT);
  pinMode(pin_5,  OUTPUT);
  pinMode(pin_6,  OUTPUT);
  pinMode(pin_7,  OUTPUT);
}

void loop() {
  digitalWrite(pin_0, (buf[x][0] == 1) ? HIGH : LOW);
  digitalWrite(pin_1, (buf[x][1] == 1) ? HIGH : LOW);
  digitalWrite(pin_2, (buf[x][2] == 1) ? HIGH : LOW);
  digitalWrite(pin_3, (buf[x][3] == 1) ? HIGH : LOW);
  digitalWrite(pin_4, (buf[x][4] == 1) ? HIGH : LOW);
  digitalWrite(pin_5, (buf[x][5] == 1) ? HIGH : LOW);
  digitalWrite(pin_6, (buf[x][6] == 1) ? HIGH : LOW);
  digitalWrite(pin_7, (buf[x][7] == 1) ? HIGH : LOW);
  
  if(x<8)
    x++;
  else
    x=0;
  
  delay(10);
}
