#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <semaphore.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <semaphore.h>

int main(int argc, char** argv) {
    const int readingBufferSize = 1024;
    const int sharedMemSize = 4096;
    
    // Declarations
    const char* childPath = "./child.out"; // Path to child process executable
    const char* outputPath = "./output.txt"; // Path to output file

    const char* sharedMemName = "/shared_memory";
    const char* semaphoreName = "/main_semaphore";
    
    const int initValue = 1; // Semaphore value
    
    // Open shared memory
    int shm_fd = shm_open(sharedMemName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    
    // Open semaphore
    sem_t* semaphore = sem_open(semaphoreName, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, initValue);
    
    if (semaphore == SEM_FAILED) {
        std::cerr << "Semaphore failed in parent" << std::endl;
        return -2;
    }
    
    sem_wait(semaphore);
    
    // Fork
    pid_t pid = fork();
    
    if (pid == -1) { 
        std::cerr << "Fork error" << std::endl;
        return -1;
    }
    
    if (pid > 0) { 
        // Parent process
        
        // Get user input
        std::cout << "Please, enter numbers: " << std::endl;
        std::string inputLine;
        getline(std::cin, inputLine);
        int msgSize = inputLine.length();
        char* message = inputLine.data();
        
        // Resize shared memory
        ftruncate(shm_fd, msgSize);
        
        // Map shared memory
        char* mapped_file = static_cast<char*>(mmap(NULL, msgSize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));
        
        if (mapped_file == MAP_FAILED) {
            std::cerr << "Couldn't map memory in parent" << std::endl;
            return 1;
        }
        
        // Put message into the shared memory
        strncpy(mapped_file, message, msgSize);
        
        sem_post(semaphore);
        sem_wait(semaphore);
        
        // Print the child's response
        std::cout << "Child process response: " << mapped_file << std::endl;
        
        wait(nullptr);

        munmap(mapped_file, sharedMemSize);
        close(shm_fd);

        shm_unlink(sharedMemName);

        sem_close(semaphore);
        sem_unlink(semaphoreName);
    }
    else if (pid == 0) { 
        // Child process
        
        // Execute the child process
        const char* args[] = {outputPath, sharedMemName, semaphoreName, nullptr};
        execv(childPath, const_cast<char* const*>(args));
    }
    
    return 0;
}
