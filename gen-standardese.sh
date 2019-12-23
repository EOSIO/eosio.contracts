rm -rf standardese_generated
docker build -t eosio-contracts-standardese -f ./standardese.dockerfile .
docker create --name eosio-contracts-standardese-temp eosio-contracts-standardese
docker cp eosio-contracts-standardese-temp:/root/eosio-contracts/docs/standardese_generated .
docker rm eosio-contracts-standardese-temp
ls -al ./standardese_generated

