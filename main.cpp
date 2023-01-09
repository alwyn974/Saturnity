/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** main
*/

#include "comm.pb.h"
#include <boost/asio.hpp>

using namespace boost::asio;
using std::string;
using ip::tcp;
using std::cout;
using std::endl;

string read_(tcp::socket & socket) {
       boost::asio::streambuf buf;
       boost::asio::read_until( socket, buf, "\n" );
       string data = boost::asio::buffer_cast<const char*>(buf.data());
       return data;
}

int socket(void) {
    boost::asio::io_service io_service;

    //listen for new connection
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234 ));

    //socket creation
    tcp::socket socket_(io_service);

    //waiting for connection
    acceptor_.accept(socket_);

    //read operation
    string message = read_(socket_);
    cout << message << endl;

    //write operation
    server::Player player = server::Player();
    player.set_username("Player One");
    std::string temp;
    player.SerializeToString(&temp);
    cout << "Sent: " << temp << endl;
    boost::asio::write(socket_, boost::asio::buffer(temp));
    return 0;
}

int main(void) {
    socket();
}