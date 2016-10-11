#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/**
 * lazy initialization
 * for RemoteConnectionManager, the connection establishing is called once when send_data or receive_data
 */
struct ConnectionInfo {};
struct DataPacket {};
struct ConnectionHandle {
    void send_data(DataPacket const&){}
    DataPacket receive_data(){
        return DataPacket();
    }
};
struct RemoteConnectionManager {
    ConnectionHandle open(ConnectionInfo const&){
        return ConnectionHandle();
    }
} manager;

class X
{
private:
    ConnectionInfo connection_details;
    ConnectionHandle connection;
    std::once_flag connection_init_flag;

    void open_connection(){
        connection = manager.open(connection_details);
    }
public:
    X(ConnectionInfo const& connection_details_): connection_details(connection_details_){}
    void send_data(DataPacket const& data){
        std::call_once(connection_init_flag, &X::open_connection, this);
        connection.send_data(data);
    }
    DataPacket receive_data(){
        std::call_once(connection_init_flag, &X::open_connection, this);
        return connection.receive_data();
    }
};

int main(){
    ConnectionInfo info;
    X x(info);
    x.receive_data();
    return 0;
}