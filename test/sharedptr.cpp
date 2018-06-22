#include <iostream>
#include <string>
#include <memory>

int main()
{
	std::string kk = "This is a test string";
	std::cout << sizeof(kk) << std::endl;

	auto sp = std::make_shared<std::string>(&kk);
	*sp = "new string";

	std::cout << *sp << std::endl;

	return 0;
}