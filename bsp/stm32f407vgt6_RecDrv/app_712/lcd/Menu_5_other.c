#include "Menu_Include.h"
#include <string.h>


unsigned char noselect_5[]={0x3C,0x7E,0xC3,0xC3,0xC3,0xC3,0x7E,0x3C};//空心
unsigned char select_5[]={0x3C,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x3C};//实心

DECL_BMP(8,8,select_5); DECL_BMP(8,8,noselect_5); 

static unsigned char menu_pos=0;
static PMENUITEM psubmenu[8]=
{
	&Menu_5_1_TelDis,
	&Menu_5_2_TelAtd,
	&Menu_5_3_bdupgrade,
	&Menu_5_4_bdColdBoot,
	//&Menu_5_5_can,
	&Menu_5_6_Concuss,
	&Menu_5_7_Version,
	&Menu_5_8_Usb,
	&Menu_5_9_mode,
};
static void menuswitch(void)
{
unsigned char i=0;
	
lcd_fill(0);
lcd_text12(0,3,"其它",4,LCD_MODE_SET);
lcd_text12(0,17,"信息",4,LCD_MODE_SET);
for(i=0;i<8;i++)
	lcd_bitmap(30+i*11, 5, &BMP_noselect_5, LCD_MODE_SET);
lcd_bitmap(30+menu_pos*11,5,&BMP_select_5,LCD_MODE_SET);
lcd_text12(30,19,(char *)(psubmenu[menu_pos]->caption),psubmenu[menu_pos]->len,LCD_MODE_SET);
lcd_update_all();
}
static void msg( void *p)
{
}
static void show(void)
{
    menu_pos=0;
	menuswitch();
}


static void keypress(unsigned int key)
{
switch(KeyValue)
	{
	case KeyValueMenu:
		//允许退出
		Password_correctFlag=1;
		
		pMenuItem=&Menu_6_SetInfor;
		pMenuItem->show();
		CounterBack=0;

		break;
	case KeyValueOk:
		if(menu_pos==7)
			{
			MENU_set_InsertMode_flag=1;
			pMenuItem=&Menu_0_0_password;//输入密码
			pMenuItem->show();
            }
		else
			{
			pMenuItem=psubmenu[menu_pos];//疲劳驾驶
			pMenuItem->show();
			}
		break;
	case KeyValueUP:
		if(menu_pos==0) 
			menu_pos=7;
		else
			menu_pos--;
		menuswitch();		
		break;
	case KeyValueDown:
		menu_pos++;
		if(menu_pos>7)
			menu_pos=0;
		menuswitch();
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

ALIGN(RT_ALIGN_SIZE)
MENUITEM	Menu_5_other=
{
    "其他信息",
	8,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};

