/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#define portCHAR		char
#define portFLOAT		float
#define portDOUBLE		double
#define portLONG		long
#define portSHORT		short
#define portSTACK_TYPE	uint32_t
#define portBASE_TYPE	long

typedef portSTACK_TYPE StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
typedef uint16_t TickType_t;
#define portMAX_DELAY ( TickType_t ) 0xffff
#else
typedef uint32_t TickType_t;
#define portMAX_DELAY ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
not need to be guarded with a critical section. */
#define portTICK_TYPE_IS_ATOMIC 1
#endif
/*-----------------------------------------------------------*/

/* MPU specific constants. */
#define portUSING_MPU_WRAPPERS		1
#define portPRIVILEGE_BIT			( 0x80000000UL )

#define portMPU_REGION_READ_WRITE				( 0x03UL << 24UL )
#define portMPU_REGION_PRIVILEGED_READ_ONLY		( 0x05UL << 24UL )
#define portMPU_REGION_READ_ONLY				( 0x06UL << 24UL )
#define portMPU_REGION_PRIVILEGED_READ_WRITE	( 0x01UL << 24UL )
#define portMPU_REGION_CACHEABLE_BUFFERABLE		( 0x07UL << 16UL )
#define portMPU_REGION_EXECUTE_NEVER			( 0x01UL << 28UL )

#define portUNPRIVILEGED_FLASH_REGION		( 0UL )
#define portPRIVILEGED_FLASH_REGION			( 1UL )
#define portPRIVILEGED_RAM_REGION			( 2UL )
#define portGENERAL_PERIPHERALS_REGION		( 3UL )
#define portSTACK_REGION					( 4UL )
#define portFIRST_CONFIGURABLE_REGION	    ( 5UL )
#define portLAST_CONFIGURABLE_REGION		( 7UL )
#define portNUM_CONFIGURABLE_REGIONS		( ( portLAST_CONFIGURABLE_REGION - portFIRST_CONFIGURABLE_REGION ) + 1 )
#define portTOTAL_NUM_REGIONS				( portNUM_CONFIGURABLE_REGIONS + 1 ) /* Plus one to make space for the stack region. */

void vPortSwitchToUserMode( void );
#define portSWITCH_TO_USER_MODE()	vPortSwitchToUserMode()

typedef struct MPU_REGION_REGISTERS {
	uint32_t ulRegionBaseAddress;
	uint32_t ulRegionAttribute;
} xMPU_REGION_REGISTERS;

/* Plus 1 to create space for the stack region. */
typedef struct MPU_SETTINGS {
	xMPU_REGION_REGISTERS xRegion[ portTOTAL_NUM_REGIONS ];
} xMPU_SETTINGS;

/* Architecture specifics. */
#define portSTACK_GROWTH			( -1 )
#define portTICK_PERIOD_MS			( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT			8

/* Constants used with memory barrier intrinsics. */
#define portSY_FULL_READ_WRITE		( 15 )

/*-----------------------------------------------------------*/

/* SVC numbers for various services. */
#define portSVC_START_SCHEDULER				0
#define portSVC_YIELD						1
#define portSVC_RAISE_PRIVILEGE				2

/* Scheduler utilities. */

#define portYIELD()				__asm{ SVC portSVC_YIELD }
#define portYIELD_WITHIN_API() 													\
	{																				\
		/* Set a PendSV to request a context switch. */								\
		portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;								\
		\
		/* Barriers are normally not required but do ensure the code is completely	\
		within the specified behaviour for the architecture. */						\
		__dsb( portSY_FULL_READ_WRITE );											\
		__isb( portSY_FULL_READ_WRITE );											\
	}
/*-----------------------------------------------------------*/

#define portNVIC_INT_CTRL_REG		( * ( ( volatile uint32_t * ) 0xe000ed04 ) )
#define portNVIC_PENDSVSET_BIT		( 1UL << 28UL )
#define portEND_SWITCHING_ISR( xSwitchRequired ) if( xSwitchRequired ) portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET
#define portYIELD_FROM_ISR( x ) portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
extern void vPortEnterCritical( void );
extern void vPortExitCritical( void );

#define portDISABLE_INTERRUPTS()				vPortRaiseBASEPRI()
#define portENABLE_INTERRUPTS()					vPortSetBASEPRI(0)
#define portENTER_CRITICAL()					vPortEnterCritical()
#define portEXIT_CRITICAL()						vPortExitCritical()
#define portSET_INTERRUPT_MASK_FROM_ISR()		ulPortRaiseBASEPRI()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x)	vPortSetBASEPRI(x)

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#endif

#if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
#if( configMAX_PRIORITIES > 32 )
#error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
#endif

/* Store/clear the ready priorities in a bit map. */
#define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
#define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

#define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31UL - ( uint32_t ) __clz( ( uxReadyPriorities ) ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
not necessary for to use this port.  They are defined so the common demo files
(which build with all the ports) will build. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )
/*-----------------------------------------------------------*/

#ifdef configASSERT
void vPortValidateInterruptPriority( void );
#define portASSERT_IF_INTERRUPT_PRIORITY_INVALID() 	vPortValidateInterruptPriority()
#endif

/* portNOP() is not required by this port. */
#define portNOP()

#define portINLINE __inline

#ifndef portFORCE_INLINE
#define portFORCE_INLINE __forceinline
#endif

/*-----------------------------------------------------------*/

static portFORCE_INLINE void vPortSetBASEPRI( uint32_t ulBASEPRI ) {
	__asm {
		/* Barrier instructions are not used as this function is only used to
		lower the BASEPRI value. */
		msr basepri, ulBASEPRI
	}
}
/*-----------------------------------------------------------*/

static portFORCE_INLINE void vPortRaiseBASEPRI( void ) {
	uint32_t ulNewBASEPRI = configMAX_SYSCALL_INTERRUPT_PRIORITY;

	__asm {
		/* Set BASEPRI to the max syscall priority to effect a critical
		section. */
		msr basepri, ulNewBASEPRI
		dsb
		isb
	}
}
/*-----------------------------------------------------------*/

static portFORCE_INLINE void vPortClearBASEPRIFromISR( void ) {
	__asm {
		/* Set BASEPRI to 0 so no interrupts are masked.  This function is only
		used to lower the mask in an interrupt, so memory barriers are not
		used. */
		msr basepri, #0
	}
}
/*-----------------------------------------------------------*/

static portFORCE_INLINE uint32_t ulPortRaiseBASEPRI( void ) {
	uint32_t ulReturn, ulNewBASEPRI = configMAX_SYSCALL_INTERRUPT_PRIORITY;

	__asm {
		/* Set BASEPRI to the max syscall priority to effect a critical
		section. */
		mrs ulReturn, basepri
		msr basepri, ulNewBASEPRI
		dsb
		isb
	}

	return ulReturn;
}
/*-----------------------------------------------------------*/

static portFORCE_INLINE BaseType_t xPortIsInsideInterrupt( void ) {
	uint32_t ulCurrentInterrupt;
	BaseType_t xReturn;

	/* Obtain the number of the currently executing interrupt. */
	__asm {
		mrs ulCurrentInterrupt, ipsr
	}

	if( ulCurrentInterrupt == 0 ) {
		xReturn = pdFALSE;
	} else {
		xReturn = pdTRUE;
	}

	return xReturn;
}
/*-----------------------------------------------------------*/

/* Set the privilege level to user mode if xRunningPrivileged is false. */
portFORCE_INLINE static void vPortResetPrivilege( BaseType_t xRunningPrivileged ) {
	uint32_t ulReg;

	if( xRunningPrivileged != pdTRUE ) {
		__asm {
			mrs ulReg, control
			orr ulReg, #1
			msr control, ulReg
		}
	}
}
/*-----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */

