#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "context/ApplicationContext.h"
/**
 * @brief Abstract class which defines a command
 */
class ICommand {
public:
	virtual ~ICommand() = default;

	virtual std::string name() const = 0; 

	virtual std::string description() const = 0;
    virtual std::string usage() const = 0;

	virtual void execute(ApplicationContext& ctx) = 0;
};
