FROM debian:jessie
MAINTAINER Arkan M. Gerges <arkan.m.gerges@gmail.com>

ENV ZMQ_VERSION 4.2.2
ENV CMAKE_VERSION 3.9.3
ENV CMAKE_MAJOR_MINOR_VERSION 3.9

# Range of ports that are exposed
EXPOSE 5000-5500

COPY ./zmq_xpub_xsub_broker /myapp 

# Install needed packages
RUN apt-get update && apt-get install -y --fix-missing \
    curl \
    libtool \
    pkg-config \
    build-essential \
    autoconf \
    automake \
	wget \
	git
	
	# Install zeromq
RUN mkdir -p /tmp/zeromq \
    && curl -SL https://github.com/zeromq/libzmq/releases/download/v$ZMQ_VERSION/zeromq-$ZMQ_VERSION.tar.gz | tar zxC /tmp/zeromq \
    && cd /tmp/zeromq/zeromq-$ZMQ_VERSION/ \
    && ./configure --without-libsodium \
    && make \
    && make install \
    && ldconfig \
    && rm -rf /tmp/zeromq
	
	# Install cmake
RUN mkdir -p /tmp/cmake \
	&& curl -SL https://cmake.org/files/v$CMAKE_MAJOR_MINOR_VERSION/cmake-$CMAKE_VERSION.tar.gz | tar zxC /tmp/cmake \
	&& cd /tmp/cmake/cmake-$CMAKE_VERSION/ \
    && ./bootstrap \
    && make \
    && make install \
    && ldconfig \
    && rm -rf /tmp/cmake \
	&& ln -s /usr/local/bin/cmake /usr/bin/cmake
	
	# Install google/cmockery
RUN	mkdir -p /tmp/cmockery \
	&& git clone https://github.com/google/cmockery.git /tmp/cmockery \
	&& cd /tmp/cmockery \
	&& ./configure \
	&& make \
	&& make install \
	&& ldconfig \
	&& rm -fr /tmp/cmockery
	
	# Install zmq_xpub_xsub_broker
RUN cd /myapp \
	&& mkdir -p /myapp/cmake-build-release \
	&& cd /myapp/cmake-build-release \
	&& cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" /myapp \
	&& make
	
	# Cleaning
RUN apt-get clean && apt-get autoclean && apt-get -y autoremove
	
ENTRYPOINT ["/myapp/cmake-build-release/zmq_xpub_xsub_broker"]
CMD ["tcp://*:5001", "tcp://*:5002"]

