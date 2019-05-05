#!/bin/bash

sftp pi@10.0.10.10 <<EOF
cd Desktop/RestServer
rm -r *
put -r * .
exit

EOF
