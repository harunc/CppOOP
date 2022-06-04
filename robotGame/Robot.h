//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Harun Çifci
//---Student Number: 150180089
//--------------------------//
#include <iostream>
#ifndef _H
#define _H
using namespace std;
class Robot
{
private:
	friend class CommandCenter;
	friend class Explorer;
	friend class Miner;
	static int unqID;
	string RobotName;
	string RobotType;
	float speed;
	int durability;
	int manufactureCost;
	float maintenanceCost;
	bool canMove;

public:
	Robot(string RobotType, float speed, int durability, int manufactureCost, float maintenanceCost)
		: RobotType(RobotType), speed(speed), durability(durability), manufactureCost(manufactureCost), maintenanceCost(maintenanceCost)
	{
		this->canMove = false;
	}

	virtual ~Robot(){};
	// -----------------------GETTERS --------------------------
	bool getCanMove() const
	{
		return this->canMove;
	}
	string getType() const
	{
		return this->RobotType;
	}
	float getSpeed() const
	{
		return this->speed;
	}
	int getDurability() const
	{
		return this->durability;
	}
	int getManufactureCost() const
	{
		return this->manufactureCost;
	}
	float getMaintenanceCost() const
	{
		return this->maintenanceCost;
	}
	string getName() const
	{
		return this->RobotName;
	}
	static int getID()
	{
		return unqID;
	}
	//----------------------------------------------------------

	//------------------------SETTERS---------------------------
	void setRobotName(string name)
	{
		this->RobotName = name;
	}
	static void setID()
	{
		unqID++;
	}
	void setCanMove(bool t)
	{
		this->canMove = t;
	}
	void decreaseDurability()
	{
		this->durability -= 1;
	}
	//----------------------------------------------------------

	void showInfo()
	{
		cout << "Name: " << this->RobotName << endl;
		cout << "Type: " << this->RobotType << endl;
		cout << "Speed: " << this->speed << endl;
		cout << "Durability: " << this->durability << endl;
		cout << "ManufactureCost: " << this->manufactureCost << endl;
		cout << "MaintenanceCost: " << this->maintenanceCost << endl;
		cout << "Can Move: " << this->canMove << endl;
	}

	Robot &operator=(const Robot &t)
	{
		this->RobotName = t.RobotName;
		this->RobotType = t.RobotType;
		this->speed = t.speed;
		this->durability = t.durability;
		this->manufactureCost = t.manufactureCost;
		this->maintenanceCost = t.maintenanceCost;
		return *this;
	}
};

class Explorer : public Robot
{
private:
	static float totalExploredArea;
	static int totalNumberOfSeleniumArea;
	float exploredArea;
	bool detectedSelenium;
	friend class CommandCenter;
	friend class Miner;

public:
	Explorer(string robotType, float speed, int durability)
		: Robot{robotType, speed, durability, 3000, 450 / speed}
	{
		this->exploredArea = 0;
	}
	float getTotalExplored() const
	{
		return totalExploredArea;
	}
	float getExplored() const
	{
		return this->exploredArea;
	}

	bool move()
	{
		return this->canMove;
	}

	void explore()
	{
		int selenium = rand() % 101;
		totalExploredArea += 1500;
		this->exploredArea = 1500;
		if (selenium >= 40)
		{
			this->detectedSelenium = true;
			totalNumberOfSeleniumArea++;
		}
		else
		{
			this->detectedSelenium = false;
		}
	}
	void showInfo()
	{
		Robot::showInfo();
		cout << "explored area: " << this->exploredArea << endl;
	}
	Explorer &operator=(const Explorer &t) // Dön buraya
	{
		this->RobotName = t.RobotName;
		this->RobotType = t.RobotType;
		this->speed = t.speed;
		this->durability = t.durability;
		this->manufactureCost = t.manufactureCost;
		this->maintenanceCost = t.maintenanceCost;
		this->detectedSelenium = t.detectedSelenium;
		this->totalExploredArea = t.totalExploredArea;
		this->totalNumberOfSeleniumArea = t.totalNumberOfSeleniumArea;
		this->exploredArea = t.exploredArea;
		return *this;
	}
};

class Miner : public Robot
{
private:
	friend class CommandCenter;
	static int totalGatheredSelenium;
	int gatheredSelenium;

public:
	Miner(string RobotType, float speed, int durability)
		: Robot(RobotType, speed, durability, 5000, (750 / speed))
	{
	}
	void setGatheredSelenium(int a)
	{
		this->gatheredSelenium = a;
	}
	bool move()
	{
		if ((Explorer::totalNumberOfSeleniumArea > 0) && (this->getCanMove() == true))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void mine()
	{
		int extracted = 5 * (rand() % 91 + 10);
		setGatheredSelenium(extracted);
		totalGatheredSelenium += extracted;
		if (Explorer::totalNumberOfSeleniumArea > 0)
		{
			Explorer::totalNumberOfSeleniumArea--;
		}
	}

	void showInfo()
	{
		Robot::showInfo();
		cout << "# of gathered selenium: " << this->gatheredSelenium << endl;
	}

	Miner &operator=(const Miner &t) // dön
	{
		this->RobotName = t.RobotName;
		this->RobotType = t.RobotType;
		this->speed = t.speed;
		this->durability = t.durability;
		this->manufactureCost = t.manufactureCost;
		this->maintenanceCost = t.maintenanceCost;
		this->gatheredSelenium = t.gatheredSelenium;
		this->totalGatheredSelenium = t.totalGatheredSelenium;
		return *this;
	}
};

#endif