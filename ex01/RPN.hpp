#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <sstream>
# include <cstdlib>
# include <stdexcept>
# include <cctype>

class RPN
{
	private:
		std::stack<int> _stack;

		bool	isOperator(const std::string &token) const;
		int		doOperation(int a, int b, const std::string &op) const;

	public:
		RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);
		~RPN();

		int	evaluate(const std::string &expression);
};

#endif