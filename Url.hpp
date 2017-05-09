#ifndef URL_H
#define URL_H

#include "Utils.hpp"
#include "Exception.hpp"
#include <string>

namespace requests {

class Url
{
public:
    using String     = std::string;
    using StringMap  = std::unordered_map<String, String>;
    
    explicit Url(const String &url)
        : url_(url),
          port_("80")
    {
        auto tokens = splitString(url, "://");        
        if (tokens.size() != 2)
        {
            throw Exception("Invalid URL - no schema supplied: " + url_);                        
        }
        
        schema_ = std::move(tokens[0]);

        auto other = splitString(tokens[1], "/", 1);

        auto hostAndPort = splitString(other[0], ":");
        if (hostAndPort.size() != 1 && hostAndPort.size() != 2)
        {
            throw Exception("Invalid Host and Port: " + other[0]);
        }        

        host_ = std::move(hostAndPort[0]);

        if (hostAndPort.size() == 2)
        {
            port_ = std::move(hostAndPort[1]);
        }

        path_ = "/";

        if (other.size() == 2)
        {
            auto pathQueries = splitString(other[1], "?", 1);
            
            if (pathQueries.size() == 1)
            {
                queries_ = std::move(pathQueries[0]);
            }
            else
            {
                path_.append(pathQueries[0]);
                queries_ = std::move(pathQueries[1]);
            }
        }
    }

    void addQueries(const StringMap &params)
    {
        auto queries = urlEncode(params);
        if (hasQueries())
        {
            queries_.append("&").append(queries);
        }
        else
        {
            queries_ = std::move(queries);
        }
    }
    
    bool hasQueries() const
    {
        return !queries_.empty();        
    }

    String pathAndQueries() const
    {
        if (hasQueries())
        {
            return path_ + "?" + queries_;
        }
        return path_;
    }
    
    const String &host() const
    {
        return host_;
    }

    const String &port() const
    {
        return port_;
    }
    
    const String &schema() const
    {
        return schema_;
    }

    const String &path() const
    {
        return path_;
    }

    const String &queries() const
    {
        return queries_;
    }

    String toString() const
    {
        return schema() + "://" + host() + pathAndQueries();
    }
    
private:
    String         url_;
    String         schema_;
    String         host_;
    String         port_;
    String         path_;
    String         queries_;    
};

std::ostream &operator<<(std::ostream &os, const Url &url)
{
    os << url.toString() << std::endl;
    return os;
}
    
} // namespace requests

#endif /* URL_H */
