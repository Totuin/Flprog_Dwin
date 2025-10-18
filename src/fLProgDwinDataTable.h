#pragma once
#include <Arduino.h>
#include "flprogUtilites.h"
#include "flprogModbusUtilites.h"

#define FLPROG_DWIN_READY 0
#define FLPROG_DWIN_WAITING_SENDING 1
#define FLPROG_DWIN_WAITING_ANSWER 2
#define FLPROG_DWIN_SP_TABLE 0
#define FLPROG_DWIN_VP_TABLE 1

typedef void (*FLProgDwinNewDataCallback)(uint8_t index, int32_t addressIndex, int8_t value);

class FLProgDwinDataTable
{
public:
  FLProgDwinDataTable() {};

  void index(uint8_t index) { _index = index; };
  uint8_t index() { return _index; };
  void setTableSize(int32_t dataSize);
  int32_t getTableSize() { return _dataSize; };
  void setAddress(int32_t addressIndex, int32_t address);
  void setReqestPeriod(uint32_t period) { _reqestPeriod = period; };

  int32_t address(int32_t addressIndex);
  int32_t indexForAddres(int32_t address);
  uint32_t reqestPeriod() { return _reqestPeriod; };

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

  bool hasWriteRegisters();
  int32_t firstWriteAddress();

  void setDataByIndex(int32_t addressIndex, uint16_t value);
  void writeDataByIndex(int32_t addressIndex, uint16_t value);
  uint16_t getDataByIndex(int32_t addressIndex);
  void resetIsNeedWriteIndex(int32_t addressIndex);

  int32_t minAddres();
  int32_t maxAddres();
  bool isReady();

  void lastReqestTime(uint32_t time) { _lastReqestTime = time; };
  uint8_t readRegSize(int32_t address, uint8_t result);
  int32_t firstReadAddress();
  int32_t findNextReadAddres(int32_t address);

  void setType(uint8_t type) { _type = type; };
  uint8_t getType() { return _type; };

protected:
  bool needWriteAddressForIndex(int32_t addressIndex);
  bool hasCanReadAddresses();

  uint32_t _reqestPeriod = 1000;
  int32_t _dataSize = 0;
  uint32_t _lastReqestTime;
  uint8_t _index = 0;
  uint16_t *_values = 0;
  int32_t *_adreses = 0;
  bool *_isNeedSend = 0;
  bool *_canWrite = 0;
  bool *_canRead = 0;

  int32_t _minAddres = -1;
  int32_t _maxAddres = -1;

  uint8_t _type = FLPROG_DWIN_VP_TABLE;

  FLProgDwinNewDataCallback _newDataCallback = 0;
};
