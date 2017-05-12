#include "Request.hpp"
#include "Response.hpp"
#include "AsyncRequest.hpp"
#include "Url.hpp"
#include "Exception.hpp"

#include <iostream>

void callback(requests::Response &resp)
{
    std::cout << "Status Code: " << resp.statusCode() << std::endl;
    std::cout << "Content-Type: " << resp.headers()["Content-Type"] << std::endl;    
}

int main(int argc, char *argv[])
{   
    try {
        requests::Request request;
        requests::Url url("http://www.baidu.com");

        std::cout << "Make request to " << url << std::endl;        
        auto resp = request.get(url, {{"sx", "cdcd"}});
        
        std::cout << "Status Code: " << resp.statusCode() << std::endl;
        std::cout << "Content-Type: " << resp.headers()["Content-Type"] << std::endl;
        
        requests::AsyncRequest asyncRequest;
        asyncRequest.get(url, callback);
    }
    catch (const requests::Exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    
    return 0;
}