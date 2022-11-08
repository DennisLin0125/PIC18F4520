 #include <delays.h>


/*一些固定延時函式*/
void delay1s()
{
	unsigned int i;	
	unsigned int j;	
	for(j=1000;j;j--)	
		for(i=192;i;i--);
}

void delay100ms()
{
	Delay10KTCYx(25);
}

void delay10ms()
{
	Delay1KTCYx(25);
}

void delay5ms()
{
	Delay100TCYx(125);
}

void delay2ms()
{
	Delay100TCYx(50);
}

void delay1ms()
{
	Delay100TCYx(25);
}

/*void delay1ms()
{
	unsigned int i;	
	for(i=192;i;i--);
}*/

void delay500us()
{
	Delay10TCYx(125);
}

void delay200us()
{
	Delay10TCYx(50);
}

void delay100us()
{
	Delay10TCYx(25);
}



/*一個毫秒級可變延時函式*/
/*功  能：實現與參數直接對應的時間（單位為毫秒）的延時*/
/*參  數：範圍1到255*/
/*返回值：無*/
void delayms(unsigned int t)
{
	unsigned int i;	
	unsigned int j;	
	for(j=t;j;j--)	
		for(i=192;i;i--);/*1ms延時*/
}
  

/*一個秒級可變延時函式*/
/*功  能：實現與參數直接對應的時間（單位為秒）的延時*/
/*參  數：範圍0.01到42949672*/
/*返回值：無*/
void delay(float sec)
{
 	unsigned int i;
 	unsigned int j;
	j=sec*100;
     while(j--)
    	{
    		i=1561;
    		while(--i);
    	}
}
  
