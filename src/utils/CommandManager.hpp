#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP

#include <stack>
#include "Command.hpp"

class CommandManager
{
private:
    static CommandManager *instance;
    std::stack<Command *> commandStack;

    CommandManager();
    ~CommandManager();

public:
    static CommandManager *getInstance();
    CommandManager(const CommandManager &) = delete;
    void operator=(const CommandManager &) = delete;
    static void destroyInstance();

    bool isEmpty() { return commandStack.empty(); }
    Command *getTop() { return commandStack.top(); }
    void executeCommand(Command *command);
    void undoCommand();
    void clean();
};

#endif