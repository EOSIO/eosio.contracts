# Configure and Use the `PowerUp` Resource Model

## Configuration

### Definitions

#### Configuration
```
// configure the `powerup` market. The market becomes available the first time this action is invoked
void cfgpowerup( powerup_config& args );

struct powerup_config_resource {
    std::optional<int64_t>        current_weight_ratio;   // Immediately set weight_ratio to this amount. 1x = 10^15. 0.01x = 10^13.                                                //    Do not specify to preserve the existing setting or use the default;
                                                          //    this avoids sudden price jumps. For new chains which don't need
                                                          //    to gradually phase out staking and REX, 0.01x (10^13) is a good
                                                          //    value for both current_weight_ratio and target_weight_ratio.
    std::optional<int64_t>        target_weight_ratio;    // Linearly shrink weight_ratio to this amount. 1x = 10^15. 0.01x = 10^13.
                                                          //    Do not specify to preserve the existing setting or use the default.
    std::optional<int64_t>        assumed_stake_weight;   // Assumed stake weight for ratio calculations. Use the sum of total
                                                          //    staked and total rented by REX at the time the power market
                                                          //    is first activated. Do not specify to preserve the existing
                                                          //    setting (no default exists); this avoids sudden price jumps.
                                                          //    For new chains which don't need to phase out staking and REX,
                                                          //    10^12 is probably a good value.
    std::optional<time_point_sec> target_timestamp;       // Stop automatic weight_ratio shrinkage at this time. Once this
                                                          //    time hits, weight_ratio will be target_weight_ratio. Ignored
                                                          //    if current_weight_ratio == target_weight_ratio. Do not specify
                                                          //    this to preserve the existing setting (no default exists).
    std::optional<double>         exponent;               // Exponent of resource price curve. Must be >= 1. Do not specify
                                                          //    to preserve the existing setting or use the default.
    std::optional<uint32_t>       decay_secs;             // Number of seconds for the gap between adjusted resource
                                                          //    utilization and instantaneous resource utilization to shrink
                                                          //    by 63%. Do not specify to preserve the existing setting or
                                                          //    use the default.
    std::optional<asset>          min_price;              // Fee needed to rent the entire resource market weight at the
                                                          //    minimum price. For example, this could be set to 0.005% of
                                                          //    total token supply. Do not specify to preserve the existing
                                                          //    setting or use the default.
    std::optional<asset>          max_price;              // Fee needed to rent the entire resource market weight at the
                                                          //    maximum price. For example, this could be set to 10% of total
                                                          //    token supply. Do not specify to preserve the existing
                                                          //    setting (no default exists).

   };

struct powerup_config {
    powerup_config_resource  net;             // NET market configuration
    powerup_config_resource  cpu;             // CPU market configuration
    std::optional<uint32_t> powerup_days;     // `power` `days` argument must match this. Do not specify to preserve the
                                              //    existing setting or use the default.
    std::optional<asset>    min_powerup_fee;  // Rental fees below this amount are rejected. Do not specify to preserve the
                                              //    existing setting (no default exists).
};
```
#### State

Definitions useful to help understand the configuration, including defaults:
```
inline constexpr int64_t powerup_frac = 1'000'000'000'000'000ll;  // 1.0 = 10^15

struct powerup_state_resource {
    static constexpr double   default_exponent   = 2.0;                  // Exponent of 2.0 means that the price to rent a
                                                                         //    tiny amount of resources increases linearly
                                                                         //    with utilization.
    static constexpr uint32_t default_decay_secs = 1 * seconds_per_day;  // 1 day; if 100% of bandwidth resources are in a
                                                                         //    single loan, then, assuming no further renting,
                                                                         //    1 day after it expires the adjusted utilization
                                                                         //    will be at approximately 37% and after 3 days
                                                                         //    the adjusted utilization will be less than 5%.

    uint8_t        version                 = 0;
    int64_t        weight                  = 0;                  // resource market weight. calculated; varies over time.
                                                                 //    1 represents the same amount of resources as 1
                                                                 //    satoshi of SYS staked.
    int64_t        weight_ratio            = 0;                  // resource market weight ratio:
                                                                 //    assumed_stake_weight / (assumed_stake_weight + weight).
                                                                 //    calculated; varies over time. 1x = 10^15. 0.01x = 10^13.
    int64_t        assumed_stake_weight    = 0;                  // Assumed stake weight for ratio calculations.
    int64_t        initial_weight_ratio    = powerup_frac;       // Initial weight_ratio used for linear shrinkage.
    int64_t        target_weight_ratio     = powerup_frac / 100; // Linearly shrink the weight_ratio to this amount.
    time_point_sec initial_timestamp       = {};                 // When weight_ratio shrinkage started
    time_point_sec target_timestamp        = {};                 // Stop automatic weight_ratio shrinkage at this time. Once this
                                                                 //    time hits, weight_ratio will be target_weight_ratio.
    double         exponent                = default_exponent;   // Exponent of resource price curve.
    uint32_t       decay_secs              = default_decay_secs; // Number of seconds for the gap between adjusted resource
                                                                 //    utilization and instantaneous utilization to shrink by 63%.
    asset          min_price               = {};                 // Fee needed to rent the entire resource market weight at
                                                                 //    the minimum price (defaults to 0).
    asset          max_price               = {};                 // Fee needed to rent the entire resource market weight at
                                                                 //    the maximum price.
    int64_t        utilization             = 0;                  // Instantaneous resource utilization. This is the current
                                                                 //    amount sold. utilization <= weight.
    int64_t        adjusted_utilization    = 0;                  // Adjusted resource utilization. This is >= utilization and
                                                                 //    <= weight. It grows instantly but decays exponentially.
    time_point_sec utilization_timestamp   = {};                 // When adjusted_utilization was last updated
};

struct powerup_state {
    static constexpr uint32_t default_powerup_days = 30; // 30 day resource powerups

    uint8_t                    version           = 0;
    powerup_state_resource     net               = {};                     // NET market state
    powerup_state_resource     cpu               = {};                     // CPU market state
    uint32_t                   powerup_days      = default_powerup_days;   // `powerup` `days` argument must match this.
    asset                      min_powerup_fee   = {};                     // fees below this amount are rejected

    uint64_t primary_key()const { return 0; }
};
```

### Preparation for Upgrade
1. Build [eosio.contracts](https://github.com/EOSIO/eosio.contracts) with `powerup` code. Version **1.9.2** or greater .
2. Deploy eosio.system contract to `eosio`.
3. Create account `eosio.reserv` and ensure the account has enough at least 4 KiB of RAM.
4. Deploy `powup.results.abi` to `eosio.reserv` account using `setabi`. The ABI can be found in the `build/contracts/eosio.system/.powerup/` directory.
5. Enable the REX system (if not enabled).

### Configuring `PowerUp`

#### Config file
```
# config.json
{
    "net": {
        "assumed_stake_weight": 944076307,
        "current_weight_ratio": 1000000000000000,
        "decay_secs": 86400,
        "exponent": 2,
        "max_price": "10000000.0000 TST",
        "min_price": "0.0000 TST",
        "target_timestamp": "2022-01-01T00:00:00.000",
        "target_weight_ratio": 10000000000000
    },
    "cpu": {
        "assumed_stake_weight": 3776305228,
        "current_weight_ratio": 1000000000000000,
        "decay_secs": 86400,
        "exponent": 2,
        "max_price": "10000000.0000 TST",
        "min_price": "0.0000 TST",
        "target_timestamp": "2022-01-01T00:00:00.000",
        "target_weight_ratio": 10000000000000
    },
    "min_powerup_fee": "0.0001 TST",
    "powerup_days": 1
}
```

#### `cfgpowerup` Action Call
```
# call to `cfgpowerup`
cleos push action eosio cfgpowerup "[`cat ./config.json`]" -p eosio
```

#### Check state
```
cleos get table eosio 0 powup.state
{
  "rows": [{
      "version": 0,
      "net": {
        "version": 0,
        "weight": 0,
        "weight_ratio": "1000000000000000",
        "assumed_stake_weight": 944076307,
        "initial_weight_ratio": "1000000000000000",
        "target_weight_ratio": "10000000000000",
        "initial_timestamp": "2020-11-16T19:52:50",
        "target_timestamp": "2022-01-01T00:00:00",
        "exponent": "2.00000000000000000",
        "decay_secs": 3600,
        "min_price": "0.0000 EOS",
        "max_price": "10000000.0000 EOS",
        "utilization": 0,
        "adjusted_utilization": 0,
        "utilization_timestamp": "2020-11-16T19:52:50"
      },
      "cpu": {
        "version": 0,
        "weight": 0,
        "weight_ratio": "1000000000000000",
        "assumed_stake_weight": 3776305228,
        "initial_weight_ratio": "1000000000000000",
        "target_weight_ratio": "10000000000000",
        "initial_timestamp": "2020-11-16T19:52:50",
        "target_timestamp": "2022-01-01T00:00:00",
        "exponent": "2.00000000000000000",
        "decay_secs": 3600,
        "min_price": "0.0000 EOS",
        "max_price": "10000000.0000 EOS",
        "utilization": 0,
        "adjusted_utilization": 0,
        "utilization_timestamp": "2020-11-16T19:52:50"
      },
      "powerup_days": 1,
      "min_powerup_fee": "0.0001 EOS"
    }
  ],
  "more": false,
  "next_key": ""
}
```

### Using `PowerUp`

#### Executing an order
The action to powerup an account is `powerup`. It takes a `payer` and a `receiver` of the resources. The `days` should always match `state.powerup_days`. `net_frac` and `cpu_frac` are the percentage of the resources that you need. The easiest way to caclulate the percentage is to multiple 10^15 (100%) by the desired percentage. For example: 10^15 * 1% = 10^13.
```
cleos push action eosio powerup '[user, user, 1, 10000000000000, 10000000000000, "1000.0000 EOS"]' -p user
executed transaction: 82b7124601612b371b812e3bf65cf63bb44616802d3cd33a2c0422b58399f54f  144 bytes  521 us
#         eosio <= eosio::powerup               {"payer":"user","receiver":"user","days":1,"net_frac":"10000000000000","cpu_frac":"10000000000000","...
#   eosio.token <= eosio.token::transfer        {"from":"user","to":"eosio.rex","quantity":"999.9901 EOS","memo":"transfer from user to eosio.rex"}
#  eosio.reserv <= eosio.reserv::powupresult    {"fee":"999.9901 EOS","powup_net":"1.6354 EOS","powup_cpu":"6.5416 EOS"}
#          user <= eosio.token::transfer        {"from":"user","to":"eosio.rex","quantity":"999.9901 EOS","memo":"transfer from user to eosio.rex"}
#     eosio.rex <= eosio.token::transfer        {"from":"user","to":"eosio.rex","quantity":"999.9901 EOS","memo":"transfer from user to eosio.rex"}
```
You can see how many tokens were received for `NET` and `CPU` as well as the fee by looking at the `eosio.reserv::powupresult` informational action. 

*It is worth mentioning that the network being used for the example has not fully transitioned so the available resources are minimal therefore 1% of the resources are quite expensive. As the system continues the transition more resources are available to the `PowerUp` resource model and will become more affordable.*

#### Clearing the orders queue

The orders table `powup.order` can be viewed by calling:
```
cleos get table eosio 0 powup.order
{
  "rows": [{
      "version": 0,
      "id": 0,
      "owner": "user",
      "net_weight": 16354,
      "cpu_weight": 65416,
      "expires": "2020-11-18T13:04:33"
    }
  ],
  "more": false,
  "next_key": ""
}
```

The action `powerupexec` that takes a `name` of a user and the `max` number of orders that will be cleared if expired. It is worth noting that the call to `powerup` will also clear up to two expired orders per call.

```
cleos push action eosio powerupexec '[user, 2]' -p user
executed transaction: 93ab4ac900a7902e4e59e5e925e8b54622715328965150db10774aa09855dc98  104 bytes  363 us
#         eosio <= eosio::powerupexec           {"user":"user","max":2}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```