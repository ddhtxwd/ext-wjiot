#ifndef _WJIOT_H
#define _WJIOT_H

#include "Arduino.h"
#include "Stream.h"



class WJIOT
{
public:

    WJIOT();

    ~WJIOT();
	Stream *wjSerial;
	bool is_wifi_conneted = false;
	bool is_mqtt_conneted = false;
	bool is_available = false;
	String receive_value;
	void WJIOT::serialInit(uint8_t send, uint8_t receive);
	void WJIOT::begin();
	void WJIOT::begin(uint8_t send, uint8_t receive);
	void WJIOT::WIFI_connect(const String &ssid,const String &pass);
	void WJIOT::OneNET_connect(const String &product_id,const String &machine_id,const String &pass);
	void WJIOT::OneNET_send(const String &data_id,const String &data_value);
	String WJIOT::get_value();
	void WJIOT::serialread();
	bool WJIOT::available();
	uint8_t WJIOT::prase_at_cmd(String data);
	void WJIOT::OneNET_subscribe(const String &data_id);
	void WJIOT::OneNET_publish(const String &data_id,const String &data_value);
	void WJIOT::is_connected();
	void WJIOT::lcd_display_number(int y, int x, int number);
	void WJIOT::lcd_display_string(int y, int x, const String &string);
};

#endif 
