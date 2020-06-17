#include "Widget.h"
#include "Mediator.h"

WidgetContainer::WidgetContainer(Mediator* iMediator) : mRenderer(nullptr)
{
	mSystemMediator = iMediator;
}

void WidgetContainer::render()
{
	for (auto& wid : mWidgetsSortedByPriority)
		wid.second->render();
}

void WidgetContainer::addWidget(std::shared_ptr<Widget> iWidget)
{
	iWidget->setMediator(this);
	iWidget->loadTexture();
	mWidgetsSortedByPriority.emplace(iWidget->getOrder(), iWidget);
	mWidgetsSortedByName.emplace(iWidget->getId(), iWidget);
}

void WidgetContainer::handleEvent(SDL_Event& e)
{
	for (auto& wid : mWidgetsSortedByPriority)
		wid.second->handleEvent(e);
}

void WidgetContainer::free()
{
	for (auto& wid : mWidgetsSortedByPriority)
		wid.second->free();
}

void WidgetContainer::widgetChanged(Widget* iWidget, int iType)
{
	if ("image1" == iWidget->getId() && eEvent_WidgetSelected == iType)
	{
		auto it = mWidgetsSortedByName.find("image2");
		if (it != mWidgetsSortedByName.end())
		{
			if (iWidget->isSelected())
				it->second->setVisible(true);
			else
				it->second->setVisible(false);
		}
	}
	if ("button1" == iWidget->getId() && eEvent_ButtonPressed)
	{
		mSystemMediator->dropCommand(Command::create(eEvent_ButtonPressed, "button1"));
	}
	if ("button2" == iWidget->getId() && eEvent_ButtonPressed)
	{
		mSystemMediator->dropCommand(Command::create(eEvent_ButtonPressed, "button2"));
	}
}