
#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

//UART�ֽڳ�ʱʱ��
#define UART_PACK_TIMEOUT	(5)
//UARTһ֡������󳤶�
#define UART_MAX_RECV_LEN	(0x3F)
//UART������󳤶�
#define UART_RECV_FLAG		(0x8000)

/*---���Թ��ܿ���---*/
#define PRINTF_OFF 	(0)
#define PRINTF_ON	(1)
#define PRINTF_ONOFF	PRINTF_ON
#if ( PRINTF_ONOFF == PRINTF_ON )
#define PRINTF _printf
#else
#define PRINTF(...)
#endif
/*---���Թ��ܿ���---*/

#endif

