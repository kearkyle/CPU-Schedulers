// C program for Consumer process illustrating
// POSIX shared-memory API.
// References: Aleesha Ali from Graphic Era Deemed to be University - Schedulers algorithm
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include "Process.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <pthread.h>
#include <mutex>
#include <algorithm>

using namespace std;
//global variables
std::vector<Process> allProcess;
double avgFCFS =      0.0;
double avgSJF_P =     0.0;
int ab;
mutex mtx;

//Declaration of the schedulers' threads
void *FCFS (void* data);      //First come first serve

void *SJF_P (void* data);     //Shortest job first preemptive


long int findSize(char file_name[])
{
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");

    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file
    long int res = ftell(fp);

    // closing the file
    fclose(fp);

    return res;
}

int main()
{
	/* the size (in bytes) of shared memory object */
  char file_name[] = {"example.txt"};
  long int SIZE = findSize(file_name)+1;

	//const int SIZE = 4096;
  FILE *myfile;
  myfile = fopen("output.txt", "w");


	/* name of the shared memory object */
	const char* name = "OS";

	/* shared memory file descriptor */
	int shm_fd;

	/* pointer to shared memory object */
	void* ptr;

	/* open the shared memory object */
	shm_fd = shm_open(name, O_RDONLY, 0666);

	/* memory map the shared memory object */
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

	/* read from the shared memory object */
  fprintf(myfile,"%s" ,(char*)ptr);
	//printf("%s", (char*)ptr);

	/* remove the shared memory object */
	shm_unlink(name);
  fclose(myfile);

  std::ifstream fin("output.txt", std::ios::binary);
  Process process;
  while (fin >> process)
  {
    allProcess.push_back(process);
  }
  cout << "size of allProcess is: " << allProcess.size() << "\n";
  for (int i = 0; i != allProcess.size(); i++)
  {
    //cout << allProcess[i].getID() << allProcess[i].getBT() << allProcess[i].getPR() << allProcess[i].getAT();
    cout << allProcess[i] << "\n";
  }
  fin.close();
  //Threading starts
  pthread_t tid[6];

  //Creating the threads
  pthread_create(&tid[0], NULL, FCFS, NULL);
  pthread_create(&tid[1], NULL, SJF_P, NULL);

  //Joining the threads
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);

  //SECTION to print the minimum waiting time to screen
  ofstream resultfile;

  vector <double> all_wt {avgFCFS, avgSJF_P};
  auto min_wt = std::min_element(all_wt.begin(),all_wt.end());

  //Opening file in appending mode. This will not overwrite what we already had in file
  resultfile.open("result.txt", ofstream::app);
  //Check and output to result file the minimum waiting time of all schedulers
  if (*min_wt == avgFCFS)
  {
    resultfile << "Thus, the First Come First Serve policy results the minimum average waiting time: " << *min_wt << "\n";
  }
  else
  {
    resultfile << "Thus, the Shortest Job First Preemptive policy results the minimum average waiting time: " << *min_wt << "\n";
  }
  resultfile.close();

	return 0;
}

//Boolean function to compare arrival time
bool compare_aTime (Process lhs, Process rhs)
{
  return lhs.getAT() < rhs.getAT();
}

//Boolean function to compare burst time
bool compare_bTime (Process lhs, Process rhs)
{
  return lhs.getBT() < rhs.getBT();
}

void *FCFS(void* data)
{
  mtx.lock();
  //variables declaration and initialization part
  std::vector<Process> myProcess = allProcess;
  int n,i;
  n = myProcess.size();
  int tat[n], ct[n], wt[n];
  //sorting all processes by arrival time
  sort(myProcess.begin(),myProcess.begin()+n,compare_aTime);
  //initial values
  ct[0]  = myProcess[0].getAT() + myProcess[0].getBT();
  tat[0] = ct[0] - myProcess[0].getAT();
  wt[0]  = 0;
  //Calculation part
  for(i=1;i<n;i++)
  {
        if(myProcess[i].getAT() <= ct[i-1])
        {
              ct[i]  = ct[i-1] + myProcess[i].getBT();
              tat[i] = ct[i]   - myProcess[i].getAT();
              wt[i]  = tat[i]  - myProcess[i].getBT();
        }
        else
        {
              ct[i]  = myProcess[i].getBT() + myProcess[i].getAT();
              tat[i] = ct[i]  - myProcess[i].getAT();
              wt[i]  = tat[i] - myProcess[i].getBT();
        }
        avgFCFS += wt[i];
  }

  avgFCFS = avgFCFS / n;
  ofstream myfile;
  myfile.open("result.txt", ofstream::app);
  myfile << "Average wait time for FCFS: " << avgFCFS << "\n";
  myfile.close();
  mtx.unlock();
  pthread_exit(0);

}

void *SJF_P (void* data)
{
  mtx.lock();
  //variables declaration part
  std::vector<Process> myProcess = allProcess;
  int n,i,j,_check;
  int ct[n], wt[n], ta[n];
  n = myProcess.size();
  //Sorting processes by arrival time
  sort(myProcess.begin(),myProcess.begin()+n,compare_aTime);
  i=0;
  _check=0;
  while (_check < n)
  {
        for(j=0;j<n;j++)
        {
              if(myProcess[j].getAT()>i)
              break;
        }
        //sorting processes by burst time
        sort(myProcess.begin(),myProcess.begin()+j,compare_bTime);
        if (j>0)
        {
              for(j=0;j<n;j++)
              {
                    if(myProcess[j].getBT() != 0)
                    break;
              }
              if(myProcess[j].getAT() > i)
              {
                    i = myProcess[j].getAT();
              }
              ct[j]=i+1;
              //int hold = myProcess[j].getBT();
              //hold--;
              //myProcess[j].setBT(hold);
              myProcess[j].setBT(myProcess[j].getBT()-1);
        }
        i++;
        _check=0;
        for(j=0;j<n;j++)
        {
              if(myProcess[j].getBT() == 0)
                  _check++;
        }
  }
  for(i=0;i<n;i++)
  {
        ta[i] = ct[i] - myProcess[i].getAT();
        wt[i] = ta[i] - allProcess[i].getBT();
        avgSJF_P += wt[i];
  }
  //Dividing sum of waiting time by number of processes to get average waiting time
  avgSJF_P = avgSJF_P / n;
  //output to result.txt file starts here
  ofstream myfile;
  myfile.open("result.txt", ofstream::app);
  myfile << "Average wait time for SJF preemptive: " << avgSJF_P << "\n";
  myfile.close();
  mtx.unlock();
  pthread_exit(0);
}


