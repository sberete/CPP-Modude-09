#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

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
	}
	return (*this);
}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(char **argv)
{
	int	value;

	for (int i = 1; argv[i]; i++)
	{
		std::stringstream ss(argv[i]);

		ss >> value;

		if (ss.fail() || !ss.eof())
			throw std::runtime_error("Error");

		if (value < 0)
			throw std::runtime_error("Error");

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

void PmergeMe::mergeVector(std::vector<int> &left, std::vector<int> &right, std::vector<int> &result)
{
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;

	while (i < left.size() && j < right.size())
	{
		if (left[i] < right[j])
			result[k++] = left[i++];
		else
			result[k++] = right[j++];
	}

	while (i < left.size())
		result[k++] = left[i++];

	while (j < right.size())
		result[k++] = right[j++];
}

void PmergeMe::mergeInsertSortVector(std::vector<int> &vec)
{
	if (vec.size() <= 1)
		return ;

	size_t mid = vec.size() / 2;

	std::vector<int> left(vec.begin(), vec.begin() + mid);
	std::vector<int> right(vec.begin() + mid, vec.end());

	mergeInsertSortVector(left);
	mergeInsertSortVector(right);

	mergeVector(left, right, vec);
}

void PmergeMe::mergeDeque(std::deque<int> &left, std::deque<int> &right, std::deque<int> &result)
{
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;

	while (i < left.size() && j < right.size())
	{
		if (left[i] < right[j])
			result[k++] = left[i++];
		else
			result[k++] = right[j++];
	}

	while (i < left.size())
		result[k++] = left[i++];

	while (j < right.size())
		result[k++] = right[j++];
}

void PmergeMe::mergeInsertSortDeque(std::deque<int> &deq)
{
	if (deq.size() <= 1)
		return ;

	size_t mid = deq.size() / 2;

	std::deque<int> left(deq.begin(), deq.begin() + mid);
	std::deque<int> right(deq.begin() + mid, deq.end());

	mergeInsertSortDeque(left);
	mergeInsertSortDeque(right);

	mergeDeque(left, right, deq);
}

void PmergeMe::sortVector()
{
	clock_t start;
	clock_t end;

	start = clock();

	mergeInsertSortVector(_vector);

	end = clock();

	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " << static_cast<double>(end - start) << " us" << std::endl;
}

void PmergeMe::sortDeque()
{
	clock_t start;
	clock_t end;

	start = clock();

	mergeInsertSortDeque(_deque);

	end = clock();

	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque : " << static_cast<double>(end - start) << " us" << std::endl;
}