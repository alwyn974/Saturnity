/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** client
*/

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
using namespace boost::asio;

using ip::tcp;
using std::endl;
using std::string;

string read(tcp::socket& socket)
{
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}

int tcpClient()
{
    boost::asio::io_service io_service;

    // socket creation
    tcp::socket socket(io_service);

    // connection
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));

    // request/message from client
    const string msg = "Hello from Client!\n";
    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(msg), error);
    if (!error) {
        std::cout << "Client sent hello message!" << endl;
    } else {
        std::cout << "send failed: " << error.message() << endl;
    }

    // getting response from server
    boost::asio::streambuf receive_buffer;
    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        std::cout << "receive failed: " << error.message() << endl;
    } else {
        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        std::cout << "Received: " << data << endl;
    }
    return 0;
}

int udpClient(std::string arg)
{

    try {
        boost::asio::io_service io_service;
        boost::asio::ip::udp::resolver resolver(io_service);
        boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "192.168.74.93", "25565");
        boost::asio::ip::udp::endpoint receiver_endpoint = *resolver.resolve(query);

        boost::asio::ip::udp::socket socket(io_service);
        socket.open(boost::asio::ip::udp::v4());

        std::cout << receiver_endpoint << std::endl;
        socket.send_to(boost::asio::buffer("test"), receiver_endpoint);

        boost::array<char, 128> recv_buf;
        boost::asio::ip::udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

        std::cout << recv_buf.data() << " AND " << len << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

int main(int ac, char** av)
{
    udpClient(av[1]);

    // tcpClient();
}