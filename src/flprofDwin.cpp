#include "flprofDwin.h"

FLProgDwin::FLProgDwin(uint8_t uirtPort, uint8_t croupsSize, FlprogAbstractUartExecutor *executor)
{
  _executor = executor;
  _uartPortNumber = uirtPort;
  _croupsSize = croupsSize;
  _tables = new FLProgDwinDataTable[croupsSize];
  for (uint8_t i = 0; i < _croupsSize; i++)
  {
    _tables->index(i);
  }
  _status = FLPROG_DWIN_READY;
}

void FLProgDwin::setTableSize(uint8_t groupIndex, int32_t dataSize)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex].setTableSize(dataSize);
}

void FLProgDwin::setAddress(uint8_t groupIndex, int32_t addressIndex, int32_t address)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex].setAddress(addressIndex, address);
}

void FLProgDwin::setReqestPeriod(uint8_t groupIndex, uint32_t period)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex].setReqestPeriod(period);
}

uint32_t FLProgDwin::address(uint8_t groupIndex, int32_t addressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return -1;
  }
  return _tables[groupIndex].address(addressIndex);
}

int32_t FLProgDwin::indexForAddres(uint8_t groupIndex, int32_t address)
{
  if (groupIndex >= _croupsSize)
  {
    return -1;
  }
  return _tables[groupIndex].indexForAddres(address);
}

uint32_t FLProgDwin::reqestPeriod(uint8_t groupIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return 0;
  }
  return _tables[groupIndex].reqestPeriod();
}

void FLProgDwin::setType(uint8_t groupIndex, uint8_t type)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  return _tables[groupIndex].setType(type);
}

uint8_t FLProgDwin::getType(uint8_t groupIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return FLPROG_DWIN_VP_TABLE;
  }
  return _tables[groupIndex].getType();
}

void FLProgDwin::saveLongByIndex(uint8_t groupIndex, int32_t value, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex].saveLongByIndex(value, startAddressIndex);
}

void FLProgDwin::saveUnsignedLongByIndex(uint8_t groupIndex, uint32_t value, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex].saveUnsignedLongByIndex(value, startAddressIndex);
}

void FLProgDwin::saveFloatByIndex(uint8_t groupIndex, float value, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex].saveFloatByIndex(value, startAddressIndex);
}

void FLProgDwin::saveIntegerByIndex(uint8_t groupIndex, int16_t value, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex].saveIntegerByIndex(value, startAddressIndex);
}

void FLProgDwin::saveByteByIndex(uint8_t groupIndex, uint8_t value, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex].saveByteByIndex(value, startAddressIndex);
}

void FLProgDwin::saveBoolByIndex(uint8_t groupIndex, bool value, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex].saveBoolByIndex(value, startAddressIndex);
}

uint8_t FLProgDwin::readByteByIndex(uint8_t groupIndex, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return 0;
  }
  return _tables[groupIndex].readByteByIndex(startAddressIndex);
}

int16_t FLProgDwin::readIntegerByIndex(uint8_t groupIndex, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return 0;
  }
  return _tables[groupIndex].readIntegerByIndex(startAddressIndex);
}

float FLProgDwin::readFloatByIndex(uint8_t groupIndex, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return 0;
  }
  return _tables[groupIndex].readFloatByIndex(startAddressIndex);
}

int32_t FLProgDwin::readLongByIndex(uint8_t groupIndex, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return 0;
  }
  return _tables[groupIndex].readLongByIndex(startAddressIndex);
}

uint32_t FLProgDwin::readUnsignedLongByIndex(uint8_t groupIndex, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return 0;
  }
  return _tables[groupIndex].readUnsignedLongByIndex(startAddressIndex);
}

bool FLProgDwin::readBoolByIndex(uint8_t groupIndex, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return false;
  }
  return _tables[groupIndex].readBoolByIndex(startAddressIndex);
}

void FLProgDwin::pool()
{
  if (!_enable)
  {
    return;
  }
  if (_eventsCount < _skippingEvents)
  {
    _eventsCount++;
    return;
  }
  _eventsCount = 0;
  if (_isPause)
  {
    return;
  }
  if (_executor == 0)
  {
    return;
  }
  setFlags();
  /*
  if (_status == FLPROG_DWIN_WAITING_SENDING)
  {
    if (flprog::isTimer(_startSendTime, _timeOfSend))
    {
      _status = FLPROG_DWIN_WAITING_ANSWER;
      _startSendTime = millis();
    }
    else
    {
      return;
    }
  }*/
  if (_status == FLPROG_DWIN_WAITING_ANSWER)
  {
    checkAnswer();
  }
  if (_status == FLPROG_DWIN_READY)
  {
    nextQuery();
  }
}

void FLProgDwin::nextQuery()
{
  if (!createNewTelegramm())
  {
    return;
  }
  sendQuery();
}

bool FLProgDwin::createNewTelegramm()
{
  if (hasWriteRegisters())
  {
    return createWriteTelegramm();
  }
  if (!nextStep())
  {
    return false;
  }
  return createReadTelegram();
}

bool FLProgDwin::hasWriteRegisters()
{
  return !(firstWriteTable() == 0);
}

FLProgDwinDataTable *FLProgDwin::firstWriteTable()
{
  for (int8_t i = 0; i < _croupsSize; i++)
  {
    if (_tables[i].hasWriteRegisters())
    {
      return &_tables[i];
    }
  }
  return 0;
}

bool FLProgDwin::createWriteTelegramm()
{
  FLProgDwinDataTable *table = firstWriteTable();
  int16_t startAddress = table->firstWriteAddress();
  int32_t addrIndex = table->indexForAddres(startAddress);
  uint16_t value = table->getDataByIndex(addrIndex);
  table->resetIsNeedWriteIndex(addrIndex);
  _bufferSize = 8;
  _buffer[0] = 0x5A;
  _buffer[1] = 0xA5;
  if (_isUseCRC)
  {
    _buffer[2] = 7;
  }
  else
  {
    _buffer[2] = 5;
  }
  _buffer[3] = 0x82;
  _buffer[4] = highByte(startAddress);
  _buffer[5] = lowByte(startAddress);
  _buffer[6] = highByte(value);
  _buffer[7] = lowByte(value);
  if (_isUseCRC)
  {
    uint16_t crc = flprogModus::modbusCalcCRC(_bufferSize, _buffer, 3);
    _buffer[_bufferSize] = lowByte(crc);
    _bufferSize++;
    _buffer[_bufferSize] = highByte(crc);
    _bufferSize++;
  }
  return true;
}

void FLProgDwin::sendQuery()
{
  while (_executor->availableUart(_uartPortNumber))
  {
    _executor->readUart(_uartPortNumber);
  }
  Serial4.print("Dwin Send: ");
  for (uint8_t i = 0; i < _bufferSize; i++)
  {
    Serial4.print(_buffer[i], HEX);
    Serial4.print("-");
  }
  Serial4.println();
  _executor->writeUart(_buffer, _bufferSize, _uartPortNumber);
  _startSendTime = millis();
  _status = FLPROG_DWIN_WAITING_ANSWER;
  _bufferSize = 0;
}

void FLProgDwin::checkAnswer()
{
  if (flprog::isTimer(_startSendTime, _timeOutTime))
  {
    _errorCode = 244;
    _status = FLPROG_DWIN_READY;
    _bufferSize = 0;
    return;
  }
  while (_executor->availableUart(_uartPortNumber))
  {
    if (_bufferSize < FLPROG_MODBUS_BUFER_SIZE)
    {
      _buffer[_bufferSize] = _executor->readUart(_uartPortNumber);
      _bufferSize++;
      if (_bufferSize == pacadgeSize())
      {
        checkAnswerData();
        _errorCode = 0;
        return;
      }
    }
  }
}

uint16_t FLProgDwin::pacadgeSize()
{
  if (_bufferSize < 4)
  {
    return 0;
  }
  if (_buffer[3] == 0x82)
  {
    return 6;
  }
  return _buffer[2] + 3;
}

void FLProgDwin::checkAnswerData()
{
  if (_buffer[3] == 0x82)
  {
    _status = FLPROG_DWIN_READY;
    _bufferSize = 0;
    return;
  }
  if (_buffer[3] == 0x83)
  {
    if (_bufferSize < 7)
    {
      _status = FLPROG_DWIN_READY;
      _bufferSize = 0;
      return;
    }
    if (_currentTable == 0)
    {
      _status = FLPROG_DWIN_READY;
      _bufferSize = 0;
      return;
    }
    Serial4.print("Dwin Read: ");
    for (uint8_t i = 0; i < _bufferSize; i++)
    {
      Serial4.print(_buffer[i], HEX);
      Serial4.print("-");
    }
    Serial4.println();

    int32_t startAddress = (int32_t)word(_buffer[4], _buffer[5]);
    int32_t addressIndex;
    uint8_t currentByte = 7;
    uint16_t currentValue;
    for (uint8_t i = 0; i < _buffer[6]; i++)
    {
      if (currentByte >= _bufferSize)
      {
        _status = FLPROG_DWIN_READY;
        _bufferSize = 0;
        return;
      }
      currentValue = word(_buffer[currentByte], _buffer[currentByte + 1]);
      addressIndex = _currentTable->indexForAddres(startAddress);
      _currentTable->writeDataByIndex(addressIndex, currentValue);
      startAddress++;
      currentByte = currentByte + 2;
    }
  }
  _status = FLPROG_DWIN_READY;
  _bufferSize = 0;
  return;
}

void FLProgDwin::setCallBack(FLProgDwinNewDataCallback func)
{
  for (int8_t i = 0; i < _croupsSize; i++)
  {
    _tables[i].setCallBack(func);
  }
}

bool FLProgDwin::hasReadySlave()
{
  for (int8_t i = 0; i < _croupsSize; i++)
  {
    if (_tables[i].isReady())
    {
      return true;
    }
  }
  return false;
}

FLProgDwinDataTable *FLProgDwin::firstReadTable()
{
  for (int8_t i = 0; i < _croupsSize; i++)
  {
    if (_tables[i].isReady())
    {
      return &_tables[i];
    }
  }
  return 0;
}

bool FLProgDwin::nextStep()
{
  if (!hasReadySlave())
  {
    return false;
  }
  if (_currentTable == 0)
  {
    _currentAddres = -1;
    _currentTable = firstReadTable();
    if (_currentTable == 0)
    {
      return false;
    }
    _currentAddres = _currentTable->firstReadAddress();
    if (_currentAddres < 0)
    {
      return false;
    }
    return true;
  }
  return nextAddress();
}

bool FLProgDwin::nextAddress()
{
  if (_currentTable == 0)
  {
    _currentAddres = -1;
    return false;
  }
  _currentAddres = _currentTable->findNextReadAddres(_currentAddres);
  if (_currentAddres < 0)
  {
    return nextTable();
  }
  return true;
}

FLProgDwinDataTable *FLProgDwin::nextTable(FLProgDwinDataTable *table)
{
  bool isFindTable = false;
  for (int8_t i = 0; i < _croupsSize; i++)
  {
    if (isFindTable)
    {
      if (_tables[i].isReady())
      {
        return &_tables[i];
      }
    }
    else
    {
      if (table == &_tables[i])
      {
        isFindTable = true;
      }
    }
  }
  return 0;
}

bool FLProgDwin::nextTable()
{
  if (_currentTable == 0)
  {
    _currentAddres = -1;
    return false;
  }
  _currentTable->lastReqestTime(millis());
  _currentTable = nextTable(_currentTable);
  if (_currentTable == 0)
  {
    _currentAddres = -1;
    return false;
  }
  _currentAddres = _currentTable->firstReadAddress();
  if (_currentAddres < 0)
  {
    return nextTable();
  }
  return true;
}

bool FLProgDwin::createReadTelegram()
{
  if (_currentTable == 0)
  {
    _currentAddres = -1;
    return false;
  }
  if (_currentAddres < 0)
  {
    return false;
  }
  uint8_t regSize = _currentTable->readRegSize(_currentAddres, 1);
  _bufferSize = 7;
  _buffer[0] = 0x5A;
  _buffer[1] = 0xA5;
  if (_isUseCRC)
  {
    _buffer[2] = 6;
  }
  else
  {
    _buffer[2] = 4;
  }
  _buffer[3] = 0x83;
  _buffer[4] = highByte(_currentAddres);
  _buffer[5] = lowByte(_currentAddres);
  _buffer[6] = regSize;
  _currentAddres = _currentAddres + regSize;
  if (_isUseCRC)
  {
    uint16_t crc = flprogModus::modbusCalcCRC(_bufferSize, _buffer, 3);
    _buffer[_bufferSize] = lowByte(crc);
    _bufferSize++;
    _buffer[_bufferSize] = highByte(crc);
    _bufferSize++;
  }
  return true;
}