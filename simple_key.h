/***************************************************************************
* Create Date:   2022/2/8
* Modified Date: 2022/2/9
* Version:1.0
* License: LGPL 2.1
* Github: https://github.com/Xinkerr
* Mail: garyzh@yeah.net
****************************************************************************/
#ifndef __SIMPLE_KEY_H__
#define __SIMPLE_KEY_H__

#include <stdint.h>

/************************驱动程序*******************************/
#include "key_drv.h"
#define KEY_PORT_INIT_DRIVER()					key_drv_port_init()
#define KEY_SCAN_DRIVER(NUMBER)					key_drv_get(NUMBER)
/***************************************************************/

/**************************配置********************************/
//消抖时间
#define DEBOUNCE_INTERVAL		1
/***************************************************************/


typedef struct
{
	uint8_t debouncePress :1;					//按下消抖标志
	uint8_t press :1;                           //有效按下标志
	uint8_t debounceRelease :1;                 //松手消抖标志
	uint8_t release :1;                         //有效松手标志
    uint8_t invaild :4;

	// uint16_t press_cnt;                          //按键按下扫描计数累加(按下时间)
	// uint16_t release_cnt;                        //按键松手扫描计数累加(松手时间)
	uint16_t debounceRe_cnt;
	uint16_t debouncePr_cnt;
}simple_key_t;

/**@brief    按键初始化
 *
 * @details
 *
 * @param[in] key_ptr: simple_key_t 结构体数组
 * @param[in] count：按键数量
 *
 * @return    void
 **/
void simple_key_init(simple_key_t* key_table, uint8_t count);

/**@brief   按键扫描 
 *
 * @details 轮询获取每个按键状态，如有触发则传出
 *          
 * @return  触发的按键序号
 **/
uint8_t simple_key_scan(void);

#endif

