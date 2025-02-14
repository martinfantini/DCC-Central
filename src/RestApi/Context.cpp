#include "Context.hpp"

namespace RestApi
{
    const http::request<http::string_body> &Context::GetRequest()
    {
        return request;
    }

    http::response<http::string_body> &Context::GetResponse() { return response; }

    void Context::SetResponseResult(http::status status, const std::string &body)
    {
        response.result(status);
        response.body() = body;
        response.prepare_payload();
    }

    void Context::SetParam(const std::string &key, const std::string &value)
    {
        params[key] = value;
    }

    std::string Context::GetParam(const std::string &key) const
    {
        auto it = params.find(key);
        if (it != params.end())
        {
            return it->second;
        }
        return ""; // or throw, based on how you want to handle missing params
    }
}
