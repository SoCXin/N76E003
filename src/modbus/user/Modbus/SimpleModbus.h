#ifndef SIMPLE_MODBUS_H
#define SIMPLE_MODBUS_H

#include "Common.h"

void modbus_configure(UINT32 baud, UINT8 _slaveID, UINT16 _holdingRegsSize, UINT8 _lowLatency);
UINT16 modbus_poll(UINT16 *holdingRegs);

#endif /* SIMPLE_MODBUS_H */