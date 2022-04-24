#include "Process.hpp"

using namespace std;

//Default constructor
std::istream& operator>>(std::istream& stream, Process& process)
{
	Process check;
	//char delim = ',';
	stream >> check.name  >> check.bTime
		>> check.prio  >> check.aTime;

	if (stream) process = std::move(check);
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Process& process)
{
  stream << process.name << " " << process.bTime << " " << process.prio << " " <<process.aTime;
  return stream;
}

Process::Process()
{
	name = "P0";
	bTime = 0;
	prio = 0;
	aTime = 0;
}

//Overloaded constructor
Process::Process(string newName, int newBT, int newPR, int newAT)
{
	name = newName;
	bTime = newBT;
	prio = newPR;
	aTime = newAT;
}
//Definition of the setter
void Process::setBT(int newBT)
{
  bTime = newBT;
}

void Process::setAT(int newAT)
{
  aTime = newAT;
}

//Definition of the get functions
std::string Process::getID() const
{
  return name;
}

int Process::getBT() const	//return Burst Time
{
	return bTime;
}

int Process::getPR() const	//return Priority
{
	return prio;
}

int Process::getAT() const	//return arrival Time
{
	return aTime;
}

//Destructor
Process::~Process()
{

}
