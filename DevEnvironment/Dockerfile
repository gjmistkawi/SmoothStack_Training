FROM centos:latest
RUN yum update -y
RUN yum -y install vim
RUN yum -y install gdb
RUN yum -y install clang
RUN yum -y install curl
RUN yum -y install tree
#RUN yum -y install htop
#RUN yum -y install iftop
#RUN yum -y install iotop
#RUN yum -y install wget
#RUN yum -y install xterm
#RUN yum -y install epel-release

RUN dnf -y group install "Development Tools"

COPY . /usr/src
WORKDIR /usr/src