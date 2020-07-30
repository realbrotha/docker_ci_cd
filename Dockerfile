FROM       ubuntu:16.04
MAINTAINER realbrosss@naver.com

ENV WORK_HOME=/test 
    
WORKDIR ${WORK_HOME}

RUN        apt-get -y update

# 1. 필요한 친구들
RUN apt-get -y install build-essential
RUN apt-get -y install gcc
RUN apt-get -y install git
RUN apt-get -y install vim

RUN git clone https://github.com/realbrotha/docker_ci_cd.git
RUN mv /test/docker_ci_cd/cross /opt
RUN export PATH=$PATH:/opt/cross/solaris/bin:/opt/cross/aix/bin

#RUN apt-get -y install python
# RUN pip install --upgrade conan<2.0

RUN     echo "test comeplete"
