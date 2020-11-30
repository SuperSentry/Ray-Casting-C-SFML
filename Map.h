#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>

#define raysnum 100
#define MAX_DEPTH 200

class Map 
{
private:
	sf::Vertex rays[raysnum*2];
	sf::Sprite mapsprt;//map preload
	sf::CircleShape p_shape;//player shape on minimap
	sf::RectangleShape wall2d;//2d wall
	sf::RectangleShape wall3d;//2d wall
	sf::RectangleShape floor;
	sf::RectangleShape sky;

	Player player;


	bool tilemap[40][40];//map
	double m_w, m_h, deltaangle, fov, distance, proj_cf;
	int mapx, mapy, maps, tilesz, w, h;
public:

	Map(int mw, int mh);
	void KbControl(sf::RenderWindow & wind);
	//void MControl(sf::RenderWindow & wind);
	void Update();
	bool getTile(float x, float y);
	void CastRays(sf::RenderWindow & wind);
	void Draw(sf::RenderWindow & wind);
	void setWall(sf::Vector2f size, int index, sf::Color col);
	
};
