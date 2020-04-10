# nRF91TCPTest

Test BSD TCP client connect to server (server/tcp_server)

# Nordicsemi nRF9160 NB-IoT 
https://www.nordicsemi.com/Software-and-tools/Development-Kits/nRF9160-DK

# nRF Connect SDK!
https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/index.html

### Build hex 
  $ west build -b nrf9160_pca10090ns

### Program nRF9160-DK using nrfjprog
  $ nrfjprog --program build/zephyr/merged.hex -f nrf91 --chiperase --reset --verify

# Change Test Server ip & port in prj.conf  
CONFIG_SERVER_HOST="x.x.x.x"

CONFIG_SERVER_PORT=42501


