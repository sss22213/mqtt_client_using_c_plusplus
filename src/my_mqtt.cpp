#include "my_mqtt.hpp"

// my_mqtt_service
my_mqtt::my_mqtt_service::my_mqtt_service(std::string ip, std::string port, std::string id){
    this->tcp_address = "tcp://" + ip + ":" + port;
    this->client = new mqtt::async_client(this->tcp_address, id);
    this->conopts = new mqtt::connect_options(); 
}

my_mqtt::my_mqtt_service::my_mqtt_service(std::string ip, std::string port, std::string user, std::string pwd, std::string id){
    this->tcp_address = "tcp://" + ip + ":" + port;
    this->client = new mqtt::async_client(this->tcp_address, id);
    this->conopts = new mqtt::connect_options(user.c_str(), pwd.c_str());
}

bool my_mqtt::my_mqtt_service::connect(){
    try{
        this->client->set_callback(cb);
        mqtt::token_ptr conntok = client->connect(*this->conopts);
        conntok->wait();
    }
    catch(...){
        return false;
    }
    return true;
}

// nodehandle
my_mqtt::nodehandle::nodehandle(my_mqtt_service* my_mqtt_server){
    this->my_mqtt_server = my_mqtt_server;
}

my_mqtt::publisher* my_mqtt::nodehandle::advertise(std::string topic_name){
    return new publisher(this->my_mqtt_server, topic_name);
}

my_mqtt::subscriber* my_mqtt::nodehandle::subscribe(std::string topic_name, void(*sub_callback)(std::string)){
    subscriber *new_sub = new subscriber(this->my_mqtt_server, topic_name, sub_callback);
    // subscribe
    this->my_mqtt_server->client->subscribe(topic_name, 1);
    this->my_mqtt_server->cb.add_topic(topic_name, new_sub);
    return new_sub;
}

// publisher
my_mqtt::publisher::publisher(my_mqtt_service* my_mqtt_server, std::string topic_name){
    this->mqtt_server = my_mqtt_server;
    this->topic_name = topic_name;
}


bool my_mqtt::publisher::publish(std::string message){
    try{
        mqtt::message_ptr pubmsg = mqtt::make_message(this->topic_name, message.c_str());
        pubmsg->set_qos(1);
        this->mqtt_server->client->publish(pubmsg)->wait_for(std::chrono::seconds(10));
    }
    catch(...){
        return false;
    }
    return true;
}

// subscriber
my_mqtt::subscriber::subscriber(my_mqtt_service* server, 
                                std::string topic_name, 
                                void(*cb_func)(std::string)){
    this->mqtt_server = server;
    this->topic_name = topic_name;
    this->cb_func = cb_func;
}

std::string my_mqtt::subscriber::get_topic_name(){
    return this->topic_name;
}
