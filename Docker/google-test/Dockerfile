FROM ubuntu:20.04

RUN apt-get update && apt-get install --no-install-recommends -y \
libgtest-dev \
cmake \
make \
g++ \
&& apt-get install -y git  \
&& rm -rf /var/lib/apt/lists/*