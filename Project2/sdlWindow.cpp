#include "sdlWindow.h"
#include "Mediator.h"

sdlWindow::sdlWindow()
{
}

bool sdlWindow::init()
{

    mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (mWindow != nullptr)
    {
        mMouseFocus = true;
        mKeyboardFocus = true;
        mWidth = SCREEN_WIDTH;
        mHeight = SCREEN_HEIGHT;

        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (mRenderer == nullptr)
        {
            std::cout << "Renderer could not be created! SDL Error: " <<  SDL_GetError() << std::endl;
            SDL_DestroyWindow(mWindow);
            mWindow = nullptr;
        }
        else
        {
            SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

            mWindowID = SDL_GetWindowID(mWindow);

            mShown = true;
        }
    }
    else
    {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
    }

    mWidgets = std::make_shared<WidgetContainer>(mSystemMediator);
    mWidgets->setRenderer(mRenderer);

    return mWindow != NULL && mRenderer != NULL;
}

void sdlWindow::render()
{
    if (!mMinimized)
    {
        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);

        mWidgets->render();
            
        SDL_RenderPresent(mRenderer);
    }
}

void sdlWindow::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID)
    {
        switch (e.window.event)
        {
            case SDL_WINDOWEVENT_SHOWN:
                mShown = true;
                break;

            case SDL_WINDOWEVENT_HIDDEN:
                mShown = false;
                break;

            case SDL_WINDOWEVENT_SIZE_CHANGED:
                mWidth = e.window.data1;
                mHeight = e.window.data2;
                SDL_RenderPresent(mRenderer);
                break;

            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent(mRenderer);
                break;

            case SDL_WINDOWEVENT_ENTER:
                mMouseFocus = true;
                break;

            case SDL_WINDOWEVENT_LEAVE:
                mMouseFocus = false;
                break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
                mKeyboardFocus = true;
                break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
                mKeyboardFocus = false;
                break;

            case SDL_WINDOWEVENT_MINIMIZED:
                mMinimized = true;
                break;

            case SDL_WINDOWEVENT_MAXIMIZED:
                mMinimized = false;
                break;

            case SDL_WINDOWEVENT_RESTORED:
                mMinimized = false;
                break;

            case SDL_WINDOWEVENT_CLOSE:
                SDL_HideWindow(mWindow);
                break;
        }
    }
    else if (e.window.windowID == mWindowID)
        mWidgets->handleEvent(e);
}

void sdlWindow::focus()
{
    if (!mShown)
    {
        SDL_ShowWindow(mWindow);
    }

    SDL_RaiseWindow(mWindow);
}

void sdlWindow::addWidget(std::shared_ptr<Widget> iWidget)
{
    mWidgets->addWidget(iWidget);
}

void sdlWindow::free()
{
    mWidgets->free();

    if (mRenderer != nullptr)
        SDL_DestroyRenderer(mRenderer);
    
    if (mWindow != nullptr)
        SDL_DestroyWindow(mWindow);

    mMouseFocus = false;
    mKeyboardFocus = false;
    mWidth = 0;
    mHeight = 0;
}