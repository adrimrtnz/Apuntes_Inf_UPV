FROM ubuntu:focal
WORKDIR /root
RUN apt-get update -y
RUN apt-get install -y curl ufw gcc g++ make gnupg
RUN curl -sL https://deb.nodesource.com/setup_16.x | bash -
RUN apt-get update -y
RUN apt-get install -y nodejs
RUN apt-get upgrade -y
RUN npm init -y
RUN npm install zeromq@5
