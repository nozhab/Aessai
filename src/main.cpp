#include<stdio.h>
#include <iostream>
#include <functional>
#include <string>
#include <memory>
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdlib.h>

// Link with Iphlpapi.lib
#pragma comment(lib, "IPHLPAPI.lib")
struct Erdos
{
	void whoAmI() { std::cout << " I am erdos" << std::endl; }
	virtual void whoAmIReally() { std::cout << " I am erdos" << std::endl; }
};

struct Fermat : public Erdos
{
	void whoAmI() { std::cout << " I am fermat"<< std::endl; }
	virtual void whoAmIReally() { std::cout << " I am fermat" << std::endl; }
	int b = 0;
};

int main()
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

	DWORD dwSize = 0;
	DWORD dwRetVal = 0;

	unsigned int i = 0;

	// Set the flags to pass to GetAdaptersAddresses
	ULONG flags = GAA_FLAG_SKIP_ANYCAST & GAA_FLAG_SKIP_MULTICAST;

	// default to unspecified address family (both)
	ULONG family = AF_INET;

	LPVOID lpMsgBuf = NULL;

	ULONG outBufLen = 0;
	ULONG Iterations = 0;

	PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
	PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
	PIP_ADAPTER_ANYCAST_ADDRESS pAnycast = NULL;
	PIP_ADAPTER_MULTICAST_ADDRESS pMulticast = NULL;
	IP_ADAPTER_DNS_SERVER_ADDRESS *pDnServer = NULL;
	IP_ADAPTER_PREFIX *pPrefix = NULL;

	dwRetVal = GetAdaptersAddresses(family, flags, NULL, NULL, &outBufLen);

	std::shared_ptr<int> pIntPtr((int*) malloc(10),
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

	auto pt = new int[3];
	delete[] pt;
	

	return 0;
}