#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <SFML/Network.hpp>

using namespace std;

int main(int argc, char *argv[]) {
  string ip_arg = argv[1];
  string port_arg = argv[2];
  string word_arg = argv[3];
  string condition_arg = argv[4];
  string package_arg = argv[5];
  sf::UdpSocket socket;
  sf::IpAddress server_ip = ip_arg;
  unsigned short port = atoi(port_arg.c_str());
  unsigned short server_port = 54042;
  socket.bind(port);
  sf::Packet that_packet;
  unsigned int packet_type = atoi(word_arg.c_str());
  that_packet<<packet_type<<condition_arg<<package_arg;
  socket.send(that_packet, server_ip, server_port);
  sf::Packet that_packet_return;
  socket.receive(that_packet_return, server_ip, server_port);
  if (packet_type==0) {
    bool server_request;
    string string_array[31];
    for (short int vixmakes=0; vixmakes<=31; vixmakes++) {
      that_packet_return>>string_array[vixmakes];
      cout<<string_array[vixmakes]<<endl;
    }
    that_packet_return>>server_request;
    cout<<server_request<<endl;
  } else if (packet_type==1) {
    bool server_write;
    that_packet_return>>server_write;
    cout<<server_write<<endl;
  } else if (packet_type==2) {

  } else if (packet_type==3) {
    //check
    bool server_check;
    that_packet_return>>server_check;
    cout<<server_check<<endl;
  } else if (packet_type==4) {

  } else {

  }
  return 42;
}
