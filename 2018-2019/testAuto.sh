#!/bin/bash

ssh pi@10.0.10.10 <<EOF
cd Desktop/RestServer
sudo python3 Autonomous.py

EOF
