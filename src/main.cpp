#include <signal.h>
#include <cstdlib>
#include <iostream>

#include "CommandHandler.h"

using namespace std;

#define NUM_QUERY 3
#define NUM_ARG_MAX 3

// Define the function to be called when ctrl-c (SIGINT) is sent to process
void signal_callback_handler(int signum) {
    // Terminate program
    exit(signum);
}

int main() {
    ICommandHandler &CmdHandler = CommandHandler::GetHandler();

    // Register signal and signal handler
    signal(SIGINT, signal_callback_handler);

    while (1) {
        if (CmdHandler.InputHandler(std::cin))
            return EXIT_SUCCESS;
    }
}