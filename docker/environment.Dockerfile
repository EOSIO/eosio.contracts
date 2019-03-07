# set environment variables
RUN PATH=/usr/local/eosio/bin:$(echo "/usr/opt/eosio.cdt/$(ls /usr/opt/eosio.cdt)/bin"):$PATH
ENV EOSIO_ROOT=/usr/local/eosio
ENV LD_LIBRARY_PATH=/usr/local/lib
# add the entrypoint script
ENTRYPOINT ["/eosio.contracts/docker/buildContracts.sh"]