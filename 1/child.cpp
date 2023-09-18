#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    // Set the reading buffer size
    const int readingBufferSize = 1024;
    
    // Get the file path from command line arguments
    const char* filePath = argv[0];
    
    // Open the file for writing
    std::ofstream fs(filePath);
    
    // Open the FIFO for reading
    int fd = open(argv[1], O_RDONLY);
    
    // Check if FIFO opening failed
    if (fd == -1) {
        close(fd);
        return 1;
    }
    
    int msgSize;
    
    // Read the message size from the FIFO
    if (read(fd, &msgSize, sizeof(int)) == -1) {
        close(fd);
        return 2;
    }
    
    std::string message;
    
    // Resize the message string to the message size
    message.resize(msgSize);
    
    // Read the message from the FIFO
    if (read(fd, const_cast<char*>(message.data()), sizeof(char) * msgSize) == -1) {
        close(fd);
        return 2;
    }
    
    close(fd);
    
    // Create a string stream from the message
    std::stringstream ss(message);
    
    // Create a vector to store the numbers
    std::vector<int> numbers;
    
    int number;
    
    // Extract numbers from the string stream and store them in the vector
    while (ss >> number) {
        numbers.push_back(number);
    }
    
    // Calculate the result
    double result = static_cast<double>(numbers.front());
    
    for (int i = 1; i < numbers.size(); i++) {
        int n = static_cast<double>(numbers.at(i));
        
        // Check for division by zero
        if (n == 0) {
            fs << "<Zero Division Mistake>";
            fs.close();
            return 0;
        }
        
        result /= n;
    }
    
    // Write the values and the result to the file
    fs << "Values (message size " << msgSize << "): " << message << '\n';
    fs << "Answer: " << result << std::endl;
    fs.close();
    
    return 0;
}