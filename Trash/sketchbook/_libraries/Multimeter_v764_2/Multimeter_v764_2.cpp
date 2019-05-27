//---------------------------------------------------------------
#include "Multimeter_v764_2.h"
//---------------------------------------------------------------
Multimeter_v764_2::Multimeter_v764_2()
{

}
//---------------------------------------------------------------
bool Multimeter_v764_2::send_question_and_get_answer(uint8_t *question_buf,
				    int question_len,
				    uint8_t *answer_buf,
				    int *answer_len)
{
    input_buf_index = question_len;
    for(int n=0; n<question_len; n++)
      input_buf[n] = question_buf[n];
    
    bool ok = false;
    switch(input_buf[1])
    {
      case V764_2_CMD_0x41:
	ok = check_V764_2_CMD_0x41();
	if(ok)
	{
	}
	break;
	
      case V764_2_CMD_0x42:
	ok = check_V764_2_CMD_0x42();
	if(ok)
	{
	}
	break;
	
      case V764_2_CMD_0x45:
	ok = check_V764_2_CMD_0x45();
	if(ok)
	{
	  CMD_V7642_0x45_ANSWER answer;
	  answer.data.address = 1;
	  answer.data.cmd = V764_2_CMD_0x45;
	  answer.data.count_data = 0;
	  answer.data.crc16 = crc16((unsigned char *)&answer.buf, sizeof(CMD_V7642_0x46_ANSWER) - 2);;

	  for(int n=0; n<sizeof(CMD_V7642_0x45_ANSWER); n++)
	    *answer_buf++ = answer.buf[n];
	  *answer_len = sizeof(CMD_V7642_0x45_ANSWER);
	}
	break;
	
      case V764_2_CMD_0x46:
	ok = check_V764_2_CMD_0x46();
	if(ok)
	{
	  CMD_V7642_0x46_ANSWER answer;
	  answer.data.address = 1;
	  answer.data.cmd = V764_2_CMD_0x46;
	  answer.data.count_data = 9;
	  answer.data.type = 0;
	  answer.data.year = 14;
	  answer.data.month = 1;
	  answer.data.serno_lo = 200;
	  answer.data.serno_hi = 0;
	  answer.data.baud = 0;
	  answer.data.time_waiting = 1;
	  answer.data.address_station = 1;
	  answer.data.byte_test = 1;
	  answer.data.crc16 = crc16((unsigned char *)&answer.buf, sizeof(CMD_V7642_0x46_ANSWER) - 2);
	  
	  for(int n=0; n<sizeof(CMD_V7642_0x46_ANSWER); n++)
	    *answer_buf++ = answer.buf[n];
	  *answer_len = sizeof(CMD_V7642_0x46_ANSWER);
	}
	break;
	
      case V764_2_CMD_0x47:
	ok = check_V764_2_CMD_0x47();
	if(ok)
	{
	  CMD_V7642_0x47_ANSWER answer;
	  answer.data.address = 1;
	  answer.data.cmd = V764_2_CMD_0x47;
	  answer.data.count_data = 8;
	  answer.data.state = 0;
	  answer.data.error = 0;
	  answer.data.value = 666;
	  answer.data.crc16 = crc16((unsigned char *)&answer.buf, sizeof(CMD_V7642_0x47_ANSWER) - 2);

	  for(int n=0; n<sizeof(CMD_V7642_0x47_ANSWER); n++)
	    *answer_buf++ = answer.buf[n];
	  *answer_len = sizeof(CMD_V7642_0x47_ANSWER);
	}
	break;
	
      case V764_2_CMD_0x48:
	ok = check_V764_2_CMD_0x48();
	if(ok)
	{
	  CMD_V7642_0x48_ANSWER answer;
	  answer.data.address = 1;
	  answer.data.cmd = V764_2_CMD_0x48;
	  answer.data.count_data = 1;
	  answer.data.address_station = 1;
	  answer.data.crc16 = crc16((unsigned char *)&answer.buf, sizeof(CMD_V7642_0x48_ANSWER) - 2);

	  for(int n=0; n<sizeof(CMD_V7642_0x48_ANSWER); n++)
	    *answer_buf++ = answer.buf[n];
	  *answer_len = sizeof(CMD_V7642_0x48_ANSWER);
	}
	break;
	
      case V764_2_CMD_0x53:
	ok = check_V764_2_CMD_0x53();
	if(ok)
	{
	  CMD_V7642_0x53_ANSWER answer;
	  answer.data.address = 1;
	  answer.data.cmd = V764_2_CMD_0x53;
	  answer.data.count_data = 1;
	  answer.data.data = 1;
	  answer.data.crc16 = crc16((unsigned char *)&answer.buf, sizeof(CMD_V7642_0x53_ANSWER) - 2);

	  for(int n=0; n<sizeof(CMD_V7642_0x53_ANSWER); n++)
	    *answer_buf++ = answer.buf[n];
	  *answer_len = sizeof(CMD_V7642_0x53_ANSWER);
	}
	break;
      

      default:
	ok = false;
	break;
    }
    return ok;
}
//---------------------------------------------------------------
bool Multimeter_v764_2::check_V764_2_CMD_0x41(void)
{
    return true;
}
//---------------------------------------------------------------
bool Multimeter_v764_2::check_V764_2_CMD_0x42(void)
{
    return true;
}
//---------------------------------------------------------------
bool Multimeter_v764_2::check_V764_2_CMD_0x45(void)
{
    return true;
}
//---------------------------------------------------------------
bool Multimeter_v764_2::check_V764_2_CMD_0x46(void)
{
    return true;
}
//---------------------------------------------------------------
bool Multimeter_v764_2::check_V764_2_CMD_0x47(void)
{
    return true;
}
//---------------------------------------------------------------
bool Multimeter_v764_2::check_V764_2_CMD_0x48(void)
{
    return true;
}
//---------------------------------------------------------------
bool Multimeter_v764_2::check_V764_2_CMD_0x53(void)
{
    return true;
}
//---------------------------------------------------------------
// Compute the MODBUS RTU CRC
uint16_t Multimeter_v764_2::crc16(unsigned char *buf, int len)
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
