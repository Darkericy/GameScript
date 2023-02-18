#include "GFactory.h"
Game* CollapseFactory::CreateGame() {
	return new collapse_three();
}
