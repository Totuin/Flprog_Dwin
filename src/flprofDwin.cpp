#include "flprofDwin.h"

//----------------------------------------FLProgDwinDataTable----------------------------------------

void FLProgDwinDataTable::setTableSize(uint32_t dataSize)
{
  _dataSize = dataSize;
  _adreses = new int32_t[_dataSize];
  _values = new uint8_t[_dataSize];
  _isNeedSend = new bool[_dataSize];
  _canWrite = new bool[_dataSize];
  _canRead = new bool[_dataSize];

  for (uint32_t i = 0; i < _dataSize; i++)
  {
    _adreses[i] = -1;
    _values[i] = 0;
    _isNeedSend[i] = false;
    _canWrite[i] = false;
    _canRead[i] = false;
  }
  _lastReqestTime = flprog::timeBack(_reqestPeriod);
}

void FLProgDwinDataTable::setAddress(uint32_t addressIndex, int32_t address)
{
  if (addressIndex >= _dataSize)
  {
    return;
  }
  _adreses[addressIndex] = address;
  _canWrite[addressIndex] = true;
  _canRead[addressIndex] = true;
}

//----------------------------------------FLProgDwin----------------------------------------
FLProgDwin::FLProgDwin(uint8_t croupsSize, FlprogAbstractUartExecutor *executor)
{
  _executor = executor;
  _croupsSize = croupsSize;
  _tables = new FLProgDwinDataTable[croupsSize];
}

void FLProgDwin::setTableSize(uint8_t groupIndex, uint32_t dataSize)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex]->setTableSize(dataSize);
}

void FLProgDwin::setAddress(uint8_t groupIndex, uint32_t addressIndex, int32_t address)
{
  if (groupIndex >= _croupsSize)
  {
    return;
  }
  _tables[groupIndex]->setAddress(addressIndex, address);
}
