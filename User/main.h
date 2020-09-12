
#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

//UART字节超时时间
#define UART_PACK_TIMEOUT	(5)
//UART一帧数据最大长度
#define UART_MAX_RECV_LEN	(0x3F)
//UART接收最大长度
#define UART_RECV_FLAG		(0x8000)

/*---调试功能开关---*/
#define PRINTF_OFF 	(0)
#define PRINTF_ON	(1)
#define PRINTF_ONOFF	PRINTF_ON
#if ( PRINTF_ONOFF == PRINTF_ON )
#define PRINTF _printf
#else
#define PRINTF(...)
#endif
/*---调试功能开关---*/

#endif

