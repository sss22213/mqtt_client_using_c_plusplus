mqtt_client_using_c_plusplus
===

This repository contains the source code for the MQTT C++ client library.

## Feature:
- using tcp.
- not support ssl.
- support username and password login.
- like roscpp library

## Depend:

* Eclipse Paho MQTT C++:
  - Install depend for Eclipse Paho MQTT C++:
```
sudo apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui
sudo apt-get install libssl-dev 
sudo apt-get install doxygen graphviz
sudo apt-get install libcppunit-dev
```

  - Install paho_mqtt_c and paho.mqtt.cpp:
```
git clone https://github.com/eclipse/paho.mqtt.cpp
cd paho.mqtt.cpp
sudo bash install_paho_mqtt_c.sh
sudo ldconfig
cmake -Bbuild -H. -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
sudo cmake --build build/ --target install
sudo ldconfig
```

## Install:
```
make
```

## Test:
```
./build/main
```
## Sample:

```c
#include "my_mqtt.hpp"
#include <unistd.h>

// subscribe callback function
void calls(std::string s1){
    std::cout << s1 << std::endl;
}

int main()
{
    // connect mqtt server
    my_mqtt::my_mqtt_service new_device("", "", "", "", ""); // my_mqtt::my_mqtt_service(std::string ip, std::string port, std::string usaername, std::string password, std::string id);
    // my_mqtt::my_mqtt_service new_device("", "", ""); // my_mqtt::my_mqtt_service(std::string ip, std::string port, std::string id);
    if(!new_device.connect()){
        std::cout << "connect fail" << std::endl;
    }
    // declare new node
    my_mqtt::nodehandle nh(&new_device);
    // declare publisher
    my_mqtt::publisher *pub = nh.advertise("TOPIC2"); // advertise(std::string topic_name);
    // declare subscriber
    my_mqtt::subscriber *subs = nh.subscribe("TRY", calls); //subscribe(void(*callback_function)(std::string));
    while(true){
        // publish data
        pub->publish("DATA"); // publish(std::string data);
        sleep(1);
    }
    return 0;
}
```

# Refenerce
* paho.mqtt: https://github.com/eclipse/paho.mqtt.cpp

