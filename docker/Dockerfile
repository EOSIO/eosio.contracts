FROM gcr.io/b1-automation-dev/eosio/builder:develop as builder
# import build-time arguments
ARG CONTRACTS_COMMIT
ARG CONTRACTS_BRANCH
# install external dependencies
RUN apt-get update && \
apt-get -y upgrade && \
DEBIAN_FRONTEND=noninteractive apt-get -y install openssl ca-certificates build-essential libbz2-dev zlib1g-dev libssl-dev libgmp3-dev libicu-dev cmake bc jq curl wget net-tools unzip gnupg git graphviz awscli
# download contracts
RUN echo "# git clone -n https://github.com/EOSIO/eosio.contracts.git" && \
git clone -n https://github.com/EOSIO/eosio.contracts.git && \
echo "# cd eosio.contracts" && \
cd eosio.contracts && \
echo "# git checkout $CONTRACTS_COMMIT" && \
git checkout $CONTRACTS_COMMIT && \
echo "# git submodule update --recursive --init --quiet" && \
git submodule update --recursive --init --quiet
# download internal dependencies
ADD downloadDependencies.sh /
RUN /downloadDependencies.sh
# build eosio
RUN cd eos && \
./eosio_build.sh
# install eosio
RUN cd eos && \
./eosio_install.sh
# install cdt
RUN for filename in $(ls *.deb); do /usr/bin/dpkg -i "$filename" && rm -f "$filename"; done
# set environment variables
ENV EOSIO_ROOT=/opt/eosio
ENV LD_LIBRARY_PATH /usr/local/lib
ENV PATH /opt/eosio/bin:/opt/eosio.cdt/1.4.1/bin/:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
RUN echo "# ls" && \
ls && \
echo "# ls /eosio.contracts" && \
ls /eosio.contracts
# add the entrypoint script
ADD buildContracts.sh /
ENTRYPOINT ["/buildContracts.sh"] 