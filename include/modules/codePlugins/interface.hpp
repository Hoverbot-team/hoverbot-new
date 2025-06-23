// ModInterface.h
#ifndef MOD_INTERFACE_H
#define MOD_INTERFACE_H

#include <string>

class IMod {
public:
    virtual ~IMod() {}
    virtual void onLoad() = 0;
    virtual void onUpdate(float deltaTime) = 0;
    virtual std::string getName() const = 0;
    virtual std::string getVersion() const = 0;
};

extern "C" {
    typedef IMod* (*CreateModFunc)();
    IMod* createMod();
}

#endif
