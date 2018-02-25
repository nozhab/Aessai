#include <iostream>

#include "abc.hpp"
#include "types.hpp"
namespace TestNozha
{
void test_nozha_1()
{
	Test_nozha_1 test;
	const std::string& s = test.get_s();
//	s = "noura";
	std::cout << test.get_s();

}
}



