#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <memory>

enum priorities
{
	ePriority_Undefined = 0,
	ePriority_Priority1,
	ePriority_Priority2,
	ePriority_Priority3,
};

enum types
{
	eType_Image,
	eType_Button,
};

enum events
{
	eEvent_WidgetSelected,
	eEvent_ButtonPressed,
};

class WidgetContainer;

class Widget
{
	public:

		virtual void loadTexture();
		virtual void loadTexture(const std::string& iFile);

		virtual void setId(const std::string& iId) { mId = iId; };
		virtual void setOrder(const int iPriority) { mPriority = iPriority; };
		virtual void setPos(const int iX, const int iY) { mClip->x = iX; mClip->y = iY; };
		virtual void setSize(const int iW, const int iH) { mClip->w = iW; mClip->h = iH; };
		virtual void setVisible(bool iVisible) { mIsVisible = iVisible; };
		virtual void setMediator(WidgetContainer* iMediator) { mMediator = iMediator; };
		virtual void update(int iType);
		virtual void free();

		virtual bool isSelected() { return mIsSelected; }

		int getOrder() const { return mPriority; }
		std::string getId() const { return mId; }

		//virtual void update();
		virtual void render();
		virtual void handleEvent(SDL_Event& e);

		Widget() { mClip = new SDL_Rect; };
		Widget(const bool iIsVisible, const int iPriority, const std::string iId, const int iX, const int iY) : mIsVisible(iIsVisible), mPriority(iPriority), mId(iId) 
		{
			mClip = new SDL_Rect;
			setPos(iX, iY);
		}
		virtual ~Widget() { delete mClip; }

	protected:

		bool             mIsVisible;
		int              mPriority;
		int              mType;
		std::string      mId;
		bool             mIsSelected = false;
		SDL_Texture*     mImage = nullptr;
		SDL_Rect*        mClip = nullptr;
		WidgetContainer* mMediator = nullptr;
};

class Button : public Widget
{
	public:

		Button() : Widget() { mType = eType_Button; }
		virtual void loadTexture() override;
		virtual void loadTexture(const std::string& iFile) override;
		virtual void render() override;
		virtual void handleEvent(SDL_Event& e) override;
		virtual void free() override;

	private:

		bool mIsPressed = false;
		SDL_Texture* mButtonReleased = nullptr;
		SDL_Texture* mButtonPressed = nullptr;
};

class Image : public Widget
{
	public:
		Image() : Widget() { mType = eType_Image; }
		virtual void handleEvent(SDL_Event& e);
};

class WidgetFactory
{
	public:
		virtual std::shared_ptr<Widget> create(int iIsVisible, int iOrder, std::string iId, int iX, int iY) = 0;
		virtual ~WidgetFactory() {}
};

class ImageFactory : public WidgetFactory
{
	public:
		virtual std::shared_ptr<Widget> create(int iIsVisible, int iOrder, std::string iId, int iX, int iY)
		{
			auto tmp = std::make_shared<Image>();

			tmp->setVisible(iIsVisible);
			tmp->setOrder(iOrder);
			tmp->setId(iId);
			tmp->setPos(iX, iY);

			return tmp;
		}
};

class ButtonFactory : public WidgetFactory
{
	public:
		virtual std::shared_ptr<Widget> create(int iIsVisible, int iOrder, std::string iId, int iX, int iY)
		{
			auto tmp = std::make_shared<Button>();

			tmp->setVisible(iIsVisible);
			tmp->setOrder(iOrder);
			tmp->setId(iId);
			tmp->setPos(iX, iY);

			return tmp;
		}
};


class Mediator;

class WidgetContainer
{
public:

	WidgetContainer(Mediator* iMediator);
	void addWidget(std::shared_ptr<Widget> iWid);
	void setRenderer(SDL_Renderer* iRenderer) { mRenderer = iRenderer; };
	void handleEvent(SDL_Event& e);
	void render();
	void widgetChanged(Widget* iWidget, int iType);
	void setWinName(const std::string& iName) { mWinName = iName; }
	void free();

	SDL_Renderer* getRenderer() { return mRenderer; }

private:
	std::string                                              mWinName;
	SDL_Renderer*                                            mRenderer = nullptr;
	Mediator*                                                mSystemMediator = nullptr;
	std::multimap<int, std::shared_ptr<Widget>>              mWidgetsSortedByPriority;
	std::unordered_map<std::string, std::shared_ptr<Widget>> mWidgetsSortedByName;
};

