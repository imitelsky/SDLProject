#include "Mediator.h"

int main(int argc, char* argv[])
{
	auto systemMediator = std::make_shared<Mediator>();
	systemMediator->init();

	systemMediator->mainLoop();

	return 0;
}