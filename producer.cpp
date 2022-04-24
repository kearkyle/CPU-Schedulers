#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <algorithm>

using namespace std;

/*Returns size of file in bytes*/
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

int main(){

    string file = "example.txt";
    vector<string> data;
    string line;
    fstream myfile (file);


    //Opens file and stores data into vector
    if(myfile.is_open()){
        while(getline(myfile, line, '\n')){
            data.push_back(line);
        }
        myfile.close();
    }
    else{
        cout << "Unable to open file";
    }

    //Remove commas from data
    for(int i = 0; i < data.size(); ++i){
        data[i].erase(remove(data[i].begin(), data[i].end(), ','), data[i].end());
        cout << data[i] << endl;
    }

    cout << "Parsing was sucessful!\n";

    // /* the size (in bytes) of shared memory object */
    char file_name[] = {"example.txt"};
    long int SIZE = findSize(file_name)+1;

    // if (res != -1)
    //     printf("Size of the file is %ld bytes \n", res);

    //const int SIZE = findSize("example.txt");

    /* name of the shared memory object */
    const char *name = "OS";

    /* strings written to shared memory */
    const char *c;
    const char* newline = "\n";

    /* shared memory file descriptor */
    int fd;

    /* pointer to shared memory obect */
    char *ptr;

    /* create the shared memory object */
    fd = shm_open (name,O_CREAT | O_RDWR,0666);

    /* configure the size of the shared memory object */
    ftruncate(fd, SIZE);

    /* memory map the shared memory object */
    ptr = (char *)
    mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);


    /* write to the shared memory object */
    for(auto str: data){
        c = str.c_str();
        sprintf(ptr, "%s", c);
        ptr += strlen(c);
        sprintf(ptr, "%s", newline);
        ptr += strlen(newline);
    }

    myfile.close();

    return 0;
}
