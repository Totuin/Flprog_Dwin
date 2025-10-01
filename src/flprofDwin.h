#pragma once
#include <Arduino.h>
#include "flprogUtilites.h"

typedef void (*FLProgDwinNewDataCallback)(uint8_group, int32_t index, int8_t value);

class FLProgDwinDataTable
{
public:
  FLProgDwinDataTable() {};
  void setTableSize(uint32_t dataSize);
  void setAddress( uint32_t addressIndex, int32_t address);

protected:
  uint32_t _reqestPeriod = 1000;
  uint32_t _dataSize = 0;
  uint32_t _lastReqestTime;
  uint8_t *_values = 0;
  int32_t *_adreses = 0;
  bool *_isNeedSend = 0;
  bool *_canWrite = 0;
  bool *_canRead = 0;

  FLProgDwinNewDataCallback _newDataCallback = 0;
};

class FLProgDwin
{
public:
  FLProgDwin(uint8_t croupsSize, FlprogAbstractUartExecutor *executor);
  void setTableSize(uint8_t groupIndex, uint32_t dataSize);
  void setAddress(uint8_t groupIndex, uint32_t addressIndex, int32_t address);
  void setAddress(uint8_t groupIndex, uint32_t addressIndex, int32_t address);

protected:
  FlprogAbstractUartExecutor *_executor = 0;
  FLProgDwinDataTable *_tables = 0;
  uint8_t _croupsSize = 0;
  uint8_t *_values = 0;
};