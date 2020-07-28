FROM       ubuntu:16.04
MAINTAINER subicura@subicura.com
RUN        apt-get -y update

# 2. ruby 설치
RUN apt-get -y install build-essential
RUN apt-get -y gcc

# COPY . /usr/src/app


#WORKDIR /usr/src/app
# RUN     bundle install


#EXPOSE 4567
RUN     echo "test comeplete"
