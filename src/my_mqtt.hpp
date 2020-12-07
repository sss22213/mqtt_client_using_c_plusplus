#pragma once
#include <string.h>
#include <mqtt/async_client.h>
#include <chrono>
#include <iostream>
#include <functional>
#include <vector>
#include <map>
using namespace std;

namespace my_mqtt{
    // declare
    class my_mqtt_service;
    class nodehandle;

    class publisher{
        private:
            std::string topic_name;
            my_mqtt_service *mqtt_server;
        public:
            publisher(my_mqtt_service*, std::string);
            ~publisher(){};
            bool publish(std::string);
    };

    class subscriber{
        private:
            std::string topic_name;
            my_mqtt_service *mqtt_server;
        public:
            subscriber(my_mqtt_service*, std::string, void(*)(std::string));
            ~subscriber(){};
            std::string get_topic_name(void);
            void(*cb_func)(std::string);
    };
    class callback : public virtual mqtt::callback
    {
        private:
            std::map<std::string, subscriber*> topic_mapping_subscriber;
            std::map<std::string, bool> have_topic;
        public:

            void add_topic(std::string topic_name, subscriber *topic_sub){
                this->topic_mapping_subscriber[topic_name] = topic_sub;
                this->have_topic[topic_name] = true;
            }

            void message_arrived(mqtt::const_message_ptr msg) override {
                std::string topic_name = msg->get_topic();
                if(this->have_topic[topic_name] == false)
                    return;
                this->topic_mapping_subscriber[topic_name]->cb_func(msg->to_string());
                //std::cout << "Message arrived" << std::endl;
                //std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
                //std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;
            }

            void connection_lost(const string& cause) override {
                std::cout << "\nConnection lost" << std::endl;
                if (!cause.empty())
                    std::cout << "\tcause: " << cause << std::endl;
            }

            void delivery_complete(mqtt::delivery_token_ptr tok) override {
                std::cout << "\tDelivery complete for token: "
                    << (tok ? tok->get_message_id() : -1) << std::endl;
            }
    };
    class my_mqtt_service
    {
        private:
            std::string tcp_address;
            // connect option
            mqtt::connect_options *conopts;
        public:
            my_mqtt_service(std::string, std::string, std::string);
            my_mqtt_service(std::string, std::string, std::string, std::string, std::string);
            ~my_mqtt_service(){};
            mqtt::async_client *client;
            bool connect();
            // mqtt callback
            callback cb;
    };
    class nodehandle{
        public:
            nodehandle(my_mqtt_service*);
            ~nodehandle(){};
            publisher *advertise(std::string);
            subscriber* subscribe(std::string, void(*)(std::string));
            my_mqtt_service *my_mqtt_server;
    };
};