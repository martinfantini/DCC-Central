#ifndef __DCC_EX_DCC_TCP_SERVER__
#define __DCC_EX_DCC_TCP_SERVER__

#include <boost/asio.hpp>
#include <string>

#include "CommandInterface.hpp"

namespace DccExParser
{
    /**
     * Class to generate the listener, where receive TCP connections.
     */
    class DccTcpServer
    {
        public:
            DccTcpServer(boost::asio::io_context& io_context,
                    const std::string& Addrress, int port,
                    CommandInterface& command_interface):
                        m_endpoint(boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::make_address_v4(Addrress), port)),
                        m_acceptor(io_context),
                        m_command_interface(command_interface)
                    {
                        do_accept();
                    }

        private:

            void do_accept()
            {
                m_acceptor.open(m_endpoint.protocol());
                m_acceptor.bind(m_endpoint);
                m_acceptor.listen(boost::asio::socket_base::max_connections);                
                m_acceptor.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
                {
                    if (!ec)
                    {
                        std::make_shared<DccTcpSession>(std::move(socket), m_command_interface)->run();
                    }
                    else 
                    {
                        std::cout << "DccTcpServer Error: " << ec.message() << std::endl;
                    }
                    do_accept();
                });
            }
        private:
            boost::asio::ip::tcp::endpoint  m_endpoint;
            boost::asio::ip::tcp::acceptor  m_acceptor;
            CommandInterface&               m_command_interface;
    }
}
#endif
