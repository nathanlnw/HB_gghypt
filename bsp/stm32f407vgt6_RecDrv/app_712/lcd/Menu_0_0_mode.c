#include  <string.h>
#include "Menu_Include.h"
#include "Lcd.h"

static u8 type_selc_screen=0;
static u8 type_selc_flag=0;
static void msg( void *p)
{

}
static void show(void)
{
lcd_fill(0);
lcd_text12(0, 3,"货运模式",8,LCD_MODE_INVERT);
lcd_text12(0,18,"二客一危模式",12,LCD_MODE_SET); 
lcd_update_all();
type_selc_flag=1;
type_selc_screen=1;
}


static void keypress(unsigned int key)
{
	switch(KeyValue)
		{
		case KeyValueMenu:
			break;
		case KeyValueOk:
			if(type_selc_screen==1)
				{
				type_selc_screen=2;
				if(type_selc_flag==1)
					{
						lcd_fill(0);
						lcd_text12(9,3,"模式:货运模式",13,LCD_MODE_SET);
						lcd_text12(6,18,"按确认键设置下一项",18,LCD_MODE_SET);
						lcd_update_all();
						Vechicle_Info.Vech_MODE_Mark=1;
					}
				else
					{   
						lcd_fill(0);
						lcd_text12(15,3,"模式:二客一危模式",17,LCD_MODE_SET); 
						lcd_text12(6,18,"按确认键设置下一项",18,LCD_MODE_SET); 
						lcd_update_all();
						Vechicle_Info.Vech_MODE_Mark=2;
					}
				}
			else if(type_selc_screen==2)
				{
				if(MENU_set_carinfor_flag==1)
					{
					 //--------------------------------------------------------------------------------
                     //  select mode
					 if(Vechicle_Info.Vech_MODE_Mark==1)  //  公共货运平台
					 	{
	                         Vechicle_Info.Link_Frist_Mode=0; 
							 dnsr_main("jt1.gghypt.net");//修改DNS后  清空鉴权码
							 port_main("7008");
							 link_mode("0");//DNS 优先
							  //--------    清除鉴权码 ------------------- 
					         idip("clear");		

							memset((u8*)SysConf_struct.DNSR,0 ,sizeof(SysConf_struct.DNSR));
							memcpy(SysConf_struct.DNSR,"jt1.gghypt.net",14); 
							//   域名aux
							memset((u8*)SysConf_struct.DNSR_Aux,0 ,sizeof(SysConf_struct.DNSR_Aux));
							memcpy(SysConf_struct.DNSR_Aux,"jt2.gghypt.net",14);   

							//    2. Operate
							Api_Config_write(config,ID_CONF_SYS,(u8*)&SysConf_struct,sizeof(SysConf_struct)); 

							if( Api_Config_read(config,ID_CONF_SYS,(u8*)&SysConf_struct,sizeof(SysConf_struct))==true)   //读取系统配置信息
								{
								//   域名
								memset((u8*)DomainNameStr,0 ,sizeof(DomainNameStr));
								memcpy((u8*)DomainNameStr,SysConf_struct.DNSR,strlen((const char*)SysConf_struct.DNSR)); 
								//   域名aux
								memset((u8*)DomainNameStr_aux,0 ,sizeof(DomainNameStr_aux));
								memcpy((u8*)DomainNameStr_aux,SysConf_struct.DNSR_Aux,strlen((const char*)SysConf_struct.DNSR_Aux)); 
								}
					 	}
					 else if(Vechicle_Info.Vech_MODE_Mark==2)   //两客一危
					 	{
					 	    Vechicle_Info.Link_Frist_Mode=1;
	                        //Socket_main_Set("60.28.50.210:9131"); 
	                        dnsr_main(TDT_MainDnsStr);////修改DNS后  清空鉴权码
	                        port_main("8201");
							link_mode("0");
							 //--------    清除鉴权码 -------------------
					        idip("clear");		
							
                            memset((u8*)SysConf_struct.DNSR,0 ,sizeof(SysConf_struct.DNSR));
							memcpy(SysConf_struct.DNSR,TDT_MainDnsStr,strlen(TDT_MainDnsStr)); 
							//   域名aux
							memset((u8*)SysConf_struct.DNSR_Aux,0 ,sizeof(SysConf_struct.DNSR_Aux));
							memcpy(SysConf_struct.DNSR_Aux,TDT_AuxDnsStr,strlen(TDT_AuxDnsStr));   

							//    2. Operate
							Api_Config_write(config,ID_CONF_SYS,(u8*)&SysConf_struct,sizeof(SysConf_struct));       
							if( Api_Config_read(config,ID_CONF_SYS,(u8*)&SysConf_struct,sizeof(SysConf_struct))==true)   //读取系统配置信息
								{
								//   域名
								memset((u8*)DomainNameStr,0 ,sizeof(DomainNameStr));
								memcpy((u8*)DomainNameStr,SysConf_struct.DNSR,strlen((const char*)SysConf_struct.DNSR)); 
								//   域名aux
								memset((u8*)DomainNameStr_aux,0 ,sizeof(DomainNameStr_aux));
								memcpy((u8*)DomainNameStr_aux,SysConf_struct.DNSR_Aux,strlen((const char*)SysConf_struct.DNSR_Aux)); 
								}
					 	}
					 //------------------------------------------------------------------------------------					
					DF_WriteFlashSector(DF_Vehicle_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info)); 
					WatchDog_Feed();
					DF_WriteFlashSector(DF_VehicleBAK_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info)); 
					WatchDog_Feed();
					DF_WriteFlashSector(DF_VehicleBAK2_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info));
					}
				type_selc_screen=0;
				type_selc_flag=0;
				
				CarSet_0_counter=1;
				
				pMenuItem=&Menu_0_loggingin;
				pMenuItem->show();
				}
			break;
		case KeyValueUP:
			if(type_selc_screen==1)
				{
				type_selc_flag=1;
				lcd_fill(0);
				lcd_text12(0, 3,"货运模式",8,LCD_MODE_INVERT); 
				lcd_text12(0,18,"二客一危模式",12,LCD_MODE_SET);
				lcd_update_all();
				}
			break;
		case KeyValueDown:
			if(type_selc_screen==1)
				{
				type_selc_flag=2;
				lcd_fill(0);
				lcd_text12(0, 3,"货运模式",8,LCD_MODE_SET);
				lcd_text12(0,18,"二客一危模式",12,LCD_MODE_INVERT);
				lcd_update_all();
				}
			break;
		}
	KeyValue=0;
}


static void timetick(unsigned int systick)
{

}

ALIGN(RT_ALIGN_SIZE)
MENUITEM	Menu_0_0_mode=
{
	"类型",
	6,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};




