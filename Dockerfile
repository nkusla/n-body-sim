FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive
SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get install -y \
	build-essential \
	wget \
	cmake \
	libglm-dev \
	libglfw3-dev \
	xorg

COPY . /n-body-sim

WORKDIR /n-body-sim/
RUN ./init.sh

WORKDIR /n-body-sim/build
RUN cmake .. && make
CMD ./SimulationGUI
