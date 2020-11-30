#include "Map.h"
#include <SFML\Graphics.hpp>
#define PI 3.1415926535


Map::Map(int mw, int mh)
{
	fov = PI / 4;//Field of view in radians
	deltaangle = fov / raysnum;//space between rays
	tilesz = 5;//tile size

	this->m_w = mw;
	this->m_h = mh;

	player.pa = 0;
	player.px = 20;
	player.py = 50;
	player.pdx = cos(player.pa);
	player.pdy = sin(player.pa);
	player.radius = 2;

	distance = raysnum / (2 * tan(fov/2));//some math(distance to wall size)
	proj_cf = 8*distance * tilesz;//some math(distance to wall size)

	mapx = 40;//horizontal tiles count
	mapy = 40;//vertical tiles count
	maps = 1600;//map area, 40x40
	bool tempmap[40][40] = {//our tile map, 1=wall, 2=free space
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	w = mapx * tilesz;
	h = mapy * tilesz;


	memcpy(&tilemap, &tempmap, sizeof(tempmap));//temporary tilemap > tilemap
	memset(&tempmap, 0, sizeof(tempmap));//free memory

	wall2d.setSize(sf::Vector2f(tilesz, tilesz));//2d obstacle size;

	
	p_shape.setRadius(player.radius);
	p_shape.setFillColor(sf::Color::Red);
	p_shape.setPosition(player.px, player.py);
	for (int i = 0; i < raysnum*2; i++)
	{
		rays[i].color = sf::Color::Green;//rays color
	}


	floor.setFillColor(sf::Color(255, 100, 100));//floor
	floor.setSize(sf::Vector2f(m_w, m_h / 2));
	floor.setPosition(sf::Vector2f(0, m_h / 2));

	sky.setFillColor(sf::Color(50, 50, 255));//sky
	sky.setSize(sf::Vector2f(m_w, m_h / 2));
	sky.setPosition(sf::Vector2f(0, 0));
}


void Map::CastRays(sf::RenderWindow & wind)
{

	double rayang = player.pa - fov / 2;//ray angle 
	float ray_x, ray_y, cos_a, sin_a;//ray position, cos, sin


	for (int i = 0; i < raysnum * 2; i++)
	{
		if (i % 2 == 0)
		{
			rays[i].position = sf::Vector2f(player.px + player.radius, player.py + player.radius);
			/* 
			We need to set positions of 2 points to draw our rays
			Every even array item is player position 
			*/
			continue;
		}
		cos_a = cos(rayang);
		sin_a = sin(rayang);

		for (float depth = 0; depth < MAX_DEPTH; depth+=0.5)//transform ray until it hits an obstacle
		{
			ray_x = player.px + cos_a * depth;//ray x  coord
			ray_y = player.py + sin_a * depth;//ray y coord
			rays[i].position = sf::Vector2f(ray_x, ray_y);
			if (getTile(ray_x, ray_y)) {
				depth *= cos(player.pa - rayang);//delete fish eye
				int c = 255 / (1 + depth * depth * 0.001);//color from distance

				setWall(sf::Vector2f(int(m_w / raysnum), proj_cf / depth),
					i,
					sf::Color(c,0,0));

				wind.draw(wall3d);
				break;
			}
		}

		rayang += deltaangle;//space between rays

	}
}

void Map::KbControl(sf::RenderWindow & wind)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.pa += 0.02;
		if (player.pa<0)
		{
			player.pa += 2 * PI;//function resets the angle of view every 360 degrees(2PI)

		}
		player.pdx = cos(player.pa)/3;//player delta x
		player.pdy = sin(player.pa)/3;//player delta y

		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.pa -= 0.02;
		if (player.pa >2 * PI)
		{
			player.pa -= 2 * PI;//function resets the angle of view every 360 degrees(2PI)

		}
		player.pdx = cos(player.pa)/3;//player delta x
		player.pdy = sin(player.pa)/3;//player delta y

		
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)&&getTile(player.px+player.pdx, player.py+player.pdy)<1)
	{
		player.px += player.pdx;
		player.py += player.pdy;
		p_shape.setPosition(player.px, player.py);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && getTile(player.px - player.pdx, player.py - player.pdy)<1)
	{
		player.px -= player.pdx;
		player.py -= player.pdy;
		p_shape.setPosition(player.px, player.py);
	}

	
}

//void Map::MControl(sf::RenderWindow & wind)
//{
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
//	{
//		int mx = sf::Mouse::getPosition(wind).x;
//		int my = sf::Mouse::getPosition(wind).y;
//
//		if (mx > 0 && mx < mapx&&my>0 && my < mapy)
//		{
//			tilemap[mx][my] = 1;
//			updateTiles();
//		}
//	}
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
//	{
//		int mx = sf::Mouse::getPosition(wind).x;
//		int my = sf::Mouse::getPosition(wind).y;
//
//		if (mx > 0 && mx < mapx&&my>0 && my < mapy)
//		{
//			tilemap[mx][my] = 0;
//			updateTiles();
//		}
//	}
//}




void Map::Update()
{
	
	sf::RenderWindow window(sf::VideoMode(m_w, m_h), "Ray Casting");
	window.setFramerateLimit(100);
	
	sf::RenderTexture maptxtr;//prerender map texture
	maptxtr.create(tilesz*mapx, tilesz*mapy);
	maptxtr.clear(sf::Color::Black);


	for (int y = 0; y < mapy; y++)
	{
		for (int x = 0; x < mapx; x++)
		{
			if (tilemap[x][y])
			{
				wall2d.setFillColor(sf::Color::White);//wall or free space?
			}
			else
			{
				wall2d.setFillColor(sf::Color::Black);
			}
			wall2d.setPosition(sf::Vector2f(x * tilesz, y * tilesz));
			maptxtr.draw(wall2d);
		}
	}
	maptxtr.display();
	mapsprt.setTexture(maptxtr.getTexture());

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		KbControl(window);

		window.clear();
		Draw(window);
		window.display();
	}

}

bool Map::getTile(float x, float y)
{
	return (tilemap[int(x / tilesz)][int(y / tilesz)]);
}

void Map::Draw(sf::RenderWindow & wind) {
	wind.draw(floor);
	wind.draw(sky);
	CastRays(wind);
	wind.draw(mapsprt);
	wind.draw(rays, raysnum * 2, sf::Lines);
	wind.draw(p_shape);

}



void Map::setWall(sf::Vector2f size, int index, sf::Color col=sf::Color::Red)
{
	wall3d.setSize(size);
	wall3d.setPosition(sf::Vector2f((index - 1)*wall3d.getSize().x / 2, m_h / 2 - (int)wall3d.getSize().y / 2));
	wall3d.setFillColor(col);
}
