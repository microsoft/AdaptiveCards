#!/bin/bash
machine='machine microsoft.vsblob.visualstudio.com'
user='login joswo@microsoft.com'
ACPAT='7rvtdw3ihxbfo262z7h24asnkr42znukpzzccy7fl2eoinfdqrdq'

machineRepo='machine microsoft.visualstudio.com'
userRepo='login joswo@microsoft.com'
ACRepoPAT='lp4qhhgrruxy5k6sznwdmlb3sk3lyivodox5x4vntnje5vdtaca'

echo -e "\n${machine}" >> ~/.netrc
echo "  ${user}" >> ~/.netrc
echo "  password ${ACPAT}" >> ~/.netrc

echo -e "\n${machineRepo}" >> ~/.netrc
echo "  ${userRepo}" >> ~/.netrc
echo "  password ${ACRepoPAT}" >> ~/.netrc
