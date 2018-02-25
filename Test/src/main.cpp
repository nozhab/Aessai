#include<stdio.h>
#include <iostream>
#include <functional>
#include <string>
#include <memory>
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdlib.h>
#include <io.h> 
#include <fcntl.h>

// Link with Iphlpapi.lib
#pragma comment(lib, "IPHLPAPI.lib")

//#include "abc.hpp"

/*namespace TestNozha
{*/ 

struct Erdos
{
	void whoAmI() { std::cout << " I am erdos" << std::endl; }
	virtual void whoAmIReally() { std::cout << " I am erdos" << std::endl; }
};
int data[4] = { 1, 2,3 };
//int* const a ;
int * b = data;
//*b = 2;
//struct Foo
//{
//	int ip[4] = { 1, 2,3 };
//	int mac;
//};
//
//void f(Foo const& a)
//{
//	a.ip[0] = 1;
//}
//
//void f(Foo const* a)
//{
//	a->ip = 1;
//} 

//void f(const Foo& a)
//{
//	a.ip = 1;
//}
struct Fermat : public Erdos
{
	void whoAmI() { std::cout << " I am fermat"<< std::endl; }
	virtual void whoAmIReally() { std::cout << " I am fermat" << std::endl; }
	int b = 0;
};

void test_virtual()
{
	Erdos e;
	Fermat f;

	e.whoAmI();
	e.whoAmIReally();

	f.whoAmI();
	f.whoAmIReally();

	e = f;

	e.whoAmI();
	e.whoAmIReally();

	Erdos& e1 = f;

	e1.whoAmI();
	e1.whoAmIReally();

	std::unique_ptr<Erdos> e2;

	e2 = std::make_unique<Fermat>();
}
void test_getadapter(std::wstring const& adaptername)
{
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;

	unsigned int i = 0;

	// Set the flags to pass to GetAdaptersAddresses
	ULONG flags = GAA_FLAG_SKIP_ANYCAST & GAA_FLAG_SKIP_MULTICAST;

	// default to unspecified address family (both)
	ULONG family = AF_INET;

	LPVOID lpMsgBuf = NULL;

	ULONG outBufLen = 0;
	auto s = sizeof(IP_ADAPTER_ADDRESSES);
	ULONG Iterations = 0;

	PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
	PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
	PIP_ADAPTER_MULTICAST_ADDRESS pMulticast = NULL;
	IP_ADAPTER_PREFIX *pPrefix = NULL;

	dwRetVal = GetAdaptersAddresses(family, flags, NULL, NULL, &outBufLen);

	std::shared_ptr<int> pIntPtr((int*)malloc(10),
		[](int *pi) { delete pi; }); // deleter 

	const std::unique_ptr<IP_ADAPTER_ADDRESSES, std::function<void(IP_ADAPTER_ADDRESSES *)>> pAddresses
	(
		(IP_ADAPTER_ADDRESSES *)malloc(outBufLen),
		[](IP_ADAPTER_ADDRESSES *pi)
	{
		std::cout << "destroying from a custom deleter...\n";
		free(pi);
	}
	);

	const std::unique_ptr<IP_ADAPTER_ADDRESSES, decltype(free)*> pAddresses1
	(
		(IP_ADAPTER_ADDRESSES *)malloc(outBufLen), free
	);

	std::unique_ptr<BYTE[]> buf(new BYTE[outBufLen]);
	PIP_ADAPTER_ADDRESSES pAddresses2 = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buf.get());
	/*const std::unique_ptr<IP_ADAPTER_ADDRESSES[]> pAddresses1 (new IP_ADAPTER_ADDRESSES[(outBufLen/s)]);

	auto a = new IP_ADAPTER_ADDRESSES[(outBufLen / s)];
*/
	std::cout << Iterations << "  size  " << sizeof(*pAddresses1) << std::endl;


	dwRetVal = GetAdaptersAddresses(family, flags, NULL, pAddresses2, &outBufLen);

	for (auto& adress = pAddresses2; adress != NULL; adress = adress->Next)
	{
		Iterations += 1;
		//	std::cout << Iterations << "  size  " << sizeof(*adress) << std::endl;
		auto name = std::wstring(pAddresses2->FriendlyName);
		if (adaptername == name)
		{
			std::wcout << name <<'\n';
		}
	}
}


int main()
{
	/*Foo const* a;
	auto b = a->ip;*/
	//TestNozha::test_nozha_1();
	//std::cout << " I am fermat
	_setmode(_fileno(stdout), _O_U16TEXT);
	std::wstring name = L"Connexion au réseau local";
	test_getadapter(name);
	return 0;
}
