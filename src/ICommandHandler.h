#ifndef KVPSTORAGE_ICOMMANDHANDLER_H
#define KVPSTORAGE_ICOMMANDHANDLER_H

#include <string>

// Interface of handling user commands
class ICommandHandler {
    // DESIGN PATTERN: Interface Design Pattern
public:
    ICommandHandler() {
    };

    virtual bool InputHandler(std::istream &input) = 0; //Any input stream method can be used like std::cin

    virtual bool HandleUserCommands(std::string line) = 0; //Test purposes

    virtual ~ICommandHandler() {
    };
};

#endif //KVPSTORAGE_ICOMMANDHANDLER_H
