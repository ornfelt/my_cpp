#include <iostream>
#include "jsonparser.hpp"

int main()
{
	const std::string data("{lol: 7,\
        k: 5,\
        mam: {\
            j: \"78 {}\"     \
        },\
		lil : { \
		ar : [5, 6, 7],\
		l: 3\
		}\
     }");

	jsp::JsonObject root(data);

	std::cout << root["mam"]["j"].asString() << std::endl;

	return 0;
}