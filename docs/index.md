## About System Contracts

The EOSIO blockchain platform is unique in that the features and characteristics of the blockchain built on it are flexible, that is, they can be changed, or modified completely to suit each business case requirement. Core blockchain features such as consensus, fee schedules, account creation and modification, token economics, block producer registration, voting, multi-sig, etc., are implemented inside smart contracts which are deployed on the blockchain built on the EOSIO platform.

Block.one implements and maintains EOSIO open source platform which contains, as an example, the system contracts encapsulating the base functionality for an EOSIO based blockchain. This document will detail each one of them, [eosio.bios](#eosiobios-system-contract), [eosio.system](#eosiosystem-system-contract), [eosio.msig](#eosiomsig-system-contract), [eosio.token](#eosiotoken-system-contract), [eosio.wrap](#eosiowrap-system-contract) along with a few other main concepts.

## Core Concepts

1. [System](01_core_concepts/01_system.md)
2. [RAM](01_core_concepts/02_ram.md)
3. [CPU](01_core_concepts/03_cpu.md)
4. [NET](01_core_concepts/04_net.md)
5. [Stake](01_core_concepts/05_stake.md)
6. [Vote](01_core_concepts/06_vote.md)

## System contracts defined in eosio.contracts

1. [eosio.bios](02_system_contracts/01_eosio_bios.md)
2. [eosio.system](02_system_contracts/02_eosio_system.md)
3. [eosio.msig](02_system_contracts/03_eosio_msig.md)
4. [eosio.token](02_system_contracts/04_eosio_token.md)
5. [eosio.wrap](02_system_contracts/05_eosio_wrap.md)

## Build and deploy
To build and deploy the system contract follow the instruction from [Build and deploy](03_build_and_deploy.md) section.