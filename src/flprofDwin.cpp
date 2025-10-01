#include "flprofDwin.h"

FLProgDwin::FLProgDwin(uint8_t croupsSize, FlprogAbstractUartExecutor *executor)
{
  _executor = executor;
  _croupsSize = croupsSize;
  _tables = new FLProgDwinDataTable[croupsSize];
  for (uint8_t i = 0; i < _croupsSize; i++)
  {
    _tables->index(i);
  }
}

void FLProgDwin::setTableSize(uint8_t groupIndex, int32_t dataSize)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex]->setTableSize(dataSize);
}

void FLProgDwin::setAddress(uint8_t groupIndex, int32_t addressIndex, int32_t address)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex]->setAddress(addressIndex, address);
}

void FLProgDwin::setReqestPeriod(uint8_t groupIndex, uint32_t period)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex]->setReqestPeriod(groupIndex, period);
}

uint32_t FLProgDwin::address(uint8_t groupIndex, int32_t addressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return -1;
  }
  return _tables[groupIndex]->address(addressIndex);
}

int32_t FLProgDwin::indexForAddres(uint8_t groupIndex, int32_t address)
{
  if (groupIndex >= _croupsSize)
  {
    return -1;
  }
  return _tables[groupIndex]->indexForAddres(address);
}

uint32_t FLProgDwin::reqestPeriod(uint8_t groupIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex]->reqestPeriod();
}

void FLProgDwin::saveLongByIndex(uint8_t groupIndex, int32_t value, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex]->saveLongByIndex(value, startAddressIndex);
}

void FLProgDwin::saveUnsignedLongByIndex(uint8_t groupIndex, uint32_t value, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex]->saveUnsignedLongByIndex(value, startAddressIndex);
}

void FLProgDwin::saveFloatByIndex(uint8_t groupIndex, float value, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex]->saveFloatByIndex(value, startAddressIndex);
}

void FLProgDwin::saveIntegerByIndex(uint8_t groupIndex, int16_t value, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex]->saveIntegerByIndex(value, startAddressIndex);
}

void FLProgDwin::saveByteByIndex(uint8_t groupIndex, uint8_t value, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex]->saveByteByIndex(value, startAddressIndex);
}

void FLProgDwin::saveBoolByIndex(uint8_t groupIndex, bool value, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex]->saveBoolByIndex(value, startAddressIndex);
}

uint8_t FLProgDwin::readByteByIndex(uint8_t groupIndex, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return 0;
  }
  return _tables[groupIndex]->readByteByIndex(startAddressIndex);
}

int16_t FLProgDwin::readIntegerByIndex(uint8_t groupIndex, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return 0;
  }
  return _tables[groupIndex]->readIntegerByIndex(startAddressIndex);
}

float FLProgDwin::readFloatByIndex(uint8_t groupIndex, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return 0;
  }
  return _tables[groupIndex]->readFloatByIndex(startAddressIndex);
}

int32_t FLProgDwin::readLongByIndex(uint8_t groupIndex, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return 0;
  }
  return _tables[groupIndex]->readLongByIndex(startAddressIndex);
}

uint32_t FLProgDwin::readUnsignedLongByIndex(uint8_t groupIndex, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return 0;
  }
  return _tables[groupIndex]->readUnsignedLongByIndex(startAddressIndex);
}

bool FLProgDwin::readBoolByIndex(uint8_t groupIndex, int32_t startAddressIndex)
{
  if (groupIndex >= _croupsSize)
  {
    return false;
  }
  return _tables[groupIndex]->readBoolByIndex(startAddressIndex);
}