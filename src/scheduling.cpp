#include <scheduling.h>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>

using namespace std;

//MLFQ function 
//considers 4 queues of type pqueue_arrival, this is valid because each queue represents a level and all processes in the same level are sent to round robin
//adds all elements in workload to q4 initially and sets it to 4 (as a new job enters the system, it will be in the highest prio queue)
//if q4 is not empty, calls round robin on q4 and gets results, repeat process for q3 q2 q1
//returns list of completed processes 

list<Process> mlfq(pqueue_arrival workload){
  pqueue_arrival q1, q2, q3, q4; 
  pqueue_arrival new_workload; 
  int time_stamp = workload.top().arrival;
  list<Process> completed_and_rescheduled_processes; 

  //select ones with highest priority from return list of round robin 
  pqueue_arrival highest_priority_queue; 

  list<Process> completed_jobs; 
  //reading from workload queue and populating highest priority
  //update while loop so that it adds priorities on the go? this is not doing it based on time stamp 
   while(!workload.empty()){
    Process p = workload.top();
    p.priority = 4;
    q4.push(p);
    workload.pop();
  }


  while (!q4.empty()||!q3.empty()||!q2.empty()||!q1.empty()) {
    if(!q4.empty()){
      
      
      completed_and_rescheduled_processes = rr(q4); 

      //examine if the job is a completed or rescheduled job by checking if the duration is 0 
     for (auto const &i: completed_and_rescheduled_processes) {
        if(i.duration == 0){
          completed_jobs.push_back(i);
        }
        else{
         //select elements with highest priority from completed and rescheduled process 
         //add to the priorities queue 
         //consider temp_queue 
          if(i.priority == 4){
            q4.push(i);
          }
          else if(i.priority == 3){
            q3.push(i);
          }
          else if(i.priority == 2){
            q2.push(i);
          }
          else{
            q1.push(i);
          }
        }
    }
    }


    else if (!q3.empty()){
        completed_and_rescheduled_processes = rr(q3); 
        for (auto const &i: completed_and_rescheduled_processes) {
        if(i.duration == 0){
          completed_jobs.push_back(i);
        }
        else{
         //select elements with highest priority from completed and rescheduled process 
         //add to the priorities queue 
         //consider temp_queue 
          if(i.priority == 4){
            q4.push(i);
          }
          else if(i.priority == 3){
            q3.push(i);
          }
          else if(i.priority == 2){
            q2.push(i);
          }
          else{
            q1.push(i);
          }
        }
    }

    }

    else if (!q2.empty()){
      completed_and_rescheduled_processes = rr(q2); 

      for (auto const &i: completed_and_rescheduled_processes) {
        if(i.duration == 0){
          completed_jobs.push_back(i);
        }
        else{
         //select elements with highest priority from completed and rescheduled process 
         //add to the priorities queue 
         //consider temp_queue 
          if(i.priority == 4){
            q4.push(i);
          }
          else if(i.priority == 3){
            q3.push(i);
          }
          else if(i.priority == 2){
            q2.push(i);
          }
          else{
            q1.push(i);
          }
        }
    }
    }
    else{
      completed_and_rescheduled_processes = rr(q1); 

      for (auto const &i: completed_and_rescheduled_processes) {
        if(i.duration == 0){
          completed_jobs.push_back(i);
        }
        else{
         //select elements with highest priority from completed and rescheduled process 
         //add to the priorities queue 
         //consider temp_queue 
          if(i.priority == 4){
            q4.push(i);
          }
          else if(i.priority == 3){
            q3.push(i);
          }
          else if(i.priority == 2){
            q2.push(i);
          }
          else{
            q1.push(i);
          }
        }
    }
    }

}

//print_completed_jobs(completed_jobs);
return completed_jobs; 
}

void print_completed_jobs(list<Process> completed_jobs){
  for (auto const &i: completed_jobs) {
        cout << i.arrival << i.completion << i.duration << i.first_run << i.priority;

}
}

//round robin variant 
list<Process> rr(pqueue_arrival workload, int time_quanta, int priority_boost_time) {
  list<Process> executing;
  list<Process> complete_reschedule;
  int time_acc = 0;

  while(!workload.empty() || !executing.empty()) {
    
    while(workload.top().arrival <= time_acc && !workload.empty()) {
      executing.push_back(workload.top());
      workload.pop();
    }
    Process p = executing.front();
    executing.pop_front();
    if (p.first_run == -1) {
      p.first_run = time_acc;
    }
    p.duration -= time_quanta;
    time_acc += time_quanta;

    //check if the time slice has been exhausted 
    //set reschedule parameters and give it to rescheduling -> if duration is completed then job is completed 
    if (p.duration <= 0) {
      p.completion = time_acc;
      complete_reschedule.push_back(p);
    }
    else if(time_acc % time_quanta == 0){
      if(p.priority > 1){
        p.priority-=1; 
      }
     
      complete_reschedule.push_back(p);
    }
    //duration is not finished but it is given up within the time slice 
    else if(time_acc % time_quanta != 0 && p.duration > 0){ 
      complete_reschedule.push_back(p);

    }
    //process back into highest priority boost time
    else if(time_acc > priority_boost_time && p.duration > 0){
      p.priority = 4; 
    }
     else {
      executing.push_back(p);
    }
  }
  return complete_reschedule;

}

//create one priority queue which holds multiple jobs with a priority assigned (1, 2, 3, 4)
//read the highest priority jobs (4) and call round robin algorithm on it
//create a pqueue_arrival for the highest priority and give it to round robin


//inputs: workload 
/* list<Process> mlfq(pqueue_arrival workload){
  pqueue_arrival new_workload; 
  int time_slice; 
  int time_stamp = workload.top().arrival;
  list<Process> completed_and_rescheduled_processes; 
  pqueue_arrival priorities;
  int highest_priority = -100;  
  pqueue_arrival temp_queue; 

  //select ones with highest priority from return list of round robin 
  pqueue_arrival highest_priority_queue; 

  list<Process> completed_jobs; 
  //Initialize a priorities queue with a workload queue 
 
  while(!workload.empty()){
    Process p = workload.top();
    p.priority = 4;
    priorities.push(p);
    workload.pop();
  }

  while(!priorities.empty()){

    completed_and_rescheduled_processes = rr(priorities); 
    //returned values from round robin could be at various priorities 
    //select ones with highest priority and give it to round robin 
    //queue the rest to be submitted next time 
    //examine if the job is a completed or rescheduled job by checking if the duration is 0 
     for (auto const &i: completed_and_rescheduled_processes) {
        if(i.duration == 0){
          completed_jobs.push_back(i);
        }
        else{
         //select elements with highest priority from completed and rescheduled process 
         //add to the priorities queue 
         //consider temp_queue 
          if(i.priority > highest_priority){
            highest_priority = i.priority;
            temp_queue.push(priorities.top());
            priorities.pop();
             priorities.push(i);
          }
          else{
            temp_queue.push(i);
          }
        }
    }
    
 
  } 
} */

pqueue_arrival read_workload(string filename) {
  pqueue_arrival workload_pqueue;
  ifstream myfile(filename);
  int arrival_time; 
  int duration; 
  while(myfile >> arrival_time >> duration){
      cout << "entering first while loop!";
      Process proc = {arrival_time, -1, duration, -1, 0};
      workload_pqueue.push(proc);
      //string word;
      
}
  return workload_pqueue;
}

void show_workload(pqueue_arrival workload) {
  pqueue_arrival xs = workload;
  cout << "Workload:" << endl;
  while (!xs.empty()) {
    Process p = xs.top();
    cout << '\t' << p.arrival << ' ' << p.duration << endl;
    xs.pop();
  }
}

void show_processes(list<Process> processes) {
  list<Process> xs = processes;
  cout << "Processes:" << endl;
  while (!xs.empty()) {
    Process p = xs.front();
    cout << "\tarrival=" << p.arrival << ", duration=" << p.duration
         << ", first_run=" << p.first_run << ", completion=" << p.completion
         << endl;
    xs.pop_front();
  }
}

list<Process> fifo(pqueue_arrival workload) {
  int time_stamp = workload.top().arrival; 
  list<Process> complete;

  while(!workload.empty()){
    Process p = workload.top();
    p.first_run = time_stamp; 
    p.completion = p.first_run + p.duration;
    time_stamp = p.completion; 

    complete.push_back(p);
    workload.pop();
  }
  return complete;
}

list<Process> sjf(pqueue_arrival workload) {
  list<Process> complete;
  int time_stamp = workload.top().arrival;
  pqueue_duration durations; 
  while(!workload.empty() || !durations.empty()){
    
    while(!workload.empty() &&workload.top().arrival <= time_stamp){
      durations.push(workload.top());
      workload.pop();
    }

      if(durations.empty()){
        time_stamp = workload.top().arrival;
        continue;
      }
      Process d = durations.top();
      d.first_run = time_stamp; 
      d.completion = d.first_run + d.duration; 
      time_stamp = d.completion;
      complete.push_back(d);
      durations.pop();
    }
  return complete;
}


list<Process> stcf(pqueue_arrival workload) {
  list<Process> complete;
  int time_stamp = workload.top().arrival;
  pqueue_duration duration; 

  while(!workload.empty()){
  pqueue_duration duration_queue;
  list<Process> complete;
  int time_acc = 0;
  while(!workload.empty() || !duration_queue.empty()) {
    while(workload.top().arrival <= time_acc && !workload.empty()) {
      duration_queue.push(workload.top());
      workload.pop();
    }
    Process p = duration_queue.top();
    duration_queue.pop();
    if (p.first_run == -1) {
      p.first_run = time_acc;
    }
    // Execute process for 1 time quanta
    p.duration -= 1;
    time_acc += 1;

    if (p.duration == 0) {
      p.completion = time_acc;
      complete.push_back(p);
    } else {
      duration_queue.push(p);
    }
  }
  return complete;
  }
  

}



/* list<Process> mlfq(pqueue_arrival workload){
  pqueue_arrival new_workload; 
  int time_slice; 
  int time_stamp = workload.top().arrival;
  list<Process> completed_and_rescheduled_processes; 
  pqueue_priority priorities;   

  while(!workload.empty()){
    static int current_job_arrival_time = 0; 
    Process p = workload.top();
    if(current_job_arrival_time == 0 || current_job_arrival_time == p.arrival){ //check this condition
      current_job_arrival_time = p.arrival; 
      p.priority = 4; 
      priorities.push(p);
      workload.pop();
    }
    completed_and_rescheduled_processes = rr(priorities); 
    
    
    //read all the jobs from the workload queue which have the highest priority (arrival time)
    // create the priority queue with them, call round robin on them
    
    //examine the complete processes and see if job is really completed and send it to metrics
    //if time slice is exhausted and job not completed, use the new priority
    //push it back to priorities queue 
    //update arrival time
 
  }  */
  


float avg_turnaround(list<Process> processes) {
  float total_turnaround_time = 0; 
  int num_processes = 0; 

  for (const Process & proc : processes)
  {
    total_turnaround_time += proc.completion - proc.arrival;
    num_processes++;
  }

  return total_turnaround_time/=num_processes;
}

float avg_response(list<Process> processes) {

  float total_response_time = 0; 
  int num_processes = 0; 

  for (const Process & proc : processes)
  {
    total_response_time += proc.first_run - proc.arrival;
    num_processes++;
  }

  return total_response_time/=num_processes;
}

void show_metrics(list<Process> processes) {
  float avg_t = avg_turnaround(processes);
  float avg_r = avg_response(processes);
  show_processes(processes);
  cout << '\n';
  cout << "Average Turnaround Time: " << avg_t << endl;
  cout << "Average Response Time:   " << avg_r << endl;
}
