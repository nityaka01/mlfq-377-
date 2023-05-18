# mlfq-377-

I chose to implement an MLFQ for my final project. This is an extension of project 3 except it includes an MLFQ implementation. 

My implementation of MLFQ follows the description in Operating Systems: A Three Easy Pieces. Scheduling is a common problem in operating system. Computer Scientists want to find the most efficient ways to schedule processes while optimizing the turnaround time and the response time. Existing algorithms either optimize one or the other, but not both. As a result, the MLFQ was an algorithm to design both of these things. They leverage the functionality of queues and priority queues to be able to do this. 

MLFQ (Multilevel feedback queue) entails the following rules 
1. Priority (A) > Priority (B) A runs before B always 
2. Priority (A) = Priority (B) A and B run in round robin 
3. As a job enters the CPU, it will be placed on the highest priority 
4. If a job is not completed after a time slice, its priority will be decremented by one. If it gives up the CPU before the time slice is done, it stays the same level 
5. After a certain point, it goes to the top. 

The approach we take here is the standard approach, but we also explore other approaches to this. One of the biggest changes that we make is a modification to the round robin algorithm. The traditional round robin algorithm uses 1 ms time quanta as our algorithm, whereas our round robin algorithm parametrizes it. 


Here is the link to the video: https://drive.google.com/file/d/1vVaF5qyo9N9r22rMq4mbSbcbW_MtdDXm/view 
