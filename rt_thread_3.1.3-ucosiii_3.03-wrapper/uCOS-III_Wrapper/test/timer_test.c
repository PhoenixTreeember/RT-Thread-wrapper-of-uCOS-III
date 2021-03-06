#include <os.h>

#define THREAD_PRIORITY         5
#define THREAD_STACK_SIZE       256
#define THREAD_TIMESLICE        5

ALIGN(RT_ALIGN_SIZE)
static CPU_STK thread2_stack[THREAD_STACK_SIZE];
OS_TCB thread2;

OS_TMR 	tmr1;		//定时器1

//定时器1的回调函数
void tmr1_callback(void *p_tmr, void *p_arg)
{
//    OS_ERR err;
    rt_kprintf("tmr1_callback\r\n");
   
//    OSTmrDel(&tmr1,&err);
//    if(err != OS_ERR_NONE)
//    {
//        rt_kprintf("err:%d\r\n",err);
//    }
}

/* 线程2入口 */
static void thread2_entry(void *param)
{
    OS_ERR err;
    CPU_STK_SIZE free,used,used_max;
	//创建定时器1
	OSTmrCreate((OS_TMR		*)&tmr1,		//定时器1
                (CPU_CHAR	*)"tmr1",		//定时器名字
                (OS_TICK	 )20,			//20*10=200ms
                (OS_TICK	 )100,          //100*10=1000ms
                (OS_OPT		 )OS_OPT_TMR_PERIODIC, //周期模式
                (OS_TMR_CALLBACK_PTR)tmr1_callback,//定时器1回调函数
                (void	    *)0,			//参数为0
                (OS_ERR	    *)&err);		//返回的错误码   
                
    OSTmrStart(&tmr1,&err);	//开启定时器1
    while(1)
    {
        OSTaskStkChk(RT_NULL,&free,&used,&used_max,&err);
        rt_kprintf("free:%d,used:%d,used_max:%d\r\n",free,used,used_max);
        OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);
    }
}
rt_err_t _rt_thread_init(struct rt_thread *thread,
                        const char       *name,
                        void (*entry)(void *parameter),
                        void             *parameter,
                        void             *stack_start,
                        rt_uint32_t       stack_size,
                        rt_uint8_t        priority,
                        rt_uint32_t       tick)
{
    return rt_thread_init(thread,name,entry,parameter,stack_start,stack_size,priority,tick);
}                        

void timer_test (void)
{
    OS_ERR err;

	OSTaskCreate(&thread2,		            //任务控制块
			   (CPU_CHAR*)"thread2", 		//任务名字
               thread2_entry, 			    //任务函数
               0,					        //传递给任务函数的参数
               THREAD_PRIORITY-1,           //任务优先级
               thread2_stack,	            //任务堆栈基地址
               THREAD_STACK_SIZE/10,	    //任务堆栈深度限位
               THREAD_STACK_SIZE,		    //任务堆栈大小
               0,					        //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
               THREAD_TIMESLICE,			//当使能时间片轮转时的时间片长度，为0时为默认长度，
               0,					        //用户补充的存储区
               OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
               &err);
        if(err!=OS_ERR_NONE)
        {
            rt_kprintf("task create err:%d\r\n",err);
        }               
}
