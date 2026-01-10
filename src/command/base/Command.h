#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../../argument/Arguments.h"

/**
 * @brief Abstract class which defines a command
 */
class Command {
public:
	virtual ~Command() = default;

	virtual void execute(const Arguments& args) = 0;

    std::string getCmdName() const { return this->cmdName; }
protected:    
	std::string cmdName;
};