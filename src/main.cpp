#include <mqtt/client.h>

int main()
{
    mqtt::client new_client("111.250.228.72", "1883");
    new_client.connect();
    return 0;
}