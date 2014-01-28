#include  <string.h>
#include "Menu_Include.h"


u8 screen_2_8_counter=0;

void Disp_DnsIP(u8 par)
{

u8 apn[20]={"APN:"};   
u32 len1=0,len2=0;  

if(par==1)
	{
      lcd_fill(0);	
	//--------根据系统存入的条件判断显示
	if(Vechicle_Info.Link_Frist_Mode==1)
		lcd_text12(0,3,"优先连接主IP",12,LCD_MODE_SET);
	else
		lcd_text12(0,3,"优先连接主DNS",13,LCD_MODE_SET);
	//---------------------------------------------------
	if(Vechicle_Info.Vech_MODE_Mark==1)
		lcd_text12(0, 18,"模式:货运模式",13,LCD_MODE_SET);
	else if(Vechicle_Info.Vech_MODE_Mark==2)
		lcd_text12(0, 18,"模式:二客一危模式",17,LCD_MODE_SET);   
	lcd_update_all();
  } 
else if(par==2)
	{
	
	lcd_fill(0);
	if(strncmp((char *)APN_String,"CMNET",5)==0)
		{
		memcpy(apn+4,"CMNET",5);
		len1=5;
		}
	else if(strncmp((char *)APN_String,"UNINET",6)==0)
		{
		memcpy(apn+4,"UNINET",6);
		len1=6;
		}
	lcd_fill(0);
	lcd_text12(0,0,(char *)apn,4+len1,LCD_MODE_SET);

	if(Vechicle_Info.Vech_MODE_Mark==1)   //  货运模式
		{
          
		  lcd_text12(0, 11,DomainNameStr,strlen(DomainNameStr),LCD_MODE_SET);
		  lcd_text12(0, 22,DomainNameStr_aux,strlen(DomainNameStr_aux),LCD_MODE_SET);

		}
    else
	if(Vechicle_Info.Vech_MODE_Mark==2)   //   二客一危模式
		{
			lcd_text12(0, 11,TDT_MainDnsStr,strlen(TDT_MainDnsStr),LCD_MODE_SET);
			lcd_text12(0,22,TDT_AuxDnsStr,strlen(TDT_AuxDnsStr),LCD_MODE_SET); 
		}
	lcd_update_all();
	}
else if(par==3)
	{
	 lcd_fill(0);
	
		if(Vechicle_Info.Vech_MODE_Mark==1)   //  货运模式
		{
			lcd_text12(0, 3,TDT_MainDnsStr,strlen(TDT_MainDnsStr),LCD_MODE_SET);
			lcd_text12(0,18,TDT_AuxDnsStr,strlen(TDT_AuxDnsStr),LCD_MODE_SET); 
	   	}
	 lcd_update_all(); 
	}

}
static void msg( void *p)
{
}
static void show(void)
	{
	if(Vechicle_Info.Vech_MODE_Mark==2)
		screen_2_8_counter=2;
	else
		screen_2_8_counter=1;
	lcd_fill(0);
	lcd_text12(24,3,"查看设置信息",12,LCD_MODE_SET);
	lcd_text12(30,18,"请按确认键",10,LCD_MODE_SET);
	lcd_update_all();
	}
static void keypress(unsigned int key)
{

	switch(KeyValue)
		{
		case KeyValueMenu:
			screen_2_8_counter=0;
			CounterBack=0;
			
			pMenuItem=&Menu_2_InforCheck;
			pMenuItem->show();
			
			break;
		case KeyValueOk:
				Disp_DnsIP(screen_2_8_counter);
			break;
		case KeyValueUP:
			if(Vechicle_Info.Vech_MODE_Mark==1)
				{
				if(screen_2_8_counter>1)
					screen_2_8_counter--;
				else
					screen_2_8_counter=3;
				Disp_DnsIP(screen_2_8_counter);
				}
			else if(Vechicle_Info.Vech_MODE_Mark==2)
				{
				if(screen_2_8_counter>1)
					screen_2_8_counter--;
				else
					screen_2_8_counter=2;
				Disp_DnsIP(screen_2_8_counter);   
				}

			break;
		case KeyValueDown:
			if(Vechicle_Info.Vech_MODE_Mark==1) //  货运 3 page
				{
				screen_2_8_counter++;
				if(screen_2_8_counter>3)
					screen_2_8_counter=1;
					
				Disp_DnsIP(screen_2_8_counter);
				}
			else if(Vechicle_Info.Vech_MODE_Mark==2) // 二客一危  2 page
				{
				screen_2_8_counter++;
				if(screen_2_8_counter>2) 
					screen_2_8_counter=1;
					
				Disp_DnsIP(screen_2_8_counter);
				}
			break;
		}
 KeyValue=0;
}


static void timetick(unsigned int systick)
{
	CounterBack++;
	if(CounterBack!=MaxBankIdleTime)
		return;
	CounterBack=0;
	pMenuItem=&Menu_1_Idle;
	pMenuItem->show();

}


MENUITEM	Menu_2_8_DnsIpDisplay=
{
"DNS显示",
	7,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};

