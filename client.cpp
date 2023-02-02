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

void readTcp(tcp::socket socket) {
    // getting response from server
    boost::system::error_code error;
    boost::asio::streambuf receive_buffer;
    // TODO: Fix it
     boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        std::cout << "receive failed: " << error.message() << endl;
    } else {
        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        std::cout << "Received: " << data << endl;
    }
}

void sendTcp(tcp::socket socket, const std::string& msg) {
    // request/message from client
    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(msg), error);
    if (!error) {
        std::cout << "Client sent hello message!" << endl;
    } else {
        std::cout << "send failed: " << error.message() << endl;
    }
}

tcp::socket tcpClient(std::string address, int port)
{
    // socket creation
    boost::asio::io_service ioService;
    tcp::socket socket(ioService);

    // connection
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(address), port));
    return socket;
}

void readUdp(boost::asio::ip::udp::socket &socket, boost::asio::ip::udp::endpoint receiverEndpoint) {
    char recv_buf[1024];
    socket.async_receive_from(boost::asio::buffer(recv_buf), receiverEndpoint, [&] (boost::system::error_code error, std::size_t len) {
        std::cout << "Received: " << recv_buf << " and size: " << len << std::endl;
    });

    //    Blocking call
    //    size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
}

void sendUdp(boost::asio::ip::udp::socket socket, boost::asio::ip::udp::endpoint receiverEndpoint, std::string msg) {
    std::cout << receiverEndpoint << std::endl;
    socket.send_to(boost::asio::buffer(msg), receiverEndpoint);
}

void udpClient(std::string address, std::string port)
{
    setvbuf(stdout, nullptr, _IONBF, 0);

    try {
        boost::asio::io_service io_service;
        boost::asio::ip::udp::resolver resolver(io_service);
        boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), address, "25565");
        boost::asio::ip::udp::endpoint receiverEndpoint = *resolver.resolve(query);

        boost::asio::ip::udp::socket msocket(io_service);
        msocket.open(boost::asio::ip::udp::v4());

        while (1) {
            std::string input;
            std::cin >> input;
            readUdp(msocket, receiverEndpoint);
            msocket.async_send_to(boost::asio::buffer(input, input.length()), receiverEndpoint, [&] (boost::system::error_code error, std::size_t len){
                std::cout << "Sent: " << input << " and size: " << len << std::endl;
                io_service.reset();
            });
//            msocket.send_to(boost::asio::buffer(input, input.size()), receiver_endpoint);
        }

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return;
}

int main(int ac, char** av)
{
    boost::asio::io_service io_service;
    udpClient("192.168.0.106", "25565");
    io_service.run();

//     tcp::socket tcpSocket = tcpClient("127.0.0.1", 1234);
//    while (1) {
//        std::string input;
//        std::cin >> input;
//        readTcp();
//         tcpSocket.send(input)
//    }

}