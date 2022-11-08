#include <p18cxxx.h>/*18F系列微控制器標頭檔案*/
#include "k18.h"/*開發板標頭檔案*/

/*蜂鳴器發出「嘀」聲函式*/
/*功  能：蜂鳴器發出「嘀」（1KHZ高頻音）的一聲,發聲持續時間可變*/
/*參  數：t=1到255;發聲持續時間=t/10(秒)*/
/*返回值：無*/
void di(unsigned char t)
{
	unsigned char i,j;
	for (j=0;j<=t;j++)
		for (i=0;i<=100;i++)
		{
			BZ=1;/*輸出高電平*/
			delay500us();/*呼叫500us延時函式*/
			BZ=0;/*輸出低電平*/
			delay500us();/*呼叫500us延時函式*/
		}
}

/*蜂鳴器發出「嗒」聲函式*/
/*功  能：蜂鳴器發出「嗒」（500HZ低頻音）的一聲,發聲持續時間可變*/
/*參  數：t=1到255;發聲持續時間=t/10(秒)*/
/*返回值：無*/
void da(unsigned char t)
{
	unsigned char i,j;
	for (j=0;j<=t;j++)
		for (i=0;i<=50;i++)
		{
			BZ=1;/*輸出高電平*/
			delay1ms();/*呼叫1ms延時函式*/
			BZ=0;/*輸出低電平*/
			delay1ms();/*呼叫1ms延時函式*/
		}
}
