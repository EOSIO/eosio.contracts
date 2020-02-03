# Building the documentation

```
rm -rf standardese_generated
docker build -t eosio-contracts-standardese -f ./standardese.dockerfile .
docker create --name eosio-contracts-standardese-temp eosio-contracts-standardese
docker cp eosio-contracts-standardese-temp:/root/eosio-contracts/docs/standardese_generated .
docker rm eosio-contracts-standardese-temp
ls -al ./standardese_generated
```

The built documentation is at `/root/eosio-contracts/docs/standardese_generated` inside the image. This copies it to the local `standardese_generated` directory.
