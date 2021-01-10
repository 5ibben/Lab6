#pragma once
#include "SDL.h"
#include "Snake.h"
using namespace std;

//test of the DoublyLinkedList class
void linkedListTest()
{
	std::cout << "Tests for DoublyLinkedList...\n\n";
	//List Object
	DoublyLinkedList list;
	//Adding...
	list.add(new Node(12), 0);
	list.add(new Node(5), 0);
	list.add(new Node(66), 0);
	list.add(new Node(7), 0);

	//Size...
	std::cout << "size of list: " << list.size() << std::endl;

	//Print...
	std::cout << "Printing list forward...\n";
	list.display_forward();
	std::cout << "Printing list backward...\n";
	list.display_backward();

	//Remove...
	std::cout << "Removing Node at index 2...\n";
	list.remove(2);

	//Replace...
	std::cout << "Replacing the first node...\n";
	list.replace(list.nodeAt(0), new Node(77));

	//Printing after removal and replacement...
	std::cout << "Printing list forward...\n";
	list.display_forward();
	std::cout << "Printing list backward...\n";
	list.display_backward();

	//data by index
	std::cout << "Data at index 2: " << list[2] << std::endl;
	//assign data at index
	std::cout << "Changing data at index 1 to '33'...\n";
	list[1] = 33;
	std::cout << "Data at index 1: " << list[1] << std::endl;
	//comparison by index
	if (list[1] == 33 && list[2] != 5)
		cout << "Comparison is working!\n\n";
}

int main(int argc, char* argv[])
{
	linkedListTest();
	
	//some variables for game settings
	Point2D mapSize(1200, 600);
	int scale=30;
	int gameSpeed = 7;
	int players= 2;
	//game settings
	cout << "\n\t~~~~~~SNAKE~~~~~~\n\n1: Single player\n2: Two player\n";
	int x;
	cin >> x;
	switch (x)
	{
	case 1:
		players = 1;
		break;
	case 2:
		players = 2;
		scale = 30;
		break;
	}
	cout << "\nmaps size:\n1: Small\n2: Medium\n3: Large\n";
	cin >> x;
	switch (x)
	{
	case 1:
		mapSize = Point2D(600, 300);
		gameSpeed = 15;
		break;
	case 2:
		mapSize = Point2D(1200, 600);
		gameSpeed = 20;
		break;
	case 3:
		mapSize = Point2D(2400, 1200);
		gameSpeed = 40;
		break;
	}
	cout << "\nPRESS SPACE TO START!\n\n";


	//SDL subsystem, window, and renderer initialization
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Snakey", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mapSize.x, mapSize.y, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


	// game object initialization and startscreen bullshit
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	Food* food1 = new Food(renderer, mapSize, scale);
	Snake* snake1 = new Snake(renderer, food1, mapSize, scale, Point2D(0, mapSize.y / 3 - scale),mapSize.x/120);
	Snake* snake2 = new Snake(renderer, food1, mapSize, scale, Point2D(mapSize.x / 2 - scale, mapSize.y / 3 - scale), mapSize.x / 120);
	snake1->setOpponent(snake2);
	snake2->setOpponent(snake1);
	snake2->color(0, 0, 255);
	//only for startscreen
	Snake* snake3 = new Snake(renderer, food1, mapSize, scale, Point2D(0, mapSize.y / 4 - scale), mapSize.x / 120);
	Snake* snake4 = new Snake(renderer, food1, mapSize, scale, Point2D(mapSize.x / 3 - scale, mapSize.y / 4 - scale), mapSize.x / 120);
	snake3->setOpponent(snake4);
	snake4->setOpponent(snake3);
	snake3->color(255, 255, 0);
	snake4->color(255, 0, 0);
	
	// event declaration
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);

	//gameloop, startstate
	bool startGame = true;
	bool gameLoop = true;
	while (gameLoop)
	{
		//fetch event from the event queue 
		SDL_PollEvent(&event);

		if (!startGame)
		{
			//snake1 controls
			if (state[SDL_SCANCODE_W])
				snake1->setDirection(0);
			if (state[SDL_SCANCODE_S])
				snake1->setDirection(1);
			if (state[SDL_SCANCODE_A])
				snake1->setDirection(2);
			if (state[SDL_SCANCODE_D])
				snake1->setDirection(3);
			//snake2 controls
			if (state[SDL_SCANCODE_KP_8])
				snake2->setDirection(0);
			if (state[SDL_SCANCODE_KP_5])
				snake2->setDirection(1);
			if (state[SDL_SCANCODE_KP_4])
				snake2->setDirection(2);
			if (state[SDL_SCANCODE_KP_6])
				snake2->setDirection(3);
		}

		//general input
		switch (event.type)
		{
		case SDL_QUIT://on event application quit.
			gameLoop = false;
			break;
		case SDL_KEYDOWN://on event keydown.
			switch (event.key.keysym.sym)
			{

			case SDLK_x://exit
				gameLoop = false;
				break;

			case SDLK_g://grow snakes
				cout << "growing snake...\n";
				snake1->grow();
				if (players == 2)
					snake2->grow();
				break;

			case SDLK_SPACE://start/restart
				//resets the game to start state
				if (startGame || !snake1->alive)
				{
					gameSpeed = 7;
					if (startGame)
						startGame = false;
						delete snake1;
						delete food1;
						if (players==2)
							delete snake2;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderClear(renderer);
					food1 = new Food(renderer, mapSize,scale);
					food1->render();
					snake1 = new Snake(renderer, food1, mapSize, scale);
					if (players == 2)
					{
						snake2 = new Snake(renderer, food1, mapSize, scale, Point2D(mapSize.x -scale, mapSize.y - scale));
						snake1->setOpponent(snake2);
						snake2->setOpponent(snake1);
						snake2->color(0, 0, 255);
						snake2->setPlayer(2);
					}
				}
				break;

			case SDLK_KP_PLUS://increase speed
				gameSpeed ++;
				cout << "speed = " << gameSpeed << endl;
				break;

			case SDLK_KP_MINUS://decrease speed
				if (1<gameSpeed)
					gameSpeed--;
				cout << "speed = " << gameSpeed << endl;
				break;

			case SDLK_p://pause game
				cout << "GAME PAUSED!\n";
				bool pauseloop = true;
				while (pauseloop)
				{
					SDL_PollEvent(&event);
					switch (event.type)
					{
					case SDL_KEYDOWN://on event keydown.
						switch (event.key.keysym.sym)
						{
						case SDLK_p://unpause game
							pauseloop = false;
							cout << "GAME RESUMED!\n";
							break;
						}
						break;
					}
				}
			}
			break;
		}

		//snake movement and renderer update
		if (snake1->alive)
		{
			if (startGame)
			{
				snake1->move();
				snake2->move();
				snake3->move();
				snake4->move();
			}
			else
			{
				snake1->move();
				if (players==2 && snake2->alive)
					snake2->move();
			}
			SDL_Delay((10 * scale) / gameSpeed);
		SDL_RenderPresent(renderer);//updates screen
		}
	}

	// Tidy up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//cleans up initialized subsystems
	SDL_Quit();
	return 0;
}