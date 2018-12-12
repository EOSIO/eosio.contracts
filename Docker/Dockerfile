FROM gcr.io/b1-automation-dev/eosio/builder:latest as builder

ARG eos_branch=release/1.5.x
ARG cdt_release=latest

# Make sure we have everything we need
RUN apt-get update && \
DEBIAN_FRONTEND=noninteractive apt-get -y install openssl ca-certificates build-essential libbz2-dev zlib1g-dev libssl-dev libgmp3-dev libicu-dev cmake bc jq curl wget net-tools unzip gnupg git graphviz 

RUN git clone -b $eos_branch https://github.com/EOSIO/eos.git --recursive \
&& cd eos && echo "$branch:$(git rev-parse HEAD)" > /etc/eosio-version \
&& ./eosio_build.sh && ./eosio_install.sh

# Get the CDT binaries
ADD downloadBinaries.sh /
RUN /downloadBinaries.sh $cdt_release

# Install the binaries
RUN for filename in $(ls *.deb); do /usr/bin/dpkg -i "$filename" && rm -f "$filename"; done

# Set environment variables
ENV EOSIO_ROOT=/opt/eosio
ENV LD_LIBRARY_PATH /usr/local/lib
ENV PATH /opt/eosio/bin:/opt/eosio.cdt/1.4.1/bin/:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

# Add the entrypoint script
ADD buildContracts.sh /
ENTRYPOINT ["/buildContracts.sh"]