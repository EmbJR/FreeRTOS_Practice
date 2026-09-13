# Basic information
- I wanted to create the scenario of Tast Priority inversion with the STM32F0 and STM32Cube IDE with CMSIS OS2. 
- I have created the 3 tasks with priorities of low, medium, and High. I have also generated the code for External GPIO interrupt where the switch is connected. 
- I uses the semaphore to lock the execution of tasks so that the priority inversion issue is reflected.

# Main code flow to generate the priority inversion.
- The three tasks named "TaskL_Func", "TaskM_Func" and "TaskH_Func" are generated with "Low", "Medium" and "High" priorities accordingly.
- GPIO interrupt code also implemented to trigger the priority inversion issue.
- Out of three tasks, "TaskM_Func" and "TaskH_Func" tasks are delayed from "TaskL_Func" task to ensure the semaphore lock occupied by the low priority task. The "TaskM_Func" will get delayed ~5 second so the low priority task can have the window to unlock the semaphore to allow high priority task.
- The "TaskM_Func" contains the infinite loop so it uses the 100% CPU if it is the only task running from all three tasks. This will happens only in case of priority inversion issue.

- The code flow to generate the priority inversion issue is as under.
1> First the "TaskL_Func" aquired the semaphore "semaphore1" and proceed further.

2> The "TaskH_Func" will wait for the semaphore to unlock.

3> After some time, the semaphore will be unlocked by the "TaskL_Func". Also the "TaskH_Func" will lock the semaphore and proceed further.

4> Because the "TaskM_Func" initialy delayed ~5 second, the "TaskL_Func" will get another window to lock the semaphore.

5> When the "TaskL_Func" locks the semaphore, and will executing the next instruction (for(volatile uint32_t i = 0; i < 1500000; i++)), I will instantly fires the GPIO interrupt. 
    This time is crucial to generate the priority inversion because the semaphore gets locked and the interrupt fired.

6> Interrupt service routine sets the flag (trigger) and also request to execute the high priority task "TaskH_Func". 
    The high priority task executes and finds the lock in semaphore. 
    This is the scenario for the inversion issue because the "TaskH_Func" cannot proceed further because of semaphore lock, the "TaskM_Func" will get execute.
    Since the "TaskM_Func" only the task which has the unblocked state, it will hogg the cpu and will execute infinitely. 
    Also because the "trigger" flag set by the interrupt, the low priority task will not have the window to execute the respective tasks and also unlock the semaphore.

# The resolution flow wile using the mutex instead of semaphores.
1> First the "TaskL_Func" aquired the mutex "Mutex_1Handle" and proceed further.

2> The "TaskH_Func" will wait for the mutex to unlock.

3> After some time, the mutex  will be unlocked by the "TaskL_Func". Also the "TaskH_Func" will lock the mutex and proceed further.

4> Because the "TaskM_Func" initialy delayed ~5 second, the "TaskL_Func" will get another window to lock the mutex.

5> When the "TaskL_Func" locks the mutex, and will executing the next instruction (for(volatile uint32_t i = 0; i < 1500000; i++)), I will instantly fires the GPIO interrupt. 
    This time is crucial to generate the priority inversion because the mutex gets locked and the interrupt fired.

6> Interrupt service routine sets the flag (trigger) and also request to execute the high priority task "TaskH_Func". The high priority task executes and finds the lock in mutex. 
    This is the scenario for the inversion issue because the "TaskH_Func" cannot proceed further because of mutex lock, the "TaskM_Func" should get execute.
    Since we have used mutex, the kernel will instantly switches the "TaskL_Func" priority to the highest and thus the next task after "TaskH_Func" to be executed becomes "TaskL_Func" instead of "TaskM_Func".

7> Since the flag (trigger) has been set, so for the debugging purpose, we have performed some task for huge amount of time when the flag (trigger) sets in "TaskL_Func". 
    So for some seconds, the task "TaskL_Func" will have the total CPU window and complete the tasks then unlocks the mutex.

8> After unlocking the mutex, the "TaskL_Func" becomes low priority, also the "TaskH_Func" and "TaskM_Func" will get executed which is the idle situation after priority inversion.