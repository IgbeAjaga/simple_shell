#!/bin/bash

# Get the maximum value of  process ID in /proc/sys/kernel/pid_max
pid_max=$(cat /proc/sys/kernel/pid_max)

# Print the maximum value
echo "The maximum value for a process ID is: $pid_max"

