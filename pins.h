#ifndef PINS_H
#define PINS_H
#include <Arduino.h>
#include "config.h"
#include "DebugUtils.h"

//#include <pcf8574_esp.h>

/*
#define NODEMCU_PIN_A0 17
#define NODEMCU_PIN_D0 16	Buzzer
#define NODEMCU_PIN_D1 5	 [I/O]SCL // I2C
#define NODEMCU_PIN_D2 4	 [I/O]SDA // I2C
#define NODEMCU_PIN_D3 0
#define NODEMCU_PIN_D4 2
#define NODEMCU_PIN_D5 14    Pump
#define NODEMCU_PIN_D6 12    Sensor
#define NODEMCU_PIN_D7 13    Heater
#define NODEMCU_PIN_D8 15    auxHeaterIO
*/

#define I2C_SCL 	NODEMCU_PIN_D1
#define I2C_SDA 	NODEMCU_PIN_D2
#define SensorPin pinosATmega::TEMP_SENS_pin


#define ButtonUpPin    		1
#define ButtonDownPin  		2
#define ButtonStartPin 		6
#define ButtonEnterPin 		5
#define pumpPin  	pinosATmega::CON_C1_pin
#define heatPin  	pinosATmega::CON_C2_pin
#define AuxheatPin pinosATmega::CON_B1_pin

//#define BuzzControlPin pinosESP::BUZZER_pin

//Compartilhado

#include "compartilhado.h"
static Compartilhado compartilhado;

void teste()
{
	compartilhado.setPin(pumpPin, HIGH);
	compartilhado.send();
}



///CLASS DIGITAL IO

#define ATMEGA_SEND(...) Serial.print(__VA_ARGS__)
#define ATMEGA_SENDLN(...) Serial.println(__VA_ARGS__)


class DigitalIO{

public:
	enum Local{
			ESP,
			ATMEGA,
			VIRTUAL
	  };

	DigitalIO(uint8_t _pin, DigitalIO::Local _local){
	  local= _local;
	  pin=_pin;
	  value = 0;
	}

	void pinModeIO(uint8_t mode){
		//DEBUG_PRINTLN( String("DBG-PNMOD ") + String(pin) +String(" ")+ String(mode) );
	  switch (local) {
	    case ESP:
	      pinMode(pin, mode);
	    break;
	    case ATMEGA:
	      ATMEGA_SENDLN( String(COMAND_PIN_MODE) + String(pin) +String(" ")+ String(mode) );
	    break;
	  }
	}

	void digitalWriteIO(uint8_t _value){
		//DEBUG_PRINTLN( String("DBG-PNWRT ") + String(pin) +String(" ")+ String(value) );
	  switch (local) {
	    case ESP:
	      digitalWrite(pin, _value);
	    break;
	    case ATMEGA:
	      ATMEGA_SENDLN( String(COMAND_DIGITAL_WRITE) + String(pin) + String(" ") + String(value) );
	    break;
	  }
	  value = _value;
	}

	bool digitalReadIO(){
	  switch (local) {
	    case ESP:
	      return digitalRead(pin);
	    break;
	    case ATMEGA:
	      ATMEGA_SENDLN( String(COMMAND_DIGITAL_READ) + " " + String(pin) );
	    break;
	  }
	  return 0;
	}

	uint16_t analogReadIO(){
	  switch (local) {
	    case ESP:
	      return analogRead(pin);
	    break;
	    case ATMEGA:
	      ATMEGA_SENDLN( String("ANLGRD ") + String(pin) );
	    break;
	  }
	  return 0;
	}

	void analogWriteIO(uint8_t _value){
	  switch (local) {
	    case ESP:
	      //::analogWrite(pin,_value);
	      analogWrite(pin,_value);
	    break;
	    case ATMEGA:
	      ATMEGA_SENDLN( String("ANLGWR ") + String(pin) + String(_value) );
	    break;
	    value = _value;
	  }
	}

private:
	uint8_t pin;
	Local local;
	uint8_t value;
};


//FIM DIGITAL IO CLASS

 //DigitalIO auxHeaterIO(AuxheatPin, DigitalIO::ATMEGA);
 //DigitalIO heatIO(heatPin, DigitalIO::ATMEGA);
 //DigitalIO pumpIO(pumpPin, DigitalIO::ATMEGA);
 DigitalIO buzzerIO(pinosESP::BUZZER_pin, DigitalIO::ESP);
 DigitalIO wakeIO(pinosESP::WAKE_pin, DigitalIO::ESP);
 DigitalIO ledIO(pinosESP::LED_pin, DigitalIO::ESP);
 DigitalIO btnWifiIO(pinosESP::BT_WIFI_pin,DigitalIO::ESP);
 DigitalIO resetATIO(pinosESP::RST_AT_pin, DigitalIO::ESP);




uint8_t _portvalue;
void btnPrepareRead(void)
{
	//_portvalue=pcf8574.read8();
	resetATIO.digitalWriteIO(HIGH);
}


uint8_t btnReadPin(uint8_t pin)
{
	//return (_portvalue & pin);
	return 1;
}


// Heater, Pump, Buzz are OUTPUTs
inline void setHeaterOut(uint8_t v)
{
	//digitalWrite (heatPin, v);
	// heatIO.digitalWriteIO(v);
	//compartilhado.setPin(heatPin, v);
}

inline void setPumpOut(uint8_t v)
{
	//digitalWrite (pumpPin, v);
	// pumpIO.digitalWriteIO(v);
	 compartilhado.setPin(pumpPin, v);
}

inline void setBuzzOut(uint8_t v)
{
	// digitalWrite (BuzzControlPin, v);
		buzzerIO.digitalWriteIO(v);
}

inline void setAuxHeaterOut(uint8_t v)
{
	//digitalWrite (AuxheatPin, v);
	// 	auxHeaterIO.digitalWriteIO(v);
	//compartilhado.setPin(AuxheatPin, v);
}

inline void setSecondaryHeaterOut(uint8_t v)
{
	//digitalWrite (AuxheatPin, v);
	// 	auxHeaterIO.digitalWriteIO(v);
	//compartilhado.setPin(AuxheatPin, v);
}




void initIOPins(void)
{
//  	pinMode (ButtonUpPin,    INPUT_PULLUP);
//  	pinMode (ButtonDownPin,    INPUT_PULLUP);
//  	pinMode (ButtonStartPin, INPUT_PULLUP);
//  	pinMode (ButtonEnterPin, INPUT_PULLUP);
	DEBUG_PRINTLN("initIOPins");
// //		pinMode (heatPin, OUTPUT);
 //	heatIO.pinModeIO(OUTPUT);
//	heatIO.digitalWriteIO(LOW);
// //		pinMode (pumpPin, OUTPUT);
// 	pumpIO.pinModeIO(OUTPUT);
// //		setPumpOut(LOW);
 //	pumpIO.digitalWriteIO(LOW);
// //		pinMode (BuzzControlPin, OUTPUT);
 	buzzerIO.pinModeIO(OUTPUT);
// //		setBuzzOut(LOW);
 	buzzerIO.digitalWriteIO(LOW);
// //		pinMode (AuxheatPin, OUTPUT);
 //	auxHeaterIO.pinModeIO(OUTPUT);
// //		setauxHeaterOut(LOW);
// 	auxHeaterIO.digitalWriteIO(LOW);


	resetATIO.pinModeIO(INPUT);
	btnWifiIO.pinModeIO(INPUT);
	wakeIO.pinModeIO(OUTPUT);
	wakeIO.digitalWriteIO(HIGH);
	ledIO.pinModeIO(OUTPUT);
	ledIO.digitalWriteIO(LOW);
	delay(500);
	ledIO.digitalWriteIO(HIGH);
	delay(500);
	ledIO.digitalWriteIO(LOW);
	DEBUG_PRINTLN("#");
	teste();
}

#endif
