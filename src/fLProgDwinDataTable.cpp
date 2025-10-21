#include "fLProgDwinDataTable.h"

void FLProgDwinDataTable::setTableSize(int32_t dataSize)
{
  _dataSize = dataSize;
  _adreses = new int32_t[_dataSize];
  _values = new uint16_t[_dataSize];
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
  if (address > 0xFFFF)
  {
    _adreses[addressIndex] = -1;
  }
  else
  {
    _adreses[addressIndex] = address;
  }
  _canWrite[addressIndex] = true;
  _canRead[addressIndex] = true;
  _minAddres = -1;
  _maxAddres = -1;
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
    if (_adreses[i] == address)
    {
      return i;
    }
  }
  return -1;
}

void FLProgDwinDataTable::setDataByIndex(int32_t addressIndex, uint16_t value)
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

void FLProgDwinDataTable::writeDataByIndex(int32_t addressIndex, uint16_t value)
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
  if (_newDataCallback != 0)
  {
    _newDataCallback(_index, addressIndex, value);
  }
}

void FLProgDwinDataTable::saveLongByIndex(int32_t value, int32_t startAddressIndex)
{
  uint8_t sourse[4];
  memcpy(sourse, &value, 4);
  setDataByIndex(startAddressIndex, ((int16_t)(word(sourse[3], sourse[2]))));
  setDataByIndex((startAddressIndex + 1), ((int16_t)(word(sourse[1], sourse[0]))));
}

void FLProgDwinDataTable::saveUnsignedLongByIndex(uint32_t value, int32_t startAddressIndex)
{
  uint8_t sourse[4];
  memcpy(sourse, &value, 4);
  setDataByIndex(startAddressIndex, ((int16_t)(word(sourse[3], sourse[2]))));
  setDataByIndex((startAddressIndex + 1), ((int16_t)(word(sourse[1], sourse[0]))));
}

void FLProgDwinDataTable::saveFloatByIndex(float value, int32_t startAddressIndex)
{
  uint8_t sourse[4];
  memcpy(sourse, &value, 4);
  setDataByIndex(startAddressIndex, ((int16_t)(word(sourse[3], sourse[2]))));
  setDataByIndex((startAddressIndex + 1), ((int16_t)(word(sourse[1], sourse[0]))));
}

void FLProgDwinDataTable::saveIntegerByIndex(int16_t value, int32_t startAddressIndex)
{
  setDataByIndex(startAddressIndex, value);
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

uint16_t FLProgDwinDataTable::getDataByIndex(int32_t addressIndex)
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
  return getDataByIndex(startAddressIndex);
}

float FLProgDwinDataTable::readFloatByIndex(int32_t startAddressIndex)
{
  float result;
  uint8_t sourse[4];
  uint16_t temp = getDataByIndex(startAddressIndex);
  sourse[2] = lowByte(temp);
  sourse[3] = highByte(temp);
  temp = getDataByIndex(startAddressIndex + 1);
  sourse[0] = lowByte(temp);
  sourse[1] = highByte(temp);
  memcpy(&result, sourse, 4);
  return result;
}

int32_t FLProgDwinDataTable::readLongByIndex(int32_t startAddressIndex)
{
  int32_t result;
  uint8_t sourse[4];
  uint16_t temp = getDataByIndex(startAddressIndex);
  sourse[2] = lowByte(temp);
  sourse[3] = highByte(temp);
  temp = getDataByIndex(startAddressIndex + 1);
  sourse[0] = lowByte(temp);
  sourse[1] = highByte(temp);
  memcpy(&result, sourse, 4);
  return result;
}

uint32_t FLProgDwinDataTable::readUnsignedLongByIndex(int32_t startAddressIndex)
{
  uint32_t result;
  uint8_t sourse[4];
  uint16_t temp = getDataByIndex(startAddressIndex);
  sourse[2] = lowByte(temp);
  sourse[3] = highByte(temp);
  temp = getDataByIndex(startAddressIndex + 1);
  sourse[0] = lowByte(temp);
  sourse[1] = highByte(temp);
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

bool FLProgDwinDataTable::hasWriteRegisters()
{
  if (!_enable)
  {
    return false;
  }
  return firstWriteAddress() > 0x0FFF;
}

int32_t FLProgDwinDataTable::firstWriteAddress()
{
  if (!_enable)
  {
    return -1;
  }
  for (int32_t i = 0; i < _dataSize; i++)
  {
    if (needWriteAddressForIndex(i))
    {
      return _adreses[i];
    }
  }
  return -1;
}

bool FLProgDwinDataTable::needWriteAddressForIndex(int32_t addressIndex)
{
  if (addressIndex < 0)
  {
    return false;
  }
  if (addressIndex >= _dataSize)
  {
    return false;
  }
  if (_adreses[addressIndex] < 0x1000)
  {
    return false;
  }
  if (!_canWrite[addressIndex])
  {
    return false;
  }
  return _isNeedSend[addressIndex];
}

void FLProgDwinDataTable::resetIsNeedWriteIndex(int32_t addressIndex)
{
  if (addressIndex < 0)
  {
    return;
  }
  if (addressIndex >= _dataSize)
  {
    return;
  }
  _isNeedSend[addressIndex] = false;
}

int32_t FLProgDwinDataTable::minAddres()
{
  if (_minAddres >= 0)
  {
    return _minAddres;
  }
  _minAddres = 1000000;
  for (int32_t i = 0; i < _dataSize; i++)
  {
    if (_adreses[i] < _minAddres)
    {
      _minAddres = _adreses[i];
    }
  }
  if (_minAddres == 1000000)
  {
    _minAddres = -1;
  }
  return _minAddres;
}

int32_t FLProgDwinDataTable::maxAddres()
{
  if (_maxAddres >= 0)
  {
    return _maxAddres;
  }
  for (int32_t i = 0; i < _dataSize; i++)
  {
    if (_adreses[i] > _maxAddres)
    {
      _maxAddres = _adreses[i];
    }
  }
  return _maxAddres;
}

bool FLProgDwinDataTable::isReady()
{
  if (!_enable)
  {
    return false;
  }
  if (!hasCanReadAddresses())
  {
    return false;
  }
  if (flprog::isTimer(_lastReqestTime, _reqestPeriod))
  {
    return true;
  }
  return false;
}

bool FLProgDwinDataTable::hasCanReadAddresses()
{
  for (int32_t i = 0; i < _dataSize; i++)
  {
    if (_canRead[i])
    {
      return true;
    }
  }
  return false;
}

int32_t FLProgDwinDataTable::firstReadAddress()
{
  if (!_enable)
  {
    return -1;
  }
  int32_t address = minAddres();
  int32_t newIndex = indexForAddres(address);
  if (newIndex < 0)
  {
    return findNextReadAddres(address);
  }
  if (_canRead[newIndex])
  {
    return address;
  }
  return findNextReadAddres(address);
}

int32_t FLProgDwinDataTable::findNextReadAddres(int32_t address)
{
  if (!_enable)
  {
    return -1;
  }
  int32_t newAddress = address + 1;
  if (newAddress > maxAddres())
  {
    return -1;
  }
  int32_t newIndex = indexForAddres(newAddress);
  if (newIndex < 0)
  {
    return findNextReadAddres(newAddress);
  }
  if (_canRead[newIndex])
  {
    return newAddress;
  }
  return findNextReadAddres(newAddress);
}

uint8_t FLProgDwinDataTable::readRegSize(int32_t address, uint8_t result)
{
  if (result >= (FLPROG_MODBUS_BUFER_SIZE - 6))
  {
    return result;
  }
  int32_t newAddress = address + 1;
  int32_t newIndex = indexForAddres(newAddress);
  if (newIndex < 0)
  {
    return result;
  }
  if (!_canRead[newIndex])
  {
    return result;
  }
  return readRegSize(newAddress, (result + 1));
}
