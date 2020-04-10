# nRF91TCPTest

## Test BSD library - NB-IoT TCP client connect to server (server/tcp_server)

### nRF Connect SDK!
    https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/index.html

### Nordicsemi nRF9160 NB-IoT 
    https://www.nordicsemi.com/Software-and-tools/Development-Kits/nRF9160-DK

### Application Description
    JSON Data packet {"ActionName":"BSD Test","LED1":false,"LED2":true}

    Client: Connect to server
    Client: Send JSON packet to server
    Server: Return JSON packet to client on open socket
    Client: Close socket

    Client: Validate ActionName - "ActionName":"BSD Test"
    Client: Toggle nRF9160-DK leds - "LED1":false,"LED2":true

### Change Test Server ip & port in prj.conf  
    CONFIG_SERVER_HOST="139.162.163.251"
    CONFIG_SERVER_PORT=42501

### Build hex 
    $ export ZEPHYR_BASE=/????
    $ west build -b nrf9160_pca10090ns

### Program nRF9160-DK using nrfjprog
    $ nrfjprog --program build/zephyr/merged.hex -f nrf91 --chiperase --reset --verify

### Build server
    $ gcc tcp_server.c -o tcp_server


### nRF Connect
![alt text](https://raw.githubusercontent.com/fsieberhagen/nRF91TCPTest/master/images/nRFConnect.jpg)


### Server
![alt text](https://raw.githubusercontent.com/fsieberhagen/nRF91TCPTest/master/images/server.jpg)



