#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <SFML/Network.hpp>

using namespace std;

#include "server_dev/server_set.h"

//global space
bool shutdown_crit=false;

bool package_manager(sf::UdpSocket& socket, string& exe_arg, string& word_arg);

int main(int argc, char *argv[]) {
  unsigned long long int works=0;
  unsigned long long int fails=0;
  string exe_arg = argv[0];
  string word_arg = argv[1];
  cout<<"Server Started With: "<<word_arg<<endl;
  sf::UdpSocket socket;
  socket.bind(54042);
  while (true) {
    if (package_manager(socket, exe_arg, word_arg)==false) {
      fails=fails+1;
    } else if (shutdown_crit==true) {
      break;
    } else {
      works=works+1;
    }
  }
  cout<<"Closing Log: fails["<<fails<<"] works["<<works<<"]"<<endl;
  system("pause");
  //for linux: system("");
  return 42;
}

bool package_manager(sf::UdpSocket& socket, string& exe_arg, string& word_arg) {
  bool packet_operation = true;
  sf::IpAddress sender; unsigned short port; sf::Packet that_packet;
  unsigned int packet_type;
  socket.receive(that_packet, sender, port);
  that_packet>>packet_type;
  if (packet_type==0) {
    //request
    package_request(socket, sender, port, that_packet);
  } else if (packet_type==1) {
    //write
    package_write(socket, sender, port, that_packet);
  } else if (packet_type==2) {
    //edit
  } else if (packet_type==3) {
    //check
    package_check(socket, sender, port);
  } else if (packet_type==4) {
    //debug
  } else {
    packet_operation=false;
  }
  return packet_operation;
}
