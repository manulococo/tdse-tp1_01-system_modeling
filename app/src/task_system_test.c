/*
 * Copyright (c) 2023 Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * @file   : task_system_test.c
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version	v1.0.0
 */

/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"

/* Demo includes. */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes. */
#include "board.h"
#include "app.h"
#include "task_system_attribute.h"
#include "task_system_interface.h"

/********************** macros and definitions *******************************/
#define G_TASK_SYS_TEST_CNT_INI	0u

#define INDEX_INI	0u
#define INDEX_MAX	(sizeof(task_system_test_array)/sizeof(task_system_ev_t))

#define DELAY_INI	0u
#define DELAY_MAX	5000u

//typedef enum {TEST_0, TEST_1, TEST_2} test_x_t;
#define TASK_SYS_TEST_0 (0)
#define TASK_SYS_TEST_1 (1)
#define TASK_SYS_TEST_2 (2)

#define TASK_SYS_TEST_X (TASK_SYS_TEST_0)

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_task_system_test	= "Task System Test";
const char *p_task_system_test_	= "(System Modeling)";

#if (TASK_SYS_TEST_X == TASK_SYS_TEST_0)
/* Array of events to excite Task System */
const task_system_ev_t task_system_test_array[] = {EV_SYSTEM_AUTO_POSICION_ON, EV_SYSTEM_AUTO_POSICION_OFF,};
#endif

#if (TASK_SYS_TEST_X == TASK_SYS_TEST_1)
/* Array of events to excite Task System */
#endif

#if (TASK_SYS_TEST_X == TASK_SYS_TEST_2)
/* Array of events to excite Task System */
#endif

/********************** external data declaration ****************************/
uint32_t g_task_system_test_cnt;

/********************** external functions definition ************************/
void task_system_test_init(void *parameters)
{
	uint32_t array = TASK_SYS_TEST_X;

	/* Print out: Task Initialized */
	LOGGER_LOG("  %s is is running - %s", GET_NAME(task_system_test_update), p_task_system_test);
	LOGGER_LOG("  %s\r\n", p_task_system_test_);

	g_task_system_test_cnt = G_TASK_SYS_TEST_CNT_INI;

	/* Print out: Task execution counter */
	LOGGER_LOG("   %s = %d\r\n", GET_NAME(g_task_system_test_cnt), (int)g_task_system_test_cnt);

	/* Print out: Array of events to excite Task System */
	LOGGER_LOG("   %s = %d\r\n", GET_NAME(task_system_test_array), (int)array);
}

void task_system_test_update(void *parameters)
{
	static uint32_t index = INDEX_INI;
	uint32_t array = TASK_SYS_TEST_X;

	task_system_ev_t event;

	static uint32_t then = DELAY_INI;
	static uint32_t now  = DELAY_INI;

	/* Update Task System Counter */
	g_task_system_test_cnt++;

	/* Check the current tick */
	now = HAL_GetTick();
	if ((now - then) >= DELAY_MAX)
	{
		/* Only if the current tick is DELAY_MAX mS after the last */
		/* Reset then = now */
		then = now;

		/* Print out: Application Update */
		LOGGER_LOG("  %s is is running - %s\r\n", GET_NAME(task_system_test_update), p_task_system_test);

		/* Print out: Task execution counter */
		LOGGER_LOG("   %s = %d\r\n", GET_NAME(g_task_system_test_cnt), (int)g_task_system_test_cnt);

		/* Print out: Array of events to excite Task System */
		LOGGER_LOG("   %s = %d - %s = %d \r\n", GET_NAME(task_system_test_array), (int)array, GET_NAME(index), (int)index);

		/* Get the event to excite Task System. */
		event = task_system_test_array[index];
		put_event_task_system(event);

		if (INDEX_MAX == ++index)
			index = INDEX_INI;
	}
}

/********************** end of file ******************************************/
