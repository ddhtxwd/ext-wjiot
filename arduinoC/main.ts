



//% color="#AA278D" iconWidth=50 iconHeight=40
namespace WJ_iot {



	/**
     * 连接WIFI
     * @param tx ; eg: "1"
     * @param rx ; eg: "0"
    */
    //% block="初始化 UART：TX引脚 1 RX引脚：0"
    //% subcategory="联网"
    export function WIFI_init(parameter: any, block: any){
        Generator.addInclude('wjiot', '#include <wjiot.h>');
		Generator.addObject(`wjiot`, `WJIOT`, `wjiot;`);
		Generator.addSetup(`wjiot.begin`, `wjiot.begin(1,0);`);
    }
    /**
     * 连接WIFI
     * @param ssid ; eg: "WIFI"
     * @param pass ; eg: "12345678"
    */
    //% block="连接WIFI 名称：[ssid] 密码：[pass]"
    //% subcategory="联网"

    export function WIFI_connect(parameter: any, block: any){
		let ssid=parameter.ssid.code;
		let pass=parameter.pass.code;
        Generator.addInclude('wjiot', '#include <wjiot.h>');
		Generator.addObject(`wjiot`, `WJIOT`, `wjiot;`);
		Generator.addSetup(`wjiot.begin`, `wjiot.begin();`);
		Generator.addCode(`wjiot.WIFI_connect(${ssid},${pass});`);
    }
	

    /**
     * 连接云平台
     * @param product_id ; eg: "123456"
     * @param machine_id ; eg: "123456789"
     * @param pass ; eg: "1234"
    */
    //% block="连接云平台 产品ID：[product_id] 设备ID：[machine_id] 鉴权信息：[pass]"
    //% subcategory="联网"
    export function OneNET_connect(parameter: any, block: any){
		let product_id=parameter.product_id.code;
		let machine_id=parameter.machine_id.code;
		let pass=parameter.pass.code;
        Generator.addInclude('wjiot', '#include <wjiot.h>');
		Generator.addObject(`wjiot`, `WJIOT`, `wjiot;`);
		Generator.addSetup(`wjiot.begin`, `wjiot.begin();`);
		Generator.addCode(`wjiot.OneNET_connect(${product_id},${machine_id},${pass});`);
    }
	
 
    /**
     * 向云平台发送信息
     * @param data_id ; eg: "temp"
     * @param data_value ; eg: "28.5"
    */
    //% block="向云平台发送信息 数据流名称：[data_id] 内容：[data_value]"
    //% subcategory="联网"
    export function OneNET_send(parameter: any, block: any){
        let data_id=parameter.data_id.code;
		let data_value=parameter.data_value.code;

        Generator.addInclude('wjiot', '#include <wjiot.h>');
		Generator.addObject(`wjiot`, `WJIOT`, `wjiot;`);
		Generator.addSetup(`wjiot.begin`, `wjiot.begin();`);
		Generator.addCode(`wjiot.OneNET_send(${data_id},${data_value});`);
    }   

    //% block="收到的命令" blockType="reporter"
    //% subcategory="联网"
    export function get_value(parameter: any, block: any){

        Generator.addInclude('wjiot', '#include <wjiot.h>');
		Generator.addObject(`wjiot`, `WJIOT`, `wjiot;`);
		Generator.addSetup(`wjiot.begin`, `wjiot.begin();`);
		///Generator.addCode(`wjiot.get_value()`);
		let code: string = `wjiot.get_value()`;
		Generator.addCode([code, Generator.ORDER_UNARY_POSTFIX]);
    }		
    
	/**
     * 开启接收另一个设备的信息
     * @param data_id ; eg: "cmd"
    */
    //% block="开启接收另一个设备的信息 话题名称：[data_id]"
    //% subcategory="联网"
    export function OneNET_subscribe(parameter: any, block: any){
        let data_id=parameter.data_id.code;

        Generator.addInclude('wjiot', '#include <wjiot.h>');
		Generator.addObject(`wjiot`, `WJIOT`, `wjiot;`);
		Generator.addSetup(`wjiot.begin`, `wjiot.begin();`);
		Generator.addCode(`wjiot.OneNET_subscribe(${data_id});`);
    }	
	/**
     * 向另一个设备发送信息
     * @param data_id ; eg: "cmd"
     * @param data_value ; eg: "28.5"
    */
    //% block="向另一个设备发送信息 话题名称：[data_id] 内容：[data_value]"
    //% subcategory="联网"
    export function OneNET_publish(parameter: any, block: any){
		let data_id=parameter.data_id.code;
		let data_value=parameter.data_value.code;
        Generator.addInclude('wjiot', '#include <wjiot.h>');
		Generator.addObject(`wjiot`, `WJIOT`, `wjiot;`);
		Generator.addSetup(`wjiot.begin`, `wjiot.begin();`);
		Generator.addCode(`wjiot.OneNET_publish(${data_id},${data_value});`);
    }
	
	//% block="连接到云平台成功" blockType="boolean"
    //% subcategory="联网"
    export function is_connected(parameter: any, block: any){
        Generator.addInclude('wjiot', '#include <wjiot.h>');
		Generator.addObject(`wjiot`, `WJIOT`, `wjiot;`);
		Generator.addSetup(`wjiot.begin`, `wjiot.begin();`);
		///Generator.addCode(`wjiot.get_value()`);
		let code: string = `wjiot.is_connected()`;
		Generator.addCode([code, Generator.ORDER_UNARY_POSTFIX]);
    }
	//% block="接收到命令？" blockType="boolean"
    //% subcategory="联网"
    export function is_available(parameter: any, block: any){
        Generator.addInclude('wjiot', '#include <wjiot.h>');
		Generator.addObject(`wjiot`, `WJIOT`, `wjiot;`);
		Generator.addSetup(`wjiot.begin`, `wjiot.begin();`);
		///Generator.addCode(`wjiot.get_value()`);
		let code: string = `wjiot.available()`;
		Generator.addCode([code, Generator.ORDER_UNARY_POSTFIX]);
    }
 


}


