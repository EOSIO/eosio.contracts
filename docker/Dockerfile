FROM gcr.io/b1-automation-dev/eosio/builder:develop as builder
# import build-time arguments
ARG CONTRACTS_COMMIT
ARG CONTRACTS_BRANCH
# install external dependencies
RUN apt-get update && \
apt-get -y upgrade && \
DEBIAN_FRONTEND=noninteractive apt-get -y install openssl ca-certificates build-essential libbz2-dev zlib1g-dev libssl-dev libgmp3-dev libicu-dev cmake bc jq curl wget net-tools unzip gnupg git graphviz awscli
# download contracts
RUN echo "# git clone -n https://github.com/EOSIO/eosio.contracts.git --quiet" && \
git clone -n https://github.com/EOSIO/eosio.contracts.git --quiet && \
echo "# cd eosio.contracts" && \
cd eosio.contracts && \
echo "# git checkout $CONTRACTS_COMMIT --quiet" && \
git checkout $CONTRACTS_COMMIT --quiet && \
echo "# git submodule update --recursive --init --quiet" && \
git submodule update --recursive --init --quiet
# download internal dependencies
RUN /eosio.contracts/docker/downloadDependencies.sh
# build eosio
RUN cd eos && \
./eosio_build.sh
# install eosio
RUN cd eos && \
./eosio_install.sh
# install cdt
RUN for filename in $(ls *.deb); do /usr/bin/dpkg -i "$filename" && rm -f "$filename"; done
# set environment variables
RUN PATH=/usr/local/eosio/bin:$(echo "/usr/opt/eosio.cdt/$(ls /usr/opt/eosio.cdt)/bin"):$PATH
ENV EOSIO_ROOT=/usr/local/eosio
ENV LD_LIBRARY_PATH=/usr/local/lib
# add the entrypoint script
ENTRYPOINT ["/eosio.contracts/docker/buildContracts.sh"] 