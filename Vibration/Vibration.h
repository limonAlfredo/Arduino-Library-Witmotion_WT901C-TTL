#ifndef VIBRATION_H
#define VIBRATION_H
#include <HardwareSerial.h>
#include <REG.h>
#include <wit_c_sdk.h>

#define ACC_UPDATE 0x01
#define GYRO_UPDATE 0x02
#define ANGLE_UPDATE 0x04
#define MAG_UPDATE 0x08
#define READ_UPDATE 0x80

class Vibration
{
private:
    int i;
    float fAcc[3], fGyro[3], fAngle[3], fMagg[3];
    static volatile char s_cDataUpdate;
    static void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
    static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
    static void Delayms(uint16_t ucMs);

public:
    Vibration(uint8_t rxpin, uint8_t txpin, int baud);
    void getData();
    float *getAcc();
    float *getGyro();
    float *getAngle();
    float *getMagg();
};
#endif