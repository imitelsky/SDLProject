#include "Widget.h"

void Widget::loadTexture()
{
    std::string fileName{ mId + ".png" };
    int w, h;
    SDL_Texture* texture = IMG_LoadTexture(mMediator->getRenderer(), fileName.c_str());
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    setSize(w, h);

    mImage = texture;
}

void Widget::loadTexture(const std::string& iFile)
{
    std::string fileName{ iFile + ".png" };
    int w, h;
    SDL_Texture* texture = IMG_LoadTexture(mMediator->getRenderer(), fileName.c_str());
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    setSize(w, h);

    mImage = texture;
}

void Widget::render()
{
    if (mIsVisible)
        SDL_RenderCopy(mMediator->getRenderer(), mImage, NULL, mClip);
}

void Widget::handleEvent(SDL_Event& e)
{

}

void Widget::update(int iType)
{
    mMediator->widgetChanged(this, iType);
}

void Widget::free()
{
    SDL_DestroyTexture(mImage);
    delete mClip;
    mClip = nullptr;
}

void Button::loadTexture()
{
    std::string fileName{ mId + ".png" };
    int w, h;
    SDL_Texture* texture = IMG_LoadTexture(mMediator->getRenderer(), fileName.c_str());
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    setSize(w, h);

    mButtonReleased = texture;

    fileName = mId + "_pressed.png";
    texture = IMG_LoadTexture(mMediator->getRenderer(), fileName.c_str());
    mButtonPressed = texture;
}

void Button::loadTexture(const std::string& iFile)
{ 
    std::string fileName{ iFile + ".png" };
    int w, h;
    SDL_Texture* texture = IMG_LoadTexture(mMediator->getRenderer(), fileName.c_str());
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    setSize(w, h);

    mButtonReleased = texture;

    fileName = iFile + "_pressed.png";
    texture = IMG_LoadTexture(mMediator->getRenderer(), fileName.c_str());
    mButtonPressed = texture;
}

void Button::render()
{
    if (mIsPressed)
        mImage = mButtonPressed;
    else
        mImage = mButtonReleased;

    Widget::render();
}

void Button::free()
{
    SDL_DestroyTexture(mButtonPressed);
    SDL_DestroyTexture(mButtonReleased);

    Widget::free();
}

void Image::handleEvent(SDL_Event& e)
{
    Widget::handleEvent(e);
    if (e.type == SDL_MOUSEMOTION)
    {
        if ((e.motion.x >= mClip->x) &&
            (e.motion.y >= mClip->y) &&
            (e.motion.x <= (mClip->x + mClip->w)) &&
            (e.motion.y <= (mClip->y + mClip->h)))
        {
            mIsSelected = true;
            update(eEvent_WidgetSelected);
        }
        else
        {
            mIsSelected = false;
            update(eEvent_WidgetSelected);
        }
    }
}

void Button::handleEvent(SDL_Event& e)
{
    Widget::handleEvent(e);
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if ((e.button.button == SDL_BUTTON_LEFT) &&
            (e.button.x >= mClip->x) &&
            (e.button.y >= mClip->y) &&
            (e.button.x <= (mClip->x + mClip->w)) &&
            (e.button.y <= (mClip->y + mClip->h)))
        {
            mIsPressed = true;
        }
        else
            mIsPressed = false;
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
        if ((e.button.button == SDL_BUTTON_LEFT) &&
            (e.button.x >= mClip->x) &&
            (e.button.y >= mClip->y) &&
            (e.button.x <= (mClip->x + mClip->w)) &&
            (e.button.y <= (mClip->y + mClip->h)))
        {
            mIsPressed = false;
            update(eEvent_ButtonPressed);
        }
        else
            mIsPressed = false;
    }
    else
        mIsPressed = false;
}