FROM gcr.io/b1-automation-dev/eosio/builder:latest as builder
# install external dependencies
RUN apt-get update && \
DEBIAN_FRONTEND=noninteractive apt-get -y install openssl ca-certificates build-essential libbz2-dev zlib1g-dev libssl-dev libgmp3-dev libicu-dev cmake bc jq curl wget net-tools unzip gnupg git graphviz 
# download internal dependencies
ADD downloadDependencies.sh /
RUN /downloadDependencies.sh
# build eosio
RUN cd eos && \
./eosio_build.sh
# install eosio
RUN ./eosio_install.sh && \
cd ..
# install cdt
RUN for filename in $(ls *.deb); do /usr/bin/dpkg -i "$filename" && rm -f "$filename"; done
# set environment variables
ENV EOSIO_ROOT=/opt/eosio
ENV LD_LIBRARY_PATH /usr/local/lib
ENV PATH /opt/eosio/bin:/opt/eosio.cdt/1.4.1/bin/:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
# add the entrypoint script
ADD buildContracts.sh /
ENTRYPOINT ["/buildContracts.sh"] 