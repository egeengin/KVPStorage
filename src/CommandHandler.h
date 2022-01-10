#ifndef KVPSTORAGE_COMMANDHANDLER_H
#define KVPSTORAGE_COMMANDHANDLER_H

#include <string>
#include <ICommandHandler.h>

class QKVPair{
public:
    static const int num_query = 3;
    const int max_arg_num = 3;
    const std::string queryList[num_query] = {"SET", "GET", "DELETE"};
    std::string query, key, value;
};

// Handle command line commands
class CommandHandler : public ICommandHandler {
    // DESIGN PATTERN: Factory Design Pattern
public:
    CommandHandler() = default;

    static CommandHandler &GetHandler();

    CommandHandler(const CommandHandler &orig) = delete;

    virtual bool Handle(QKVPair qkvPair);

    bool InputHandler(std::istream &input) override;

    bool HandleUserCommands(std::string line) override;

    CommandHandler *MakeCommandHandler(QKVPair qkvPair);

    virtual ~CommandHandler();

private:
    bool LineParser(std::string input_str, QKVPair &qkvPair);

    bool PrintWrongInput();
};

class SetCommandHandler : public CommandHandler{
public:
    bool Handle(QKVPair qkvPair);
};

class GetCommandHandler : public CommandHandler{
public:
    bool Handle(QKVPair qkvPair);
};

class DeleteCommandHandler : public CommandHandler{
public:
    bool Handle(QKVPair qkvPair);
};

#endif //KVPSTORAGE_COMMANDHANDLER_H
