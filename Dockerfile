FROM       ubuntu:16.04
MAINTAINER realbrosss@naver.com

ENV WORK_HOME=/test 
ENV PATH /opt/cross/solaris/bin:/opt/cross/aix/bin:$PATH
WORKDIR ${WORK_HOME}

RUN        apt-get -y update
RUN        apt-get -y upgrade

# 1. 필요한 친구들
RUN apt-get -y install build-essential
RUN apt-get -y install gcc
RUN apt-get -y install git
RUN apt-get -y install vim
RUN apt-get -y install wget
RUN apt-get -y install unzip

RUN git clone https://github.com/realbrotha/docker_ci_cd.git

RUN mv /test/docker_ci_cd/updateset /opt
RUN mv /test/docker_ci_cd/cross /opt

RUN     echo "test comeplete"

