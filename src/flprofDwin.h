#pragma once
#include <Arduino.h>
#include "flprogUtilites.h"
#include "fLProgDwinDataTable.h"

class FLProgDwin
{
public:
  FLProgDwin(uint8_t croupsSize, FlprogAbstractUartExecutor *executor);

  void setTableSize(uint8_t groupIndex, int32_t dataSize);
  void setAddress(uint8_t groupIndex, int32_t addressIndex, int32_t address);
  void setReqestPeriod(uint8_t groupIndex, uint32_t period);

  uint32_t address(uint8_t groupIndex, int32_t addressIndex);
  int32_t indexForAddres(uint8_t groupIndex, int32_t address);
  uint32_t reqestPeriod(uint8_t groupIndex);

  void saveLongByIndex(uint8_t groupIndex, int32_t value, int32_t startAddressIndex);
  void saveUnsignedLongByIndex(uint8_t groupIndex, uint32_t value, int32_t startAddressIndex);
  void saveFloatByIndex(uint8_t groupIndex, float value, int32_t startAddressIndex);
  void saveIntegerByIndex(uint8_t groupIndex, int16_t value, int32_t startAddressIndex);
  void saveByteByIndex(uint8_t groupIndex, uint8_t value, int32_t startAddressIndex);
  void saveBoolByIndex(uint8_t groupIndex, bool value, int32_t startAddressIndex);

  uint8_t readByteByIndex(uint8_t groupIndex, int32_t startAddressIndex);
  int16_t readIntegerByIndex(uint8_t groupIndex, int32_t startAddressIndex);
  float readFloatByIndex(uint8_t groupIndex, int32_t startAddressIndex);
  int32_t readLongByIndex(uint8_t groupIndex, int32_t startAddressIndex);
  uint32_t readUnsignedLongByIndex(uint8_t groupIndex, int32_t startAddressIndex);
  bool readBoolByIndex(uint8_t groupIndex, int32_t startAddressIndex);

  void setCallBack(FLProgDwinNewDataCallback func) { _newDataCallback = func; };

protected:
  FlprogAbstractUartExecutor *_executor = 0;
  FLProgDwinDataTable *_tables = 0;
  uint8_t _croupsSize = 0;
  uint8_t *_values = 0;
};