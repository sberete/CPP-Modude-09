#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vector_time(0), _deque_time(0) {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_deque = other._deque;
		_vector_time = other._vector_time;
		_deque_time = other._deque_time;
	}
	return (*this);
}

PmergeMe::~PmergeMe() {}

int PmergeMe::parseNumber(const std::string &str) const
{
	std::stringstream	ss(str);
	long				value;
	char				c;

	if (str.empty())
		throw std::runtime_error("Error");
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
			throw std::runtime_error("Error");
	}
	ss >> value;
	if (ss.fail() || (ss >> c))
		throw std::runtime_error("Error");
	if (value < 0 || value > INT_MAX)
		throw std::runtime_error("Error");
	return (static_cast<int>(value));
}

void PmergeMe::parseInput(char **argv)
{
	int	value;

	for (int i = 1; argv[i]; i++)
	{
		value = parseNumber(argv[i]);
		_vector.push_back(value);
		_deque.push_back(value);
	}
}

void PmergeMe::printBefore() const
{
	std::cout << "Before: ";
	for (size_t i = 0; i < _vector.size(); i++)
		std::cout << _vector[i] << " ";
	std::cout << std::endl;
}

void PmergeMe::printAfter() const
{
	std::cout << "After: ";
	for (size_t i = 0; i < _vector.size(); i++)
		std::cout << _vector[i] << " ";
	std::cout << std::endl;
}

std::vector<size_t> PmergeMe::buildJacobOrderVector(size_t size) const
{
	std::vector<size_t>	order;
	std::vector<size_t>	jacob;
	size_t				prev;
	size_t				curr;
	size_t				next;

	if (size == 0)
		return (order);
	jacob.push_back(0);
	jacob.push_back(1);
	while (jacob.back() < size)
	{
		prev = jacob[jacob.size() - 2];
		curr = jacob[jacob.size() - 1];
		next = curr + 2 * prev;
		jacob.push_back(next);
	}
	for (size_t i = 1; i < jacob.size(); i++)
	{
		size_t end = jacob[i];
		size_t start = jacob[i - 1];

		if (end > size)
			end = size;
		while (end > start)
		{
			order.push_back(end - 1);
			end--;
		}
	}
	return (order);
}

std::deque<size_t> PmergeMe::buildJacobOrderDeque(size_t size) const
{
	std::deque<size_t>	order;
	std::deque<size_t>	jacob;
	size_t				prev;
	size_t				curr;
	size_t				next;

	if (size == 0)
		return (order);
	jacob.push_back(0);
	jacob.push_back(1);
	while (jacob.back() < size)
	{
		prev = jacob[jacob.size() - 2];
		curr = jacob[jacob.size() - 1];
		next = curr + 2 * prev;
		jacob.push_back(next);
	}
	for (size_t i = 1; i < jacob.size(); i++)
	{
		size_t end = jacob[i];
		size_t start = jacob[i - 1];

		if (end > size)
			end = size;
		while (end > start)
		{
			order.push_back(end - 1);
			end--;
		}
	}
	return (order);
}

std::vector<int>::iterator PmergeMe::boundVector(std::vector<int> &main_chain, const s_vec_item &item)
{
	if (!item.has_bound)
		return (main_chain.end());
	return (std::lower_bound(main_chain.begin(), main_chain.end(), item.bound));
}

std::deque<int>::iterator PmergeMe::boundDeque(
	std::deque<int> &main_chain,
	const s_deq_item &item)
{
	if (!item.has_bound)
		return (main_chain.end());
	return (std::lower_bound(main_chain.begin(), main_chain.end(), item.bound));
}

void PmergeMe::insertPendVector(std::vector<int> &main_chain, std::vector<s_vec_item> &pend)
{
	std::vector<size_t>	order;
	std::vector<int>::iterator	end;
	std::vector<int>::iterator	pos;

	order = buildJacobOrderVector(pend.size());
	for (size_t i = 0; i < order.size(); i++)
	{
		end = boundVector(main_chain, pend[order[i]]);
		pos = std::lower_bound(main_chain.begin(), end, pend[order[i]].value);
		main_chain.insert(pos, pend[order[i]].value);
	}
}

void PmergeMe::insertPendDeque(std::deque<int> &main_chain, std::deque<s_deq_item> &pend)
{
	std::deque<size_t>	order;
	std::deque<int>::iterator	end;
	std::deque<int>::iterator	pos;

	order = buildJacobOrderDeque(pend.size());
	for (size_t i = 0; i < order.size(); i++)
	{
		end = boundDeque(main_chain, pend[order[i]]);
		pos = std::lower_bound(main_chain.begin(), end, pend[order[i]].value);
		main_chain.insert(pos, pend[order[i]].value);
	}
}

void PmergeMe::fordJohnsonVector(std::vector<int> &container)
{
	std::vector<int>		bigs;
	std::vector<int>		main_chain;
	std::vector<s_vec_item>	pend;
	bool					has_odd;
	int						odd;

	if (container.size() <= 1)
		return ;
	has_odd = false;
	for (size_t i = 0; i + 1 < container.size(); i += 2)
	{
		int a = container[i];
		int b = container[i + 1];

		if (a < b)
		{
			bigs.push_back(b);
			s_vec_item item = {a, b, true};
			pend.push_back(item);
		}
		else
		{
			bigs.push_back(a);
			s_vec_item item = {b, a, true};
			pend.push_back(item);
		}
	}
	if (container.size() % 2)
	{
		has_odd = true;
		odd = container.back();
	}
	fordJohnsonVector(bigs);
	main_chain = bigs;
	if (has_odd)
	{
		s_vec_item item = {odd, 0, false};
		pend.push_back(item);
	}
	insertPendVector(main_chain, pend);
	container = main_chain;
}

void PmergeMe::fordJohnsonDeque(std::deque<int> &container)
{
	std::deque<int>		bigs;
	std::deque<int>		main_chain;
	std::deque<s_deq_item>	pend;
	bool					has_odd;
	int						odd;

	if (container.size() <= 1)
		return ;
	has_odd = false;
	for (size_t i = 0; i + 1 < container.size(); i += 2)
	{
		int a = container[i];
		int b = container[i + 1];

		if (a < b)
		{
			bigs.push_back(b);
			s_deq_item item = {a, b, true};
			pend.push_back(item);
		}
		else
		{
			bigs.push_back(a);
			s_deq_item item = {b, a, true};
			pend.push_back(item);
		}
	}
	if (container.size() % 2)
	{
		has_odd = true;
		odd = container.back();
	}
	fordJohnsonDeque(bigs);
	main_chain = bigs;
	if (has_odd)
	{
		s_deq_item item = {odd, 0, false};
		pend.push_back(item);
	}
	insertPendDeque(main_chain, pend);
	container = main_chain;
}

void PmergeMe::sortVector()
{
	clock_t	start;
	clock_t	end;

	start = clock();
	fordJohnsonVector(_vector);
	end = clock();
	_vector_time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

void PmergeMe::sortDeque()
{
	clock_t	start;
	clock_t	end;

	start = clock();
	fordJohnsonDeque(_deque);
	end = clock();
	_deque_time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

void PmergeMe::printTimes() const
{
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " << _vector_time << " us" << std::endl;

	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque : " << _deque_time << " us" << std::endl;
}

void PmergeMe::run(char **argv)
{
	parseInput(argv);
	printBefore();
	sortVector();
	sortDeque();
	printAfter();
	printTimes();
}