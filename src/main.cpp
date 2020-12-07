#include "my_mqtt.hpp"
#include <unistd.h>

void calls(std::string s1){
    std::cout << s1 << std::endl;
}

int main()
{
    my_mqtt::my_mqtt_service new_device("", "", "", "");
    if(!new_device.connect()){
        std::cout << "connect fail" << std::endl;
    }
    my_mqtt::nodehandle nh(&new_device);
    my_mqtt::publisher *pub = nh.advertise("TOPIC2");
    my_mqtt::subscriber* subs = nh.subscribe("TRY", calls);
    while(true){
        pub->publish("DATA");
        sleep(1);
    }
    return 0;
}