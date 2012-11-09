#include <stdexcept>

using namespace std;

class InvalidEntryError : public runtime_error
{
public:
	InvalidEntryError(string strIn = "Invalid Entry!") : runtime_error(strIn){}
};