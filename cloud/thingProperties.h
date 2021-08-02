#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "secrets.h"


const char THING_ID[]           = "38bef95f-4481-4502-8a19-f9dbf18584e6";
const char DEVICE_LOGIN_NAME[]  = "d711de5f-96eb-4b45-83d5-29d7c9379faf";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onAguaChange();
void onFlujoChange();
void onTurbidezChange();
void onSuciedadChange();
void onHayAguaChange();

CloudPercentage agua;
CloudFlowRate flujo;
CloudLuminousIntensity turbidez;
CloudColor suciedad;
bool hay_agua;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(agua, READWRITE, ON_CHANGE, onAguaChange);
  ArduinoCloud.addProperty(flujo, READWRITE, ON_CHANGE, onFlujoChange);
  ArduinoCloud.addProperty(turbidez, READWRITE, ON_CHANGE, onTurbidezChange);
  ArduinoCloud.addProperty(suciedad, READWRITE, ON_CHANGE, onSuciedadChange);
  ArduinoCloud.addProperty(hay_agua, READWRITE, ON_CHANGE, onHayAguaChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
