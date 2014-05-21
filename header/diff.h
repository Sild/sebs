#include <string>
#include <iostream>
#include <map>
class Diff {
public:
	Diff();
	std::map<int, char *> calculate(std::string oldf, std::string newf);


};