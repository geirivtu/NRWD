#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define YIELDHOOK(x) PORTD &=~0x80; 

#define configUSE_PREEMPTION		1
#define configUSE_IDLE_HOOK			0
#define configCPU_CLOCK_HZ			( ( unsigned portLONG ) 8000000 )
#define configTICK_RATE_HZ			( ( portTickType ) 1000 )
#define configMAX_PRIORITIES		( ( unsigned portBASE_TYPE ) 4 )
#define configMINIMAL_STACK_SIZE	( ( unsigned portSHORT ) (85+15) )
#define configTOTAL_HEAP_SIZE		( (size_t ) ( 3500) )
#define configMAX_TASK_NAME_LEN		( 6 )
#define configUSE_TRACE_FACILITY	0
#define configUSE_16_BIT_TICKS		1
#define configIDLE_SHOULD_YIELD		1
#define configUSE_TICK_HOOK			0
#define configUSE_CO_ROUTINES		0
#define configUSE_MUTEXES			1

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet		0
#define INCLUDE_uxTaskPriorityGet		0
#define INCLUDE_vTaskDelete				0
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1


#endif /* FREERTOS_CONFIG_H */
