#pragma once

#include "sdlWindow.h"

const std::string win1Widgets[3] = { "image1", "image2", "button1" };
const std::string win2Widgets[2] = { "image3", "button2" };

class Command
{
public:

    static std::shared_ptr<Command> create(const int iId, const std::string& iName)
    {
        auto tmp = std::make_shared<Command>();

        tmp->setId(iId);
        tmp->setWidName(iName);

        return tmp;
    }

    void setId(const int iId) { mId = iId; }
    void setWidName(const std::string& iName) { mWidName = iName; }

    int getId() const { return mId; }
    const std::string& getWidName() const { return mWidName; }
private:
    int mId;
    std::string mWidName;
};

class Mediator
{
public:

    void init();
    void createWindow(const std::string& iWinName);
    void closeWindow(const std::string& iWinName);
    void dropCommand(std::shared_ptr<Command> iCommand) { mCommands.push(iCommand); }
    void processCommands();
    void processCommand(std::shared_ptr<Command> iCommand);
    void mainLoop();

private:

    std::queue<std::shared_ptr<Command>> mCommands;
    std::unordered_map<std::string, std::shared_ptr<sdlWindow>>     mWindows;
    std::unordered_map<std::string, std::shared_ptr<WidgetFactory>> mFactories;

    SDL_Renderer* mRenderer = nullptr;
};

