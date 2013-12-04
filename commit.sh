#!/bin/expect -f

log_user 0
spawn git push origin master

expect "Username"
send "pkuwwt\r"
log_user 1
interact
