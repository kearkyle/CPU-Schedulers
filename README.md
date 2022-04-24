# **CPU Schedulers Multi-threading**
This is a CPU multithreading project that takes in inputs from a **.txt** file and calculate the time to finish a process by using threads on the producer and consumer side.  
The inputs are formatted in this order in the example.txt file: **Process name - Burst time - Priority - Arrival Time**  
The calculated time will be printed on result.txt file and it will indicate the algorithm the takes the shortest time to finish a process.  
## Installation
   `git clone https://github.com/kearkyle/CPU-Schedulers`  
   
## How it works in detail:
1. Threads will output the Average waiting time to result.txt file for the CPU schedulers algorithm  
2. Producer.cpp will grab data from example.txt file and send them to the buffer. Then consumer.cpp will grab the data set in the buffer, put into a vector of Processes, then the threads will calculate the average time.  
3. Each threads will be outputting the average waiting time out the result.txt individually  
4. main from consumer.cpp will output the lowest average waiting time from all the threads to result.txt  

## Schedulers:
The current CPU schedulers include: First come first serve, Shorstest Job First Preemptive  

## To Do:
- [ ] Add Shortest Job First Non-preemptive scheduler
- [ ] Add Round Robin scheduler
- [ ] Add Priority Non-preemptive scheduler
- [ ] Add Priority Preemptive scheduler
- [ ] Add panel to let user type in the inputs instead of reading from .txt file
- [ ] Add test cases to make sure the schedulers work as intended
- [ ] Show results on the panel instead of saving to result.txt file
- [ ] Restructure the code format
- [ ] Add comments to code for easy pickup 

## Development:
All contributions are welcome. I will respond and gladly review any pull requests or issues that you may have. Feel free to [open an issue](https://github.com/kearkyle/CPU-Schedulers/issues) for any issues that you may find.
Take a look on the [contributing guidelines](https://github.com/kearkyle/CPU-Schedulers/blob/master/contributing.md) to start with contributions.

## Running code
To run the code, on Linux terminal type:
```
chmod +x r.sh
./r.sh
```   

