#include "wjiot.h"
#include <SoftwareSerial.h>

String inputString = ""; //缓存
WJIOT *myWJIOT;


WJIOT::WJIOT()
{
    myWJIOT=this;
}

WJIOT::~WJIOT()
{
    
}


void WJIOT::serialInit(uint8_t send, uint8_t receive)
{
	if(send==1 && receive==0){
		Serial.begin(115200);
		wjSerial=&Serial;
	}else{
		SoftwareSerial softwareSerial(receive, send);
		softwareSerial.begin(115200);
		wjSerial=&softwareSerial;
	}
	
}

void WJIOT::begin()
{
	serialInit(14, 13);
}

void WJIOT::begin(uint8_t send, uint8_t receive)
{
	delay(1000);
	serialInit(send, receive);
	delay(500);
}

void WJIOT::WIFI_connect(const String &ssid,const String &pass)
{
	is_wifi_conneted==false;
	delay(10);
	String msg = "AT+XMU_WIFI=" + ssid + ',' + pass + '\n';
	while(is_wifi_conneted==false){
		wjSerial->print(msg.c_str());
		long start_time = millis();
		while(millis() - start_time < 5000){
			delay(10);
			serialread();
		}
	}
}

void WJIOT::OneNET_connect(const String &product_id,const String &machine_id,const String &pass)
{
	is_mqtt_conneted=false;
	delay(10);
	String msg = "AT+ONENET=" + product_id + ',' + machine_id + ',' + pass + '\n';
	while(is_mqtt_conneted==false){
		wjSerial->print(msg.c_str());
		long start_time = millis();
		while(millis() - start_time < 5000){
			delay(10);
			serialread();
		}
	}
}

void WJIOT::OneNET_send(const String &data_id,const String &data_value)
{
	if(is_mqtt_conneted==false)return;
    String msg = "AT+ON_SEND=" + data_id + ',' + data_value + '\n';
	wjSerial->print(msg.c_str());
    delay(100);
}
String WJIOT::get_value()
{
	serialread();
	return receive_value;
}
bool WJIOT::available()
{
    serialread();
	if(is_available==true){
		is_available=false;
		return true;
	}
    return false;
}
void WJIOT::OneNET_subscribe(const String &data_id){
	if(is_mqtt_conneted==false)return;
	String msg = "AT+SUBSCRIBE=" + data_id + '\n';
	wjSerial->print(msg.c_str());
    delay(100);
}
void WJIOT::OneNET_publish(const String &data_id,const String &data_value)
{
	if(is_mqtt_conneted==false)return;
    String msg = "AT+PUBLISH=" + data_id + ',' + data_value + '\n';
	wjSerial->print(msg.c_str());
    delay(100);
}
void WJIOT::is_connected()
{
	return is_mqtt_conneted;
}
void WJIOT::lcd_display_number(int y, int x, int number){
    String msg = "AT+DRAW="  + String(x) + ',' + String(y+1) + ',' + String(number) + '\n';
	wjSerial->print(msg.c_str());
    delay(100);    
}
void WJIOT::lcd_display_string(int y, int x, const String &string){
    String msg = "AT+DRAW="  + String(x) + ',' + String(y+1) + ',' + string + '\n';
	wjSerial->print(msg.c_str());
    delay(100);    
}
uint8_t WJIOT::prase_at_cmd(String data)
{
  uint8_t cmd = 0;
  uint8_t receive_start = 10;

  if (!data.startsWith("AT"))
  {
    return 99;
  }
  if (!data.startsWith("+", 2))
  {
    return 98;
  }
  if (data.startsWith("X", 3))
  {
    is_wifi_conneted = true;
  }
  else if (data.startsWith("O", 3))
  {
    is_mqtt_conneted = true;
  }
  else if (data.startsWith("R", 3))
  {
	  is_available=true;
    receive_value = data.substring(11, data.length());
  }
  else
  {
    return 97;
  }

}
void WJIOT::serialread() {
  while (wjSerial->available())
  {
    char bytes = wjSerial->read();
   // Serial.print(bytes);//debug
    if (bytes == '\n'||bytes == '\r')
    {
      while (inputString.length() > 0)
      {
        if (!inputString.startsWith("A"))
        {
          inputString.remove(0, 1);
        }
        else
        {
          break;
        }
      }
      while (inputString.length() > 0)
      {
        if (!inputString.startsWith("T",1))
        {
          inputString.remove(0, 1);
        }
        else
        {
          break;
        }
      }
      prase_at_cmd(inputString);
      inputString.remove(0, inputString.length());
    }
    else
    {
      inputString = inputString + String(bytes);
    }
  }
}

// static void mqttTick()
// {
	// //int n = uBit.serial.getRxBufferSize();
	// //ManagedString s = uBit.serial.read(n, MicroBitSerialMode::ASYNC);
	// String serial_read = s.toCharArray();
	// //argumentParsing(Obloq_message_str);
	// //serial_read = "";
		
    // //serial_read = serial.readString()
	// static String Obloq_message_str;

    // while (obloqSerial && obloqSerial->available() > 0)
    // {
        // int c;
        // while (obloqSerial->available())
        // {
            // c = obloqSerial->read();
            // if (c >= 0)
                // Obloq_message_str += (char)c;
            // if (c == '\n')
		// }
	// }
	// if (serial_read.indexOf("AT",0) != -1) {
		// if (serial_read.indexOf("XMU_WIFI",0) != -1 && serial_read.indexOf("OK",0) != -1) {
			// myWJIOT->is_wifi_conneted = true;
			// //if (wifi_conneted) wifi_conneted()
		// }
		// else if (serial_read.indexOf("ONENET",0) != -1 && serial_read.indexOf("OK",0) != -1) {
			// myWJIOT->is_mqtt_conneted = true;
			// //if (mqtt_conneted) mqtt_conneted()
		// }
		// else if (serial_read.indexOf("RECEIVE",0) != -1) {
			// int start_index = 11;
			// myWJIOT->receive_value = serial_read.substring(start_index, serial_read.length() - start_index);
			// while (myWJIOT->receive_value.length() > 0) {
				// String c = receive_value.substr(myWJIOT->receive_value.length() - 1, myWJIOT->receive_value.length());
				// if (c == '\r' || c == '\n') {
					// myWJIOT->receive_value = myWJIOT->receive_value.substr(0, myWJIOT->receive_value.length() - 1);
				// } else {
					// break
				// }
			// }
			// if (mqtt_received) mqtt_received();
		// }
	// }
// }