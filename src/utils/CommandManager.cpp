#include "CommandManager.hpp"

CommandManager* CommandManager::instance = nullptr;

CommandManager::CommandManager()
{
    // cout << "CommandManager created" << endl;
}

CommandManager::~CommandManager()
{
    // cout << "CommandManager deleted" << endl;
}

CommandManager *CommandManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new CommandManager();
    }
    return instance;
}

void CommandManager::destroyInstance()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

void CommandManager::executeCommand(Command *command)
{
    command->execute();
    commandStack.push(command);
}

void CommandManager::undoCommand()
{
    if (!commandStack.empty())
    {
        Command *command = commandStack.top();
        command->undoMove();
        commandStack.pop();
        delete command;
    }
}

void CommandManager::clean()
{
    while (!commandStack.empty())
    {
        Command *command = commandStack.top();
        commandStack.pop();
        delete command;
    }
}