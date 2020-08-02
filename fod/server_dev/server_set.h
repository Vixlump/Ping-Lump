void package_request(sf::UdpSocket& socket,sf::IpAddress& sender,unsigned short& port,sf::Packet& that_packet) {
  //0
  string condition_arg;
  string package_arg;
  string string_array[31];
  short int array_controller=0;
  that_packet>>condition_arg;
  condition_arg = "data/"+condition_arg;
  ifstream filetoread (condition_arg.c_str());
  while (getline(filetoread, package_arg)) {
    string_array[array_controller]=package_arg;
    array_controller=array_controller+1;
    if (array_controller==32) {string_array[31]="__ServerForcedStop__";break;}
  }
  sf::Packet that_packet_return;
  for (short int vixmakes=0; vixmakes<=31; vixmakes++) {
    that_packet_return<<string_array[vixmakes];
  }
  bool server_request = true;
  that_packet_return<<server_request;
  socket.send(that_packet_return, sender, port);
}
void package_write(sf::UdpSocket& socket,sf::IpAddress& sender,unsigned short& port,sf::Packet& that_packet) {
  //1
  string condition_arg;
  string package_arg;
  that_packet>>condition_arg>>package_arg;
  condition_arg = "data/"+condition_arg;
  ofstream filetowrite (condition_arg.c_str());
  filetowrite << package_arg;
  bool server_write = true;
  sf::Packet that_packet_return;
  that_packet_return<<server_write;
  socket.send(that_packet_return, sender, port);
  cout<<package_arg<<" was writen to "<<condition_arg<<" by: "<</*sender<<":"<<port<<*/endl;
}
void package_check(sf::UdpSocket& socket,sf::IpAddress& sender,unsigned short& port) {
  sf::Packet that_packet_return;
  bool server_check = true;
  that_packet_return<<server_check;
  socket.send(that_packet_return, sender, port);
  cout<<"server was checked by: "<</*sender<<":"<<port<<*/endl;
}
