/*****************************************************************************
 *
 *   Copyright(C) 2011, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * Embedded Artists AB assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. Embedded Artists AB
 * reserves the right to make changes in the software without
 * notification. Embedded Artists AB also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "string.h"
#include "stdio.h"
#include "lpc_types.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_timer.h"
#include "lpc177x_8x_i2c.h"
#include "lpc177x_8x_uart.h"

#include "acc.h"
#include "board.h"


/******************************************************************************
 * Typedefs and defines
 *****************************************************************************/

#define I2C_PORT (I2C_0)

/******************************************************************************
 * Local Functions
 *****************************************************************************/


/******************************************************************************
 * Main method
 *****************************************************************************/

int main (void)
{
  int32_t xoff;
  int32_t yoff;
  int32_t zoff;

  int8_t x;
  int8_t y;
  int8_t z;

  char buff[30];
  TIM_TIMERCFG_Type timerCfg;
  

  /* Initialize devices */

  // initialize timer
  TIM_ConfigStructInit(TIM_TIMER_MODE, &timerCfg);
  TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timerCfg);

  console_init();
  i2c0_pinConfig();


  /* Initialize I2C */
  I2C_Init(I2C_PORT, 100000);
  I2C_Cmd(I2C_PORT, ENABLE);

  acc_init();

  acc_read(&x, &y, &z);
  xoff = 0-x;
  yoff = 0-y;
  zoff = 64-z;

  while(1) {
  
    acc_read(&x, &y, &z);
    x = x+xoff;
    y = y+yoff;
    z = z+zoff;

    sprintf(buff, "x=%d, y=%d, z=%d\r\n", (int)x, (int)y, (int)z);
    console_sendString((uint8_t*)buff);

    TIM_Waitms(200);

  }
}



