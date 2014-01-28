#include "Menu_Include.h"


u8 mode_sel=0;
u8 mode_sel_mark=0;
static void msg( void *p)
{

}
static void show(void)
{
	mode_sel=1;
	lcd_fill(0);
    lcd_text12(0, 18,"货运模式    二客一危",20,LCD_MODE_SET);		
	if(Vechicle_Info.Vech_MODE_Mark==1)
		{
		lcd_text12(0, 0,"模式:货运模式",13,LCD_MODE_SET);
		lcd_text12(0, 18,"货运模式",8,LCD_MODE_INVERT);
		}
	else if(Vechicle_Info.Vech_MODE_Mark==2)
		{
		lcd_text12(0, 0,"模式:二客一危",13,LCD_MODE_SET);
		lcd_text12(72, 18,"二客一危",8,LCD_MODE_INVERT);
		}
	lcd_update_all();
}


static void keypress(unsigned int key)
{

	switch(KeyValue)
		{
		case KeyValueMenu:
			pMenuItem=&Menu_5_other;
			pMenuItem->show();
			
			CounterBack=0;

			mode_sel=0;
			mode_sel_mark=0;
			break;
			
		case KeyValueOk:
			if(mode_sel==1)
				{
				mode_sel=2;
				if(mode_sel_mark==1)//货运模式
					{
					lcd_fill(0);
					lcd_text12(10, 3,"接入模式:货运模式",17,LCD_MODE_SET);
					lcd_text12(24, 18,"按确认键保存",12,LCD_MODE_SET);
					Vechicle_Info.Vech_MODE_Mark=1;
					idip("clear");	// 清除鉴权码
					DEV_regist.Enable_sd=1; // set 发送注册标志位
			        DataLink_EndFlag=1; 
					lcd_update_all();
					}
				else//标准模式
					{
					lcd_fill(0);
					lcd_text12(10, 3,"模式:二客一危",13,LCD_MODE_SET);
					lcd_text12(24, 18,"按确认键保存",12,LCD_MODE_SET);
					Vechicle_Info.Vech_MODE_Mark=2;
					idip("clear");	// 清除鉴权码
					DEV_regist.Enable_sd=1; // set 发送注册标志位
			        DataLink_EndFlag=1; 
					lcd_update_all();
					}
				}
			else if(mode_sel==2)
				{
				mode_sel=0;
				mode_sel_mark=0;

				DF_WriteFlashSector(DF_Vehicle_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info)); 
				WatchDog_Feed();
				lcd_fill(0);
				lcd_text12(36, 10,"保存成功",8,LCD_MODE_SET);
				lcd_update_all();
				}

			break;
			
		case KeyValueUP:
			if(mode_sel==1)
				{
				mode_sel_mark=1;
				lcd_fill(0);
				lcd_text12(0, 18,"货运模式    二客一危",20,LCD_MODE_SET);
				lcd_text12(0, 18,"货运模式",8,LCD_MODE_INVERT);
				if(Vechicle_Info.Vech_MODE_Mark==1)
					lcd_text12(0, 0,"接入模式:货运模式",17,LCD_MODE_SET);
				else if(Vechicle_Info.Vech_MODE_Mark==2)
					lcd_text12(0, 0,"模式:二客一危",13,LCD_MODE_SET);
				lcd_update_all();
				} 
			break;
			
		case KeyValueDown:
			if(mode_sel==1)
				{
				mode_sel_mark=2;
				lcd_fill(0);
				lcd_text12(0, 18,"货运模式    二客一危",20,LCD_MODE_SET);
				lcd_text12(72, 18,"二客一危",8,LCD_MODE_INVERT);
				if(Vechicle_Info.Vech_MODE_Mark==1)
					lcd_text12(0, 0,"模式:货运模式",13,LCD_MODE_SET);
				else if(Vechicle_Info.Vech_MODE_Mark==2)
					lcd_text12(0, 0,"模式:二客一危",13,LCD_MODE_SET); 
				lcd_update_all();
				} 
			break;	
		}
 KeyValue=0;
}


static void timetick(unsigned int systick)
{
	CounterBack++;
	if(CounterBack!=MaxBankIdleTime*5)
		return;
	CounterBack=0;
	pMenuItem=&Menu_1_Idle;
	pMenuItem->show();

}

ALIGN(RT_ALIGN_SIZE)
MENUITEM	Menu_5_9_mode=
{
"接入模式设置",
	12,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};
