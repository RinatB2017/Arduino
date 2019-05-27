//---------------------------------------------------------------
#include <IRremote.h>
//---------------------------------------------------------------
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
//---------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}
//---------------------------------------------------------------
#if 0
class decode_results
{
public:
  decode_type_t          decode_type;  // UNKNOWN, NEC, SONY, RC5, ...
  unsigned int           address;      // Used by Panasonic & Sharp [16-bits]
  unsigned long          value;        // Decoded value [max 32-bits]
  int                    bits;         // Number of bits in decoded value
  volatile unsigned int  *rawbuf;      // Raw intervals in 50uS ticks
  int                    rawlen;       // Number of records in rawbuf
  int                    overflow;     // true iff IR raw code too long
};
#endif
//---------------------------------------------------------------
void print_type(decode_type_t type)
{
  switch(type)
  {
  case UNKNOWN:
    Serial.println("UNKNOWN");
    break;
  case UNUSED:
    Serial.println("UNUSED");
    break;
  case RC5:
    Serial.println("RC5");
    break;
  case RC6:
    Serial.println("RC6");
    break;
  case NEC:
    Serial.println("NEC");
    break;
  case SONY:
    Serial.println("SONY");
    break;
  case PANASONIC:
    Serial.println("PANASONIC");
    break;
  case JVC:
    Serial.println("JVC");
    break;
  case SAMSUNG:
    Serial.println("SAMSUNG");
    break;
  case WHYNTER:
    Serial.println("WHYNTER");
    break;
  case AIWA_RC_T501:
    Serial.println("AIWA_RC_T501");
    break;
  case LG:
    Serial.println("LG");
    break;
  case SANYO:
    Serial.println("SANYO");
    break;
  case MITSUBISHI:
    Serial.println("MITSUBISHI");
    break;
  case DISH:
    Serial.println("DISH");
    break;
  case SHARP:
    Serial.println("SHARP");
    break;
  case DENON:
    Serial.println("DENON");
    break;
  case PRONTO:
    Serial.println("PRONTO");
    break;
  }
}
//---------------------------------------------------------------
void loop(void) 
{
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    //print_type(results.decode_type);
    irrecv.resume(); // Receive the next value
  }
}
//---------------------------------------------------------------




