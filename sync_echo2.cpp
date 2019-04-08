#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/lockfree/queue.hpp>
//#include "concurrentqueue.h"
#include <thread>

using boost::asio::ip::tcp;

const int max_length = 1024;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

void session(boost::lockfree::queue<tcp::socket*, boost::lockfree::capacity<1024>> & q) {
    for(;;) {
        tcp::socket* sock;
        if (q.pop(sock)){
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
            sock->close();

    }
    }

}

int main()
{
    boost::lockfree::queue<tcp::socket*, boost::lockfree::capacity<1024>> q;
//    moodycamel::ConcurrentQueue<int> q;
    boost::asio::io_service ios;

    tcp::endpoint ep(tcp::v4(), 8001);
    tcp::acceptor a(ios, ep);

    std::thread t1(session, std::ref(q));
//    std::thread t2(session, std::ref(q));
//    std::thread t3(session, std::ref(q));
//    std::thread t4(session, std::ref(q));
    t1.detach();
//    t2.detach();
//    t3.detach();
//    t4.detach();

    for (;;) {
        auto* s = new tcp::socket(ios);
        a.accept(*s);
        q.bounded_push(s);
    }

    return 0;
}