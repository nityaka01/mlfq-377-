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

Round Robin Algorithm makes the following modifications: 
Instead of solely taking a priority queue sorted by arrival times, we take a priority queue parametrized with the parameters 
pqueue_arrival, int time_quanta, int priority_boost_time. We consider the cases in round robin 

if the job has been completed, there is no duration left in the queue 
if a time quanta has been passed (time_accumulator % time_quanta == 0) we decrement the priority by 1 and add it to a complete_rescheduled list 
if a time quanta has not been passed but the job itself has stopped or completed, we keep it at the same priority and add it to a completed_rescheduled list 
if a time accumulated has exceeded the priority boosting threshold, boost everything to the topmost priority and run it in round robin. 

further modifications: instead of using a constant time slice for this, we can use different methods to use time slicing. the code encapsulates both the constant time quanta, as well as a changed time quanta. for the modified time quanta, we can use shorter time intervals for the topmost queue and larger time intervals for the bottom most queue. This aims to make the topmost queue more interactive (due to shorter jobs remaining on the higher level queue while longer, more cpu-intensive jobs are on the bottom most queue). 

Approaches we can take are: using geometric series to make it 1/n^k where n > 1 for each level. for n = 2, this would look like 1, 2, 4, 8 ... based on the level. 

We handle the interactive jobs and CPU intensive jobs through this. 

For the actual implementation of mlfq, this calls round robin. We have 4 priority queues q1, q2, q3, q4. Ideally, we can also parametrize this by making an array of queues and allowing for it to work on any number of priority queues. However, operating on 4 is sufficient for the purposes of this project. A while loop addresses the fact that every job starts out with a priority of 4. NOTE: in project 3, we are given a process structure, but we make modifications to this process structure by adding a field priority which comes useful in the algorithm. We then check while there exists some process remaining in either of our 4 queues, we check if all of the queues are not empty. The first queue which has a nomempty process will run that process for a time quanta. If the priority is updated, we check for that in our completed_and_rescheduled processes queue. Specfically, if the priority has been decremented, we will add that to its corresponding queue. 

Our algorithm uses i/o when calling mlfq. The focus of this is to ultimately optimize both Tturnaround and Tresponse time. 
Here is the link to the video:[ https://drive.google.com/file/d/1vVaF5qyo9N9r22rMq4mbSbcbW_MtdDXm/view ](https://drive.google.com/file/d/1nLMFXmYvH2QL1wKHBBnVSNWMc2k4jd4c/view)

https://drive.google.com/file/d/1nLMFXmYvH2QL1wKHBBnVSNWMc2k4jd4c/view
