#include "flprogUart.h"
#include "flprofDwin.h"
FlprogUartExecutor FLProgUart;
FLProgDwin dwin(1, 1, &FLProgUart);

uint32_t timerTime = 0;
uint32_t counterPeriod = 500;
int16_t counter = 0;
int16_t value5000 = 0;
int16_t value5006 = 0;
int16_t tempInt;
int16_t x = 6;
int16_t y = 6;


void setup()
{
  dwin.setUseCRC(false);
  dwin.setTableSize(0, 10);
  dwin.setType(0, FLPROG_DWIN_VP_TABLE);
  dwin.setAddress(0, 0, 0x5000);
  dwin.setAddress(0, 1, 0x5001);
  dwin.setAddress(0, 2, 0x5002);
  dwin.setAddress(0, 3, 0x5003);
  dwin.setAddress(0, 4, 0x5004);
  dwin.setAddress(0, 5, 0x5005);
  dwin.setAddress(0, 6, 0x5006);
  dwin.setAddress(0, 7, 0x5007);
  dwin.setAddress(0, 8, 0x7001);
  dwin.setAddress(0, 9, 0x7002);

  dwin.setSpeedUart(115200);
  dwin.setReqestPeriod(0, 100);
  timerTime = flprog::timeBack(counterPeriod);
  Serial4.begin(115200);
}

void loop()
{
  dwin.pool();
  if (flprog::isTimer(timerTime, counterPeriod))
  {
    timerTime = millis();
    if (counter > 100)
    {
      counter = -100;
    }
    else
    {
      counter++;
    }
    if (x > 40)
    {
      x = 0;
    }
    else
    {
      x++;
    }

    if (y > 35)
    {
      y = 0;
    }
    else
    {
      y++;
    }
    dwin.saveIntegerByIndex(0, counter, 2);
    dwin.saveIntegerByIndex(0, counter, 3);
    dwin.saveIntegerByIndex(0, counter, 4);

    dwin.saveIntegerByIndex(0, x, 8);
    dwin.saveIntegerByIndex(0, y, 9);
  }
  tempInt = dwin.readIntegerByIndex(0, 0);
  if (!(value5000 == tempInt))
  {
    value5000 = tempInt;
    Serial4.print("0x5000 = ");
    Serial4.println(value5000);
    dwin.saveIntegerByIndex(0, value5000, 6);
  }
  tempInt = dwin.readIntegerByIndex(0, 6);
  if (!(value5006 == tempInt))
  {
    value5006 = tempInt;
    Serial4.print("0x5006 = ");
    Serial4.println(value5006);
  }
}