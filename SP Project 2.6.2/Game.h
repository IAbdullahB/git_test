#pragma once
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace sf;
using namespace std;

struct Game
{

private:

	RenderWindow* window; 
	Event ev;

	// mouse pos
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	// logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	float maxEnemies;
	bool mouseHeld;


	// objects
	vector<RectangleShape> enemies;
	RectangleShape enemy;


	
	// initials
	
	void initVariables();
	void initWindow();
	void initEnemy();

	
public:
	Game();
	virtual ~Game();

	// accessors

	const bool running() const;
	const bool getEndGame() const;



	// functions
	void spwanEnemy();
	void pollEvents();
	void updateMousePos();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();

};
