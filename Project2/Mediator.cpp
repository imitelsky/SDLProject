#include "Mediator.h"
#include "sdlWindow.h"

void Mediator::init()
{
	mFactories.emplace("image", std::make_shared<ImageFactory>());
	mFactories.emplace("button", std::make_shared<ButtonFactory>());

	createWindow("window1");
}

void Mediator::createWindow(const std::string& iWinName)
{
	auto window = std::make_shared<sdlWindow>();

	window->setSystemMediator(this);
	window->init();

	if ("window1" == iWinName)
	{
		window->addWidget(mFactories["image"]->create(true, ePriority_Priority1, "image1", 0, 0));
		window->addWidget(mFactories["image"]->create(false, ePriority_Priority1, "image2", 320, 0));
		window->addWidget(mFactories["button"]->create(true, ePriority_Priority2, "button1", 320, 240));
	}
	else
	{
		window->addWidget(mFactories["image"]->create(true, ePriority_Priority1, "image3", 0, 0));
		window->addWidget(mFactories["button"]->create(true, ePriority_Priority2, "button2", 320, 240));
	}

	mWindows.emplace(iWinName, window);
}

void Mediator::processCommands()
{
	while (!mCommands.empty())
	{
		processCommand(mCommands.front());
		mCommands.pop();
	}
}

void Mediator::processCommand(std::shared_ptr<Command> iCommand)
{
	if (iCommand->getId() == eEvent_ButtonPressed && iCommand->getWidName() == "button1")
		createWindow("window2");
	if (iCommand->getId() == eEvent_ButtonPressed && iCommand->getWidName() == "button2")
		closeWindow("window2");
}

void Mediator::closeWindow(const std::string& iWinName)
{
	auto it = mWindows.find(iWinName);

	if (it == mWindows.end()) return;

	it->second->free();

	mWindows.erase(iWinName);
}

void Mediator::mainLoop()
{
	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;

			for (auto& win : mWindows)
				win.second->handleEvent(e);
		}

		processCommands();

		for (auto& win : mWindows)
			win.second->render();

		SDL_Delay(30);
	}

	closeWindow("window2");
	closeWindow("window1");

	IMG_Quit();
	SDL_Quit();
}
