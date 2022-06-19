#pragma once

#define FPS 1000/60
#define NOMINMAX

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <functional>
#include <windows.h>
#include <glut.h>
#include <thread>


class Bouncer {
private:
	// Structs
	struct rgb {
		double red, green, blue;
		rgb(double red, double green, double blue) : red(red), green(green), blue(blue) {}
	};

	//Static declarations
	static std::map<int, std::vector<int>> objectPoints;
	static std::vector <std::function<void()>> levels;
	static std::map<int, std::vector<int>> obstaclePoints;
	static double position_x, position_y, gravity, acceleration, gravityAmount, yAxisUpperLimit, yAxisLowerLimit, size;
	static int blockSize;
	static int winX, winY;
	static bool winCondition, movementAllowed;
	static int currentLevel;
	static std::string displayCondition;

	static void specialFunc(int key, int x, int y) {
		//Declaring Necessary Variables
		const double movementAmount = 2.5;
		//Keyboard Events
		switch (key) {
		case GLUT_KEY_UP:
			if (!gravityAmount) {
				//sndPlaySound("jump.wav", SND_ASYNC);
				gravityAmount = gravity;
			}
			break;
		case GLUT_KEY_LEFT:
			acceleration = -movementAmount;
			break;
		case GLUT_KEY_RIGHT:
			acceleration = movementAmount;
			break;
		default:
			break;
		}
	}
	static void keyboardFunc(unsigned char key, int x, int y) {
		switch (key) {
		case 'a':
			if (!gravityAmount) {
				// sndPlaySound(L"jump.wav", SND_ASYNC);
				gravityAmount = gravity;
			}
			break;
		default:
			break;
		}
	}
	static void specialUpFunc(int key, int x, int y) {
		switch (key) {
		case GLUT_KEY_LEFT:
			acceleration = 0;
			break;
		case GLUT_KEY_RIGHT:
			acceleration = 0;
			break;
		}
	}
	static void block(int x, int y, rgb color) {
		// Drawing the block
		glBegin(GL_LINE_LOOP);
		//glColor3f(0.49,0.0, 0.0);
		glColor3f(0.482f, 0.141f, 0.109f);
		glVertex2d(x * size, y * size);
		glVertex2d(x * size + size, y * size);
		glVertex2d(x * size + size, y * size + size);
		glVertex2d(x * size, y * size + size);
		glEnd();
		glBegin(GL_QUADS);
		glColor3f(color.red, color.green, color.blue);
		glVertex2d(x * size, y * size);
		glVertex2d(x * size + size, y * size);
		glColor3f(color.red / 2, color.green / 2, color.blue / 2);
		glVertex2d(x * size + size, y * size + size);
		glVertex2d(x * size, y * size + size);
		glEnd();

	}
	static void deathblock(int x, int y, rgb color) {

		glBegin(GL_QUADS);
		glColor3f(color.red / 2, color.green / 2, color.blue / 2);
		glVertex2d(x * size + 2, y * size + 2);
		glVertex2d(x * size + size - 2, y * size + 2);
		glColor3f(color.red, color.green, color.blue);
		glVertex2d(x * size + size - 2, y * size + size - 2);
		glVertex2d(x * size + 2, y * size + size - 2);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.482f, 0.141f, 0.109f);
		glVertex2d(x * size, y * size);
		glVertex2d(x * size + size, y * size);
		glVertex2d(x * size + size, y * size + size);
		glVertex2d(x * size, y * size + size);
		glEnd();
		glBegin(GL_QUADS);
		glColor3f(color.red, color.green, color.blue);
		glVertex2d(x * size, y * size);
		glVertex2d(x * size + size, y * size);
		glColor3f(color.red / 2, color.green / 2, color.blue / 2);
		glVertex2d(x * size + size, y * size + size);
		glVertex2d(x * size, y * size + size);
		glEnd();
	}
	// Functions for OpenGL
	void init() {
		glClearColor(0, 0, 0, 0);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(80, 1, 1, 1000.0);
	}
	static void draw() {
		if (displayCondition == "level") {
			// Drawing Entity
			// Text
			glRasterPos2f(-10.0 + position_x, 75.0 + position_y);
			char c = '1' + currentLevel;
			std::string str = "LEVEL ";
			str += c;
			for (auto i : str) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)i);
			}

			// Main Character
			glPushMatrix();
			glTranslatef(position_x + blockSize / 2, position_y + blockSize / 2, 0);

			bouncer(rgb(1, 0, 0));
			glPopMatrix();

			if (winCondition) { // If winBlock is set, draw it.
				//block(winX, winY, rgb(0.176, 0.511, 0.306));
				block(winX, winY, rgb(0.0, 0.0, 0.8));
			}

			// Drawing the background based on given points.
			for (auto element : objectPoints) {
				for (auto point : element.second) {
					//block(element.first, point, rgb(0.5, 0.7, 0.9));
					block(element.first, point, rgb(1.0, 0.0, 0.0));
					//block(element.first, point, rgb(0.723,0.224,0.169));
				}
			}

			for (auto element : obstaclePoints) {
				for (auto point : element.second) {
					//block(element.first, point, rgb(0.8, 0.2, 0.2));
					deathblock(element.first, point, rgb(0.2, 0.3, 0.4));
				}
			}
		}
		else if (displayCondition == "win") {
			glColor3f(0, 1, 0);
			glRasterPos2f(position_x, position_y);
			std::string str("You Win!");
			for (auto i : str) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)i);
			}
		}
		else if (displayCondition == "death") {
			glColor3f(1, 0, 0);
			glRasterPos2f(position_x, position_y);
			glRasterPos2f(position_x, position_y);
			std::string str("You DIED!");
			for (auto i : str) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)i);
			}
		}
	}
	static void display() {
		//Clear the display
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.83, 0.92, 0.97, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Camera
		gluLookAt(0 + position_x, 0 + position_y, 100, 0 + position_x, 0 + position_y, 0, 0, 1, 0);
		glMatrixMode(GL_MODELVIEW);

		draw();

		//For double buffers. Not sure what that is....
		glutSwapBuffers();
	}
	static void animate(int) {
		movement();

		// New Frame
		glutPostRedisplay();
		glutTimerFunc(FPS, animate, 0);
	}
	static void bouncer(rgb color) {
		// Code for square bouncer.
		/*glBegin(GL_POLYGON);
		glColor3f(color.red, color.green, color.blue);
		glVertex2d(x, y);
		glVertex2d(x + size, y);
		glVertex2d(x + size, y + size);
		glVertex2d(x, y + size);
		glEnd();*/
		//Code for circular bouncer.

		double angle = 0, radiusX = blockSize / 2, radiusY = blockSize / 2;
		//glTranslatef(radiusX, radiusY, 0);
		glBegin(GL_LINES);
		//glColor3f(color.red, color.green, color.blue);
		glColor3f(0.0, 0.0, 0.0);
		for (int i = 0; i < 100; ++i) {
			angle = 2 * 3.1416 * i / 100;
			//glColor3f(1.0/(i+1), 0.3, 1.5/(i+1));
			glVertex3f(cos(angle) * radiusX , sin(angle) * radiusY , 0);
		}
		glEnd();
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		for (int i = 1; i < 100; ++i) {
			angle = 2 * 3.1416 * i / 100;
			//glColor3f(1.0/(i+1), 0.3, 1.5/(i+1));
			glVertex3f(cos(angle) * radiusX, sin(angle) * radiusY, 0);
		}
		glEnd();

		glRotatef((int)position_x * 50, 0, 0, 1);
		glBegin(GL_POLYGON);
		//glColor3f(color.red, color.green, color.blue);
		for (int i = 0; i < 100; ++i) {
			angle = 2 * 3.1416 * i / 100;
			glColor3f(1.0, 0.75 / i, 0.0);
			glVertex3f(cos(angle) * radiusX, sin(angle) * radiusY, 0);
		}
		glEnd();

	}

	// Gameplay functions.
	static void nextLevel() {
		if (levels.size()) { // If there are any levels.
			sndPlaySound("win.wav", SND_ASYNC);
			std::thread th(showMessage, "win");
			th.detach();
			// Reposition main character to start.
			/*position_x = 0;
			position_y = 10;*/
			// Trun off win condition in case it was not set on the next level.
			winCondition = false;
			// clear and save the new level information on ObjectPoints.
			objectPoints.clear();
			obstaclePoints.clear();
			currentLevel = (currentLevel + 1) % levels.size(); // Change level index.
			levels.at(currentLevel)();
		}
	}

	static void showMessage(std::string str) {
		displayCondition = str; // Change the display to specified by parameter.

		// Turning off gravity while game is paused.
		int tempGravity = gravity;
		movementAllowed = false;
		gravity = 0;
		gravityAmount = 0;
		Sleep(2000);
		// Start the new level with reseting everything necessary.
		position_x = 0;
		position_y = 100;
		sndPlaySound("background.wav", SND_ASYNC | SND_LOOP);
		displayCondition = "level";
		gravity = tempGravity;
		movementAllowed = true;
	}

	static void death() { // Can be used as a lose condition.
		sndPlaySound("lose_extreme.wav", SND_ASYNC);
		std::thread th(showMessage, "death");
		th.detach();
		gravityAmount = 0;
		position_x = 0;
		position_y = 100;
	}

	static void movement() {
		// std::cout << "Position y : " << position_y << "\n";
	   //std::cout << gravityAmount << "\n";
	   // Declarations
		bool canMove = true;
		double tempUpperLimit = INT32_MAX, tempLowerLimit = INT32_MIN;

		// Gravity
		//std::cout << gravityAmount - gravity / blockSize << "\t" << blockSize << "\n";
		if (gravityAmount - gravity / blockSize > -blockSize) {
			gravityAmount -= gravity / 11; // gravity amount applied should always decrease based on current gravity.
		}
		if (position_y + gravityAmount < yAxisLowerLimit) { // If adding the gravity takes the entity out of limit bring it back to limit.
			gravityAmount = 0;
			position_y = yAxisLowerLimit;
		}
		else if (position_y + gravityAmount > yAxisUpperLimit) { // If adding the gravity takes the entity out of limit bring it back to limit.
			gravityAmount = 0;
			position_y = yAxisUpperLimit;
		}
		else { // Change height based on the gravity amount.
			position_y += gravityAmount;
		}

		if (position_y < -300) {
			death();
		}

		//Bouncer movement
		if (acceleration > 0) {
			// All the points form the block the the object will be in after moving left.
			for (auto point : objectPoints[floor((position_x + blockSize) / blockSize)]) {
				//std::cout << point << "\t" << floor(y / blockSize) << "\n";
				if (point == floor(position_y / blockSize)) {
					canMove = false;
				}
			}
			if (canMove && movementAllowed) {
				position_x += acceleration;
			}
		}
		else if (acceleration < 0) {
			// All the points form the block the the object will be in after moving right.
			// As the starting point is at bottem left we need to check
			for (auto point : objectPoints[floor((position_x + acceleration) / blockSize)]) {
				//std::cout << point << "\t" << floor(y / blockSize) << "\n";
				if (point == floor(position_y / blockSize)) {
					canMove = false;
				}
			}
			if (canMove && movementAllowed) {
				position_x += acceleration;
			}
		}

		//Calculating Lower and Upper limit
		for (auto point : objectPoints[floor(position_x / blockSize)]) {
			if (floor(position_y / blockSize) < point) {
				tempUpperLimit = std::min(tempUpperLimit, double(point));
			}
			else {
				tempLowerLimit = std::max(tempLowerLimit, double(point));
			}
		}
		if (int(position_x) % blockSize) {
			for (auto point : objectPoints[floor(position_x / blockSize) + 1]) {
				if (floor(position_y / blockSize) < point) {
					tempUpperLimit = std::min(tempUpperLimit, double(point));
				}
				else {
					tempLowerLimit = std::max(tempLowerLimit, double(point));
				}
			}
		}

		// Lose Condition
		for (auto point : obstaclePoints[floor(position_x / blockSize)]) {
			if (ceil(position_y / blockSize) == point || floor(position_y / blockSize) == point) {
				death();
			}
		}
		if (int(position_x) % blockSize) {
			for (auto point : obstaclePoints[floor(position_x / blockSize) + 1]) {
				if (ceil(position_y / blockSize) == point || floor(position_y / blockSize) == point) {
					death();
				}
			}
		}

		// Win Condition
		if (ceil(position_x / blockSize) == winX && (ceil(position_y / blockSize) == winY || floor(position_y / blockSize) == winY)) {
			nextLevel();
		}
		else if (floor(position_x / blockSize) == winX && ceil(position_y / blockSize) == winY) {
			nextLevel();
		}
		//Trying New Win condition. Previous one does not work if keyboard left/right is not pressed.
		/*if (position_x + blockSize > winX * blockSize && position_x - blockSize < winX * blockSize && ceil(position_y / blockSize) == winY) {
			nextLevel();
		}
		else if (ceil(position_y / blockSize) == winY) {
			std::cout << "Meh\n";
		}*/

		yAxisLowerLimit = (tempLowerLimit + 1) * blockSize;
		yAxisUpperLimit = (tempUpperLimit - 1) * blockSize;
	}
public:
	Bouncer(int& argc, char** argv) {
		size = 10;
		blockSize = 10;
		//Initilizing glut
		glutInit(&argc, argv);
		glutInitWindowSize(800, 800);
		glutInitWindowPosition(300, 100);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
		glutCreateWindow("Bounce");

		init();

		glEnable(GL_DEPTH_TEST);
		glutDisplayFunc(display);
		glutTimerFunc(FPS, animate, 0);
	}
	// Code for adding background.
	void add(int x, int y) {
		// Saving the block data
		try {
			objectPoints[x].push_back(y);
		}
		catch (std::exception e) {
			objectPoints.insert(std::pair<int, std::vector<int> >(x, { y }));
		}
	}
	void horizontal_line(int start_x, int end_x, int y) {
		while (start_x <= end_x) {
			add(start_x, y);
			start_x++;
		}
	}
	void vertical_line(int x, int start_y, int end_y) {
		while (start_y <= end_y) {
			add(x, start_y);
			start_y++;
		}
	}
	void square(int start_x, int end_x, int start_y, int end_y) {
		while (start_x <= end_x) {
			vertical_line(start_x, start_y, end_y);
			start_x++;
		}
	}
	void winBlock(int x, int y) {
		winCondition = true;
		winX = x;
		winY = y;
	}

	void loseBlock(int x, int y) {
		// Saving the block data
		try {
			obstaclePoints[x].push_back(y);
		}
		catch (std::exception e) {
			obstaclePoints.insert(std::pair<int, std::vector<int> >(x, { y }));
		}
	}

	//Code for game.
	void test() {
		winCondition = false;
		glutMainLoop();
	}
	void move() {
		//Keyboard Events
		glutSpecialFunc(specialFunc);
		glutKeyboardFunc(keyboardFunc);
		glutSpecialUpFunc(specialUpFunc);
	}
	void play() {
		winCondition = false;
		if (levels.size()) {
			levels.at(currentLevel)();
		}
		// std::thread background([]() {while (1) { std::cout << "Hello"; }});
		sndPlaySound("background.wav", SND_ASYNC | SND_LOOP);

		glutMainLoop();
	}
	void addLevel(std::function<void()> func) {
		levels.push_back(func);
	}
};

std::map<int, std::vector<int>> Bouncer::objectPoints;
std::map<int, std::vector<int>> Bouncer::obstaclePoints;
std::vector <std::function<void()>> Bouncer::levels;
double Bouncer::position_x, Bouncer::position_y, Bouncer::gravity = 10, Bouncer::acceleration, Bouncer::gravityAmount, Bouncer::yAxisUpperLimit, Bouncer::yAxisLowerLimit, Bouncer::size;
int Bouncer::blockSize, Bouncer::winX, Bouncer::winY, Bouncer::currentLevel = 0;
bool Bouncer::winCondition = false, Bouncer::movementAllowed = true;
std::string Bouncer::displayCondition("level");
