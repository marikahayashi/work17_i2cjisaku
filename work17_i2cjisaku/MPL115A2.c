#include "sfr_r835c.h"
#include "MPL115A2.h"


#define WAIT1 (0x4)
#define WAIT2 (0x8)
#define WAIT3 (0x2)

#define SCLHiZ() pd3_5=0
#define SCLLow() pd3_5=1;p3_5=0
#define SDAHiZ() pd3_7=0
#define SDALow() pd3_7=1;p3_7=0
#define SDA p3_7
#define SCL p3_5

void i2c_startcondition(void);
void i2c_stopcondition(void);
int i2c_sendbyte(unsigned char byData);
void i2c_read1byte(unsigned char *byData);
void waitloop(int nTimes);
int i2c_sendcommand(unsigned char byAddr,unsigned char byCmd);
int i2c_requestfrom(unsigned char byAddr,
	unsigned char byROMAddr,unsigned char *abyData,int nBytes);

void i2c_init(void) {
	//port setting
	pd3_7 = 0;
	pd3_5 = 0;
	p3_7 = 0; //SDA
	p3_5 = 0; //SCL

}

void i2c_startcondition(void) {
	SDAHiZ();
	SCLHiZ();
	waitloop(WAIT1);
	SDALow();
	waitloop(WAIT1);
}

void i2c_stopcondition(void) {
	SDALow();
	SCLHiZ();
	waitloop(WAIT1);
	SDAHiZ();
}

int i2c_sendbyte(unsigned char byData) {
	int i;
	char cCurbit;
	for(i=7; i>=0; i--) {
		cCurbit = (byData >> i) & 0x01;
		SCLLow();
		waitloop(WAIT3);
		if(cCurbit == 0) {
			SDALow();
		} else {
			SDAHiZ();
		}
		waitloop(WAIT3);
		SCLHiZ();
		waitloop(WAIT1);
		SCLLow();
	}
	waitloop(WAIT1);
	//waitloop(WAIT1);
	//9thclock
	SDAHiZ();
	SCLHiZ();
	waitloop(WAIT3);
	if(SDA != 0) {//if not ACK -> error
		return I2C_ERROR;
	}
	waitloop(WAIT1);
	//SDALow(); //Ç‡ÇµìÆÇ©Ç»Ç¢Ç»ÇÁÇŒÉRÉÅÉìÉgÉCÉì
	SCLLow();
	//waitloop(WAIT2);
	waitloop(WAIT1);
	return I2C_SUCCESS;
}

int i2c_sendcommand(unsigned char byAddr,unsigned char byCmd) {
	int nRtn;
	i2c_startcondition();
	nRtn = i2c_sendbyte(byAddr & 0xfe);
	if (nRtn == I2C_ERROR) { return I2C_ERROR; }
	nRtn = i2c_sendbyte(byCmd);
	if (nRtn == I2C_ERROR) { return I2C_ERROR; }
	nRtn = i2c_sendbyte(0x01);
	if (nRtn == I2C_ERROR) { return I2C_ERROR; }
	i2c_stopcondition();
	return I2C_SUCCESS;
}

int MPL115A2_startADC(void) {
	return i2c_sendcommand(0xc0, 0x12);
}

int i2c_requestfrom(unsigned char byAddr,
									 unsigned char byROMAddr,
									 unsigned char *abyData, int nBytes) {
	int nRtn;
	int i;
	i2c_startcondition();
	nRtn = i2c_sendbyte(byAddr & 0xfe); //write LSB=0
	if (nRtn == I2C_ERROR) { return I2C_ERROR; }
	nRtn = i2c_sendbyte(byROMAddr);
	if (nRtn == I2C_ERROR) { return I2C_ERROR; }
	i2c_startcondition();
	nRtn = i2c_sendbyte(byAddr | 0x01);	//read LSB=1
	if (nRtn == I2C_ERROR) { return I2C_ERROR; }
	for(i=0; i<nBytes-1; i++) {
		i2c_read1byte(&abyData[i]);
		SDALow();//ACK
		waitloop(WAIT3);
		SCLHiZ();
		waitloop(WAIT3);
	}
	i2c_read1byte(&abyData[nBytes-1]);
	SCLHiZ();
	SDAHiZ();//NACK
	waitloop(WAIT1);
	SCLLow();
	waitloop(WAIT2);
	i2c_stopcondition();
	return I2C_SUCCESS;
}

int MPL115A2_readrawdata(unsigned short *puwPadc, unsigned short *puwTadc) {
	unsigned char abyData[4];
	int nRet;
	nRet = i2c_requestfrom(0xc0, 0x00, abyData, 4);
	if(nRet==I2C_ERROR) { return I2C_ERROR; }
	*puwPadc = (unsigned int)abyData[0] << 2
								| (unsigned int)abyData[1] >> 6;
	*puwTadc = (unsigned int)abyData[2] << 2
								| (unsigned int)abyData[3] >> 6;
	return I2C_SUCCESS;
}

void i2c_read1byte(unsigned char *byData) {
	int i;
	*byData = 0x00;
	for(i=7; i>=0; i--) {
		SCLLow();
		SDAHiZ();
		waitloop(WAIT1);
		SCLHiZ();
		waitloop(WAIT3);
		*byData |= SDA<<i;
		waitloop(WAIT3);
	}
	SCLLow();
	waitloop(WAIT2);
}


void waitloop(int nTimes) {
	int i=0;
	for (i=0; i<nTimes; i++);
}