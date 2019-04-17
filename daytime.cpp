#include <ctime>
#include <string>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/format.hpp>
#include <boost/smart_ptr.hpp>
#include <time.h>

using boost::asio::ip::tcp;

class client_session
{
public:
    typedef boost::shared_ptr<client_session> pointer;

    static pointer create(boost::asio::io_service &io) {
        return pointer(new client_session(io));
    }

    ~client_session() {
        log("Connection closed");
    }

    tcp::socket &socket() { return socket_; }

    void start() {
        log("Connection established");

        std::string time_string;
        for (int i = 0; i < 5; ++i) {
//            time_string = make_time_string();
            boost::asio::write(socket_, boost::asio::buffer("return value\n"));
//            sleep(1);
        }
    }

protected:
    client_session(boost::asio::io_service &io)
            : socket_(io) {
    }

//    std::string make_time_string() {
//        char buf[32];
//        time_t now = time(0);
//        return ctime_s(&buf, sizeof(buf), now);
//    }

    void log(std::string const &message) {
        std::clog << boost::format("%|-25| [client address: %|15|]\n")
                     % message % socket_.remote_endpoint().address().to_string();
    }

private:
    tcp::socket socket_;
};

int main()
{
    boost::asio::io_service io;

    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8001));
    for (;;) {
        client_session::pointer new_client = client_session::create(io);
        acceptor.accept(new_client->socket());
        boost::thread(boost::bind(&client_session::start, new_client)).detach();
    }
}