#include "simulate.h"

simulate::simulate()
{
	int numCustomers = 0;
	int clock = 0;
}
//Destrcutor
simulate::~simulate()
{
	int numCustomers = 0;
	int clock = 0;
	while (!tellerQueue.empty())
	{
		tellerQueue.pop();
	}
	while (!bankerQueue.empty())
	{
		bankerQueue.pop();
	}
}

void simulate::arrivalEvent(int time)
{
	Event temp;
	temp.arrival = 1;
	temp.currentTime = time;
	events.push_back(temp);
}

void simulate::departureEvent(int time)
{
	Event temp;
	temp.departure = 1;
	temp.currentTime = time;
	events.push_back(temp);
}

//add people to their respective queue
void simulate::addPerson(int arrival, int wait)
{
	numCustomers++;

	Person temp = Person();
	temp.arrivalTime = arrival;
	temp.waitTime = wait;

	if (wait > 10)
	{
		bankerQueue.push(temp);
	}
	else
	{
		tellerQueue.push(temp);
	}
	arrivalEvent(arrival);
}

void simulate::action()
{
	int wait = 100;
	int currentWait = 0;
	int currentTotal = 0;
	events.pop_back();
	while (!(tellerQueue.empty()))
	{
		clock++;
		if (tellerQueue.front().arrivalTime <= clock)
		{
			if (tellerAvailable)
			{
				if (tellerQueue.size() == 1)
				{
					tellerQueue.pop();
					break;
				}
				Person currentTellerCustomer = tellerQueue.front();
				tellerAvailable = false;
				wait = currentTellerCustomer.waitTime;
				currentWait = clock - currentTellerCustomer.arrivalTime;
				if (currentWait > maxWait)
				{
					maxWait = currentWait;
				}
				totalWait = totalWait + currentWait;
				currentTotal = currentWait + wait;
				if (currentTotal > maxTime)
				{
					maxTime = currentTotal;
				}
				totalTime = currentTotal + totalTime;
			}
			if (wait == 0)
			{
				departureEvent(clock);
				tellerQueue.pop();
				tellerAvailable = true;
				clock--;
			}
			if (maxInLine < tellerQueue.size())
			{
				maxInLine = tellerQueue.size()-1;
			}

		}
		wait--;
	}
	while (!(bankerQueue.empty()))
	{
		clock++;
		if (bankerQueue.front().arrivalTime <= clock)
		{
			if (bankerAvailable)
			{
				if (bankerQueue.size() == 1)
				{
					bankerQueue.pop();
					break;
				}
				Person currentBankerCustomer = bankerQueue.front();
				bankerAvailable = false;
				wait = currentBankerCustomer.waitTime;
				currentWait = clock - currentBankerCustomer.arrivalTime;
				if (currentWait > maxWait)
				{
					maxWait = currentWait;
				}
				totalWait = totalWait + currentWait;
				currentTotal = currentWait + wait;
				if (currentTotal > maxTime)
				{
					maxTime = currentTotal;
				}
				totalTime = currentTotal + totalTime;
				bankerQueue.pop();
			}
			if (wait == 0)
			{
				departureEvent(clock);
				bankerAvailable = true;
				clock--;
			}
			if (maxInLine < bankerQueue.size())
			{
				maxInLine = bankerQueue.size() - 1;
			}

		}
		wait--;
	}
}

void simulate::printEvents()
{
	int currentSize = events.size();
	for (int i = 0; i < currentSize; i++)
	{
		if (events.front().arrival == 1)
		{
			cout << "t = " << events.front().currentTime << ": Arrival event" << endl;
		}
		else
		{
			cout << "t = " << events.front().currentTime << ": Departure event" << endl;
		}
		events.pop_front();
	}
}

void simulate::endResults()
{
	cout << setprecision(1) << fixed;
	averageTime = totalTime / (numCustomers - 1);
	averageWait = totalWait / (numCustomers - 1);
	cout << "Total number of customers = " << numCustomers-1 << endl;
	cout << "Average amount of time in the bank = " << averageTime << " minutes" << endl;
	cout << "Maximum amount of time in the bank = " << maxTime << " minutes" << endl;
	cout << "Average amount of time waiting = " << averageWait << " minutes" << endl;
	cout << "Maximum amount of time waiting = " << maxWait << " minutes" << endl;
	cout << "Maximum length of line = " << maxInLine << " customers" << endl;
}