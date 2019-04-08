//#include <iostream>
//#include <thread>
//#include <memory>
//#include <atomic>
//
//#include <boost/asio.hpp>
//#include <boost/asio/spawn.hpp>
//
//using namespace boost::asio::ip;
//using namespace boost::asio;
//using std::cout;
//using std::endl;
//
//std::atomic<int> active;
//
//void echo_server(boost::asio::io_service &svc, int c)
//{
//    spawn(svc, [&svc, c](yield_context y) {
//        try
//        {
//            tcp::acceptor acceptor(svc, tcp::endpoint(tcp::v4(), 8001));
//            for (int i = 0; i < c; i++)
//            {
//                std::shared_ptr<tcp::socket> s = std::make_shared<tcp::socket>(svc);
//                acceptor.async_accept(*s, y);
//
//                spawn(y, [s](yield_context y) mutable {
//                    try
//                    {
//                        streambuf buf;
//                        for (;;)
//                        {
//                            async_read(*s, buf, transfer_at_least(1), y);
//                            async_write(*s, buf, y);
//                        }
//                    }
//                    catch (boost::system::system_error &e)
//                    {
//                        if (e.code() != error::eof)
//                            cout << e.what() << endl;
//                    }
//                });
//            }
//            cout << "Server Done\n";
//        }
//        catch (std::exception &e)
//        {
//            std::cerr << "Server Exception: " << e.what() << std::endl;
//        }
//    });
//}
//
//int main()
//{
//    boost::asio::io_service svc;
//    int c = 100;
//
//    // Schedule a server
//    echo_server(svc, c);
//
//    svc.run();
//}