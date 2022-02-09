/***************************************************************************
* Create Date:   2022/2/8
* Modified Date: 2022/2/9
* Version:1.0
* License: LGPL 2.1
* Github: https://github.com/Xinkerr
* Mail: garyzh@yeah.net
****************************************************************************/
#include "simple_key.h"
#include <string.h>

#define	SET						1
#define RESET					0

static simple_key_t* simple_key;
static uint8_t key_count;

/**@brief    按键初始化
 *
 * @details
 *
 * @param[in] key_ptr: simple_key_t 结构体数组
 * @param[in] count：按键数量
 *
 * @return    void
 **/
void simple_key_init(simple_key_t* key_table, uint8_t count)
{
	KEY_PORT_INIT_DRIVER();
	
	simple_key = key_table;
	key_count = count;
}

/**@brief   按键扫描 
 *
 * @details 轮询获取每个按键状态，如有触发则传出
 *          
 * @return  触发的按键序号
 **/
uint8_t simple_key_scan(void)
{
	uint8_t i;
	for(i = 1; i <= key_count; i++)
	{
		if(KEY_SCAN_DRIVER(i))
		{
			//按下消抖后
			if(simple_key[i].debouncePress)
			{
                //相关松手标志清零
				simple_key[i].release = RESET;
				simple_key[i].debounceRelease = RESET;

                if(simple_key[i].press == RESET)
                {
				    simple_key[i].press = SET;
                    return i;
                } 
			}
			else
			{
				//按下消抖
				simple_key[i].debouncePr_cnt ++;
				if(simple_key[i].debouncePr_cnt >= DEBOUNCE_INTERVAL)
				{
					simple_key[i].debouncePress = SET;
				}
			}
			simple_key[i].debounceRe_cnt = 0;

			//检测PRESS信号后，松手消抖需重新检测
			simple_key[i].debounceRelease = RESET;
		}
		else
		{
			//松手消抖有效
			if(simple_key[i].debounceRelease)
			{	
				simple_key[i].release = SET;
				//相关按下标志清零
				simple_key[i].debouncePress = RESET;
				simple_key[i].press = RESET;
			}
			else
			{
				//松手消抖
				simple_key[i].debounceRe_cnt ++;
				if(simple_key[i].debounceRe_cnt >= DEBOUNCE_INTERVAL)
				{
					simple_key[i].debounceRelease = SET;
				}
			}
			simple_key[i].debouncePr_cnt = 0;
		}
	}
	return 0;
}