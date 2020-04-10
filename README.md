# nRF91TCPTest

nRF Connect SDK!
https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/index.html

west build -b nrf9160_pca10090ns
nrfjprog --program build/zephyr/merged.hex -f nrf91 --chiperase --reset --verify

# Test Server
CONFIG_SERVER_HOST="139.162.163.251"
CONFIG_SERVER_PORT=42501

