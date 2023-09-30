#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    // Set the reading buffer size
    const int readingBufferSize = 1024;

    // Get the file path from command line arguments
    const char* filePath = argv[0];
    
    // Open the file for writing
    std::ofstream fs(filePath);

    // Read the message size from stdin
    int msgSize;
    if (read(STDIN_FILENO, &msgSize, sizeof(int)) == -1) {
        std::cout << "<Reading Error>" << std::endl;
        return 1;
    }

    // Read the message from stdin
    std::string message;
    message.resize(msgSize);
    if (read(STDIN_FILENO, &message[0], sizeof(char) * msgSize) == -1) {
        std::cout << "<Reading Error>" << std::endl;
        return 2;
    }

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
            std::cout << "<Zero Division Mistake>" << std::endl;
            return 0;
        }

        result /= n;
    }

    // Write the values and the result to output file
    fs << "Values (message size " << msgSize << "): " << message << '\n';
    fs << "Answer: " << result << std::endl;

    fs.close();

    std::cout << "OK" << std::endl;
    return 0;
}
