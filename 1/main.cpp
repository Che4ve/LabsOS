#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    const int readingBufferSize = 1024;
    // Declarations
    int pcPipe[2]; // Parent to Child pipe
    int cpPipe[2]; // Child to Parent pipe
    const char* childPath = "./child.out"; // Path to child process executable
    const char* outputPath = "../output.txt"; // Path to output file
    
    // Create pipes
    if (pipe(pcPipe) == -1 || pipe(cpPipe) == -1) {
        std::cerr << "Pipe error" << std::endl;
        return 1;
    }
    
    // Fork
    pid_t pid = fork();
    if (pid == -1) { 
        std::cerr << "Fork error" << std::endl;
        return -1;
    }
    
    if (pid > 0) { 
        // Parent process
        // Close unnecessary pipe ends
        close(pcPipe[0]); // Close read end of parent to child pipe
        close(cpPipe[1]); // Close write end of child to parent pipe
        
        // Get user input
        std::cout << "Please, enter numbers: " << std::endl;
        std::string inputLine;
        getline(std::cin, inputLine);
        int msgSize = inputLine.length();
        
        // Write message size to pipe
        if (write(pcPipe[1], &msgSize, sizeof(int)) == -1) {
            std::cerr << "Writing error" << std::endl;
            return 2;
        }
        
        // Write input line to pipe
        if (write(pcPipe[1], inputLine.data(), sizeof(char) * msgSize) == -1) {
            std::cerr << "Writing error" << std::endl;
            return 3;
        }
        
        close(pcPipe[1]); // Close write end of parent to child pipe
        
        // Read the child's response from the pipe
        char buffer[readingBufferSize]; // Adjust buffer size as needed
        int bytesRead = read(cpPipe[0], buffer, sizeof(buffer));
        if (bytesRead == -1) {
            std::cerr << "Reading error" << std::endl;
            return 4;
        }
        
        // Print the child's response
        std::cout << "Child process response: " << std::string(buffer, bytesRead) << std::endl;
        
        close(cpPipe[0]); // Close read end of child to parent pipe
        wait(nullptr);
    }
    else if (pid == 0) { 
        // Child process
        // Close unnecessary pipe ends
        close(pcPipe[1]); // Close write end of parent to child pipe
        close(cpPipe[0]); // Close read end of child to parent pipe
        
        // Redirect stdin and stdout to pipes
        dup2(pcPipe[0], STDIN_FILENO);  // Redirect stdin to read end of parent to child pipe
        dup2(cpPipe[1], STDOUT_FILENO); // Redirect stdout to write end of child to parent pipe
        
        // Execute the child process
        const char* args[] = {outputPath, nullptr};
        execv(childPath, const_cast<char* const*>(args));
    }
    
    return 0;
}
