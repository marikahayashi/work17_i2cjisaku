#ifndef __H_UART1__
#define __H_UART1__

#define MAX_RECV (20)
void uart1_write(char* msg_string);
void uart1_receive(char* recv_buf);
void uart1_init(void);
#endif