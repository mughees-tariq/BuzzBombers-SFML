//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace sf;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.
const int resolutionX = 960;
const int resolutionY = 640;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionY / boxPixelsY; // Total rows on grid
const int gameColumns = resolutionX / boxPixelsX; // Total columns on grid

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//These functions will be used in the menu:
void mainMenu (RenderWindow &window);
void startGame(RenderWindow &window);
void bossLevel(RenderWindow &window);
void highScore(RenderWindow &window);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//These functions will be used during all of the gameplay:
void currentScore (RenderWindow &window, int &score);		//It will display current score
void  displayCans (RenderWindow &window, int sprayCan);		//It will display number of remaining cans

//This function will draw spray can on the screen:
void drawPlayer(RenderWindow &window, float player[], float flower[][3], int &x_cord, float &speed, Sprite &moveSprite, Clock &playerClock);

//This function will draw bullet on the screen:
void drawBullet(RenderWindow &window, float bullet[], float player[], int &x_cord, int &can, int &bullets, Sprite &moveSprite1, Sprite &moveSprite2,
				Clock &moveClock1, Clock &moveClock2);
				
//This function will control the movement of bullet on screen:				
void moveBullet(RenderWindow &window, float bullet[], float player[], int &x_cord, Sprite &moveSprite1, Sprite &moveSprite2, Clock &moveClock);

//This function will draw the humming bird and control all of its attributes:
void  drawBird(RenderWindow &window, float bird[], float bullet[], Sprite &moveSprite, Clock &clock1, Clock &clock2, int &score, 
			  float comb1[][3], int size1, float comb2[][3]={}, int size2 = 0);

//These function will draw existing hives, combs and flowers on screen:
void   drawHive(RenderWindow &window, float   hive[][3], Sprite &moveSprite, int i);
void  drawComb1(RenderWindow &window, float  comb1[][3], Sprite &moveSprite, int i);
void drawFlower(RenderWindow &window, float flower[][3], Sprite &moveSprite, int i);

//These function will do other processes than gameplay:
void levelComplete(RenderWindow &window, int score);
void Score(RenderWindow &window, int score);
void compareScore(RenderWindow &window, int score, char name[]);
void bonus(int scores, int &sprayCans);
void leftHives(int &scores, float hive[][3], int size);
void retryLevel(RenderWindow &window, int &cans, int scores);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Functions for level1:
void level1(RenderWindow &window, int &score, int &sprayCan, int &x_cord, float speed, float player[], float bullet[], float bird[], float flower[][3],
			Sprite &moveSprite1, Sprite &moveSprite2, Sprite &moveSprite3, Sprite &moveSprite4, Sprite &moveSprite5, Sprite &moveSprite6, 
			Sprite &moveSprite7, Texture &texture, RectangleShape &rectangle);

//This is the main function containing all the game thought process:
void gameLogic(RenderWindow &window, int &score, int &bees_on_screen, int &currentFrame, int &bees_to_generate, int &bee_number, int &currentSpeed, 
				int &x_cord, int &spawnBee, int &bees1, int stoppingFrame[], bool &first_time, bool &first_bee, bool bee_move[], bool beeInitialized[],
				bool pollinated[], float &spawnInterval, float &sinceLastSpawn, float player[], float bee1[][4], float bullet[], float comb1[][3], 
				float hive[][3], float bird[], float flower[][3], float stopTime[], float intervalTime[], Sprite &bee1Sprite, Sprite &comb1Sprite, 
				Sprite &birdSprite, Sprite &hiveSprite, Sprite &flowerSprite, Clock &bee1Clock, Clock &comb1Clock, Clock &birdClock, Clock &beeClock, 
				Clock &spawnClock, Clock &birdStart, Clock stopClock[], Clock intervalClock[], Texture &bee1Texture, int size1, int size2);

//This function will calculate how many bees to display on screen:
void beeonScreen(int &bees1, int &bees_on_screen, int &bees_to_generate, int &bee_number, float bee1[][4]);

//This function will spawn bees on screen:
void bee1Spawn(int bound_l, int bound_r, int &spawnBee, bool beeInitialized[], float intervalTime[], float bee1[][4], float &sinceLastSpawn, 
				float &spawnInterval, Clock &spawnClock, Clock intervalClock[]);

//This function will control the movement of the bees on screen:
void bee1Move(int bound_l, int bound_r, int &bees_on_screen, int &currentFrame, int &x_cord, int &spawnBee, int stoppingFrame[], bool bee_move[],
			  int &current_speed, float time_elapsed, float intervalTime[], float stop_time[], float bee1[][4], float comb1[][3], float hive[][3],
			  Clock stopClock[], Clock intervalClock[], Texture &bee1Texture, Sprite &bee1Sprite, RenderWindow &window);			

//This function will generate random combs on screen:
void randomComb(int i, int bound_l, int bound_r, float comb1[][3], int bound1, int bound2);

//This function will generate flowers on the screen:
void flowerGeneration(int i, float bee1[][4], float flower[][3], bool pollinated[], bool &first_bee);

//void hiveGeneration(int i, int &bees, float bee1[][4], float hive[][3]);

//This function will be used to handle different types of collisions that occur during gameplay:
void collisions(int &bees_on_screen, int &score, float bullet[], float bee1[][4], float comb1[][3], float hive[][3], int size1, 
				 int size2, float bee2[][4] = {});

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Functions for collision checking:
bool  bullet_hive_collision(float bullet[], float  hive[][3], int i, int j);
bool  bullet_bee1_collision(float bullet[], float  bee1[][4], int i);
bool  bullet_bee2_collision(float bullet[], float  bee2[][4], int i);
bool bullet_comb1_collision(float bullet[], float comb1[][3], int i);
bool bullet_comb2_collision(float bullet[], float comb2[][3], int i);
bool  bullet_bird_collision(float bullet[], float  bird[]);

bool bee1_comb1_collision(float bee1[][4], float comb1[][3], int i, int j);
bool bee1_comb2_collision(float bee1[][4], float comb2[][3], int i, int j);
bool  bee1_hive_collision(float bee1[][4], float  hive[][3], int i);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
	
	srand(time(0));

	//Declaring RenderWindow.
	RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar | Style::Resize);

	//Used to position your window on every launch. Use according to your needs.
	window.setPosition(Vector2i(500, 200));	   
	
	mainMenu(window);
	
	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//                                                                        //
// Write your functions definitions here. Some have been written for you. //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mainMenu(RenderWindow &window){

	Font font1;
	font1.loadFromFile("Fonts/ARCADE_I.TTF");
	
	Font font2;
	font2.loadFromFile("Fonts/arial.ttf");

	Texture backgroundTexture;
	Sprite backgroundSprite;
	backgroundTexture.loadFromFile("Textures/bg.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	
	Text nameOfGame;
	nameOfGame.setFont(font1);
	nameOfGame.setString("BUZZ BOMBERS");
	nameOfGame.setCharacterSize(50);
	nameOfGame.setPosition(resolutionX/2-290, 50);
	nameOfGame.setFillColor(Color::Yellow);
	
	Text menuHeading;
	menuHeading.setFont(font1);
	menuHeading.setString("Main Menu");
	menuHeading.setCharacterSize(30);
	menuHeading.setPosition(resolutionX/2-130, 150);
	menuHeading.setFillColor(Color(173, 216, 230));
	
	Text copyright;
	copyright.setFont(font2);
	copyright.setString("Muhammad Mughees Tariq Khawaja (24I-0806)");
	copyright.setCharacterSize(15);
	copyright.setPosition(resolutionX/2-155, resolutionY-30);
	copyright.setFillColor(Color::White);
	
	RectangleShape layer(Vector2f(960, 640));
	layer.setFillColor(Color(0,0,0,150));
	
	const int menuOptions = 4;
	
	string options[menuOptions] = {"Start Game", "Boss Level", "High Scores", "Exit Game"};
	
	Text menu[menuOptions];
	RectangleShape box[menuOptions];

	for (int i=0; i<menuOptions; i++){
		menu[i].setFont(font2);
		menu[i].setString(options[i]);
		menu[i].setCharacterSize(30);
		menu[i].setFillColor(Color::White);
		
		box[i].setSize(Vector2f(260, 50));
		box[i].setFillColor(Color::Transparent);
		box[i].setOutlineColor(Color::White);
		box[i].setOutlineThickness(2);
		box[i].setPosition(resolutionX/2-130, 250+75*i);
		}	
		
		menu[0].setPosition(resolutionX/2-80, 255+75*0);
		menu[1].setPosition(resolutionX/2-75, 255+75*1);
		menu[2].setPosition(resolutionX/2-80, 255+75*2);
		menu[3].setPosition(resolutionX/2-70, 255+75*3);
		
	int optionSelected = 0;
	menu[optionSelected].setFillColor(Color::Green);
	
	Music menuMusic;
	menuMusic.openFromFile("Music/Title.ogg");
	menuMusic.play();
	menuMusic.setVolume(50);
	
	while (window.isOpen()){
		Event event;
		
		while (window.pollEvent(event)){
			
			if (event.type == Event::Closed)
				exit(0);
			
			else if (event.type == Event::KeyPressed){
			
				if(event.key.code == Keyboard::Up){
				
					menu[optionSelected].setFillColor(Color::White);
					optionSelected = (optionSelected-1+menuOptions)%menuOptions;
					menu[optionSelected].setFillColor(Color::Green);
					}
			
				else if(event.key.code == Keyboard::Down){
				
					menu[optionSelected].setFillColor(Color::White);
					optionSelected = (optionSelected+1)%menuOptions;
					menu[optionSelected].setFillColor(Color::Green);
					}
			
				else if (event.key.code == Keyboard::Enter){
			
					if (options[optionSelected] == "Start Game"){
						menuMusic.stop();	startGame(window);
						}
				
					else if (options[optionSelected] == "Boss Level")
						bossLevel(window);
					
					else if (options[optionSelected] == "High Scores"){
						menuMusic.stop();	highScore(window);
						}
						
					else 
						exit(0);
					}
				}
			}
	
		window.clear();			
		window.draw(backgroundSprite);
		window.draw(layer);
		window.draw(nameOfGame);
		window.draw(menuHeading);
		window.draw(copyright);
		
		for (int i=0; i<menuOptions; i++){
			
			window.draw( box[i]);
			window.draw(menu[i]);
			
			}

		window.display();
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void bossLevel(RenderWindow &window){
	
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void highScore(RenderWindow &window){
	
	Font font1;
	font1.loadFromFile("Fonts/ARCADE_I.TTF");
	
	Font font2;
	font2.loadFromFile("Fonts/arial.ttf");
	
	fstream scoreFile;
	string names[10] = {};
	int highscores[10] = {};
	
	scoreFile.open("highscores.txt", ios::in);
	
	for (int i=0; i<10; i++){
		
		scoreFile >> names[i];
		scoreFile >> highscores[i]; 		
		}
	
	scoreFile.close();

	Texture backgroundTexture;
	Sprite backgroundSprite;
	backgroundTexture.loadFromFile("Textures/bg.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	
	Text nameOfGame;
	nameOfGame.setFont(font1);
	nameOfGame.setString("BUZZ BOMBERS");
	nameOfGame.setCharacterSize(50);
	nameOfGame.setPosition(resolutionX/2-290, 50);
	nameOfGame.setFillColor(Color::Yellow);
	
	Text heading;
	heading.setFont(font1);
	heading.setString("High Scores");
	heading.setCharacterSize(30);
	heading.setPosition(resolutionX/2-160, 150);
	heading.setFillColor(Color(173, 216, 230));
	
	Music menuMusic;
	menuMusic.openFromFile("Music/Title.ogg");
	menuMusic.play();
	menuMusic.setVolume(50);
	
	Text  name[10];
	Text score[10];
	
	int score_number = 0;
	
	for (int i=0; i<10; i++){
		
		if (names[i] == "\0")
			continue;
		
		score_number++;
		
		name[i].setPosition(resolutionX/2-200, 200+35*score_number);
		name[i].setFont(font2);
		name[i].setCharacterSize(20);
		name[i].setFillColor(Color(152, 255, 152));
		name[i].setString(names[i]);
		
		score[i].setPosition(resolutionX/2+130, 200+35*score_number);
		score[i].setFont(font2);
		score[i].setCharacterSize(20);
		score[i].setFillColor(Color(255, 182, 193));
		score[i].setString(to_string(highscores[i]));
		}
	
	Text copyright;
	copyright.setFont(font2);
	copyright.setString("Muhammad Mughees Tariq Khawaja (24I-0806)");
	copyright.setCharacterSize(15);
	copyright.setPosition(resolutionX/2-155, resolutionY-30);
	copyright.setFillColor(Color::White);
	
	RectangleShape layer(Vector2f(960, 640));
	layer.setFillColor(Color(0,0,0,150));
	
	Text exit;
	exit.setFont(font2);
	exit.setString("(Press escape button to exit to main menu)");
	exit.setCharacterSize(20);
	exit.setPosition(resolutionX/2-200, 190);
	exit.setFillColor(Color::White);
	
	while (window.isOpen()){
		Event event;
		
		while (window.pollEvent(event)){
			
			if (event.type == Event::Closed)
				window.close();
				
			else if (event.type == Event::KeyPressed){
			
				if(event.key.code == Keyboard::Escape){
					menuMusic.stop(); mainMenu(window);
					}
				}	
			}
	
		window.clear();			
		window.draw(backgroundSprite);
		window.draw(layer);
		window.draw(nameOfGame);
		window.draw(heading);
		window.draw(copyright);
		window.draw(exit);

		for (int i=0; i<10; i++){
			
			window.draw(name[i]);
			window.draw(score[i]);
			}

		window.display();
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void startGame(RenderWindow &window){
	
	/*------------------------------------------------------------------------------------------------------------------------------------------*/
	/*
	The 0th index of every array is for x coordinate 
	The 1st index of every array is for y coordinate

	The 2nd index of every array is for checking existence	
	The 3rd index of bees arrays are for left and right movement check
	*/
	/*------------------------------------------------------------------------------------------------------------------------------------------*/
	
	//Initializing Player:
	float player[3] = {};
	player[0] = resolutionX/2-64;
	player[1] = (gameRows - 7) * boxPixelsY;
	player[2] = 1;
	
	float max_player_speed = 800;
	float min_player_speed = 400;
	float player_speed = 600;

	int x_cord = 0; 
	
	/*------------------------------------------------------------------------------------------------------------------------------------------*/

	// Initializing Bullet:
	float bullet[3] = {};
	
	/*------------------------------------------------------------------------------------------------------------------------------------------*/
	
	//Initializing Humming bird:
	float  bird[3] = {};
	
	bird[0] = player[0];
	bird[1] = player[1];
	bird[2] = 0;
	
	/*------------------------------------------------------------------------------------------------------------------------------------------*/	
	
	//Initializing flowers:
	float flower[20][3] = {};	//At max there can be 20 flowers on the screen
	
	/*------------------------------------------------------------------------------------------------------------------------------------------*/
	
	//The ground on which player moves:
	RectangleShape groundRectangle(Vector2f(resolutionX-160, 64));
	groundRectangle.setPosition(80, (gameRows - 4) * boxPixelsY);
	groundRectangle.setFillColor(Color::Green);
	
	/*------------------------------------------------------------------------------------------------------------------------------------------*/
	
	//Loading Textures for player, bullet, slow bee, fast bee, yellow comb, red comb, humming bird and hive:
	Texture playerTexture;
	Sprite playerSprite;
	playerTexture.loadFromFile("Textures/spray.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(2,1.5);
	playerSprite.setTextureRect(IntRect(0, 0, 64, 64));
	playerSprite.setPosition(player[0],player[1]);
	
	Texture bulletTexture;
	Sprite bulletSprite;
	bulletTexture.loadFromFile("Textures/bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setScale(3, 3);
	
	Texture bee1Texture;
	Sprite bee1Sprite;	
	bee1Texture.loadFromFile("Textures/bee.png");
	bee1Sprite.setTexture(bee1Texture);
	bee1Sprite.setTextureRect(IntRect(0,0,64,64));
	bee1Sprite.setScale(1,0.5);

	Texture bee2Texture;
	Sprite bee2Sprite;	
	bee2Texture.loadFromFile("Textures/fastBee.png");
	bee2Sprite.setTexture(bee1Texture);
	bee2Sprite.setTextureRect(IntRect(0,0,64,64));
	bee2Sprite.setScale(1,0.5);

	Texture birdTexture;
	Sprite birdSprite;
	birdTexture.loadFromFile("Textures/bird.png");
	birdSprite.setTexture(birdTexture);
	birdSprite.setTextureRect(IntRect(0,0,64,64));
	birdSprite.setScale(0.5,1);
	
	Texture hiveTexture;
	Sprite hiveSprite;
	hiveTexture.loadFromFile("Textures/hive.png");
	hiveSprite.setTexture(hiveTexture);
	hiveSprite.setScale(1,0.5);
	
	Texture comb1Texture;
	Sprite comb1Sprite;
	comb1Texture.loadFromFile("Textures/honeycomb_yellow.png");
	comb1Sprite.setTexture(comb1Texture);
	comb1Sprite.setScale(1,0.5);
	
	Texture comb2Texture;
	Sprite comb2Sprite;
	comb2Texture.loadFromFile("Textures/honeycomb_red.png");
	comb2Sprite.setTexture(comb2Texture);
	comb2Sprite.setScale(1,0.5);
	
	Texture flowerTexture;
	Sprite flowerSprite;
	flowerTexture.loadFromFile("Textures/flower2.png");
	flowerSprite.setTexture(flowerTexture);
	
	/*------------------------------------------------------------------------------------------------------------------------------------------*/
	
	int score = 0;					//The starting score is zero		
	static int sprayCan = 2;		//The starting spray can are 3
	
	level1(window, score, sprayCan, x_cord, player_speed, player, bullet, bird, flower, playerSprite, bulletSprite, birdSprite, bee1Sprite, 
		   comb1Sprite, hiveSprite, flowerSprite, bee1Texture, groundRectangle);	
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void currentScore(RenderWindow &window, int &score){
	
	Font font;
	font.loadFromFile("Fonts/ARCADE_I.TTF");
	
	Text playerScore;
	playerScore.setFont(font);
	playerScore.setString(to_string(score));
	playerScore.setCharacterSize(36);
	playerScore.setFillColor(Color::Black);
	playerScore.setPosition(resolutionX - 260, (gameRows-3)*boxPixelsY-20);
	window.draw(playerScore);	
	
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void displayCans(RenderWindow &window, int sprayCan){
	
	Texture sprayAvailable;
	Sprite spraySprite;
	
	sprayAvailable.loadFromFile("Textures/spray.png");
	spraySprite.setTexture(sprayAvailable);
	spraySprite.setTextureRect(IntRect(0, 0, 64, 64));
	spraySprite.setColor(Color::Black);
	spraySprite.setScale(0.7, 0.7);
	
	for (int i=0; i<sprayCan; i++){
		
		spraySprite.setPosition(100+40*i, (gameRows-3)*boxPixelsY-28);
		window.draw(spraySprite);
		}
	}
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawPlayer(RenderWindow &window, float player[], float flower[][3], int &x_cord, float &player_speed, Sprite &playerSprite, Clock &playerClock) {

	float time_elapsed = playerClock.getElapsedTime().asSeconds();
	playerClock.restart();
	
	if (!player[2])
		return;
	
	float  left_move = player[0] - player_speed*time_elapsed;
	float right_move = player[0] + player_speed*time_elapsed;
	
	bool left = true;
	bool right = true;
	
	const int playerWidth = 120;
	const int flowerWidth = 40;
	
	
	for (int i=0; i<20; i++){
	
		if (flower[i][2]){
			
			if (left_move < flower[i][0]+flowerWidth && left_move+playerWidth > flower[i][0])
				left = false;
		
			
			if (right_move < flower[i][0]+flowerWidth && right_move+playerWidth > flower[i][0])
				right = false;
			
			}
		}
	
	if (!left && right)
		player[0] = right_move;
		
	else if (!right && left)
		player[0] = left_move;
		
	else if (!left && !right){
		
		int start = 80;
		int end = resolutionX-80-playerWidth;
		bool availableSpace = false;
		
		for (int i=start; i<=end; i++){
					
			bool clearSpace = true;
			
			for (int j=0; j<20; j++){
				
				if (flower[j][2]){
				
					if (i<flower[j][0]+flowerWidth && i+playerWidth>flower[j][0]){
						clearSpace = false;
						break;
						}	
					}
				}
				
			if (clearSpace){
				availableSpace = true;
				player[0] = i;
				break;
				}	
			}
			
		if (!availableSpace)
			player[2] = 0;
		}	
	
	else{
	
		if ((Keyboard::isKeyPressed(Keyboard::Left)) && player[0] > 60 && left)
			player[0] = left_move;	//Moving Left
		
		else if ((Keyboard::isKeyPressed(Keyboard::Right)) && player[0] < resolutionX-60-128 && right)
			player[0] = right_move;	//Moving Right
	
		}
				
	playerSprite.setPosition(player[0],player[1]);
	window.draw(playerSprite);
		
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void moveBullet(RenderWindow &window, float bullet[], float player[], int &x_cord, Sprite &bulletSprite, Sprite &playerSprite, Clock &bulletClock) {
	
	int x_cord_temp = x_cord;
	
	float time_elapsed = bulletClock.getElapsedTime().asSeconds();
	bulletClock.restart();
	
	bullet[1] -= 600*time_elapsed;
	bullet[2] = true;
	
	x_cord+=64;
		
	playerSprite.setTextureRect(IntRect(x_cord, 0, 64, 64));
	
	x_cord-=64;
	
	if(bullet[1]<0)
		bullet[2] = false;
	
	bulletSprite.setPosition(bullet[0], bullet[1]);
	window.draw(bulletSprite);
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawBullet(RenderWindow &window, float bullet[], float player[], int &x_cord, int &sprayCan, int &bullets, Sprite &bulletSprite, 
				Sprite &playerSprite, Clock &bulletClock, Clock &delayClock){
	
	if (delayClock.getElapsedTime().asMilliseconds()<80 && !bullet[2])
		return;
		
	delayClock.restart();
	
	int temp_bullets = bullets;
	
	if (bullets == 0){
		if (sprayCan>0){
			bullets = 56;
			sprayCan--;		
			}
			
		else {
			bullet[2] = 0;
			return;
			}
		}
	
	else if (Keyboard::isKeyPressed(Keyboard::Space) && !bullet[2]){
	
		bullet[0] = player[0] + 42;
		bullet[1] = (gameRows - 8) * boxPixelsY - 16; 
		bullet[2] = true;
		bulletClock.restart();
		bullets--;
		}
	
	if (bullet[1]<(gameRows-17)*boxPixelsY)
		bullet[2] = false;	
	
	if (bullets%8==0 && temp_bullets!=bullets){
		
		if (bullets == 0 || bullets == 56)
			x_cord = 0;	
		else
			x_cord += 128;
			
		playerSprite.setTextureRect(IntRect(x_cord, 0, 64, 64));
		playerSprite.setPosition(player[0], player[1]);
		
		}
		
	
	if (!bullet[2])
		playerSprite.setTextureRect(IntRect(x_cord, 0, 64, 64));
	
	else
		moveBullet(window, bullet, player, x_cord, bulletSprite, playerSprite, bulletClock);	
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool  bullet_hive_collision(float bullet[], float  hive[][3], int i){

	bool collisionX = (bullet[0] < hive[i][0] + 64) && (bullet[0] + 48 > hive[i][0]) && hive[i][2] && bullet[2];
	bool collisionY = (bullet[1] < hive[i][1] + 32) && (bullet[1] + 48 > hive[i][1]) && hive[i][2] && bullet[2];

	if (collisionX && collisionY) return true; else return false;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool  bullet_bee1_collision(float bullet[], float  bee1[][4], int i){

	bool collisionX = (bullet[0] < bee1[i][0] + 64) && (bullet[0] + 48 > bee1[i][0]) && bee1[i][2] && bullet[2];
	bool collisionY = (bullet[1] < bee1[i][1] + 32) && (bullet[1] + 48 > bee1[i][1]) && bee1[i][2] && bullet[2]; 

	if (collisionX && collisionY) return true; else return false;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool  bullet_bee2_collision(float bullet[], float  bee2[][4], int i){

	bool collisionX = (bullet[0] < bee2[i][0] + 64) && (bullet[0] + 48 > bee2[i][0]) && bee2[i][2] && bullet[2];
	bool collisionY = (bullet[1] < bee2[i][1] + 32) && (bullet[1] + 48 > bee2[i][1]) && bee2[i][2] && bullet[2]; 

	if (collisionX && collisionY) return true; else return false;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool bullet_comb1_collision(float bullet[], float comb1[][3], int i){

	bool collisionX = (bullet[0] < comb1[i][0] + 64) && (bullet[0] + 48 > comb1[i][0]) && comb1[i][2] && bullet[2];
	bool collisionY = (bullet[1] < comb1[i][1] + 32) && (bullet[1] + 48 > comb1[i][1]) && comb1[i][2] && bullet[2];

	if (collisionX && collisionY) return true; else return false;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool bullet_comb2_collision(float bullet[], float comb2[][3], int i){

	bool collisionX = (bullet[0] < comb2[i][0] + 64) && (bullet[0] + 48 > comb2[i][0]) && comb2[i][2] && bullet[2];
	bool collisionY = (bullet[1] < comb2[i][1] + 32) && (bullet[1] + 48 > comb2[i][1]) && comb2[i][2] && bullet[2];

	if (collisionX && collisionY) return true; else return false;
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool bee1_comb1_collision(float bee1[][4], float comb1[][3], int i, int j){

	bool collisionX = (bee1[i][0] < comb1[j][0] + 64) && (bee1[i][0] + 64 > comb1[j][0]) && bee1[i][2] && comb1[j][2];
	bool collisionY = (bee1[i][1] < comb1[j][1] + 32) && (bee1[i][1] + 32 > comb1[j][1]) && bee1[i][2] && comb1[j][2];
		
	if (collisionX && collisionY) return true; else return false;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool bee1_comb2_collision(float bee1[][4], float comb2[][3], int i, int j){

	bool collisionX = (bee1[i][0] < comb2[j][0] + 64) && (bee1[i][0] + 64 > comb2[j][0]) && bee1[i][2] && comb2[j][2];
	bool collisionY = (bee1[i][1] < comb2[j][1] + 32) && (bee1[i][1] + 32 > comb2[j][1]) && bee1[i][2] && comb2[j][2];
		
	if (collisionX && collisionY) return true; else return false;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool  bee1_hive_collision(float bee1[][4], float  hive[][3], int i, int j){

	bool collisionX = (bee1[i][0] < hive[j][0] + 64) && (bee1[i][0] + 64 > hive[j][0]) && bee1[i][2] && hive[j][2];
	bool collisionY = (bee1[i][1] < hive[j][1] + 32) && (bee1[i][1] + 32 > hive[j][1]) && bee1[i][2] && hive[j][2];

	if (collisionX && collisionY) return true; else return false;
	}
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool bullet_bird_collision(float bullet[], float bird[]){

	bool collisionX = (bullet[0] < bird[0] + 64) && (bullet[0] + 48 > bird[0]) && bird[2] && bullet[2];
	bool collisionY = (bullet[1] < bird[1] + 64) && (bullet[1] + 48 > bird[1]) && bird[2] && bullet[2];
	
	if (collisionX && collisionY) return true; else return false;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawBird(RenderWindow& window, float bird[], float bullet[], Sprite &birdSprite, Clock &birdClock, Clock &birdStart, int &score, 
				float comb1[][3], int size1, float comb2[][3], int size2){ 
	
	static int hitCount = 0;
	static bool first_time = true;
	
	if (first_time){
		bird[0] = resolutionX/2-32;
		bird[1] = resolutionY/2+32;
		first_time = false;
		}
	
	int secs[] = {4,5,6,7}; 
	int random1 = rand()%4;
	
	static int startSec = secs[random1];
	
	if (birdStart.getElapsedTime().asSeconds()<startSec)
		bird[2] = 0;
	else 
		bird[2] = 1;
	
	if (!bird[2])
		return;	
	
	static int frame = 0;
	frame++;
	
	static int reached = 1;		
	//reached = 1 represents target needs to be found
	//reached = 2 represents target is found and the bird need to move
	//reached = 3 represents bird is at target and it will check for comb
	
	(frame%2!=0 && (frame%11==0||frame%13==0)) ? birdSprite.setTextureRect(IntRect(0,0,64,64)) : birdSprite.setTextureRect(IntRect(64,0,64,64));
	
	float time_elapsed = birdClock.getElapsedTime().asSeconds();	
	float speed = 100;
	
	static int randomX = 0;
	static int randomY = 0;
	
	if (time_elapsed > 2 && reached==1){
		
		float possibleY[] = {32*(gameRows-16), 32*(gameRows-15), 32*(gameRows-14), 32*(gameRows-13), 32*(gameRows-12), 
		 					 32*(gameRows-11), 32*(gameRows-10), 32*(gameRows-9), 32*(gameRows-8)};

		int random2 = rand()%9;

		bool collisionX = true;
		bool collisionY = true;
	
		while (collisionX && collisionY){
		
			randomX = 80 + rand()%(resolutionX-160-64);
			randomY = possibleY[random2];
				
			collisionX = randomX < bird[0]+64 && bird[0] < randomX+64;
			collisionY = randomY < bird[1]+64 && bird[1] < randomY+64;
			}
			
		reached = 2;	
		birdClock.restart();		
		}			
		
	if (bullet_bird_collision(bullet, bird)){
		hitCount++;
		bullet[2] = 0;
		}
	
	if (hitCount == 3){
		reached  = 2;
		hitCount = 0;
		
		(rand() % 2) ? randomX = -100 : randomX = 1000;
		birdClock.restart();
		}		
			
	if (reached==2 && birdClock.getElapsedTime().asSeconds()>1){
		if (bird[1] < randomY)
			bird[1] += 1;
			
		else if (bird[0] < randomX)
			bird[0] += 1;
			
		else if (bird[1] > randomY)
			bird[1] -= 1;
		
		else if (bird[0] > randomX)
			bird[0] -= 1;
			
		else {
			reached = 3;
			birdClock.restart();
			}	
		}		
	
	if (reached==3){	
		for (int i=0; i<size1+3; i++){
		
			bool bird_comb1_collisionX = bird[0] < comb1[i][0] + 64 && bird[0] + 64 > comb1[i][0] && comb1[i][2];
			bool bird_comb1_collisionY = bird[1] < comb1[i][1] + 64 && bird[1] + 64 > comb1[i][1] && comb1[i][2];		
			
			if (bird_comb1_collisionX && bird_comb1_collisionY){
				
				//Showing that bird is on the comb:
				bird[0] = comb1[i][0];	
				bird[1] = comb1[i][1];
				
				//Removing the comb:
				comb1[i][2] = 0;					
					
				birdClock.restart();
					
				if (bird[1] == 32*(gameRows-16) || bird[1] == 32*(gameRows-15))
					score += 1000;	
					
				else if (bird[1] == 32*(gameRows-14) || bird[1] == 32*(gameRows-13) || bird[1] == 32*(gameRows-12))
					score += 800;
					
				else
					score += 500;					
				}
			}
			
		for (int i=0; i<size2; i++){
		
			bool bird_comb2_collisionX = bird[0] < comb2[i][0] + 64 && bird[0] + 64 > comb2[i][0] && comb2[i][2];
			bool bird_comb2_collisionY = bird[1] < comb2[i][1] + 32 && bird[1] + 64 > comb2[i][1] && comb2[i][2];		
			
			if (bird_comb2_collisionX && bird_comb2_collisionY){
				
				//Showing that bird is on the comb:
				bird[0] = comb2[i][0];	
				bird[1] = comb2[i][1];
				
				if (birdClock.getElapsedTime().asSeconds()>1){
				
					//Removing the comb:
					comb2[i][2] = 0;					
					
					birdClock.restart();
					
					if (bird[1] == 32*(gameRows-16) || bird[1] == 32*(gameRows-15))
						score += 2000;	
					
					else if (bird[1] == 32*(gameRows-14) || bird[1] == 32*(gameRows-13) || bird[1] == 32*(gameRows-12))
						score += 1600;
					
					else
						score += 1000;					
					}
				}
			}
			
			reached = 1;	
			
		}
		
	birdSprite.setPosition(bird[0], bird[1]);
	window.draw(birdSprite);	
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawHive(RenderWindow& window, float hive[][3], Sprite &hiveSprite, int i){
	
	hiveSprite.setPosition(hive[i][0], hive[i][1]);
	window.draw(hiveSprite);
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawComb1(RenderWindow &window, float comb1[][3], Sprite &comb1Sprite, int i){
	
	comb1Sprite.setPosition(comb1[i][0], comb1[i][1]);
	window.draw(comb1Sprite);
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawComb2(RenderWindow &window, float comb2[][3], Sprite &comb2Sprite, int i){
	
	comb2Sprite.setPosition(comb2[i][0], comb2[i][1]);
	window.draw(comb2Sprite);
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawFlower(RenderWindow &window, float flower[][3], Sprite &flowerSprite, int i){

	flowerSprite.setPosition(flower[i][0], flower[i][1]);
	window.draw(flowerSprite);
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void beeonScreen(int &bees1, int &bees_on_screen, int &bees_to_generate, int &bee_number, float bee1[][4]){
	
	if (bees1>10){
		int temp = bees_on_screen, count = 0;
		if (bees_on_screen<6){ bees_on_screen++;	count++;	bee1[bee_number++][2] = 1;	}		
		if (temp < bees_on_screen){	bees_to_generate = bees_on_screen;	bees1 -= count;	}
		}
		
	else if (bees1>6){
		int temp = bees_on_screen, count = 0;
		if (bees_on_screen<5){ bees_on_screen++;	count++;	bee1[bee_number++][2] = 1;	}		
		if (temp < bees_on_screen){	bees_to_generate = bees_on_screen;	bees1 -= count;	}
		}
	
	else if (bees1>4){
		int temp = bees_on_screen, count = 0;
		if (bees_on_screen<4){ bees_on_screen++;	count++;	bee1[bee_number++][2] = 1;	}		
		if (temp < bees_on_screen){	bees_to_generate = bees_on_screen;	bees1 -= count;	}
		}
		
	else if (bees1>2){
		int temp = bees_on_screen, count = 0;
		if (bees_on_screen<3){ bees_on_screen++;	count++;	bee1[bee_number++][2] = 1;	}		
		if (temp < bees_on_screen){	bees_to_generate = bees_on_screen;	bees1 -= count;	}
		}
	
	else if (bees1>0){
		int temp = bees_on_screen, count = 0;
		if (bees_on_screen<2){ bees_on_screen++;	count++;	bee1[bee_number++][2] = 1;	}		
		if (temp < bees_on_screen){	bees_to_generate = bees_on_screen;	bees1 -= count;	}
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void bee1Spawn(int bound_l, int bound_r, int &spawnBee, bool beeInitialized[], float intervalTime[], float bee1[][4], float &sinceLastSpawn, 
				float &spawnInterval, Clock &spawnClock, Clock intervalClock[]){
	
	sinceLastSpawn += spawnClock.getElapsedTime().asMilliseconds();
	
	if (sinceLastSpawn >= spawnInterval && spawnBee<20 && bee1[spawnBee][2] && !beeInitialized[spawnBee]){
		
		if (spawnBee<6) { if (spawnBee%2==1) bee1[spawnBee][0] = bound_l+1; else bee1[spawnBee][0] = bound_r-1; }
		
				   else { if (rand() % 2==1) bee1[spawnBee][0] = bound_l+1; else bee1[spawnBee][0] = bound_r-1; }
				   
				   
        bee1[spawnBee][3] = (bee1[spawnBee][0] == bound_l+1) ? 1 : 0;
        beeInitialized[spawnBee] = true;
		
		spawnClock.restart();
		spawnBee++;
		sinceLastSpawn = 0;
		
		intervalTime[spawnBee] = intervalClock[spawnBee].getElapsedTime().asSeconds();		
		}	
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void randomComb(int i, float comb1[][3], int bound_l, int bound_r){
			
	bool exist = true;
			
	while (exist){
		
		comb1[i][0] = bound_l + rand() % (bound_r - bound_l);
		
		for (int j=20; j<23; j++){
			if (j==i) continue;
					
			if (comb1[i][0]+64>comb1[j][0] && comb1[i][0]<comb1[j][0]+64 && comb1[i][1]+32>comb1[j][1] && comb1[i][1]<comb1[j][1]+32){
				exist = true; break;
				}
			else 
				exist = false;
			}		
		}
			
	float possible_coordinates[9] = {32*(gameRows-16), 32*(gameRows-15), 32*(gameRows-14), 32*(gameRows-13), 32*(gameRows-12),
									 32*(gameRows-11), 32*(gameRows-10), 32*(gameRows- 9), 32*(gameRows-8)};
	
	int random = rand()%9;
	
	comb1[i][1] = possible_coordinates[random];
	comb1[i][2] = 1;	
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void flowerGeneration(int i, float bee1[][4], float flower[][3], bool pollinated[], bool &first_bee){
	           	
    for (int j=0; j<19; j++){
           		
    	bool present = true;
           		
    	if (!flower[j][2] && flower[j][1] == bee1[i][1]+32 && flower[j][0]+40 > bee1[i][0] && flower[j][0] < bee1[i][0]+40){
			present = false; 
           	}
           		
		if (first_bee && !present){
			(bee1[i][3] == 1) ? bee1[i][3] = 0 : bee1[i][3] = 1;
           			
           	pollinated[i] = true;
           		
           	flower[0][0] = 80;
           	flower[0][1] = bee1[i][1]+32;	
          	flower[0][2] = 1;
          			
          	flower[19][0] = resolutionX-80-40;		//border-40
           	flower[19][1] = bee1[i][1]+32;
          	flower[19][2] = 1;
           	
           	first_bee = false;
           	break;
           	}
           			
		else if (!first_bee && !present && !flower[j][2] && !pollinated[i]){
			(bee1[i][3] == 1) ? bee1[i][3] = 0 : bee1[i][3] = 1;
        		
        	pollinated[i] = true;
        
        	flower[j][0] = bee1[i][0]-40;
        	flower[j][1] = bee1[i][1]+32;
        	flower[j][2] = 1;
        			
        	break;
        	}
        }
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void hiveGeneration(int i, int &bees_on_screen, float bee1[][4], float hive[][3]){
		
	bee1[i][2] = 0;
	bees_on_screen--;
	
	hive[i][0] = bee1[i][0];
	hive[i][1] = bee1[i][1]-32;
	hive[i][2] = 1;	
	}*/
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void bee1Move(int bound_l, int bound_r, int &bees_on_screen, int &currentFrame, int &x_cord, int &spawnBee, int stoppingFrame[], bool bee_move[],
			  int &currentSpeed, float time_elapsed, float intervalTime[], float stopTime[], float bee1[][4], float comb1[][3], float hive[][3],
			  Clock stopClock[], Clock intervalClock[], Texture &bee1Texture, Sprite &bee1Sprite, RenderWindow &window){
				  
	for (int i = 0; i < 20; i++) {
        if (bee1[i][2] && intervalClock[spawnBee].getElapsedTime().asSeconds() - intervalTime[i] > 1) {			// Only process active bees
        	
            if (bee1[i][3])			//Loading texture based on the direction
                x_cord = 384;
            else 
				x_cord = 0;
	
			bee1Sprite.setTextureRect(IntRect(x_cord,0,64,64));
            bee1Sprite.setTexture(bee1Texture);
 
            bee1Sprite.setPosition(bee1[i][0], bee1[i][1]);
            window.draw(bee1Sprite);     	
            
            float random_factor = currentSpeed/400;
            
            if ((currentFrame - stoppingFrame[i] > (currentSpeed/random_factor+rand()%2000)) && rand()%1000==0 && bee1[i][1]!=(gameRows-7)*boxPixelsY){
                	bee_move[i] = false;
                	stopTime[i] = rand()%3+1;
                	stopClock[i].restart();
                	stoppingFrame[i] = currentFrame;                	
                	}
            
	     	if (bee_move[i]) {                
                	                
                if (!bee1[i][3]) {  // Moving left
                
                	if (bee1[i][1] == (gameRows-7)*boxPixelsY && bee1[i][0] < bound_l){
                		
                		bee1[i][2] = 0;
                		bees_on_screen--;
                		
                		}
                
                    else if (bee1[i][0]>bound_l) 
                        bee1[i][0] -= currentSpeed*time_elapsed;
                    	
                    else {
                        bee1[i][1] += 32;
                      	bee1[i][0]  = bound_l+1;	
                      	bee1[i][3]  =  1; // Change direction to right
                      		
                    	}
                	} 
                
                else {  // Moving right
                
                	if (bee1[i][1] == (gameRows-7)*boxPixelsY && bee1[i][0] > bound_r){
                		
                		bee1[i][2] = 0;
                		bees_on_screen--;
                		
                		}
                
                    else if (bee1[i][0]<bound_r)
                        bee1[i][0] += currentSpeed*time_elapsed;
                	    
					else {
                        bee1[i][1] += 32;	
                      	bee1[i][0]  = bound_r-1;
                      	bee1[i][3]  =   0; // Change direction to left	
                      		                        
                	    }
                	}                	
            	} 
            
            else {
                
                if (stopClock[i].getElapsedTime().asSeconds() >= stopTime[i])
                	bee_move[i] = true;
                	
            	}
    	    }
    	}
	}	
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void collisions(int &bees_on_screen, int &score, float bullet[], float bee1[][4], float comb1[][3], float hive[][3], int size1, 
				int size2, float bee2[][4]){

	for (int i=0; i<size1; i++){
        if (bullet_bee1_collision(bullet, bee1, i)) {
            bee1[i][2] = 0; 		//Removing the existence of the bee
            bullet[2] = false; 		//Removing the existence of bullet
            bees_on_screen--;		//Decrementing the number of bees on screen
            score+=100;    			//Increasing the scores by 100
            
            //Storing the same coordinates for formation of honey comb at that place:
            comb1[i][0] = bee1[i][0];	 
            comb1[i][1] = bee1[i][1];	
            comb1[i][2] = 1;
            }       		
		}
		
	for (int i=0; i<size2; i++){
        if (bullet_bee2_collision(bullet, bee2, i)) {
            bee2[i][2] = 0; 		//Removing the existence of the bee
            bullet[2] = false; 		//Removing the existence of bullet
            bees_on_screen--;		//Decrementing the number of bees on screen
            score+=1000;    		//Increasing the scores by 1000
            
            //Storing the same coordinates for formation of honey comb at that place:
            comb1[i][0] = bee2[i][0];	 
            comb1[i][1] = bee2[i][1];	
            comb1[i][2] = 1;
            }       		
		}		
    	
    for (int i=0; i<size1; i++){
		for (int j=0; j<size1+3; j++){
			if (bee1_comb1_collision(bee1, comb1, i, j)){	
				bee1[i][1] += 32;				
				(bee1[i][3] == 1) ? bee1[i][3] = 0 : bee1[i][3] = 1;
				}
			}
		}
		
	for (int i=0; i<size1; i++){
		for (int j=0; j<size1; j++){
			if (bee1_hive_collision(bee1, hive, i, j)){
				bee1[i][1] += 32;
				(bee1[i][3] == 1) ? bee1[i][3] = 0 : bee1[i][3] = 1;
				}
			}
		}
	
	for (int i=0; i<size1+3; i++){
		if (bullet_comb1_collision(bullet, comb1, i)){
			comb1[i][2] = 0;
			bullet[2] = false;
			}
		}
		
	for (int i=0; i<size1; i++){	
		if (bullet_hive_collision(bullet, hive, i)){
			hive[i][2] = 0;
			bullet[2] = false;
			}
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void level1(RenderWindow &window, int &score, int &sprayCan, int &x_cord, float player_speed, float player[], float bullet[], float bird[], 
			float flower[][3], Sprite &playerSprite, Sprite &bulletSprite, Sprite &birdSprite, Sprite &bee1Sprite, Sprite &comb1Sprite, 
			Sprite &hiveSprite, Sprite &flowerSprite, Texture &bee1Texture, RectangleShape &groundRectangle){
	
	int bullets = 56;	//At the start of each level, there will be two cans and the starting bullets will be 56 (that came out of third can)
	int bees1 = 20;		//Number of bees in level 1 are 20
	
	int size1 = bees1;
	int size2 = 0;
	
	//Initializing bees for level 1 and based on number of bees the other components have been declared:
	float   bee1[size1][4] = {};
	float   hive[size1][3] = {}; 
	float  comb1[size1+3][3] = {};
	
	int bees_on_screen = 0;
	
	//Declaring clocks for each sprite:
	Clock bulletClock;
	Clock playerClock;
	Clock bee1Clock;
	Clock birdClock;
	Clock hiveClock;
	Clock comb1Clock;
	Clock delayClock;

	Texture backgroundTexture;
	Sprite backgroundSprite;
	backgroundTexture.loadFromFile("Textures/bg.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	
	RectangleShape layer(Vector2f(960, 640));
	layer.setFillColor(Color(0,0,0,200));

	Font font;
	font.loadFromFile("Fonts/ARCADE_I.TTF");
	
	Text bulletText;
	bulletText.setFont(font);
	bulletText.setCharacterSize(20);
	bulletText.setPosition(resolutionX/2-130, resolutionY-105);
	bulletText.setFillColor(Color::Blue);

	Music gameMusic;
	gameMusic.openFromFile("Music/Forest.ogg");
	gameMusic.play();
	gameMusic.setVolume(50);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Variable Declaration:
	
	int currentFrame = 0;
	int bees_to_generate = 0;	
	int bee_number = 0;

	bool beeInitialized[size1] = {}; 
	 int stoppingFrame [size1] = {};
	
	int max_speed = 400;
	int min_speed = 200;
	int currentSpeed = 200;
  
    Clock 	  stopClock[size1] = {};
	Clock intervalClock[size1] = {};
	Clock beeClock;	
	
	float  	   stopTime[size1] = {};
	float  intervalTime[size1] = {};

	int x_coordinate = 0;

	bool bee_move[size1] = {};
	bool first_time   = true;

	float spawnInterval = currentSpeed*20;
	float sinceLastSpawn = 0;
	int spawnBee = 0;
		
	Clock spawnClock; 

	bool first_bee = true;
	bool pollinated[20] = {};	//Size is equal to max flowers
	
	Clock birdStart;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Level1 Loop:
	while (window.isOpen()) {

		Event gameplay;
		
		while (window.pollEvent(gameplay)) {
			if (gameplay.type == Event::Closed)
				exit(0);
			}

		window.clear();
		
		window.draw(backgroundSprite);
		window.draw(layer);		
		
		drawPlayer(window, player, flower, x_cord, player_speed, playerSprite, playerClock);
	    
	    gameLogic(window, score, bees_on_screen, currentFrame, bees_to_generate, bee_number, currentSpeed, x_coordinate, spawnBee, bees1, 
	    stoppingFrame, first_time, first_bee, bee_move, beeInitialized, pollinated, spawnInterval, sinceLastSpawn, player, bee1, bullet, comb1, 
	    hive, bird, flower, stopTime, intervalTime, bee1Sprite, comb1Sprite, birdSprite, hiveSprite, flowerSprite, bee1Clock, comb1Clock, birdClock, 
	    beeClock, spawnClock, birdStart, stopClock, intervalClock, bee1Texture, size1, size2);
		
		drawBullet(window, bullet, player, x_cord, sprayCan, bullets, bulletSprite, playerSprite, bulletClock, delayClock);
		
		window.draw(groundRectangle);

		currentScore(window, score);
		displayCans(window, sprayCan);
		
		bulletText.setString("Bullets: " + to_string(bullets));
		window.draw(bulletText);
		
		window.display(); 
		
		currentFrame++;
		
		bonus(score, sprayCan);
		
		if (!player[2]){
			Clock exitClock;
			while (exitClock.getElapsedTime().asSeconds()<3);			//This will act as timer to stop the screen for 3 seconds
				gameMusic.stop();
				leftHives(score, hive, size1);
				retryLevel(window, sprayCan, score);	
			}
		
		else if (bees_on_screen == 0 && bees1 == 0){
		
			static int frame = currentFrame;
			if (currentFrame - frame > 1){
				Clock exitClock;
				gameMusic.stop();
									
				while (exitClock.getElapsedTime().asSeconds()<3);		//This will act as timer to stop the screen for 3 seconds

				leftHives(score, hive, size1);
				levelComplete(window, score);
				}			
			}
			
		else if (bullets == 0 && sprayCan == 0 && !bullet[2]){
			
			Clock exitClock;
			while (exitClock.getElapsedTime().asSeconds()<3);			//This will act as timer to stop the screen for 3 seconds
				gameMusic.stop();
				leftHives(score, hive, size1);
				Score(window, score);
			}	
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gameLogic(RenderWindow &window, int &score, int &bees_on_screen, int &currentFrame, int &bees_to_generate, int &bee_number, int &currentSpeed, 
				int &x_cord, int &spawnBee, int &bees1, int stoppingFrame[], bool &first_time, bool &first_bee, bool bee_move[], bool beeInitialized[],
				bool pollinated[], float &spawnInterval, float &sinceLastSpawn, float player[], float bee1[][4], float bullet[], float comb1[][3], 
				float hive[][3], float bird[], float flower[][3], float stopTime[], float intervalTime[], Sprite &bee1Sprite, Sprite &comb1Sprite, 
				Sprite &birdSprite, Sprite &hiveSprite, Sprite &flowerSprite, Clock &bee1Clock, Clock &comb1Clock, Clock &birdClock, Clock &beeClock, 
				Clock &spawnClock, Clock &birdStart, Clock stopClock[], Clock intervalClock[], Texture &bee1Texture, int size1, int size2){
 
 	/*------------------------------------------------------------------------------------------------------------------------------------------*/
 	//Variable declaration:
 	
    int bound_l = 80;
    int bound_r = resolutionX - 80 - 64;

	/*------------------------------------------------------------------------------------------------------------------------------------------*/
	
	//This function will check how many bees are on the screen and then bring the bees on screen according to its findings: 
	beeonScreen(bees1, bees_on_screen, bees_to_generate, bee_number, bee1);

	//When the level starts, the block of code below will generate 3 yellow combs at random locations, assign the starting row to all the bees 
	//and set the initial states of all the bees as "can move":
	if (first_time){
		for (int i=0; i<size1; i++)
			bee_move[i] = true;
		
		for (int i=0; i<size1; i++)
			bee1[i][1] = 32*4;
		
		for (int i=size1; i<size1+3; i++)
			randomComb(i, comb1, bound_l, bound_r);		//Function for making 3 random yellow combs
			
		first_time = false;		//Setting first_time untrue so that only in the first frame all the above setting is done
		} 	
	
	//This function will spawn the bees on screen:
	bee1Spawn(bound_l, bound_r, spawnBee, beeInitialized, intervalTime, bee1, sinceLastSpawn, spawnInterval, spawnClock, intervalClock);
	
	//The code below will make sure that flowers are only in last 2 rows and they do not overlap on eachother:
	for (int i=0; i<size1; i++){
		flower[i][0] = 80+40*i;
		flower[i][1] = (gameRows-6)*boxPixelsY;
		}
	
	//The function below will generate flowers on the screen only when the rows in which bees are is last row above flower row:
	for (int i=0; i<size1; i++){
		if (bee1[i][2] && bee1[i][1] == (gameRows-7)*boxPixelsY){
           	flowerGeneration(i, bee1, flower, pollinated, first_bee); 
            }		
		}	

	//time_elapsed is storing the time since last frame to control the speed of movement of bees:
	float time_elapsed = beeClock.getElapsedTime().asSeconds();
	beeClock.restart();

	//This function will control all the movement of regular bees:
	bee1Move(bound_l, bound_r, bees_on_screen, currentFrame, x_cord, spawnBee, stoppingFrame, bee_move, currentSpeed, time_elapsed, intervalTime, 
			 stopTime, bee1, comb1, hive, stopClock, intervalClock, bee1Texture, bee1Sprite, window);	
	
	//This function will check for all the collision that can happen in level1: 	 
    collisions(bees_on_screen, score, bullet, bee1, comb1, hive, size1, size2);
	
	//This function will bring the humming bird:
	drawBird(window, bird, bullet, birdSprite, birdClock, birdStart, score, comb1, size1);
	
	//Calling the function to draw yellow combs if they exist:
	for (int i=0; i<size1+3; i++){
		if (comb1[i][2])
            drawComb1(window, comb1, comb1Sprite, i);
		}
	
	//Calling the function to draw flowers if they exist:
	for (int i=0; i<size1; i++){
		if (flower[i][2])
			drawFlower(window, flower, flowerSprite, i);	
        }	
	
	//Calling the function to draw hives if they exist:
	for (int i=0; i<size1; i++){
		if (hive[i][2])
			drawHive(window, hive, hiveSprite, i);
		}
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void leftHives(int &scores, float hive[][3], int size){

	for (int i=0; i<size; i++){
	
		if (hive[i][2]){
			
			if (hive[i][1] = (gameRows-16)*boxPixelsY || (gameRows-15)*boxPixelsY)
				scores += 2000;
			
			else if (hive[i][1] = (gameRows-14)*boxPixelsY || (gameRows-13)*boxPixelsY || (gameRows-12)*boxPixelsY)
				scores += 1600;
			
			else
				scores += 1000;	
			}
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void retryLevel(RenderWindow &window, int &sprayCans, int scores){

	if (sprayCans>0)
		sprayCans--;
	
	else 
		Score(window, scores);
	
	Font font1;
	font1.loadFromFile("Fonts/ARCADE_I.TTF");
	
	Font font2;
	font2.loadFromFile("Fonts/arial.ttf");

	Texture backgroundTexture;
	Sprite backgroundSprite;
	backgroundTexture.loadFromFile("Textures/bg.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	
	Text nameOfGame;
	nameOfGame.setFont(font1);
	nameOfGame.setString("BUZZ BOMBERS");
	nameOfGame.setCharacterSize(50);
	nameOfGame.setPosition(resolutionX/2-290, 50);
	nameOfGame.setFillColor(Color::Yellow);
	
	Text heading;
	heading.setFont(font1);
	heading.setString("Level Failed");
	heading.setCharacterSize(30);
	heading.setPosition(resolutionX/2-175, 150);
	heading.setFillColor(Color(173, 216, 230));
	
	Text text;
	text.setFont(font2);
	text.setString("Do you want to retry level or end game?");
	text.setCharacterSize(20);
	text.setPosition(resolutionX/2-190, 230);
	text.setFillColor(Color::Green);
	
	Text copyright;
	copyright.setFont(font2);
	copyright.setString("Muhammad Mughees Tariq Khawaja (24I-0806)");
	copyright.setCharacterSize(15);
	copyright.setPosition(resolutionX/2-155, resolutionY-30);
	copyright.setFillColor(Color::White);
	
	RectangleShape layer(Vector2f(960, 640));
	layer.setFillColor(Color(0,0,0,150));
	
	Music menuMusic;
	menuMusic.openFromFile("Music/Title.ogg");
	menuMusic.play();
	menuMusic.setVolume(50);
	
	const int menuOptions = 2;
	
	string options[menuOptions] = {"Retry", "End game"};
	
	Text menu[menuOptions];
	RectangleShape box[menuOptions];

	for (int i=0; i<menuOptions; i++){
		menu[i].setFont(font2);
		menu[i].setString(options[i]);
		menu[i].setCharacterSize(30);
		menu[i].setFillColor(Color::White);
		
		box[i].setSize(Vector2f(260, 50));
		box[i].setFillColor(Color::Transparent);
		box[i].setOutlineColor(Color::White);
		box[i].setOutlineThickness(2);
		box[i].setPosition(resolutionX/2-130, 310+70*i);
		}	
		
	menu[0].setPosition(resolutionX/2-55, 315+70*0);
	menu[1].setPosition(resolutionX/2-70, 315+70*1);
	
			
	int optionSelected = 0;
	menu[optionSelected].setFillColor(Color::Green);
	
	while (window.isOpen()){
		Event event;
		
		while (window.pollEvent(event)){
			
			if (event.type == Event::Closed)
				exit(0);
			
			else if (event.type == Event::KeyPressed){
			
				if(event.key.code == Keyboard::Up){
				
					menu[optionSelected].setFillColor(Color::White);
					optionSelected = (optionSelected-1+menuOptions)%menuOptions;
					menu[optionSelected].setFillColor(Color::Green);
					}
			
				else if(event.key.code == Keyboard::Down){
				
					menu[optionSelected].setFillColor(Color::White);
					optionSelected = (optionSelected+1)%menuOptions;
					menu[optionSelected].setFillColor(Color::Green);
					}
			
				else if (event.key.code == Keyboard::Enter){
			
					if (options[optionSelected] == "Retry"){
						menuMusic.stop();	startGame(window);
						}
				
					else if (options[optionSelected] == "End game"){
						menuMusic.stop();	Score(window, scores);
						}
					}
				}
			}
	
		window.clear();			
		window.draw(backgroundSprite);
		window.draw(layer);
		window.draw(nameOfGame);
		window.draw(heading);
		window.draw(text);
		window.draw(copyright);
		
		for (int i=0; i<menuOptions; i++){
			
			window.draw( box[i]);
			window.draw(menu[i]);
			
			}

		window.display();
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void levelComplete(RenderWindow &window, int score){
	
	Font font1;
	font1.loadFromFile("Fonts/ARCADE_I.TTF");
	
	Font font2;
	font2.loadFromFile("Fonts/arial.ttf");

	Texture backgroundTexture;
	Sprite backgroundSprite;
	backgroundTexture.loadFromFile("Textures/bg.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	
	Text nameOfGame;
	nameOfGame.setFont(font1);
	nameOfGame.setString("BUZZ BOMBERS");
	nameOfGame.setCharacterSize(50);
	nameOfGame.setPosition(resolutionX/2-290, 50);
	nameOfGame.setFillColor(Color::Yellow);
	
	Text heading;
	heading.setFont(font1);
	heading.setString("Level Completed");
	heading.setCharacterSize(30);
	heading.setPosition(resolutionX/2-220, 150);
	heading.setFillColor(Color(173, 216, 230));
	
	Text text;
	text.setFont(font2);
	text.setString("Do you want to continue to next level or end game?");
	text.setCharacterSize(20);
	text.setPosition(resolutionX/2-230, 230);
	text.setFillColor(Color::Green);
	
	Text copyright;
	copyright.setFont(font2);
	copyright.setString("Muhammad Mughees Tariq Khawaja (24I-0806)");
	copyright.setCharacterSize(15);
	copyright.setPosition(resolutionX/2-155, resolutionY-30);
	copyright.setFillColor(Color::White);
	
	RectangleShape layer(Vector2f(960, 640));
	layer.setFillColor(Color(0,0,0,150));
	
	const int menuOptions = 2;
	
	string options[menuOptions] = {"Continue", "End game"};
	
	Text menu[menuOptions];
	RectangleShape box[menuOptions];

	for (int i=0; i<menuOptions; i++){
		menu[i].setFont(font2);
		menu[i].setString(options[i]);
		menu[i].setCharacterSize(30);
		menu[i].setFillColor(Color::White);
		
		box[i].setSize(Vector2f(260, 50));
		box[i].setFillColor(Color::Transparent);
		box[i].setOutlineColor(Color::White);
		box[i].setOutlineThickness(2);
		box[i].setPosition(resolutionX/2-130, 310+70*i);
		}	
		
	menu[0].setPosition(resolutionX/2-65, 315+70*0);
	menu[1].setPosition(resolutionX/2-70, 315+70*1);
	
	int optionSelected = 0;
	menu[optionSelected].setFillColor(Color::Green);
	
	Music menuMusic;
	menuMusic.openFromFile("Music/Title.ogg");
	menuMusic.play();
	menuMusic.setVolume(50);
	
	while (window.isOpen()){
		Event event;
		
		while (window.pollEvent(event)){
			
			if (event.type == Event::Closed)
				exit(0);
			
			else if (event.type == Event::KeyPressed){
			
				if(event.key.code == Keyboard::Up){
				
					menu[optionSelected].setFillColor(Color::White);
					optionSelected = (optionSelected-1+menuOptions)%menuOptions;
					menu[optionSelected].setFillColor(Color::Green);
					}
			
				else if(event.key.code == Keyboard::Down){
				
					menu[optionSelected].setFillColor(Color::White);
					optionSelected = (optionSelected+1)%menuOptions;
					menu[optionSelected].setFillColor(Color::Green);
					}
			
				else if (event.key.code == Keyboard::Enter){
			
					if (options[optionSelected] == "Continue");
						//calling of next level
				
					else if (options[optionSelected] == "End game"){
						menuMusic.stop();	Score(window, score);
						}
					}
				}
			}
	
		window.clear();			
		window.draw(backgroundSprite);
		window.draw(layer);
		window.draw(nameOfGame);
		window.draw(heading);
		window.draw(text);
		window.draw(copyright);
		
		for (int i=0; i<menuOptions; i++){
			
			window.draw( box[i]);
			window.draw(menu[i]);
			
			}

		window.display();
		}
	}
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Score(RenderWindow &window, int playerScore){
	
	 int nameIndex = 0;
	char playerName [17];
	
	for (int i=0; i<17; i++)
		playerName[i] = '\0';
	
	Font font1;
	font1.loadFromFile("Fonts/ARCADE_I.TTF");
	
	Font font2;
	font2.loadFromFile("Fonts/arial.ttf");

	Texture backgroundTexture;
	Sprite backgroundSprite;
	backgroundTexture.loadFromFile("Textures/bg.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	
	Text nameOfGame;
	nameOfGame.setFont(font1);
	nameOfGame.setString("BUZZ BOMBERS");
	nameOfGame.setCharacterSize(50);
	nameOfGame.setPosition(resolutionX/2-290, 50);
	nameOfGame.setFillColor(Color::Yellow);
	
	Text heading;
	heading.setFont(font1);
	heading.setString("Register Score");
	heading.setCharacterSize(30);
	heading.setPosition(resolutionX/2-200, 170);
	heading.setFillColor(Color(173, 216, 230));
	
	Text text;
	text.setFont(font2);
	text.setString("Enter Player Name:");
	text.setCharacterSize(20);
	text.setPosition(resolutionX/2-180, 280);
	text.setFillColor(Color::Green);
	
	Text name;
	name.setFont(font2);
	name.setCharacterSize(20);
	name.setFillColor(Color::White);
	name.setPosition(resolutionX/2+10, 280);
	
	RectangleShape box(Vector2f(400, 50));
	box.setOutlineThickness(2);
	box.setOutlineColor(Color::White);
	box.setFillColor(Color::Transparent);
	box.setPosition(resolutionX/2-200, 270);
	
	RectangleShape layer(Vector2f(960, 640));
	layer.setFillColor(Color(0,0,0,150));
	
	Text copyright;
	copyright.setFont(font2);
	copyright.setString("Muhammad Mughees Tariq Khawaja (24I-0806)");
	copyright.setCharacterSize(15);
	copyright.setPosition(resolutionX/2-155, resolutionY-30);
	copyright.setFillColor(Color::White);			
				
	Music menuMusic;
	menuMusic.openFromFile("Music/Title.ogg");
	menuMusic.play();
	menuMusic.setVolume(50);			
				
	bool playerTyping = true; 
	char charTyped;
	
	while (window.isOpen() && playerTyping){
		Event typing;
		
		while (window.pollEvent(typing)){
			
			if (typing.type == Event::Closed)
				exit(0);
			
			if (typing.type == Event::TextEntered){
			
				if (typing.text.unicode < 128 && typing.text.unicode!=32){
				
					if (typing.text.unicode == 8){
						
						if (playerName[0] != '\0')
							nameIndex--;
							playerName[nameIndex] = '\0';
							name.setString(playerName);
						}
						
					else if (typing.text.unicode == 13){
						
						if (playerName[0] != '\0')
							playerTyping = false;
						
						}	
						
					else if (nameIndex<16){
					
						playerName[nameIndex++] = typing.text.unicode;
						name.setString(playerName);
						
						}
					}
				}
			}
	
		window.clear();		
			
		window.draw(backgroundSprite);
		window.draw(layer);
		window.draw(nameOfGame);
		window.draw(heading);
		window.draw(text);
		window.draw(copyright);
		window.draw(name);
		window.draw(box);
		
		window.display();
		}

	Clock displayClock;

	while (displayClock.getElapsedTime().asSeconds()<3){
		
		Text score;
		score.setFont(font2);
		score.setString("Your score is " + to_string(playerScore));
		score.setCharacterSize(30);
		score.setPosition(resolutionX/2-120, 350);
		score.setFillColor(Color::White);
		
		window.clear();		
			
		window.draw(backgroundSprite);
		window.draw(layer);
		window.draw(nameOfGame);
		window.draw(heading);
		window.draw(text);
		window.draw(copyright);
		window.draw(name);
		window.draw(box);
		window.draw(score);
		
		window.display();
		
		}

	menuMusic.stop();
	compareScore(window, playerScore, playerName);

	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void compareScore(RenderWindow &window, int playerScore, char playerName[]){
	
	fstream scoreFile;
	
	int size = 11;
	
	string name[size] = {};
	int highscores[size] = {};
	
	scoreFile.open("highscores.txt", ios::in);
	
	for (int i=1; i<size; i++)		
		scoreFile >> name[i] >> highscores[i]; 		
	
	scoreFile.close();
	
	highscores[0] = playerScore;
	name[0] = playerName;
	
	for (int i=0; i<size-1; i++){
	
		bool swapStatus = false;

		for (int j=0; j<size-i-1; j++){
			
			if (highscores[j] < highscores[j+1]){
				
				int temp1 = highscores[j];
				highscores[j] = highscores[j+1];
				highscores[j+1] = temp1;
				
				string temp2 = name[j];
				name[j] = name[j+1];
				name[j+1] = temp2;
				
				swapStatus = true;
				}
			}
			
		if (!swapStatus) break;	
		}
	
	scoreFile.open("highscores.txt", ios::out);
	
	for (int i=0; i<size-1; i++){
		
		if (name[i] != "\0"){
			scoreFile << name[i];
			scoreFile << " ";
			scoreFile << highscores[i] << endl;
			}
		}
	
	scoreFile.close();
	
	highScore(window);

	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void bonus(int scores, int &sprayCans){
	
	if (scores == 20000)
		sprayCans++;
	else if (scores == 40000)
		sprayCans++;
	else if (scores == 80000)
		sprayCans++;
	else if (scores % 80000 == 0 && scores!=0)
		sprayCans++;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





















