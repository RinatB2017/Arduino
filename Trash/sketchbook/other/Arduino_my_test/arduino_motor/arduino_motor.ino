//---------------------------------------------------------------
//#define USE_LCD
#define USE_SERVO
//---------------------------------------------------------------
#ifdef USE_LCD
  #include <LiquidCrystal.h>
#endif
//---------------------------------------------------------------
#include <SimpleModbusSlave.h>
#include <Servo.h> 
//---------------------------------------------------------------
#ifdef USE_LCD
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#endif  
//---------------------------------------------------------------
#ifdef USE_SERVO
  Servo myservo_1;
  Servo myservo_2;

  const int Motor_1  = 10;
  const int Motor_2  = 11;

  unsigned int value_motor_1 = 0;
  unsigned int value_motor_2 = 0;
  unsigned int old_value_motor_1 = 0;
  unsigned int old_value_motor_2 = 0;
#endif  
//---------------------------------------------------------------
enum 
{     
  // The first register starts at address 0
  VALUE_MOTOR_1,     
  VALUE_MOTOR_2,  
  TOTAL_ERRORS,  
  TOTAL_REGS_SIZE
};
unsigned int holdingRegs[TOTAL_REGS_SIZE]; // function 3 and 16 register array
//---------------------------------------------------------------
void setup(void)
{
/*
void modbus_configure(HardwareSerial *SerialPort,
                      long baud,
                      unsigned char byteFormat,
                      unsigned char _slaveID,
                      unsigned char _TxEnablePin,
                      unsigned int _holdingRegsSize,
                      unsigned int* _regs)
*/
  modbus_configure(&Serial, 
                    9600, 
                    SERIAL_8N1, 
                    1, 
                    2, 
                    TOTAL_REGS_SIZE, 
                    holdingRegs); 
#ifdef USE_LCD
  lcd.begin(16, 2);
#endif  

#ifdef USE_SERVO
  myservo_1.attach(Motor_1);
  myservo_2.attach(Motor_2);
  
  myservo_1.write(0);
  myservo_2.write(0);
#endif  
}
//---------------------------------------------------------------
void loop(void)
{
#ifdef USE_LCD
  lcd.clear();
#endif  

  holdingRegs[TOTAL_ERRORS] = modbus_update();

#ifdef USE_LCD
  lcd.setCursor(0, 0);
  lcd.print("update ");
  lcd.print(holdingRegs[TOTAL_ERRORS]);
  lcd.print(" ");
  lcd.print(get_my_error());
#endif  
  
#ifdef USE_LCD
  lcd.setCursor(0, 1);
  lcd.print(holdingRegs[VALUE_MOTOR_1]);
  lcd.print(' ');
  lcd.print(holdingRegs[VALUE_MOTOR_2]);
#endif  

#ifdef USE_SERVO
  value_motor_1 = holdingRegs[VALUE_MOTOR_1];
  if(value_motor_1 > 180) value_motor_1 = 180;
  value_motor_2 = holdingRegs[VALUE_MOTOR_2];
  if(value_motor_2 > 180) value_motor_1 = 180;

  if((value_motor_1 != old_value_motor_1) || 
     (value_motor_2 != old_value_motor_2))
  {
    myservo_1.write(value_motor_1);
    myservo_2.write(value_motor_2);
    old_value_motor_1 = value_motor_1;
    old_value_motor_2 = value_motor_2;
  }
#endif  
  delay(1000);
}
//---------------------------------------------------------------

