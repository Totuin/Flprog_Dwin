#include "fLProgDwinDataTable.h"

void FLProgDwinDataTable::setTableSize(int32_t dataSize)
{
  _dataSize = dataSize;
  _adreses = new int32_t[_dataSize];
  _values = new uint8_t[_dataSize];
  _isNeedSend = new bool[_dataSize];
  _canWrite = new bool[_dataSize];
  _canRead = new bool[_dataSize];

  for (int32_t i = 0; i < _dataSize; i++)
  {
    _adreses[i] = -1;
    _values[i] = 0;
    _isNeedSend[i] = false;
    _canWrite[i] = false;
    _canRead[i] = false;
  }
  _lastReqestTime = flprog::timeBack(_reqestPeriod);
}

void FLProgDwinDataTable::setAddress(int32_t addressIndex, int32_t address)
{
  if (addressIndex >= _dataSize)
  {
    return;
  }
  _adreses[addressIndex] = address;
  _canWrite[addressIndex] = true;
  _canRead[addressIndex] = true;
}

int32_t FLProgDwinDataTable::address(int32_t addressIndex)
{
  if (addressIndex >= _dataSize)
  {
    return -1;
  }
  return _adreses[addressIndex];
}

int32_t FLProgDwinDataTable::indexForAddres(int32_t address)
{
  if (address < 0)
  {
    return -1;
  }
  for (int32_t i = 0; i < _dataSize; i++)
  {
    if (_adreses[i] = address)
    {
      return i;
    }
  }
  return -1;
}

void FLProgDwinDataTable::setDataByIndex(int32_t addressIndex, uint8_t value)
{
  if (addressIndex < 0)
  {
    return;
  }

  if (addressIndex >= _dataSize)
  {
    return;
  }
  if (_values[addressIndex] == value)
  {
    return;
  }
  _values[addressIndex] = value;
  _isNeedSend[addressIndex] = true;
  if (_newDataCallback != 0)
  {
    _newDataCallback(_index, addressIndex, value);
  }
}

void FLProgDwinDataTable::saveLongByIndex(int32_t value, int32_t startAddressIndex)
{
  unsigned char sourse[4];
  memcpy(sourse, &value, 4);
  setDataByIndex(startAddressIndex, sourse[0]);
  setDataByIndex((startAddressIndex + 1), sourse[1]);
  setDataByIndex((startAddressIndex + 2), sourse[2]);
  setDataByIndex((startAddressIndex + 3), sourse[3]);
}

void FLProgDwinDataTable::saveUnsignedLongByIndex(uint32_t value, int32_t startAddressIndex)
{
  unsigned char sourse[4];
  memcpy(sourse, &value, 4);
  setDataByIndex(startAddressIndex, sourse[0]);
  setDataByIndex((startAddressIndex + 1), sourse[1]);
  setDataByIndex((startAddressIndex + 2), sourse[2]);
  setDataByIndex((startAddressIndex + 3), sourse[3]);
}

void FLProgDwinDataTable::saveFloatByIndex(float value, int32_t startAddressIndex)
{
  unsigned char sourse[4];
  memcpy(sourse, &value, 4);
  setDataByIndex(startAddressIndex, sourse[0]);
  setDataByIndex((startAddressIndex + 1), sourse[1]);
  setDataByIndex((startAddressIndex + 2), sourse[2]);
  setDataByIndex((startAddressIndex + 3), sourse[3]);
}

void FLProgDwinDataTable::saveIntegerByIndex(int16_t value, int32_t startAddressIndex)
{
  setDataByIndex(startAddressIndex, lowByte(value));
  setDataByIndex((startAddressIndex + 1), highByte(value));
}

void FLProgDwinDataTable::saveByteByIndex(uint8_t value, int32_t startAddressIndex)
{
  setDataByIndex(startAddressIndex, value);
}

void FLProgDwinDataTable::saveBoolByIndex(bool value, int32_t startAddressIndex)
{
  if (value)
  {
    setDataByIndex(startAddressIndex, 1);
    return;
  }
  setDataByIndex(startAddressIndex, 0);
}

uint8_t FLProgDwinDataTable::getDataByIndex(int32_t addressIndex)
{
  if (addressIndex < 0)
  {
    return 0;
  }

  if (addressIndex >= _dataSize)
  {
    return 0;
  }
  return _values[addressIndex];
}

uint8_t FLProgDwinDataTable::readByteByIndex(int32_t startAddressIndex)
{
  return getDataByIndex(startAddressIndex);
}

int16_t FLProgDwinDataTable::readIntegerByIndex(int32_t startAddressIndex)
{
  return (int16_t(word(lowByte(getDataByIndex(startAddressIndex)), highByte(getDataByIndex(startAddressIndex + 1)))));
}

float FLProgDwinDataTable::readFloatByIndex(int32_t startAddressIndex)
{
  float result;
  unsigned char sourse[4];
  sourse[0] = getDataByIndex(startAddressIndex);
  sourse[1] = getDataByIndex(startAddressIndex + 1);
  sourse[2] = getDataByIndex(startAddressIndex + 2);
  sourse[3] = getDataByIndex(startAddressIndex + 3);
  memcpy(&result, sourse, 4);
  return result;
}

int32_t FLProgDwinDataTable::readLongByIndex(int32_t startAddressIndex)
{
  int32_t result;
  unsigned char sourse[4];
  sourse[0] = getDataByIndex(startAddressIndex);
  sourse[1] = getDataByIndex(startAddressIndex + 1);
  sourse[2] = getDataByIndex(startAddressIndex + 2);
  sourse[3] = getDataByIndex(startAddressIndex + 3);
  memcpy(&result, sourse, 4);
  return result;
}

uint32_t FLProgDwinDataTable::readUnsignedLongByIndex(int32_t startAddressIndex)
{
  uint32_t result;
  unsigned char sourse[4];
  sourse[0] = getDataByIndex(startAddressIndex);
  sourse[1] = getDataByIndex(startAddressIndex + 1);
  sourse[2] = getDataByIndex(startAddressIndex + 2);
  sourse[3] = getDataByIndex(startAddressIndex + 3);
  memcpy(&result, sourse, 4);
  return result;
}

bool FLProgDwinDataTable::readBoolByIndex(int32_t startAddressIndex)
{
  if (getDataByIndex(startAddressIndex) > 0)
  {
    return true;
  }
  return false;
}

