#pragma once
#include <Arduino.h>
#include "flprogUtilites.h"

typedef void (*FLProgDwinNewDataCallback)(uint8_t index, int32_t addressIndex, int8_t value);

class FLProgDwinDataTable
{
public:
  FLProgDwinDataTable() {};

  void index(uint8_t index) { _index = _index; };
  uint8_t index() { return _index; };
  void setTableSize(int32_t dataSize);
  void setAddress(int32_t addressIndex, int32_t address);
  void setReqestPeriod(uint32_t period) { _reqestPeriod = period; };

  int32_t address(int32_t addressIndex);
  int32_t indexForAddres(int32_t address);
  uint32_t reqestPeriod() { return _reqestPeriod };

  void saveLongByIndex(int32_t value, int32_t startAddressIndex);
  void saveUnsignedLongByIndex(uint32_t value, int32_t startAddressIndex);
  void saveFloatByIndex(float value, int32_t startAddressIndex);
  void saveIntegerByIndex(int16_t value, int32_t startAddressIndex);
  void saveByteByIndex(uint8_t value, int32_t startAddressIndex);
  void saveBoolByIndex(bool value, int32_t startAddressIndex);

  uint8_t readByteByIndex(int32_t startAddressIndex);
  int16_t readIntegerByIndex(int32_t startAddressIndex);
  float readFloatByIndex(int32_t startAddressIndex);
  int32_t readLongByIndex(int32_t startAddressIndex);
  uint32_t readUnsignedLongByIndex(int32_t startAddressIndex);
  bool readBoolByIndex(int32_t startAddressIndex);

  void setCallBack(FLProgDwinNewDataCallback func) { _newDataCallback = func; };

protected:
  void setDataByIndex(int32_t addressIndex, uint8_t value);
  uint8_t getDataByIndex(int32_t addressIndex);

  uint32_t _reqestPeriod = 1000;
  int32_t _dataSize = 0;
  uint32_t _lastReqestTime;
  uint8_t _index = 0;
  uint8_t *_values = 0;
  int32_t *_adreses = 0;
  bool *_isNeedSend = 0;
  bool *_canWrite = 0;
  bool *_canRead = 0;

  FLProgDwinNewDataCallback _newDataCallback = 0;
};
