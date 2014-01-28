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
    lcd_text12(0, 18,"����ģʽ    ����һΣ",20,LCD_MODE_SET);		
	if(Vechicle_Info.Vech_MODE_Mark==1)
		{
		lcd_text12(0, 0,"ģʽ:����ģʽ",13,LCD_MODE_SET);
		lcd_text12(0, 18,"����ģʽ",8,LCD_MODE_INVERT);
		}
	else if(Vechicle_Info.Vech_MODE_Mark==2)
		{
		lcd_text12(0, 0,"ģʽ:����һΣ",13,LCD_MODE_SET);
		lcd_text12(72, 18,"����һΣ",8,LCD_MODE_INVERT);
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
				if(mode_sel_mark==1)//����ģʽ
					{
					lcd_fill(0);
					lcd_text12(10, 3,"����ģʽ:����ģʽ",17,LCD_MODE_SET);
					lcd_text12(24, 18,"��ȷ�ϼ�����",12,LCD_MODE_SET);
					Vechicle_Info.Vech_MODE_Mark=1;
					idip("clear");	// �����Ȩ��
					DEV_regist.Enable_sd=1; // set ����ע���־λ
			        DataLink_EndFlag=1; 
					lcd_update_all();
					}
				else//��׼ģʽ
					{
					lcd_fill(0);
					lcd_text12(10, 3,"ģʽ:����һΣ",13,LCD_MODE_SET);
					lcd_text12(24, 18,"��ȷ�ϼ�����",12,LCD_MODE_SET);
					Vechicle_Info.Vech_MODE_Mark=2;
					idip("clear");	// �����Ȩ��
					DEV_regist.Enable_sd=1; // set ����ע���־λ
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
				lcd_text12(36, 10,"����ɹ�",8,LCD_MODE_SET);
				lcd_update_all();
				}

			break;
			
		case KeyValueUP:
			if(mode_sel==1)
				{
				mode_sel_mark=1;
				lcd_fill(0);
				lcd_text12(0, 18,"����ģʽ    ����һΣ",20,LCD_MODE_SET);
				lcd_text12(0, 18,"����ģʽ",8,LCD_MODE_INVERT);
				if(Vechicle_Info.Vech_MODE_Mark==1)
					lcd_text12(0, 0,"����ģʽ:����ģʽ",17,LCD_MODE_SET);
				else if(Vechicle_Info.Vech_MODE_Mark==2)
					lcd_text12(0, 0,"ģʽ:����һΣ",13,LCD_MODE_SET);
				lcd_update_all();
				} 
			break;
			
		case KeyValueDown:
			if(mode_sel==1)
				{
				mode_sel_mark=2;
				lcd_fill(0);
				lcd_text12(0, 18,"����ģʽ    ����һΣ",20,LCD_MODE_SET);
				lcd_text12(72, 18,"����һΣ",8,LCD_MODE_INVERT);
				if(Vechicle_Info.Vech_MODE_Mark==1)
					lcd_text12(0, 0,"ģʽ:����ģʽ",13,LCD_MODE_SET);
				else if(Vechicle_Info.Vech_MODE_Mark==2)
					lcd_text12(0, 0,"ģʽ:����һΣ",13,LCD_MODE_SET); 
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
"����ģʽ����",
	12,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};
