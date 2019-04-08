#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
//#include <boost/thread.hpp>

#include <thread>

using boost::asio::ip::tcp;

const int max_length = 1024;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

void session(tcp::endpoint& ep) {
        boost::asio::io_service ios;
        for (;;) {
        tcp::acceptor a(ios, ep);
        socket_ptr sock(new tcp::socket(ios));
        a.accept(*sock);

        for (;;) {
            char data[max_length];

            boost::system::error_code error;
            size_t length = sock->read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            boost::asio::write(*sock, boost::asio::buffer(data, length));
        }
//        std::cout << std::this_thread::get_id() << std::endl;
    }


}

int main()
{

    tcp::endpoint ep(tcp::v4(), 8001);

    std::thread t1(session, std::ref(ep));
    std::thread t2(session, std::ref(ep));
    std::thread t3(session, std::ref(ep));
    std::thread t4(session, std::ref(ep));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}