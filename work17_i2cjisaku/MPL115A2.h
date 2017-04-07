
#define I2C_ERROR (-1)
#define I2C_SUCCESS (1)

void i2c_init(void);
int MPL115A2_startADC(void);
int MPL115A2_readrawdata(unsigned short *puwPadc, unsigned short *puwTadc);