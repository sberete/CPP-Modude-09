#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	PmergeMe sorter;

	if (argc < 2)
	{
		std::cerr << "Usage: ./PmergeMe numbers" << std::endl;
		return (1);
	}

	try
	{
		sorter.parseInput(argv);

		sorter.printBefore();

		sorter.sortVector();
		sorter.sortDeque();

		sorter.printAfter();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}