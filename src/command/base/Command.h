#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../../argument/ArgumentParser.h"

/**
 * @brief Abstract class which defines a command
 */
class Command {
public:
	virtual ~Command() = default;

	virtual std::string name() const = 0; 

	virtual void execute(const ArgumentParser& args) = 0;
};