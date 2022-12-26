#ifndef __IOBSERVEE_H
#define __IOBSERVEE_H

#include "IObserver.h"

class IObservable{
public:
    virtual void AddListener(IObserver* listener) = 0;
    virtual void RemoveListener(IObserver* listener) = 0;
};

#endif
