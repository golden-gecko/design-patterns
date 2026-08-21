#pragma once

#include <iostream>
#include <string>

namespace DemoAdapter
{
    class VeryLegacyDriver
    {
    public:
        void setHost(const std::string& host)
        {
            std::cout << "VeryLegacyDriver::setHost(" << host << ")" << std::endl;
        }

        void setPort(int port)
        {
            std::cout << "VeryLegacyDriver::setPort(" << port << ")" << std::endl;
        }

        bool makeConnection()
        {
            std::cout << "VeryLegacyDriver::connect()" << std::endl;

            return true;
        }
    };

    class IConnectable
    {
    public:
        virtual bool connect(const std::string& uri) = 0;
    };

    class Driver : public IConnectable, private VeryLegacyDriver
    {
    public:
        bool connect(const std::string& uri) override
        {
            std::cout << "Driver::connect(" << uri << ")" << std::endl;

            setHost("host");
            setPort(10);

            return makeConnection();
        }
    };

    void run()
    {
        Driver driver;

        driver.connect("protocol://host:10");
    }
}
