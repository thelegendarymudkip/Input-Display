#include <SFML\Graphics.hpp>
#include <fstream>
#include <Windows.h>

sf::RenderWindow window;
sf::Sprite cSprite, bSel, bSt, bL, bR;
sf::Texture cTexture, ssPos, lrPos;
sf::RectangleShape dUp(sf::Vector2f(20, 21)), dDown(sf::Vector2f(21, 21)), dLeft(sf::Vector2f(21, 21)), dRight(sf::Vector2f(21, 21));
sf::CircleShape bA(15), bB(15), bX(15), bY(15);
sf::Vector2i windowPosition;
sf::VideoMode desktop;

std::ifstream bg;
std::ofstream keep;

float dX, dY;
bool l, r, left, right, up, down, a, b, x, y, sel, st;
short unsigned int i, controllerPort, framesPerSecond, intR, intG, intB;


void readSettings()
{
	desktop = sf::VideoMode::getDesktopMode();
	bg.open("settings.txt");

	if (bg.is_open())
	{

		bg >> intR;
		intR = intR & 255; //mod 256

		bg >> intG;
		intG = intG & 255; //mod 256

		bg >> intB;
		intB = intB & 255; //mod 256

		bg >> windowPosition.x;
		windowPosition.x = windowPosition.x % desktop.width;

		bg >> windowPosition.y;
		windowPosition.y = windowPosition.y % desktop.height;

		bg >> controllerPort;
		controllerPort = controllerPort & 7; //mod 8;

		bg >> framesPerSecond;

		if (framesPerSecond > 120 || framesPerSecond <= 0)
		{
			framesPerSecond = 60; //No, I'm not letting you run it that fast.
		}

		bg.close();

	}

	else
	{

		intR = 255;
		intG = 255;
		intB = 255;

		controllerPort = 0;

		framesPerSecond = 60;

		MessageBox(NULL, (LPCWSTR)L"Settings.txt not found, using defaults.", (LPCWSTR)L"Resource Missing", MB_ICONEXCLAMATION);

	}

}

void initWindow()
{

	readSettings();

	sf::ContextSettings settings;
	window.create(sf::VideoMode(400, 177), "SNES Input Display", sf::Style::Close);

	if (!cTexture.loadFromFile("resources/controller.png"))
	{

		MessageBox(NULL, (LPCWSTR)L"controller.png not found.", (LPCWSTR)L"Resource Missing", MB_ICONEXCLAMATION);

	}

	if (!ssPos.loadFromFile("resources/ss.png"))
	{

		MessageBox(NULL, (LPCWSTR)L"ss.png not found.", (LPCWSTR)L"Resource Missing", MB_ICONEXCLAMATION);

	}

	if (!lrPos.loadFromFile("resources/LR.png"))
	{

		MessageBox(NULL, (LPCWSTR)L"lr.png not found.", (LPCWSTR)L"Resource Missing", MB_ICONEXCLAMATION);

	}


	dLeft.setPosition(51, 80);
	dRight.setPosition(95, 80);
	dUp.setPosition(74, 58);
	dDown.setPosition(73, 102);
	bSel.setPosition(144, 84);

	bSt.setPosition(188, 84);
	bY.setPosition(262, 75);
	bA.setPosition(338, 75);
	bX.setPosition(300, 44);
	bB.setPosition(300, 104);
	bL.setPosition(78, 2);
	bR.setPosition(295, 3);

	dUp.setFillColor(sf::Color(255, 0, 0, 0));
	dDown.setFillColor(sf::Color(255, 0, 0, 0));
	dLeft.setFillColor(sf::Color(255, 0, 0, 0));
	dRight.setFillColor(sf::Color(255, 0, 0, 0));

	bA.setFillColor(sf::Color(127, 0, 0, 0));
	bB.setFillColor(sf::Color(127, 127, 0, 0));
	bX.setFillColor(sf::Color(0, 0, 127, 0));
	bY.setFillColor(sf::Color(0, 127, 0, 0));

	cSprite.setTexture(cTexture);

	bSel.setTexture(ssPos);
	bSt.setTexture(ssPos);
	bL.setTexture(lrPos);
	bR.setTexture(lrPos);

	bR.setOrigin(25, 2);
	bR.setScale(-1, 1);

	desktop = sf::VideoMode::getDesktopMode();

	window.setPosition(windowPosition);
	window.setFramerateLimit(framesPerSecond);

}

void getInput()
{
	sf::Joystick::update();

	if (sf::Joystick::isConnected(controllerPort))
	{
		if (sf::Joystick::getButtonCount(controllerPort)>=10)
		{
			x = sf::Joystick::isButtonPressed(controllerPort, 0);
			a = sf::Joystick::isButtonPressed(controllerPort, 1);
			b = sf::Joystick::isButtonPressed(controllerPort, 2);
			y = sf::Joystick::isButtonPressed(controllerPort, 3);
			l = sf::Joystick::isButtonPressed(controllerPort, 6);
			r = sf::Joystick::isButtonPressed(controllerPort, 7);
			sel = sf::Joystick::isButtonPressed(controllerPort, 8);
			st = sf::Joystick::isButtonPressed(controllerPort, 9);
		}

		if (sf::Joystick::hasAxis(controllerPort, sf::Joystick::X))
			dX = sf::Joystick::getAxisPosition(controllerPort, sf::Joystick::X);
		else
			dX = 0;

		if (sf::Joystick::hasAxis(controllerPort, sf::Joystick::Y))
			dY = sf::Joystick::getAxisPosition(controllerPort, sf::Joystick::Y);
		else
			dY = 0;

	}

	else
	{

		x = false;
		a = false;
		b = false;
		y = false;
		l = false;
		r = false;
		sel = false;
		st = false;

		dX = 0;
		dY = 0;

	}

}

void displayInput()
{

	if (x)
		bX.setFillColor(sf::Color(0, 0, 127, 255));
	else
		bX.setFillColor(sf::Color(0, 0, 127, 0));

	if (y)
		bY.setFillColor(sf::Color(0, 127, 0, 255));
	else
		bY.setFillColor(sf::Color(0, 127, 0, 0));

	if (a)
		bA.setFillColor(sf::Color(127, 0, 0, 255));
	else
		bA.setFillColor(sf::Color(127, 0, 0, 0));

	if (b)
		bB.setFillColor(sf::Color(127, 127, 0, 255));
	else
		bB.setFillColor(sf::Color(127, 127, 0, 0));

	if (l)
		bL.setColor(sf::Color(255, 255, 255, 255));
	else
		bL.setColor(sf::Color(255, 255, 255, 0));

	if (r)
		bR.setColor(sf::Color(255, 255, 255, 255));
	else
		bR.setColor(sf::Color(255, 255, 255, 0));

	if (sel)
		bSel.setColor(sf::Color(255, 255, 255, 255));
	else
		bSel.setColor(sf::Color(255, 255, 255, 0));

	if (st)
		bSt.setColor(sf::Color(255, 255, 255, 255));
	else
		bSt.setColor(sf::Color(255, 255, 255, 0));

	if (dX <= -1)
		dLeft.setFillColor(sf::Color(255, 0, 0, 255));
	else
		dLeft.setFillColor(sf::Color(255, 0, 0, 0));

	if (dX >= 1)
		dRight.setFillColor(sf::Color(255, 0, 0, 255));
	else
		dRight.setFillColor(sf::Color(255, 0, 0, 0));

	if (dY <= -1)
		dUp.setFillColor(sf::Color(255, 0, 0, 255));
	else
		dUp.setFillColor(sf::Color(255, 0, 0, 0));

	if (dY >= 1)
		dDown.setFillColor(sf::Color(255, 0, 0, 255));
	else
		dDown.setFillColor(sf::Color(255, 0, 0, 0));

	window.clear(sf::Color(intR, intG, intB));
	window.draw(cSprite);

	window.draw(dUp);
	window.draw(dDown);
	window.draw(dLeft);
	window.draw(dRight);

	window.draw(bSel);
	window.draw(bSt);
	window.draw(bA);
	window.draw(bB);
	window.draw(bX);
	window.draw(bY);
	window.draw(bL);
	window.draw(bR);

	window.display();

}

void writeSettings()
{
	windowPosition = window.getPosition();

	keep.open("settings.txt");

	keep << intR << "\n";
	keep << intG << "\n";
	keep << intB << "\n";
	keep << controllerPort << "\n";
	keep << windowPosition.x << "\n";
	keep << windowPosition.y << "\n";
	keep << framesPerSecond;

	keep.close();
}

int main()
{

	initWindow();

	while (window.isOpen())
	{

		sf::Event event;

		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{

				writeSettings();

				window.close();

			}

		}

		getInput();
		displayInput();

	}

	return 0;

}