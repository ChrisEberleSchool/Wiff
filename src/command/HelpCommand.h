#pragma once

#include <iostream>
#include <string>

#include "./base/Command.h"

class HelpCommand : public Command {
public:
    HelpCommand() = default;

    std::string name() const override {
        return "help";
    }

    void execute(const ArgumentParser& args) override {
       
    }

    void printAll(){}
private:
};