#include <iostream>
#include <cstdio>


#include "vector.hpp"

using namespace std;

int main()
{
    std::cout << "*********************************" << std::endl;
    std::cout << "Testing Vector Implementation...." << std::endl;
    std::cout << "*********************************" << std::endl;

    std::cout << "Create a new Vector of default size" << std::endl;
    lni::vector<int> v1;
    std::cout << "v1 size:" << v1.size() << std::endl;
    //for (auto &n: v1)
	// 	printf(" %d", n);

    std::cout << "Create a vector of size (n * 2^2)" << std::endl;
    lni::vector<int> v2(10);
    std::cout << "v2 size:" << v2.size() << std::endl;
    //for (auto &n: v2)
	// 	printf(" %d", n);

    std::cout << "Create a vector of size type n and add a default value to it." << std::endl;
    lni::vector<int> v3(10, 5);
    std::cout << "v3 size:" << v3.size() << std::endl;
    int sz = v3.size();
	//for (int i = 0; i < sz; i++)
	//	printf(" %d", v3[i]);
	//puts("\n");




    return 0;
}
