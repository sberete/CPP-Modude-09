#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <cstdlib>
# include <algorithm>
# include <ctime>
# include <sstream>
# include <stdexcept>

class PmergeMe
{
	private:
		std::vector<int>	_vector;
		std::deque<int>		_deque;

		void	mergeInsertSortVector(std::vector<int> &vec);
		void	mergeInsertSortDeque(std::deque<int> &deq);

		void	mergeVector(std::vector<int> &left, std::vector<int> &right, std::vector<int> &result);
		void	mergeDeque(std::deque<int> &left, std::deque<int> &right, std::deque<int> &result);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		void	parseInput(char **argv);

		void	sortVector();
		void	sortDeque();

		void	printBefore() const;
		void	printAfter() const;
};

#endif