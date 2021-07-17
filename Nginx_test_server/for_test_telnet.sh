#!/bin/bash
{ echo "open www.example.com 80"
sleep 2
echo "GET /index.html HTTP/1.1"
echo "Host: www.example.com"
echo
echo
sleep 2; } | telnet


#TODO need fix for alpine linux!!!