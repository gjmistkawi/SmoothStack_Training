FROM centos:latest

RUN yum -y install clang

RUN yum -y install vim

COPY . /usr/src

WORKDIR /usr/src

RUN clang++ -o Hello-World hello-world.cpp

CMD ["./Hello-World"]