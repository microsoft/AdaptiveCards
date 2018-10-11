#!/bin/bash
machine='machine microsoft.vsblob.visualstudio.com'
user='login joswo@microsoft.com'
ACPAT='7rvtdw3ihxbfo262z7h24asnkr42znukpzzccy7fl2eoinfdqrdq'

machineRepo='machine microsoft.visualstudio.com'
userRepo='login joswo@microsoft.com'
ACRepoPAT='hj3sp5iwflhtpfcxjru2tlpaki5ac24vejrxjiocaxk5r7gppaxa'

echo -e "\n${machine}" >> ~/.netrc
echo "  ${user}" >> ~/.netrc
echo "  password ${ACPAT}" >> ~/.netrc

echo -e "\n${machineRepo}" >> ~/.netrc
echo "  ${userRepo}" >> ~/.netrc
echo "  password ${ACRepoPAT}" >> ~/.netrc
