#ifndef __REST_API_ROUTER__
#define __REST_API_ROUTER__

#include "Context.hpp"

#include <boost/beast.hpp>
#include <functional>
#include <map>
#include <memory>
#include <regex>
#include <string>

namespace RestApi
{
    namespace http = boost::beast::http;

    class Router 
    {
        private:
            struct RouteInfo
            {
                http::verb method;
                std::string pathPattern;
                std::function<void(Context &)> handler;
            };

            std::vector<RouteInfo> routes;
            std::string prefix;

            std::vector<std::string> SplitPath(const std::string &path);

        public:
            void AddRoute(
                    http::verb method,
                    const std::string &pathPattern,
                    std::function<void(Context &)> handler);

            bool Route(Context &ctx);
            void SetPrefix(const std::string &prefix);
    };
}

#endif
