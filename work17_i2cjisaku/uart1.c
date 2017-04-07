
#include "sfr_r835c.h"
#include "uart1.h"

void uart1_init(void){
	_asm(" FCLR I");
	////uart�̐ݒ�////	
	//�p���e�B�Ȃ��A�X�g�b�v�r�b�g2�A�����N���b�N�AUART���[�h�]���f�[�^��8�r�b�g
	u1mr = 0b00010101;
	//fj/(16(n+1))�Ȃ̂ŁA
	// 20MHz/(16*x)=19200�Ƃ����x=20M/19200/16=65
	//u1brg = 65-1;
	u1brg = 33-1; //�덷0.45/33.55 = 1.3%
	//u1brg = 16-1; //�덷0.2/16.27 = 1.2% //�����Ȃ�
	//�J�E���g�\�[�Xf1�Atxd1��cmos�A�E�g�v�b�g�ALSB�t�@�[�X�g
	u1c0 = 0x00;
	//�A����M���[�h�֎~�A���M���荞�ݗv���͑��M�o�b�t�@��A
	//��M�����t���O��U1RB�Ƀf�[�^�Ȃ��A��M���A
	//���M�o�b�t�@��t���O��u1TB�Ƀf�[�^�Ȃ��A���M����
	u1c1 = 0x05;
	//TXD1 P0_1
	txd1sel0 = 1;
	txd1sel1 = 0;
	//RXD1 P0_2
	rxd1sel0 = 1;
	rxd1sel1 = 0;
	//���荞�݃��x��1
	s1tic = 0x00;
	s1ric = 0x00;
	_asm(" FSET I");
}

void uart1_write(char* msg_string) {
	char i;
	unsigned char trn_buf;
	for(i=0; msg_string[i] != '\0'; i++) {
		//���M�o�b�t�@����ɂȂ�̂�҂�
		while(ti_u1c1 == 0);
		//���M�o�b�t�@�ɕ������Z�b�g
		trn_buf = msg_string[i];
		u1tbl = trn_buf;
		
	}
}

void uart1_receive(char* recv_buf) {
	unsigned char recv_error[MAX_RECV];
	int recv_cnt=0;
	//�����Ȃɂ��o�b�t�@�ɓ͂��Ă�����
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