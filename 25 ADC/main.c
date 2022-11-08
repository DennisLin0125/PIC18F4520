#include <p18cxxx.h>
#include "define.h"

void main(void)
{	
	uint lednum=0,m;
	uchar a[4]={0},i;
	ADCinit();
	while(1)
	{
		m=1;
		i=0;
		lednum=get_ad();
		while(m<=1000)
		{
			*(a+i)=lednum/m%10;   //擷取個位~千位
			m*=10;
			i++;
		}
		display(a);	  //將a陣列丟到七段顯示
	}
}