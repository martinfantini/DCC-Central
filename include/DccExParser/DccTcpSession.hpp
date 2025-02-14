#ifndef __DCC_EX_DCC_TCP_SESSION__
#define __DCC_EX_DCC_TCP_SESSION__

#include <boost/asio.hpp>
#include <string>

#include "CommandInterface.hpp"
#include "DccExCommandConverter.hpp"
#include <mutex>

namespace DccExParser
{
    class DccTcpSession :
        public DccExCommandResponse,
        public std::enable_shared_from_this<DccTcpSession>
    {
        public:
            DccTcpSession(
                boost::asio::ip::tcp::socket socket, DccExCommandParser& dcc_command_parser):
                    m_socket(std::move(socket)),
                    m_dcc_command_parser(dcc_command_parser)
                    m_dcc_parser(dcc_command_parser)
            {}

            void run()
            {
                m_dcc_command_parser.set_response_callback(shared_from_this());
                wait_for_request();
            }

        private:

            void send_response(const std::string& response)
            {
                m_socket.async_send(boost::asio::buffer(response), boost:bind(m_socket,response));
            }

            void wait_for_request()
            {
                auto self(shared_from_this());
                std::lock_guard<std::mutex> guard{m_useBufferMutex};
                boost::asio::async_read_until(m_socket, m_buffer, "\0", 
                    [this, self](boost::system::error_code ec, std::size_t /*length*/)
                    {
                        if (!ec)
                        {
                            std::string data{std::istreambuf_iterator<char>(&m_buffer),  std::istreambuf_iterator<char>()}; 
                            m_dcc_parser.read_stream(data);
                            wait_for_request();
                        }
                        else
                        {
                            std::cout << "error: " << ec << std::endl;;
                        }
                    });
            }

            boost::asio::ip::tcp::socket m_socket;
            boost::asio::streambuf       m_buffer;
            DccExCommandParser&          m_dcc_command_parser;
            DCCBasicParser               m_dcc_parser;
    }
}
#endif
