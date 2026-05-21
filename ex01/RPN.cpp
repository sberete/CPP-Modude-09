#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other)
{
	*this = other;
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_stack = other._stack;
	return (*this);
}

RPN::~RPN() {}

bool RPN::isOperator(const std::string &token) const
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::doOperation(int a, int b, const std::string &op) const
{
	if (op == "+")
		return (a + b);
	if (op == "-")
		return (a - b);
	if (op == "*")
		return (a * b);
	if (op == "/")
	{
		if (b == 0)
			throw std::runtime_error("Error: division by zero.");
		return (a / b);
	}
	throw std::runtime_error("Error: invalid operator.");
}

int RPN::evaluate(const std::string &expression)
{
	std::stringstream	ss(expression);
	std::string			token;
	int					a;
	int					b;

	while (ss >> token)
	{
		if (token.size() == 1 && std::isdigit(token[0]))
			_stack.push(token[0] - '0');
		else if (isOperator(token))
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Error.");

			b = _stack.top();
			_stack.pop();

			a = _stack.top();
			_stack.pop();

			_stack.push(doOperation(a, b, token));
		}
		else
			throw std::runtime_error("Error.");
	}

	if (_stack.size() != 1)
		throw std::runtime_error("Error.");

	return (_stack.top());
}