#ifndef ABC_HPP
#define ABC_HPP

#include <string>
namespace TestNozha
{
void test_nozha_1();
class Test_nozha_1
{
private:
	std::string s = "nozha";
public:
	const std::string& get_s() const
	{
		return s;
	}
};

}
#endif // !ABC_HPP
