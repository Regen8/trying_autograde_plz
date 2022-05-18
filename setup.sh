#!/usr/bin/env bash

cd /autograder/source

mkdir -p /root/.ssh
cp ssh_config /root/.ssh/config

mv deploy_key /root/.ssh/deploy_key
chmod 600 /root/.ssh/deploy_key

ssh-keyscan -t rsa github.tamu.edu >> ~/.ssh/known_hosts

ls -la /dev/tty
ssh -vT git@github.tamu.edu

git clone git@github.tamu.edu:Regen8/sample_gradescope /autograder/autograder-code