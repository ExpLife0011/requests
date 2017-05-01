#ifndef RESPONSE_H
#define RESPONSE_H

#include "Exception.hpp"
#include "Utils.hpp"

#include <string>
#include <unordered_map>
#include <iostream>

namespace requests {

class Response
{
public:
    Response(const std::string &headers, const std::string &content)
        : headers_(headers), content_(content)
    {
        auto lines = splitTokens(headers_, "\r\n");
        auto tokens = splitTokens(lines[0], " ");

        version_ = std::move(tokens[0]);
        statusCode_ = std::stoi(tokens[1]);
        statusMessage_ = std::move(tokens[2]);
    }

    unsigned short statusCode() const
    {
        return statusCode_;
    }

    const std::string &content() const
    {
        return content_;
    }

    const std::string &statusMessage() const
    {
        return statusMessage_;
    }

    const std::string &headers() const
    {
        return headers_;
    }
    
private:
    std::string       headers_;
    std::string       content_;

    unsigned short    statusCode_;    
    std::string       version_;
    std::string       statusMessage_;
};

} // namespace requests

#endif /* RESPONSE_H */
