#!/bin/bash

sftp pi@10.0.10.10 <<EOF
cd Desktop/RestServer
put * .
exit

EOF