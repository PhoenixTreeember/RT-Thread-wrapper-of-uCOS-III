/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-29     Meco Man     the first verion
 */

/*
************************************************************************************************************************
*                                                      uC/OS-III
*                                                 The Real-Time Kernel
*
*                                  (c) Copyright 2009-2012; Micrium, Inc.; Weston, FL
*                           All rights reserved.  Protected by international copyright laws.
*
*                                                    CORE FUNCTIONS
*
* File    : OS_CORE.C
* By      : JJL
* Version : V3.03.00
*
* LICENSING TERMS:
* ---------------
*           uC/OS-III is provided in source form for FREE short-term evaluation, for educational use or 
*           for peaceful research.  If you plan or intend to use uC/OS-III in a commercial application/
*           product then, you need to contact Micrium to properly license uC/OS-III for its use in your 
*           application/product.   We provide ALL the source code for your convenience and to help you 
*           experience uC/OS-III.  The fact that the source is provided does NOT mean that you can use 
*           it commercially without paying a licensing fee.
*
*           Knowledge of the source code may NOT be used to develop a similar product.
*
*           Please help us continue to provide the embedded community with the finest software available.
*           Your honesty is greatly appreciated.
*
*           You can contact us at www.micrium.com, or by phone at +1 (954) 217-2036.
************************************************************************************************************************
*/

#include <os.h>

/*
RTT接管,以下函数不予实现
OSInit
OSStart
由于RTT没有相关接口，因此以下函数没有实现
OSSchedRoundRobinCfg
*/

/*
************************************************************************************************************************
*                                                      ENTER ISR
*
* Description: This function is used to notify uC/OS-III that you are about to service an interrupt service routine
*              (ISR).  This allows uC/OS-III to keep track of interrupt nesting and thus only perform rescheduling at
*              the last nested ISR.
*
* Arguments  : none
*
* Returns    : none
*
* Note(s)    : 1) This function MUST be called with interrupts already disabled
*
*              2) Your ISR can directly increment 'OSIntNestingCtr' without calling this function because OSIntNestingCtr has
*                 been declared 'global', the port is actually considered part of the OS and thus is allowed to access
*                 uC/OS-III variables.
*
*              3) You MUST still call OSIntExit() even though you increment 'OSIntNestingCtr' directly.
*
*              4) You MUST invoke OSIntEnter() and OSIntExit() in pair.  In other words, for every call to OSIntEnter()
*                 (or direct increment to OSIntNestingCtr) at the beginning of the ISR you MUST have a call to OSIntExit()
*                 at the end of the ISR.
*
*              5) You are allowed to nest interrupts up to 250 levels deep.
************************************************************************************************************************
*/
void  OSIntEnter (void)
{
    rt_interrupt_enter();
}

/*
************************************************************************************************************************
*                                                       EXIT ISR
*
* Description: This function is used to notify uC/OS-III that you have completed servicing an ISR.  When the last nested
*              ISR has completed, uC/OS-III will call the scheduler to determine whether a new, high-priority task, is
*              ready to run.
*
* Arguments  : none
*
* Returns    : none
*
* Note(s)    : 1) You MUST invoke OSIntEnter() and OSIntExit() in pair.  In other words, for every call to OSIntEnter()
*                 (or direct increment to OSIntNestingCtr) at the beginning of the ISR you MUST have a call to OSIntExit()
*                 at the end of the ISR.
*
*              2) Rescheduling is prevented when the scheduler is locked (see OSSchedLock())
************************************************************************************************************************
*/
void  OSIntExit (void)
{
    rt_interrupt_leave();
}

/*
************************************************************************************************************************
*                                                      SCHEDULER
*
* Description: This function is called by other uC/OS-III services to determine whether a new, high priority task has
*              been made ready to run.  This function is invoked by TASK level code and is not used to reschedule tasks
*              from ISRs (see OSIntExit() for ISR rescheduling).
*
* Arguments  : none
*
* Returns    : none
*
* Note(s)    : 1) Rescheduling is prevented when the scheduler is locked (see OSSchedLock())
************************************************************************************************************************
*/
void  OSSched (void)
{
    rt_schedule();
}

/*
************************************************************************************************************************
*                                                 PREVENT SCHEDULING
*
* Description: This function is used to prevent rescheduling from taking place.  This allows your application to prevent
*              context switches until you are ready to permit context switching.
*
* Arguments  : p_err     is a pointer to a variable that will receive an error code:
*
*                            OS_ERR_NONE                 The scheduler is locked
*                          - OS_ERR_LOCK_NESTING_OVF     If you attempted to nest call to this function > 250 levels
*                          - OS_ERR_OS_NOT_RUNNING       If uC/OS-III is not running yet.
*                            OS_ERR_SCHED_LOCK_ISR       If you called this function from an ISR.
*                        -------------说明-------------
*                            OS_ERR_XXXX        表示可以继续沿用uCOS-III原版的错误码
*                          - OS_ERR_XXXX        表示该错误码在本兼容层已经无法使用
*                          + OS_ERR_RT_XXXX     表示该错误码为新增的RTT专用错误码集
*                         应用层需要对API返回的错误码判断做出相应的修改
*
* Returns    : none
*
* Note(s)    : 1) You MUST invoke OSSchedLock() and OSSchedUnlock() in pair.  In other words, for every
*                 call to OSSchedLock() you MUST have a call to OSSchedUnlock().
************************************************************************************************************************
*/
void  OSSchedLock (OS_ERR  *p_err)
{
    /*检查是否在中断中运行*/
    if(rt_interrupt_get_nest()!=0)
    {
        *p_err = OS_ERR_SCHED_LOCK_ISR;
        return; 
    }  
    
    *p_err = OS_ERR_NONE;/*rt_enter_critical没有返回错误码*/    
    rt_enter_critical();
}

/*
************************************************************************************************************************
*                                                  ENABLE SCHEDULING
*
* Description: This function is used to re-allow rescheduling.
*
* Arguments  : p_err     is a pointer to a variable that will contain an error code returned by this function.
*
*                            OS_ERR_NONE
*                          - OS_ERR_OS_NOT_RUNNING       The scheduler has been enabled
*                            OS_ERR_SCHED_LOCKED         The scheduler is still locked, still nested
*                            OS_ERR_SCHED_NOT_LOCKED     The scheduler was not locked
*                            OS_ERR_SCHED_UNLOCK_ISR     If you called this function from an ISR.
*                        -------------说明-------------
*                            OS_ERR_XXXX        表示可以继续沿用uCOS-III原版的错误码
*                          - OS_ERR_XXXX        表示该错误码在本兼容层已经无法使用
*                          + OS_ERR_RT_XXXX     表示该错误码为新增的RTT专用错误码集
*                          应用层需要对API返回的错误码判断做出相应的修改
*
* Returns    : none
*
* Note(s)    : 1) You MUST invoke OSSchedLock() and OSSchedUnlock() in pair.  In other words, for every call to
*                 OSSchedLock() you MUST have a call to OSSchedUnlock().
************************************************************************************************************************
*/
void  OSSchedUnlock (OS_ERR  *p_err)
{
    /*检查是否在中断中运行*/
    if(rt_interrupt_get_nest()!=0)
    {
        *p_err = OS_ERR_SCHED_LOCK_ISR;
        return; 
    }
    
    /*检查调度器是否已经完全解锁*/
    if(rt_critical_level() == 0)
    {
        *p_err = OS_ERR_SCHED_NOT_LOCKED;
        return;         
    }
    
    *p_err = OS_ERR_NONE;/*rt_exit_critical没有返回错误码*/
    rt_exit_critical();
    
    /*检查调度器是否还有锁定嵌套*/
    if(rt_critical_level() >0)
    {
        *p_err = OS_ERR_SCHED_LOCKED;      
    }
}

/*
************************************************************************************************************************
*                                      CONFIGURE ROUND-ROBIN SCHEDULING PARAMETERS
*
* Description: This function is called to change the round-robin scheduling parameters.
*
* Arguments  : en                determines whether round-robin will be enabled (when DEF_EN) or not (when DEF_DIS)
*
*              dflt_time_quanta  default number of ticks between time slices.  0 means assumes OSCfg_TickRate_Hz / 10.
*
*              p_err             is a pointer to a variable that will contain an error code returned by this function.
*
*                                    OS_ERR_NONE    The call was successful
*
* Returns    : none
************************************************************************************************************************
*/
void  OSSchedRoundRobinCfg (CPU_BOOLEAN   en,
                            OS_TICK       dflt_time_quanta,
                            OS_ERR       *p_err)
{
    
}

/*
************************************************************************************************************************
*                                    YIELD CPU WHEN TASK NO LONGER NEEDS THE TIME SLICE
*
* Description: This function is called to give up the CPU when it is done executing before its time slice expires.
*
* Argument(s): p_err      is a pointer to a variable that will contain an error code returned by this function.
*
*                             OS_ERR_NONE                   The call was successful
*                           - OS_ERR_ROUND_ROBIN_1          Only 1 task at this priority, nothing to yield to
*                           - OS_ERR_ROUND_ROBIN_DISABLED   Round Robin is not enabled
*                             OS_ERR_SCHED_LOCKED           The scheduler has been locked
*                             OS_ERR_YIELD_ISR              Can't be called from an ISR
*                         -------------说明-------------
*                             OS_ERR_XXXX        表示可以继续沿用uCOS-III原版的错误码
*                           - OS_ERR_XXXX        表示该错误码在本兼容层已经无法使用
*                           + OS_ERR_RT_XXXX     表示该错误码为新增的RTT专用错误码集
*                           应用层需要对API返回的错误码判断做出相应的修改
*
* Returns    : none
*
* Note(s)    : 1) This function MUST be called from a task.
************************************************************************************************************************
*/
void  OSSchedRoundRobinYield (OS_ERR  *p_err)
{
    rt_err_t rt_err;
    
    /*检查是否在中断中运行*/
    if(rt_interrupt_get_nest()!=0)
    {
        *p_err = OS_ERR_YIELD_ISR;
        return; 
    }
    
    /*检查调度器是否被锁*/
    if(rt_critical_level() > 0)
    {
        *p_err = OS_ERR_SCHED_LOCKED;
        return;         
    }
    
    rt_err = rt_thread_yield();
    *p_err = _err_rtt_to_ucosiii(rt_err); 
}

/*
************************************************************************************************************************
*                                                    GET VERSION
*
* Description: This function is used to return the version number of uC/OS-III.  The returned value corresponds to
*              uC/OS-III's version number multiplied by 10000.  In other words, version 3.01.02 would be returned as 30102.
*
* Arguments  : p_err   is a pointer to a variable that will receive an error code.  However, OSVersion() set this
*                      variable to
*
*                         OS_ERR_NONE
*
* Returns    : The version number of uC/OS-III multiplied by 10000.
************************************************************************************************************************
*/
CPU_INT16U  OSVersion (OS_ERR  *p_err)
{
    *p_err = OS_ERR_NONE;
    return RTTHREAD_VERSION;
}
