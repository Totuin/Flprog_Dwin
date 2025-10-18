#pragma once
#include <Arduino.h>
#include "flprogUtilites.h"
#include "fLProgDwinDataTable.h"

class FLProgDwin : public AbstractFLProgClass
{
public:
  FLProgDwin(uint8_t uirtPort, uint8_t croupsSize, FlprogAbstractUartExecutor *executor);

  void setTableSize(uint8_t groupIndex, int32_t dataSize);
  void setAddress(uint8_t groupIndex, int32_t addressIndex, int32_t address);
  void setReqestPeriod(uint8_t groupIndex, uint32_t period);

  uint32_t address(uint8_t groupIndex, int32_t addressIndex);
  int32_t indexForAddres(uint8_t groupIndex, int32_t address);
  uint32_t reqestPeriod(uint8_t groupIndex);

  void setType(uint8_t groupIndex, uint8_t type);
  uint8_t getType(uint8_t groupIndex);

  void pool();

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

  void setCallBack(FLProgDwinNewDataCallback func);

  uint16_t getSkippingEvents() { return _skippingEvents; };
  void setSkippingEvents(uint16_t value) { _skippingEvents = value; };
  void isPause(bool value) { _isPause = value; };
  bool isPause() { return _isPause; };
  void setEnable(bool enable) { _enable = enable; };
  bool getEnable() { return _enable; };

  void setUart(uint8_t uartPort) { _uartPortNumber = uartPort; };
  void setSpeedUart(uint32_t speed) { _executor->setSpeedUart(speed, _uartPortNumber); };
  void setDataBitUart(uint8_t value) { _executor->setDataBitUart(value, _uartPortNumber); };
  void setStopBitUart(uint8_t value) { _executor->setStopBitUart(value, _uartPortNumber); };
  void setParityUart(uint8_t value) { _executor->setParityUart(value, _uartPortNumber); };
  void setPinRxUart(uint8_t pin) { _executor->setPinRxUart(pin, _uartPortNumber); };
  void setPinTxUart(uint8_t pin) { _executor->setPinTxUart(pin, _uartPortNumber); };
  void setPort(uint8_t value) { _uartPortNumber = value; };
  uint8_t getPort() { return _uartPortNumber; };

  void setTimeOutTime(uint32_t time) { _timeOutTime = time; };
  uint32_t getTimeOutTime() { return _timeOutTime; };
  void setUseCRC(bool value) { _isUseCRC = value; };
  bool getUseCRC() { return _isUseCRC; };

protected:
  void
  nextQuery();
  void checkAnswer();
  uint16_t pacadgeSize();
  void checkAnswerData();
  bool nextStep();
  bool hasReadySlave();
  bool hasWriteRegisters();
  bool createNewTelegramm();
  bool createWriteTelegramm();
  bool createReadTelegram();
  void sendQuery();
  bool nextAddress();
  bool nextTable();
  FLProgDwinDataTable *firstReadTable();
  FLProgDwinDataTable *nextTable(FLProgDwinDataTable *_table);
  FLProgDwinDataTable *firstWriteTable();

  FlprogAbstractUartExecutor *_executor = 0;
  FLProgDwinDataTable *_tables = 0;
  uint8_t _croupsSize = 0;

  uint16_t _skippingEvents = 0;
  uint16_t _eventsCount = 0;
  bool _enable = true;
  bool _isPause = false;
  uint32_t _startSendTime;
  uint32_t _timeOfSend;
  uint32_t _timeOutTime = 1000;

  uint8_t _uartPortNumber = 0;

  uint8_t _bufferSize = 0;
  uint8_t _buffer[FLPROG_MODBUS_BUFER_SIZE];

  bool _isUseCRC = false;

  FLProgDwinDataTable *_currentTable = 0;
  int32_t _currentAddres = -1;
};