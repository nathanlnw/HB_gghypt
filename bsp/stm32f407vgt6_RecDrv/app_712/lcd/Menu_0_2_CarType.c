#include  <string.h>
#include "Menu_Include.h"


struct IMG_DEF test_scr_CarType={12,12,test_00};

unsigned char CarType_counter=0;
unsigned char CarType_Type=0;


void CarType(unsigned char type_Sle,unsigned char sel) 
{
switch(type_Sle)
	{
	case 1:
		lcd_fill(0);
		if(sel==0)
			{
			lcd_text12(24,3,"车辆类型选择",12,LCD_MODE_SET); 
		    lcd_text12(0,19,"1.  客运车",10,LCD_MODE_SET);
			}
		else
			lcd_text12(12,10,"车辆类型:客运车",15,LCD_MODE_SET);
		lcd_update_all();
		break;
	case 2:
		lcd_fill(0);
		if(sel==0)
			{
			lcd_text12(24,3,"车辆类型选择",12,LCD_MODE_SET); 
		    lcd_text12(0,19,"2.  危品车",10,LCD_MODE_SET);
			}
		else
			lcd_text12(12,10,"车辆类型:危品车",15,LCD_MODE_SET);
		lcd_update_all();
		break;
	case 3:
		lcd_fill(0);
		if(sel==0)
			{
			lcd_text12(24,3,"车辆类型选择",12,LCD_MODE_SET); 
		    lcd_text12(0,19,"3.  旅游车",10,LCD_MODE_SET);
			}
		else
			lcd_text12(12,10,"车辆类型:旅游车",15,LCD_MODE_SET);
		lcd_update_all();
		break;
	}
}

static void msg( void *p)
{

}
static void show(void)
{
    CounterBack=0;	
	CarType_counter=1;
	
    if(Vechicle_Info.Vech_MODE_Mark==1)
    	{
    	CarType_Type=2;
		lcd_fill(0);
		lcd_text12(12,10,"车辆类型:客运车",15,LCD_MODE_SET);
		lcd_update_all();
    	}
	else
		{
		CarType_Type=1;
		CarType(CarType_counter,0);
		}	
}


static void keypress(unsigned int key)
{
	switch(KeyValue)
		{
		case KeyValueMenu:
			
			pMenuItem=&Menu_0_loggingin;
			pMenuItem->show();
			CarType_counter=0;
			CarType_Type=0;
			break;
		case KeyValueOk:

			if(CarType_Type==1)
				{
				CarType_Type=2;
				CarType(CarType_counter,1);
				}
			else if(CarType_Type==2)
				{				
				//写入车辆类型
				if((CarType_counter>=1)&&(CarType_counter<=3))
					memset(Menu_VechileType,0,sizeof(Menu_VechileType));
				if(Vechicle_Info.Vech_MODE_Mark==1)
					memcpy(Menu_VechileType,"货运车",6); 
				else
					{
					if(CarType_counter==1)
						memcpy(Menu_VechileType,"客运车",6); 
					else if(CarType_counter==2)
						memcpy(Menu_VechileType,"危品车",6); 
					else if(CarType_counter==3)
						memcpy(Menu_VechileType,"旅游车",6); 
					}

				CarType_Type=3;
								// 车辆类型
				if(MENU_set_carinfor_flag==1)
					{
					rt_kprintf("\r\n车辆类型设置完成，按菜单键返回，%s",Menu_VechileType);		
					memset(Vechicle_Info.Vech_Type,0,sizeof(Vechicle_Info.Vech_Type));
					memcpy(Vechicle_Info.Vech_Type,Menu_VechileType,10);
					DF_WriteFlashSector(DF_Vehicle_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info));         
						WatchDog_Feed();
					    DF_WriteFlashSector(DF_VehicleBAK_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info)); 
						WatchDog_Feed();
					    DF_WriteFlashSector(DF_VehicleBAK2_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info));
					}
				lcd_fill(0);
				lcd_text12(12,3,"车辆类型选择完毕",16,LCD_MODE_SET);
				lcd_text12(6,18,"按确认键设置下一项",18,LCD_MODE_SET);
				lcd_update_all();
				}
			else if(CarType_Type==3)
				{
				CarSet_0_counter=3;//设置第3项
				pMenuItem=&Menu_0_loggingin;
				pMenuItem->show();
				
				CarType_counter=0;
				CarType_Type=0;
				}
			break;
		case KeyValueUP:
			if(Vechicle_Info.Vech_MODE_Mark==2)
				{
				if(	CarType_Type==1)
					{
					if(CarType_counter==1)
						CarType_counter=3;
					else
						CarType_counter--;
					//printf("\r\n  up  车辆类型选择 = %d",CarType_counter);
					CarType(CarType_counter,0);
					}
				}
			break;
		case KeyValueDown:
			if(Vechicle_Info.Vech_MODE_Mark==2)
				{
				if(	CarType_Type==1)
					{
					if(CarType_counter>=3)
						CarType_counter=1;
					else
						CarType_counter++;
						
					//printf("\r\n down 车辆类型选择 = %d",CarType_counter);
					CarType(CarType_counter,0);
					}
				}

			break;
		}
	KeyValue=0;
}


static void timetick(unsigned int systick)
{

}


MENUITEM	Menu_0_2_CarType=
{
    "车辆类型设置",
	12,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};


