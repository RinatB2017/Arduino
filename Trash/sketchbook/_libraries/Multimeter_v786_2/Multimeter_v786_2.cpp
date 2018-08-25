//---------------------------------------------------------------
#include "Multimeter_v786_2.h"
//---------------------------------------------------------------
Multimeter_v786_2::Multimeter_v786_2()
{

}
//---------------------------------------------------------------
bool Multimeter_v786_2::send_question_and_get_answer(uint8_t *question_buf,
				    int question_len,
				    uint8_t *answer_buf,
				    int answer_len)
{
    input_buf_index = question_len;
    for(int n=0; n<question_len; n++)
      input_buf[n] = question_buf[n];
    
    bool ok = false;
    switch(input_buf[2])
    {
      case CMD_GET_STATE:
	ok = check_CMD_GET_STATE();
	if(ok)
	{
	}
	break;
      case CMD_REMOTE_CONTROL_ON:
	ok = check_CMD_REMOTE_CONTROL_ON();
	if(ok)
	{
	}
	break;
      case CMD_REMOTE_CONTROL_OFF:
	ok = check_CMD_REMOTE_CONTROL_OFF();
	if(ok)
	{
	}
	break;
      case CMD_SERVICE_ON:
	ok = check_CMD_SERVICE_ON();
	if(ok)
	{
	}
	break;
      case CMD_POWER_OFF:
	ok = check_CMD_POWER_OFF();
	if(ok)
	{
	}
	break;
      case CMD_MEASURING_DC_VOLTAGE:
	ok = check_CMD_MEASURING_DC_VOLTAGE();
	if(ok)
	{
	}
	break;
      case CMD_MEASURING_AC_VOLTAGE:
	ok = check_CMD_MEASURING_AC_VOLTAGE();
	if(ok)
	{
	}
	break;
      case CMD_MEASURING_DC_CURRENT:
	ok = check_CMD_MEASURING_DC_CURRENT();
	if(ok)
	{
	}
	break;
      case CMD_MEASURING_AC_CURRENT:
	ok = check_CMD_MEASURING_AC_CURRENT();
	if(ok)
	{
	}
	break;
      case CMD_MEASURING_R:
	ok = check_CMD_MEASURING_R();
	if(ok)
	{
	}
	break;
      case CMD_MEASURING_C:
	ok = check_CMD_MEASURING_C();
	if(ok)
	{
	}
	break;
      case CMD_MEASURING_L:
	ok = check_CMD_MEASURING_L();
	if(ok)
	{
	}
	break;
      case CMD_CONTINUITY:
	ok = check_CMD_CONTINUITY();
	if(ok)
	{
	}
	break;
      case CMD_MEASURING_F:
	ok = check_CMD_MEASURING_F();
	if(ok)
	{
	}
	break;
      case CMD_MEASURING_ACTIVE_POWER:
	ok = check_CMD_MEASURING_ACTIVE_POWER();
	if(ok)
	{
	}
	break;
      case CMD_MEASURING_REACTIVE_POWER:
	ok = check_CMD_MEASURING_REACTIVE_POWER();
	if(ok)
	{
	}
	break;
      case CMD_MEASURING_FULL_POWER:
	ok = check_CMD_MEASURING_FULL_POWER();
	if(ok)
	{
	}
	break;
      case CMD_MEASURING_POWER_FACTOR:
	ok = check_CMD_MEASURING_POWER_FACTOR();
	if(ok)
	{
	}
	break;
      case CMD_CALIBRATION_DC_VOLTAGE:
	ok = check_CMD_CALIBRATION_DC_VOLTAGE();
	if(ok)
	{
	}
	break;
      case CMD_CALIBRATION_AC_VOLTAGE:
	ok = check_CMD_CALIBRATION_AC_VOLTAGE();
	if(ok)
	{
	}
	break;
      case CMD_CALIBRATION_DC_CURRENT:
	ok = check_CMD_CALIBRATION_DC_CURRENT();
	if(ok)
	{
	}
	break;
      case CMD_CALIBRATION_AC_CURRENT:
	ok = check_CMD_CALIBRATION_AC_CURRENT();
	if(ok)
	{
	}
	break;
      case CMD_CALIBRATION_R:
	ok = check_CMD_CALIBRATION_R();
	if(ok)
	{
	}
	break;
      case CMD_ENABLING_CHARGE:
	ok = check_CMD_ENABLING_CHARGE();
	if(ok)
	{
	}
	break;
      case CMD_DISABLING_CHARGE:
	ok = check_CMD_DISABLING_CHARGE();
	if(ok)
	{
	}
	break;
      case CMD_REQUEST_SETTINGS_CHARGE:
	ok = check_CMD_REQUEST_SETTINGS_CHARGE();
	if(ok)
	{
	}
	break;
      case CMD_WRITE_TO_FLASH:
	ok = check_CMD_WRITE_TO_FLASH();
	if(ok)
	{
	}
	break;
	
      default:
	ok = false;
	break;
    }
    return ok;
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_GET_STATE(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_REMOTE_CONTROL_ON(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_REMOTE_CONTROL_OFF(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_SERVICE_ON(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_POWER_OFF(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_MEASURING_DC_VOLTAGE(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_MEASURING_AC_VOLTAGE(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_MEASURING_DC_CURRENT(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_MEASURING_AC_CURRENT(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_MEASURING_R(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_MEASURING_C(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_MEASURING_L(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_CONTINUITY(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_MEASURING_F(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_MEASURING_ACTIVE_POWER(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_MEASURING_REACTIVE_POWER(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_MEASURING_FULL_POWER(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_MEASURING_POWER_FACTOR(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_CALIBRATION_DC_VOLTAGE(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_CALIBRATION_AC_VOLTAGE(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_CALIBRATION_DC_CURRENT(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_CALIBRATION_AC_CURRENT(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_CALIBRATION_R(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_ENABLING_CHARGE(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_DISABLING_CHARGE(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_REQUEST_SETTINGS_CHARGE(void)
{
  
}
//---------------------------------------------------------------
bool Multimeter_v786_2::check_CMD_WRITE_TO_FLASH(void)
{
  
}
//---------------------------------------------------------------
// Compute the MODBUS RTU CRC
uint16_t Multimeter_v786_2::ModRTU_CRC(unsigned char *buf, int len)
{
  unsigned short crc = 0xFFFF;

  for (int pos = 0; pos < len; pos++)
  {
    crc ^= (unsigned short)buf[pos]; 

    for (int i = 8; i != 0; i--)
    {
      if ((crc & 0x0001) != 0)
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
        crc >>= 1;
    }
  }
  return crc;
}
//---------------------------------------------------------------
