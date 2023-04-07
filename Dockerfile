FROM ubuntu:20.04

#--------------------------------------------------------------------------
# Install OpenCV & CMake
# SOURCE: https://docs.opencv.org/4.5.4/d7/d9f/tutorial_linux_install.html
#--------------------------------------------------------------------------

RUN apt update 

RUN apt install -y cmake wget unzip g++

#--------------------------------------------------------------------------
# Install 0MQ
#--------------------------------------------------------------------------

# Installs boost and zmq core library
RUN apt update 

RUN apt install -y git libboost-all-dev libzmq3-dev

WORKDIR /usr/src

# Installing zmq cpp library
RUN git clone https://github.com/zeromq/zmqpp

WORKDIR /usr/src/zmqpp

RUN make

RUN make install

RUN ldconfig

#--------------------------------------------------------------------------
# Compile
#--------------------------------------------------------------------------

COPY . /usr/src/dummy

WORKDIR /usr/src/dummy

RUN export CC=/usr/local/bin/gcc
RUN export CXX=/usr/local/bin/g++

RUN cmake .

RUN make

#--------------------------------------------------------------------------
# Run
#--------------------------------------------------------------------------

CMD ["./dummy"]