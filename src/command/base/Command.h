#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../../argument/ParsedArgs.h"

/**
 * @brief Abstract class which defines a command
 */
class Command {
public:
	virtual ~Command() = default;

	virtual std::string name() const = 0; 

	virtual std::string description() const = 0;
  virtual std::string usage() const = 0;

	virtual void execute(const ParsedArgs& args) = 0;
};
