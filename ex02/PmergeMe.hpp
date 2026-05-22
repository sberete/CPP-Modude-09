#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <sstream>
# include <stdexcept>
# include <cstdlib>
# include <ctime>
# include <climits>
# include <algorithm>
#include <iomanip>

struct s_vec_item
{
	int		value;
	int		bound;
	bool	has_bound;
};

struct s_deq_item
{
	int		value;
	int		bound;
	bool	has_bound;
};

class PmergeMe
{
	private:
		std::vector<int>	_vector;
		std::deque<int>		_deque;

		double				_vector_time;
		double				_deque_time;

		void				parseInput(char **argv);
		int					parseNumber(const std::string &str) const;

		void				printBefore() const;
		void				printAfter() const;

		void				sortVector();
		void				sortDeque();

		void				fordJohnsonVector(std::vector<int> &container);
		void				fordJohnsonDeque(std::deque<int> &container);

		std::vector<size_t>	buildJacobOrderVector(size_t size) const;
		std::deque<size_t>	buildJacobOrderDeque(size_t size) const;

		void				insertPendVector(std::vector<int> &main_chain,std::vector<s_vec_item> &pend);

		void				insertPendDeque(std::deque<int> &main_chain,std::deque<s_deq_item> &pend);

		std::vector<int>::iterator	boundVector(std::vector<int> &main_chain,const s_vec_item &item);

        std::deque<int>::iterator	boundDeque(std::deque<int> &main_chain,const s_deq_item &item);

		void				printTimes() const;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		void				run(char **argv);
};

#endif