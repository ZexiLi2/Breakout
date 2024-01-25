// Fronton.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
// Zexi Li Li
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <sstream>
#include <iostream>
#include "Funcions.h"
using namespace std;
using namespace sf;
//brick:
const int numBricks = 9;	//number of bricks
RectangleShape brick[numBricks];	//array
float separation = 150.0f;	//space between bricks
//funcions:

//void UpdateInput(RenderWindow& finestre, RectangleShape& player) {
//
//}
//void Update(float dt, CircleShape& bola, RectangleShape& player,
//	float& ballSpeedX, float& ballSpeedY);

void Draw(RenderWindow& window, Sprite& spriteBackground, CircleShape& bola, Sprite&
	spritePlayer, Text messageText) {
	 {
		window.clear();
		window.draw(spriteBackground);

		window.draw(bola);
		window.draw(spritePlayer);
		window.draw(messageText);
		for (int i = 0; i < numBricks; ++i) //draw bricks
		{
			window.draw(brick[i]);
		}
		// Show everything we just drew
		window.display();
	}
}
//int ColisioAmbBola(CircleShape& bola, Sprite& spritePlayer, int
//	incre_yc) {
//
//}

const float ballSpeedBase = 7.0f;
const float playerSpeed = 9.0f;
const int x_min = 0, x_max = 800;
const int y_min = 0, y_max = 600;
const int incre_xr = 10, incre_yr = 10;
const int longitut = 100, amplada = 20, radi = 25;

int main()
{
	Vector2f viewSize(1920, 1080);
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Atarie Brakeout");
	window.setFramerateLimit(75);

	//font
	Font font;
	font.loadFromFile("fonts/gang_wolfik.ttf");
	Text messageText;
	messageText.setFont(font);
	messageText.setString("Wellecom to Atarie Brakeout");
	messageText.setCharacterSize(175);
	messageText.setFillColor(Color(Color(247, 197, 177, 255)));
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	messageText.setStyle(Text::Bold);

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;
	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/retropaint.png");
	// Create a sprite
	Sprite spriteBackground;
	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);
	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);


	//texture player
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(700, 950);
	spritePlayer.setScale(0.75, 0.75);
	spritePlayer.setRotation(270);	//270 és el correcte
	// Control the player input
	bool acceptInput = false;
	//player movement
	int changeX = 0;
	int changeY = 0;

	//si arriba a l'esquerre reapareix a la dreta no funciona btw
	bool playerActive = false;
	float playerSpeed = 0.0f;
	
	//ball, spawn no centre
	CircleShape bola(radi);
	bola.setFillColor(Color::Black);
	bola.setOrigin(bola.getRadius(), bola.getRadius());
	bola.setPosition(viewSize.x / 2, viewSize.y / 2); //per alguna raó la pilota es genera a la cantonada
	//bola.setPosition(400.0f - bola.getRadius(), 300.0f - bola.getRadius());

	bola.setPointCount(20);	//arestes cercle
	bola.setRadius(25);	//radi bola (25 default)
	float ballX = 1920;
	float ballY = 1080;
	float ballSpeed = 30.0f;

	const float LEFT = -1;
	const float RIGHT = 1;
	const float UP = -1;
	const float DOWN = 1;
	float ballDirectionX = RIGHT;
	float ballDirectionY = DOWN;
	float speed = 7.0;	//velocitat bola (7.0 default)
	// Variables to control time itself
	Clock clock;

	/*RectangleShape brick;
	brick.setFillColor(Color::Green);
	brick.setPosition(50, 20);
	brick.setSize(Vector2f(175, 100));
	const int numBrick = 7;
	const int distance = 150;
	breek RectangleShape[numBrick];
	for (int i = 0; i < brick; i++) {
		
	}*/
	//const int numBricks = 9;	//number of bricks
	//RectangleShape brick[numBricks];	//array
	//float separation = 150.0f;	//space between bricks
	for (int i = 0; i < numBricks; ++i)
	{
		brick[i].setSize(Vector2f(175.0f, 100.0f));  // Set the size of the rectangle
		brick[i].setFillColor(Color(192, 218, 46, 250));	// Set the fill color (rgbacolorpicker.com)
		brick[i].setPosition(50.0f + (50.0f + separation) * i, 20.0f);       // Set the position of the rectangle
	}
	// Track whether the game is running
	bool paused = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//si la tecla esc es apretada, llavors tancarà el programa
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				paused = false;
			}
			if (event.type == Event::KeyReleased && !paused)
			{
				//Listen for key presses again
				acceptInput = true;
				// hide axe
				bola.setPosition(2000, bola.getPosition().y);
			}
			// Move the player into position
			acceptInput = true;

			if (Keyboard::isKeyPressed(Keyboard::A))
				changeX = -10;

			else if (Keyboard::isKeyPressed(Keyboard::D))
				changeX = 10;

			else {
				changeX = 0;
			}
			//easter egg (
			if (Keyboard::isKeyPressed(Keyboard::Quote))
				changeY = -10;
			else if (Keyboard::isKeyPressed(Keyboard::Hyphen))
				changeY = 10;
			else {
				changeY = 0;
			}

			// Measure time
			Time dt = clock.restart();
			Time predt = clock.getElapsedTime();

		}
		//hitbox
		FloatRect hitboxpl = spritePlayer.getGlobalBounds();
		FloatRect hitboxbo = bola.getGlobalBounds();
		if (hitboxbo.intersects(hitboxpl)  ) {
			// Collision detected
			//ballDirectionX *= -ballDirectionX;
			ballDirectionY *= -ballDirectionY;
		}
	
		for (int i = 0; i < numBricks; ++i)
		{
			if (hitboxbo.intersects(brick[i].getGlobalBounds()))
			{
				// Collision detected, make the rectangle disappear
				brick[i].setSize(sf::Vector2f(0.0f, 0.0f));
				ballDirectionY *= -ballDirectionY;
			}
		}

		// Measure time
		Time dt = clock.restart();
		Time predt = clock.getElapsedTime();
		// Bola moviment
		if (ballX > 1920) {
			// Ball is near right of screen
			ballDirectionX = LEFT;
		}
		else if (ballX < 0) {
			// Ball shape is near left of screen
			ballDirectionX = RIGHT;
		}
		if (ballY < 0) {
			// Ball shape is near top of screen
			ballDirectionY = DOWN;
		}
		if (ballY == 1080) {
			// Ball shape is near bottom of screen
			ballDirectionY = UP;
			paused = true;
			//messageText.setString("<player> has dyed");
		}
		
		ballX = ballX + speed * ballDirectionX;
		ballY = ballY + speed * ballDirectionY;
		bola.setPosition(ballX, ballY);
		
		// Has the player reached the right hand edge of the screen?
		if (spritePlayer.getPosition().x < -100)
		{
			playerActive = false;
		}

		Draw(window, spriteBackground, bola, spritePlayer, messageText);
		
		spritePlayer.move(changeX, changeY);

	}
}
