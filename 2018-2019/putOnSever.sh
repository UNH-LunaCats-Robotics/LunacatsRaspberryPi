#!/bin/bash

sftp pi@10.0.10.10 <<EOF
cd Desktop/LunacatsCode/LunacatsRaspberryPi
rm -r *
put -r * .
exit

EOF
