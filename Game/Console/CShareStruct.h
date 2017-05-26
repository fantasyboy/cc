#pragma once

#define US_MAP_NAME "GAME_LOL_1.0"


//游戏基地址相关
typedef struct _BASE_GAME_ADDR 
{
}BASE_GAME_ADDR;

//UI界面
typedef struct _UI_CONFIG_INFO
{

}UI_CONFIG_INFO;

#pragma pack(1)
typedef struct _SHARED_MEMORY_DATA
{
	BASE_GAME_ADDR game;
	UI_CONFIG_INFO ui;
}SHARED_MEMORY_DATA , *PSHARED_MEMORY_DATA;
#pragma pack()