# Building the documentation

```
rm -rf _standardese_generated
docker build -t eosio-contracts-docs -f ./build-docs.dockerfile .
docker create --name eosio-contracts-docs-temp eosio-contracts-docs
docker cp eosio-contracts-docs-temp:/root/eosio-contracts/docs/_standardese_generated .
docker rm eosio-contracts-docs-temp
ls -al ./_standardese_generated
```

The built documentation is at `/root/eosio-contracts/docs/_standardese_generated` inside the image. This copies it to the local `_standardese_generated` directory.
