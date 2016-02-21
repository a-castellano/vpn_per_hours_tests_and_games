#!/bin/bash

TOKEN="CHURRO"


rx_bytes=$(cat /sys/class/net/eth0/statistics/rx_bytes)
tx_bytes=$(cat /sys/class/net/eth0/statistics/tx_bytes)

total_bytes=`expr $rx_bytes + $tx_bytes`

echo "RX -> $rx_bytes"
echo "TX -> $tx_bytes"
echo "Total -> $total_bytes"
