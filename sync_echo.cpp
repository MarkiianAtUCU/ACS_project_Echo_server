#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
const int max_length = 1024;

int main()
{

    tcp::endpoint ep(tcp::v4(), 8001);
    boost::asio::io_service ios;
    tcp::acceptor a(ios, ep);

    tcp::socket sock(ios);
    for (;;) {
        a.accept(sock);
        for (;;) {
            char data[max_length];
            boost::system::error_code error;
            size_t length = sock.read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof) break;
            boost::asio::write(sock, boost::asio::buffer(data, length));
        }
        sock.close();
    }


    return 0;
}