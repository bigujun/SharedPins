#ifndef COMPARTILHADO_H
#define COMPARTILHADO_H
#include <Arduino.h>
//TODO CRC-16
//CONEXAO ESP AT MEGA
// Bigujun 12/2017

//-----EXEMPLO:
//  pinosATmega::HX711_CLK

#define totalPinosCompartilhados 6
#define COMAND_HANDLE_RECEIVE "HNDRCV"
#define COMAND_DIGITAL_WRITE "DIGWRT"
#define COMAND_PIN_MODE "PINMOD"
#define COMMAND_DIGITAL_READ "DIGRED"


#if !(defined(__AVR_ATmega328P__) || defined(ESP8266))
  #error "ESP8266 OU ATmega328P ??"
#endif

#if defined(__AVR_ATmega328P__)
  #define SIZE_RECEIVE sizeof(ESP2AT)
  #define SIZE_SEND sizeof(AT2ESP)
  #define RECEIVE_t ESP2AT
  #define SEND_t AT2ESP
  #define SEND_obj at2esp
  #define RECEIVE_obj esp2at
#elif defined(ESP8266)
  #define SIZE_RECEIVE sizeof(AT2ESP)
  #define SIZE_SEND sizeof(ESP2AT)
  #define RECEIVE_t AT2ESP
  #define SEND_t ESP2AT
  #define SEND_obj esp2at
  #define RECEIVE_obj at2esp
#else
  #error "ESP8266 E ATmega328P ??"
#endif


//Pinagens
enum pinosATmega
{
HX711_CLK_pin	=  3,   //HX711-CLK	INT1	OC2B	3	PCINT19	PD3
TEMP_SENS_pin	=  4,   //SENS-D18B20	DHT22			4	PCINT20	PD4
CON_A1_pin		  = 20,  //COOL		XTAL1		20	PCINT6	PB6
CON_A2_pin		  = 21,  //HEAT_3		XTAL2		21	PCINT7	PB7
MOSFET_1_pin  =	5,   //COOLER	RACAO		OC0B	5	PCINT21	PD5
MOSFET_2_pin   =	6,   //DESCARTE	AIN0	OC0A	6	PCINT22	PD6
HX711_DT_pin   =	7,   //HX711-DT	=	AIN1		7	PCINT23	PD7
RST_ESP_pin	  = 	8,   //RST_ESP	RST→ESP			8	PCINT0	PB0
BAT_OUT_pin	  = 	9,   //BAT-OUT		OC1A	9	PCINT1	PB1
SPI_CS_pin		  = 10 , //KEY4	RFID-SDA	SS	OC1B	10	PCINT2	PB2
SPI_MOSI_pin   =	11 , //MOSI	KEY3	RFID-MOSI	MOSI	OC2A	11	PCINT3	PB3
SPI_MISO_pin   =	12 , //MISO	KEY2	RFID-MISO	MISO		12	PCINT4	PB4

SPI_INT_pin    =   2 ,  //PD2	PCINT18	2		INT0	RFID-RST  KEY1			          SPI-INT-AT
SERIAL_TX_pin  =   1 ,  //PD1	PCINT17	1		TX	  ESP-RX	  ESP-RX		ESP-RX		SERIAL-TX-AT
SERIAL_RX_pin  =   0 ,  //PD0	PCINT16	0		RX	  ESP-TX	  ESP-TX		RSP-TX		SERIAL-RX-AT
//RST_AT     =  22 , //PC6	PCINT14	22		RST	=	=	RST	RST(capacitor)	PULL-UP	RST-AT
I2C_SCL_pin    =  19 , //PC5	PCINT13	19	A5	SCL	RTC-SDA	RTC-SDA				I2C-SCL-AT
I2C_SDA_pin    =  18 , //PC4	PCINT12	18	A4	SDA	RTC-SCL	RTC-SDA				I2C-SDA-AT
CON_B2_pin     =  17 , //PC3	PCINT11	17	A3		DESC-ENC	HEAT-1				PB-2
CON_B1_pin      = 16 , //PC2	PCINT10	16	A2		RACAO-ENC	BMB-1				PB-1
CON_C2_pin      = 15 , //PC1	PCINT9	15	A1			HEAT-2				PC-2
CON_C1_pin      = 14 , //PC0	PCINT8	14	A0			BMB-2				PC-1
//BAT_A7_PIN     =  A7 , //			A7		BAT-1					BAT-A7
// BAT_AREF   = AREF//
//BAT_A6_PIN     =  A6  ,//ADC6			A6		BAT-2					BAT-A6
SPI_SCLK_pin   =  13  //PB5	PCINT5	13		SCK	RFID-SCK	KEY5	SCK			SPI-SCLK-AT
};




enum pinosESP
{
                    //  PIN	I/O		ANLG	NODE	FUNCTIONS	TIGGU	SMART-BREW	BREW-ESP+AT	BOOT	FTDI(flash)	ESP>AT-FTDI	PCB
                    //	1		RST		RST		RST		ESP-IO16/BT-WIFI	ESP-IO16/BT-WIFI	ESP-IO16/BT-WIFI	PULL-UP	PULL-UP		BT-WIFI
                    //	2		ADC		A0		SENSOR-AGUA	SENSOR-AGUA				SENS-AGUA
                    //	3		EN		EN		ENABLE				PULL-UP
  WAKE_pin 	=	 16,	//	4		16		PWM		D0		USER / WAKE	ESP-RST	ESP-RST	ESP-RST				WAKE
                    //	5		14		PWM		D5		HSPI-CLK		HX711-CLK					HX711-CLK-ESP
  LED_pin 	=  12,	//	6		12		PWM		D6		HSPI-Q	=	LED	=				LED
  BT_WIFI_pin =13,	//	7		13		PWM		D7		HSPI-D / CTS0 / RX2	=	BT-WIFI	=				BT-WIFI
                    //	22	1			PWM		TX0 / CS1	TX	ATMEGA-RX	SENS-D18B20	ATMEGA-RX		RX	RX	SERIAL-TX-ESP
                    //	21	3			PWM		RX0	RX	ATMEGA-TX	HX711-DT	ATMEGA-TX		TX	TX	SERIAL-RX-ESP
                    //	20	5			PWM		I2C-SCL	D1	SCL-3V3	HEAT-2	SCL-3V3				I2C-SCL-ESP / PD-1
                    //	19	4			PWM		I2C-SDA	D2	SDA-3V3	HEAT-1	SDA-3V3				I2C-SDA-ESP / PD-2
                    //	18	0			PWM		CS2/FLASH	D3		BOMBA2-INV		Pull UP	Pull DOWN		PE-1
  RST_AT_pin	= 2,	//	17	2			PWM		TX1	D4	FTDI-DTR	BOMBA1-INV	FTDI-DTR	Pull UP	Pull UP	DRT-RST	PE-2
  BUZZER_pin	=15  	//	16	15					TX2 / RTS0 / HSPI-CS	D8		BUZZER	BUZZER	Pull Down	Pull DOWN
                    //	14							CLK / SD-CLK	CLK							SPI2
                    //	13				INT		SD-D1	SD1							SPI2
                    //	12	10		PWM		CS  / SD-D3	SD3							SPI2
};

typedef struct _ESP2AT{
  char PINS[6];
}ESP2AT;

typedef struct _AT2ESP{
  long unixTime;
  long HX711[2];
  char totalTemp;
  unsigned int TEMP[2];
}AT2ESP;




class Compartilhado{

 public:
  static ESP2AT esp2at;
  static AT2ESP at2esp;
  //Compartilhado();
  static void set(ESP2AT);
  static void set(AT2ESP);
  static void send();
  static void handleReceive();
  static void setPin(char pin,char status);
  static void update();
  static void debug();
  const static char pinosCompartilhados[totalPinosCompartilhados];
 private:
};

#endif
