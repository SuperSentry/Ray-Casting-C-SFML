#include <SFML/Graphics.hpp>
#include "Map.h"
#include <thread>

int main()
{

	Map map = Map(1200, 600);
	
	std::thread main_thread(&Map::Update, &map);
	main_thread.join();

	
	return 0;
}