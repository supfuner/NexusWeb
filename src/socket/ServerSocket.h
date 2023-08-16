#include "Socket.h"

namespace pisco{
namespace socket{
    
class ServerSocket : public Socket
{
public:
    ServerSocket(){};
    ServerSocket(const string &ip, int port);
};

}
}