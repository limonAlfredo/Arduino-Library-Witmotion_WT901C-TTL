#include "Vibration.h"

volatile char Vibration::s_cDataUpdate = 0;

Vibration::Vibration(uint8_t rxpin, uint8_t txpin, int baud) {
  Serial1.begin(baud, SERIAL_8N1, rxpin, txpin);
  WitInit(WIT_PROTOCOL_NORMAL, 0x50);
  WitSerialWriteRegister(SensorUartSend);
  WitRegisterCallBack(SensorDataUpdata);
  WitDelayMsRegister(Delayms);
}

void Vibration::SensorUartSend(uint8_t *p_data, uint32_t uiSize) {
  Serial1.write(p_data, uiSize);
  Serial1.flush();
}

void Vibration::Delayms(uint16_t ucMs) {
  delay(ucMs);
}

void Vibration::SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum) {
  int i;
  for (i = 0; i < uiRegNum; i++) {
    switch (uiReg) {
      case AZ:
        s_cDataUpdate |= ACC_UPDATE;
        break;
      case GZ:
        s_cDataUpdate |= GYRO_UPDATE;
        break;
      case HZ:
        s_cDataUpdate |= MAG_UPDATE;
        break;
      case Yaw:
        s_cDataUpdate |= ANGLE_UPDATE;
        break;
      default:
        s_cDataUpdate |= READ_UPDATE;
        break;
    }
    uiReg++;
  }
}

float *Vibration::getAcc() {
  return fAcc;
}

float *Vibration::getGyro() {
  return fGyro;
}

float *Vibration::getAngle() {
  return fAngle;
}

float *Vibration::getMagg() {
  return fMagg;
}

void Vibration::getData() {
  while (Serial1.available()) {
    WitSerialDataIn(Serial1.read());
  }
  if (s_cDataUpdate) {
    for (i = 0; i < 3; i++) {
      fAcc[i] = sReg[AX + i] / 32768.0f * 16.0f;
      fGyro[i] = sReg[GX + i] / 32768.0f * 2000.0f;
      fAngle[i] = sReg[Roll + i] / 32768.0f * 180.0f;
    }
    fMagg[0] = sReg[HX];
    fMagg[1] = sReg[HY];
    fMagg[2] = sReg[HZ];
    if (s_cDataUpdate & ACC_UPDATE) {
      s_cDataUpdate &= ~ACC_UPDATE;
    }
    if (s_cDataUpdate & GYRO_UPDATE) {
      s_cDataUpdate &= ~GYRO_UPDATE;
    }
    if (s_cDataUpdate & ANGLE_UPDATE) {
      s_cDataUpdate &= ~ANGLE_UPDATE;
    }
    if (s_cDataUpdate & MAG_UPDATE) {
      s_cDataUpdate &= ~MAG_UPDATE;
    }
    s_cDataUpdate = 0;
  } else {
    for (i = 0; i < 3; i++) {
      fAcc[i] = 0.0f;
      fGyro[i] = 0.0f;
      fAngle[i] = 0.0f;
      fMagg[i] = 0.0f;
    }
  }
}