#ifndef OBSERVER_HPP
#define OBSERVER_HPP

class Observer
{
public:
    virtual ~Observer() {}
    virtual void update() = 0;
};

#endif