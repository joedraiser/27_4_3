#include <iostream>
#include <random>
#include <vector>

enum taskType {NONE, A, B, C};

class Mob
{
private:
    taskType task;
public:
    Mob() { task=NONE; }

    bool addTask(taskType task)
    {
        if(this->task==NONE)
        {
            this->task = task;
            return true;
        }
        else
            return false;
    }

    taskType getTask() { return task; }
};

class Capo
{
private:
    int seed=0;
    std::vector<Mob> mobs;
public:
    Capo(int seed) { this->seed=seed; }

    void addWorkers(int workersQty)
    {
        for(int i=0;i<workersQty;i++)
            mobs.push_back(Mob ());
    }
    
    void addTask(int seed)
    {
        this->seed+=seed;
        std::srand(this->seed);
        int taskQty=1+std::rand()%mobs.size();
        taskType task;

        for(int i=0;i<mobs.size() && taskQty>0;i++)
        {
            task=(taskType)(std::rand()%3+1);
            if(mobs[i].addTask(task))
            {
                taskQty--;
            }
            else
                continue;
        }
    }

    bool isFull()
    {
        for(int i=0;i<mobs.size();i++)
        {
            if(mobs[i].getTask()==NONE)
                return false;
        }
        return true;
    }

    void displayBacklog()
    {
        for(int i=0;i<mobs.size();i++)
        {
            std::cout << "  Worker #" << i+1 << ": ";
            switch(mobs[i].getTask())
            {
                case NONE:
                    std::cout << "none\n";
                    break;
                case A:
                    std::cout << "A\n";
                    break;
                case B:
                    std::cout << "B\n";
                    break;
                case C:
                    std::cout << "C\n";
                    break;
            }
        }
    }
};

class Boss
{
private:
    std::vector<Capo> capos;
public:
    Boss(int caposQty)
    {
        for(int i=0;i<caposQty;i++)
        {
            capos.push_back(Capo (i));
        }
    }

    Capo* getTeam(int i)
    {
        if(i>=0&&i<capos.size())
            return &capos[i];
        else
            return nullptr;

    }

    void addTask(int seed)
    {
        for(int i=0;i<capos.size();i++)
        {
            if(!capos[i].isFull())
                capos[i].addTask(seed);
        }
    }

    bool isFull()
    {
        for(int i=0;i<capos.size();i++)
        {
            if (!capos[i].isFull())
                return false;
        }
        return true;
    }

    void displayBacklog()
    {
        for(int i=0;i<capos.size();i++)
        {
            std::cout << "Team #" << i+1 << ":\n";
            capos[i].displayBacklog();
        }
    }
};



int main()
{
    int teamsQty, workersQty, seed;
    std::cout << "Input teams quantity: ";
    std::cin >> teamsQty;

    Boss boss(teamsQty);

    for(int i=0;i<teamsQty;i++)
    {
        std::cout << "Enter workers quantity for the #" << i+1 << " team: ";
        std::cin >> workersQty;
        boss.getTeam(i)->addWorkers(workersQty);
    }

    boss.displayBacklog();

    do
    {
        std::cout << "Input seed: ";
        std::cin >> seed;
        boss.addTask(seed);
        boss.displayBacklog();
    }
    while(!boss.isFull());

    return 0;
}
