//CONEXAO ESP AT MEGA
// Bigujun 12/2017

#include "compartilhado.h"
#include "DebugUtils.h"
/*Compartilhado::Compartilhado()
{

}
*/
const char Compartilhado::pinosCompartilhados[] =
                        {
                          pinosATmega::CON_A1_pin,
                          pinosATmega::CON_A2_pin,
                          pinosATmega::CON_B1_pin,
                          pinosATmega::CON_B2_pin,
                          pinosATmega::CON_C1_pin,
                          pinosATmega::CON_C2_pin
                        };

ESP2AT Compartilhado::esp2at;
AT2ESP Compartilhado::at2esp;

void Compartilhado::handleReceive()
{
  DEBUG_PRINTLN("DBG-handleReceive");
  if(Serial.available() >= SIZE_RECEIVE)
  {
      static RECEIVE_t aux;
      static char *auxPonteiro = (char*)&aux;
      for(int i=0;i>SIZE_RECEIVE;i++)
      {
        auxPonteiro[i]=Serial.read();
      }
      set(aux);
      update();
  }

}

#if defined(__AVR_ATmega328P__)
void Compartilhado::update()
{
  for(int i=0; i<totalPinosCompartilhados; i++)
  {
    digitalWrite(pinosCompartilhados[i], esp2at.PINS[i]);
  }
}

#else
void Compartilhado::update()
{

}
#endif //#if defined(__AVR_ATmega328P__)




void Compartilhado::set(ESP2AT _esp2at)
{
  esp2at = _esp2at;


}

void Compartilhado::debug()
{
  DEBUG_PRINT("PINS-");
  for(int i=0;i<totalPinosCompartilhados;i++)
    Serial.write('0'+ esp2at.PINS[i]);
  DEBUG_PRINTLN("#");
}

void Compartilhado::set(AT2ESP _at2esp)
{
  at2esp = _at2esp;
}

void Compartilhado::send()
{
  Serial.println(COMAND_HANDLE_RECEIVE);
  Serial.write((uint8_t*) &SEND_obj,SIZE_SEND);
}

void Compartilhado::setPin(char pin, char status)
{
  for(char i=0;i<totalPinosCompartilhados;i++)
  {
    if(pin == pinosCompartilhados[i])
        esp2at.PINS[i] = status;
  }
  send();
}


//TODO
/*
--Permite string
#define DECL_ERROR_TYPE(errorType, value) , errorType = value << 16
#define DECL_ERROR(errorType, cause, value) , errorType##_##cause = (errorType + value)

#define GET_ERROR_TYPE(error) (error & 0xFFFF0000)

enum Error
{
NoError = 0
DECL_ERROR_TYPE(Type1, 1)
DECL_ERROR(Type1, Cause1, 1)
DECL_ERROR(Type1, Cause2, 2)

DECL_ERROR_TYPE(Type2, 2)
DECL_ERROR(Type2, Cause1, 1)

DECL_ERROR_TYPE(Type3, 3)
DECL_ERROR(Type3, Cause1, 1)
DECL_ERROR(Type3, Cause2, 2)
};


-----------------ex
Error err1 = Type1_Cause1;

if(Type1 == GET_ERROR_TYPE(err1))
    return 0; // Works

*/

//TODO

/*

struct ErrorType
{
   enum type {
      UNKNOWNTYPE = 0,
      TYPE1 = 1,
      TYPE2 = 2,
      TYPE3 = 3
   };
};

struct ErrorSubtype
{
   enum type {
      UNKNOWNSUBTYPE = 0,
      // subtype for error type 1
      CAUSE1 = 1001,
      CAUSE2 = 1002,
      CAUSE3 = 1003,
      // subtype for error type 2
      CAUSE4 = 2001,
      CAUSE5 = 2002
   };
};

struct Error
{
   ErrorType::type type;
   ErrorSubtype::type subtype;
};

int main()
{
   Error error;
   error.type = ErrorType::TYPE1;
   error.subtype = ErrorSubtype::CAUSE1;
}

*/
