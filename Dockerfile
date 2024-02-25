FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
	build-essential \
	cmake \
	libglm-dev \
	libglfw3-dev \
	xorg

RUN apk update

ENV DISPLAY=:0

COPY . /n-body-sim
WORKDIR /n-body-sim

RUN mkdir -p build
WORKDIR /n-body-sim/build
RUN rm -rf * && cmake ..
