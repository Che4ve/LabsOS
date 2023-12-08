#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <semaphore.h>

int main(int argc, char** argv) {
    // Set the reading buffer size
    const int readingBufferSize = 1024;

    const char* outputFileName = argv[0];
    const char* sharedMemName = argv[1];
    const char* semaphoreName = argv[2];

    std::string response = "OK";

    sem_t* semaphore = sem_open(semaphoreName, 0);
    
    if (semaphore == SEM_FAILED) {
        std::cerr << "Semaphore failed in child" << std::endl;
        return -2;
    }

    sem_wait(semaphore);

    int shm_fd = shm_open(sharedMemName, O_RDWR, S_IRUSR | S_IWUSR);

    struct stat file_stat;
    if (fstat(shm_fd, &file_stat) == -1) {
        std::cerr << "Couldn't get file stat" << std::endl;
        close(shm_fd);
    }

    char* mapped_file = static_cast<char*>(
            mmap(NULL, file_stat.st_size, 
            PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

    if (mapped_file == MAP_FAILED) {
        std::cerr << "Couldn't map memory in child" << std::endl;
        return 1;
    }
    
    char* message = new char[file_stat.st_size];
    snprintf(message, file_stat.st_size, "%s", mapped_file);
    memset(mapped_file, '\0', file_stat.st_size);

    // Create a string stream from the message
    std::istringstream ss(message);

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
        double n = static_cast<double>(numbers.at(i));

        // Check for division by zero
        if (n == 0) {
            response = "<Zero Division Mistake>";
            break;
        }

        result /= n;
    }

    // Open the file for writing
    std::ofstream fs(outputFileName);

    // Write the values and the result to output file
    fs << "Values: " << message << '\n';
    fs << "Answer: " << result << std::endl;

    fs.close();
    
    ftruncate(shm_fd, response.size());
    strncpy(mapped_file, response.c_str(), response.size());

    sem_post(semaphore);
    sem_close(semaphore);

    munmap(mapped_file, file_stat.st_size);
    close(shm_fd);

    return 0;
}
