#!/usr/bin/env bash

cd /autograder/source

mkdir -p /root/.ssh
cp ssh_config /root/.ssh/config

mv deploy_key /root/.ssh/deploy_key
chmod 600 /root/.ssh/deploy_key

ssh-keyscan -t rsa github.com >> /root/.ssh/known_hosts

git clone git@github.com:Regen8/trying_autograde_plz /autograder/autograder-code