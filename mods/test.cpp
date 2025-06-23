// MyMod.cpp
#include "modules/codePlugins/interface.hpp"
#include <iostream>

class MyMod : public IMod {
public:
    void onLoad() override {
        std::cout << "MyMod loaded\n";
    }

    void onUpdate(float dt) override {
        std::cout << "MyMod updating (" << dt << "s)\n";
    }

    std::string getName() const override {
        return "MyMod";
    }

    std::string getVersion() const override {
        return "1.0";
    }
};

extern "C" IMod* createMod() {
    return new MyMod();
}
