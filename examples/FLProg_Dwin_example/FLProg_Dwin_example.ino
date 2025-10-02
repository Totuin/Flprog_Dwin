#include "flprogUart.h"
#include "flprofDwin.h"
FlprogUartExecutor FLProgUart;
FLProgDwin dwin(1, 1, &FLProgUart);

void setup()
{
  dwin.setTableSize(0, 1);
  dwin.setAddress(0, 0, 0x5000);
  dwin.setSpeedUart(115200);
  dwin.setReqestPeriod(0, 10);

  Serial6.begin(115200);
}

void loop()
{
  dwin.pool();
}