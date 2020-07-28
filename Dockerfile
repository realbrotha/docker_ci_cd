FROM       ubuntu:16.04
MAINTAINER subicura@subicura.com
RUN        apt-get -y update

# 1. 필요한 친구들
RUN apt-get -y install build-essential
RUN apt-get -y install gcc
RUN apt-get -y install git
RUN apt-get -y install vim
RUN apt-get -y install python2
RUN pip install --upgrade conan<2.0

RUN     echo "test comeplete"
