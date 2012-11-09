#include <stdexcept>

using namespace std;

class UnavailableRoomError : public runtime_error
{
public:
	UnavailableRoomError(string strIn = "That room is unavailable!") : runtime_error(strIn){}
};