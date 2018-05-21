#include "utils.h"

bool fexists(const char *filename)
{
	std::ifstream ifile(filename);
	return (bool)ifile;
}