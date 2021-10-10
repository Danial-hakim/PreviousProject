#include<iostream>
#include<time.h>

int main();

std::string selectWarhead(); // a selection of warhead
int getLaunchCode(); // let player input launch code
bool targetLocation(int t_x,int t_y); // let user put the location of their target
bool armMissile(bool t_isArm); //switch to check if the missile is arm
void collisionDectection(int t_radius , int t_x, int t_y, bool t_targetInput);//to see if there is any collision
bool launchMissile(int t_currentLaunchCode); // to launch the missile
int checkRadius(std::string t_currentWarhead); // check the raidus of the missile as different missile have different radius
int enemyLocationRangeY(); 
int enemyLocationRangeX();

int main()
{
	srand(time(NULL));


	int menuNum = 0; // number of options and the menu will go following the number user input
	std::string currentWarhead = "";
	bool isMissileArm = false;
	int warheadRadius = 0;
	int currentLaunchCode = 0;
	bool allowLaunch = false;
	bool exitGame = false; // if player want to exit game , this is true
	bool targetFound = false;
	int enemyX = 0;
	int enemyY = 0;

	while (exitGame == false)
	{
		std::cout << "Press 1 to select Warhead" << std::endl;
		std::cout << "Press 2 to put target coordinates" << std::endl;
		std::cout << "Press 3 to get the launch code" << std::endl;
		std::cout << "Press 4 to arm missile" << std::endl;
		std::cout << "Press 5 to launch missile" << std::endl;
		std::cout << "Press 6 to know enemy whereabouts" << std::endl;
		std::cout << "Press 7 to exit" << std::endl;
		std::cout << "--------------------------------------------" << std::endl;
		std::cin >> menuNum;
		std::cout << "--------------------------------------------" << std::endl;

		if (menuNum == 1)
		{
			currentWarhead = selectWarhead();
			warheadRadius = checkRadius(currentWarhead);
		}
		else if (menuNum == 2)
		{
			targetFound = targetLocation(enemyX, enemyY);
		}
		else if (menuNum == 3)
		{
			currentLaunchCode = getLaunchCode();
		}
		else if (menuNum == 4)
		{
			armMissile(isMissileArm);
		}
		else if (menuNum == 5)
		{
			allowLaunch = launchMissile(currentLaunchCode);
			if (allowLaunch == true)
			{
				collisionDectection(warheadRadius, enemyX, enemyY,targetFound);
			}
		}
		else if (menuNum == 6)
		{
			enemyX = enemyLocationRangeX();
			enemyY = enemyLocationRangeY();
		}
		else if (menuNum == 7)
		{
			std::cout << "You have chosen to leave the game " << std::endl;
			exitGame = true;
		}

	}




	system("pause");
	return 1;
}



std::string selectWarhead()
{
	std::string selectedWarhead = "";
	int warHeadNum = 0;
	
	std::cout << "1 == Nuclear Warhead" << std::endl;
	std::cout << "2 == Explosive Warhead" << std::endl;
	std::cout << "3 == Kaboom Warhead" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

	std::cout << "Select warhead corresponding to their number" << std::endl;
	std::cout << "Each warhead have different radius" << std::endl;
	std::cin >> warHeadNum;
	std::cout << "--------------------------------------------" << std::endl;

	if (warHeadNum == 1)
	{
		selectedWarhead = "Nuclear Warhead";
		std::cout << "Nuclear Warhead has been selected" << std::endl;
		std::cout << "--------------------------------------------" << std::endl;
	}
	else if (warHeadNum == 2)
	{
		selectedWarhead = "Explosive Warhead";
		std::cout << "Explosive Warhead has been selected" << std::endl;
		std::cout << "--------------------------------------------" << std::endl;
	}
	else if (warHeadNum ==  3)
	{ 
		selectedWarhead = "Kaboom Warhead";
		std::cout << "Kaboom Warhead has been selected" << std::endl;
		std::cout << "--------------------------------------------" << std::endl;
	}
	else
	{
		selectedWarhead = "No Warhead has been selected ";
	}
	return selectedWarhead; // return value to check the radius
}

int checkRadius(std::string t_currentWarhead) // check radius based on warhead
{
	int radius = 0;  // the bigger the radius , the more space the warhead affect thus higher chance of getting a hit

	if (t_currentWarhead == "Nuclear Warhead")
	{
		radius = 35;
	}
	else if (t_currentWarhead == "Explosive Warhead")
	{
		radius = 20;
	}
	else if (t_currentWarhead == "Kaboom Warhead")
	{
		radius = 50;
	}
	return radius;
}

bool targetLocation(int t_x, int t_y) // to see if user put in a target that is close to enemy location
{
	int xPos = 0;
	int yPos = 0;
	bool targetFound = false;

	std::cout << "Put the x coordinates of the target " << std::endl;
	std::cin >> xPos;
	std::cout << "Put the y coordinates of the target " << std::endl;
	std::cin >> yPos;

	if (xPos == t_x)
	{
		if (yPos == t_y)
		{
			targetFound = true; //if yes , increase chance to hit 
		}
	}
	return targetFound;
}
int getLaunchCode() // get the launch code , will need it to launch missile
{
	int launchCode = (rand() % 5000) + 1000; // random every time

	std::cout << "Launch code is " << launchCode << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

	return launchCode;
}
bool armMissile(bool t_isArm) // switch to see if missile is arm
{
	if (t_isArm == false)
	{
		t_isArm = true;
		std::cout << "Missile is armed " << std::endl;
		std::cout << "--------------------------------------------" << std::endl;
	}
	else
	{
		t_isArm == false;
		std::cout << "Missile is disarmed " << std::endl;
		std::cout << "--------------------------------------------" << std::endl;
	}
	return t_isArm;
}

void collisionDectection(int t_radius , int t_x , int t_y , bool t_targetInput)
{
	int currentX = (rand() % 50) + 6;
	int currentY = (rand() % 50) + 6;

	int targetX = t_x;
	int targetY = t_y;


	while (currentX <= 800)
	{
		currentX++;
		currentY = currentY + 2;
		if (t_targetInput == true) // if user put in the correct location , target will always be hit
		{
			std::cout << "Target Hit " << std::endl;
			break;
		}
		else if (currentX <= targetX + t_radius && currentX >= targetX - t_radius) // + radius as different warhead have different radius 
		{
			if (currentY <= targetY + t_radius && currentY >= targetY - t_radius) // if user did not put any target , they can still launch and get a hit
			{
				std::cout << "Target Hit by luck" << std::endl;
				break;
			}
		}
		else
		{
			std::cout << "Target Miss" << std::endl; // if the missile did not reach or went past target
			break;
		}
	}
}

bool launchMissile(int t_currentLaunchCode)
{
	int checkLaunchCode = 0;
	bool permission = false;

	std::cout << "Enter launch code " << std::endl;
	std::cin >> checkLaunchCode;

	if (checkLaunchCode == t_currentLaunchCode) // to check if user put in the right launch code 
	{
		std::cout << "Permission granted" << std::endl;
		permission = true;
	}
	else // if no launch code was given or the code was wrong , missile would not be launch
	{
		std::cout << "Error" << std::endl;
		std::cout << "Missile could not be launch" << std::endl;
	}
	std::cout << "--------------------------------------------" << std::endl;
	return permission;
}

int enemyLocationRangeX() // give hint about enemy where about
{
	int targetX = (rand() % 600) + 20;

	std::cout << "enemy x position is near " << targetX << std::endl;

	return targetX;
}

int enemyLocationRangeY()
{
	int targetY = ((rand() % 400) + 25)*2;

	std::cout << "enemy y position is near " << targetY << std::endl;

	return targetY;
}