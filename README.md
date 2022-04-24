#CPSC-351--Group-Project  
#CPSC351: Multithreading with Producer and Consumer. Threads will output the Average waiting time to result.txt file for the CPU schedulers algorithm  
#Producer.cpp will grab data from example.txt file and send them to the buffer . Then consumer.cpp will grab the data set in the buffer, put into a vector of Processes, then the threads will calculate the average time.  

#The CPU schedulers include: First come first serve, Shortest Job First Non-preemptive, Shorstest Job First Preemptive, Round Robin, Priority Non-preemptive, Priority Preemptive  
#Each threads will be outputting the average waiting time out the result.txt individually  
#main.cpp will output the lowest average waiting time from all the threads to result.txt  

#To run the code, on Linux terminal type: chmod +x r.sh  
#then type ./r.sh  

