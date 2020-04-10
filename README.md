# nRF91TCPTest
BCD TCP Test on nrf9160 


# Test Server
CONFIG_SERVER_HOST="139.162.163.251"
CONFIG_SERVER_PORT=42501

set(ENV{GNUARMEMB_TOOLCHAIN_PATH} /opt/gnuarmemb)
set(ENV{ZEPHYR_BASE} /Users/francissieberhagen/Work/Nordic/ncs/zephyr)

https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/index.html
https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/gs_assistant.html

west build -b nrf9160_pca10090ns
nrfjprog --program build/zephyr/merged.hex -f nrf91 --chiperase --reset --verify

SEGGER Embedded Studio for ARM 4.52
https://developer.nordicsemi.com/nRF_Connect_SDK/doc/0.4.0/nrf/gs_programming.html?highlight=zephyr%20base
