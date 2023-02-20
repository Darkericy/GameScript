#include "GFactory.h"
shared_ptr<Game> CollapseFactory::CreateGame() {
	return shared_ptr<Game> (new collapse_three());
}
