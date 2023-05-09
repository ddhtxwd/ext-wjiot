#ifndef _WJIOT_H
#define _WJIOT_H

#include "Arduino.h"
#include "Stream.h"
#include<vector>
#include <iostream>


class WJIOT:
{
public:

    WJIOT();

    ~WJIOT();
	
	bool is_wifi_conneted = false;
	bool is_mqtt_conneted = false;
	String receive_value;
	
	void WJIOT::begin();
	void WJIOT::begin(uint8_t send, uint8_t receive);
	void WJIOT::WIFI_connect(const String &ssid,const String &pass);
	void WJIOT::OneNET_connect(const String &product_id,const String &machine_id,const String &pass);
	void WJIOT::OneNET_send(const String &data_id,const String &data_value);
	void WJIOT::get_value();
	void WJIOT::on_wifi_connected(const MsgHandleCb handle);
	void WJIOT::on_mqtt_connected(const MsgHandleCb handle);
	void WJIOT::on_mqtt_receiveed(const MsgHandleCb handle);
	void WJIOT::OneNET_subscribe(const String &data_id);
	void WJIOT::OneNET_publish(const String &data_id,const String &data_value);
	void WJIOT::is_connected();
	void WJIOT::lcd_display_number(int y, int x, int number);
	void WJIOT::lcd_display_string(int y, int x, const String &string);
};

#endif 
