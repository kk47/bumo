#include <iostream>
#include <set>

int main()
{
	std::multiset<int> int_set;
	int_set.insert(1);
	int_set.insert(1);

	std::cout << int_set.size() << std::endl;
	return 0;
}