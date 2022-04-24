#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>

class Process
{
	//Insertion operator (insert into Process from text file: Ex myfile >> myprocess)
	friend std::istream& operator>>(std::istream& stream, Process& process);
  friend std::ostream& operator<<(std::ostream& stream, const Process& process);
public:
	//Declarations
	Process();	//creates default process variable

	Process(std::string, int, int, int);

  void setBT(int newBT); //setting new Burst time value

  void setAT(int newAT); //setting new Arrival time value

  std::string getID() const; //return process ID

	int getBT() const;	//return Burst Time

	int getPR() const;	//return Priority

	int getAT() const;	//return arrival Time

	~Process();			//destructor

private:
	std::string name;
	int	bTime;	//burst time
	int prio;	//priority
	int aTime;	//arrival time
};

#endif
