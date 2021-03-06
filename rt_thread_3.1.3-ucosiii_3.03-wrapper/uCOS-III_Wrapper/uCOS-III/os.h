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
* File    : OS.H
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
* Note(s) : (1) Assumes the following versions (or more recent) of software modules are included in the project build:
*
*               (a) uC/LIB V1.36.01
*               (b) uC/CPU V1.29.00
************************************************************************************************************************
*/
#ifndef   OS_H
#define   OS_H

/*
************************************************************************************************************************
*                                               uC/OS-III VERSION NUMBER
************************************************************************************************************************
*/

#define  OS_VERSION  30300u                       /* Version of uC/OS-III (Vx.yy.zz mult. by 10000)                   */

/*
************************************************************************************************************************
*                                                 INCLUDE HEADER FILES
************************************************************************************************************************
*/
#include <rtthread.h>
#include <os_type.h>
#include <os_cfg.h>
#include <lib_def.h>


/*
************************************************************************************************************************
************************************************************************************************************************
*                                                   # D E F I N E S
************************************************************************************************************************
************************************************************************************************************************
*/

/*
========================================================================================================================
*                                           Possible values for 'opt' argument
========================================================================================================================
*/

#define  OS_OPT_NONE                         (OS_OPT)(0x0000u)

/*
------------------------------------------------------------------------------------------------------------------------
*                                                    DELETE OPTIONS
------------------------------------------------------------------------------------------------------------------------
*/

#define  OS_OPT_DEL_NO_PEND                  (OS_OPT)(0x0000u)
#define  OS_OPT_DEL_ALWAYS                   (OS_OPT)(0x0001u)

/*
------------------------------------------------------------------------------------------------------------------------
*                                                     PEND OPTIONS
------------------------------------------------------------------------------------------------------------------------
*/

#define  OS_OPT_PEND_FLAG_MASK               (OS_OPT)(0x000Fu)
#define  OS_OPT_PEND_FLAG_CLR_ALL            (OS_OPT)(0x0001u)  /* Wait for ALL    the bits specified to be CLR       */
#define  OS_OPT_PEND_FLAG_CLR_AND            (OS_OPT)(0x0001u)

#define  OS_OPT_PEND_FLAG_CLR_ANY            (OS_OPT)(0x0002u)  /* Wait for ANY of the bits specified to be CLR       */
#define  OS_OPT_PEND_FLAG_CLR_OR             (OS_OPT)(0x0002u)

#define  OS_OPT_PEND_FLAG_SET_ALL            (OS_OPT)(0x0004u)  /* Wait for ALL    the bits specified to be SET       */
#define  OS_OPT_PEND_FLAG_SET_AND            (OS_OPT)(0x0004u)

#define  OS_OPT_PEND_FLAG_SET_ANY            (OS_OPT)(0x0008u)  /* Wait for ANY of the bits specified to be SET       */
#define  OS_OPT_PEND_FLAG_SET_OR             (OS_OPT)(0x0008u)

#define  OS_OPT_PEND_FLAG_CONSUME            (OS_OPT)(0x0100u)  /* Consume the flags if condition(s) satisfied        */


#define  OS_OPT_PEND_BLOCKING                (OS_OPT)(0x0000u)
#define  OS_OPT_PEND_NON_BLOCKING            (OS_OPT)(0x8000u)

/*
------------------------------------------------------------------------------------------------------------------------
*                                                     POST OPTIONS
------------------------------------------------------------------------------------------------------------------------
*/

#define  OS_OPT_POST_NONE                    (OS_OPT)(0x0000u)

#define  OS_OPT_POST_FLAG_SET                (OS_OPT)(0x0000u)
#define  OS_OPT_POST_FLAG_CLR                (OS_OPT)(0x0001u)

#define  OS_OPT_POST_FIFO                    (OS_OPT)(0x0000u)  /* Default is to post FIFO                            */
#define  OS_OPT_POST_LIFO                    (OS_OPT)(0x0010u)  /* Post to highest priority task waiting              */
#define  OS_OPT_POST_1                       (OS_OPT)(0x0000u)  /* Post message to highest priority task waiting      */
#define  OS_OPT_POST_ALL                     (OS_OPT)(0x0200u)  /* Broadcast message to ALL tasks waiting             */

#define  OS_OPT_POST_NO_SCHED                (OS_OPT)(0x8000u)  /* Do not call the scheduler if this is selected      */

/*
------------------------------------------------------------------------------------------------------------------------
*                                                     TASK OPTIONS
------------------------------------------------------------------------------------------------------------------------
*/

#define  OS_OPT_TASK_NONE                    (OS_OPT)(0x0000u)  /* No option selected                                 */
#define  OS_OPT_TASK_STK_CHK                 (OS_OPT)(0x0001u)  /* Enable stack checking for the task                 */
#define  OS_OPT_TASK_STK_CLR                 (OS_OPT)(0x0002u)  /* Clear the stack when the task is create            */
#define  OS_OPT_TASK_SAVE_FP                 (OS_OPT)(0x0004u)  /* Save the contents of any floating-point registers  */
#define  OS_OPT_TASK_NO_TLS                  (OS_OPT)(0x0008u)  /* Specifies the task DOES NOT require TLS support    */

/*
------------------------------------------------------------------------------------------------------------------------
*                                                     TIME OPTIONS
------------------------------------------------------------------------------------------------------------------------
*/

#define  OS_OPT_TIME_DLY                             DEF_BIT_NONE
#define  OS_OPT_TIME_TIMEOUT                ((OS_OPT)DEF_BIT_01)
#define  OS_OPT_TIME_MATCH                  ((OS_OPT)DEF_BIT_02)
#define  OS_OPT_TIME_PERIODIC               ((OS_OPT)DEF_BIT_03)

#define  OS_OPT_TIME_HMSM_STRICT            ((OS_OPT)DEF_BIT_NONE)
#define  OS_OPT_TIME_HMSM_NON_STRICT        ((OS_OPT)DEF_BIT_04)

#define  OS_OPT_TIME_MASK                   ((OS_OPT)(OS_OPT_TIME_DLY      | \
                                                      OS_OPT_TIME_TIMEOUT  | \
                                                      OS_OPT_TIME_PERIODIC | \
                                                      OS_OPT_TIME_MATCH))

#define  OS_OPT_TIME_OPTS_MASK                       (OS_OPT_TIME_DLY            | \
                                                      OS_OPT_TIME_TIMEOUT        | \
                                                      OS_OPT_TIME_PERIODIC       | \
                                                      OS_OPT_TIME_MATCH          | \
                                                      OS_OPT_TIME_HMSM_NON_STRICT)

/*
------------------------------------------------------------------------------------------------------------------------
*                                                    TIMER OPTIONS
------------------------------------------------------------------------------------------------------------------------
*/

#define  OS_OPT_TMR_NONE                          (OS_OPT)(0u)  /* No option selected                                 */

#define  OS_OPT_TMR_ONE_SHOT                      (OS_OPT)(1u)  /* Timer will not auto restart when it expires        */
#define  OS_OPT_TMR_PERIODIC                      (OS_OPT)(2u)  /* Timer will     auto restart when it expires        */

#define  OS_OPT_TMR_CALLBACK                      (OS_OPT)(3u)  /* OSTmrStop() option to call 'callback' w/ timer arg */
#define  OS_OPT_TMR_CALLBACK_ARG                  (OS_OPT)(4u)  /* OSTmrStop() option to call 'callback' w/ new   arg */


/*
************************************************************************************************************************
************************************************************************************************************************
*                                                E N U M E R A T I O N S
************************************************************************************************************************
************************************************************************************************************************
*/
/*
------------------------------------------------------------------------------------------------------------------------
*                                                      ERROR CODES
*
* Note(s) : 请勿随意打开注释掉的枚举体成员,这些注释掉的成员会在迁移时编译报错,用以提醒用户这些错误代码在兼容层已经不可用
------------------------------------------------------------------------------------------------------------------------
*/
typedef  enum  os_err {
    OS_ERR_NONE                      =     0u,

    OS_ERR_A                         = 10000u,
//    OS_ERR_ACCEPT_ISR                = 10001u,

    OS_ERR_B                         = 11000u,

    OS_ERR_C                         = 12000u,
    OS_ERR_CREATE_ISR                = 12001u,

    OS_ERR_D                         = 13000u,
    OS_ERR_DEL_ISR                   = 13001u,

    OS_ERR_E                         = 14000u,

    OS_ERR_F                         = 15000u,
//    OS_ERR_FATAL_RETURN              = 15001u,

//    OS_ERR_FLAG_GRP_DEPLETED         = 15101u,
//    OS_ERR_FLAG_NOT_RDY              = 15102u,
//    OS_ERR_FLAG_PEND_OPT             = 15103u,
//    OS_ERR_FLUSH_ISR                 = 15104u,

    OS_ERR_G                         = 16000u,

    OS_ERR_H                         = 17000u,

    OS_ERR_I                         = 18000u,
//    OS_ERR_ILLEGAL_CREATE_RUN_TIME   = 18001u,
//    OS_ERR_INT_Q                     = 18002u,
//    OS_ERR_INT_Q_FULL                = 18003u,
//    OS_ERR_INT_Q_SIZE                = 18004u,
//    OS_ERR_INT_Q_STK_INVALID         = 18005u,
//    OS_ERR_INT_Q_STK_SIZE_INVALID    = 18006u,

    OS_ERR_J                         = 19000u,

    OS_ERR_K                         = 20000u,

    OS_ERR_L                         = 21000u,
//    OS_ERR_LOCK_NESTING_OVF          = 21001u,

    OS_ERR_M                         = 22000u,

//    OS_ERR_MEM_CREATE_ISR            = 22201u,
    OS_ERR_MEM_FULL                  = 22202u,
//    OS_ERR_MEM_INVALID_P_ADDR        = 22203u,
//    OS_ERR_MEM_INVALID_BLKS          = 22204u,
//    OS_ERR_MEM_INVALID_PART          = 22205u,
//    OS_ERR_MEM_INVALID_P_BLK         = 22206u,
//    OS_ERR_MEM_INVALID_P_MEM         = 22207u,
//    OS_ERR_MEM_INVALID_P_DATA        = 22208u,
//    OS_ERR_MEM_INVALID_SIZE          = 22209u,
//    OS_ERR_MEM_NO_FREE_BLKS          = 22210u,

//    OS_ERR_MSG_POOL_EMPTY            = 22301u,
//    OS_ERR_MSG_POOL_NULL_PTR         = 22302u,

    OS_ERR_MUTEX_NOT_OWNER           = 22401u,
//    OS_ERR_MUTEX_OWNER               = 22402u,
//    OS_ERR_MUTEX_NESTING             = 22403u,

    OS_ERR_N                         = 23000u,
    OS_ERR_NAME                      = 23001u,
//    OS_ERR_NO_MORE_ID_AVAIL          = 23002u,

    OS_ERR_O                         = 24000u,
    OS_ERR_OBJ_CREATED               = 24001u,
//    OS_ERR_OBJ_DEL                   = 24002u,
    OS_ERR_OBJ_PTR_NULL              = 24003u,
    OS_ERR_OBJ_TYPE                  = 24004u,

    OS_ERR_OPT_INVALID               = 24101u,

//    OS_ERR_OS_NOT_RUNNING            = 24201u,
//    OS_ERR_OS_RUNNING                = 24202u,

    OS_ERR_P                         = 25000u,
//    OS_ERR_PEND_ABORT                = 25001u,
//    OS_ERR_PEND_ABORT_ISR            = 25002u,
//    OS_ERR_PEND_ABORT_NONE           = 25003u,
//    OS_ERR_PEND_ABORT_SELF           = 25004u,
//    OS_ERR_PEND_DEL                  = 25005u,
    OS_ERR_PEND_ISR                  = 25006u,
//    OS_ERR_PEND_LOCKED               = 25007u,
//    OS_ERR_PEND_WOULD_BLOCK          = 25008u,

//    OS_ERR_POST_NULL_PTR             = 25101u,
    OS_ERR_POST_ISR                  = 25102u,

//    OS_ERR_PRIO_EXIST                = 25201u,
//    OS_ERR_PRIO                      = 25202u,
    OS_ERR_PRIO_INVALID              = 25203u,

    OS_ERR_PTR_INVALID               = 25301u,

    OS_ERR_Q                         = 26000u,
//    OS_ERR_Q_FULL                    = 26001u,
//    OS_ERR_Q_EMPTY                   = 26002u,
    OS_ERR_Q_MAX                     = 26003u,
    OS_ERR_Q_SIZE                    = 26004u,

    OS_ERR_R                         = 27000u,
//    OS_ERR_REG_ID_INVALID            = 27001u,
//    OS_ERR_ROUND_ROBIN_1             = 27002u,
//    OS_ERR_ROUND_ROBIN_DISABLED      = 27003u,

    OS_ERR_S                         = 28000u,
//    OS_ERR_SCHED_INVALID_TIME_SLICE  = 28001u,
    OS_ERR_SCHED_LOCK_ISR            = 28002u,
    OS_ERR_SCHED_LOCKED              = 28003u,
    OS_ERR_SCHED_NOT_LOCKED          = 28004u,
    OS_ERR_SCHED_UNLOCK_ISR          = 28005u,

//    OS_ERR_SEM_OVF                   = 28101u,
//    OS_ERR_SET_ISR                   = 28102u,

//    OS_ERR_STAT_RESET_ISR            = 28201u,
//    OS_ERR_STAT_PRIO_INVALID         = 28202u,
//    OS_ERR_STAT_STK_INVALID          = 28203u,
//    OS_ERR_STAT_STK_SIZE_INVALID     = 28204u,
//    OS_ERR_STATE_INVALID             = 28205u,
//    OS_ERR_STATUS_INVALID            = 28206u,
    OS_ERR_STK_INVALID               = 28207u,
    OS_ERR_STK_SIZE_INVALID          = 28208u,
//    OS_ERR_STK_LIMIT_INVALID         = 28209u,

    OS_ERR_T                         = 29000u,
//    OS_ERR_TASK_CHANGE_PRIO_ISR      = 29001u,
    OS_ERR_TASK_CREATE_ISR           = 29002u,
//    OS_ERR_TASK_DEL                  = 29003u,
//    OS_ERR_TASK_DEL_IDLE             = 29004u,
//    OS_ERR_TASK_DEL_INVALID          = 29005u,
    OS_ERR_TASK_DEL_ISR              = 29006u,
    OS_ERR_TASK_INVALID              = 29007u,
//    OS_ERR_TASK_NO_MORE_TCB          = 29008u,
//    OS_ERR_TASK_NOT_DLY              = 29009u,
    OS_ERR_TASK_NOT_EXIST            = 29010u,
    OS_ERR_TASK_NOT_SUSPENDED        = 29011u,
//    OS_ERR_TASK_OPT                  = 29012u,
    OS_ERR_TASK_RESUME_ISR           = 29013u,
//    OS_ERR_TASK_RESUME_PRIO          = 29014u,
    OS_ERR_TASK_RESUME_SELF          = 29015u,
//    OS_ERR_TASK_RUNNING              = 29016u,
    OS_ERR_TASK_STK_CHK_ISR          = 29017u,
//    OS_ERR_TASK_SUSPENDED            = 29018u,
//    OS_ERR_TASK_SUSPEND_IDLE         = 29019u,
//    OS_ERR_TASK_SUSPEND_INT_HANDLER  = 29020u,
    OS_ERR_TASK_SUSPEND_ISR          = 29021u,
//    OS_ERR_TASK_SUSPEND_PRIO         = 29022u,
//    OS_ERR_TASK_WAITING              = 29023u,

    OS_ERR_TCB_INVALID               = 29101u,

//    OS_ERR_TLS_ID_INVALID            = 29120u,
//    OS_ERR_TLS_ISR                   = 29121u,
//    OS_ERR_TLS_NO_MORE_AVAIL         = 29122u,
//    OS_ERR_TLS_NOT_EN                = 29123u,
//    OS_ERR_TLS_DESTRUCT_ASSIGNED     = 29124u,

//    OS_ERR_TICK_PRIO_INVALID         = 29201u,
//    OS_ERR_TICK_STK_INVALID          = 29202u,
//    OS_ERR_TICK_STK_SIZE_INVALID     = 29203u,
//    OS_ERR_TICK_WHEEL_SIZE           = 29204u,

    OS_ERR_TIME_DLY_ISR              = 29301u,
//    OS_ERR_TIME_DLY_RESUME_ISR       = 29302u,
//    OS_ERR_TIME_GET_ISR              = 29303u,
    OS_ERR_TIME_INVALID_HOURS        = 29304u,
    OS_ERR_TIME_INVALID_MINUTES      = 29305u,
    OS_ERR_TIME_INVALID_SECONDS      = 29306u,
    OS_ERR_TIME_INVALID_MILLISECONDS = 29307u,
//    OS_ERR_TIME_NOT_DLY              = 29308u,
//    OS_ERR_TIME_SET_ISR              = 29309u,
    OS_ERR_TIME_ZERO_DLY             = 29310u,

    OS_ERR_TIMEOUT                   = 29401u,

//    OS_ERR_TMR_INACTIVE              = 29501u,
//    OS_ERR_TMR_INVALID_DEST          = 29502u,
    OS_ERR_TMR_INVALID_DLY           = 29503u,
    OS_ERR_TMR_INVALID_PERIOD        = 29504u,
//    OS_ERR_TMR_INVALID_STATE         = 29505u,
    OS_ERR_TMR_INVALID               = 29506u,
    OS_ERR_TMR_ISR                   = 29507u,
//    OS_ERR_TMR_NO_CALLBACK           = 29508u,
//    OS_ERR_TMR_NON_AVAIL             = 29509u,
//    OS_ERR_TMR_PRIO_INVALID          = 29510u,
//    OS_ERR_TMR_STK_INVALID           = 29511u,
//    OS_ERR_TMR_STK_SIZE_INVALID      = 29512u,
    OS_ERR_TMR_STOPPED               = 29513u,

    OS_ERR_U                         = 30000u,

    OS_ERR_V                         = 31000u,

    OS_ERR_W                         = 32000u,

    OS_ERR_X                         = 33000u,

    OS_ERR_Y                         = 34000u,
    OS_ERR_YIELD_ISR                 = 34001u,

    OS_ERR_Z                         = 35000u,
    
    /*
    由于uCOS-III的错误码分类较细，而RTT的错误码分类较为笼统，
    以下RTT错误码使用uCOS-III的错误码很难准确描述
    因此将针对RTT的错误码重新定义(新增)uCOS-III的错误码
    */    
    OS_ERR_RT                        = 36000u,/* RTT专用错误码集 */
    OS_ERR_RT_ERROR                  = 36001u,/* 普通错误     */
    OS_ERR_RT_EEMPTY                 = 36002u,/* 无资源       */
    OS_ERR_RT_ENOMEM                 = 36003u,/* 无内存       */
    OS_ERR_RT_ENOSYS                 = 36004u,/* 系统不支持   */
    OS_ERR_RT_EBUSY                  = 36005u,/* 系统忙       */
    OS_ERR_RT_EIO                    = 36006u,/* IO 错误      */
    OS_ERR_RT_EINTR                  = 36007u /* 中断系统调用 */

} OS_ERR;


/*
************************************************************************************************************************
************************************************************************************************************************
*                                          D A T A   S T R U C T U R E S
************************************************************************************************************************
************************************************************************************************************************
*/
/*
------------------------------------------------------------------------------------------------------------------------
*                                                    MESSAGE QUEUES
*
* Note(s) : RTT的消息队列与uCOS的消息队列实现机理完全不同：
*           ·RTT的消息队列是采用数据拷贝的方式，直接完成数据的传递
*           ·uCOS的消息队列采用传递指针的零拷贝方式
*           虽然RTT的邮箱也采用传递指针的方式，但是没有提供urgent函数用于LIFO发送消息,因此采用RTT的消息队列实现
*           将uCOS传递的数据指针和数据大小作为RTT消息队列的数据段封装到RTT的消息队列中,因此需要构建ucos_msg_t结构体
*           并重新构建os_q结构体
------------------------------------------------------------------------------------------------------------------------
*/
typedef  struct 
{
    rt_uint8_t *data_ptr;/*uCOS-III消息数据指针*/
    rt_uint32_t data_size;/*uCOS-III消息数据长度*/
}ucos_msg_t;/*uCOS消息段*/

struct os_q
{
    struct  rt_messagequeue rt_msg;
    void    *p_pool;
    ucos_msg_t ucos_msg;
};


/*
************************************************************************************************************************
************************************************************************************************************************
*                                                  D A T A   T Y P E S
************************************************************************************************************************
************************************************************************************************************************
*/
typedef  struct  rt_event            OS_FLAG_GRP;

typedef  struct  os_q                OS_Q;

typedef  struct  rt_mutex            OS_MUTEX;

typedef  struct  rt_semaphore        OS_SEM;

/*注意：RTT的定时器回调函数比uCOS-III的少了一个参数！*/
//typedef  void                      (*OS_TMR_CALLBACK_PTR)(void *p_tmr, void *p_arg);
typedef  void                        (*OS_TMR_CALLBACK_PTR)(void *parameter);
typedef  struct  rt_timer            OS_TMR;

typedef  void                        (*OS_TASK_PTR)        (void *parameter);
typedef  struct  rt_thread           OS_TCB;


/*
************************************************************************************************************************
************************************************************************************************************************
*                                        F U N C T I O N   P R O T O T Y P E S
************************************************************************************************************************
************************************************************************************************************************
*/
/* ================================================================================================================== */
/*                                                      DEBUG                                                     */
/* ================================================================================================================== */

OS_ERR        _err_rtt_to_ucosiii       (rt_err_t rt_err);


/* ================================================================================================================== */
/*                                                    EVENT FLAGS                                                     */
/* ================================================================================================================== */

void          OSFlagCreate              (OS_FLAG_GRP           *p_grp,
                                         CPU_CHAR              *p_name,
                                         OS_FLAGS               flags,
                                         OS_ERR                *p_err);

OS_OBJ_QTY    OSFlagDel                 (OS_FLAG_GRP           *p_grp,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);

OS_FLAGS      OSFlagPend                (OS_FLAG_GRP           *p_grp,
                                         OS_FLAGS               flags,
                                         OS_TICK                timeout,
                                         OS_OPT                 opt,
                                         CPU_TS                *p_ts,
                                         OS_ERR                *p_err);

#if OS_CFG_FLAG_PEND_ABORT_EN > 0u
OS_OBJ_QTY    OSFlagPendAbort           (OS_FLAG_GRP           *p_grp,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);
#endif

OS_FLAGS      OSFlagPendGetFlagsRdy     (OS_ERR                *p_err);

OS_FLAGS      OSFlagPost                (OS_FLAG_GRP           *p_grp,
                                         OS_FLAGS               flags,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);


/* ================================================================================================================== */
/*                                                 TASK MANAGEMENT                                                    */
/* ================================================================================================================== */

void          OSTaskChangePrio          (OS_TCB                *p_tcb,
                                         OS_PRIO                prio_new,
                                         OS_ERR                *p_err);

void          OSTaskCreate              (OS_TCB                *p_tcb,
                                         CPU_CHAR              *p_name,
                                         OS_TASK_PTR            p_task,
                                         void                  *p_arg,
                                         OS_PRIO                prio,
                                         CPU_STK               *p_stk_base,
                                         CPU_STK_SIZE           stk_limit,
                                         CPU_STK_SIZE           stk_size,
                                         OS_MSG_QTY             q_size,
                                         OS_TICK                time_quanta,
                                         void                  *p_ext,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);

void          OSTaskDel                 (OS_TCB                *p_tcb,
                                         OS_ERR                *p_err);

void          OSTaskResume              (OS_TCB                *p_tcb,
                                         OS_ERR                *p_err);

void          OSTaskSuspend             (OS_TCB                *p_tcb,
                                         OS_ERR                *p_err);

void          OSTaskStkChk              (OS_TCB                *p_tcb,
                                         CPU_STK_SIZE          *p_free,
                                         CPU_STK_SIZE          *p_used,
                                         CPU_STK_SIZE          *p_used_max,
                                         OS_ERR                *p_err);

void          OSTaskTimeQuantaSet       (OS_TCB                *p_tcb,
                                         OS_TICK                time_quanta,
                                         OS_ERR                *p_err);


/* ================================================================================================================== */
/*                                             MUTUAL EXCLUSION SEMAPHORES                                            */
/* ================================================================================================================== */

void          OSMutexCreate             (OS_MUTEX              *p_mutex,
                                         CPU_CHAR              *p_name,
                                         OS_ERR                *p_err);

OS_OBJ_QTY    OSMutexDel                (OS_MUTEX              *p_mutex,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);

void          OSMutexPend               (OS_MUTEX              *p_mutex,
                                         OS_TICK                timeout,
                                         OS_OPT                 opt,
                                         CPU_TS                *p_ts,
                                         OS_ERR                *p_err);

#if OS_CFG_MUTEX_PEND_ABORT_EN > 0u
OS_OBJ_QTY    OSMutexPendAbort          (OS_MUTEX              *p_mutex,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);
#endif

void          OSMutexPost               (OS_MUTEX              *p_mutex,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);


/* ================================================================================================================== */
/*                                                   MESSAGE QUEUES                                                   */
/* ================================================================================================================== */

void          OSQCreate                 (OS_Q                  *p_q,
                                         CPU_CHAR              *p_name,
                                         OS_MSG_QTY             max_qty,
                                         OS_ERR                *p_err);

OS_OBJ_QTY    OSQDel                    (OS_Q                  *p_q,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);

#if OS_CFG_Q_FLUSH_EN > 0u
OS_MSG_QTY    OSQFlush                  (OS_Q                  *p_q,
                                         OS_ERR                *p_err);
#endif

void         *OSQPend                   (OS_Q                  *p_q,
                                         OS_TICK                timeout,
                                         OS_OPT                 opt,
                                         OS_MSG_SIZE           *p_msg_size,
                                         CPU_TS                *p_ts,
                                         OS_ERR                *p_err);

#if OS_CFG_Q_PEND_ABORT_EN > 0u
OS_OBJ_QTY    OSQPendAbort              (OS_Q                  *p_q,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);
#endif

void          OSQPost                   (OS_Q                  *p_q,
                                         void                  *p_void,
                                         OS_MSG_SIZE            msg_size,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);
                                         
                            
/* ================================================================================================================== */
/*                                                     SEMAPHORES                                                     */
/* ================================================================================================================== */

void          OSSemCreate               (OS_SEM                *p_sem,
                                         CPU_CHAR              *p_name,
                                         OS_SEM_CTR             cnt,
                                         OS_ERR                *p_err);

OS_OBJ_QTY    OSSemDel                  (OS_SEM                *p_sem,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);

OS_SEM_CTR    OSSemPend                 (OS_SEM                *p_sem,
                                         OS_TICK                timeout,
                                         OS_OPT                 opt,
                                         CPU_TS                *p_ts,
                                         OS_ERR                *p_err);

OS_OBJ_QTY    OSSemPendAbort            (OS_SEM                *p_sem,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);

OS_SEM_CTR    OSSemPost                 (OS_SEM                *p_sem,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);

void          OSSemSet                  (OS_SEM                *p_sem,
                                         OS_SEM_CTR             cnt,
                                         OS_ERR                *p_err);


/* ================================================================================================================== */
/*                                                    MISCELLANEOUS                                                   */
/* ================================================================================================================== */

void          OSInit                    (OS_ERR                *p_err);

void          OSIntEnter                (void);
void          OSIntExit                 (void);

void          OSSchedRoundRobinCfg      (CPU_BOOLEAN            en,
                                         OS_TICK                dflt_time_quanta,
                                         OS_ERR                *p_err);

void          OSSchedRoundRobinYield    (OS_ERR                *p_err);

void          OSSched                   (void);

void          OSSchedLock               (OS_ERR                *p_err);
void          OSSchedUnlock             (OS_ERR                *p_err);

void          OSStart                   (OS_ERR                *p_err);

void          OSStatReset               (OS_ERR                *p_err);

void          OSStatTaskCPUUsageInit    (OS_ERR                *p_err);

CPU_INT16U    OSVersion                 (OS_ERR                *p_err);


/* ================================================================================================================== */
/*                                                 TIME MANAGEMENT                                                    */
/* ================================================================================================================== */

void          OSTimeDly                 (OS_TICK                dly,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);

void          OSTimeDlyHMSM             (CPU_INT16U             hours,
                                         CPU_INT16U             minutes,
                                         CPU_INT16U             seconds,
                                         CPU_INT32U             milli,
                                         OS_OPT                 opt,
                                         OS_ERR                *p_err);

void          OSTimeDlyResume           (OS_TCB                *p_tcb,
                                         OS_ERR                *p_err);

OS_TICK       OSTimeGet                 (OS_ERR                *p_err);

void          OSTimeSet                 (OS_TICK                ticks,
                                         OS_ERR                *p_err);

void          OSTimeTick                (void);


/* ================================================================================================================== */
/*                                                 TIMER MANAGEMENT                                                   */
/* ================================================================================================================== */

void          OSTmrCreate               (OS_TMR                *p_tmr,
                                         CPU_CHAR              *p_name,
                                         OS_TICK                dly,
                                         OS_TICK                period,
                                         OS_OPT                 opt,
                                         OS_TMR_CALLBACK_PTR    p_callback,
                                         void                  *p_callback_arg,
                                         OS_ERR                *p_err);

CPU_BOOLEAN   OSTmrDel                  (OS_TMR                *p_tmr,
                                         OS_ERR                *p_err);

OS_TICK       OSTmrRemainGet            (OS_TMR                *p_tmr,
                                         OS_ERR                *p_err);

CPU_BOOLEAN   OSTmrStart                (OS_TMR                *p_tmr,
                                         OS_ERR                *p_err);

OS_STATE      OSTmrStateGet             (OS_TMR                *p_tmr,
                                         OS_ERR                *p_err);

CPU_BOOLEAN   OSTmrStop                 (OS_TMR                *p_tmr,
                                         OS_OPT                 opt,
                                         void                  *p_callback_arg,
                                         OS_ERR                *p_err);


#endif
