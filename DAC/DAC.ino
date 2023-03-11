#include <Wire.h>

#define TCAADDR 0x70
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 forward;
Adafruit_MCP4725 back;
Adafruit_MCP4725 right;
Adafruit_MCP4725 left;

int val;String input;

void TCAChannel(uint8_t i) {
  Wire.beginTransmission(0x70);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void voltage(int channel,Adafruit_MCP4725 &DAC, long value) {
  TCAChannel(channel);
  DAC.setVoltage(value,false);

}
void setup() {
   Serial.begin(9600);

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  forward.begin(0x60);
  back.begin(0x60);
  right.begin(0x60);
  left.begin(0x60);
  voltage(0,forward,2048);
  voltage(1,back,2048);
  voltage(2,right,2048);
  voltage(3,left,2048);
}

void loop() {
while (Serial.available() == 0){}
  input=Serial.readString();
  if(input.startsWith("f"))
        {
         voltage(0,forward,3030);
          voltage(1,back,3030);
           voltage(2,right,2048);
            voltage(3,left,2048);
        }
  else if(input.startsWith("b"))
        {
         voltage(0,forward,900);
          voltage(1,back,900);
           voltage(2,right,2048);
            voltage(3,left,2048);
        }
 else if(input.startsWith("r"))
        {
          voltage(0,forward,2048);
           voltage(1,back,2048);
            voltage(2,right,3030);
             voltage(3,left,3030);
        }
else if(input.startsWith("l"))
        {
          voltage(0,forward,2048);
           voltage(1,back,2048);
            voltage(2,right,900);
             voltage(3,left,900);
        }
else if(input.startsWith("m"))
        {
          voltage(0,forward,2048);
           voltage(1,back,2048);
            voltage(2,right,2048);
             voltage(3,left,2048);
        }
  Serial.println(input);
  
}
