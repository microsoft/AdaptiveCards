#!/bin/bash
machine='machine microsoft.vsblob.visualstudio.com'
user='login joswo@microsoft.com'
ACPAT='7rvtdw3ihxbfo262z7h24asnkr42znukpzzccy7fl2eoinfdqrdq'

echo -e "\n${machine}" >> ~/.netrc
echo "  ${user}" >> ~/.netrc
echo "  password ${ACPAT}" >> ~/.netrc
