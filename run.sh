#!/bin/bash

sudo rm -rf /var/log/matt_daemon/matt_daemon.log
sudo rm -rf /var/lock/matt_daemon.lock
sudo pkill Matt_daemon
