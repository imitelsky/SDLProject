#pragma once

//#include <SDL.h>
//#include <SDL_image.h>
//#include <iostream>
#include "Widget.h"

class WidgetContainer
{
	public:

		WidgetContainer();
		void addWidget(Widget* iWid);
		void setRenderer(SDL_Renderer* iRenderer) { mRenderer = iRenderer; };
		void handleEvent(SDL_Event& e);
		void widgetChanged(Widget* iWidget);
		void render();

		SDL_Renderer* getRenderer() { return mRenderer; }

	private:
		SDL_Renderer* mRenderer = nullptr;
		std::multimap<int, Widget*> mWidgets;
		//std::multiset<Widget*, Widget> mWidgets
};

