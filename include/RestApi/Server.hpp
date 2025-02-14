#ifndef __REST_API_SERVER__
#define __REST_API_SERVER__

#include "Context.hpp"
#include "Router.hpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

namespace RestApi
{
    namespace beast = boost::beast; // from <boost/beast.hpp>
    namespace http = beast::http;   // from <boost/beast/http.hpp>
    namespace net = boost::asio;    // from <boost/asio.hpp>
    using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

    #define GET (http::verb::get)
    #define POST (http::verb::post)
    #define PUT (http::verb::put)
    #define PATCH (http::verb::patch)
    #define DELETE (http::verb::delete_)

    class Server
    {
        private:
            std::string address;
            short port;
            std::shared_ptr<Router> router;
            net::io_context io_context{1};

        public:
          Server(const std::string& address, short port, std::shared_ptr<Router> router) :
              address(address),
              port(port),
              router(std::move(router))
          {}

          void Session(tcp::socket socket);
          void Run();
          short GetPort();
    };
}

#endif
