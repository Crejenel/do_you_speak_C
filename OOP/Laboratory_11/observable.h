#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"
#include <vector>
#include <algorithm>

class Observable {

private:

    std::vector<Observer*> observers;

protected:

    void notifyObservers() {
        for (auto obs : observers) {
            obs->update();
        }
    }

public:

    
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    virtual ~Observable() = default;
};

#endif
