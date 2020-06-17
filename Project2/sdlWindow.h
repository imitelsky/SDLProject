#pragma once

#include "Widget.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Mediator;

class sdlWindow
{
	public:

        sdlWindow();

        bool init();
        void handleEvent(SDL_Event& e);
        void focus();
        void render();
        void addWidget(std::shared_ptr<Widget> iWidget);
        void setSystemMediator(Mediator* iMediator) { mSystemMediator = iMediator; };
        void free();

	private:
        int                           mWindowID = 0;
        SDL_Window*                   mWindow = nullptr;
        SDL_Renderer*                 mRenderer = nullptr;
        Mediator*                     mSystemMediator;

        int mWidth = 0;
        int mHeight = 0;

        bool mMouseFocus = 0;
        bool mKeyboardFocus = 0;
        bool mFullScreen = 0;
        bool mMinimized = 0;
        bool mShown = 0;

        std::shared_ptr<WidgetContainer> mWidgets = nullptr;
};

