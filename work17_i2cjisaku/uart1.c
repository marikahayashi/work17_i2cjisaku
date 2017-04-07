
#include "sfr_r835c.h"
#include "uart1.h"

void uart1_init(void){
	_asm(" FCLR I");
	////uartの設定////	
	//パリティなし、ストップビット2、内部クロック、UARTモード転送データ長8ビット
	u1mr = 0b00010101;
	//fj/(16(n+1))なので、
	// 20MHz/(16*x)=19200とするとx=20M/19200/16=65
	//u1brg = 65-1;
	u1brg = 33-1; //誤差0.45/33.55 = 1.3%
	//u1brg = 16-1; //誤差0.2/16.27 = 1.2% //動かない
	//カウントソースf1、txd1はcmosアウトプット、LSBファースト
	u1c0 = 0x00;
	//連続受信モード禁止、送信割り込み要因は送信バッファ空、
	//受信完了フラグはU1RBにデータなし、受信許可、
	//送信バッファ空フラグはu1TBにデータなし、送信許可
	u1c1 = 0x05;
	//TXD1 P0_1
	txd1sel0 = 1;
	txd1sel1 = 0;
	//RXD1 P0_2
	rxd1sel0 = 1;
	rxd1sel1 = 0;
	//割り込みレベル1
	s1tic = 0x00;
	s1ric = 0x00;
	_asm(" FSET I");
}

void uart1_write(char* msg_string) {
	char i;
	unsigned char trn_buf;
	for(i=0; msg_string[i] != '\0'; i++) {
		//送信バッファが空になるのを待つ
		while(ti_u1c1 == 0);
		//送信バッファに文字をセット
		trn_buf = msg_string[i];
		u1tbl = trn_buf;
		
	}
}

void uart1_receive(char* recv_buf) {
	unsigned char recv_error[MAX_RECV];
	int recv_cnt=0;
	//もしなにかバッファに届いていたら
	while (ri_u1c1 == 1)
	{
		recv_buf[recv_cnt] = u1rbl;
		recv_error[recv_cnt] = u1rbh;
		recv_cnt++;
		if(recv_cnt==MAX_RECV-1) {
			recv_cnt = 0;
			break;
		}
	}
	recv_buf[recv_cnt+1] = '\0';
	
}