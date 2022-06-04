//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Harun Çifci
//---Student Number: 150180089
//--------------------------//
#include <iostream>
#include "Robot.h"
using namespace std;
class Crew
{
private:
	int maxExplorers;
	int maxMiners;
	int crewManufactureCost;
	float crewMaintenanceCost;
	static int explorerCrewSize;
	static int minerCrewSize;
	static Explorer **ExplorerCrew;
	static Miner **MinerCrew;

public:
	friend class CommandCenter;
	Crew(int crewMaxExplorer, int crewMaxMiner, int expCrewSize, int minCrewSize)
	{
		this->crewManufactureCost = 0;
		this->crewMaintenanceCost = 0;
		//-----------------Check Conventions of Inputs and Assign Begin---------------//
		if ((crewMaxExplorer < 1) || (crewMaxExplorer > 5))
		{
			this->maxExplorers = 2;
		}
		else
		{
			this->maxExplorers = crewMaxExplorer;
		}

		if ((crewMaxExplorer < 1) || (crewMaxExplorer > 5))
		{
			this->maxMiners = 2;
		}
		else
		{
			this->maxMiners = crewMaxMiner;
		}

		if ((expCrewSize > this->maxExplorers) || (expCrewSize < 0))
		{
			explorerCrewSize = this->maxExplorers;
		}
		else
		{
			explorerCrewSize = expCrewSize;
		};

		if ((minCrewSize > this->maxMiners) || (minCrewSize < 0))
		{
			minerCrewSize = this->maxMiners;
		}
		else
		{
			minerCrewSize = minCrewSize;
		};
		//-----------------Check Conventions of Inputs and Assign Finish---------------//

		//-----------------Create Crew Arrays and First Robots BEGIN---------------//
		ExplorerCrew = new Explorer *[this->maxExplorers];
		MinerCrew = new Miner *[this->maxMiners];

		for (int i = 0; i < this->explorerCrewSize; i++)
		{
			int durability = 1 + (rand() % 5);
			float speed = 1.5 + static_cast<float>(rand()) / RAND_MAX;
			Explorer *exp = new Explorer("explorer", speed, durability);
			exp->setCanMove(true);
			string name = "exp-" + to_string(Robot::getID());
			Robot::setID();
			exp->setRobotName(name);
			crewManufactureCost += exp->getManufactureCost();
			ExplorerCrew[i] = exp;
		}
		for (int i = 0; i < this->minerCrewSize; i++)
		{
			int durability = 1 + (rand() % 5);
			float speed = 1 + (static_cast<float>(rand()) / RAND_MAX) * 0.5;
			Miner *min = new Miner("miner", speed, durability);
			min->setCanMove(true);
			string name = "mnr-" + to_string(Robot::getID());
			Robot::setID();
			min->setRobotName(name);
			crewManufactureCost += min->getManufactureCost();
			MinerCrew[i] = min;
		}
	}
	//-----------------Create Crew Arrays and First Robots FINISH---------------//

	// -----------------------GETTERS BEGIN--------------------------//
	static Explorer **getExplorers()
	{
		return ExplorerCrew;
	}
	static Miner **getMiners()
	{
		return MinerCrew;
	}
	float getCrewMaintenanceCost() const
	{
		return this->crewMaintenanceCost;
	}
	int getCrewManufactureCost() const
	{
		return this->crewManufactureCost;
	}

	static int getMinerCrewSize()
	{
		return minerCrewSize;
	}
	static int getExplorerCrewSize()
	{
		return explorerCrewSize;
	}
	// -----------------------GETTERS END--------------------------//

	//------------------------SETTERS BEGIN---------------------------//
	void setCrewMaintenanceCost(float t)
	{
		this->crewMaintenanceCost = t;
	}
	void setCrewManufactureCost(int crewManufactureCost)
	{
		this->crewManufactureCost = crewManufactureCost;
	}
	//------------------------SETTERS END---------------------------//

	//------------------------Necessary Functions BEGIN-----------------------------//
	Robot *manufactureRobot()
	{
		string t;
		cout << "Type:" << endl;
		cin >> t;
		if (t == "explorer") // FIRST CREATE THE ROBOT THEN CHECK IF THERE IS ENOUGH PLACE
		{
			int durability = 1 + (rand() % 5);
			float speed = 1.5 + static_cast<float>(rand()) / RAND_MAX;
			Explorer *exp = new Explorer(t, speed, durability);
			exp->setCanMove(true);
			string name = "exp-" + to_string(Robot::getID());
			Robot::setID();
			exp->setRobotName(name);

			if (!(explorerCrewSize + 1 > maxExplorers))
			{
				crewManufactureCost += exp->getManufactureCost();
				return exp;
			}
			else
			{
				delete exp;
				cout << "This robot cannot be added, check maximum size of the crew" << endl;
			}
		}
		else if (t == "miner") // FIRST CREATE THE ROBOT THEN CHECK IF THERE IS ENOUGH PLACE
		{
			int durability = 1 + (rand() % 5);
			float speed = 1 + (static_cast<float>(rand()) / RAND_MAX) * 0.5;
			Miner *min = new Miner(t, speed, durability);
			min->setCanMove(true);
			string name = "mnr-" + to_string(Robot::getID());
			Robot::setID();
			min->setRobotName(name);
			if (!(minerCrewSize + 1 > maxMiners))
			{
				crewManufactureCost += min->getManufactureCost();
				return min;
			}
			else
			{
				delete min;
				cout << "This robot cannot be added, check maximum size of the crew" << endl;
			}
		}
		else
		{
			cout << "You have entered wrong type of Robot" << endl;
		}
		return NULL;
	}

	void disassambleRobot(const string robotName)
	{
		if (robotName[0] == 'e')
		{
			if (this->explorerCrewSize != 1)
			{
				for (int i = 0; i < explorerCrewSize; i++)
				{
					if (ExplorerCrew[i]->getName() == robotName)
					{
						delete ExplorerCrew[i];
						for (int k = i; k < maxMiners; k++)
						{
							ExplorerCrew[k] = ExplorerCrew[k + 1];
						}
						explorerCrewSize--;
					}
				}
			}
		}
		else if (robotName[0] == 'm')
		{
			if (this->minerCrewSize != 1)
			{
				for (int i = 0; i < minerCrewSize; i++)
				{
					if (MinerCrew[i]->getName() == robotName)
					{
						delete MinerCrew[i];
						for (int k = i; k < maxMiners; k++)
						{
							MinerCrew[k] = MinerCrew[k + 1];
						}
						minerCrewSize--;
					}
				}
			}
		}
	}

	void initMovement()
	{
		int i = 0;
		while (i < this->explorerCrewSize)
		{
			if (ExplorerCrew[i] != NULL)
			{
				ExplorerCrew[i]->setCanMove(true);
				i++;
			}
		}
		int j = 0;
		while (j < this->minerCrewSize)
		{
			if (MinerCrew[j] != NULL)
			{
				MinerCrew[j]->setCanMove(true);
				j++;
			}
		}
	}
	void updateDurability()
	{
		cout << "Explorer durability is being updated" << endl;
		for (int i = 0; i < explorerCrewSize; i++)
		{
			if (getExplorers()[i]->getDurability() != 0)
			{
				getExplorers()[i]->decreaseDurability();
				if (getExplorers()[i]->getDurability() == 0)
				{
					cout << getExplorers()[i]->getName() << "'s durability=0" << endl;
					cout << getExplorers()[i]->getName() << ": Goodbye" << endl;
					if (explorerCrewSize != 1)
					{
						disassambleRobot(getExplorers()[i]->getName());
					}
				}
			}
		}
		cout << "Miner durability is being updated" << endl;
		for (int i = 0; i < minerCrewSize; i++)
		{
			if (getMiners()[i]->getDurability() != 0)
			{
				getMiners()[i]->decreaseDurability();
				if (getMiners()[i]->getDurability() == 0)
				{
					cout << getMiners()[i]->getName() << "'s durability=0" << endl;
					cout << getMiners()[i]->getName() << ": Goodbye" << endl;
					if (minerCrewSize != 1)
					{
						disassambleRobot(getMiners()[i]->getName());
					}
				}
			}
		}
	}

	bool searchInCrew(string t)
	{
		for (int i = 0; i < explorerCrewSize; i++)
		{
			if (ExplorerCrew[i]->getName() == t)
			{
				return true;
			}
		}
		for (int i = 0; i < minerCrewSize; i++)
		{
			if (MinerCrew[i]->getName() == t)
			{
				return true;
			}
		}
		return false;
	}

	void showInfo()
	{
		cout << "explorerCrew Size:" << explorerCrewSize << endl;
		cout << "minerCrew Size:" << minerCrewSize << endl;

		for (int i = 0; i < explorerCrewSize + 1; i++)
		{
			if (i < explorerCrewSize)
			{
				(ExplorerCrew[i])->showInfo();
			}
		}
		for (int j = 0; j < minerCrewSize + 1; j++)
		{
			if (j < minerCrewSize)
			{
				(MinerCrew[j])->showInfo();
			}
		}

		cout << "Total manufacture cost: " << crewManufactureCost << endl;
		cout << "Total maintenance cost: " << crewMaintenanceCost << endl;
	}
	//------------------------Necessary Functions END-----------------------------//

	//------------------------Operator Overloading BEGIN-----------------------------//
	Crew &operator+=(const Robot *t)
	{
		if (t != NULL)
		{
			if (t->getType() == "explorer")
			{
				Explorer *newRobot = new Explorer(t->getType(), t->getSpeed(), t->getDurability());
				newRobot->setRobotName(t->getName());
				ExplorerCrew[getExplorerCrewSize()] = newRobot;
				explorerCrewSize++;
			}
			else if (t->getType() == "miner")
			{
				Miner *newRobot = new Miner(t->getType(), t->getSpeed(), t->getDurability());
				newRobot->setRobotName(t->getName());
				MinerCrew[getMinerCrewSize()] = newRobot;
				minerCrewSize++;
			}
		}
		delete t;
		return *this;
	}
	Crew &operator-=(string t)
	{
		if (searchInCrew(t))
		{
			cout << t << ": Goodbye" << endl;
		}
		disassambleRobot(t);
		return *this;
	}
	//------------------------Operator Overloading END-----------------------------//
};

class CommandCenter
{
private:
	int neededSelenium;
	float searchArea;
	int seleniumWorth;
	int turnCount;
	float totalCrewMaintenanceCost;
	float profit;

public:
	CommandCenter()
	{
		this->neededSelenium = 0;
		this->searchArea = 0;
		this->seleniumWorth = 30;
		this->turnCount = 1;
		this->totalCrewMaintenanceCost = 0;
		this->profit = 0;
	}
	CommandCenter(int neededSelenium, float searchArea, int seleniumWorth) // constructor with name and atk
	{
		this->neededSelenium = neededSelenium;
		this->searchArea = searchArea;
		this->seleniumWorth = seleniumWorth;
		this->turnCount = 1;
		this->totalCrewMaintenanceCost = 0;
		this->profit = 0;
	}

	void setProfit(float profit)
	{
		this->profit = profit;
	}
	float getProfit() const
	{
		return this->profit;
	}

	void calculateProfit(Crew Crew)
	{
		float sellSelenium = Miner::totalGatheredSelenium * seleniumWorth;
		float expenses = Crew.getCrewMaintenanceCost() + Crew.getCrewManufactureCost();
		setProfit(sellSelenium - expenses);
		cout << "Profit:" << this->profit << endl;
		cout << "Expenses:" << expenses << endl;
		cout << "Selenium Revenue:" << sellSelenium << endl;
	}

	CommandCenter operator++()
	{
		CommandCenter temp;
		temp = *this;
		turnCount++;
		return temp;
	}

	bool isGameEnded()
	{
		if (Explorer::totalExploredArea >= searchArea)
		{
			cout << "Area has been fully explored." << endl;
			cout << "Aim: " << neededSelenium << " selenium." << endl;
			cout << "Collected: " << Miner::totalGatheredSelenium << endl;
			if (Miner::totalGatheredSelenium >= neededSelenium)
			{
				cout << "Congrats!" << endl;
			}
			else
			{
				cout << "Mission Failed!" << endl;
			}
			for (int i = 0; i < Crew::explorerCrewSize; i++)
			{
				delete Crew::ExplorerCrew[i];
			}
			for (int m = 0; m < Crew::minerCrewSize; m++)
			{
				delete Crew::MinerCrew[m];
			}

			delete[] Crew::ExplorerCrew;
			delete[] Crew::MinerCrew;
			return true;
		}
		else
		{
			return false;
		}
	};

	void showInfo()
	{
		int exploredAreas = Explorer::totalExploredArea;
		int totalNumberOfSeleniumAreas = Explorer::totalNumberOfSeleniumArea;
		int collectedSelenium = Miner::totalGatheredSelenium;
		cout << "Current turn: " << turnCount << endl;
		cout << "Aim: " << neededSelenium << " selenium." << endl;
		cout << "Collected: " << collectedSelenium << endl;
		cout << "Total Search Area: " << searchArea << endl;
		cout << "Explored Area: " << exploredAreas << endl;
		cout << "Currently, there are " << totalNumberOfSeleniumAreas
			 << " area/s that include selenium." << endl;
		if (totalNumberOfSeleniumAreas > 0)
		{
			cout << "Mine these areas if miners have not finished their turn! If you cannot cope with mining, you can always add new miners!" << endl;
		}
	}
};
