#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <windows.h>

using namespace std;

bool messageRead = false;
HANDLE semaphore;

void writeMessageToFile() {
    std::ofstream file("chat.txt", std::ios::in);
   
    while (true) {
        file.open("chat.txt", ios::app);
        if (file.is_open()) {
            std::string message;
            std::cout << "Enter your message: ";
            std::getline(std::cin, message);
            file << message << '\n';
            messageRead = true;
            file.close();
            ReleaseSemaphore(semaphore, 2, NULL);
        }
    }
    


}

void readMessageFromFile() {
    while (true) {
        WaitForSingleObject(semaphore, INFINITE);

        std::ifstream file("chat.txt");
        if (file.is_open()) {
            std::string text;
            if (!messageRead) {
                while (std::getline(file, text)) {
                    std::cout << "user: " + text << std::endl;
                }
                file.close();
            }
            messageRead = false;
        }
    }
}

    int main() {
        semaphore = CreateSemaphoreA(NULL, 0, 2, "semaphore_name");
        std::thread writerThread(writeMessageToFile);
        std::thread readerThread(readMessageFromFile);

        writerThread.join();
        readerThread.join();
        return 0;
    }