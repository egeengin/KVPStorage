#include <string>
#include <iostream>

#include "DaoInMemory.h"
#include "CommandHandler.h"

using namespace std;

IDao &Dao = DaoInMemory::GetInstance();

CommandHandler &CommandHandler::GetHandler() {
    static CommandHandler handler;
    return handler;
}

bool SetCommandHandler::Handle(QKVPair qkvPair) {
    return Dao.SetKVP(qkvPair.key, qkvPair.value);
}

bool GetCommandHandler::Handle(QKVPair qkvPair){
    return Dao.GetKVP(qkvPair.key);
}

bool DeleteCommandHandler::Handle(QKVPair qkvPair) {
    return Dao.DeleteKVP(qkvPair.key);
}

bool CommandHandler::LineParser(std::string input_str,QKVPair &qkvPair) {
    stringstream s(input_str);
    string word;

    int num = 0;
    while (s >> word) {
        switch (num) {
            case 0:
                qkvPair.query = word;
                break;
            case 1:
                qkvPair.key = word;
                break;
            case 2:
                qkvPair.value = word;
                break;
            default:
                break;
        }
        num++;
    }

    // Check argument num
    if (num == 0) { // Enter returns as exit function
        return EXIT_FAILURE;   // Return to command line, Exit Function
    } else if (num == 3 && qkvPair.query == qkvPair.queryList[0]) { // SET [KEY] [VALUE]
        return EXIT_SUCCESS;
    } else if (num == 2 && (qkvPair.query == qkvPair.queryList[1] || qkvPair.query == qkvPair.queryList[2])) { //GET/DELETE [KEY]
        return EXIT_SUCCESS;
    } else{
        return PrintWrongInput();
    }
}

bool CommandHandler::PrintWrongInput() {
    cout << "Wrong input" << endl;
    return EXIT_FAILURE;
}

CommandHandler *CommandHandler::MakeCommandHandler(QKVPair qkvPair) {
    if (qkvPair.query == qkvPair.queryList[0]) {
        return new SetCommandHandler;
    } else if (qkvPair.query == qkvPair.queryList[1]) {
        return new GetCommandHandler;
    } else if (qkvPair.query == qkvPair.queryList[2]) {
        return new DeleteCommandHandler;
    } else {
        PrintWrongInput();
        return new CommandHandler; // to disable warnings
    }
}

bool CommandHandler::HandleUserCommands(std::string line) {
    QKVPair qkvPair;
    CommandHandler *commandHandler;
    if (LineParser(line, qkvPair)) {
        return EXIT_FAILURE;
    } else {
        commandHandler = MakeCommandHandler(qkvPair);
    }
    commandHandler->Handle(qkvPair);
    delete commandHandler;
    return EXIT_SUCCESS;
}

bool CommandHandler::InputHandler(std::istream &input = std::cin) {
    std::string line;
    getline(input, line);
    return HandleUserCommands(line);
}

CommandHandler::~CommandHandler() {

}

bool CommandHandler::Handle(QKVPair qkvPair) {
    return EXIT_FAILURE;
}
