#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	PmergeMe sorter;

	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	try
	{
		sorter.run(argv);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}