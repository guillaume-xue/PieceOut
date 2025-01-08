#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <vector>
#include "Observer.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

class Subject
{
private:
    vector<Observer *> observers;
    int updateCount = 0;

public:
    virtual ~Subject() {}
    void addObserver(Observer *observer)
    {
        observers.push_back(observer);
    }
    void removeObserver(Observer *observer)
    {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notifyObservers()
    {
        updateCount = observers.size();
        for (Observer *observer : observers)
        {
            observer->update();
        }
        while (updateCount > 0)
        {
            // Attendre que tous les observateurs aient terminé
        }
    }
    void observerFinished()
    {
        updateCount--;
    }
};

#endif