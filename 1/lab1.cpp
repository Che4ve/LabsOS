#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    // Declarations
    const char* pcFifoName = "PtoCFifo"; // Parent to Child FIFO name
    const char* cpFifoName = "CtoPFifo"; // Child to Parent FIFO name
    const char* childPath = "./child.out"; // Path to child process executable
    const char* outputPath = "./output.txt"; // Path to output file
    
    // Create FIFOs
    if (mkfifo(pcFifoName, 0777) < 0 || mkfifo(cpFifoName, 0777) < 0) {
        if (errno != EEXIST) {
            printf("Couldn't create named pipe\n");
        }
    }
    
    // Fork
    pid_t pid = fork();
    if (pid == -1) { 
        std::cerr << "Fork error" << std::endl;
        return -1;
    }
    
    if (pid > 0) { 
        // Parent process

        // Open FIFO for writing
        int fd = open("PtoCFifo", O_WRONLY);
        if (fd == -1) {
            close(fd);
            return 1;
        }
        
        // Get user input
        std::cout << "Please, enter numbers: " << std::endl;
        std::string inputLine;
        getline(std::cin, inputLine);
        int msgSize = inputLine.length();
        
        // Write message size to FIFO
        if (write(fd, &msgSize, sizeof(int)) == -1) {
            close(fd);
            return 2;
        }
        
        // Write input line to FIFO
        if (write(fd, inputLine.data(), sizeof(char) * msgSize) == -1) {
            close(fd);
            return 3;
        }
        
        close(fd);
        wait(nullptr);
    }
    else if (pid == 0) { 
        // Child process
        const char* args[] = {outputPath, pcFifoName, cpFifoName, nullptr};
        execv(childPath, const_cast<char* const*>(args));
    }
    
    return 0;
}