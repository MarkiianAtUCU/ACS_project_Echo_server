#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include <boost/enable_shared_from_this.hpp>
#include <boost/core/noncopyable.hpp>
using namespace boost::asio;

class talk_to_client : public boost::enable_shared_from_this<talk_to_client>, boost::noncopyable
{
    typedef talk_to_client self_type;
    talk_to_client() : sock_(service), started_(false) {}
public:
    typedef boost::system::error_code error_code;
    typedef boost::shared_ptr<talk_to_client> ptr;
    void start()
    {
        started_ = true;
        do_read();
    }
    static ptr new_()
    {
        ptr new_(new talk_to_client);
        return new_;
    }
    void stop()
    {
        if ( !started_) return;
        started_ = false;
        vsock_.close();
    }
    ip::tcp::socket & sock() { return sock_;}
    ...
private:
    ip::tcp::socket sock_;
    enum { max_msg = 1024 };
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    bool started_;
};