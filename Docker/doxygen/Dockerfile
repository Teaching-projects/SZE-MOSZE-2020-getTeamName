FROM ubuntu:20.04

RUN apt-get update && apt-get install --no-install-recommends -y \
make \
doxygen \
graphviz \
git=v2.28.0-rc2 \
&& rm -rf /var/lib/apt/lists/*