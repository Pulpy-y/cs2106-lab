#!/bin/bash
date=$(date +"%e %B %Y") 
time=$(date +%T) 
echo "Hello $(whoami), today is $(date +%A), $date, and the time is $time"
