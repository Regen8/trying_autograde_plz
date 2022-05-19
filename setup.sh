#!/usr/bin/env bash

cd /autograder/source

mkdir -p /root/.ssh
cp ssh_config /root/.ssh/config
# Make sure to include your private key here
mv deploy_key /root/.ssh/deploy_key
chmod 600 /root/.ssh/deploy_key
# To prevent host key verification errors at runtime
ssh-keyscan -t rsa github.com >> ~/.ssh/known_hosts

ssh -vT git@github.tamu.edu
# Clone autograder files
git clone git@github.com:Regen8/trying_autograde_plz.git /autograder/autograder-code