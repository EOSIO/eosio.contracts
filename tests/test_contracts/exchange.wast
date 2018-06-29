(module
 (type $FUNCSIG$vijiiii (func (param i32 i64 i32 i32 i32 i32)))
 (type $FUNCSIG$viji (func (param i32 i64 i32)))
 (type $FUNCSIG$vijji (func (param i32 i64 i64 i32)))
 (type $FUNCSIG$vijjdi (func (param i32 i64 i64 f64 i32)))
 (type $FUNCSIG$v (func))
 (type $FUNCSIG$j (func (result i64)))
 (type $FUNCSIG$vjj (func (param i64 i64)))
 (type $FUNCSIG$vii (func (param i32 i32)))
 (type $FUNCSIG$ijjjj (func (param i64 i64 i64 i64) (result i32)))
 (type $FUNCSIG$iiii (func (param i32 i32 i32) (result i32)))
 (type $FUNCSIG$vijii (func (param i32 i64 i32 i32)))
 (type $FUNCSIG$ijjjjii (func (param i64 i64 i64 i64 i32 i32) (result i32)))
 (type $FUNCSIG$vi (func (param i32)))
 (type $FUNCSIG$ijjjij (func (param i64 i64 i64 i32 i64) (result i32)))
 (type $FUNCSIG$iii (func (param i32 i32) (result i32)))
 (type $FUNCSIG$ijjjii (func (param i64 i64 i64 i32 i32) (result i32)))
 (type $FUNCSIG$vj (func (param i64)))
 (type $FUNCSIG$vd (func (param f64)))
 (type $FUNCSIG$ijjjji (func (param i64 i64 i64 i64 i32) (result i32)))
 (type $FUNCSIG$ij (func (param i64) (result i32)))
 (type $FUNCSIG$i (func (result i32)))
 (import "env" "abort" (func $abort))
 (import "env" "action_data_size" (func $action_data_size (result i32)))
 (import "env" "current_receiver" (func $current_receiver (result i64)))
 (import "env" "current_time" (func $current_time (result i64)))
 (import "env" "db_find_i64" (func $db_find_i64 (param i64 i64 i64 i64) (result i32)))
 (import "env" "db_get_i64" (func $db_get_i64 (param i32 i32 i32) (result i32)))
 (import "env" "db_idx64_find_primary" (func $db_idx64_find_primary (param i64 i64 i64 i32 i64) (result i32)))
 (import "env" "db_idx64_lowerbound" (func $db_idx64_lowerbound (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx64_next" (func $db_idx64_next (param i32 i32) (result i32)))
 (import "env" "db_idx64_remove" (func $db_idx64_remove (param i32)))
 (import "env" "db_idx64_store" (func $db_idx64_store (param i64 i64 i64 i64 i32) (result i32)))
 (import "env" "db_idx64_update" (func $db_idx64_update (param i32 i64 i32)))
 (import "env" "db_lowerbound_i64" (func $db_lowerbound_i64 (param i64 i64 i64 i64) (result i32)))
 (import "env" "db_next_i64" (func $db_next_i64 (param i32 i32) (result i32)))
 (import "env" "db_remove_i64" (func $db_remove_i64 (param i32)))
 (import "env" "db_store_i64" (func $db_store_i64 (param i64 i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_update_i64" (func $db_update_i64 (param i32 i64 i32 i32)))
 (import "env" "eosio_assert" (func $eosio_assert (param i32 i32)))
 (import "env" "eosio_exit" (func $eosio_exit (param i32)))
 (import "env" "has_auth" (func $has_auth (param i64) (result i32)))
 (import "env" "memcpy" (func $memcpy (param i32 i32 i32) (result i32)))
 (import "env" "printdf" (func $printdf (param f64)))
 (import "env" "printi" (func $printi (param i64)))
 (import "env" "printn" (func $printn (param i64)))
 (import "env" "prints" (func $prints (param i32)))
 (import "env" "prints_l" (func $prints_l (param i32 i32)))
 (import "env" "printui" (func $printui (param i64)))
 (import "env" "read_action_data" (func $read_action_data (param i32 i32) (result i32)))
 (import "env" "require_auth" (func $require_auth (param i64)))
 (import "env" "require_auth2" (func $require_auth2 (param i64 i64)))
 (import "env" "require_recipient" (func $require_recipient (param i64)))
 (import "env" "send_inline" (func $send_inline (param i32 i32)))
 (table 6 6 anyfunc)
 (elem (i32.const 0) $__wasm_nullptr $_ZN5eosio8exchange7createxEyNS_5assetEmNS_14extended_assetES2_ $_ZN5eosio8exchange4lendEyNS_11symbol_typeENS_14extended_assetE $_ZN5eosio8exchange8withdrawEyNS_14extended_assetE $_ZN5eosio8exchange6unlendEyNS_11symbol_typeEdNS_15extended_symbolE $_ZN5eosio8exchange7depositEyNS_14extended_assetE)
 (memory $0 1)
 (data (i32.const 4) "\b0W\00\00")
 (data (i32.const 16) "magnitude of asset amount must be less than 2^62\00")
 (data (i32.const 80) "invalid symbol name\00")
 (data (i32.const 112) "unexpected asset contract input\00")
 (data (i32.const 144) "unexpected asset symbol input\00")
 (data (i32.const 176) "invalid sell\00")
 (data (i32.const 192) "invalid conversion\00")
 (data (i32.const 224) "object passed to iterator_to is not in multi_index\00")
 (data (i32.const 288) "cannot create objects in table of another contract\00")
 (data (i32.const 352) "cannot pass end iterator to modify\00")
 (data (i32.const 400) "object passed to modify is not in multi_index\00")
 (data (i32.const 448) "cannot modify objects in table of another contract\00")
 (data (i32.const 512) "overdrawn balance 2\00")
 (data (i32.const 544) "updater cannot change primary key when modifying an object\00")
 (data (i32.const 608) "write\00")
 (data (i32.const 624) "overdrawn balance 1\00")
 (data (i32.const 656) "error reading iterator\00")
 (data (i32.const 688) "read\00")
 (data (i32.const 704) "get\00")
 (data (i32.const 720) "unknown market\00")
 (data (i32.const 736) "programmer error: insufficient collateral to cover\00")
 (data (i32.const 800) "type mismatch\00")
 (data (i32.const 816) "attempt to subtract asset with different symbol\00")
 (data (i32.const 864) "subtraction underflow\00")
 (data (i32.const 896) "subtraction overflow\00")
 (data (i32.const 928) "cannot pass end iterator to erase\00")
 (data (i32.const 976) "object passed to erase is not in multi_index\00")
 (data (i32.const 1024) "cannot erase objects in table of another contract\00")
 (data (i32.const 1088) "attempt to remove object that was not in multi_index\00")
 (data (i32.const 1152) "cannot increment end iterator\00")
 (data (i32.const 1184) "unable to lend to this market\00")
 (data (i32.const 1216) "underflow\00")
 (data (i32.const 1232) "cannot unlend negative balance\00")
 (data (i32.const 1264) "sym: \00")
 (data (i32.const 1280) "@\00")
 (data (i32.const 1296) "unlend: \00")
 (data (i32.const 1312) " existing interest_shares:  \00")
 (data (i32.const 1344) "\n\00")
 (data (i32.const 1360) ",\00")
 (data (i32.const 1376) "invalid debt asset\00")
 (data (i32.const 1408) "no known margin position\00")
 (data (i32.const 1440) "attempt to cover more than user has\00")
 (data (i32.const 1488) "unable to cover debt\00")
 (data (i32.const 1520) "cannot borrow neg\00")
 (data (i32.const 1552) "cannot have neg collat\00")
 (data (i32.const 1584) "user failed to claim all collateral\00")
 (data (i32.const 1632) "attempt to add asset with different symbol\00")
 (data (i32.const 1680) "addition underflow\00")
 (data (i32.const 1712) "addition overflow\00")
 (data (i32.const 1744) "insufficient funds availalbe to borrow\00")
 (data (i32.const 1792) "this update would trigger a margin call\00")
 (data (i32.const 1840) "invalid quantity\00")
 (data (i32.const 1872) "deposit\00")
 (data (i32.const 1888) "active\00")
 (data (i32.const 1904) "transfer\00")
 (data (i32.const 1920) "cannot withdraw negative balance\00")
 (data (i32.const 1968) "withdraw\00")
 (data (i32.const 1984) "invalid sell amount\00")
 (data (i32.const 2016) "sell amount must be positive\00")
 (data (i32.const 2048) "invalid min receive amount\00")
 (data (i32.const 2080) "min receive amount cannot be negative\00")
 (data (i32.const 2128) "   \00")
 (data (i32.const 2144) "  =>  \00")
 (data (i32.const 2160) "unable to fill\00")
 (data (i32.const 2176) "sold\00")
 (data (i32.const 2192) "received\00")
 (data (i32.const 2224) "unable to find key\00")
 (data (i32.const 2256) "can only transfer to white listed accounts\00")
 (data (i32.const 2304) "receiver requires whitelist by issuer\00")
 (data (i32.const 2352) ".\00")
 (data (i32.const 2368) " \00")
 (data (i32.const 2384) "invalid borrow delta\00")
 (data (i32.const 2416) "invalid collateral delta\00")
 (data (i32.const 2448) "no effect\00")
 (data (i32.const 2464) "invalid args\00")
 (data (i32.const 2480) "invalid asset for market\00")
 (data (i32.const 2512) "borrowed\00")
 (data (i32.const 2528) "collateral\00")
 (data (i32.const 2544) "invalid cover amount\00")
 (data (i32.const 2576) "cover amount must be positive\00")
 (data (i32.const 2608) "invalid initial supply\00")
 (data (i32.const 2640) "initial supply must be positive\00")
 (data (i32.const 2672) "invalid base deposit\00")
 (data (i32.const 2704) "base deposit must be positive\00")
 (data (i32.const 2736) "invalid quote deposit\00")
 (data (i32.const 2768) "quote deposit must be positive\00")
 (data (i32.const 2800) "must exchange between two different currencies\00")
 (data (i32.const 2848) "base: \00")
 (data (i32.const 2864) "quote: \00")
 (data (i32.const 2880) "marketid: \00")
 (data (i32.const 2896) " \n \00")
 (data (i32.const 2912) "market already exists\00")
 (data (i32.const 2944) "initial exchange tokens\00")
 (data (i32.const 2976) "new exchange issue\00")
 (data (i32.const 3008) "new exchange deposit\00")
 (data (i32.const 3040) "token with symbol already exists\00")
 (data (i32.const 3088) "must lend a positive amount\00")
 (data (i32.const 3120) "must unlend a positive amount\00")
 (data (i32.const 3152) "invalid quantity in transfer\00")
 (data (i32.const 3184) "zero quantity is disallowed in transfer\00")
 (data (i32.const 3232) "withdrew tokens without withdraw in memo\00")
 (data (i32.const 3280) "received tokens without deposit in memo\00")
 (data (i32.const 3328) "must transfer positive quantity\00")
 (data (i32.const 3360) "overdrawn balance\00")
 (data (i32.const 3392) "account is frozen by issuer\00")
 (data (i32.const 3424) "all transfers are frozen by issuer\00")
 (data (i32.const 3472) "account is not white listed\00")
 (data (i32.const 3504) "issuer may not recall token\00")
 (data (i32.const 3536) "insufficient authority\00")
 (data (i32.const 3568) "issue\n\00")
 (data (i32.const 3584) "transfer\n\00")
 (data (i32.const 3600) "create\n\00")
 (data (i32.const 3616) "must issue positive quantity\00")
 (data (i32.const 3664) "\00\00\00\00\00\00\f0?\00\00\00\00\00\00\f8?")
 (data (i32.const 3680) "\00\00\00\00\00\00\00\00\06\d0\cfC\eb\fdL>")
 (data (i32.const 3696) "\00\00\00\00\00\00\00\00\00\00\00@\03\b8\e2?")
 (data (i32.const 12112) "malloc_from_freed was designed to only be called after _heap was completely allocated\00")
 (export "memory" (memory $0))
 (export "_ZeqRK11checksum256S1_" (func $_ZeqRK11checksum256S1_))
 (export "_ZeqRK11checksum160S1_" (func $_ZeqRK11checksum160S1_))
 (export "_ZneRK11checksum160S1_" (func $_ZneRK11checksum160S1_))
 (export "now" (func $now))
 (export "_ZN5eosio12require_authERKNS_16permission_levelE" (func $_ZN5eosio12require_authERKNS_16permission_levelE))
 (export "_ZN5eosio14exchange_state19convert_to_exchangeERNS0_9connectorENS_14extended_assetE" (func $_ZN5eosio14exchange_state19convert_to_exchangeERNS0_9connectorENS_14extended_assetE))
 (export "_ZN5eosio14exchange_state21convert_from_exchangeERNS0_9connectorENS_14extended_assetE" (func $_ZN5eosio14exchange_state21convert_from_exchangeERNS0_9connectorENS_14extended_assetE))
 (export "_ZN5eosio14exchange_state7convertENS_14extended_assetENS_15extended_symbolE" (func $_ZN5eosio14exchange_state7convertENS_14extended_assetENS_15extended_symbolE))
 (export "_ZNK5eosio14exchange_state20requires_margin_callERKNS0_9connectorE" (func $_ZNK5eosio14exchange_state20requires_margin_callERKNS0_9connectorE))
 (export "_ZNK5eosio14exchange_state20requires_margin_callEv" (func $_ZNK5eosio14exchange_state20requires_margin_callEv))
 (export "_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE" (func $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE))
 (export "_ZN5eosio12market_stateC2EyNS_11symbol_typeERNS_17exchange_accountsE" (func $_ZN5eosio12market_stateC2EyNS_11symbol_typeERNS_17exchange_accountsE))
 (export "_ZN5eosio12market_state11margin_callENS_15extended_symbolE" (func $_ZN5eosio12market_state11margin_callENS_15extended_symbolE))
 (export "_ZN5eosio12market_state11margin_callERNS_14exchange_state9connectorERNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS5_yXadL_ZNKS5_8get_callEvEEEEEEEEE" (func $_ZN5eosio12market_state11margin_callERNS_14exchange_state9connectorERNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS5_yXadL_ZNKS5_8get_callEvEEEEEEEEE))
 (export "_ZNK5eosio12market_state13initial_stateEv" (func $_ZNK5eosio12market_state13initial_stateEv))
 (export "_ZN5eosio12market_state4lendEyRKNS_14extended_assetE" (func $_ZN5eosio12market_state4lendEyRKNS_14extended_assetE))
 (export "_ZN5eosio12market_state18adjust_lend_sharesEyRNS_11multi_indexILy10163845904742744064ENS_13loan_positionEJEEEd" (func $_ZN5eosio12market_state18adjust_lend_sharesEyRNS_11multi_indexILy10163845904742744064ENS_13loan_positionEJEEEd))
 (export "_ZN5eosio12market_state6unlendEydRKNS_15extended_symbolE" (func $_ZN5eosio12market_state6unlendEydRKNS_15extended_symbolE))
 (export "_ZN5eosio12market_state12cover_marginEyRKNS_14extended_assetE" (func $_ZN5eosio12market_state12cover_marginEyRKNS_14extended_assetE))
 (export "_ZN5eosio12market_state12cover_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetE" (func $_ZN5eosio12market_state12cover_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetE))
 (export "_ZN5eosio12market_state13update_marginEyRKNS_14extended_assetES3_" (func $_ZN5eosio12market_state13update_marginEyRKNS_14extended_assetES3_))
 (export "_ZN5eosio12market_state13adjust_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetESG_" (func $_ZN5eosio12market_state13adjust_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetESG_))
 (export "_ZN5eosio12market_state4saveEv" (func $_ZN5eosio12market_state4saveEv))
 (export "_ZN5eosio8exchange7depositEyNS_14extended_assetE" (func $_ZN5eosio8exchange7depositEyNS_14extended_assetE))
 (export "_ZN5eosio8exchange8withdrawEyNS_14extended_assetE" (func $_ZN5eosio8exchange8withdrawEyNS_14extended_assetE))
 (export "_ZN5eosio8exchange2onERKNS0_5tradeE" (func $_ZN5eosio8exchange2onERKNS0_5tradeE))
 (export "_ZN5eosio8exchange2onERKNS0_8upmarginE" (func $_ZN5eosio8exchange2onERKNS0_8upmarginE))
 (export "_ZN5eosio8exchange2onERKNS0_11covermarginE" (func $_ZN5eosio8exchange2onERKNS0_11covermarginE))
 (export "_ZN5eosio8exchange7createxEyNS_5assetEmNS_14extended_assetES2_" (func $_ZN5eosio8exchange7createxEyNS_5assetEmNS_14extended_assetES2_))
 (export "_ZN5eosio8exchange4lendEyNS_11symbol_typeENS_14extended_assetE" (func $_ZN5eosio8exchange4lendEyNS_11symbol_typeENS_14extended_assetE))
 (export "_ZN5eosio8exchange6unlendEyNS_11symbol_typeEdNS_15extended_symbolE" (func $_ZN5eosio8exchange6unlendEyNS_11symbol_typeEdNS_15extended_symbolE))
 (export "_ZN5eosio8exchange2onERKNS_8currency8transferEy" (func $_ZN5eosio8exchange2onERKNS_8currency8transferEy))
 (export "_ZN5eosio8exchange5applyEyy" (func $_ZN5eosio8exchange5applyEyy))
 (export "apply" (func $apply))
 (export "pow" (func $pow))
 (export "sqrt" (func $sqrt))
 (export "fabs" (func $fabs))
 (export "scalbn" (func $scalbn))
 (export "memcmp" (func $memcmp))
 (export "strlen" (func $strlen))
 (export "malloc" (func $malloc))
 (export "free" (func $free))
 (func $_ZeqRK11checksum256S1_ (param $0 i32) (param $1 i32) (result i32)
  (i32.eqz
   (call $memcmp
    (get_local $0)
    (get_local $1)
    (i32.const 32)
   )
  )
 )
 (func $_ZeqRK11checksum160S1_ (param $0 i32) (param $1 i32) (result i32)
  (i32.eqz
   (call $memcmp
    (get_local $0)
    (get_local $1)
    (i32.const 32)
   )
  )
 )
 (func $_ZneRK11checksum160S1_ (param $0 i32) (param $1 i32) (result i32)
  (i32.ne
   (call $memcmp
    (get_local $0)
    (get_local $1)
    (i32.const 32)
   )
   (i32.const 0)
  )
 )
 (func $now (result i32)
  (i32.wrap/i64
   (i64.div_u
    (call $current_time)
    (i64.const 1000000)
   )
  )
 )
 (func $_ZN5eosio12require_authERKNS_16permission_levelE (param $0 i32)
  (call $require_auth2
   (i64.load
    (get_local $0)
   )
   (i64.load offset=8
    (get_local $0)
   )
  )
 )
 (func $_ZN5eosio14exchange_state19convert_to_exchangeERNS0_9connectorENS_14extended_assetE (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i64)
  (local $5 i64)
  (local $6 i64)
  (i64.store offset=8
   (get_local $1)
   (i64.add
    (tee_local $5
     (i64.trunc_s/f64
      (f64.neg
       (f64.mul
        (f64.convert_s/i64
         (i64.load offset=8
          (get_local $1)
         )
        )
        (f64.sub
         (f64.const 1)
         (call $pow
          (f64.add
           (f64.div
            (f64.convert_s/i64
             (tee_local $6
              (i64.load
               (get_local $3)
              )
             )
            )
            (f64.convert_s/i64
             (i64.add
              (get_local $6)
              (i64.load
               (get_local $2)
              )
             )
            )
           )
           (f64.const 1)
          )
          (f64.div
           (f64.convert_u/i32
            (i32.load offset=24
             (get_local $2)
            )
           )
           (f64.const 1e3)
          )
         )
        )
       )
      )
     )
    )
    (i64.load offset=8
     (get_local $1)
    )
   )
  )
  (i64.store
   (get_local $2)
   (i64.add
    (get_local $6)
    (i64.load
     (get_local $2)
    )
   )
  )
  (set_local $4
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
   )
  )
  (set_local $6
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
   )
  )
  (i64.store
   (get_local $0)
   (get_local $5)
  )
  (i64.store offset=8
   (get_local $0)
   (get_local $6)
  )
  (call $eosio_assert
   (i64.lt_u
    (i64.add
     (get_local $5)
     (i64.const 4611686018427387903)
    )
    (i64.const 9223372036854775807)
   )
   (i32.const 16)
  )
  (set_local $6
   (i64.shr_u
    (get_local $6)
    (i64.const 8)
   )
  )
  (set_local $1
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $6)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $6
          (i64.shr_u
           (get_local $6)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $6
           (i64.shr_u
            (get_local $6)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $1
          (i32.add
           (get_local $1)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $2
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $1
        (i32.add
         (get_local $1)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $2
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $2)
   (i32.const 80)
  )
  (i64.store offset=16
   (get_local $0)
   (get_local $4)
  )
 )
 (func $_ZN5eosio14exchange_state21convert_from_exchangeERNS0_9connectorENS_14extended_assetE (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i64)
  (local $5 f64)
  (local $6 i64)
  (local $7 i64)
  (call $eosio_assert
   (i64.eq
    (i64.load offset=16
     (get_local $3)
    )
    (i64.load
     (i32.add
      (get_local $1)
      (i32.const 24)
     )
    )
   )
   (i32.const 112)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load offset=8
     (get_local $3)
    )
    (i64.load
     (i32.add
      (get_local $1)
      (i32.const 16)
     )
    )
   )
   (i32.const 144)
  )
  (set_local $6
   (i64.load
    (get_local $2)
   )
  )
  (set_local $5
   (call $pow
    (f64.add
     (f64.div
      (f64.convert_s/i64
       (tee_local $7
        (i64.load
         (get_local $3)
        )
       )
      )
      (f64.convert_s/i64
       (i64.sub
        (i64.load offset=8
         (get_local $1)
        )
        (get_local $7)
       )
      )
     )
     (f64.const 1)
    )
    (f64.div
     (f64.const 1e3)
     (f64.convert_u/i32
      (i32.load offset=24
       (get_local $2)
      )
     )
    )
   )
  )
  (i64.store offset=8
   (get_local $1)
   (i64.sub
    (i64.load offset=8
     (get_local $1)
    )
    (get_local $7)
   )
  )
  (i64.store
   (get_local $2)
   (i64.sub
    (i64.load
     (get_local $2)
    )
    (tee_local $7
     (i64.trunc_s/f64
      (f64.mul
       (f64.convert_s/i64
        (get_local $6)
       )
       (f64.add
        (get_local $5)
        (f64.const -1)
       )
      )
     )
    )
   )
  )
  (set_local $4
   (i64.load offset=16
    (get_local $2)
   )
  )
  (set_local $6
   (i64.load offset=8
    (get_local $2)
   )
  )
  (i64.store
   (get_local $0)
   (get_local $7)
  )
  (i64.store offset=8
   (get_local $0)
   (get_local $6)
  )
  (call $eosio_assert
   (i64.lt_u
    (i64.add
     (get_local $7)
     (i64.const 4611686018427387903)
    )
    (i64.const 9223372036854775807)
   )
   (i32.const 16)
  )
  (set_local $7
   (i64.shr_u
    (get_local $6)
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $7)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $7
          (i64.shr_u
           (get_local $7)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $7
           (i64.shr_u
            (get_local $7)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $1
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $1
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $1)
   (i32.const 80)
  )
  (i64.store offset=16
   (get_local $0)
   (get_local $4)
  )
 )
 (func $_ZN5eosio14exchange_state7convertENS_14extended_assetENS_15extended_symbolE (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i64)
  (local $5 i64)
  (local $6 i64)
  (local $7 i64)
  (local $8 i64)
  (local $9 f64)
  (local $10 i32)
  (local $11 i32)
  (local $12 i64)
  (local $13 i32)
  (local $14 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $14
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 208)
    )
   )
  )
  (set_local $8
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 152)
    )
   )
  )
  (set_local $7
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 144)
    )
   )
  )
  (set_local $6
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 56)
    )
   )
  )
  (set_local $5
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 48)
    )
   )
  )
  (set_local $12
   (i64.load offset=16
    (get_local $2)
   )
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (block $label$6
         (block $label$7
          (block $label$8
           (br_if $label$8
            (i64.ne
             (tee_local $4
              (i64.load offset=8
               (get_local $2)
              )
             )
             (i64.load
              (i32.add
               (get_local $1)
               (i32.const 16)
              )
             )
            )
           )
           (br_if $label$8
            (i64.ne
             (get_local $12)
             (i64.load
              (i32.add
               (get_local $1)
               (i32.const 24)
              )
             )
            )
           )
           (br_if $label$7
            (i64.ne
             (tee_local $12
              (i64.load
               (get_local $3)
              )
             )
             (get_local $5)
            )
           )
           (br_if $label$7
            (i64.ne
             (i64.load offset=8
              (get_local $3)
             )
             (get_local $6)
            )
           )
           (i64.store
            (i32.add
             (i32.add
              (get_local $14)
              (i32.const 160)
             )
             (i32.const 16)
            )
            (tee_local $5
             (i64.load
              (tee_local $13
               (i32.add
                (get_local $2)
                (i32.const 16)
               )
              )
             )
            )
           )
           (i64.store
            (i32.add
             (i32.add
              (get_local $14)
              (i32.const 160)
             )
             (i32.const 8)
            )
            (tee_local $4
             (i64.load
              (tee_local $10
               (i32.add
                (get_local $2)
                (i32.const 8)
               )
              )
             )
            )
           )
           (set_local $12
            (i64.load
             (get_local $2)
            )
           )
           (i64.store
            (i32.add
             (i32.add
              (get_local $14)
              (i32.const 48)
             )
             (i32.const 16)
            )
            (get_local $5)
           )
           (i64.store
            (i32.add
             (i32.add
              (get_local $14)
              (i32.const 48)
             )
             (i32.const 8)
            )
            (get_local $4)
           )
           (i64.store offset=160
            (get_local $14)
            (get_local $12)
           )
           (i64.store offset=48
            (get_local $14)
            (get_local $12)
           )
           (call $_ZN5eosio14exchange_state21convert_from_exchangeERNS0_9connectorENS_14extended_assetE
            (i32.add
             (get_local $14)
             (i32.const 184)
            )
            (get_local $1)
            (i32.add
             (get_local $1)
             (i32.const 40)
            )
            (i32.add
             (get_local $14)
             (i32.const 48)
            )
           )
           (i64.store
            (get_local $13)
            (i64.load
             (i32.add
              (i32.add
               (get_local $14)
               (i32.const 184)
              )
              (i32.const 16)
             )
            )
           )
           (i64.store
            (get_local $10)
            (i64.load
             (i32.add
              (i32.add
               (get_local $14)
               (i32.const 184)
              )
              (i32.const 8)
             )
            )
           )
           (i64.store
            (get_local $2)
            (i64.load offset=184
             (get_local $14)
            )
           )
           (br $label$0)
          )
          (br_if $label$6
           (i64.ne
            (get_local $4)
            (get_local $5)
           )
          )
          (br_if $label$6
           (i64.ne
            (get_local $12)
            (get_local $6)
           )
          )
          (set_local $5
           (i64.load offset=8
            (get_local $1)
           )
          )
          (set_local $9
           (call $pow
            (f64.add
             (f64.div
              (f64.convert_s/i64
               (tee_local $12
                (i64.load
                 (get_local $2)
                )
               )
              )
              (f64.convert_s/i64
               (i64.add
                (i64.load
                 (tee_local $13
                  (i32.add
                   (get_local $1)
                   (i32.const 40)
                  )
                 )
                )
                (get_local $12)
               )
              )
             )
             (f64.const 1)
            )
            (f64.div
             (f64.convert_u/i32
              (i32.load
               (i32.add
                (get_local $1)
                (i32.const 64)
               )
              )
             )
             (f64.const 1e3)
            )
           )
          )
          (i64.store
           (get_local $13)
           (i64.add
            (get_local $12)
            (i64.load
             (get_local $13)
            )
           )
          )
          (i64.store offset=8
           (get_local $1)
           (i64.add
            (tee_local $5
             (i64.trunc_s/f64
              (f64.neg
               (f64.mul
                (f64.convert_s/i64
                 (get_local $5)
                )
                (f64.sub
                 (f64.const 1)
                 (get_local $9)
                )
               )
              )
             )
            )
            (i64.load offset=8
             (get_local $1)
            )
           )
          )
          (set_local $6
           (i64.load
            (i32.add
             (get_local $1)
             (i32.const 24)
            )
           )
          )
          (set_local $4
           (i64.load
            (i32.add
             (get_local $1)
             (i32.const 16)
            )
           )
          )
          (call $eosio_assert
           (i64.lt_u
            (i64.add
             (get_local $5)
             (i64.const 4611686018427387903)
            )
            (i64.const 9223372036854775807)
           )
           (i32.const 16)
          )
          (set_local $12
           (i64.shr_u
            (get_local $4)
            (i64.const 8)
           )
          )
          (set_local $13
           (i32.const 0)
          )
          (loop $label$9
           (br_if $label$5
            (i32.gt_u
             (i32.add
              (i32.shl
               (i32.wrap/i64
                (get_local $12)
               )
               (i32.const 24)
              )
              (i32.const -1073741825)
             )
             (i32.const 452984830)
            )
           )
           (block $label$10
            (br_if $label$10
             (i64.ne
              (i64.and
               (tee_local $12
                (i64.shr_u
                 (get_local $12)
                 (i64.const 8)
                )
               )
               (i64.const 255)
              )
              (i64.const 0)
             )
            )
            (loop $label$11
             (br_if $label$5
              (i64.ne
               (i64.and
                (tee_local $12
                 (i64.shr_u
                  (get_local $12)
                  (i64.const 8)
                 )
                )
                (i64.const 255)
               )
               (i64.const 0)
              )
             )
             (br_if $label$11
              (i32.lt_s
               (tee_local $13
                (i32.add
                 (get_local $13)
                 (i32.const 1)
                )
               )
               (i32.const 7)
              )
             )
            )
           )
           (set_local $10
            (i32.const 1)
           )
           (br_if $label$9
            (i32.lt_s
             (tee_local $13
              (i32.add
               (get_local $13)
               (i32.const 1)
              )
             )
             (i32.const 7)
            )
           )
           (br $label$4)
          )
         )
         (block $label$12
          (br_if $label$12
           (i64.ne
            (get_local $12)
            (get_local $7)
           )
          )
          (br_if $label$12
           (i64.ne
            (i64.load offset=8
             (get_local $3)
            )
            (get_local $8)
           )
          )
          (i64.store
           (i32.add
            (i32.add
             (get_local $14)
             (i32.const 136)
            )
            (i32.const 16)
           )
           (tee_local $5
            (i64.load
             (tee_local $13
              (i32.add
               (get_local $2)
               (i32.const 16)
              )
             )
            )
           )
          )
          (i64.store
           (i32.add
            (i32.add
             (get_local $14)
             (i32.const 136)
            )
            (i32.const 8)
           )
           (tee_local $4
            (i64.load
             (tee_local $10
              (i32.add
               (get_local $2)
               (i32.const 8)
              )
             )
            )
           )
          )
          (set_local $12
           (i64.load
            (get_local $2)
           )
          )
          (i64.store
           (i32.add
            (i32.add
             (get_local $14)
             (i32.const 72)
            )
            (i32.const 16)
           )
           (get_local $5)
          )
          (i64.store
           (i32.add
            (i32.add
             (get_local $14)
             (i32.const 72)
            )
            (i32.const 8)
           )
           (get_local $4)
          )
          (i64.store offset=136
           (get_local $14)
           (get_local $12)
          )
          (i64.store offset=72
           (get_local $14)
           (get_local $12)
          )
          (call $_ZN5eosio14exchange_state21convert_from_exchangeERNS0_9connectorENS_14extended_assetE
           (i32.add
            (get_local $14)
            (i32.const 184)
           )
           (get_local $1)
           (i32.add
            (get_local $1)
            (i32.const 136)
           )
           (i32.add
            (get_local $14)
            (i32.const 72)
           )
          )
          (i64.store
           (get_local $13)
           (i64.load
            (i32.add
             (i32.add
              (get_local $14)
              (i32.const 184)
             )
             (i32.const 16)
            )
           )
          )
          (i64.store
           (get_local $10)
           (i64.load
            (i32.add
             (i32.add
              (get_local $14)
              (i32.const 184)
             )
             (i32.const 8)
            )
           )
          )
          (i64.store
           (get_local $2)
           (i64.load offset=184
            (get_local $14)
           )
          )
          (br $label$0)
         )
         (call $eosio_assert
          (i32.const 0)
          (i32.const 192)
         )
         (br $label$0)
        )
        (br_if $label$3
         (i64.ne
          (get_local $4)
          (get_local $7)
         )
        )
        (br_if $label$3
         (i64.ne
          (get_local $12)
          (get_local $8)
         )
        )
        (set_local $5
         (i64.load offset=8
          (get_local $1)
         )
        )
        (set_local $9
         (call $pow
          (f64.add
           (f64.div
            (f64.convert_s/i64
             (tee_local $12
              (i64.load
               (get_local $2)
              )
             )
            )
            (f64.convert_s/i64
             (i64.add
              (i64.load
               (tee_local $13
                (i32.add
                 (get_local $1)
                 (i32.const 136)
                )
               )
              )
              (get_local $12)
             )
            )
           )
           (f64.const 1)
          )
          (f64.div
           (f64.convert_u/i32
            (i32.load
             (i32.add
              (get_local $1)
              (i32.const 160)
             )
            )
           )
           (f64.const 1e3)
          )
         )
        )
        (i64.store
         (get_local $13)
         (i64.add
          (get_local $12)
          (i64.load
           (get_local $13)
          )
         )
        )
        (i64.store offset=8
         (get_local $1)
         (i64.add
          (tee_local $5
           (i64.trunc_s/f64
            (f64.neg
             (f64.mul
              (f64.convert_s/i64
               (get_local $5)
              )
              (f64.sub
               (f64.const 1)
               (get_local $9)
              )
             )
            )
           )
          )
          (i64.load offset=8
           (get_local $1)
          )
         )
        )
        (set_local $6
         (i64.load
          (i32.add
           (get_local $1)
           (i32.const 24)
          )
         )
        )
        (set_local $4
         (i64.load
          (i32.add
           (get_local $1)
           (i32.const 16)
          )
         )
        )
        (call $eosio_assert
         (i64.lt_u
          (i64.add
           (get_local $5)
           (i64.const 4611686018427387903)
          )
          (i64.const 9223372036854775807)
         )
         (i32.const 16)
        )
        (set_local $12
         (i64.shr_u
          (get_local $4)
          (i64.const 8)
         )
        )
        (set_local $13
         (i32.const 0)
        )
        (loop $label$13
         (br_if $label$2
          (i32.gt_u
           (i32.add
            (i32.shl
             (i32.wrap/i64
              (get_local $12)
             )
             (i32.const 24)
            )
            (i32.const -1073741825)
           )
           (i32.const 452984830)
          )
         )
         (block $label$14
          (br_if $label$14
           (i64.ne
            (i64.and
             (tee_local $12
              (i64.shr_u
               (get_local $12)
               (i64.const 8)
              )
             )
             (i64.const 255)
            )
            (i64.const 0)
           )
          )
          (loop $label$15
           (br_if $label$2
            (i64.ne
             (i64.and
              (tee_local $12
               (i64.shr_u
                (get_local $12)
                (i64.const 8)
               )
              )
              (i64.const 255)
             )
             (i64.const 0)
            )
           )
           (br_if $label$15
            (i32.lt_s
             (tee_local $13
              (i32.add
               (get_local $13)
               (i32.const 1)
              )
             )
             (i32.const 7)
            )
           )
          )
         )
         (set_local $10
          (i32.const 1)
         )
         (br_if $label$13
          (i32.lt_s
           (tee_local $13
            (i32.add
             (get_local $13)
             (i32.const 1)
            )
           )
           (i32.const 7)
          )
         )
         (br $label$1)
        )
       )
       (set_local $10
        (i32.const 0)
       )
      )
      (call $eosio_assert
       (get_local $10)
       (i32.const 80)
      )
      (i64.store
       (i32.add
        (get_local $2)
        (i32.const 8)
       )
       (get_local $4)
      )
      (i64.store
       (get_local $2)
       (get_local $5)
      )
      (i64.store
       (i32.add
        (get_local $2)
        (i32.const 16)
       )
       (get_local $6)
      )
      (br $label$0)
     )
     (call $eosio_assert
      (i32.const 0)
      (i32.const 176)
     )
     (br $label$0)
    )
    (set_local $10
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (get_local $10)
    (i32.const 80)
   )
   (i64.store
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
    (get_local $4)
   )
   (i64.store
    (get_local $2)
    (get_local $5)
   )
   (i64.store
    (i32.add
     (get_local $2)
     (i32.const 16)
    )
    (get_local $6)
   )
  )
  (block $label$16
   (block $label$17
    (br_if $label$17
     (i64.ne
      (i64.load
       (get_local $3)
      )
      (i64.load
       (tee_local $13
        (i32.add
         (get_local $2)
         (i32.const 8)
        )
       )
      )
     )
    )
    (br_if $label$17
     (i64.ne
      (i64.load offset=8
       (get_local $3)
      )
      (i64.load
       (tee_local $10
        (i32.add
         (get_local $2)
         (i32.const 16)
        )
       )
      )
     )
    )
    (i64.store
     (get_local $0)
     (i64.load
      (get_local $2)
     )
    )
    (i64.store
     (i32.add
      (get_local $0)
      (i32.const 16)
     )
     (i64.load
      (get_local $10)
     )
    )
    (i64.store
     (i32.add
      (get_local $0)
      (i32.const 8)
     )
     (i64.load
      (i32.add
       (get_local $2)
       (i32.const 8)
      )
     )
    )
    (br $label$16)
   )
   (i64.store
    (tee_local $10
     (i32.add
      (i32.add
       (get_local $14)
       (i32.const 112)
      )
      (i32.const 16)
     )
    )
    (i64.load
     (i32.add
      (get_local $2)
      (i32.const 16)
     )
    )
   )
   (i64.store
    (tee_local $11
     (i32.add
      (i32.add
       (get_local $14)
       (i32.const 112)
      )
      (i32.const 8)
     )
    )
    (i64.load
     (get_local $13)
    )
   )
   (i64.store offset=112
    (get_local $14)
    (i64.load
     (get_local $2)
    )
   )
   (i64.store
    (tee_local $13
     (i32.add
      (i32.add
       (get_local $14)
       (i32.const 96)
      )
      (i32.const 8)
     )
    )
    (i64.load
     (i32.add
      (get_local $3)
      (i32.const 8)
     )
    )
   )
   (i64.store offset=96
    (get_local $14)
    (i64.load
     (get_local $3)
    )
   )
   (i64.store
    (i32.add
     (i32.add
      (get_local $14)
      (i32.const 24)
     )
     (i32.const 16)
    )
    (i64.load
     (get_local $10)
    )
   )
   (i64.store
    (i32.add
     (i32.add
      (get_local $14)
      (i32.const 24)
     )
     (i32.const 8)
    )
    (i64.load
     (get_local $11)
    )
   )
   (i64.store offset=24
    (get_local $14)
    (i64.load offset=112
     (get_local $14)
    )
   )
   (i64.store
    (i32.add
     (i32.add
      (get_local $14)
      (i32.const 8)
     )
     (i32.const 8)
    )
    (i64.load
     (get_local $13)
    )
   )
   (i64.store offset=8
    (get_local $14)
    (i64.load offset=96
     (get_local $14)
    )
   )
   (call $_ZN5eosio14exchange_state7convertENS_14extended_assetENS_15extended_symbolE
    (get_local $0)
    (get_local $1)
    (i32.add
     (get_local $14)
     (i32.const 24)
    )
    (i32.add
     (get_local $14)
     (i32.const 8)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $14)
    (i32.const 208)
   )
  )
 )
 (func $_ZNK5eosio14exchange_state20requires_margin_callERKNS0_9connectorE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i64)
  (local $3 f64)
  (local $4 i64)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 336)
    )
   )
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i64.lt_s
      (tee_local $5
       (i64.load
        (i32.add
         (get_local $1)
         (i32.const 56)
        )
       )
      )
      (i64.const 1)
     )
    )
    (drop
     (call $memcpy
      (i32.add
       (get_local $7)
       (i32.const 104)
      )
      (get_local $0)
      (i32.const 232)
     )
    )
    (set_local $3
     (f64.load
      (i32.add
       (get_local $1)
       (i32.const 80)
      )
     )
    )
    (i64.store offset=64
     (get_local $7)
     (tee_local $4
      (i64.load offset=8
       (get_local $1)
      )
     )
    )
    (i64.store offset=56
     (get_local $7)
     (tee_local $5
      (i64.trunc_s/f64
       (f64.mul
        (get_local $3)
        (f64.convert_s/i64
         (get_local $5)
        )
       )
      )
     )
    )
    (set_local $2
     (i64.load offset=16
      (get_local $1)
     )
    )
    (call $eosio_assert
     (i64.lt_u
      (i64.add
       (get_local $5)
       (i64.const 4611686018427387903)
      )
      (i64.const 9223372036854775807)
     )
     (i32.const 16)
    )
    (set_local $5
     (i64.shr_u
      (get_local $4)
      (i64.const 8)
     )
    )
    (set_local $0
     (i32.const 0)
    )
    (block $label$2
     (block $label$3
      (loop $label$4
       (br_if $label$3
        (i32.gt_u
         (i32.add
          (i32.shl
           (i32.wrap/i64
            (get_local $5)
           )
           (i32.const 24)
          )
          (i32.const -1073741825)
         )
         (i32.const 452984830)
        )
       )
       (block $label$5
        (br_if $label$5
         (i64.ne
          (i64.and
           (tee_local $5
            (i64.shr_u
             (get_local $5)
             (i64.const 8)
            )
           )
           (i64.const 255)
          )
          (i64.const 0)
         )
        )
        (loop $label$6
         (br_if $label$3
          (i64.ne
           (i64.and
            (tee_local $5
             (i64.shr_u
              (get_local $5)
              (i64.const 8)
             )
            )
            (i64.const 255)
           )
           (i64.const 0)
          )
         )
         (br_if $label$6
          (i32.lt_s
           (tee_local $0
            (i32.add
             (get_local $0)
             (i32.const 1)
            )
           )
           (i32.const 7)
          )
         )
        )
       )
       (set_local $6
        (i32.const 1)
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $0
          (i32.add
           (get_local $0)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
       (br $label$2)
      )
     )
     (set_local $6
      (i32.const 0)
     )
    )
    (call $eosio_assert
     (get_local $6)
     (i32.const 80)
    )
    (i64.store offset=72
     (get_local $7)
     (get_local $2)
    )
    (set_local $5
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 64)
      )
     )
    )
    (set_local $4
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 72)
      )
     )
    )
    (i32.store
     (i32.add
      (i32.add
       (get_local $7)
       (i32.const 16)
      )
      (i32.const 20)
     )
     (i32.load
      (i32.add
       (i32.add
        (get_local $7)
        (i32.const 56)
       )
       (i32.const 20)
      )
     )
    )
    (i32.store
     (i32.add
      (get_local $7)
      (i32.const 32)
     )
     (i32.load offset=72
      (get_local $7)
     )
    )
    (i64.store offset=48
     (get_local $7)
     (get_local $4)
    )
    (i32.store
     (i32.add
      (i32.add
       (get_local $7)
       (i32.const 16)
      )
      (i32.const 12)
     )
     (i32.load
      (i32.add
       (i32.add
        (get_local $7)
        (i32.const 56)
       )
       (i32.const 12)
      )
     )
    )
    (i32.store
     (i32.add
      (i32.add
       (get_local $7)
       (i32.const 16)
      )
      (i32.const 8)
     )
     (i32.load
      (i32.add
       (i32.add
        (get_local $7)
        (i32.const 56)
       )
       (i32.const 8)
      )
     )
    )
    (i64.store offset=40
     (get_local $7)
     (get_local $5)
    )
    (i32.store offset=20
     (get_local $7)
     (i32.load offset=60
      (get_local $7)
     )
    )
    (i32.store offset=16
     (get_local $7)
     (i32.load offset=56
      (get_local $7)
     )
    )
    (i64.store
     (i32.add
      (get_local $7)
      (i32.const 8)
     )
     (i64.load offset=48
      (get_local $7)
     )
    )
    (i64.store
     (get_local $7)
     (i64.load offset=40
      (get_local $7)
     )
    )
    (call $_ZN5eosio14exchange_state7convertENS_14extended_assetENS_15extended_symbolE
     (i32.add
      (get_local $7)
      (i32.const 80)
     )
     (i32.add
      (get_local $7)
      (i32.const 104)
     )
     (i32.add
      (get_local $7)
      (i32.const 16)
     )
     (get_local $7)
    )
    (set_local $0
     (i32.const 1)
    )
    (br_if $label$0
     (i64.le_s
      (i64.load offset=80
       (get_local $7)
      )
      (i64.load
       (i32.add
        (get_local $1)
        (i32.const 56)
       )
      )
     )
    )
   )
   (set_local $0
    (i32.const 0)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $7)
    (i32.const 336)
   )
  )
  (get_local $0)
 )
 (func $_ZNK5eosio14exchange_state20requires_margin_callEv (param $0 i32) (result i32)
  (local $1 i32)
  (set_local $1
   (i32.const 1)
  )
  (block $label$0
   (br_if $label$0
    (call $_ZNK5eosio14exchange_state20requires_margin_callERKNS0_9connectorE
     (get_local $0)
     (i32.add
      (get_local $0)
      (i32.const 40)
     )
    )
   )
   (set_local $1
    (call $_ZNK5eosio14exchange_state20requires_margin_callERKNS0_9connectorE
     (get_local $0)
     (i32.add
      (get_local $0)
      (i32.const 136)
     )
    )
   )
  )
  (get_local $1)
 )
 (func $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE (param $0 i32) (param $1 i64) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i64)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (local $12 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $12
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 96)
    )
   )
  )
  (i64.store offset=16
   (get_local $12)
   (get_local $1)
  )
  (set_local $4
   (i32.add
    (tee_local $11
     (i32.load offset=8
      (get_local $0)
     )
    )
    (tee_local $10
     (i32.mul
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 12)
       )
      )
      (i32.const 48)
     )
    )
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (get_local $10)
    )
   )
   (set_local $10
    (i32.div_s
     (get_local $10)
     (i32.const 48)
    )
   )
   (set_local $9
    (get_local $11)
   )
   (loop $label$1
    (set_local $9
     (select
      (tee_local $7
       (i32.add
        (tee_local $6
         (i32.add
          (get_local $9)
          (i32.mul
           (tee_local $5
            (i32.shr_u
             (get_local $10)
             (i32.const 1)
            )
           )
           (i32.const 48)
          )
         )
        )
        (i32.const 48)
       )
      )
      (get_local $9)
      (tee_local $6
       (i64.lt_u
        (i64.load
         (get_local $6)
        )
        (get_local $1)
       )
      )
     )
    )
    (set_local $11
     (select
      (get_local $7)
      (get_local $11)
      (get_local $6)
     )
    )
    (br_if $label$1
     (tee_local $10
      (select
       (i32.sub
        (i32.add
         (get_local $10)
         (i32.const -1)
        )
        (get_local $5)
       )
       (get_local $5)
       (get_local $6)
      )
     )
    )
   )
  )
  (block $label$2
   (br_if $label$2
    (i32.eq
     (get_local $11)
     (get_local $4)
    )
   )
   (set_local $11
    (select
     (get_local $4)
     (get_local $11)
     (i64.gt_u
      (i64.load
       (get_local $11)
      )
      (get_local $1)
     )
    )
   )
  )
  (block $label$3
   (br_if $label$3
    (i32.ne
     (get_local $11)
     (get_local $4)
    )
   )
   (set_local $8
    (i64.load
     (get_local $0)
    )
   )
   (i64.store
    (i32.add
     (get_local $12)
     (i32.const 64)
    )
    (get_local $1)
   )
   (i64.store
    (i32.add
     (get_local $12)
     (i32.const 72)
    )
    (i64.const -1)
   )
   (i64.store
    (tee_local $10
     (i32.add
      (get_local $12)
      (i32.const 80)
     )
    )
    (i64.const 0)
   )
   (i32.store
    (i32.add
     (get_local $12)
     (i32.const 88)
    )
    (i32.const 0)
   )
   (i64.store offset=56
    (get_local $12)
    (get_local $8)
   )
   (i64.store offset=48
    (get_local $12)
    (get_local $1)
   )
   (call $_ZN5boost9container3dtl9flat_treeINS1_4pairIyN5eosio11multi_indexILy6290548272952901632ENS4_9exaccountEJEEEEENS1_9select1stIyEENSt3__14lessIyEENS0_13new_allocatorIS8_EEE13insert_uniqueEOS8_
    (i32.add
     (get_local $12)
     (i32.const 40)
    )
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
    (i32.add
     (get_local $12)
     (i32.const 48)
    )
   )
   (block $label$4
    (br_if $label$4
     (i32.eqz
      (tee_local $5
       (i32.load
        (get_local $10)
       )
      )
     )
    )
    (block $label$5
     (block $label$6
      (br_if $label$6
       (i32.eq
        (tee_local $10
         (i32.load
          (tee_local $6
           (i32.add
            (get_local $12)
            (i32.const 84)
           )
          )
         )
        )
        (get_local $5)
       )
      )
      (loop $label$7
       (set_local $9
        (i32.load
         (tee_local $10
          (i32.add
           (get_local $10)
           (i32.const -24)
          )
         )
        )
       )
       (i32.store
        (get_local $10)
        (i32.const 0)
       )
       (block $label$8
        (br_if $label$8
         (i32.eqz
          (get_local $9)
         )
        )
        (block $label$9
         (br_if $label$9
          (i32.eqz
           (i32.load
            (i32.add
             (get_local $9)
             (i32.const 16)
            )
           )
          )
         )
         (call $_ZdlPv
          (i32.load offset=8
           (get_local $9)
          )
         )
        )
        (call $_ZdlPv
         (get_local $9)
        )
       )
       (br_if $label$7
        (i32.ne
         (get_local $5)
         (get_local $10)
        )
       )
      )
      (set_local $10
       (i32.load
        (i32.add
         (get_local $12)
         (i32.const 80)
        )
       )
      )
      (br $label$5)
     )
     (set_local $10
      (get_local $5)
     )
    )
    (i32.store
     (get_local $6)
     (get_local $5)
    )
    (call $_ZdlPv
     (get_local $10)
    )
   )
   (set_local $11
    (i32.load offset=40
     (get_local $12)
    )
   )
   (set_local $1
    (i64.load offset=16
     (get_local $12)
    )
   )
  )
  (block $label$10
   (br_if $label$10
    (i32.eq
     (tee_local $5
      (i32.load
       (i32.add
        (get_local $11)
        (i32.const 36)
       )
      )
     )
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $11)
        (i32.const 32)
       )
      )
     )
    )
   )
   (set_local $10
    (i32.add
     (get_local $5)
     (i32.const -24)
    )
   )
   (set_local $6
    (i32.sub
     (i32.const 0)
     (get_local $7)
    )
   )
   (loop $label$11
    (br_if $label$10
     (i64.eq
      (i64.load
       (i32.load
        (get_local $10)
       )
      )
      (get_local $1)
     )
    )
    (set_local $5
     (get_local $10)
    )
    (set_local $10
     (tee_local $9
      (i32.add
       (get_local $10)
       (i32.const -24)
      )
     )
    )
    (br_if $label$11
     (i32.ne
      (i32.add
       (get_local $9)
       (get_local $6)
      )
      (i32.const -24)
     )
    )
   )
  )
  (set_local $10
   (i32.add
    (get_local $11)
    (i32.const 8)
   )
  )
  (block $label$12
   (block $label$13
    (block $label$14
     (block $label$15
      (br_if $label$15
       (i32.eq
        (get_local $5)
        (get_local $7)
       )
      )
      (call $eosio_assert
       (i32.eq
        (i32.load offset=20
         (tee_local $9
          (i32.load
           (i32.add
            (get_local $5)
            (i32.const -24)
           )
          )
         )
        )
        (get_local $10)
       )
       (i32.const 224)
      )
      (br_if $label$14
       (get_local $9)
      )
      (br $label$13)
     )
     (br_if $label$13
      (i32.lt_s
       (tee_local $9
        (call $db_find_i64
         (i64.load
          (i32.add
           (get_local $11)
           (i32.const 8)
          )
         )
         (i64.load
          (i32.add
           (get_local $11)
           (i32.const 16)
          )
         )
         (i64.const 6290548272952901632)
         (get_local $1)
        )
       )
       (i32.const 0)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=20
        (tee_local $9
         (call $_ZNK5eosio11multi_indexILy6290548272952901632ENS_9exaccountEJEE31load_object_by_primary_iteratorEl
          (get_local $10)
          (get_local $9)
         )
        )
       )
       (get_local $10)
      )
      (i32.const 224)
     )
    )
    (i32.store offset=48
     (get_local $12)
     (get_local $2)
    )
    (call $eosio_assert
     (i32.const 1)
     (i32.const 352)
    )
    (call $_ZN5eosio11multi_indexILy6290548272952901632ENS_9exaccountEJEE6modifyIZNS_17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEE3$_1EEvRKS1_yOT_
     (get_local $10)
     (get_local $9)
     (i32.add
      (get_local $12)
      (i32.const 48)
     )
    )
    (br $label$12)
   )
   (set_local $1
    (i64.load offset=16
     (get_local $12)
    )
   )
   (i32.store offset=12
    (get_local $12)
    (get_local $2)
   )
   (i32.store offset=8
    (get_local $12)
    (i32.add
     (get_local $12)
     (i32.const 16)
    )
   )
   (i64.store offset=40
    (get_local $12)
    (get_local $1)
   )
   (call $eosio_assert
    (i64.eq
     (i64.load
      (i32.add
       (get_local $11)
       (i32.const 8)
      )
     )
     (call $current_receiver)
    )
    (i32.const 288)
   )
   (i32.store offset=48
    (get_local $12)
    (get_local $10)
   )
   (i32.store offset=52
    (get_local $12)
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
   )
   (i32.store offset=56
    (get_local $12)
    (i32.add
     (get_local $12)
     (i32.const 40)
    )
   )
   (i32.store offset=16
    (tee_local $9
     (call $_Znwj
      (i32.const 32)
     )
    )
    (i32.const 0)
   )
   (i64.store offset=8 align=4
    (get_local $9)
    (i64.const 0)
   )
   (i32.store offset=20
    (get_local $9)
    (get_local $10)
   )
   (call $_ZZN5eosio11multi_indexILy6290548272952901632ENS_9exaccountEJEE7emplaceIZNS_17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEE3$_0EENS2_14const_iteratorEyOT_ENKUlRSH_E_clINS2_4itemEEEDaSJ_
    (i32.add
     (get_local $12)
     (i32.const 48)
    )
    (get_local $9)
   )
   (i32.store offset=32
    (get_local $12)
    (get_local $9)
   )
   (i64.store offset=48
    (get_local $12)
    (tee_local $1
     (i64.load
      (get_local $9)
     )
    )
   )
   (i32.store offset=28
    (get_local $12)
    (tee_local $5
     (i32.load offset=24
      (get_local $9)
     )
    )
   )
   (block $label$16
    (block $label$17
     (br_if $label$17
      (i32.ge_u
       (tee_local $10
        (i32.load
         (tee_local $6
          (i32.add
           (get_local $11)
           (i32.const 36)
          )
         )
        )
       )
       (i32.load
        (i32.add
         (get_local $11)
         (i32.const 40)
        )
       )
      )
     )
     (i64.store offset=8
      (get_local $10)
      (get_local $1)
     )
     (i32.store offset=16
      (get_local $10)
      (get_local $5)
     )
     (i32.store offset=32
      (get_local $12)
      (i32.const 0)
     )
     (i32.store
      (get_local $10)
      (get_local $9)
     )
     (i32.store
      (get_local $6)
      (i32.add
       (get_local $10)
       (i32.const 24)
      )
     )
     (br $label$16)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy6290548272952901632ENS1_9exaccountEJEE8item_ptrENS_9allocatorIS5_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS4_4itemENS_14default_deleteISB_EEEERyRlEEEvDpOT_
     (i32.add
      (get_local $11)
      (i32.const 32)
     )
     (i32.add
      (get_local $12)
      (i32.const 32)
     )
     (i32.add
      (get_local $12)
      (i32.const 48)
     )
     (i32.add
      (get_local $12)
      (i32.const 28)
     )
    )
   )
   (set_local $10
    (i32.load offset=32
     (get_local $12)
    )
   )
   (i32.store offset=32
    (get_local $12)
    (i32.const 0)
   )
   (br_if $label$12
    (i32.eqz
     (get_local $10)
    )
   )
   (block $label$18
    (br_if $label$18
     (i32.eqz
      (i32.load
       (i32.add
        (get_local $10)
        (i32.const 16)
       )
      )
     )
    )
    (call $_ZdlPv
     (i32.load offset=8
      (get_local $10)
     )
    )
   )
   (call $_ZdlPv
    (get_local $10)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $12)
    (i32.const 96)
   )
  )
 )
 (func $_ZN5boost9container3dtl9flat_treeINS1_4pairIyN5eosio11multi_indexILy6290548272952901632ENS4_9exaccountEJEEEEENS1_9select1stIyEENSt3__14lessIyEENS0_13new_allocatorIS8_EEE13insert_uniqueEOS8_ (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i64)
  (local $10 i32)
  (i32.store8 offset=4
   (get_local $0)
   (i32.const 0)
  )
  (i32.store
   (get_local $0)
   (i32.const 0)
  )
  (set_local $5
   (i64.load
    (get_local $2)
   )
  )
  (set_local $6
   (tee_local $3
    (i32.load
     (get_local $1)
    )
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (tee_local $7
      (i32.div_s
       (i32.mul
        (tee_local $4
         (i32.load offset=4
          (get_local $1)
         )
        )
        (i32.const 48)
       )
       (i32.const 48)
      )
     )
    )
   )
   (loop $label$1
    (block $label$2
     (br_if $label$2
      (i64.ge_u
       (i64.load
        (tee_local $8
         (i32.add
          (get_local $6)
          (i32.mul
           (tee_local $10
            (i32.shr_u
             (get_local $7)
             (i32.const 1)
            )
           )
           (i32.const 48)
          )
         )
        )
       )
       (get_local $5)
      )
     )
     (set_local $6
      (i32.add
       (get_local $8)
       (i32.const 48)
      )
     )
     (set_local $10
      (i32.sub
       (i32.add
        (get_local $7)
        (i32.const -1)
       )
       (get_local $10)
      )
     )
    )
    (br_if $label$1
     (tee_local $7
      (get_local $10)
     )
    )
   )
  )
  (block $label$3
   (block $label$4
    (block $label$5
     (block $label$6
      (br_if $label$6
       (i32.eq
        (get_local $6)
        (i32.add
         (get_local $3)
         (i32.mul
          (get_local $4)
          (i32.const 48)
         )
        )
       )
      )
      (i32.store8
       (i32.add
        (get_local $0)
        (i32.const 4)
       )
       (i64.lt_u
        (get_local $5)
        (tee_local $9
         (i64.load
          (get_local $6)
         )
        )
       )
      )
      (br_if $label$5
       (i64.lt_u
        (get_local $5)
        (get_local $9)
       )
      )
      (br $label$4)
     )
     (i32.store8
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
      (i32.const 1)
     )
    )
    (block $label$7
     (block $label$8
      (block $label$9
       (block $label$10
        (br_if $label$10
         (i32.ne
          (i32.load offset=8
           (get_local $1)
          )
          (get_local $4)
         )
        )
        (br_if $label$3
         (i32.eq
          (get_local $4)
          (i32.const 89478485)
         )
        )
        (br_if $label$9
         (i32.gt_u
          (get_local $4)
          (i32.const 536870911)
         )
        )
        (set_local $7
         (i32.div_u
          (i32.shl
           (get_local $4)
           (i32.const 3)
          )
          (i32.const 5)
         )
        )
        (br $label$8)
       )
       (call $_ZN5boost9container6vectorINS0_3dtl4pairIyN5eosio11multi_indexILy6290548272952901632ENS4_9exaccountEJEEEEENS0_13new_allocatorIS8_EEvE40priv_forward_range_insert_expand_forwardINS2_17insert_move_proxyISA_PS8_EEEEvSE_jT_
        (get_local $1)
        (get_local $6)
        (i32.const 1)
        (get_local $2)
       )
       (br $label$7)
      )
      (set_local $7
       (select
        (i32.const -1)
        (i32.shl
         (get_local $4)
         (i32.const 3)
        )
        (i32.gt_u
         (get_local $4)
         (i32.const -1610612737)
        )
       )
      )
     )
     (br_if $label$3
      (i32.ge_u
       (tee_local $7
        (select
         (tee_local $10
          (i32.add
           (get_local $4)
           (i32.const 1)
          )
         )
         (tee_local $7
          (select
           (get_local $7)
           (i32.const 89478485)
           (i32.lt_u
            (get_local $7)
            (i32.const 89478485)
           )
          )
         )
         (i32.gt_u
          (get_local $10)
          (get_local $7)
         )
        )
       )
       (i32.const 89478486)
      )
     )
     (call $_ZN5boost9container6vectorINS0_3dtl4pairIyN5eosio11multi_indexILy6290548272952901632ENS4_9exaccountEJEEEEENS0_13new_allocatorIS8_EEvE40priv_forward_range_insert_new_allocationINS2_17insert_move_proxyISA_PS8_EEEEvSE_jSE_jT_
      (get_local $1)
      (call $_Znwj
       (i32.mul
        (get_local $7)
        (i32.const 48)
       )
      )
      (get_local $7)
      (get_local $6)
      (i32.const 1)
      (get_local $2)
     )
    )
    (set_local $6
     (i32.add
      (i32.load
       (get_local $1)
      )
      (i32.mul
       (i32.div_s
        (i32.sub
         (get_local $6)
         (get_local $3)
        )
        (i32.const 48)
       )
       (i32.const 48)
      )
     )
    )
   )
   (i32.store
    (get_local $0)
    (get_local $6)
   )
   (return)
  )
  (call $abort)
  (unreachable)
 )
 (func $_ZNK5eosio11multi_indexILy6290548272952901632ENS_9exaccountEJEE31load_object_by_primary_iteratorEl (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (set_local $8
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $9)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $2
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $3
    (i32.sub
     (i32.const 0)
     (get_local $2)
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i32.eq
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const 16)
       )
      )
      (get_local $1)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $4
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $4)
       (get_local $3)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (get_local $2)
     )
    )
    (set_local $6
     (i32.load
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br $label$2)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $6
       (call $db_get_i64
        (get_local $1)
        (i32.const 0)
        (i32.const 0)
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 656)
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.lt_u
       (get_local $6)
       (i32.const 513)
      )
     )
     (set_local $4
      (call $malloc
       (get_local $6)
      )
     )
     (br $label$4)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $4
      (i32.sub
       (get_local $9)
       (i32.and
        (i32.add
         (get_local $6)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $db_get_i64
     (get_local $1)
     (get_local $4)
     (get_local $6)
    )
   )
   (i32.store offset=36
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=32
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=40
    (get_local $8)
    (tee_local $7
     (i32.add
      (get_local $4)
      (get_local $6)
     )
    )
   )
   (block $label$6
    (br_if $label$6
     (i32.le_u
      (get_local $6)
      (i32.const 512)
     )
    )
    (call $free
     (get_local $4)
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $8)
       (i32.const 40)
      )
     )
    )
    (set_local $4
     (i32.load offset=36
      (get_local $8)
     )
    )
   )
   (i32.store offset=16
    (tee_local $6
     (call $_Znwj
      (i32.const 32)
     )
    )
    (i32.const 0)
   )
   (i64.store offset=8 align=4
    (get_local $6)
    (i64.const 0)
   )
   (i32.store offset=20
    (get_local $6)
    (get_local $0)
   )
   (call $eosio_assert
    (i32.gt_u
     (i32.sub
      (get_local $7)
      (get_local $4)
     )
     (i32.const 7)
    )
    (i32.const 688)
   )
   (drop
    (call $memcpy
     (get_local $6)
     (get_local $4)
     (i32.const 8)
    )
   )
   (i32.store offset=36
    (get_local $8)
    (i32.add
     (get_local $4)
     (i32.const 8)
    )
   )
   (drop
    (call $_ZN5eosiorsINS_10datastreamIPKcEENS_15extended_symbolExEERT_S7_RN5boost9container8flat_mapIT0_T1_NSt3__14lessISB_EENS9_13new_allocatorINSD_4pairISB_SC_EEEEEE
     (i32.add
      (get_local $8)
      (i32.const 32)
     )
     (i32.add
      (get_local $6)
      (i32.const 8)
     )
    )
   )
   (i32.store offset=24
    (get_local $6)
    (get_local $1)
   )
   (i32.store offset=24
    (get_local $8)
    (get_local $6)
   )
   (i64.store offset=16
    (get_local $8)
    (tee_local $5
     (i64.load
      (get_local $6)
     )
    )
   )
   (i32.store offset=12
    (get_local $8)
    (tee_local $7
     (i32.load offset=24
      (get_local $6)
     )
    )
   )
   (block $label$7
    (block $label$8
     (br_if $label$8
      (i32.ge_u
       (tee_local $4
        (i32.load
         (tee_local $1
          (i32.add
           (get_local $0)
           (i32.const 28)
          )
         )
        )
       )
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 32)
        )
       )
      )
     )
     (i64.store offset=8
      (get_local $4)
      (get_local $5)
     )
     (i32.store offset=16
      (get_local $4)
      (get_local $7)
     )
     (i32.store offset=24
      (get_local $8)
      (i32.const 0)
     )
     (i32.store
      (get_local $4)
      (get_local $6)
     )
     (i32.store
      (get_local $1)
      (i32.add
       (get_local $4)
       (i32.const 24)
      )
     )
     (br $label$7)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy6290548272952901632ENS1_9exaccountEJEE8item_ptrENS_9allocatorIS5_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS4_4itemENS_14default_deleteISB_EEEERyRlEEEvDpOT_
     (i32.add
      (get_local $0)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 16)
     )
     (i32.add
      (get_local $8)
      (i32.const 12)
     )
    )
   )
   (set_local $4
    (i32.load offset=24
     (get_local $8)
    )
   )
   (i32.store offset=24
    (get_local $8)
    (i32.const 0)
   )
   (br_if $label$2
    (i32.eqz
     (get_local $4)
    )
   )
   (block $label$9
    (br_if $label$9
     (i32.eqz
      (i32.load
       (i32.add
        (get_local $4)
        (i32.const 16)
       )
      )
     )
    )
    (call $_ZdlPv
     (i32.load offset=8
      (get_local $4)
     )
    )
   )
   (call $_ZdlPv
    (get_local $4)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 48)
   )
  )
  (get_local $6)
 )
 (func $_ZZN5eosio11multi_indexILy6290548272952901632ENS_9exaccountEJEE7emplaceIZNS_17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEE3$_0EENS2_14const_iteratorEyOT_ENKUlRSH_E_clINS2_4itemEEEDaSJ_ (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (local $12 i32)
  (local $13 i64)
  (local $14 i32)
  (local $15 i32)
  (set_local $14
   (tee_local $15
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $15)
  )
  (i64.store
   (get_local $1)
   (i64.load
    (i32.load
     (tee_local $3
      (i32.load offset=4
       (get_local $0)
      )
     )
    )
   )
  )
  (set_local $6
   (i32.add
    (tee_local $11
     (i32.load offset=8
      (get_local $1)
     )
    )
    (tee_local $10
     (i32.mul
      (i32.load
       (i32.add
        (get_local $1)
        (i32.const 12)
       )
      )
      (i32.const 24)
     )
    )
   )
  )
  (set_local $2
   (i32.load
    (get_local $0)
   )
  )
  (set_local $5
   (i64.load offset=16
    (tee_local $12
     (i32.load offset=4
      (get_local $3)
     )
    )
   )
  )
  (set_local $13
   (i64.load offset=8
    (get_local $12)
   )
  )
  (set_local $4
   (i64.load
    (get_local $12)
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (get_local $10)
    )
   )
   (set_local $12
    (i32.div_s
     (get_local $10)
     (i32.const 24)
    )
   )
   (set_local $10
    (get_local $11)
   )
   (loop $label$1
    (set_local $10
     (select
      (tee_local $9
       (i32.add
        (tee_local $8
         (i32.add
          (get_local $10)
          (i32.mul
           (tee_local $7
            (i32.shr_u
             (get_local $12)
             (i32.const 1)
            )
           )
           (i32.const 24)
          )
         )
        )
        (i32.const 24)
       )
      )
      (get_local $10)
      (tee_local $8
       (i64.lt_u
        (i64.load
         (get_local $8)
        )
        (get_local $13)
       )
      )
     )
    )
    (set_local $11
     (select
      (get_local $9)
      (get_local $11)
      (get_local $8)
     )
    )
    (br_if $label$1
     (tee_local $12
      (select
       (i32.sub
        (i32.add
         (get_local $12)
         (i32.const -1)
        )
        (get_local $7)
       )
       (get_local $7)
       (get_local $8)
      )
     )
    )
   )
  )
  (set_local $7
   (i32.add
    (get_local $1)
    (i32.const 8)
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $11)
      (get_local $6)
     )
    )
    (br_if $label$2
     (i64.ge_u
      (get_local $13)
      (i64.load
       (get_local $11)
      )
     )
    )
   )
   (i64.store offset=8
    (get_local $14)
    (get_local $5)
   )
   (i64.store
    (get_local $14)
    (get_local $13)
   )
   (i64.store offset=16
    (get_local $14)
    (i64.const 0)
   )
   (call $_ZN5boost9container3dtl9flat_treeINS1_4pairIN5eosio15extended_symbolExEENS1_9select1stIS5_EENSt3__14lessIS5_EENS0_13new_allocatorIS6_EEE13insert_uniqueENS0_12vec_iteratorIPS6_Lb1EEEOS6_
    (i32.add
     (get_local $14)
     (i32.const 24)
    )
    (get_local $7)
    (get_local $11)
    (get_local $14)
   )
   (set_local $11
    (i32.load offset=24
     (get_local $14)
    )
   )
  )
  (i64.store offset=16
   (get_local $11)
   (get_local $4)
  )
  (call $eosio_assert
   (i32.xor
    (i32.wrap/i64
     (i64.shr_u
      (i64.load
       (i32.load
        (i32.add
         (get_local $3)
         (i32.const 4)
        )
       )
      )
      (i64.const 63)
     )
    )
    (i32.const 1)
   )
   (i32.const 624)
  )
  (set_local $13
   (i64.extend_u/i32
    (tee_local $10
     (i32.load
      (i32.add
       (get_local $1)
       (i32.const 12)
      )
     )
    )
   )
  )
  (set_local $12
   (i32.const 8)
  )
  (loop $label$4
   (set_local $12
    (i32.add
     (get_local $12)
     (i32.const 1)
    )
   )
   (br_if $label$4
    (i64.ne
     (tee_local $13
      (i64.shr_u
       (get_local $13)
       (i64.const 7)
      )
     )
     (i64.const 0)
    )
   )
  )
  (block $label$5
   (br_if $label$5
    (i32.eqz
     (get_local $10)
    )
   )
   (set_local $12
    (i32.add
     (i32.sub
      (tee_local $10
       (i32.mul
        (get_local $10)
        (i32.const 24)
       )
      )
      (i32.rem_u
       (i32.add
        (get_local $10)
        (i32.const -24)
       )
       (i32.const 24)
      )
     )
     (get_local $12)
    )
   )
  )
  (block $label$6
   (block $label$7
    (br_if $label$7
     (i32.lt_u
      (get_local $12)
      (i32.const 513)
     )
    )
    (set_local $10
     (call $malloc
      (get_local $12)
     )
    )
    (br $label$6)
   )
   (i32.store offset=4
    (i32.const 0)
    (tee_local $10
     (i32.sub
      (get_local $15)
      (i32.and
       (i32.add
        (get_local $12)
        (i32.const 15)
       )
       (i32.const -16)
      )
     )
    )
   )
  )
  (i32.store
   (get_local $14)
   (get_local $10)
  )
  (i32.store offset=8
   (get_local $14)
   (i32.add
    (get_local $10)
    (get_local $12)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (get_local $12)
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (get_local $10)
    (get_local $1)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $14)
   (i32.add
    (get_local $10)
    (i32.const 8)
   )
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEENS_15extended_symbolExEERT_S6_RKN5boost9container8flat_mapIT0_T1_NSt3__14lessISA_EENS8_13new_allocatorINSC_4pairISA_SB_EEEEEE
    (get_local $14)
    (get_local $7)
   )
  )
  (i32.store offset=24
   (get_local $1)
   (call $db_store_i64
    (i64.load offset=8
     (get_local $2)
    )
    (i64.const 6290548272952901632)
    (i64.load
     (i32.load offset=8
      (get_local $0)
     )
    )
    (tee_local $13
     (i64.load
      (get_local $1)
     )
    )
    (get_local $10)
    (get_local $12)
   )
  )
  (block $label$8
   (br_if $label$8
    (i32.lt_u
     (get_local $12)
     (i32.const 513)
    )
   )
   (call $free
    (get_local $10)
   )
  )
  (block $label$9
   (br_if $label$9
    (i64.lt_u
     (get_local $13)
     (i64.load offset=16
      (get_local $2)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $2)
     (i32.const 16)
    )
    (select
     (i64.const -2)
     (i64.add
      (get_local $13)
      (i64.const 1)
     )
     (i64.gt_u
      (get_local $13)
      (i64.const -3)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $14)
    (i32.const 32)
   )
  )
 )
 (func $_ZNSt3__16vectorIN5eosio11multi_indexILy6290548272952901632ENS1_9exaccountEJEE8item_ptrENS_9allocatorIS5_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS4_4itemENS_14default_deleteISB_EEEERyRlEEEvDpOT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.ge_u
      (tee_local $5
       (i32.add
        (tee_local $4
         (i32.div_s
          (i32.sub
           (i32.load offset=4
            (get_local $0)
           )
           (tee_local $6
            (i32.load
             (get_local $0)
            )
           )
          )
          (i32.const 24)
         )
        )
        (i32.const 1)
       )
      )
      (i32.const 178956971)
     )
    )
    (set_local $7
     (i32.const 178956970)
    )
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.gt_u
        (tee_local $6
         (i32.div_s
          (i32.sub
           (i32.load offset=8
            (get_local $0)
           )
           (get_local $6)
          )
          (i32.const 24)
         )
        )
        (i32.const 89478484)
       )
      )
      (br_if $label$2
       (i32.eqz
        (tee_local $7
         (select
          (get_local $5)
          (tee_local $7
           (i32.shl
            (get_local $6)
            (i32.const 1)
           )
          )
          (i32.lt_u
           (get_local $7)
           (get_local $5)
          )
         )
        )
       )
      )
     )
     (set_local $6
      (call $_Znwj
       (i32.mul
        (get_local $7)
        (i32.const 24)
       )
      )
     )
     (br $label$0)
    )
    (set_local $7
     (i32.const 0)
    )
    (set_local $6
     (i32.const 0)
    )
    (br $label$0)
   )
   (call $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
    (get_local $0)
   )
   (unreachable)
  )
  (set_local $5
   (i32.load
    (get_local $1)
   )
  )
  (i32.store
   (get_local $1)
   (i32.const 0)
  )
  (i32.store
   (tee_local $1
    (i32.add
     (get_local $6)
     (i32.mul
      (get_local $4)
      (i32.const 24)
     )
    )
   )
   (get_local $5)
  )
  (i64.store offset=8
   (get_local $1)
   (i64.load
    (get_local $2)
   )
  )
  (i32.store offset=16
   (get_local $1)
   (i32.load
    (get_local $3)
   )
  )
  (set_local $4
   (i32.add
    (get_local $6)
    (i32.mul
     (get_local $7)
     (i32.const 24)
    )
   )
  )
  (set_local $5
   (i32.add
    (get_local $1)
    (i32.const 24)
   )
  )
  (block $label$4
   (block $label$5
    (br_if $label$5
     (i32.eq
      (tee_local $6
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
      )
      (tee_local $7
       (i32.load
        (get_local $0)
       )
      )
     )
    )
    (loop $label$6
     (set_local $3
      (i32.load
       (tee_local $2
        (i32.add
         (get_local $6)
         (i32.const -24)
        )
       )
      )
     )
     (i32.store
      (get_local $2)
      (i32.const 0)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
      (get_local $3)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -8)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -8)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -12)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -12)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -16)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -16)
       )
      )
     )
     (set_local $1
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
     )
     (set_local $6
      (get_local $2)
     )
     (br_if $label$6
      (i32.ne
       (get_local $7)
       (get_local $2)
      )
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $6
     (i32.load
      (get_local $0)
     )
    )
    (br $label$4)
   )
   (set_local $6
    (get_local $7)
   )
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $5)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
   (get_local $4)
  )
  (block $label$7
   (br_if $label$7
    (i32.eq
     (get_local $7)
     (get_local $6)
    )
   )
   (loop $label$8
    (set_local $1
     (i32.load
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.const 0)
    )
    (block $label$9
     (br_if $label$9
      (i32.eqz
       (get_local $1)
      )
     )
     (block $label$10
      (br_if $label$10
       (i32.eqz
        (i32.load
         (i32.add
          (get_local $1)
          (i32.const 16)
         )
        )
       )
      )
      (call $_ZdlPv
       (i32.load offset=8
        (get_local $1)
       )
      )
     )
     (call $_ZdlPv
      (get_local $1)
     )
    )
    (br_if $label$8
     (i32.ne
      (get_local $6)
      (get_local $7)
     )
    )
   )
  )
  (block $label$11
   (br_if $label$11
    (i32.eqz
     (get_local $6)
    )
   )
   (call $_ZdlPv
    (get_local $6)
   )
  )
 )
 (func $_ZN5eosio11multi_indexILy6290548272952901632ENS_9exaccountEJEE6modifyIZNS_17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEE3$_1EEvRKS1_yOT_ (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i64)
  (local $4 i64)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (local $12 i64)
  (local $13 i32)
  (local $14 i32)
  (set_local $13
   (tee_local $14
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $14)
  )
  (call $eosio_assert
   (i32.eq
    (i32.load offset=20
     (get_local $1)
    )
    (get_local $0)
   )
   (i32.const 400)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load
     (get_local $0)
    )
    (call $current_receiver)
   )
   (i32.const 448)
  )
  (set_local $6
   (i32.add
    (tee_local $11
     (i32.load offset=8
      (get_local $1)
     )
    )
    (tee_local $10
     (i32.mul
      (i32.load
       (i32.add
        (get_local $1)
        (i32.const 12)
       )
      )
      (i32.const 24)
     )
    )
   )
  )
  (set_local $3
   (i64.load
    (get_local $1)
   )
  )
  (set_local $5
   (i64.load offset=16
    (tee_local $2
     (i32.load
      (get_local $2)
     )
    )
   )
  )
  (set_local $12
   (i64.load offset=8
    (get_local $2)
   )
  )
  (set_local $4
   (i64.load
    (get_local $2)
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (get_local $10)
    )
   )
   (set_local $2
    (i32.div_s
     (get_local $10)
     (i32.const 24)
    )
   )
   (set_local $10
    (get_local $11)
   )
   (loop $label$1
    (set_local $10
     (select
      (tee_local $9
       (i32.add
        (tee_local $8
         (i32.add
          (get_local $10)
          (i32.mul
           (tee_local $7
            (i32.shr_u
             (get_local $2)
             (i32.const 1)
            )
           )
           (i32.const 24)
          )
         )
        )
        (i32.const 24)
       )
      )
      (get_local $10)
      (tee_local $8
       (i64.lt_u
        (i64.load
         (get_local $8)
        )
        (get_local $12)
       )
      )
     )
    )
    (set_local $11
     (select
      (get_local $9)
      (get_local $11)
      (get_local $8)
     )
    )
    (br_if $label$1
     (tee_local $2
      (select
       (i32.sub
        (i32.add
         (get_local $2)
         (i32.const -1)
        )
        (get_local $7)
       )
       (get_local $7)
       (get_local $8)
      )
     )
    )
   )
  )
  (set_local $7
   (i32.add
    (get_local $1)
    (i32.const 8)
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $11)
      (get_local $6)
     )
    )
    (br_if $label$2
     (i64.ge_u
      (get_local $12)
      (i64.load
       (get_local $11)
      )
     )
    )
   )
   (i64.store offset=8
    (get_local $13)
    (get_local $5)
   )
   (i64.store
    (get_local $13)
    (get_local $12)
   )
   (i64.store offset=16
    (get_local $13)
    (i64.const 0)
   )
   (call $_ZN5boost9container3dtl9flat_treeINS1_4pairIN5eosio15extended_symbolExEENS1_9select1stIS5_EENSt3__14lessIS5_EENS0_13new_allocatorIS6_EEE13insert_uniqueENS0_12vec_iteratorIPS6_Lb1EEEOS6_
    (i32.add
     (get_local $13)
     (i32.const 24)
    )
    (get_local $7)
    (get_local $11)
    (get_local $13)
   )
   (set_local $11
    (i32.load offset=24
     (get_local $13)
    )
   )
  )
  (i64.store offset=16
   (get_local $11)
   (tee_local $12
    (i64.add
     (i64.load offset=16
      (get_local $11)
     )
     (get_local $4)
    )
   )
  )
  (call $eosio_assert
   (i32.xor
    (i32.wrap/i64
     (i64.shr_u
      (get_local $12)
      (i64.const 63)
     )
    )
    (i32.const 1)
   )
   (i32.const 512)
  )
  (call $eosio_assert
   (i64.eq
    (get_local $3)
    (i64.load
     (get_local $1)
    )
   )
   (i32.const 544)
  )
  (set_local $12
   (i64.extend_u/i32
    (tee_local $10
     (i32.load
      (i32.add
       (get_local $1)
       (i32.const 12)
      )
     )
    )
   )
  )
  (set_local $2
   (i32.const 8)
  )
  (loop $label$4
   (set_local $2
    (i32.add
     (get_local $2)
     (i32.const 1)
    )
   )
   (br_if $label$4
    (i64.ne
     (tee_local $12
      (i64.shr_u
       (get_local $12)
       (i64.const 7)
      )
     )
     (i64.const 0)
    )
   )
  )
  (block $label$5
   (br_if $label$5
    (i32.eqz
     (get_local $10)
    )
   )
   (set_local $2
    (i32.add
     (i32.sub
      (tee_local $10
       (i32.mul
        (get_local $10)
        (i32.const 24)
       )
      )
      (i32.rem_u
       (i32.add
        (get_local $10)
        (i32.const -24)
       )
       (i32.const 24)
      )
     )
     (get_local $2)
    )
   )
  )
  (block $label$6
   (block $label$7
    (br_if $label$7
     (i32.lt_u
      (get_local $2)
      (i32.const 513)
     )
    )
    (set_local $10
     (call $malloc
      (get_local $2)
     )
    )
    (br $label$6)
   )
   (i32.store offset=4
    (i32.const 0)
    (tee_local $10
     (i32.sub
      (get_local $14)
      (i32.and
       (i32.add
        (get_local $2)
        (i32.const 15)
       )
       (i32.const -16)
      )
     )
    )
   )
  )
  (i32.store
   (get_local $13)
   (get_local $10)
  )
  (i32.store offset=8
   (get_local $13)
   (i32.add
    (get_local $10)
    (get_local $2)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (get_local $2)
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (get_local $10)
    (get_local $1)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $13)
   (i32.add
    (get_local $10)
    (i32.const 8)
   )
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEENS_15extended_symbolExEERT_S6_RKN5boost9container8flat_mapIT0_T1_NSt3__14lessISA_EENS8_13new_allocatorINSC_4pairISA_SB_EEEEEE
    (get_local $13)
    (get_local $7)
   )
  )
  (call $db_update_i64
   (i32.load offset=24
    (get_local $1)
   )
   (i64.const 0)
   (get_local $10)
   (get_local $2)
  )
  (block $label$8
   (br_if $label$8
    (i32.lt_u
     (get_local $2)
     (i32.const 513)
    )
   )
   (call $free
    (get_local $10)
   )
  )
  (block $label$9
   (br_if $label$9
    (i64.lt_u
     (get_local $3)
     (i64.load offset=16
      (get_local $0)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (select
     (i64.const -2)
     (i64.add
      (get_local $3)
      (i64.const 1)
     )
     (i64.gt_u
      (get_local $3)
      (i64.const -3)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $13)
    (i32.const 32)
   )
  )
 )
 (func $_ZN5boost9container3dtl9flat_treeINS1_4pairIN5eosio15extended_symbolExEENS1_9select1stIS5_EENSt3__14lessIS5_EENS0_13new_allocatorIS6_EEE13insert_uniqueENS0_12vec_iteratorIPS6_Lb1EEEOS6_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
  (local $8 i64)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (local $12 i32)
  (local $13 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $13
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (block $label$6
         (block $label$7
          (block $label$8
           (br_if $label$8
            (i32.eq
             (tee_local $6
              (i32.add
               (tee_local $4
                (i32.load
                 (get_local $1)
                )
               )
               (i32.mul
                (tee_local $5
                 (i32.load offset=4
                  (get_local $1)
                 )
                )
                (i32.const 24)
               )
              )
             )
             (get_local $2)
            )
           )
           (br_if $label$7
            (i64.ge_u
             (tee_local $7
              (i64.load
               (get_local $3)
              )
             )
             (i64.load
              (get_local $2)
             )
            )
           )
          )
          (br_if $label$4
           (i32.eq
            (get_local $4)
            (get_local $2)
           )
          )
          (br_if $label$4
           (i64.lt_u
            (tee_local $8
             (i64.load
              (tee_local $12
               (i32.add
                (get_local $2)
                (i32.const -24)
               )
              )
             )
            )
            (tee_local $7
             (i64.load
              (get_local $3)
             )
            )
           )
          )
          (br_if $label$3
           (i64.ge_u
            (get_local $7)
            (get_local $8)
           )
          )
          (set_local $2
           (get_local $4)
          )
          (br_if $label$6
           (tee_local $11
            (i32.div_s
             (i32.sub
              (get_local $12)
              (get_local $4)
             )
             (i32.const 24)
            )
           )
          )
          (br $label$5)
         )
         (block $label$9
          (br_if $label$9
           (i32.eqz
            (tee_local $11
             (i32.div_s
              (i32.sub
               (get_local $6)
               (get_local $2)
              )
              (i32.const 24)
             )
            )
           )
          )
          (loop $label$10
           (block $label$11
            (br_if $label$11
             (i64.ge_u
              (i64.load
               (tee_local $9
                (i32.add
                 (get_local $2)
                 (i32.mul
                  (tee_local $10
                   (i32.shr_u
                    (get_local $11)
                    (i32.const 1)
                   )
                  )
                  (i32.const 24)
                 )
                )
               )
              )
              (get_local $7)
             )
            )
            (set_local $2
             (i32.add
              (get_local $9)
              (i32.const 24)
             )
            )
            (set_local $10
             (i32.sub
              (i32.add
               (get_local $11)
               (i32.const -1)
              )
              (get_local $10)
             )
            )
           )
           (br_if $label$10
            (tee_local $11
             (get_local $10)
            )
           )
          )
         )
         (br_if $label$4
          (i32.eq
           (get_local $2)
           (get_local $6)
          )
         )
         (set_local $12
          (get_local $2)
         )
         (br_if $label$4
          (i64.lt_u
           (get_local $7)
           (i64.load
            (get_local $2)
           )
          )
         )
         (br $label$3)
        )
        (loop $label$12
         (block $label$13
          (br_if $label$13
           (i64.ge_u
            (i64.load
             (tee_local $9
              (i32.add
               (get_local $2)
               (i32.mul
                (tee_local $10
                 (i32.shr_u
                  (get_local $11)
                  (i32.const 1)
                 )
                )
                (i32.const 24)
               )
              )
             )
            )
            (get_local $7)
           )
          )
          (set_local $2
           (i32.add
            (get_local $9)
            (i32.const 24)
           )
          )
          (set_local $10
           (i32.sub
            (i32.add
             (get_local $11)
             (i32.const -1)
            )
            (get_local $10)
           )
          )
         )
         (br_if $label$12
          (tee_local $11
           (get_local $10)
          )
         )
        )
       )
       (br_if $label$4
        (i32.eq
         (get_local $2)
         (get_local $12)
        )
       )
       (set_local $12
        (get_local $2)
       )
       (br_if $label$3
        (i64.ge_u
         (get_local $7)
         (i64.load
          (get_local $2)
         )
        )
       )
      )
      (i32.store offset=8
       (get_local $13)
       (get_local $2)
      )
      (block $label$14
       (br_if $label$14
        (i32.ne
         (i32.load offset=8
          (get_local $1)
         )
         (get_local $5)
        )
       )
       (call $_ZN5boost9container6vectorINS0_3dtl4pairIN5eosio15extended_symbolExEENS0_13new_allocatorIS6_EEvE37priv_forward_range_insert_no_capacityINS2_17insert_move_proxyIS8_PS6_EEEENS0_12vec_iteratorISC_Lb0EEERKSC_jT_NS_11move_detail17integral_constantIjLj1EEE
        (get_local $0)
        (get_local $1)
        (i32.add
         (get_local $13)
         (i32.const 8)
        )
        (i32.const 1)
        (get_local $3)
       )
       (br $label$0)
      )
      (set_local $9
       (i32.div_s
        (i32.sub
         (get_local $2)
         (get_local $4)
        )
        (i32.const 24)
       )
      )
      (br_if $label$2
       (i32.eq
        (get_local $6)
        (get_local $2)
       )
      )
      (i64.store
       (i32.add
        (get_local $6)
        (i32.const 8)
       )
       (i64.load
        (i32.add
         (get_local $6)
         (i32.const -16)
        )
       )
      )
      (i64.store
       (get_local $6)
       (i64.load
        (tee_local $11
         (i32.add
          (get_local $6)
          (i32.const -24)
         )
        )
       )
      )
      (i64.store offset=16
       (i32.add
        (get_local $4)
        (i32.mul
         (get_local $5)
         (i32.const 24)
        )
       )
       (i64.load
        (i32.add
         (get_local $6)
         (i32.const -8)
        )
       )
      )
      (i32.store
       (tee_local $10
        (i32.add
         (get_local $1)
         (i32.const 4)
        )
       )
       (i32.add
        (i32.load
         (get_local $10)
        )
        (i32.const 1)
       )
      )
      (block $label$15
       (br_if $label$15
        (i32.eq
         (get_local $11)
         (get_local $2)
        )
       )
       (loop $label$16
        (i64.store
         (i32.add
          (get_local $11)
          (i32.const 8)
         )
         (i64.load
          (i32.add
           (get_local $11)
           (i32.const -16)
          )
         )
        )
        (i64.store
         (get_local $11)
         (i64.load
          (tee_local $10
           (i32.add
            (get_local $11)
            (i32.const -24)
           )
          )
         )
        )
        (i64.store
         (i32.add
          (get_local $11)
          (i32.const 16)
         )
         (i64.load
          (i32.add
           (get_local $11)
           (i32.const -8)
          )
         )
        )
        (set_local $11
         (get_local $10)
        )
        (br_if $label$16
         (i32.ne
          (get_local $2)
          (get_local $10)
         )
        )
       )
      )
      (i64.store
       (get_local $2)
       (i64.load
        (get_local $3)
       )
      )
      (i64.store
       (i32.add
        (get_local $2)
        (i32.const 8)
       )
       (i64.load
        (i32.add
         (get_local $3)
         (i32.const 8)
        )
       )
      )
      (i64.store offset=16
       (get_local $2)
       (i64.load offset=16
        (get_local $3)
       )
      )
      (br $label$1)
     )
     (i32.store
      (get_local $0)
      (i32.add
       (get_local $4)
       (i32.mul
        (i32.div_s
         (i32.sub
          (get_local $12)
          (get_local $4)
         )
         (i32.const 24)
        )
        (i32.const 24)
       )
      )
     )
     (br $label$0)
    )
    (i64.store
     (get_local $2)
     (i64.load
      (get_local $3)
     )
    )
    (i64.store
     (i32.add
      (get_local $2)
      (i32.const 8)
     )
     (i64.load
      (i32.add
       (get_local $3)
       (i32.const 8)
      )
     )
    )
    (i64.store offset=16
     (i32.add
      (get_local $4)
      (i32.mul
       (get_local $5)
       (i32.const 24)
      )
     )
     (i64.load offset=16
      (get_local $3)
     )
    )
    (i32.store
     (tee_local $11
      (i32.add
       (get_local $1)
       (i32.const 4)
      )
     )
     (i32.add
      (i32.load
       (get_local $11)
      )
      (i32.const 1)
     )
    )
   )
   (i32.store
    (get_local $0)
    (i32.add
     (i32.load
      (get_local $1)
     )
     (i32.mul
      (get_local $9)
      (i32.const 24)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $13)
    (i32.const 16)
   )
  )
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEENS_15extended_symbolExEERT_S6_RKN5boost9container8flat_mapIT0_T1_NSt3__14lessISA_EENS8_13new_allocatorINSC_4pairISA_SB_EEEEEE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $6
   (i32.load offset=4
    (get_local $0)
   )
  )
  (set_local $5
   (i64.load32_u offset=4
    (get_local $1)
   )
  )
  (set_local $3
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (set_local $4
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
  )
  (loop $label$0
   (set_local $7
    (i32.wrap/i64
     (get_local $5)
    )
   )
   (i32.store8 offset=15
    (get_local $8)
    (i32.or
     (i32.shl
      (tee_local $2
       (i64.ne
        (tee_local $5
         (i64.shr_u
          (get_local $5)
          (i64.const 7)
         )
        )
        (i64.const 0)
       )
      )
      (i32.const 7)
     )
     (i32.and
      (get_local $7)
      (i32.const 127)
     )
    )
   )
   (call $eosio_assert
    (i32.gt_s
     (i32.sub
      (i32.load
       (get_local $3)
      )
      (get_local $6)
     )
     (i32.const 0)
    )
    (i32.const 608)
   )
   (drop
    (call $memcpy
     (i32.load
      (get_local $4)
     )
     (i32.add
      (get_local $8)
      (i32.const 15)
     )
     (i32.const 1)
    )
   )
   (i32.store
    (get_local $4)
    (tee_local $6
     (i32.add
      (i32.load
       (get_local $4)
      )
      (i32.const 1)
     )
    )
   )
   (br_if $label$0
    (get_local $2)
   )
  )
  (block $label$1
   (br_if $label$1
    (i32.eqz
     (tee_local $4
      (i32.load
       (i32.add
        (get_local $1)
        (i32.const 4)
       )
      )
     )
    )
   )
   (set_local $3
    (i32.add
     (tee_local $7
      (i32.load
       (get_local $1)
      )
     )
     (i32.mul
      (get_local $4)
      (i32.const 24)
     )
    )
   )
   (set_local $4
    (i32.add
     (get_local $0)
     (i32.const 4)
    )
   )
   (loop $label$2
    (call $eosio_assert
     (i32.gt_s
      (i32.sub
       (i32.load
        (tee_local $2
         (i32.add
          (get_local $0)
          (i32.const 8)
         )
        )
       )
       (get_local $6)
      )
      (i32.const 7)
     )
     (i32.const 608)
    )
    (drop
     (call $memcpy
      (i32.load
       (get_local $4)
      )
      (get_local $7)
      (i32.const 8)
     )
    )
    (i32.store
     (get_local $4)
     (tee_local $6
      (i32.add
       (i32.load
        (get_local $4)
       )
       (i32.const 8)
      )
     )
    )
    (call $eosio_assert
     (i32.gt_s
      (i32.sub
       (i32.load
        (get_local $2)
       )
       (get_local $6)
      )
      (i32.const 7)
     )
     (i32.const 608)
    )
    (drop
     (call $memcpy
      (i32.load
       (get_local $4)
      )
      (i32.add
       (get_local $7)
       (i32.const 8)
      )
      (i32.const 8)
     )
    )
    (i32.store
     (get_local $4)
     (tee_local $6
      (i32.add
       (i32.load
        (get_local $4)
       )
       (i32.const 8)
      )
     )
    )
    (call $eosio_assert
     (i32.gt_s
      (i32.sub
       (i32.load
        (get_local $2)
       )
       (get_local $6)
      )
      (i32.const 7)
     )
     (i32.const 608)
    )
    (drop
     (call $memcpy
      (i32.load
       (get_local $4)
      )
      (i32.add
       (get_local $7)
       (i32.const 16)
      )
      (i32.const 8)
     )
    )
    (i32.store
     (get_local $4)
     (tee_local $6
      (i32.add
       (i32.load
        (get_local $4)
       )
       (i32.const 8)
      )
     )
    )
    (br_if $label$2
     (i32.ne
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const 24)
       )
      )
      (get_local $3)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZN5boost9container6vectorINS0_3dtl4pairIN5eosio15extended_symbolExEENS0_13new_allocatorIS6_EEvE37priv_forward_range_insert_no_capacityINS2_17insert_move_proxyIS8_PS6_EEEENS0_12vec_iteratorISC_Lb0EEERKSC_jT_NS_11move_detail17integral_constantIjLj1EEE (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (param $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (set_local $6
   (i32.div_s
    (i32.sub
     (tee_local $5
      (i32.load
       (get_local $2)
      )
     )
     (i32.load
      (get_local $1)
     )
    )
    (i32.const 24)
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.lt_u
     (i32.sub
      (i32.const 178956970)
      (tee_local $2
       (i32.load offset=8
        (get_local $1)
       )
      )
     )
     (i32.add
      (i32.sub
       (get_local $3)
       (get_local $2)
      )
      (tee_local $10
       (i32.load offset=4
        (get_local $1)
       )
      )
     )
    )
   )
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i32.gt_u
       (get_local $2)
       (i32.const 536870911)
      )
     )
     (set_local $2
      (i32.div_u
       (i32.shl
        (get_local $2)
        (i32.const 3)
       )
       (i32.const 5)
      )
     )
     (br $label$1)
    )
    (set_local $2
     (select
      (i32.const -1)
      (i32.shl
       (get_local $2)
       (i32.const 3)
      )
      (i32.gt_u
       (get_local $2)
       (i32.const -1610612737)
      )
     )
    )
   )
   (br_if $label$0
    (i32.ge_u
     (tee_local $7
      (select
       (tee_local $10
        (i32.add
         (get_local $10)
         (get_local $3)
        )
       )
       (tee_local $2
        (select
         (get_local $2)
         (i32.const 178956970)
         (i32.lt_u
          (get_local $2)
          (i32.const 178956970)
         )
        )
       )
       (i32.gt_u
        (get_local $10)
        (get_local $2)
       )
      )
     )
     (i32.const 178956971)
    )
   )
   (set_local $2
    (tee_local $9
     (call $_Znwj
      (i32.mul
       (get_local $7)
       (i32.const 24)
      )
     )
    )
   )
   (block $label$3
    (br_if $label$3
     (i32.eq
      (tee_local $8
       (i32.load
        (get_local $1)
       )
      )
      (get_local $5)
     )
    )
    (set_local $2
     (get_local $9)
    )
    (br_if $label$3
     (i32.eqz
      (get_local $8)
     )
    )
    (set_local $10
     (get_local $8)
    )
    (set_local $2
     (get_local $9)
    )
    (loop $label$4
     (i64.store
      (get_local $2)
      (i64.load
       (get_local $10)
      )
     )
     (i64.store
      (i32.add
       (get_local $2)
       (i32.const 8)
      )
      (i64.load
       (i32.add
        (get_local $10)
        (i32.const 8)
       )
      )
     )
     (i64.store
      (i32.add
       (get_local $2)
       (i32.const 16)
      )
      (i64.load
       (i32.add
        (get_local $10)
        (i32.const 16)
       )
      )
     )
     (set_local $2
      (i32.add
       (get_local $2)
       (i32.const 24)
      )
     )
     (br_if $label$4
      (i32.ne
       (tee_local $10
        (i32.add
         (get_local $10)
         (i32.const 24)
        )
       )
       (get_local $5)
      )
     )
    )
   )
   (i64.store
    (get_local $2)
    (i64.load
     (get_local $4)
    )
   )
   (i64.store
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
    (i64.load
     (i32.add
      (get_local $4)
      (i32.const 8)
     )
    )
   )
   (i64.store offset=16
    (get_local $2)
    (i64.load offset=16
     (get_local $4)
    )
   )
   (set_local $2
    (i32.add
     (get_local $2)
     (i32.mul
      (get_local $3)
      (i32.const 24)
     )
    )
   )
   (block $label$5
    (br_if $label$5
     (i32.eqz
      (get_local $8)
     )
    )
    (block $label$6
     (br_if $label$6
      (i32.eq
       (tee_local $10
        (i32.add
         (get_local $8)
         (i32.mul
          (i32.load
           (i32.add
            (get_local $1)
            (i32.const 4)
           )
          )
          (i32.const 24)
         )
        )
       )
       (get_local $5)
      )
     )
     (loop $label$7
      (i64.store
       (get_local $2)
       (i64.load
        (get_local $5)
       )
      )
      (i64.store
       (i32.add
        (get_local $2)
        (i32.const 8)
       )
       (i64.load
        (i32.add
         (get_local $5)
         (i32.const 8)
        )
       )
      )
      (i64.store
       (i32.add
        (get_local $2)
        (i32.const 16)
       )
       (i64.load
        (i32.add
         (get_local $5)
         (i32.const 16)
        )
       )
      )
      (set_local $2
       (i32.add
        (get_local $2)
        (i32.const 24)
       )
      )
      (br_if $label$7
       (i32.ne
        (tee_local $5
         (i32.add
          (get_local $5)
          (i32.const 24)
         )
        )
        (get_local $10)
       )
      )
     )
    )
    (call $_ZdlPv
     (i32.load
      (get_local $1)
     )
    )
   )
   (i32.store
    (get_local $1)
    (get_local $9)
   )
   (i32.store
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (get_local $7)
   )
   (i32.store
    (i32.add
     (get_local $1)
     (i32.const 4)
    )
    (i32.div_s
     (i32.sub
      (get_local $2)
      (get_local $9)
     )
     (i32.const 24)
    )
   )
   (i32.store
    (get_local $0)
    (i32.add
     (get_local $9)
     (i32.mul
      (get_local $6)
      (i32.const 24)
     )
    )
   )
   (return)
  )
  (call $abort)
  (unreachable)
 )
 (func $_ZN5eosiorsINS_10datastreamIPKcEENS_15extended_symbolExEERT_S7_RN5boost9container8flat_mapIT0_T1_NSt3__14lessISB_EENS9_13new_allocatorINSD_4pairISB_SC_EEEEEE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 64)
    )
   )
  )
  (set_local $6
   (i32.const 0)
  )
  (i32.store offset=4
   (get_local $1)
   (i32.const 0)
  )
  (set_local $8
   (i32.load offset=4
    (get_local $0)
   )
  )
  (set_local $5
   (i64.const 0)
  )
  (set_local $7
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (set_local $2
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
  )
  (loop $label$0
   (call $eosio_assert
    (i32.lt_u
     (get_local $8)
     (i32.load
      (get_local $7)
     )
    )
    (i32.const 704)
   )
   (set_local $3
    (i32.load8_u
     (tee_local $8
      (i32.load
       (get_local $2)
      )
     )
    )
   )
   (i32.store
    (get_local $2)
    (tee_local $8
     (i32.add
      (get_local $8)
      (i32.const 1)
     )
    )
   )
   (set_local $5
    (i64.or
     (i64.extend_u/i32
      (i32.shl
       (i32.and
        (get_local $3)
        (i32.const 127)
       )
       (tee_local $6
        (i32.and
         (get_local $6)
         (i32.const 255)
        )
       )
      )
     )
     (get_local $5)
    )
   )
   (set_local $6
    (i32.add
     (get_local $6)
     (i32.const 7)
    )
   )
   (br_if $label$0
    (i32.shr_u
     (get_local $3)
     (i32.const 7)
    )
   )
  )
  (block $label$1
   (br_if $label$1
    (i32.eqz
     (tee_local $3
      (i32.wrap/i64
       (get_local $5)
      )
     )
    )
   )
   (set_local $7
    (i32.add
     (get_local $3)
     (i32.const -1)
    )
   )
   (set_local $6
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 16)
     )
     (i32.const 8)
    )
   )
   (set_local $3
    (i32.add
     (get_local $0)
     (i32.const 4)
    )
   )
   (set_local $4
    (i32.add
     (get_local $9)
     (i32.const 56)
    )
   )
   (loop $label$2
    (i64.store
     (get_local $6)
     (i64.const 0)
    )
    (i64.store offset=16
     (get_local $9)
     (i64.const 0)
    )
    (call $eosio_assert
     (i32.gt_u
      (i32.sub
       (i32.load
        (tee_local $2
         (i32.add
          (get_local $0)
          (i32.const 8)
         )
        )
       )
       (get_local $8)
      )
      (i32.const 7)
     )
     (i32.const 688)
    )
    (drop
     (call $memcpy
      (i32.add
       (get_local $9)
       (i32.const 16)
      )
      (i32.load
       (get_local $3)
      )
      (i32.const 8)
     )
    )
    (i32.store
     (get_local $3)
     (tee_local $8
      (i32.add
       (i32.load
        (get_local $3)
       )
       (i32.const 8)
      )
     )
    )
    (call $eosio_assert
     (i32.gt_u
      (i32.sub
       (i32.load
        (get_local $2)
       )
       (get_local $8)
      )
      (i32.const 7)
     )
     (i32.const 688)
    )
    (drop
     (call $memcpy
      (get_local $6)
      (i32.load
       (get_local $3)
      )
      (i32.const 8)
     )
    )
    (i32.store
     (get_local $3)
     (tee_local $8
      (i32.add
       (i32.load
        (get_local $3)
       )
       (i32.const 8)
      )
     )
    )
    (call $eosio_assert
     (i32.gt_u
      (i32.sub
       (i32.load
        (get_local $2)
       )
       (get_local $8)
      )
      (i32.const 7)
     )
     (i32.const 688)
    )
    (drop
     (call $memcpy
      (i32.add
       (get_local $9)
       (i32.const 8)
      )
      (i32.load
       (get_local $3)
      )
      (i32.const 8)
     )
    )
    (i32.store
     (get_local $3)
     (i32.add
      (i32.load
       (get_local $3)
      )
      (i32.const 8)
     )
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 40)
      )
      (i32.const 8)
     )
     (i64.load
      (get_local $6)
     )
    )
    (i64.store offset=40
     (get_local $9)
     (i64.load offset=16
      (get_local $9)
     )
    )
    (i64.store
     (get_local $4)
     (i64.load offset=8
      (get_local $9)
     )
    )
    (call $_ZN5boost9container3dtl9flat_treeINS1_4pairIN5eosio15extended_symbolExEENS1_9select1stIS5_EENSt3__14lessIS5_EENS0_13new_allocatorIS6_EEE13insert_uniqueEOS6_
     (i32.add
      (get_local $9)
      (i32.const 32)
     )
     (get_local $1)
     (i32.add
      (get_local $9)
      (i32.const 40)
     )
    )
    (br_if $label$1
     (i32.eqz
      (get_local $7)
     )
    )
    (set_local $7
     (i32.add
      (get_local $7)
      (i32.const -1)
     )
    )
    (set_local $8
     (i32.load
      (get_local $3)
     )
    )
    (br $label$2)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 64)
   )
  )
  (get_local $0)
 )
 (func $_ZN5boost9container3dtl9flat_treeINS1_4pairIN5eosio15extended_symbolExEENS1_9select1stIS5_EENSt3__14lessIS5_EENS0_13new_allocatorIS6_EEE13insert_uniqueEOS6_ (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i64)
  (local $10 i32)
  (local $11 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $11
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i32.store8 offset=4
   (get_local $0)
   (i32.const 0)
  )
  (i32.store
   (get_local $0)
   (i32.const 0)
  )
  (set_local $5
   (i64.load
    (get_local $2)
   )
  )
  (set_local $6
   (tee_local $3
    (i32.load
     (get_local $1)
    )
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (tee_local $7
      (i32.div_s
       (i32.mul
        (tee_local $4
         (i32.load offset=4
          (get_local $1)
         )
        )
        (i32.const 24)
       )
       (i32.const 24)
      )
     )
    )
   )
   (loop $label$1
    (block $label$2
     (br_if $label$2
      (i64.ge_u
       (i64.load
        (tee_local $8
         (i32.add
          (get_local $6)
          (i32.mul
           (tee_local $10
            (i32.shr_u
             (get_local $7)
             (i32.const 1)
            )
           )
           (i32.const 24)
          )
         )
        )
       )
       (get_local $5)
      )
     )
     (set_local $6
      (i32.add
       (get_local $8)
       (i32.const 24)
      )
     )
     (set_local $10
      (i32.sub
       (i32.add
        (get_local $7)
        (i32.const -1)
       )
       (get_local $10)
      )
     )
    )
    (br_if $label$1
     (tee_local $7
      (get_local $10)
     )
    )
   )
  )
  (block $label$3
   (block $label$4
    (block $label$5
     (block $label$6
      (br_if $label$6
       (i32.eqz
        (tee_local $7
         (i32.ne
          (get_local $6)
          (tee_local $10
           (i32.add
            (get_local $3)
            (i32.mul
             (get_local $4)
             (i32.const 24)
            )
           )
          )
         )
        )
       )
      )
      (i32.store8
       (i32.add
        (get_local $0)
        (i32.const 4)
       )
       (i64.lt_u
        (get_local $5)
        (tee_local $9
         (i64.load
          (get_local $6)
         )
        )
       )
      )
      (br_if $label$5
       (i64.lt_u
        (get_local $5)
        (get_local $9)
       )
      )
      (br $label$4)
     )
     (i32.store8
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
      (i32.const 1)
     )
    )
    (i32.store offset=8
     (get_local $11)
     (get_local $6)
    )
    (block $label$7
     (br_if $label$7
      (i32.ne
       (i32.load offset=8
        (get_local $1)
       )
       (get_local $4)
      )
     )
     (call $_ZN5boost9container6vectorINS0_3dtl4pairIN5eosio15extended_symbolExEENS0_13new_allocatorIS6_EEvE37priv_forward_range_insert_no_capacityINS2_17insert_move_proxyIS8_PS6_EEEENS0_12vec_iteratorISC_Lb0EEERKSC_jT_NS_11move_detail17integral_constantIjLj1EEE
      (get_local $11)
      (get_local $1)
      (i32.add
       (get_local $11)
       (i32.const 8)
      )
      (i32.const 1)
      (get_local $2)
     )
     (set_local $6
      (i32.load
       (get_local $11)
      )
     )
     (br $label$3)
    )
    (set_local $8
     (i32.div_s
      (i32.sub
       (get_local $6)
       (get_local $3)
      )
      (i32.const 24)
     )
    )
    (block $label$8
     (block $label$9
      (br_if $label$9
       (i32.eqz
        (get_local $7)
       )
      )
      (i64.store
       (i32.add
        (get_local $10)
        (i32.const 8)
       )
       (i64.load
        (i32.add
         (get_local $10)
         (i32.const -16)
        )
       )
      )
      (i64.store
       (get_local $10)
       (i64.load
        (tee_local $7
         (i32.add
          (get_local $10)
          (i32.const -24)
         )
        )
       )
      )
      (i64.store offset=16
       (i32.add
        (get_local $3)
        (i32.mul
         (get_local $4)
         (i32.const 24)
        )
       )
       (i64.load
        (i32.add
         (get_local $10)
         (i32.const -8)
        )
       )
      )
      (i32.store
       (tee_local $10
        (i32.add
         (get_local $1)
         (i32.const 4)
        )
       )
       (i32.add
        (i32.load
         (get_local $10)
        )
        (i32.const 1)
       )
      )
      (block $label$10
       (br_if $label$10
        (i32.eq
         (get_local $7)
         (get_local $6)
        )
       )
       (loop $label$11
        (i64.store
         (i32.add
          (get_local $7)
          (i32.const 8)
         )
         (i64.load
          (i32.add
           (get_local $7)
           (i32.const -16)
          )
         )
        )
        (i64.store
         (get_local $7)
         (i64.load
          (tee_local $10
           (i32.add
            (get_local $7)
            (i32.const -24)
           )
          )
         )
        )
        (i64.store
         (i32.add
          (get_local $7)
          (i32.const 16)
         )
         (i64.load
          (i32.add
           (get_local $7)
           (i32.const -8)
          )
         )
        )
        (set_local $7
         (get_local $10)
        )
        (br_if $label$11
         (i32.ne
          (get_local $6)
          (get_local $10)
         )
        )
       )
      )
      (i64.store
       (get_local $6)
       (i64.load
        (get_local $2)
       )
      )
      (i64.store
       (i32.add
        (get_local $6)
        (i32.const 8)
       )
       (i64.load
        (i32.add
         (get_local $2)
         (i32.const 8)
        )
       )
      )
      (i64.store offset=16
       (get_local $6)
       (i64.load offset=16
        (get_local $2)
       )
      )
      (br $label$8)
     )
     (i64.store
      (get_local $6)
      (i64.load
       (get_local $2)
      )
     )
     (i64.store
      (i32.add
       (get_local $6)
       (i32.const 8)
      )
      (i64.load
       (i32.add
        (get_local $2)
        (i32.const 8)
       )
      )
     )
     (i64.store offset=16
      (i32.add
       (get_local $3)
       (i32.mul
        (get_local $4)
        (i32.const 24)
       )
      )
      (i64.load offset=16
       (get_local $2)
      )
     )
     (i32.store
      (tee_local $7
       (i32.add
        (get_local $1)
        (i32.const 4)
       )
      )
      (i32.add
       (i32.load
        (get_local $7)
       )
       (i32.const 1)
      )
     )
    )
    (set_local $6
     (i32.add
      (i32.load
       (get_local $1)
      )
      (i32.mul
       (get_local $8)
       (i32.const 24)
      )
     )
    )
   )
   (i32.store
    (get_local $11)
    (get_local $6)
   )
  )
  (i32.store
   (get_local $0)
   (get_local $6)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $11)
    (i32.const 16)
   )
  )
 )
 (func $_ZN5boost9container6vectorINS0_3dtl4pairIyN5eosio11multi_indexILy6290548272952901632ENS4_9exaccountEJEEEEENS0_13new_allocatorIS8_EEvE40priv_forward_range_insert_new_allocationINS2_17insert_move_proxyISA_PS8_EEEEvSE_jSE_jT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (param $4 i32) (param $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (local $12 i32)
  (set_local $11
   (get_local $1)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $10
      (i32.load
       (get_local $0)
      )
     )
     (get_local $3)
    )
   )
   (set_local $11
    (get_local $1)
   )
   (br_if $label$0
    (i32.eqz
     (get_local $10)
    )
   )
   (set_local $6
    (get_local $10)
   )
   (set_local $11
    (get_local $1)
   )
   (loop $label$1
    (i64.store
     (get_local $11)
     (i64.load
      (get_local $6)
     )
    )
    (i64.store
     (i32.add
      (get_local $11)
      (i32.const 24)
     )
     (i64.load
      (i32.add
       (get_local $6)
       (i32.const 24)
      )
     )
    )
    (i64.store
     (i32.add
      (get_local $11)
      (i32.const 16)
     )
     (i64.load
      (i32.add
       (get_local $6)
       (i32.const 16)
      )
     )
    )
    (i64.store
     (i32.add
      (get_local $11)
      (i32.const 8)
     )
     (i64.load
      (i32.add
       (get_local $6)
       (i32.const 8)
      )
     )
    )
    (i32.store
     (tee_local $12
      (i32.add
       (get_local $11)
       (i32.const 32)
      )
     )
     (i32.const 0)
    )
    (i32.store
     (tee_local $9
      (i32.add
       (get_local $11)
       (i32.const 36)
      )
     )
     (i32.const 0)
    )
    (i32.store
     (tee_local $7
      (i32.add
       (get_local $11)
       (i32.const 40)
      )
     )
     (i32.const 0)
    )
    (i32.store
     (get_local $12)
     (i32.load
      (tee_local $8
       (i32.add
        (get_local $6)
        (i32.const 32)
       )
      )
     )
    )
    (i32.store
     (get_local $9)
     (i32.load
      (i32.add
       (get_local $6)
       (i32.const 36)
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.load
      (tee_local $12
       (i32.add
        (get_local $6)
        (i32.const 40)
       )
      )
     )
    )
    (i32.store
     (get_local $12)
     (i32.const 0)
    )
    (i64.store align=4
     (get_local $8)
     (i64.const 0)
    )
    (set_local $11
     (i32.add
      (get_local $11)
      (i32.const 48)
     )
    )
    (br_if $label$1
     (i32.ne
      (tee_local $6
       (i32.add
        (get_local $6)
        (i32.const 48)
       )
      )
      (get_local $3)
     )
    )
   )
  )
  (i64.store
   (get_local $11)
   (i64.load
    (get_local $5)
   )
  )
  (i64.store
   (i32.add
    (get_local $11)
    (i32.const 24)
   )
   (i64.load
    (i32.add
     (get_local $5)
     (i32.const 24)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $11)
    (i32.const 16)
   )
   (i64.load
    (i32.add
     (get_local $5)
     (i32.const 16)
    )
   )
  )
  (i64.store offset=8
   (get_local $11)
   (i64.load offset=8
    (get_local $5)
   )
  )
  (i32.store
   (tee_local $6
    (i32.add
     (get_local $11)
     (i32.const 32)
    )
   )
   (i32.const 0)
  )
  (i32.store
   (tee_local $12
    (i32.add
     (get_local $11)
     (i32.const 36)
    )
   )
   (i32.const 0)
  )
  (i32.store
   (tee_local $9
    (i32.add
     (get_local $11)
     (i32.const 40)
    )
   )
   (i32.const 0)
  )
  (i32.store
   (get_local $6)
   (i32.load
    (tee_local $7
     (i32.add
      (get_local $5)
      (i32.const 32)
     )
    )
   )
  )
  (i32.store
   (get_local $12)
   (i32.load
    (i32.add
     (get_local $5)
     (i32.const 36)
    )
   )
  )
  (i32.store
   (get_local $9)
   (i32.load
    (tee_local $6
     (i32.add
      (get_local $5)
      (i32.const 40)
     )
    )
   )
  )
  (i32.store
   (get_local $6)
   (i32.const 0)
  )
  (i64.store align=4
   (get_local $7)
   (i64.const 0)
  )
  (set_local $12
   (i32.add
    (get_local $11)
    (i32.mul
     (get_local $4)
     (i32.const 48)
    )
   )
  )
  (block $label$2
   (br_if $label$2
    (i32.eqz
     (get_local $10)
    )
   )
   (block $label$3
    (br_if $label$3
     (i32.eq
      (tee_local $8
       (i32.add
        (get_local $10)
        (i32.mul
         (tee_local $9
          (i32.load
           (i32.add
            (get_local $0)
            (i32.const 4)
           )
          )
         )
         (i32.const 48)
        )
       )
      )
      (get_local $3)
     )
    )
    (loop $label$4
     (i64.store
      (get_local $12)
      (i64.load
       (get_local $3)
      )
     )
     (i64.store
      (i32.add
       (get_local $12)
       (i32.const 24)
      )
      (i64.load
       (i32.add
        (get_local $3)
        (i32.const 24)
       )
      )
     )
     (i64.store
      (i32.add
       (get_local $12)
       (i32.const 16)
      )
      (i64.load
       (i32.add
        (get_local $3)
        (i32.const 16)
       )
      )
     )
     (i64.store
      (i32.add
       (get_local $12)
       (i32.const 8)
      )
      (i64.load
       (i32.add
        (get_local $3)
        (i32.const 8)
       )
      )
     )
     (i32.store
      (tee_local $11
       (i32.add
        (get_local $12)
        (i32.const 32)
       )
      )
      (i32.const 0)
     )
     (i32.store
      (tee_local $6
       (i32.add
        (get_local $12)
        (i32.const 36)
       )
      )
      (i32.const 0)
     )
     (i32.store
      (tee_local $9
       (i32.add
        (get_local $12)
        (i32.const 40)
       )
      )
      (i32.const 0)
     )
     (i32.store
      (get_local $11)
      (i32.load
       (tee_local $7
        (i32.add
         (get_local $3)
         (i32.const 32)
        )
       )
      )
     )
     (i32.store
      (get_local $6)
      (i32.load
       (i32.add
        (get_local $3)
        (i32.const 36)
       )
      )
     )
     (i32.store
      (get_local $9)
      (i32.load
       (tee_local $11
        (i32.add
         (get_local $3)
         (i32.const 40)
        )
       )
      )
     )
     (i32.store
      (get_local $11)
      (i32.const 0)
     )
     (i64.store align=4
      (get_local $7)
      (i64.const 0)
     )
     (set_local $12
      (i32.add
       (get_local $12)
       (i32.const 48)
      )
     )
     (br_if $label$4
      (i32.ne
       (tee_local $3
        (i32.add
         (get_local $3)
         (i32.const 48)
        )
       )
       (get_local $8)
      )
     )
    )
    (set_local $9
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
   )
   (block $label$5
    (br_if $label$5
     (i32.eqz
      (get_local $9)
     )
    )
    (loop $label$6
     (set_local $9
      (i32.add
       (get_local $9)
       (i32.const -1)
      )
     )
     (block $label$7
      (br_if $label$7
       (i32.eqz
        (tee_local $3
         (i32.load
          (tee_local $7
           (i32.add
            (get_local $10)
            (i32.const 32)
           )
          )
         )
        )
       )
      )
      (block $label$8
       (block $label$9
        (br_if $label$9
         (i32.eq
          (tee_local $11
           (i32.load
            (tee_local $8
             (i32.add
              (get_local $10)
              (i32.const 36)
             )
            )
           )
          )
          (get_local $3)
         )
        )
        (loop $label$10
         (set_local $6
          (i32.load
           (tee_local $11
            (i32.add
             (get_local $11)
             (i32.const -24)
            )
           )
          )
         )
         (i32.store
          (get_local $11)
          (i32.const 0)
         )
         (block $label$11
          (br_if $label$11
           (i32.eqz
            (get_local $6)
           )
          )
          (block $label$12
           (br_if $label$12
            (i32.eqz
             (i32.load
              (i32.add
               (get_local $6)
               (i32.const 16)
              )
             )
            )
           )
           (call $_ZdlPv
            (i32.load offset=8
             (get_local $6)
            )
           )
          )
          (call $_ZdlPv
           (get_local $6)
          )
         )
         (br_if $label$10
          (i32.ne
           (get_local $3)
           (get_local $11)
          )
         )
        )
        (set_local $11
         (i32.load
          (get_local $7)
         )
        )
        (br $label$8)
       )
       (set_local $11
        (get_local $3)
       )
      )
      (i32.store
       (get_local $8)
       (get_local $3)
      )
      (call $_ZdlPv
       (get_local $11)
      )
     )
     (set_local $10
      (i32.add
       (get_local $10)
       (i32.const 48)
      )
     )
     (br_if $label$6
      (get_local $9)
     )
    )
   )
   (call $_ZdlPv
    (i32.load
     (get_local $0)
    )
   )
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store offset=8
   (get_local $0)
   (get_local $2)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (i32.div_s
    (i32.sub
     (get_local $12)
     (get_local $1)
    )
    (i32.const 48)
   )
  )
 )
 (func $_ZN5boost9container6vectorINS0_3dtl4pairIyN5eosio11multi_indexILy6290548272952901632ENS4_9exaccountEJEEEEENS0_13new_allocatorIS8_EEvE40priv_forward_range_insert_expand_forwardINS2_17insert_move_proxyISA_PS8_EEEEvSE_jT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (local $12 i32)
  (local $13 i32)
  (local $14 i32)
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (get_local $2)
    )
   )
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (block $label$6
         (block $label$7
          (block $label$8
           (block $label$9
            (block $label$10
             (br_if $label$10
              (i32.eqz
               (tee_local $13
                (i32.sub
                 (tee_local $11
                  (i32.add
                   (tee_local $4
                    (i32.load
                     (get_local $0)
                    )
                   )
                   (i32.mul
                    (tee_local $6
                     (i32.load offset=4
                      (get_local $0)
                     )
                    )
                    (i32.const 48)
                   )
                  )
                 )
                 (get_local $1)
                )
               )
              )
             )
             (br_if $label$9
              (i32.ge_u
               (i32.div_s
                (get_local $13)
                (i32.const 48)
               )
               (get_local $2)
              )
             )
             (block $label$11
              (br_if $label$11
               (i32.eq
                (get_local $11)
                (get_local $1)
               )
              )
              (set_local $9
               (i32.sub
                (i32.sub
                 (i32.const 0)
                 (get_local $4)
                )
                (i32.mul
                 (get_local $6)
                 (i32.const 48)
                )
               )
              )
              (set_local $10
               (i32.mul
                (get_local $2)
                (i32.const 48)
               )
              )
              (set_local $13
               (i32.add
                (get_local $1)
                (i32.const 40)
               )
              )
              (loop $label$12
               (i64.store
                (i32.add
                 (tee_local $8
                  (i32.add
                   (get_local $13)
                   (get_local $10)
                  )
                 )
                 (i32.const -40)
                )
                (i64.load
                 (i32.add
                  (get_local $13)
                  (i32.const -40)
                 )
                )
               )
               (i32.store
                (i32.add
                 (get_local $8)
                 (i32.const -28)
                )
                (i32.load
                 (i32.add
                  (get_local $13)
                  (i32.const -28)
                 )
                )
               )
               (i32.store
                (i32.add
                 (get_local $8)
                 (i32.const -32)
                )
                (i32.load
                 (i32.add
                  (get_local $13)
                  (i32.const -32)
                 )
                )
               )
               (i64.store
                (i32.add
                 (get_local $8)
                 (i32.const -16)
                )
                (i64.load
                 (i32.add
                  (get_local $13)
                  (i32.const -16)
                 )
                )
               )
               (i64.store
                (i32.add
                 (get_local $8)
                 (i32.const -24)
                )
                (i64.load
                 (i32.add
                  (get_local $13)
                  (i32.const -24)
                 )
                )
               )
               (i32.store
                (tee_local $7
                 (i32.add
                  (get_local $8)
                  (i32.const -8)
                 )
                )
                (i32.const 0)
               )
               (i32.store
                (tee_local $12
                 (i32.add
                  (get_local $8)
                  (i32.const -4)
                 )
                )
                (i32.const 0)
               )
               (i32.store
                (get_local $8)
                (i32.const 0)
               )
               (i32.store
                (get_local $7)
                (i32.load
                 (tee_local $14
                  (i32.add
                   (get_local $13)
                   (i32.const -8)
                  )
                 )
                )
               )
               (i32.store
                (get_local $12)
                (i32.load
                 (tee_local $7
                  (i32.add
                   (get_local $13)
                   (i32.const -4)
                  )
                 )
                )
               )
               (i32.store
                (get_local $8)
                (i32.load
                 (get_local $13)
                )
               )
               (i32.store
                (get_local $14)
                (i32.const 0)
               )
               (i32.store
                (get_local $7)
                (i32.const 0)
               )
               (i32.store
                (get_local $13)
                (i32.const 0)
               )
               (br_if $label$12
                (i32.ne
                 (i32.add
                  (tee_local $13
                   (i32.add
                    (get_local $13)
                    (i32.const 48)
                   )
                  )
                  (get_local $9)
                 )
                 (i32.const 40)
                )
               )
              )
             )
             (i64.store
              (get_local $1)
              (i64.load
               (get_local $3)
              )
             )
             (i64.store
              (i32.add
               (get_local $1)
               (i32.const 24)
              )
              (i64.load
               (i32.add
                (get_local $3)
                (i32.const 24)
               )
              )
             )
             (i64.store
              (i32.add
               (get_local $1)
               (i32.const 16)
              )
              (i64.load
               (i32.add
                (get_local $3)
                (i32.const 16)
               )
              )
             )
             (i64.store offset=8
              (get_local $1)
              (i64.load offset=8
               (get_local $3)
              )
             )
             (set_local $12
              (i32.add
               (get_local $3)
               (i32.const 8)
              )
             )
             (br_if $label$8
              (i32.eqz
               (tee_local $7
                (i32.load
                 (i32.add
                  (get_local $1)
                  (i32.const 32)
                 )
                )
               )
              )
             )
             (br_if $label$6
              (i32.eq
               (tee_local $13
                (i32.load
                 (tee_local $9
                  (i32.add
                   (get_local $1)
                   (i32.const 36)
                  )
                 )
                )
               )
               (get_local $7)
              )
             )
             (loop $label$13
              (set_local $8
               (i32.load
                (tee_local $13
                 (i32.add
                  (get_local $13)
                  (i32.const -24)
                 )
                )
               )
              )
              (i32.store
               (get_local $13)
               (i32.const 0)
              )
              (block $label$14
               (br_if $label$14
                (i32.eqz
                 (get_local $8)
                )
               )
               (block $label$15
                (br_if $label$15
                 (i32.eqz
                  (i32.load
                   (i32.add
                    (get_local $8)
                    (i32.const 16)
                   )
                  )
                 )
                )
                (call $_ZdlPv
                 (i32.load offset=8
                  (get_local $8)
                 )
                )
               )
               (call $_ZdlPv
                (get_local $8)
               )
              )
              (br_if $label$13
               (i32.ne
                (get_local $7)
                (get_local $13)
               )
              )
             )
             (set_local $13
              (i32.load
               (i32.add
                (get_local $1)
                (i32.const 32)
               )
              )
             )
             (br $label$5)
            )
            (i64.store
             (get_local $11)
             (i64.load
              (get_local $3)
             )
            )
            (i64.store
             (i32.add
              (get_local $11)
              (i32.const 24)
             )
             (i64.load
              (i32.add
               (get_local $3)
               (i32.const 24)
              )
             )
            )
            (i64.store
             (i32.add
              (get_local $11)
              (i32.const 16)
             )
             (i64.load
              (i32.add
               (get_local $3)
               (i32.const 16)
              )
             )
            )
            (i64.store offset=8
             (get_local $11)
             (i64.load offset=8
              (get_local $3)
             )
            )
            (i32.store
             (tee_local $13
              (i32.add
               (get_local $11)
               (i32.const 32)
              )
             )
             (i32.const 0)
            )
            (i32.store
             (tee_local $8
              (i32.add
               (get_local $11)
               (i32.const 36)
              )
             )
             (i32.const 0)
            )
            (i32.store
             (tee_local $7
              (i32.add
               (get_local $11)
               (i32.const 40)
              )
             )
             (i32.const 0)
            )
            (i32.store
             (get_local $13)
             (i32.load
              (tee_local $11
               (i32.add
                (get_local $3)
                (i32.const 32)
               )
              )
             )
            )
            (i32.store
             (get_local $8)
             (i32.load
              (i32.add
               (get_local $3)
               (i32.const 36)
              )
             )
            )
            (i32.store
             (get_local $7)
             (i32.load
              (tee_local $13
               (i32.add
                (get_local $3)
                (i32.const 40)
               )
              )
             )
            )
            (i32.store
             (get_local $13)
             (i32.const 0)
            )
            (i64.store align=4
             (get_local $11)
             (i64.const 0)
            )
            (i32.store
             (tee_local $13
              (i32.add
               (get_local $0)
               (i32.const 4)
              )
             )
             (i32.add
              (i32.load
               (get_local $13)
              )
              (get_local $2)
             )
            )
            (return)
           )
           (set_local $6
            (i32.add
             (i32.add
              (get_local $4)
              (tee_local $13
               (i32.mul
                (i32.sub
                 (i32.const 0)
                 (get_local $2)
                )
                (i32.const 48)
               )
              )
             )
             (tee_local $8
              (i32.mul
               (get_local $6)
               (i32.const 48)
              )
             )
            )
           )
           (set_local $5
            (i32.mul
             (get_local $2)
             (i32.const 48)
            )
           )
           (set_local $4
            (i32.add
             (get_local $4)
             (get_local $8)
            )
           )
           (set_local $12
            (i32.add
             (get_local $11)
             (get_local $13)
            )
           )
           (set_local $7
            (i32.const 0)
           )
           (loop $label$16
            (i64.store
             (tee_local $13
              (i32.add
               (get_local $4)
               (get_local $7)
              )
             )
             (i64.load
              (tee_local $8
               (i32.add
                (get_local $6)
                (get_local $7)
               )
              )
             )
            )
            (i32.store
             (i32.add
              (get_local $13)
              (i32.const 12)
             )
             (i32.load
              (i32.add
               (get_local $8)
               (i32.const 12)
              )
             )
            )
            (i32.store
             (i32.add
              (get_local $13)
              (i32.const 8)
             )
             (i32.load
              (i32.add
               (get_local $8)
               (i32.const 8)
              )
             )
            )
            (i64.store
             (i32.add
              (get_local $13)
              (i32.const 24)
             )
             (i64.load
              (i32.add
               (get_local $8)
               (i32.const 24)
              )
             )
            )
            (i64.store
             (i32.add
              (get_local $13)
              (i32.const 16)
             )
             (i64.load
              (i32.add
               (get_local $8)
               (i32.const 16)
              )
             )
            )
            (i32.store
             (tee_local $14
              (i32.add
               (get_local $13)
               (i32.const 32)
              )
             )
             (i32.const 0)
            )
            (i32.store
             (tee_local $9
              (i32.add
               (get_local $13)
               (i32.const 36)
              )
             )
             (i32.const 0)
            )
            (i32.store
             (tee_local $13
              (i32.add
               (get_local $13)
               (i32.const 40)
              )
             )
             (i32.const 0)
            )
            (i32.store
             (get_local $14)
             (i32.load
              (tee_local $10
               (i32.add
                (get_local $8)
                (i32.const 32)
               )
              )
             )
            )
            (i32.store
             (get_local $9)
             (i32.load
              (tee_local $14
               (i32.add
                (get_local $8)
                (i32.const 36)
               )
              )
             )
            )
            (i32.store
             (get_local $13)
             (i32.load
              (tee_local $8
               (i32.add
                (get_local $8)
                (i32.const 40)
               )
              )
             )
            )
            (i32.store
             (get_local $8)
             (i32.const 0)
            )
            (i32.store
             (get_local $10)
             (i32.const 0)
            )
            (i32.store
             (get_local $14)
             (i32.const 0)
            )
            (br_if $label$16
             (i32.ne
              (get_local $5)
              (tee_local $7
               (i32.add
                (get_local $7)
                (i32.const 48)
               )
              )
             )
            )
           )
           (i32.store
            (tee_local $13
             (i32.add
              (get_local $0)
              (i32.const 4)
             )
            )
            (i32.add
             (i32.load
              (get_local $13)
             )
             (get_local $2)
            )
           )
           (block $label$17
            (br_if $label$17
             (i32.eq
              (get_local $12)
              (get_local $1)
             )
            )
            (loop $label$18
             (i64.store
              (tee_local $5
               (i32.add
                (get_local $11)
                (i32.const -48)
               )
              )
              (i64.load
               (tee_local $10
                (i32.add
                 (get_local $12)
                 (i32.const -48)
                )
               )
              )
             )
             (i64.store
              (i32.add
               (get_local $11)
               (i32.const -24)
              )
              (i64.load
               (i32.add
                (get_local $12)
                (i32.const -24)
               )
              )
             )
             (i64.store
              (i32.add
               (get_local $11)
               (i32.const -32)
              )
              (i64.load
               (i32.add
                (get_local $12)
                (i32.const -32)
               )
              )
             )
             (i64.store
              (i32.add
               (get_local $11)
               (i32.const -40)
              )
              (i64.load
               (i32.add
                (get_local $12)
                (i32.const -40)
               )
              )
             )
             (set_local $6
              (i32.add
               (get_local $12)
               (i32.const -16)
              )
             )
             (block $label$19
              (block $label$20
               (block $label$21
                (block $label$22
                 (br_if $label$22
                  (i32.eqz
                   (tee_local $7
                    (i32.load
                     (tee_local $9
                      (i32.add
                       (get_local $11)
                       (i32.const -16)
                      )
                     )
                    )
                   )
                  )
                 )
                 (br_if $label$21
                  (i32.eq
                   (tee_local $13
                    (i32.load
                     (tee_local $14
                      (i32.add
                       (get_local $11)
                       (i32.const -12)
                      )
                     )
                    )
                   )
                   (get_local $7)
                  )
                 )
                 (loop $label$23
                  (set_local $8
                   (i32.load
                    (tee_local $13
                     (i32.add
                      (get_local $13)
                      (i32.const -24)
                     )
                    )
                   )
                  )
                  (i32.store
                   (get_local $13)
                   (i32.const 0)
                  )
                  (block $label$24
                   (br_if $label$24
                    (i32.eqz
                     (get_local $8)
                    )
                   )
                   (block $label$25
                    (br_if $label$25
                     (i32.eqz
                      (i32.load
                       (i32.add
                        (get_local $8)
                        (i32.const 16)
                       )
                      )
                     )
                    )
                    (call $_ZdlPv
                     (i32.load offset=8
                      (get_local $8)
                     )
                    )
                   )
                   (call $_ZdlPv
                    (get_local $8)
                   )
                  )
                  (br_if $label$23
                   (i32.ne
                    (get_local $7)
                    (get_local $13)
                   )
                  )
                 )
                 (set_local $13
                  (i32.load
                   (get_local $9)
                  )
                 )
                 (br $label$20)
                )
                (set_local $8
                 (i32.add
                  (get_local $11)
                  (i32.const -8)
                 )
                )
                (set_local $14
                 (i32.add
                  (get_local $11)
                  (i32.const -12)
                 )
                )
                (br $label$19)
               )
               (set_local $13
                (get_local $7)
               )
              )
              (i32.store
               (get_local $14)
               (get_local $7)
              )
              (call $_ZdlPv
               (get_local $13)
              )
              (i32.store
               (get_local $14)
               (i32.const 0)
              )
              (i32.store
               (tee_local $8
                (i32.add
                 (get_local $11)
                 (i32.const -8)
                )
               )
               (i32.const 0)
              )
              (i32.store
               (get_local $9)
               (i32.const 0)
              )
             )
             (i32.store
              (get_local $9)
              (i32.load
               (get_local $6)
              )
             )
             (i32.store
              (get_local $14)
              (i32.load
               (tee_local $13
                (i32.add
                 (get_local $12)
                 (i32.const -12)
                )
               )
              )
             )
             (i32.store
              (get_local $8)
              (i32.load
               (i32.add
                (get_local $12)
                (i32.const -8)
               )
              )
             )
             (i32.store
              (get_local $6)
              (i32.const 0)
             )
             (i64.store align=4
              (get_local $13)
              (i64.const 0)
             )
             (set_local $11
              (get_local $5)
             )
             (set_local $12
              (get_local $10)
             )
             (br_if $label$18
              (i32.ne
               (get_local $10)
               (get_local $1)
              )
             )
            )
           )
           (i64.store
            (get_local $1)
            (i64.load
             (get_local $3)
            )
           )
           (i64.store
            (i32.add
             (get_local $1)
             (i32.const 24)
            )
            (i64.load
             (i32.add
              (get_local $3)
              (i32.const 24)
             )
            )
           )
           (i64.store
            (i32.add
             (get_local $1)
             (i32.const 16)
            )
            (i64.load
             (i32.add
              (get_local $3)
              (i32.const 16)
             )
            )
           )
           (i64.store offset=8
            (get_local $1)
            (i64.load offset=8
             (get_local $3)
            )
           )
           (br_if $label$7
            (i32.eqz
             (tee_local $7
              (i32.load
               (i32.add
                (get_local $1)
                (i32.const 32)
               )
              )
             )
            )
           )
           (br_if $label$3
            (i32.eq
             (tee_local $13
              (i32.load
               (tee_local $11
                (i32.add
                 (get_local $1)
                 (i32.const 36)
                )
               )
              )
             )
             (get_local $7)
            )
           )
           (loop $label$26
            (set_local $8
             (i32.load
              (tee_local $13
               (i32.add
                (get_local $13)
                (i32.const -24)
               )
              )
             )
            )
            (i32.store
             (get_local $13)
             (i32.const 0)
            )
            (block $label$27
             (br_if $label$27
              (i32.eqz
               (get_local $8)
              )
             )
             (block $label$28
              (br_if $label$28
               (i32.eqz
                (i32.load
                 (i32.add
                  (get_local $8)
                  (i32.const 16)
                 )
                )
               )
              )
              (call $_ZdlPv
               (i32.load offset=8
                (get_local $8)
               )
              )
             )
             (call $_ZdlPv
              (get_local $8)
             )
            )
            (br_if $label$26
             (i32.ne
              (get_local $7)
              (get_local $13)
             )
            )
           )
           (set_local $13
            (i32.load
             (i32.add
              (get_local $1)
              (i32.const 32)
             )
            )
           )
           (br $label$2)
          )
          (set_local $13
           (i32.add
            (get_local $1)
            (i32.const 40)
           )
          )
          (set_local $9
           (i32.add
            (get_local $1)
            (i32.const 36)
           )
          )
          (br $label$4)
         )
         (set_local $7
          (i32.add
           (get_local $1)
           (i32.const 40)
          )
         )
         (set_local $11
          (i32.add
           (get_local $1)
           (i32.const 36)
          )
         )
         (br $label$1)
        )
        (set_local $13
         (get_local $7)
        )
       )
       (i32.store
        (i32.add
         (get_local $1)
         (i32.const 36)
        )
        (get_local $7)
       )
       (call $_ZdlPv
        (get_local $13)
       )
       (i32.store
        (tee_local $13
         (i32.add
          (get_local $1)
          (i32.const 40)
         )
        )
        (i32.const 0)
       )
       (i64.store align=4
        (i32.add
         (get_local $1)
         (i32.const 32)
        )
        (i64.const 0)
       )
      )
      (i32.store
       (i32.add
        (get_local $1)
        (i32.const 32)
       )
       (i32.load
        (tee_local $8
         (i32.add
          (get_local $3)
          (i32.const 32)
         )
        )
       )
      )
      (i32.store
       (get_local $9)
       (i32.load
        (tee_local $14
         (i32.add
          (get_local $3)
          (i32.const 36)
         )
        )
       )
      )
      (i32.store
       (get_local $13)
       (i32.load
        (tee_local $7
         (i32.add
          (get_local $3)
          (i32.const 40)
         )
        )
       )
      )
      (i32.store
       (get_local $7)
       (i32.const 0)
      )
      (i64.store align=4
       (get_local $8)
       (i64.const 0)
      )
      (i64.store
       (get_local $11)
       (i64.load
        (get_local $3)
       )
      )
      (i64.store
       (i32.add
        (tee_local $13
         (i32.add
          (get_local $4)
          (i32.mul
           (get_local $6)
           (i32.const 48)
          )
         )
        )
        (i32.const 24)
       )
       (i64.load
        (i32.add
         (get_local $12)
         (i32.const 16)
        )
       )
      )
      (i64.store
       (i32.add
        (get_local $13)
        (i32.const 16)
       )
       (i64.load
        (i32.add
         (get_local $12)
         (i32.const 8)
        )
       )
      )
      (i64.store offset=8
       (get_local $13)
       (i64.load
        (get_local $12)
       )
      )
      (i32.store
       (tee_local $11
        (i32.add
         (get_local $13)
         (i32.const 32)
        )
       )
       (i32.const 0)
      )
      (i32.store
       (tee_local $12
        (i32.add
         (get_local $13)
         (i32.const 36)
        )
       )
       (i32.const 0)
      )
      (i32.store
       (tee_local $13
        (i32.add
         (get_local $13)
         (i32.const 40)
        )
       )
       (i32.const 0)
      )
      (i32.store
       (get_local $11)
       (i32.load
        (get_local $8)
       )
      )
      (i32.store
       (get_local $12)
       (i32.load
        (get_local $14)
       )
      )
      (i32.store
       (get_local $13)
       (i32.load
        (get_local $7)
       )
      )
      (i32.store
       (get_local $7)
       (i32.const 0)
      )
      (i64.store align=4
       (get_local $8)
       (i64.const 0)
      )
      (i32.store
       (tee_local $13
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
       (i32.add
        (i32.load
         (get_local $13)
        )
        (get_local $2)
       )
      )
      (return)
     )
     (set_local $13
      (get_local $7)
     )
    )
    (i32.store
     (i32.add
      (get_local $1)
      (i32.const 36)
     )
     (get_local $7)
    )
    (call $_ZdlPv
     (get_local $13)
    )
    (i32.store
     (tee_local $7
      (i32.add
       (get_local $1)
       (i32.const 40)
      )
     )
     (i32.const 0)
    )
    (i64.store align=4
     (i32.add
      (get_local $1)
      (i32.const 32)
     )
     (i64.const 0)
    )
   )
   (i32.store
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.load
     (tee_local $13
      (i32.add
       (get_local $3)
       (i32.const 32)
      )
     )
    )
   )
   (i32.store
    (get_local $11)
    (i32.load
     (i32.add
      (get_local $3)
      (i32.const 36)
     )
    )
   )
   (i32.store
    (get_local $7)
    (i32.load
     (tee_local $8
      (i32.add
       (get_local $3)
       (i32.const 40)
      )
     )
    )
   )
   (i32.store
    (get_local $8)
    (i32.const 0)
   )
   (i64.store align=4
    (get_local $13)
    (i64.const 0)
   )
  )
 )
 (func $_ZN5eosio12market_stateC2EyNS_11symbol_typeERNS_17exchange_accountsE (param $0 i32) (param $1 i64) (param $2 i64) (param $3 i32) (result i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i64)
  (i64.store
   (get_local $0)
   (i64.shr_u
    (get_local $2)
    (i64.const 8)
   )
  )
  (set_local $4
   (call $_ZN5eosio14exchange_stateC2Ev
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=240
   (get_local $0)
   (get_local $1)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 256)
   )
   (i64.const -1)
  )
  (i64.store align=4
   (i32.add
    (get_local $0)
    (i32.const 264)
   )
   (i64.const 0)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 272)
   )
   (i32.const 0)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 248)
   )
   (tee_local $2
    (i64.load
     (get_local $0)
    )
   )
  )
  (i64.store offset=280
   (get_local $0)
   (get_local $1)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 288)
   )
   (tee_local $6
    (i64.or
     (tee_local $5
      (i64.shl
       (get_local $2)
       (i64.const 4)
      )
     )
     (i64.const 1)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 296)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 304)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 308)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 312)
   )
   (i32.const 0)
  )
  (i32.store8
   (i32.add
    (get_local $0)
    (i32.const 316)
   )
   (i32.const 0)
  )
  (i64.store offset=320
   (get_local $0)
   (get_local $1)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 328)
   )
   (tee_local $5
    (i64.or
     (get_local $5)
     (i64.const 2)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 336)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 344)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 348)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 352)
   )
   (i32.const 0)
  )
  (i32.store8
   (i32.add
    (get_local $0)
    (i32.const 356)
   )
   (i32.const 0)
  )
  (i64.store offset=360
   (get_local $0)
   (get_local $1)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 368)
   )
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 376)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 384)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 388)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 392)
   )
   (i32.const 0)
  )
  (i64.store offset=400
   (get_local $0)
   (get_local $1)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 408)
   )
   (get_local $5)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 416)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 424)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 428)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 432)
   )
   (i32.const 0)
  )
  (i32.store offset=440
   (get_local $0)
   (get_local $3)
  )
  (call $_ZNK5eosio11multi_indexILy10497615196363685888ENS_14exchange_stateEJEE4findEy
   (i32.add
    (get_local $0)
    (i32.const 444)
   )
   (i32.add
    (get_local $0)
    (i32.const 240)
   )
   (get_local $2)
  )
  (call $eosio_assert
   (i32.ne
    (i32.load
     (tee_local $3
      (i32.add
       (get_local $0)
       (i32.const 448)
      )
     )
    )
    (i32.const 0)
   )
   (i32.const 720)
  )
  (drop
   (call $memcpy
    (get_local $4)
    (i32.load
     (get_local $3)
    )
    (i32.const 232)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio14exchange_stateC2Ev (param $0 i32) (result i32)
  (local $1 i64)
  (local $2 i32)
  (local $3 i32)
  (i64.store offset=8
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (tee_local $2
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
   )
   (i64.const 1398362884)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load
     (get_local $2)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (i64.store offset=40
   (get_local $0)
   (i64.const 0)
  )
  (i32.store offset=32
   (get_local $0)
   (i32.const 0)
  )
  (i64.store
   (tee_local $2
    (i32.add
     (get_local $0)
     (i32.const 48)
    )
   )
   (i64.const 1398362884)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load
     (get_local $2)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$5
   (block $label$6
    (loop $label$7
     (br_if $label$6
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$8
      (br_if $label$8
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$9
       (br_if $label$6
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$9
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$7
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$5)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 64)
   )
   (i32.const 500)
  )
  (drop
   (call $_ZN5eosio12margin_stateC2Ev
    (i32.add
     (get_local $0)
     (i32.const 72)
    )
   )
  )
  (i64.store
   (tee_local $2
    (i32.add
     (get_local $0)
     (i32.const 144)
    )
   )
   (i64.const 1398362884)
  )
  (i64.store offset=136
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load
     (get_local $2)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$10
   (block $label$11
    (loop $label$12
     (br_if $label$11
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$13
      (br_if $label$13
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$14
       (br_if $label$11
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$14
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$12
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$10)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 160)
   )
   (i32.const 500)
  )
  (drop
   (call $_ZN5eosio12margin_stateC2Ev
    (i32.add
     (get_local $0)
     (i32.const 168)
    )
   )
  )
  (get_local $0)
 )
 (func $_ZNK5eosio11multi_indexILy10497615196363685888ENS_14exchange_stateEJEE4findEy (param $0 i32) (param $1 i32) (param $2 i64)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $1)
        (i32.const 28)
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $1)
      )
     )
    )
   )
   (set_local $4
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i64.eq
      (i64.shr_u
       (i64.load
        (i32.add
         (i32.load
          (get_local $6)
         )
         (i32.const 16)
        )
       )
       (i64.const 8)
      )
      (get_local $2)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $5
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $5)
       (get_local $4)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (br_if $label$2
    (i32.eq
     (get_local $7)
     (get_local $3)
    )
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=232
      (tee_local $6
       (i32.load
        (i32.add
         (get_local $7)
         (i32.const -24)
        )
       )
      )
     )
     (get_local $1)
    )
    (i32.const 224)
   )
   (i32.store offset=4
    (get_local $0)
    (get_local $6)
   )
   (i32.store
    (get_local $0)
    (get_local $1)
   )
   (return)
  )
  (block $label$3
   (br_if $label$3
    (i32.le_s
     (tee_local $6
      (call $db_find_i64
       (i64.load
        (get_local $1)
       )
       (i64.load offset=8
        (get_local $1)
       )
       (i64.const -7949128877345865728)
       (get_local $2)
      )
     )
     (i32.const -1)
    )
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=232
      (tee_local $6
       (call $_ZNK5eosio11multi_indexILy10497615196363685888ENS_14exchange_stateEJEE31load_object_by_primary_iteratorEl
        (get_local $1)
        (get_local $6)
       )
      )
     )
     (get_local $1)
    )
    (i32.const 224)
   )
   (i32.store offset=4
    (get_local $0)
    (get_local $6)
   )
   (i32.store
    (get_local $0)
    (get_local $1)
   )
   (return)
  )
  (i32.store offset=4
   (get_local $0)
   (i32.const 0)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
 )
 (func $_ZNK5eosio11multi_indexILy10497615196363685888ENS_14exchange_stateEJEE31load_object_by_primary_iteratorEl (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (set_local $8
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $9)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $2
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $3
    (i32.sub
     (i32.const 0)
     (get_local $2)
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i32.eq
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const 16)
       )
      )
      (get_local $1)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $4
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $4)
       (get_local $3)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (get_local $2)
     )
    )
    (set_local $6
     (i32.load
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br $label$2)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $6
       (call $db_get_i64
        (get_local $1)
        (i32.const 0)
        (i32.const 0)
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 656)
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.lt_u
       (get_local $6)
       (i32.const 513)
      )
     )
     (set_local $4
      (call $malloc
       (get_local $6)
      )
     )
     (br $label$4)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $4
      (i32.sub
       (get_local $9)
       (i32.and
        (i32.add
         (get_local $6)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $db_get_i64
     (get_local $1)
     (get_local $4)
     (get_local $6)
    )
   )
   (i32.store offset=36
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=32
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=40
    (get_local $8)
    (i32.add
     (get_local $4)
     (get_local $6)
    )
   )
   (block $label$6
    (br_if $label$6
     (i32.lt_u
      (get_local $6)
      (i32.const 513)
     )
    )
    (call $free
     (get_local $4)
    )
   )
   (set_local $4
    (call $_ZN5eosio14exchange_stateC2Ev
     (tee_local $6
      (call $_Znwj
       (i32.const 248)
      )
     )
    )
   )
   (i32.store offset=232
    (get_local $6)
    (get_local $0)
   )
   (drop
    (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_14exchange_stateE
     (i32.add
      (get_local $8)
      (i32.const 32)
     )
     (get_local $4)
    )
   )
   (i32.store offset=236
    (get_local $6)
    (get_local $1)
   )
   (i32.store offset=24
    (get_local $8)
    (get_local $6)
   )
   (i64.store offset=16
    (get_local $8)
    (tee_local $5
     (i64.shr_u
      (i64.load offset=16
       (get_local $6)
      )
      (i64.const 8)
     )
    )
   )
   (i32.store offset=12
    (get_local $8)
    (tee_local $7
     (i32.load offset=236
      (get_local $6)
     )
    )
   )
   (block $label$7
    (block $label$8
     (br_if $label$8
      (i32.ge_u
       (tee_local $4
        (i32.load
         (tee_local $1
          (i32.add
           (get_local $0)
           (i32.const 28)
          )
         )
        )
       )
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 32)
        )
       )
      )
     )
     (i64.store offset=8
      (get_local $4)
      (get_local $5)
     )
     (i32.store offset=16
      (get_local $4)
      (get_local $7)
     )
     (i32.store offset=24
      (get_local $8)
      (i32.const 0)
     )
     (i32.store
      (get_local $4)
      (get_local $6)
     )
     (i32.store
      (get_local $1)
      (i32.add
       (get_local $4)
       (i32.const 24)
      )
     )
     (br $label$7)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy10497615196363685888ENS1_14exchange_stateEJEE8item_ptrENS_9allocatorIS5_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS4_4itemENS_14default_deleteISB_EEEERyRlEEEvDpOT_
     (i32.add
      (get_local $0)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 16)
     )
     (i32.add
      (get_local $8)
      (i32.const 12)
     )
    )
   )
   (set_local $4
    (i32.load offset=24
     (get_local $8)
    )
   )
   (i32.store offset=24
    (get_local $8)
    (i32.const 0)
   )
   (br_if $label$2
    (i32.eqz
     (get_local $4)
    )
   )
   (call $_ZdlPv
    (get_local $4)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 48)
   )
  )
  (get_local $6)
 )
 (func $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_14exchange_stateE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $1)
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 3)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 4)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 4)
   )
  )
  (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_14exchange_state9connectorE
   (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_14exchange_state9connectorE
    (get_local $0)
    (i32.add
     (get_local $1)
     (i32.const 40)
    )
   )
   (i32.add
    (get_local $1)
    (i32.const 136)
   )
  )
 )
 (func $_ZNSt3__16vectorIN5eosio11multi_indexILy10497615196363685888ENS1_14exchange_stateEJEE8item_ptrENS_9allocatorIS5_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS4_4itemENS_14default_deleteISB_EEEERyRlEEEvDpOT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.ge_u
      (tee_local $5
       (i32.add
        (tee_local $4
         (i32.div_s
          (i32.sub
           (i32.load offset=4
            (get_local $0)
           )
           (tee_local $6
            (i32.load
             (get_local $0)
            )
           )
          )
          (i32.const 24)
         )
        )
        (i32.const 1)
       )
      )
      (i32.const 178956971)
     )
    )
    (set_local $7
     (i32.const 178956970)
    )
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.gt_u
        (tee_local $6
         (i32.div_s
          (i32.sub
           (i32.load offset=8
            (get_local $0)
           )
           (get_local $6)
          )
          (i32.const 24)
         )
        )
        (i32.const 89478484)
       )
      )
      (br_if $label$2
       (i32.eqz
        (tee_local $7
         (select
          (get_local $5)
          (tee_local $7
           (i32.shl
            (get_local $6)
            (i32.const 1)
           )
          )
          (i32.lt_u
           (get_local $7)
           (get_local $5)
          )
         )
        )
       )
      )
     )
     (set_local $6
      (call $_Znwj
       (i32.mul
        (get_local $7)
        (i32.const 24)
       )
      )
     )
     (br $label$0)
    )
    (set_local $7
     (i32.const 0)
    )
    (set_local $6
     (i32.const 0)
    )
    (br $label$0)
   )
   (call $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
    (get_local $0)
   )
   (unreachable)
  )
  (set_local $5
   (i32.load
    (get_local $1)
   )
  )
  (i32.store
   (get_local $1)
   (i32.const 0)
  )
  (i32.store
   (tee_local $1
    (i32.add
     (get_local $6)
     (i32.mul
      (get_local $4)
      (i32.const 24)
     )
    )
   )
   (get_local $5)
  )
  (i64.store offset=8
   (get_local $1)
   (i64.load
    (get_local $2)
   )
  )
  (i32.store offset=16
   (get_local $1)
   (i32.load
    (get_local $3)
   )
  )
  (set_local $4
   (i32.add
    (get_local $6)
    (i32.mul
     (get_local $7)
     (i32.const 24)
    )
   )
  )
  (set_local $5
   (i32.add
    (get_local $1)
    (i32.const 24)
   )
  )
  (block $label$4
   (block $label$5
    (br_if $label$5
     (i32.eq
      (tee_local $6
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
      )
      (tee_local $7
       (i32.load
        (get_local $0)
       )
      )
     )
    )
    (loop $label$6
     (set_local $3
      (i32.load
       (tee_local $2
        (i32.add
         (get_local $6)
         (i32.const -24)
        )
       )
      )
     )
     (i32.store
      (get_local $2)
      (i32.const 0)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
      (get_local $3)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -8)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -8)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -12)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -12)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -16)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -16)
       )
      )
     )
     (set_local $1
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
     )
     (set_local $6
      (get_local $2)
     )
     (br_if $label$6
      (i32.ne
       (get_local $7)
       (get_local $2)
      )
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $6
     (i32.load
      (get_local $0)
     )
    )
    (br $label$4)
   )
   (set_local $6
    (get_local $7)
   )
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $5)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
   (get_local $4)
  )
  (block $label$7
   (br_if $label$7
    (i32.eq
     (get_local $7)
     (get_local $6)
    )
   )
   (loop $label$8
    (set_local $1
     (i32.load
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.const 0)
    )
    (block $label$9
     (br_if $label$9
      (i32.eqz
       (get_local $1)
      )
     )
     (call $_ZdlPv
      (get_local $1)
     )
    )
    (br_if $label$8
     (i32.ne
      (get_local $6)
      (get_local $7)
     )
    )
   )
  )
  (block $label$10
   (br_if $label$10
    (i32.eqz
     (get_local $6)
    )
   )
   (call $_ZdlPv
    (get_local $6)
   )
  )
 )
 (func $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_14exchange_state9connectorE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $1)
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 3)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 4)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 4)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 40)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 48)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 56)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 64)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 72)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 80)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 88)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio12margin_stateC2Ev (param $0 i32) (result i32)
  (local $1 i64)
  (local $2 i32)
  (local $3 i32)
  (i64.store offset=8
   (get_local $0)
   (i64.const 1398362884)
  )
  (i64.store
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load offset=8
     (get_local $0)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (i64.store
   (tee_local $2
    (i32.add
     (get_local $0)
     (i32.const 32)
    )
   )
   (i64.const 1398362884)
  )
  (i64.store offset=24
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load
     (get_local $2)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$5
   (block $label$6
    (loop $label$7
     (br_if $label$6
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$8
      (br_if $label$8
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$9
       (br_if $label$6
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$9
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$7
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$5)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (i64.store offset=56
   (get_local $0)
   (i64.const 0)
  )
  (i64.store offset=48
   (get_local $0)
   (i64.const 9218868437227405311)
  )
  (get_local $0)
 )
 (func $_ZN5eosio12market_state11margin_callENS_15extended_symbolE (param $0 i32) (param $1 i32)
  (block $label$0
   (br_if $label$0
    (i64.ne
     (i64.load
      (get_local $1)
     )
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 56)
      )
     )
    )
   )
   (br_if $label$0
    (i64.ne
     (i64.load offset=8
      (get_local $1)
     )
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 64)
      )
     )
    )
   )
   (call $_ZN5eosio12market_state11margin_callERNS_14exchange_state9connectorERNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS5_yXadL_ZNKS5_8get_callEvEEEEEEEEE
    (get_local $0)
    (i32.add
     (get_local $0)
     (i32.const 48)
    )
    (i32.add
     (get_local $0)
     (i32.const 280)
    )
   )
   (return)
  )
  (call $_ZN5eosio12market_state11margin_callERNS_14exchange_state9connectorERNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS5_yXadL_ZNKS5_8get_callEvEEEEEEEEE
   (get_local $0)
   (i32.add
    (get_local $0)
    (i32.const 144)
   )
   (i32.add
    (get_local $0)
    (i32.const 320)
   )
  )
 )
 (func $_ZN5eosio12market_state11margin_callERNS_14exchange_state9connectorERNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS5_yXadL_ZNKS5_8get_callEvEEEEEEEEE (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i64)
  (local $7 i64)
  (local $8 f64)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 288)
    )
   )
  )
  (i32.store offset=272
   (get_local $9)
   (get_local $2)
  )
  (i64.store offset=240
   (get_local $9)
   (i64.const 0)
  )
  (call $_ZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE5indexILy4729653573519933440ES6_Ly0ELb0EE11lower_boundERKy
   (i32.add
    (get_local $9)
    (i32.const 264)
   )
   (i32.add
    (get_local $9)
    (i32.const 272)
   )
   (i32.add
    (get_local $9)
    (i32.const 240)
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (tee_local $2
      (i32.load offset=268
       (get_local $9)
      )
     )
    )
   )
   (i64.store
    (tee_local $3
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 216)
      )
      (i32.const 16)
     )
    )
    (i64.load
     (i32.add
      (get_local $2)
      (i32.const 48)
     )
    )
   )
   (i64.store
    (tee_local $4
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 216)
      )
      (i32.const 8)
     )
    )
    (i64.load
     (i32.add
      (get_local $2)
      (i32.const 40)
     )
    )
   )
   (i64.store offset=216
    (get_local $9)
    (i64.load offset=32
     (get_local $2)
    )
   )
   (set_local $7
    (i64.load
     (i32.add
      (get_local $2)
      (i32.const 24)
     )
    )
   )
   (i64.store offset=200
    (get_local $9)
    (i64.load
     (i32.add
      (get_local $2)
      (i32.const 16)
     )
    )
   )
   (i64.store offset=208
    (get_local $9)
    (get_local $7)
   )
   (i64.store
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 80)
     )
     (i32.const 16)
    )
    (i64.load
     (get_local $3)
    )
   )
   (i64.store
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 80)
     )
     (i32.const 8)
    )
    (i64.load
     (get_local $4)
    )
   )
   (i64.store offset=80
    (get_local $9)
    (i64.load offset=216
     (get_local $9)
    )
   )
   (i64.store
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 64)
     )
     (i32.const 8)
    )
    (i64.load offset=208
     (get_local $9)
    )
   )
   (i64.store offset=64
    (get_local $9)
    (i64.load offset=200
     (get_local $9)
    )
   )
   (call $_ZN5eosio14exchange_state7convertENS_14extended_assetENS_15extended_symbolE
    (i32.add
     (get_local $9)
     (i32.const 240)
    )
    (tee_local $3
     (i32.add
      (get_local $0)
      (i32.const 8)
     )
    )
    (i32.add
     (get_local $9)
     (i32.const 80)
    )
    (i32.add
     (get_local $9)
     (i32.const 64)
    )
   )
   (call $eosio_assert
    (i64.ge_s
     (tee_local $7
      (i64.load offset=240
       (get_local $9)
      )
     )
     (i64.load offset=8
      (i32.load offset=268
       (get_local $9)
      )
     )
    )
    (i32.const 736)
   )
   (call $eosio_assert
    (i64.eq
     (tee_local $5
      (i64.load offset=256
       (get_local $9)
      )
     )
     (i64.load
      (i32.add
       (tee_local $2
        (i32.load offset=268
         (get_local $9)
        )
       )
       (i32.const 24)
      )
     )
    )
    (i32.const 800)
   )
   (call $eosio_assert
    (i64.eq
     (i64.load
      (i32.add
       (get_local $2)
       (i32.const 16)
      )
     )
     (tee_local $6
      (i64.load offset=248
       (get_local $9)
      )
     )
    )
    (i32.const 816)
   )
   (call $eosio_assert
    (i64.gt_s
     (tee_local $7
      (i64.sub
       (get_local $7)
       (i64.load offset=8
        (get_local $2)
       )
      )
     )
     (i64.const -4611686018427387904)
    )
    (i32.const 864)
   )
   (call $eosio_assert
    (i64.lt_s
     (get_local $7)
     (i64.const 4611686018427387904)
    )
    (i32.const 896)
   )
   (i64.store offset=160
    (get_local $9)
    (get_local $6)
   )
   (i64.store offset=152
    (get_local $9)
    (get_local $7)
   )
   (i64.store offset=168
    (get_local $9)
    (get_local $5)
   )
   (i64.store offset=136
    (get_local $9)
    (i64.load
     (i32.add
      (tee_local $2
       (i32.load offset=268
        (get_local $9)
       )
      )
      (i32.const 40)
     )
    )
   )
   (i64.store offset=144
    (get_local $9)
    (i64.load
     (i32.add
      (get_local $2)
      (i32.const 48)
     )
    )
   )
   (i32.store
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 40)
     )
     (i32.const 20)
    )
    (i32.load
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 152)
      )
      (i32.const 20)
     )
    )
   )
   (i32.store
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 40)
     )
     (i32.const 16)
    )
    (i32.load offset=168
     (get_local $9)
    )
   )
   (i64.store
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 40)
     )
     (i32.const 8)
    )
    (i64.load offset=160
     (get_local $9)
    )
   )
   (i64.store offset=40
    (get_local $9)
    (i64.load offset=152
     (get_local $9)
    )
   )
   (i64.store
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 24)
     )
     (i32.const 8)
    )
    (i64.load offset=144
     (get_local $9)
    )
   )
   (i64.store offset=24
    (get_local $9)
    (i64.load offset=136
     (get_local $9)
    )
   )
   (call $_ZN5eosio14exchange_state7convertENS_14extended_assetENS_15extended_symbolE
    (i32.add
     (get_local $9)
     (i32.const 176)
    )
    (get_local $3)
    (i32.add
     (get_local $9)
     (i32.const 40)
    )
    (i32.add
     (get_local $9)
     (i32.const 24)
    )
   )
   (set_local $7
    (i64.load
     (i32.load offset=268
      (get_local $9)
     )
    )
   )
   (i64.store
    (tee_local $2
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 112)
      )
      (i32.const 16)
     )
    )
    (i64.load
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 176)
      )
      (i32.const 16)
     )
    )
   )
   (i64.store
    (tee_local $3
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 112)
      )
      (i32.const 8)
     )
    )
    (i64.load
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 176)
      )
      (i32.const 8)
     )
    )
   )
   (i32.store offset=112
    (get_local $9)
    (i32.load offset=176
     (get_local $9)
    )
   )
   (i32.store offset=116
    (get_local $9)
    (i32.load offset=180
     (get_local $9)
    )
   )
   (set_local $0
    (i32.load offset=440
     (get_local $0)
    )
   )
   (i64.store
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
    (i64.load
     (get_local $2)
    )
   )
   (i64.store
    (i32.add
     (get_local $9)
     (i32.const 8)
    )
    (i64.load
     (get_local $3)
    )
   )
   (i64.store
    (get_local $9)
    (i64.load offset=112
     (get_local $9)
    )
   )
   (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
    (get_local $0)
    (get_local $7)
    (get_local $9)
    (get_local $9)
   )
   (i64.store
    (tee_local $2
     (i32.add
      (get_local $1)
      (i32.const 56)
     )
    )
    (i64.sub
     (i64.load
      (get_local $2)
     )
     (i64.load offset=8
      (i32.load offset=268
       (get_local $9)
      )
     )
    )
   )
   (i64.store offset=280
    (get_local $9)
    (tee_local $7
     (i64.load offset=264
      (get_local $9)
     )
    )
   )
   (call $eosio_assert
    (i32.ne
     (tee_local $2
      (i32.wrap/i64
       (i64.shr_u
        (get_local $7)
        (i64.const 32)
       )
      )
     )
     (i32.const 0)
    )
    (i32.const 928)
   )
   (drop
    (call $_ZN5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE5indexILy4729653573519933440ES6_Ly0ELb0EE14const_iteratorppEv
     (i32.add
      (get_local $9)
      (i32.const 280)
     )
    )
   )
   (call $_ZN5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE5eraseERKS1_
    (i32.load offset=272
     (get_local $9)
    )
    (get_local $2)
   )
   (i64.store offset=280
    (get_local $9)
    (i64.const 0)
   )
   (call $_ZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE5indexILy4729653573519933440ES6_Ly0ELb0EE11lower_boundERKy
    (i32.add
     (get_local $9)
     (i32.const 104)
    )
    (i32.add
     (get_local $9)
     (i32.const 272)
    )
    (i32.add
     (get_local $9)
     (i32.const 280)
    )
   )
   (i64.store offset=264
    (get_local $9)
    (tee_local $7
     (i64.load offset=104
      (get_local $9)
     )
    )
   )
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i32.eqz
       (tee_local $2
        (i32.wrap/i64
         (i64.shr_u
          (get_local $7)
          (i64.const 32)
         )
        )
       )
      )
     )
     (set_local $8
      (f64.load offset=56
       (get_local $2)
      )
     )
     (br $label$1)
    )
    (set_local $8
     (f64.const 18446744073709551615)
    )
   )
   (f64.store
    (i32.add
     (get_local $1)
     (i32.const 80)
    )
    (get_local $8)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 288)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE5indexILy4729653573519933440ES6_Ly0ELb0EE11lower_boundERKy (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i64.store offset=8
   (get_local $10)
   (i64.const 0)
  )
  (i64.store
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.lt_s
     (tee_local $3
      (call $db_idx64_lowerbound
       (i64.load
        (tee_local $8
         (i32.load
          (get_local $1)
         )
        )
       )
       (i64.load offset=8
        (get_local $8)
       )
       (i64.const -7949197150146002944)
       (get_local $10)
       (i32.add
        (get_local $10)
        (i32.const 8)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=8
     (get_local $10)
    )
   )
   (block $label$1
    (br_if $label$1
     (i32.eq
      (tee_local $9
       (i32.load
        (i32.add
         (tee_local $4
          (i32.load
           (get_local $1)
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $6
       (i32.load offset=24
        (get_local $4)
       )
      )
     )
    )
    (set_local $2
     (i32.add
      (get_local $9)
      (i32.const -24)
     )
    )
    (set_local $7
     (i32.sub
      (i32.const 0)
      (get_local $6)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i64.eq
       (i64.load
        (i32.load
         (get_local $2)
        )
       )
       (get_local $5)
      )
     )
     (set_local $9
      (get_local $2)
     )
     (set_local $2
      (tee_local $8
       (i32.add
        (get_local $2)
        (i32.const -24)
       )
      )
     )
     (br_if $label$2
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $7)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (i32.eq
       (get_local $9)
       (get_local $6)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=64
        (tee_local $2
         (i32.load
          (i32.add
           (get_local $9)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $4)
      )
      (i32.const 224)
     )
     (br $label$3)
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=64
       (tee_local $2
        (call $_ZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (call $db_find_i64
          (i64.load
           (get_local $4)
          )
          (i64.load offset=8
           (get_local $4)
          )
          (i64.const -7949197150146002944)
          (get_local $5)
         )
        )
       )
      )
      (get_local $4)
     )
     (i32.const 224)
    )
   )
   (i32.store
    (i32.add
     (get_local $2)
     (i32.const 72)
    )
    (get_local $3)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $2)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 16)
   )
  )
 )
 (func $_ZN5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE5indexILy4729653573519933440ES6_Ly0ELb0EE14const_iteratorppEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 0)
   )
   (i32.const 1152)
  )
  (block $label$0
   (br_if $label$0
    (i32.ne
     (tee_local $7
      (i32.load offset=72
       (tee_local $6
        (i32.load offset=4
         (get_local $0)
        )
       )
      )
     )
     (i32.const -1)
    )
   )
   (set_local $7
    (call $db_idx64_find_primary
     (i64.load
      (tee_local $7
       (i32.load
        (i32.load
         (get_local $0)
        )
       )
      )
     )
     (i64.load offset=8
      (get_local $7)
     )
     (i64.const -7949197150146002944)
     (i32.add
      (get_local $9)
      (i32.const 8)
     )
     (i64.load
      (get_local $6)
     )
    )
   )
   (i32.store offset=72
    (i32.load
     (i32.add
      (get_local $0)
      (i32.const 4)
     )
    )
    (get_local $7)
   )
  )
  (i64.store offset=8
   (get_local $9)
   (i64.const 0)
  )
  (block $label$1
   (block $label$2
    (block $label$3
     (block $label$4
      (br_if $label$4
       (i32.le_s
        (tee_local $1
         (call $db_idx64_next
          (get_local $7)
          (i32.add
           (get_local $9)
           (i32.const 8)
          )
         )
        )
        (i32.const -1)
       )
      )
      (set_local $3
       (i64.load offset=8
        (get_local $9)
       )
      )
      (block $label$5
       (br_if $label$5
        (i32.eq
         (tee_local $8
          (i32.load
           (i32.add
            (tee_local $2
             (i32.load
              (i32.load
               (get_local $0)
              )
             )
            )
            (i32.const 28)
           )
          )
         )
         (tee_local $4
          (i32.load offset=24
           (get_local $2)
          )
         )
        )
       )
       (set_local $7
        (i32.add
         (get_local $8)
         (i32.const -24)
        )
       )
       (set_local $5
        (i32.sub
         (i32.const 0)
         (get_local $4)
        )
       )
       (loop $label$6
        (br_if $label$5
         (i64.eq
          (i64.load
           (i32.load
            (get_local $7)
           )
          )
          (get_local $3)
         )
        )
        (set_local $8
         (get_local $7)
        )
        (set_local $7
         (tee_local $6
          (i32.add
           (get_local $7)
           (i32.const -24)
          )
         )
        )
        (br_if $label$6
         (i32.ne
          (i32.add
           (get_local $6)
           (get_local $5)
          )
          (i32.const -24)
         )
        )
       )
      )
      (br_if $label$3
       (i32.eq
        (get_local $8)
        (get_local $4)
       )
      )
      (call $eosio_assert
       (i32.eq
        (i32.load offset=64
         (tee_local $7
          (i32.load
           (i32.add
            (get_local $8)
            (i32.const -24)
           )
          )
         )
        )
        (get_local $2)
       )
       (i32.const 224)
      )
      (br $label$2)
     )
     (i32.store
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
      (i32.const 0)
     )
     (br $label$1)
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=64
       (tee_local $7
        (call $_ZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $2)
         (call $db_find_i64
          (i64.load
           (get_local $2)
          )
          (i64.load offset=8
           (get_local $2)
          )
          (i64.const -7949197150146002944)
          (get_local $3)
         )
        )
       )
      )
      (get_local $2)
     )
     (i32.const 224)
    )
   )
   (i32.store
    (i32.add
     (get_local $0)
     (i32.const 4)
    )
    (get_local $7)
   )
   (i32.store
    (i32.add
     (get_local $7)
     (i32.const 72)
    )
    (get_local $1)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE5eraseERKS1_ (param $0 i32) (param $1 i32)
  (local $2 i64)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (call $eosio_assert
   (i32.eq
    (i32.load offset=64
     (get_local $1)
    )
    (get_local $0)
   )
   (i32.const 976)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load
     (get_local $0)
    )
    (call $current_receiver)
   )
   (i32.const 1024)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (tee_local $5
        (i32.add
         (get_local $0)
         (i32.const 28)
        )
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $2
    (i64.load
     (get_local $1)
    )
   )
   (set_local $6
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (set_local $8
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i64.eq
      (i64.load
       (i32.load
        (get_local $8)
       )
      )
      (get_local $2)
     )
    )
    (set_local $7
     (get_local $8)
    )
    (set_local $8
     (tee_local $4
      (i32.add
       (get_local $8)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $4)
       (get_local $6)
      )
      (i32.const -24)
     )
    )
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $7)
    (get_local $3)
   )
   (i32.const 1088)
  )
  (set_local $8
   (i32.add
    (get_local $7)
    (i32.const -24)
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (tee_local $4
       (i32.load
        (get_local $5)
       )
      )
     )
    )
    (set_local $3
     (i32.sub
      (i32.const 0)
      (get_local $4)
     )
    )
    (set_local $7
     (get_local $8)
    )
    (loop $label$4
     (set_local $6
      (i32.load
       (tee_local $8
        (i32.add
         (get_local $7)
         (i32.const 24)
        )
       )
      )
     )
     (i32.store
      (get_local $8)
      (i32.const 0)
     )
     (set_local $4
      (i32.load
       (get_local $7)
      )
     )
     (i32.store
      (get_local $7)
      (get_local $6)
     )
     (block $label$5
      (br_if $label$5
       (i32.eqz
        (get_local $4)
       )
      )
      (call $_ZdlPv
       (get_local $4)
      )
     )
     (i32.store
      (i32.add
       (get_local $7)
       (i32.const 16)
      )
      (i32.load
       (i32.add
        (get_local $7)
        (i32.const 40)
       )
      )
     )
     (i64.store
      (i32.add
       (get_local $7)
       (i32.const 8)
      )
      (i64.load
       (i32.add
        (get_local $7)
        (i32.const 32)
       )
      )
     )
     (set_local $7
      (get_local $8)
     )
     (br_if $label$4
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $3)
       )
       (i32.const -24)
      )
     )
    )
    (br_if $label$2
     (i32.eq
      (tee_local $7
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 28)
        )
       )
      )
      (get_local $8)
     )
    )
   )
   (loop $label$6
    (set_local $4
     (i32.load
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.const 0)
    )
    (block $label$7
     (br_if $label$7
      (i32.eqz
       (get_local $4)
      )
     )
     (call $_ZdlPv
      (get_local $4)
     )
    )
    (br_if $label$6
     (i32.ne
      (get_local $8)
      (get_local $7)
     )
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 28)
   )
   (get_local $8)
  )
  (call $db_remove_i64
   (i32.load offset=68
    (get_local $1)
   )
  )
  (block $label$8
   (block $label$9
    (br_if $label$9
     (i32.gt_s
      (tee_local $7
       (i32.load
        (i32.add
         (get_local $1)
         (i32.const 72)
        )
       )
      )
      (i32.const -1)
     )
    )
    (br_if $label$8
     (i32.lt_s
      (tee_local $7
       (call $db_idx64_find_primary
        (i64.load
         (get_local $0)
        )
        (i64.load offset=8
         (get_local $0)
        )
        (i64.const -7949197150146002944)
        (i32.add
         (get_local $9)
         (i32.const 8)
        )
        (i64.load
         (get_local $1)
        )
       )
      )
      (i32.const 0)
     )
    )
   )
   (call $db_idx64_remove
    (get_local $7)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 16)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE31load_object_by_primary_iteratorEl (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i32.store offset=44
   (tee_local $8
    (get_local $9)
   )
   (get_local $1)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $2
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $3
    (i32.sub
     (i32.const 0)
     (get_local $2)
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i32.eq
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const 16)
       )
      )
      (get_local $1)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $4
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $4)
       (get_local $3)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (get_local $2)
     )
    )
    (set_local $6
     (i32.load
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br $label$2)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $6
       (call $db_get_i64
        (get_local $1)
        (i32.const 0)
        (i32.const 0)
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 656)
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.lt_u
       (get_local $6)
       (i32.const 513)
      )
     )
     (set_local $4
      (call $malloc
       (get_local $6)
      )
     )
     (br $label$4)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $4
      (i32.sub
       (get_local $9)
       (i32.and
        (i32.add
         (get_local $6)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $db_get_i64
     (get_local $1)
     (get_local $4)
     (get_local $6)
    )
   )
   (i32.store offset=36
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=32
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=40
    (get_local $8)
    (i32.add
     (get_local $4)
     (get_local $6)
    )
   )
   (block $label$6
    (br_if $label$6
     (i32.lt_u
      (get_local $6)
      (i32.const 513)
     )
    )
    (call $free
     (get_local $4)
    )
   )
   (i32.store offset=8
    (get_local $8)
    (get_local $0)
   )
   (i32.store offset=12
    (get_local $8)
    (i32.add
     (get_local $8)
     (i32.const 32)
    )
   )
   (i32.store offset=16
    (get_local $8)
    (i32.add
     (get_local $8)
     (i32.const 44)
    )
   )
   (drop
    (call $_ZN5eosio15margin_positionC2Ev
     (tee_local $6
      (call $_Znwj
       (i32.const 80)
      )
     )
    )
   )
   (i32.store offset=64
    (get_local $6)
    (get_local $0)
   )
   (call $_ZZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE31load_object_by_primary_iteratorElENKUlRT_E_clINS8_4itemEEEDaSA_
    (i32.add
     (get_local $8)
     (i32.const 8)
    )
    (get_local $6)
   )
   (i32.store offset=24
    (get_local $8)
    (get_local $6)
   )
   (i64.store offset=8
    (get_local $8)
    (tee_local $5
     (i64.load
      (get_local $6)
     )
    )
   )
   (i32.store offset=4
    (get_local $8)
    (tee_local $7
     (i32.load offset=68
      (get_local $6)
     )
    )
   )
   (block $label$7
    (block $label$8
     (br_if $label$8
      (i32.ge_u
       (tee_local $4
        (i32.load
         (tee_local $1
          (i32.add
           (get_local $0)
           (i32.const 28)
          )
         )
        )
       )
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 32)
        )
       )
      )
     )
     (i64.store offset=8
      (get_local $4)
      (get_local $5)
     )
     (i32.store offset=16
      (get_local $4)
      (get_local $7)
     )
     (i32.store offset=24
      (get_local $8)
      (i32.const 0)
     )
     (i32.store
      (get_local $4)
      (get_local $6)
     )
     (i32.store
      (get_local $1)
      (i32.add
       (get_local $4)
       (i32.const 24)
      )
     )
     (br $label$7)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy10497546923563548672ENS1_15margin_positionEJNS1_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS3_yXadL_ZNKS3_8get_callEvEEEEEEEE8item_ptrENS_9allocatorISB_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINSA_4itemENS_14default_deleteISH_EEEERyRlEEEvDpOT_
     (i32.add
      (get_local $0)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 8)
     )
     (i32.add
      (get_local $8)
      (i32.const 4)
     )
    )
   )
   (set_local $4
    (i32.load offset=24
     (get_local $8)
    )
   )
   (i32.store offset=24
    (get_local $8)
    (i32.const 0)
   )
   (br_if $label$2
    (i32.eqz
     (get_local $4)
    )
   )
   (call $_ZdlPv
    (get_local $4)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 48)
   )
  )
  (get_local $6)
 )
 (func $_ZN5eosio15margin_positionC2Ev (param $0 i32) (result i32)
  (local $1 i64)
  (local $2 i32)
  (local $3 i32)
  (i64.store offset=8
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (tee_local $2
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
   )
   (i64.const 1398362884)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load
     (get_local $2)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (i64.store
   (tee_local $2
    (i32.add
     (get_local $0)
     (i32.const 40)
    )
   )
   (i64.const 1398362884)
  )
  (i64.store offset=32
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load
     (get_local $2)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$5
   (block $label$6
    (loop $label$7
     (br_if $label$6
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$8
      (br_if $label$8
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$9
       (br_if $label$6
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$9
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$7
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$5)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (i64.store offset=56
   (get_local $0)
   (i64.const 0)
  )
  (get_local $0)
 )
 (func $_ZZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE31load_object_by_primary_iteratorElENKUlRT_E_clINS8_4itemEEEDaSA_ (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load offset=4
        (get_local $0)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $1)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $3
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $3)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $3
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $3)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $3
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $3)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $3
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $3)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $3
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $3)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 40)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $3
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $3)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 48)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $3
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $3)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 56)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $2
   (i32.load
    (i32.load offset=8
     (get_local $0)
    )
   )
  )
  (i32.store offset=72
   (get_local $1)
   (i32.const -1)
  )
  (i32.store offset=68
   (get_local $1)
   (get_local $2)
  )
 )
 (func $_ZNSt3__16vectorIN5eosio11multi_indexILy10497546923563548672ENS1_15margin_positionEJNS1_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS3_yXadL_ZNKS3_8get_callEvEEEEEEEE8item_ptrENS_9allocatorISB_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINSA_4itemENS_14default_deleteISH_EEEERyRlEEEvDpOT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.ge_u
      (tee_local $5
       (i32.add
        (tee_local $4
         (i32.div_s
          (i32.sub
           (i32.load offset=4
            (get_local $0)
           )
           (tee_local $6
            (i32.load
             (get_local $0)
            )
           )
          )
          (i32.const 24)
         )
        )
        (i32.const 1)
       )
      )
      (i32.const 178956971)
     )
    )
    (set_local $7
     (i32.const 178956970)
    )
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.gt_u
        (tee_local $6
         (i32.div_s
          (i32.sub
           (i32.load offset=8
            (get_local $0)
           )
           (get_local $6)
          )
          (i32.const 24)
         )
        )
        (i32.const 89478484)
       )
      )
      (br_if $label$2
       (i32.eqz
        (tee_local $7
         (select
          (get_local $5)
          (tee_local $7
           (i32.shl
            (get_local $6)
            (i32.const 1)
           )
          )
          (i32.lt_u
           (get_local $7)
           (get_local $5)
          )
         )
        )
       )
      )
     )
     (set_local $6
      (call $_Znwj
       (i32.mul
        (get_local $7)
        (i32.const 24)
       )
      )
     )
     (br $label$0)
    )
    (set_local $7
     (i32.const 0)
    )
    (set_local $6
     (i32.const 0)
    )
    (br $label$0)
   )
   (call $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
    (get_local $0)
   )
   (unreachable)
  )
  (set_local $5
   (i32.load
    (get_local $1)
   )
  )
  (i32.store
   (get_local $1)
   (i32.const 0)
  )
  (i32.store
   (tee_local $1
    (i32.add
     (get_local $6)
     (i32.mul
      (get_local $4)
      (i32.const 24)
     )
    )
   )
   (get_local $5)
  )
  (i64.store offset=8
   (get_local $1)
   (i64.load
    (get_local $2)
   )
  )
  (i32.store offset=16
   (get_local $1)
   (i32.load
    (get_local $3)
   )
  )
  (set_local $4
   (i32.add
    (get_local $6)
    (i32.mul
     (get_local $7)
     (i32.const 24)
    )
   )
  )
  (set_local $5
   (i32.add
    (get_local $1)
    (i32.const 24)
   )
  )
  (block $label$4
   (block $label$5
    (br_if $label$5
     (i32.eq
      (tee_local $6
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
      )
      (tee_local $7
       (i32.load
        (get_local $0)
       )
      )
     )
    )
    (loop $label$6
     (set_local $3
      (i32.load
       (tee_local $2
        (i32.add
         (get_local $6)
         (i32.const -24)
        )
       )
      )
     )
     (i32.store
      (get_local $2)
      (i32.const 0)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
      (get_local $3)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -8)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -8)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -12)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -12)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -16)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -16)
       )
      )
     )
     (set_local $1
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
     )
     (set_local $6
      (get_local $2)
     )
     (br_if $label$6
      (i32.ne
       (get_local $7)
       (get_local $2)
      )
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $6
     (i32.load
      (get_local $0)
     )
    )
    (br $label$4)
   )
   (set_local $6
    (get_local $7)
   )
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $5)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
   (get_local $4)
  )
  (block $label$7
   (br_if $label$7
    (i32.eq
     (get_local $7)
     (get_local $6)
    )
   )
   (loop $label$8
    (set_local $1
     (i32.load
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.const 0)
    )
    (block $label$9
     (br_if $label$9
      (i32.eqz
       (get_local $1)
      )
     )
     (call $_ZdlPv
      (get_local $1)
     )
    )
    (br_if $label$8
     (i32.ne
      (get_local $6)
      (get_local $7)
     )
    )
   )
  )
  (block $label$10
   (br_if $label$10
    (i32.eqz
     (get_local $6)
    )
   )
   (call $_ZdlPv
    (get_local $6)
   )
  )
 )
 (func $_ZNK5eosio12market_state13initial_stateEv (param $0 i32) (result i32)
  (i32.load
   (i32.add
    (get_local $0)
    (i32.const 448)
   )
  )
 )
 (func $_ZN5eosio12market_state4lendEyRKNS_14extended_assetE (param $0 i32) (param $1 i64) (param $2 i32)
  (local $3 i64)
  (local $4 i64)
  (local $5 i32)
  (local $6 i64)
  (local $7 f64)
  (local $8 f64)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i64.store offset=32
   (get_local $9)
   (tee_local $3
    (i64.load offset=8
     (get_local $2)
    )
   )
  )
  (set_local $5
   (i32.load offset=440
    (get_local $0)
   )
  )
  (set_local $4
   (i64.load offset=16
    (get_local $2)
   )
  )
  (set_local $6
   (i64.load
    (get_local $2)
   )
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 8)
   )
   (get_local $3)
  )
  (i64.store offset=24
   (get_local $9)
   (tee_local $6
    (i64.sub
     (i64.const 0)
     (get_local $6)
    )
   )
  )
  (i64.store offset=40
   (get_local $9)
   (get_local $4)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 16)
   )
   (get_local $4)
  )
  (i64.store
   (get_local $9)
   (get_local $6)
  )
  (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
   (get_local $5)
   (get_local $1)
   (get_local $9)
   (get_local $9)
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (br_if $label$5
         (i64.ne
          (get_local $3)
          (i64.load
           (i32.add
            (get_local $0)
            (i32.const 56)
           )
          )
         )
        )
        (br_if $label$5
         (i64.ne
          (get_local $4)
          (i64.load
           (i32.add
            (get_local $0)
            (i32.const 64)
           )
          )
         )
        )
        (set_local $4
         (i64.load
          (get_local $2)
         )
        )
        (br_if $label$4
         (i64.lt_s
          (tee_local $3
           (i64.load
            (i32.add
             (get_local $0)
             (i32.const 80)
            )
           )
          )
          (i64.const 1)
         )
        )
        (set_local $8
         (f64.add
          (tee_local $8
           (f64.load
            (i32.add
             (get_local $0)
             (i32.const 136)
            )
           )
          )
          (f64.div
           (f64.mul
            (get_local $8)
            (tee_local $7
             (f64.convert_s/i64
              (get_local $4)
             )
            )
           )
           (f64.convert_s/i64
            (get_local $3)
           )
          )
         )
        )
        (br $label$3)
       )
       (block $label$6
        (br_if $label$6
         (i64.ne
          (get_local $3)
          (i64.load
           (i32.add
            (get_local $0)
            (i32.const 152)
           )
          )
         )
        )
        (br_if $label$6
         (i64.ne
          (get_local $4)
          (i64.load
           (i32.add
            (get_local $0)
            (i32.const 160)
           )
          )
         )
        )
        (set_local $4
         (i64.load
          (get_local $2)
         )
        )
        (br_if $label$2
         (i64.lt_s
          (tee_local $3
           (i64.load
            (i32.add
             (get_local $0)
             (i32.const 176)
            )
           )
          )
          (i64.const 1)
         )
        )
        (set_local $8
         (f64.add
          (tee_local $8
           (f64.load
            (i32.add
             (get_local $0)
             (i32.const 232)
            )
           )
          )
          (f64.div
           (f64.mul
            (get_local $8)
            (tee_local $7
             (f64.convert_s/i64
              (get_local $4)
             )
            )
           )
           (f64.convert_s/i64
            (get_local $3)
           )
          )
         )
        )
        (br $label$1)
       )
       (call $eosio_assert
        (i32.const 0)
        (i32.const 1184)
       )
       (br $label$0)
      )
      (set_local $8
       (f64.add
        (tee_local $7
         (f64.convert_s/i64
          (get_local $4)
         )
        )
        (f64.load
         (i32.add
          (get_local $0)
          (i32.const 136)
         )
        )
       )
      )
     )
     (i64.store
      (i32.add
       (get_local $0)
       (i32.const 80)
      )
      (i64.add
       (get_local $3)
       (get_local $4)
      )
     )
     (f64.store
      (i32.add
       (get_local $0)
       (i32.const 136)
      )
      (get_local $8)
     )
     (call $_ZN5eosio12market_state18adjust_lend_sharesEyRNS_11multi_indexILy10163845904742744064ENS_13loan_positionEJEEEd
      (get_local $9)
      (get_local $1)
      (i32.add
       (get_local $0)
       (i32.const 360)
      )
      (get_local $7)
     )
     (br $label$0)
    )
    (set_local $8
     (f64.add
      (tee_local $7
       (f64.convert_s/i64
        (get_local $4)
       )
      )
      (f64.load
       (i32.add
        (get_local $0)
        (i32.const 232)
       )
      )
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $0)
     (i32.const 176)
    )
    (i64.add
     (get_local $3)
     (get_local $4)
    )
   )
   (f64.store
    (i32.add
     (get_local $0)
     (i32.const 232)
    )
    (get_local $8)
   )
   (call $_ZN5eosio12market_state18adjust_lend_sharesEyRNS_11multi_indexILy10163845904742744064ENS_13loan_positionEJEEEd
    (get_local $9)
    (get_local $1)
    (i32.add
     (get_local $0)
     (i32.const 400)
    )
    (get_local $7)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 48)
   )
  )
 )
 (func $_ZN5eosio12market_state18adjust_lend_sharesEyRNS_11multi_indexILy10163845904742744064ENS_13loan_positionEJEEEd (param $0 i32) (param $1 i64) (param $2 i32) (param $3 f64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $9
      (i32.load
       (i32.add
        (get_local $2)
        (i32.const 28)
       )
      )
     )
     (tee_local $4
      (i32.load offset=24
       (get_local $2)
      )
     )
    )
   )
   (set_local $8
    (i32.add
     (get_local $9)
     (i32.const -24)
    )
   )
   (set_local $5
    (i32.sub
     (i32.const 0)
     (get_local $4)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i64.eq
      (i64.load
       (i32.load
        (get_local $8)
       )
      )
      (get_local $1)
     )
    )
    (set_local $9
     (get_local $8)
    )
    (set_local $8
     (tee_local $6
      (i32.add
       (get_local $8)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $6)
       (get_local $5)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (block $label$4
     (block $label$5
      (br_if $label$5
       (i32.eq
        (get_local $9)
        (get_local $4)
       )
      )
      (call $eosio_assert
       (i32.eq
        (i32.load offset=16
         (tee_local $8
          (i32.load
           (i32.add
            (get_local $9)
            (i32.const -24)
           )
          )
         )
        )
        (get_local $2)
       )
       (i32.const 224)
      )
      (br_if $label$4
       (get_local $8)
      )
      (br $label$3)
     )
     (br_if $label$3
      (i32.lt_s
       (tee_local $8
        (call $db_find_i64
         (i64.load
          (get_local $2)
         )
         (i64.load offset=8
          (get_local $2)
         )
         (i64.const -8282898168966807552)
         (get_local $1)
        )
       )
       (i32.const 0)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=16
        (tee_local $8
         (call $_ZNK5eosio11multi_indexILy10163845904742744064ENS_13loan_positionEJEE31load_object_by_primary_iteratorEl
          (get_local $2)
          (get_local $8)
         )
        )
       )
       (get_local $2)
      )
      (i32.const 224)
     )
    )
    (call $eosio_assert
     (i32.const 1)
     (i32.const 352)
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=16
       (get_local $8)
      )
      (get_local $2)
     )
     (i32.const 400)
    )
    (call $eosio_assert
     (i64.eq
      (i64.load
       (get_local $2)
      )
      (call $current_receiver)
     )
     (i32.const 448)
    )
    (f64.store offset=8
     (get_local $8)
     (tee_local $3
      (f64.add
       (f64.load offset=8
        (get_local $8)
       )
       (get_local $3)
      )
     )
    )
    (set_local $1
     (i64.load
      (get_local $8)
     )
    )
    (call $eosio_assert
     (f64.ge
      (get_local $3)
      (f64.const 0)
     )
     (i32.const 1216)
    )
    (call $eosio_assert
     (i64.eq
      (get_local $1)
      (i64.load
       (get_local $8)
      )
     )
     (i32.const 544)
    )
    (call $eosio_assert
     (i32.const 1)
     (i32.const 608)
    )
    (drop
     (call $memcpy
      (i32.add
       (get_local $10)
       (i32.const 16)
      )
      (get_local $8)
      (i32.const 8)
     )
    )
    (call $eosio_assert
     (i32.const 1)
     (i32.const 608)
    )
    (drop
     (call $memcpy
      (i32.or
       (i32.add
        (get_local $10)
        (i32.const 16)
       )
       (i32.const 8)
      )
      (i32.add
       (get_local $8)
       (i32.const 8)
      )
      (i32.const 8)
     )
    )
    (call $db_update_i64
     (i32.load offset=20
      (get_local $8)
     )
     (i64.const 0)
     (i32.add
      (get_local $10)
      (i32.const 16)
     )
     (i32.const 16)
    )
    (br_if $label$2
     (i64.lt_u
      (get_local $1)
      (i64.load offset=16
       (get_local $2)
      )
     )
    )
    (i64.store
     (i32.add
      (get_local $2)
      (i32.const 16)
     )
     (select
      (i64.const -2)
      (i64.add
       (get_local $1)
       (i64.const 1)
      )
      (i64.gt_u
       (get_local $1)
       (i64.const -3)
      )
     )
    )
    (br $label$2)
   )
   (call $eosio_assert
    (i64.eq
     (i64.load
      (get_local $2)
     )
     (call $current_receiver)
    )
    (i32.const 288)
   )
   (i32.store offset=16
    (tee_local $8
     (call $_Znwj
      (i32.const 32)
     )
    )
    (get_local $2)
   )
   (f64.store offset=8
    (get_local $8)
    (get_local $3)
   )
   (i64.store
    (get_local $8)
    (get_local $1)
   )
   (call $eosio_assert
    (f64.ge
     (get_local $3)
     (f64.const 0)
    )
    (i32.const 1216)
   )
   (call $eosio_assert
    (i32.const 1)
    (i32.const 608)
   )
   (drop
    (call $memcpy
     (i32.add
      (get_local $10)
      (i32.const 16)
     )
     (get_local $8)
     (i32.const 8)
    )
   )
   (call $eosio_assert
    (i32.const 1)
    (i32.const 608)
   )
   (drop
    (call $memcpy
     (i32.or
      (i32.add
       (get_local $10)
       (i32.const 16)
      )
      (i32.const 8)
     )
     (i32.add
      (get_local $8)
      (i32.const 8)
     )
     (i32.const 8)
    )
   )
   (i32.store offset=20
    (get_local $8)
    (tee_local $9
     (call $db_store_i64
      (i64.load offset=8
       (get_local $2)
      )
      (i64.const -8282898168966807552)
      (get_local $1)
      (tee_local $7
       (i64.load
        (get_local $8)
       )
      )
      (i32.add
       (get_local $10)
       (i32.const 16)
      )
      (i32.const 16)
     )
    )
   )
   (block $label$6
    (br_if $label$6
     (i64.lt_u
      (get_local $7)
      (i64.load offset=16
       (get_local $2)
      )
     )
    )
    (i64.store
     (i32.add
      (get_local $2)
      (i32.const 16)
     )
     (select
      (i64.const -2)
      (i64.add
       (get_local $7)
       (i64.const 1)
      )
      (i64.gt_u
       (get_local $7)
       (i64.const -3)
      )
     )
    )
   )
   (i32.store offset=8
    (get_local $10)
    (get_local $8)
   )
   (i64.store offset=16
    (get_local $10)
    (tee_local $1
     (i64.load
      (get_local $8)
     )
    )
   )
   (i32.store offset=4
    (get_local $10)
    (get_local $9)
   )
   (block $label$7
    (block $label$8
     (br_if $label$8
      (i32.ge_u
       (tee_local $6
        (i32.load
         (tee_local $5
          (i32.add
           (get_local $2)
           (i32.const 28)
          )
         )
        )
       )
       (i32.load
        (i32.add
         (get_local $2)
         (i32.const 32)
        )
       )
      )
     )
     (i64.store offset=8
      (get_local $6)
      (get_local $1)
     )
     (i32.store offset=16
      (get_local $6)
      (get_local $9)
     )
     (i32.store offset=8
      (get_local $10)
      (i32.const 0)
     )
     (i32.store
      (get_local $6)
      (get_local $8)
     )
     (i32.store
      (get_local $5)
      (i32.add
       (get_local $6)
       (i32.const 24)
      )
     )
     (br $label$7)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy10163845904742744064ENS1_13loan_positionEJEE8item_ptrENS_9allocatorIS5_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS4_4itemENS_14default_deleteISB_EEEERyRlEEEvDpOT_
     (i32.add
      (get_local $2)
      (i32.const 24)
     )
     (i32.add
      (get_local $10)
      (i32.const 8)
     )
     (i32.add
      (get_local $10)
      (i32.const 16)
     )
     (i32.add
      (get_local $10)
      (i32.const 4)
     )
    )
   )
   (set_local $8
    (i32.load offset=8
     (get_local $10)
    )
   )
   (i32.store offset=8
    (get_local $10)
    (i32.const 0)
   )
   (br_if $label$2
    (i32.eqz
     (get_local $8)
    )
   )
   (call $_ZdlPv
    (get_local $8)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 32)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy10163845904742744064ENS_13loan_positionEJEE31load_object_by_primary_iteratorEl (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (set_local $8
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $9)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $2
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $3
    (i32.sub
     (i32.const 0)
     (get_local $2)
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i32.eq
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const 16)
       )
      )
      (get_local $1)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $4
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $4)
       (get_local $3)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (get_local $2)
     )
    )
    (set_local $6
     (i32.load
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br $label$2)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $4
       (call $db_get_i64
        (get_local $1)
        (i32.const 0)
        (i32.const 0)
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 656)
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.le_u
       (get_local $4)
       (i32.const 512)
      )
     )
     (drop
      (call $db_get_i64
       (get_local $1)
       (tee_local $7
        (call $malloc
         (get_local $4)
        )
       )
       (get_local $4)
      )
     )
     (call $free
      (get_local $7)
     )
     (br $label$4)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $7
      (i32.sub
       (get_local $9)
       (i32.and
        (i32.add
         (get_local $4)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
    (drop
     (call $db_get_i64
      (get_local $1)
      (get_local $7)
      (get_local $4)
     )
    )
   )
   (i32.store offset=16
    (tee_local $6
     (call $_Znwj
      (i32.const 32)
     )
    )
    (get_local $0)
   )
   (call $eosio_assert
    (i32.gt_u
     (get_local $4)
     (i32.const 7)
    )
    (i32.const 688)
   )
   (drop
    (call $memcpy
     (get_local $6)
     (get_local $7)
     (i32.const 8)
    )
   )
   (call $eosio_assert
    (i32.ne
     (i32.and
      (get_local $4)
      (i32.const -8)
     )
     (i32.const 8)
    )
    (i32.const 688)
   )
   (drop
    (call $memcpy
     (i32.add
      (get_local $6)
      (i32.const 8)
     )
     (i32.add
      (get_local $7)
      (i32.const 8)
     )
     (i32.const 8)
    )
   )
   (i32.store offset=20
    (get_local $6)
    (get_local $1)
   )
   (i32.store offset=24
    (get_local $8)
    (get_local $6)
   )
   (i64.store offset=16
    (get_local $8)
    (tee_local $5
     (i64.load
      (get_local $6)
     )
    )
   )
   (i32.store offset=12
    (get_local $8)
    (tee_local $7
     (i32.load offset=20
      (get_local $6)
     )
    )
   )
   (block $label$6
    (block $label$7
     (br_if $label$7
      (i32.ge_u
       (tee_local $4
        (i32.load
         (tee_local $1
          (i32.add
           (get_local $0)
           (i32.const 28)
          )
         )
        )
       )
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 32)
        )
       )
      )
     )
     (i64.store offset=8
      (get_local $4)
      (get_local $5)
     )
     (i32.store offset=16
      (get_local $4)
      (get_local $7)
     )
     (i32.store offset=24
      (get_local $8)
      (i32.const 0)
     )
     (i32.store
      (get_local $4)
      (get_local $6)
     )
     (i32.store
      (get_local $1)
      (i32.add
       (get_local $4)
       (i32.const 24)
      )
     )
     (br $label$6)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy10163845904742744064ENS1_13loan_positionEJEE8item_ptrENS_9allocatorIS5_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS4_4itemENS_14default_deleteISB_EEEERyRlEEEvDpOT_
     (i32.add
      (get_local $0)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 16)
     )
     (i32.add
      (get_local $8)
      (i32.const 12)
     )
    )
   )
   (set_local $4
    (i32.load offset=24
     (get_local $8)
    )
   )
   (i32.store offset=24
    (get_local $8)
    (i32.const 0)
   )
   (br_if $label$2
    (i32.eqz
     (get_local $4)
    )
   )
   (call $_ZdlPv
    (get_local $4)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 32)
   )
  )
  (get_local $6)
 )
 (func $_ZNSt3__16vectorIN5eosio11multi_indexILy10163845904742744064ENS1_13loan_positionEJEE8item_ptrENS_9allocatorIS5_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS4_4itemENS_14default_deleteISB_EEEERyRlEEEvDpOT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.ge_u
      (tee_local $5
       (i32.add
        (tee_local $4
         (i32.div_s
          (i32.sub
           (i32.load offset=4
            (get_local $0)
           )
           (tee_local $6
            (i32.load
             (get_local $0)
            )
           )
          )
          (i32.const 24)
         )
        )
        (i32.const 1)
       )
      )
      (i32.const 178956971)
     )
    )
    (set_local $7
     (i32.const 178956970)
    )
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.gt_u
        (tee_local $6
         (i32.div_s
          (i32.sub
           (i32.load offset=8
            (get_local $0)
           )
           (get_local $6)
          )
          (i32.const 24)
         )
        )
        (i32.const 89478484)
       )
      )
      (br_if $label$2
       (i32.eqz
        (tee_local $7
         (select
          (get_local $5)
          (tee_local $7
           (i32.shl
            (get_local $6)
            (i32.const 1)
           )
          )
          (i32.lt_u
           (get_local $7)
           (get_local $5)
          )
         )
        )
       )
      )
     )
     (set_local $6
      (call $_Znwj
       (i32.mul
        (get_local $7)
        (i32.const 24)
       )
      )
     )
     (br $label$0)
    )
    (set_local $7
     (i32.const 0)
    )
    (set_local $6
     (i32.const 0)
    )
    (br $label$0)
   )
   (call $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
    (get_local $0)
   )
   (unreachable)
  )
  (set_local $5
   (i32.load
    (get_local $1)
   )
  )
  (i32.store
   (get_local $1)
   (i32.const 0)
  )
  (i32.store
   (tee_local $1
    (i32.add
     (get_local $6)
     (i32.mul
      (get_local $4)
      (i32.const 24)
     )
    )
   )
   (get_local $5)
  )
  (i64.store offset=8
   (get_local $1)
   (i64.load
    (get_local $2)
   )
  )
  (i32.store offset=16
   (get_local $1)
   (i32.load
    (get_local $3)
   )
  )
  (set_local $4
   (i32.add
    (get_local $6)
    (i32.mul
     (get_local $7)
     (i32.const 24)
    )
   )
  )
  (set_local $5
   (i32.add
    (get_local $1)
    (i32.const 24)
   )
  )
  (block $label$4
   (block $label$5
    (br_if $label$5
     (i32.eq
      (tee_local $6
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
      )
      (tee_local $7
       (i32.load
        (get_local $0)
       )
      )
     )
    )
    (loop $label$6
     (set_local $3
      (i32.load
       (tee_local $2
        (i32.add
         (get_local $6)
         (i32.const -24)
        )
       )
      )
     )
     (i32.store
      (get_local $2)
      (i32.const 0)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
      (get_local $3)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -8)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -8)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -12)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -12)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -16)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -16)
       )
      )
     )
     (set_local $1
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
     )
     (set_local $6
      (get_local $2)
     )
     (br_if $label$6
      (i32.ne
       (get_local $7)
       (get_local $2)
      )
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $6
     (i32.load
      (get_local $0)
     )
    )
    (br $label$4)
   )
   (set_local $6
    (get_local $7)
   )
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $5)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
   (get_local $4)
  )
  (block $label$7
   (br_if $label$7
    (i32.eq
     (get_local $7)
     (get_local $6)
    )
   )
   (loop $label$8
    (set_local $1
     (i32.load
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.const 0)
    )
    (block $label$9
     (br_if $label$9
      (i32.eqz
       (get_local $1)
      )
     )
     (call $_ZdlPv
      (get_local $1)
     )
    )
    (br_if $label$8
     (i32.ne
      (get_local $6)
      (get_local $7)
     )
    )
   )
  )
  (block $label$10
   (br_if $label$10
    (i32.eqz
     (get_local $6)
    )
   )
   (call $_ZdlPv
    (get_local $6)
   )
  )
 )
 (func $_ZN5eosio12market_state6unlendEydRKNS_15extended_symbolE (param $0 i32) (param $1 i64) (param $2 f64) (param $3 i32)
  (local $4 i64)
  (local $5 i64)
  (local $6 i32)
  (local $7 f64)
  (local $8 f64)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 112)
    )
   )
  )
  (call $eosio_assert
   (f64.gt
    (get_local $2)
    (f64.const 0)
   )
   (i32.const 1232)
  )
  (call $_ZN5eosio12market_state18adjust_lend_sharesEyRNS_11multi_indexILy10163845904742744064ENS_13loan_positionEJEEEd
   (get_local $9)
   (get_local $1)
   (i32.add
    (get_local $0)
    (i32.const 360)
   )
   (f64.neg
    (get_local $2)
   )
  )
  (call $prints
   (i32.const 1264)
  )
  (call $_ZNK5eosio11symbol_type5printEb
   (get_local $3)
   (i32.const 1)
  )
  (call $prints
   (i32.const 1280)
  )
  (call $printn
   (i64.load offset=8
    (get_local $3)
   )
  )
  (set_local $5
   (i64.load offset=8
    (get_local $3)
   )
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i64.ne
      (tee_local $4
       (i64.load
        (get_local $3)
       )
      )
      (i64.load
       (i32.add
        (get_local $0)
        (i32.const 56)
       )
      )
     )
    )
    (br_if $label$1
     (i64.ne
      (get_local $5)
      (i64.load
       (i32.add
        (get_local $0)
        (i32.const 64)
       )
      )
     )
    )
    (i64.store
     (tee_local $6
      (i32.add
       (i32.add
        (get_local $9)
        (i32.const 96)
       )
       (i32.const 8)
      )
     )
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 120)
      )
     )
    )
    (i64.store offset=96
     (get_local $9)
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 112)
      )
     )
    )
    (call $prints
     (i32.const 1296)
    )
    (call $printdf
     (get_local $2)
    )
    (call $prints
     (i32.const 1312)
    )
    (call $printdf
     (f64.load
      (tee_local $3
       (i32.add
        (get_local $0)
        (i32.const 136)
       )
      )
     )
    )
    (call $prints
     (i32.const 1344)
    )
    (f64.store
     (get_local $3)
     (tee_local $8
      (f64.sub
       (tee_local $7
        (f64.load
         (get_local $3)
        )
       )
       (get_local $2)
      )
     )
    )
    (i64.store
     (tee_local $3
      (i32.add
       (get_local $0)
       (i32.const 80)
      )
     )
     (i64.sub
      (tee_local $5
       (i64.load
        (get_local $3)
       )
      )
      (tee_local $5
       (i64.trunc_s/f64
        (f64.div
         (f64.mul
          (f64.convert_s/i64
           (get_local $5)
          )
          (get_local $2)
         )
         (get_local $7)
        )
       )
      )
     )
    )
    (call $eosio_assert
     (f64.ge
      (get_local $8)
      (f64.const 0)
     )
     (i32.const 1216)
    )
    (call $eosio_assert
     (i32.xor
      (i32.wrap/i64
       (i64.shr_u
        (i64.load
         (get_local $3)
        )
        (i64.const 63)
       )
      )
      (i32.const 1)
     )
     (i32.const 1216)
    )
    (i32.store
     (i32.add
      (get_local $9)
      (i32.const 92)
     )
     (i32.load
      (i32.add
       (i32.add
        (get_local $9)
        (i32.const 96)
       )
       (i32.const 12)
      )
     )
    )
    (i32.store
     (tee_local $3
      (i32.add
       (i32.add
        (get_local $9)
        (i32.const 72)
       )
       (i32.const 16)
      )
     )
     (i32.load
      (get_local $6)
     )
    )
    (i32.store
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 72)
      )
      (i32.const 12)
     )
     (i32.load offset=100
      (get_local $9)
     )
    )
    (i64.store offset=72
     (get_local $9)
     (get_local $5)
    )
    (i32.store offset=80
     (get_local $9)
     (i32.load offset=96
      (get_local $9)
     )
    )
    (set_local $0
     (i32.load offset=440
      (get_local $0)
     )
    )
    (i64.store
     (i32.add
      (get_local $9)
      (i32.const 8)
     )
     (i64.load offset=80
      (get_local $9)
     )
    )
    (i64.store
     (i32.add
      (get_local $9)
      (i32.const 16)
     )
     (i64.load
      (get_local $3)
     )
    )
    (i64.store
     (get_local $9)
     (i64.load offset=72
      (get_local $9)
     )
    )
    (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
     (get_local $0)
     (get_local $1)
     (get_local $9)
     (get_local $9)
    )
    (br $label$0)
   )
   (block $label$2
    (br_if $label$2
     (i64.ne
      (get_local $4)
      (i64.load
       (i32.add
        (get_local $0)
        (i32.const 152)
       )
      )
     )
    )
    (br_if $label$2
     (i64.ne
      (get_local $5)
      (i64.load
       (i32.add
        (get_local $0)
        (i32.const 160)
       )
      )
     )
    )
    (i64.store
     (tee_local $6
      (i32.add
       (i32.add
        (get_local $9)
        (i32.const 96)
       )
       (i32.const 8)
      )
     )
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 216)
      )
     )
    )
    (i64.store offset=96
     (get_local $9)
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 208)
      )
     )
    )
    (call $prints
     (i32.const 1296)
    )
    (call $printdf
     (get_local $2)
    )
    (call $prints
     (i32.const 1312)
    )
    (call $printdf
     (f64.load
      (tee_local $3
       (i32.add
        (get_local $0)
        (i32.const 232)
       )
      )
     )
    )
    (call $prints
     (i32.const 1344)
    )
    (f64.store
     (get_local $3)
     (tee_local $8
      (f64.sub
       (tee_local $7
        (f64.load
         (get_local $3)
        )
       )
       (get_local $2)
      )
     )
    )
    (i64.store
     (tee_local $3
      (i32.add
       (get_local $0)
       (i32.const 176)
      )
     )
     (i64.sub
      (tee_local $5
       (i64.load
        (get_local $3)
       )
      )
      (tee_local $5
       (i64.trunc_s/f64
        (f64.div
         (f64.mul
          (f64.convert_s/i64
           (get_local $5)
          )
          (get_local $2)
         )
         (get_local $7)
        )
       )
      )
     )
    )
    (call $eosio_assert
     (f64.ge
      (get_local $8)
      (f64.const 0)
     )
     (i32.const 1216)
    )
    (call $eosio_assert
     (i32.xor
      (i32.wrap/i64
       (i64.shr_u
        (i64.load
         (get_local $3)
        )
        (i64.const 63)
       )
      )
      (i32.const 1)
     )
     (i32.const 1216)
    )
    (i32.store
     (i32.add
      (get_local $9)
      (i32.const 68)
     )
     (i32.load
      (i32.add
       (i32.add
        (get_local $9)
        (i32.const 96)
       )
       (i32.const 12)
      )
     )
    )
    (i32.store
     (tee_local $3
      (i32.add
       (i32.add
        (get_local $9)
        (i32.const 48)
       )
       (i32.const 16)
      )
     )
     (i32.load
      (get_local $6)
     )
    )
    (i32.store
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 48)
      )
      (i32.const 12)
     )
     (i32.load offset=100
      (get_local $9)
     )
    )
    (i64.store offset=48
     (get_local $9)
     (get_local $5)
    )
    (i32.store offset=56
     (get_local $9)
     (i32.load offset=96
      (get_local $9)
     )
    )
    (set_local $0
     (i32.load offset=440
      (get_local $0)
     )
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 24)
      )
      (i32.const 8)
     )
     (i64.load offset=56
      (get_local $9)
     )
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 24)
      )
      (i32.const 16)
     )
     (i64.load
      (get_local $3)
     )
    )
    (i64.store offset=24
     (get_local $9)
     (i64.load offset=48
      (get_local $9)
     )
    )
    (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
     (get_local $0)
     (get_local $1)
     (i32.add
      (get_local $9)
      (i32.const 24)
     )
     (get_local $9)
    )
    (br $label$0)
   )
   (call $eosio_assert
    (i32.const 0)
    (i32.const 1184)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 112)
   )
  )
 )
 (func $_ZNK5eosio11symbol_type5printEb (param $0 i32) (param $1 i32)
  (local $2 i64)
  (local $3 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $3
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (get_local $1)
    )
   )
   (call $printui
    (i64.load8_u
     (get_local $0)
    )
   )
   (call $prints
    (i32.const 1360)
   )
  )
  (i32.store8 offset=15
   (get_local $3)
   (tee_local $0
    (i32.wrap/i64
     (i64.shr_u
      (tee_local $2
       (i64.load
        (get_local $0)
       )
      )
      (i64.const 8)
     )
    )
   )
  )
  (block $label$1
   (br_if $label$1
    (i32.eqz
     (i32.and
      (get_local $0)
      (i32.const 255)
     )
    )
   )
   (call $prints_l
    (i32.add
     (get_local $3)
     (i32.const 15)
    )
    (i32.const 1)
   )
   (i32.store8 offset=15
    (get_local $3)
    (tee_local $0
     (i32.wrap/i64
      (i64.shr_u
       (get_local $2)
       (i64.const 16)
      )
     )
    )
   )
   (br_if $label$1
    (i32.eqz
     (i32.and
      (get_local $0)
      (i32.const 255)
     )
    )
   )
   (call $prints_l
    (i32.add
     (get_local $3)
     (i32.const 15)
    )
    (i32.const 1)
   )
   (i32.store8 offset=15
    (get_local $3)
    (tee_local $0
     (i32.wrap/i64
      (i64.shr_u
       (get_local $2)
       (i64.const 24)
      )
     )
    )
   )
   (br_if $label$1
    (i32.eqz
     (i32.and
      (get_local $0)
      (i32.const 255)
     )
    )
   )
   (call $prints_l
    (i32.add
     (get_local $3)
     (i32.const 15)
    )
    (i32.const 1)
   )
   (i32.store8 offset=15
    (get_local $3)
    (tee_local $0
     (i32.wrap/i64
      (i64.shr_u
       (get_local $2)
       (i64.const 32)
      )
     )
    )
   )
   (br_if $label$1
    (i32.eqz
     (i32.and
      (get_local $0)
      (i32.const 255)
     )
    )
   )
   (call $prints_l
    (i32.add
     (get_local $3)
     (i32.const 15)
    )
    (i32.const 1)
   )
   (i32.store8 offset=15
    (get_local $3)
    (tee_local $0
     (i32.wrap/i64
      (i64.shr_u
       (get_local $2)
       (i64.const 40)
      )
     )
    )
   )
   (br_if $label$1
    (i32.eqz
     (i32.and
      (get_local $0)
      (i32.const 255)
     )
    )
   )
   (call $prints_l
    (i32.add
     (get_local $3)
     (i32.const 15)
    )
    (i32.const 1)
   )
   (i32.store8 offset=15
    (get_local $3)
    (tee_local $0
     (i32.wrap/i64
      (i64.shr_u
       (get_local $2)
       (i64.const 48)
      )
     )
    )
   )
   (br_if $label$1
    (i32.eqz
     (i32.and
      (get_local $0)
      (i32.const 255)
     )
    )
   )
   (call $prints_l
    (i32.add
     (get_local $3)
     (i32.const 15)
    )
    (i32.const 1)
   )
   (i32.store8 offset=15
    (get_local $3)
    (tee_local $0
     (i32.wrap/i64
      (i64.shr_u
       (get_local $2)
       (i64.const 56)
      )
     )
    )
   )
   (br_if $label$1
    (i32.eqz
     (get_local $0)
    )
   )
   (call $prints_l
    (i32.add
     (get_local $3)
     (i32.const 15)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $3)
    (i32.const 16)
   )
  )
 )
 (func $_ZN5eosio12market_state12cover_marginEyRKNS_14extended_assetE (param $0 i32) (param $1 i64) (param $2 i32)
  (local $3 i64)
  (local $4 i64)
  (set_local $4
   (i64.load offset=16
    (get_local $2)
   )
  )
  (block $label$0
   (br_if $label$0
    (i64.ne
     (tee_local $3
      (i64.load offset=8
       (get_local $2)
      )
     )
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 56)
      )
     )
    )
   )
   (br_if $label$0
    (i64.ne
     (get_local $4)
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 64)
      )
     )
    )
   )
   (call $_ZN5eosio12market_state12cover_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetE
    (get_local $0)
    (get_local $1)
    (i32.add
     (get_local $0)
     (i32.const 280)
    )
    (i32.add
     (get_local $0)
     (i32.const 48)
    )
    (get_local $2)
   )
   (return)
  )
  (block $label$1
   (br_if $label$1
    (i64.ne
     (get_local $3)
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 152)
      )
     )
    )
   )
   (br_if $label$1
    (i64.ne
     (get_local $4)
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 160)
      )
     )
    )
   )
   (call $_ZN5eosio12market_state12cover_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetE
    (get_local $0)
    (get_local $1)
    (i32.add
     (get_local $0)
     (i32.const 320)
    )
    (i32.add
     (get_local $0)
     (i32.const 144)
    )
    (get_local $2)
   )
   (return)
  )
  (call $eosio_assert
   (i32.const 0)
   (i32.const 1376)
  )
 )
 (func $_ZN5eosio12market_state12cover_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetE (param $0 i32) (param $1 i64) (param $2 i32) (param $3 i32) (param $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (local $12 i64)
  (local $13 i64)
  (local $14 i64)
  (local $15 f64)
  (local $16 i32)
  (local $17 i32)
  (local $18 f64)
  (local $19 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $19
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 704)
    )
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $17
      (i32.load
       (i32.add
        (get_local $2)
        (i32.const 28)
       )
      )
     )
     (tee_local $10
      (i32.load offset=24
       (get_local $2)
      )
     )
    )
   )
   (set_local $16
    (i32.add
     (get_local $17)
     (i32.const -24)
    )
   )
   (set_local $5
    (i32.sub
     (i32.const 0)
     (get_local $10)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i64.eq
      (i64.load
       (i32.load
        (get_local $16)
       )
      )
      (get_local $1)
     )
    )
    (set_local $17
     (get_local $16)
    )
    (set_local $16
     (tee_local $6
      (i32.add
       (get_local $16)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $6)
       (get_local $5)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $17)
      (get_local $10)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=64
       (tee_local $16
        (i32.load
         (i32.add
          (get_local $17)
          (i32.const -24)
         )
        )
       )
      )
      (get_local $2)
     )
     (i32.const 224)
    )
    (br $label$2)
   )
   (set_local $16
    (i32.const 0)
   )
   (br_if $label$2
    (i32.lt_s
     (tee_local $6
      (call $db_find_i64
       (i64.load
        (get_local $2)
       )
       (i64.load offset=8
        (get_local $2)
       )
       (i64.const -7949197150146002944)
       (get_local $1)
      )
     )
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=64
      (tee_local $16
       (call $_ZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE31load_object_by_primary_iteratorEl
        (get_local $2)
        (get_local $6)
       )
      )
     )
     (get_local $2)
    )
    (i32.const 224)
   )
  )
  (call $eosio_assert
   (tee_local $7
    (i32.ne
     (get_local $16)
     (i32.const 0)
    )
   )
   (i32.const 1408)
  )
  (call $eosio_assert
   (i64.ge_s
    (i64.load offset=8
     (get_local $16)
    )
    (i64.load
     (get_local $4)
    )
   )
   (i32.const 1440)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $19)
     (i32.const 360)
    )
    (tee_local $6
     (i32.add
      (get_local $0)
      (i32.const 8)
     )
    )
    (i32.const 232)
   )
  )
  (i64.store
   (tee_local $8
    (i32.add
     (i32.add
      (get_local $19)
      (i32.const 312)
     )
     (i32.const 16)
    )
   )
   (i64.load
    (tee_local $17
     (i32.add
      (get_local $4)
      (i32.const 16)
     )
    )
   )
  )
  (i64.store
   (tee_local $9
    (i32.add
     (i32.add
      (get_local $19)
      (i32.const 312)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (tee_local $5
     (i32.add
      (get_local $4)
      (i32.const 8)
     )
    )
   )
  )
  (i64.store offset=312
   (get_local $19)
   (i64.load
    (get_local $4)
   )
  )
  (set_local $14
   (i64.load
    (tee_local $10
     (i32.add
      (get_local $16)
      (i32.const 48)
     )
    )
   )
  )
  (i64.store offset=296
   (get_local $19)
   (i64.load
    (tee_local $11
     (i32.add
      (get_local $16)
      (i32.const 40)
     )
    )
   )
  )
  (i64.store offset=304
   (get_local $19)
   (get_local $14)
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $19)
     (i32.const 120)
    )
    (i32.const 16)
   )
   (i64.load
    (get_local $8)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $19)
     (i32.const 120)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $9)
   )
  )
  (i64.store offset=120
   (get_local $19)
   (i64.load offset=312
    (get_local $19)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $19)
     (i32.const 104)
    )
    (i32.const 8)
   )
   (i64.load offset=304
    (get_local $19)
   )
  )
  (i64.store offset=104
   (get_local $19)
   (i64.load offset=296
    (get_local $19)
   )
  )
  (call $_ZN5eosio14exchange_state7convertENS_14extended_assetENS_15extended_symbolE
   (i32.add
    (get_local $19)
    (i32.const 336)
   )
   (i32.add
    (get_local $19)
    (i32.const 360)
   )
   (i32.add
    (get_local $19)
    (i32.const 120)
   )
   (i32.add
    (get_local $19)
    (i32.const 104)
   )
  )
  (i64.store
   (tee_local $8
    (i32.add
     (i32.add
      (get_local $19)
      (i32.const 248)
     )
     (i32.const 16)
    )
   )
   (i64.load
    (i32.add
     (i32.add
      (get_local $19)
      (i32.const 336)
     )
     (i32.const 16)
    )
   )
  )
  (i64.store
   (tee_local $9
    (i32.add
     (i32.add
      (get_local $19)
      (i32.const 248)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (i32.add
      (get_local $19)
      (i32.const 336)
     )
     (i32.const 8)
    )
   )
  )
  (i64.store offset=248
   (get_local $19)
   (i64.load offset=336
    (get_local $19)
   )
  )
  (set_local $14
   (i64.load
    (get_local $17)
   )
  )
  (i64.store offset=232
   (get_local $19)
   (i64.load
    (get_local $5)
   )
  )
  (i64.store offset=240
   (get_local $19)
   (get_local $14)
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $19)
     (i32.const 80)
    )
    (i32.const 16)
   )
   (i64.load
    (get_local $8)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $19)
     (i32.const 80)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $9)
   )
  )
  (i64.store offset=80
   (get_local $19)
   (i64.load offset=248
    (get_local $19)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $19)
     (i32.const 64)
    )
    (i32.const 8)
   )
   (i64.load offset=240
    (get_local $19)
   )
  )
  (i64.store offset=64
   (get_local $19)
   (i64.load offset=232
    (get_local $19)
   )
  )
  (call $_ZN5eosio14exchange_state7convertENS_14extended_assetENS_15extended_symbolE
   (i32.add
    (get_local $19)
    (i32.const 272)
   )
   (get_local $6)
   (i32.add
    (get_local $19)
    (i32.const 80)
   )
   (i32.add
    (get_local $19)
    (i32.const 64)
   )
  )
  (call $eosio_assert
   (i64.ge_s
    (tee_local $14
     (i64.load offset=272
      (get_local $19)
     )
    )
    (i64.load
     (get_local $4)
    )
   )
   (i32.const 1488)
  )
  (call $eosio_assert
   (i64.eq
    (tee_local $12
     (i64.load offset=288
      (get_local $19)
     )
    )
    (i64.load
     (get_local $17)
    )
   )
   (i32.const 800)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load
     (get_local $5)
    )
    (tee_local $13
     (i64.load offset=280
      (get_local $19)
     )
    )
   )
   (i32.const 816)
  )
  (call $eosio_assert
   (i64.gt_s
    (tee_local $14
     (i64.sub
      (get_local $14)
      (i64.load
       (get_local $4)
      )
     )
    )
    (i64.const -4611686018427387904)
   )
   (i32.const 864)
  )
  (call $eosio_assert
   (i64.lt_s
    (get_local $14)
    (i64.const 4611686018427387904)
   )
   (i32.const 896)
  )
  (i64.store offset=192
   (get_local $19)
   (get_local $13)
  )
  (i64.store offset=184
   (get_local $19)
   (get_local $14)
  )
  (i64.store offset=200
   (get_local $19)
   (get_local $12)
  )
  (i64.store offset=176
   (get_local $19)
   (i64.load
    (get_local $10)
   )
  )
  (i64.store offset=168
   (get_local $19)
   (i64.load
    (get_local $11)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $19)
     (i32.const 40)
    )
    (i32.const 8)
   )
   (i64.load offset=192
    (get_local $19)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $19)
     (i32.const 40)
    )
    (i32.const 20)
   )
   (i32.load
    (i32.add
     (i32.add
      (get_local $19)
      (i32.const 184)
     )
     (i32.const 20)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $19)
     (i32.const 40)
    )
    (i32.const 16)
   )
   (i32.load offset=200
    (get_local $19)
   )
  )
  (i64.store offset=40
   (get_local $19)
   (i64.load offset=184
    (get_local $19)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $19)
     (i32.const 24)
    )
    (i32.const 8)
   )
   (i64.load offset=176
    (get_local $19)
   )
  )
  (i64.store offset=24
   (get_local $19)
   (i64.load offset=168
    (get_local $19)
   )
  )
  (call $_ZN5eosio14exchange_state7convertENS_14extended_assetENS_15extended_symbolE
   (i32.add
    (get_local $19)
    (i32.const 208)
   )
   (get_local $6)
   (i32.add
    (get_local $19)
    (i32.const 40)
   )
   (i32.add
    (get_local $19)
    (i32.const 24)
   )
  )
  (i64.store offset=336
   (get_local $19)
   (tee_local $14
    (i64.sub
     (i64.load offset=336
      (get_local $19)
     )
     (i64.load offset=208
      (get_local $19)
     )
    )
   )
  )
  (block $label$4
   (block $label$5
    (br_if $label$5
     (i64.ne
      (i64.load offset=8
       (get_local $16)
      )
      (i64.load
       (get_local $4)
      )
     )
    )
    (call $eosio_assert
     (i64.eq
      (i64.load
       (get_local $10)
      )
      (i64.load offset=352
       (get_local $19)
      )
     )
     (i32.const 800)
    )
    (set_local $13
     (i64.load offset=32
      (get_local $16)
     )
    )
    (call $eosio_assert
     (i64.eq
      (i64.load offset=344
       (get_local $19)
      )
      (tee_local $12
       (i64.load
        (get_local $11)
       )
      )
     )
     (i32.const 816)
    )
    (call $eosio_assert
     (i64.gt_s
      (tee_local $14
       (i64.sub
        (get_local $13)
        (get_local $14)
       )
      )
      (i64.const -4611686018427387904)
     )
     (i32.const 864)
    )
    (call $eosio_assert
     (i64.lt_s
      (get_local $14)
      (i64.const 4611686018427387904)
     )
     (i32.const 896)
    )
    (set_local $13
     (i64.load
      (get_local $10)
     )
    )
    (call $eosio_assert
     (get_local $7)
     (i32.const 928)
    )
    (call $eosio_assert
     (get_local $7)
     (i32.const 1152)
    )
    (block $label$6
     (br_if $label$6
      (i32.lt_s
       (tee_local $6
        (call $db_next_i64
         (i32.load offset=68
          (get_local $16)
         )
         (i32.add
          (get_local $19)
          (i32.const 592)
         )
        )
       )
       (i32.const 0)
      )
     )
     (drop
      (call $_ZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE31load_object_by_primary_iteratorEl
       (get_local $2)
       (get_local $6)
      )
     )
    )
    (call $_ZN5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE5eraseERKS1_
     (get_local $2)
     (get_local $16)
    )
    (set_local $16
     (i32.const 0)
    )
    (block $label$7
     (br_if $label$7
      (i32.lt_s
       (tee_local $6
        (call $db_lowerbound_i64
         (i64.load
          (get_local $2)
         )
         (i64.load offset=8
          (get_local $2)
         )
         (i64.const -7949197150146002944)
         (i64.const 0)
        )
       )
       (i32.const 0)
      )
     )
     (set_local $16
      (call $_ZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE31load_object_by_primary_iteratorEl
       (get_local $2)
       (get_local $6)
      )
     )
    )
    (i64.store offset=152
     (get_local $19)
     (get_local $12)
    )
    (set_local $6
     (i32.load offset=440
      (get_local $0)
     )
    )
    (i64.store
     (i32.add
      (get_local $19)
      (i32.const 8)
     )
     (get_local $12)
    )
    (i64.store offset=160
     (get_local $19)
     (get_local $13)
    )
    (i64.store
     (i32.add
      (get_local $19)
      (i32.const 16)
     )
     (get_local $13)
    )
    (i64.store offset=144
     (get_local $19)
     (get_local $14)
    )
    (i64.store
     (get_local $19)
     (get_local $14)
    )
    (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
     (get_local $6)
     (get_local $1)
     (get_local $19)
     (get_local $19)
    )
    (br $label$4)
   )
   (call $eosio_assert
    (get_local $7)
    (i32.const 352)
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=64
      (get_local $16)
     )
     (get_local $2)
    )
    (i32.const 400)
   )
   (call $eosio_assert
    (i64.eq
     (i64.load
      (get_local $2)
     )
     (call $current_receiver)
    )
    (i32.const 448)
   )
   (i64.store offset=32
    (get_local $16)
    (tee_local $14
     (i64.sub
      (i64.load offset=32
       (get_local $16)
      )
      (get_local $14)
     )
    )
   )
   (i64.store offset=680
    (get_local $19)
    (i64.trunc_u/f64
     (f64.mul
      (f64.load
       (tee_local $6
        (i32.add
         (get_local $16)
         (i32.const 56)
        )
       )
      )
      (f64.const 1e6)
     )
    )
   )
   (set_local $1
    (i64.load
     (get_local $16)
    )
   )
   (i64.store offset=8
    (get_local $16)
    (tee_local $12
     (i64.sub
      (i64.load offset=8
       (get_local $16)
      )
      (i64.load
       (get_local $4)
      )
     )
    )
   )
   (f64.store
    (get_local $6)
    (f64.div
     (f64.convert_s/i64
      (get_local $12)
     )
     (f64.convert_s/i64
      (get_local $14)
     )
    )
   )
   (call $eosio_assert
    (i32.const 1)
    (i32.const 544)
   )
   (i32.store offset=672
    (get_local $19)
    (i32.add
     (i32.add
      (get_local $19)
      (i32.const 592)
     )
     (i32.const 64)
    )
   )
   (i32.store offset=668
    (get_local $19)
    (i32.add
     (get_local $19)
     (i32.const 592)
    )
   )
   (i32.store offset=664
    (get_local $19)
    (i32.add
     (get_local $19)
     (i32.const 592)
    )
   )
   (drop
    (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_15margin_positionE
     (i32.add
      (get_local $19)
      (i32.const 664)
     )
     (get_local $16)
    )
   )
   (call $db_update_i64
    (i32.load offset=68
     (get_local $16)
    )
    (i64.const 0)
    (i32.add
     (get_local $19)
     (i32.const 592)
    )
    (i32.const 64)
   )
   (block $label$8
    (br_if $label$8
     (i64.lt_u
      (get_local $1)
      (i64.load offset=16
       (get_local $2)
      )
     )
    )
    (i64.store
     (i32.add
      (get_local $2)
      (i32.const 16)
     )
     (select
      (i64.const -2)
      (i64.add
       (get_local $1)
       (i64.const 1)
      )
      (i64.gt_u
       (get_local $1)
       (i64.const -3)
      )
     )
    )
   )
   (i64.store offset=696
    (get_local $19)
    (i64.trunc_u/f64
     (f64.mul
      (f64.load
       (get_local $6)
      )
      (f64.const 1e6)
     )
    )
   )
   (br_if $label$4
    (i32.eqz
     (call $memcmp
      (i32.add
       (get_local $19)
       (i32.const 680)
      )
      (i32.add
       (get_local $19)
       (i32.const 696)
      )
      (i32.const 8)
     )
    )
   )
   (block $label$9
    (br_if $label$9
     (i32.gt_s
      (tee_local $6
       (i32.load
        (tee_local $17
         (i32.add
          (get_local $16)
          (i32.const 72)
         )
        )
       )
      )
      (i32.const -1)
     )
    )
    (i32.store
     (get_local $17)
     (tee_local $6
      (call $db_idx64_find_primary
       (i64.load
        (get_local $2)
       )
       (i64.load offset=8
        (get_local $2)
       )
       (i64.const -7949197150146002944)
       (i32.add
        (get_local $19)
        (i32.const 688)
       )
       (get_local $1)
      )
     )
    )
   )
   (call $db_idx64_update
    (get_local $6)
    (i64.const 0)
    (i32.add
     (get_local $19)
     (i32.const 696)
    )
   )
  )
  (i64.store
   (tee_local $6
    (i32.add
     (get_local $3)
     (i32.const 56)
    )
   )
   (i64.sub
    (i64.load
     (get_local $6)
    )
    (i64.load
     (get_local $4)
    )
   )
  )
  (block $label$10
   (block $label$11
    (block $label$12
     (br_if $label$12
      (i32.eqz
       (get_local $16)
      )
     )
     (br_if $label$11
      (i32.eqz
       (i32.or
        (f64.ge
         (tee_local $18
          (f64.load offset=56
           (get_local $16)
          )
         )
         (tee_local $15
          (f64.load
           (tee_local $16
            (i32.add
             (get_local $3)
             (i32.const 80)
            )
           )
          )
         )
        )
        (i32.or
         (f64.ne
          (get_local $18)
          (get_local $18)
         )
         (f64.ne
          (get_local $15)
          (get_local $15)
         )
        )
       )
      )
     )
     (br $label$10)
    )
    (set_local $16
     (i32.add
      (get_local $3)
      (i32.const 80)
     )
    )
    (set_local $18
     (f64.const 1797693134862315708145274e284)
    )
   )
   (f64.store
    (get_local $16)
    (get_local $18)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $19)
    (i32.const 704)
   )
  )
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_15margin_positionE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (get_local $1)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 40)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 48)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 56)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio12market_state13update_marginEyRKNS_14extended_assetES3_ (param $0 i32) (param $1 i64) (param $2 i32) (param $3 i32)
  (local $4 i64)
  (local $5 i64)
  (set_local $5
   (i64.load offset=16
    (get_local $2)
   )
  )
  (block $label$0
   (br_if $label$0
    (i64.ne
     (tee_local $4
      (i64.load offset=8
       (get_local $2)
      )
     )
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 56)
      )
     )
    )
   )
   (br_if $label$0
    (i64.ne
     (get_local $5)
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 64)
      )
     )
    )
   )
   (call $_ZN5eosio12market_state13adjust_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetESG_
    (get_local $0)
    (get_local $1)
    (i32.add
     (get_local $0)
     (i32.const 280)
    )
    (i32.add
     (get_local $0)
     (i32.const 48)
    )
    (get_local $2)
    (get_local $3)
   )
   (return)
  )
  (block $label$1
   (br_if $label$1
    (i64.ne
     (get_local $4)
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 152)
      )
     )
    )
   )
   (br_if $label$1
    (i64.ne
     (get_local $5)
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 160)
      )
     )
    )
   )
   (call $_ZN5eosio12market_state13adjust_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetESG_
    (get_local $0)
    (get_local $1)
    (i32.add
     (get_local $0)
     (i32.const 320)
    )
    (i32.add
     (get_local $0)
     (i32.const 144)
    )
    (get_local $2)
    (get_local $3)
   )
   (return)
  )
  (call $eosio_assert
   (i32.const 0)
   (i32.const 1376)
  )
 )
 (func $_ZN5eosio12market_state13adjust_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetESG_ (param $0 i32) (param $1 i64) (param $2 i32) (param $3 i32) (param $4 i32) (param $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i64)
  (local $10 f64)
  (local $11 i64)
  (local $12 f64)
  (local $13 i32)
  (local $14 i32)
  (local $15 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $15
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 112)
    )
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $14
      (i32.load
       (i32.add
        (get_local $2)
        (i32.const 28)
       )
      )
     )
     (tee_local $6
      (i32.load offset=24
       (get_local $2)
      )
     )
    )
   )
   (set_local $13
    (i32.add
     (get_local $14)
     (i32.const -24)
    )
   )
   (set_local $7
    (i32.sub
     (i32.const 0)
     (get_local $6)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i64.eq
      (i64.load
       (i32.load
        (get_local $13)
       )
      )
      (get_local $1)
     )
    )
    (set_local $14
     (get_local $13)
    )
    (set_local $13
     (tee_local $8
      (i32.add
       (get_local $13)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $8)
       (get_local $7)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (block $label$4
     (block $label$5
      (block $label$6
       (block $label$7
        (block $label$8
         (br_if $label$8
          (i32.eq
           (get_local $14)
           (get_local $6)
          )
         )
         (call $eosio_assert
          (i32.eq
           (i32.load offset=64
            (tee_local $8
             (i32.load
              (i32.add
               (get_local $14)
               (i32.const -24)
              )
             )
            )
           )
           (get_local $2)
          )
          (i32.const 224)
         )
         (br_if $label$7
          (get_local $8)
         )
         (br $label$6)
        )
        (br_if $label$6
         (i32.lt_s
          (tee_local $13
           (call $db_find_i64
            (i64.load
             (get_local $2)
            )
            (i64.load offset=8
             (get_local $2)
            )
            (i64.const -7949197150146002944)
            (get_local $1)
           )
          )
          (i32.const 0)
         )
        )
        (call $eosio_assert
         (i32.eq
          (i32.load offset=64
           (tee_local $8
            (call $_ZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE31load_object_by_primary_iteratorEl
             (get_local $2)
             (get_local $13)
            )
           )
          )
          (get_local $2)
         )
         (i32.const 224)
        )
       )
       (br_if $label$5
        (i64.ne
         (i64.load offset=8
          (get_local $8)
         )
         (i64.sub
          (i64.const 0)
          (i64.load
           (get_local $4)
          )
         )
        )
       )
       (call $eosio_assert
        (i64.eq
         (i64.load offset=32
          (get_local $8)
         )
         (i64.sub
          (i64.const 0)
          (i64.load
           (get_local $5)
          )
         )
        )
        (i32.const 1584)
       )
       (call $eosio_assert
        (i32.const 1)
        (i32.const 928)
       )
       (call $eosio_assert
        (i32.const 1)
        (i32.const 1152)
       )
       (set_local $13
        (i32.const 0)
       )
       (block $label$9
        (br_if $label$9
         (i32.lt_s
          (tee_local $14
           (call $db_next_i64
            (i32.load offset=68
             (get_local $8)
            )
            (get_local $15)
           )
          )
          (i32.const 0)
         )
        )
        (drop
         (call $_ZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE31load_object_by_primary_iteratorEl
          (get_local $2)
          (get_local $14)
         )
        )
       )
       (call $_ZN5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE5eraseERKS1_
        (get_local $2)
        (get_local $8)
       )
       (br_if $label$2
        (i32.lt_s
         (tee_local $8
          (call $db_lowerbound_i64
           (i64.load
            (get_local $2)
           )
           (i64.load offset=8
            (get_local $2)
           )
           (i64.const -7949197150146002944)
           (i64.const 0)
          )
         )
         (i32.const 0)
        )
       )
       (set_local $13
        (call $_ZNK5eosio11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS1_yXadL_ZNKS1_8get_callEvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $2)
         (get_local $8)
        )
       )
       (br $label$2)
      )
      (call $eosio_assert
       (i64.gt_s
        (i64.load
         (get_local $4)
        )
        (i64.const 0)
       )
       (i32.const 1520)
      )
      (call $eosio_assert
       (i64.gt_s
        (i64.load
         (get_local $5)
        )
        (i64.const 0)
       )
       (i32.const 1552)
      )
      (call $eosio_assert
       (i64.eq
        (i64.load
         (get_local $2)
        )
        (call $current_receiver)
       )
       (i32.const 288)
      )
      (set_local $8
       (call $_ZN5eosio15margin_positionC2Ev
        (tee_local $13
         (call $_Znwj
          (i32.const 80)
         )
        )
       )
      )
      (i32.store offset=64
       (get_local $13)
       (get_local $2)
      )
      (i64.store
       (get_local $13)
       (get_local $1)
      )
      (i32.store
       (i32.add
        (get_local $13)
        (i32.const 28)
       )
       (i32.load
        (i32.add
         (get_local $4)
         (i32.const 20)
        )
       )
      )
      (i32.store
       (i32.add
        (get_local $13)
        (i32.const 24)
       )
       (i32.load
        (i32.add
         (get_local $4)
         (i32.const 16)
        )
       )
      )
      (i32.store
       (i32.add
        (get_local $13)
        (i32.const 20)
       )
       (i32.load
        (i32.add
         (get_local $4)
         (i32.const 12)
        )
       )
      )
      (i32.store
       (i32.add
        (get_local $13)
        (i32.const 16)
       )
       (i32.load
        (i32.add
         (get_local $4)
         (i32.const 8)
        )
       )
      )
      (i32.store
       (i32.add
        (get_local $13)
        (i32.const 12)
       )
       (i32.load
        (i32.add
         (get_local $4)
         (i32.const 4)
        )
       )
      )
      (i32.store offset=8
       (get_local $13)
       (i32.load
        (get_local $4)
       )
      )
      (i64.store
       (i32.add
        (get_local $13)
        (i32.const 48)
       )
       (i64.load
        (i32.add
         (get_local $5)
         (i32.const 16)
        )
       )
      )
      (i64.store
       (i32.add
        (get_local $13)
        (i32.const 40)
       )
       (i64.load
        (i32.add
         (get_local $5)
         (i32.const 8)
        )
       )
      )
      (i64.store offset=32
       (get_local $13)
       (i64.load
        (get_local $5)
       )
      )
      (f64.store offset=56
       (get_local $13)
       (f64.div
        (f64.convert_s/i64
         (i64.load offset=8
          (get_local $13)
         )
        )
        (f64.convert_s/i64
         (i64.load offset=32
          (get_local $13)
         )
        )
       )
      )
      (i32.store offset=80
       (get_local $15)
       (i32.add
        (get_local $15)
        (i32.const 64)
       )
      )
      (i32.store offset=76
       (get_local $15)
       (get_local $15)
      )
      (i32.store offset=72
       (get_local $15)
       (get_local $15)
      )
      (drop
       (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_15margin_positionE
        (i32.add
         (get_local $15)
         (i32.const 72)
        )
        (get_local $8)
       )
      )
      (i32.store offset=68
       (get_local $13)
       (call $db_store_i64
        (i64.load offset=8
         (get_local $2)
        )
        (i64.const -7949197150146002944)
        (get_local $1)
        (tee_local $9
         (i64.load
          (get_local $13)
         )
        )
        (get_local $15)
        (i32.const 64)
       )
      )
      (block $label$10
       (br_if $label$10
        (i64.lt_u
         (get_local $9)
         (i64.load offset=16
          (get_local $2)
         )
        )
       )
       (i64.store
        (i32.add
         (get_local $2)
         (i32.const 16)
        )
        (select
         (i64.const -2)
         (i64.add
          (get_local $9)
          (i64.const 1)
         )
         (i64.gt_u
          (get_local $9)
          (i64.const -3)
         )
        )
       )
      )
      (set_local $9
       (i64.load
        (i32.add
         (get_local $2)
         (i32.const 8)
        )
       )
      )
      (set_local $11
       (i64.load
        (get_local $13)
       )
      )
      (i64.store offset=104
       (get_local $15)
       (i64.trunc_u/f64
        (f64.mul
         (f64.load
          (i32.add
           (get_local $13)
           (i32.const 56)
          )
         )
         (f64.const 1e6)
        )
       )
      )
      (i32.store offset=72
       (get_local $13)
       (call $db_idx64_store
        (get_local $9)
        (i64.const -7949197150146002944)
        (get_local $1)
        (get_local $11)
        (i32.add
         (get_local $15)
         (i32.const 104)
        )
       )
      )
      (i32.store offset=72
       (get_local $15)
       (get_local $13)
      )
      (i64.store
       (get_local $15)
       (tee_local $1
        (i64.load
         (get_local $13)
        )
       )
      )
      (i32.store offset=104
       (get_local $15)
       (tee_local $14
        (i32.load
         (i32.add
          (get_local $13)
          (i32.const 68)
         )
        )
       )
      )
      (br_if $label$4
       (i32.ge_u
        (tee_local $8
         (i32.load
          (i32.add
           (get_local $2)
           (i32.const 28)
          )
         )
        )
        (i32.load
         (i32.add
          (get_local $2)
          (i32.const 32)
         )
        )
       )
      )
      (i64.store offset=8
       (get_local $8)
       (get_local $1)
      )
      (i32.store offset=16
       (get_local $8)
       (get_local $14)
      )
      (i32.store offset=72
       (get_local $15)
       (i32.const 0)
      )
      (i32.store
       (get_local $8)
       (get_local $13)
      )
      (i32.store
       (i32.add
        (get_local $2)
        (i32.const 28)
       )
       (i32.add
        (get_local $8)
        (i32.const 24)
       )
      )
      (br $label$3)
     )
     (call $eosio_assert
      (i32.const 1)
      (i32.const 352)
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=64
        (get_local $8)
       )
       (get_local $2)
      )
      (i32.const 400)
     )
     (call $eosio_assert
      (i64.eq
       (i64.load
        (get_local $2)
       )
       (call $current_receiver)
      )
      (i32.const 448)
     )
     (i64.store offset=88
      (get_local $15)
      (i64.trunc_u/f64
       (f64.mul
        (f64.load
         (tee_local $13
          (i32.add
           (get_local $8)
           (i32.const 56)
          )
         )
        )
        (f64.const 1e6)
       )
      )
     )
     (set_local $1
      (i64.load
       (get_local $8)
      )
     )
     (call $eosio_assert
      (i64.eq
       (i64.load offset=8
        (get_local $4)
       )
       (i64.load
        (i32.add
         (get_local $8)
         (i32.const 16)
        )
       )
      )
      (i32.const 1632)
     )
     (i64.store offset=8
      (get_local $8)
      (tee_local $9
       (i64.add
        (i64.load offset=8
         (get_local $8)
        )
        (i64.load
         (get_local $4)
        )
       )
      )
     )
     (call $eosio_assert
      (i64.gt_s
       (get_local $9)
       (i64.const -4611686018427387904)
      )
      (i32.const 1680)
     )
     (call $eosio_assert
      (i64.lt_s
       (i64.load offset=8
        (get_local $8)
       )
       (i64.const 4611686018427387904)
      )
      (i32.const 1712)
     )
     (call $eosio_assert
      (i64.eq
       (i64.load offset=8
        (get_local $5)
       )
       (i64.load
        (i32.add
         (get_local $8)
         (i32.const 40)
        )
       )
      )
      (i32.const 1632)
     )
     (i64.store offset=32
      (get_local $8)
      (tee_local $9
       (i64.add
        (i64.load offset=32
         (get_local $8)
        )
        (i64.load
         (get_local $5)
        )
       )
      )
     )
     (call $eosio_assert
      (i64.gt_s
       (get_local $9)
       (i64.const -4611686018427387904)
      )
      (i32.const 1680)
     )
     (call $eosio_assert
      (i64.lt_s
       (i64.load offset=32
        (get_local $8)
       )
       (i64.const 4611686018427387904)
      )
      (i32.const 1712)
     )
     (f64.store
      (get_local $13)
      (f64.div
       (f64.convert_s/i64
        (i64.load offset=8
         (get_local $8)
        )
       )
       (f64.convert_s/i64
        (i64.load offset=32
         (get_local $8)
        )
       )
      )
     )
     (call $eosio_assert
      (i64.eq
       (get_local $1)
       (i64.load
        (get_local $8)
       )
      )
      (i32.const 544)
     )
     (i32.store offset=80
      (get_local $15)
      (i32.add
       (get_local $15)
       (i32.const 64)
      )
     )
     (i32.store offset=76
      (get_local $15)
      (get_local $15)
     )
     (i32.store offset=72
      (get_local $15)
      (get_local $15)
     )
     (drop
      (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_15margin_positionE
       (i32.add
        (get_local $15)
        (i32.const 72)
       )
       (get_local $8)
      )
     )
     (call $db_update_i64
      (i32.load offset=68
       (get_local $8)
      )
      (i64.const 0)
      (get_local $15)
      (i32.const 64)
     )
     (block $label$11
      (br_if $label$11
       (i64.lt_u
        (get_local $1)
        (i64.load offset=16
         (get_local $2)
        )
       )
      )
      (i64.store
       (i32.add
        (get_local $2)
        (i32.const 16)
       )
       (select
        (i64.const -2)
        (i64.add
         (get_local $1)
         (i64.const 1)
        )
        (i64.gt_u
         (get_local $1)
         (i64.const -3)
        )
       )
      )
     )
     (i64.store offset=104
      (get_local $15)
      (i64.trunc_u/f64
       (f64.mul
        (f64.load
         (get_local $13)
        )
        (f64.const 1e6)
       )
      )
     )
     (block $label$12
      (br_if $label$12
       (i32.eqz
        (call $memcmp
         (i32.add
          (get_local $15)
          (i32.const 88)
         )
         (i32.add
          (get_local $15)
          (i32.const 104)
         )
         (i32.const 8)
        )
       )
      )
      (block $label$13
       (br_if $label$13
        (i32.gt_s
         (tee_local $13
          (i32.load
           (tee_local $14
            (i32.add
             (get_local $8)
             (i32.const 72)
            )
           )
          )
         )
         (i32.const -1)
        )
       )
       (i32.store
        (get_local $14)
        (tee_local $13
         (call $db_idx64_find_primary
          (i64.load
           (get_local $2)
          )
          (i64.load offset=8
           (get_local $2)
          )
          (i64.const -7949197150146002944)
          (i32.add
           (get_local $15)
           (i32.const 96)
          )
          (get_local $1)
         )
        )
       )
      )
      (call $db_idx64_update
       (get_local $13)
       (i64.const 0)
       (i32.add
        (get_local $15)
        (i32.const 104)
       )
      )
     )
     (set_local $13
      (get_local $8)
     )
     (br $label$2)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy10497546923563548672ENS1_15margin_positionEJNS1_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS3_yXadL_ZNKS3_8get_callEvEEEEEEEE8item_ptrENS_9allocatorISB_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINSA_4itemENS_14default_deleteISH_EEEERyRlEEEvDpOT_
     (i32.add
      (get_local $2)
      (i32.const 24)
     )
     (i32.add
      (get_local $15)
      (i32.const 72)
     )
     (get_local $15)
     (i32.add
      (get_local $15)
      (i32.const 104)
     )
    )
   )
   (set_local $8
    (i32.load offset=72
     (get_local $15)
    )
   )
   (i32.store offset=72
    (get_local $15)
    (i32.const 0)
   )
   (br_if $label$2
    (i32.eqz
     (get_local $8)
    )
   )
   (call $_ZdlPv
    (get_local $8)
   )
  )
  (call $eosio_assert
   (i64.eq
    (i64.load offset=8
     (get_local $4)
    )
    (i64.load
     (i32.add
      (get_local $3)
      (i32.const 64)
     )
    )
   )
   (i32.const 1632)
  )
  (i64.store
   (tee_local $8
    (i32.add
     (get_local $3)
     (i32.const 56)
    )
   )
   (tee_local $1
    (i64.add
     (i64.load
      (get_local $8)
     )
     (i64.load
      (get_local $4)
     )
    )
   )
  )
  (call $eosio_assert
   (i64.gt_s
    (get_local $1)
    (i64.const -4611686018427387904)
   )
   (i32.const 1680)
  )
  (call $eosio_assert
   (i64.lt_s
    (i64.load
     (get_local $8)
    )
    (i64.const 4611686018427387904)
   )
   (i32.const 1712)
  )
  (call $eosio_assert
   (i64.le_s
    (i64.load
     (get_local $8)
    )
    (i64.load offset=32
     (get_local $3)
    )
   )
   (i32.const 1744)
  )
  (block $label$14
   (block $label$15
    (br_if $label$15
     (i32.eqz
      (get_local $13)
     )
    )
    (block $label$16
     (br_if $label$16
      (i32.or
       (f64.ge
        (tee_local $10
         (f64.load offset=56
          (get_local $13)
         )
        )
        (tee_local $12
         (f64.load
          (tee_local $13
           (i32.add
            (get_local $3)
            (i32.const 80)
           )
          )
         )
        )
       )
       (i32.or
        (f64.ne
         (get_local $10)
         (get_local $10)
        )
        (f64.ne
         (get_local $12)
         (get_local $12)
        )
       )
      )
     )
     (f64.store
      (get_local $13)
      (get_local $10)
     )
    )
    (call $eosio_assert
     (i32.xor
      (call $_ZNK5eosio14exchange_state20requires_margin_callERKNS0_9connectorE
       (i32.add
        (get_local $0)
        (i32.const 8)
       )
       (get_local $3)
      )
      (i32.const 1)
     )
     (i32.const 1792)
    )
    (br $label$14)
   )
   (i64.store
    (i32.add
     (get_local $3)
     (i32.const 80)
    )
    (i64.const 9218868437227405311)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $15)
    (i32.const 112)
   )
  )
 )
 (func $_ZN5eosio12market_state4saveEv (param $0 i32)
  (local $1 i64)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $4
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 240)
    )
   )
  )
  (call $eosio_assert
   (i32.ne
    (tee_local $2
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 448)
      )
     )
    )
    (i32.const 0)
   )
   (i32.const 352)
  )
  (call $eosio_assert
   (i32.eq
    (i32.load offset=232
     (get_local $2)
    )
    (i32.add
     (get_local $0)
     (i32.const 240)
    )
   )
   (i32.const 400)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load offset=240
     (get_local $0)
    )
    (call $current_receiver)
   )
   (i32.const 448)
  )
  (set_local $1
   (i64.load
    (tee_local $3
     (i32.add
      (get_local $2)
      (i32.const 16)
     )
    )
   )
  )
  (drop
   (call $memcpy
    (get_local $2)
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
    (i32.const 232)
   )
  )
  (call $eosio_assert
   (i64.eq
    (tee_local $1
     (i64.shr_u
      (get_local $1)
      (i64.const 8)
     )
    )
    (i64.shr_u
     (i64.load
      (get_local $3)
     )
     (i64.const 8)
    )
   )
   (i32.const 544)
  )
  (i32.store offset=232
   (get_local $4)
   (i32.add
    (get_local $4)
    (i32.const 220)
   )
  )
  (i32.store offset=228
   (get_local $4)
   (get_local $4)
  )
  (i32.store offset=224
   (get_local $4)
   (get_local $4)
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_14exchange_stateE
    (i32.add
     (get_local $4)
     (i32.const 224)
    )
    (get_local $2)
   )
  )
  (call $db_update_i64
   (i32.load offset=236
    (get_local $2)
   )
   (i64.const 0)
   (get_local $4)
   (i32.const 220)
  )
  (block $label$0
   (br_if $label$0
    (i64.lt_u
     (get_local $1)
     (i64.load
      (tee_local $0
       (i32.add
        (get_local $0)
        (i32.const 256)
       )
      )
     )
    )
   )
   (i64.store
    (get_local $0)
    (i64.add
     (get_local $1)
     (i64.const 1)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $4)
    (i32.const 240)
   )
  )
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_14exchange_stateE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (get_local $1)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 3)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.const 4)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 4)
   )
  )
  (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_14exchange_state9connectorE
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_14exchange_state9connectorE
    (get_local $0)
    (i32.add
     (get_local $1)
     (i32.const 40)
    )
   )
   (i32.add
    (get_local $1)
    (i32.const 136)
   )
  )
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_14exchange_state9connectorE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (get_local $1)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 3)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.const 4)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 4)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 40)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 48)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 56)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 64)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 72)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 80)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 88)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio8exchange7depositEyNS_14extended_assetE (type $FUNCSIG$viji) (param $0 i32) (param $1 i64) (param $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
  (local $8 i64)
  (local $9 i64)
  (local $10 i64)
  (local $11 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $11
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 128)
    )
   )
  )
  (set_local $4
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i64.gt_u
     (i64.add
      (i64.load
       (get_local $2)
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $8
    (i64.shr_u
     (i64.load offset=8
      (get_local $2)
     )
     (i64.const 8)
    )
   )
   (set_local $6
    (i32.const 0)
   )
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $8)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $8
          (i64.shr_u
           (get_local $8)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $8
           (i64.shr_u
            (get_local $8)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $6
          (i32.add
           (get_local $6)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $4
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $6
        (i32.add
         (get_local $6)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $4
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $4)
   (i32.const 1840)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 104)
    )
    (i32.const 20)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 20)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 104)
    )
    (i32.const 16)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 16)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 104)
    )
    (i32.const 12)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 12)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 104)
    )
    (i32.const 8)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i32.store offset=108
   (get_local $11)
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 4)
    )
   )
  )
  (i32.store offset=104
   (get_local $11)
   (i32.load
    (get_local $2)
   )
  )
  (set_local $3
   (i64.load
    (get_local $0)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 88)
    )
    (i32.const 8)
   )
   (i32.const 0)
  )
  (i64.store offset=88
   (get_local $11)
   (i64.const 0)
  )
  (block $label$5
   (block $label$6
    (br_if $label$6
     (i32.ge_u
      (tee_local $6
       (call $strlen
        (i32.const 1872)
       )
      )
      (i32.const -16)
     )
    )
    (block $label$7
     (block $label$8
      (block $label$9
       (br_if $label$9
        (i32.ge_u
         (get_local $6)
         (i32.const 11)
        )
       )
       (i32.store8 offset=88
        (get_local $11)
        (i32.shl
         (get_local $6)
         (i32.const 1)
        )
       )
       (set_local $4
        (i32.or
         (i32.add
          (get_local $11)
          (i32.const 88)
         )
         (i32.const 1)
        )
       )
       (br_if $label$8
        (get_local $6)
       )
       (br $label$7)
      )
      (set_local $4
       (call $_Znwj
        (tee_local $5
         (i32.and
          (i32.add
           (get_local $6)
           (i32.const 16)
          )
          (i32.const -16)
         )
        )
       )
      )
      (i32.store offset=88
       (get_local $11)
       (i32.or
        (get_local $5)
        (i32.const 1)
       )
      )
      (i32.store offset=96
       (get_local $11)
       (get_local $4)
      )
      (i32.store offset=92
       (get_local $11)
       (get_local $6)
      )
     )
     (drop
      (call $memcpy
       (get_local $4)
       (i32.const 1872)
       (get_local $6)
      )
     )
    )
    (i32.store8
     (i32.add
      (get_local $4)
      (get_local $6)
     )
     (i32.const 0)
    )
    (set_local $8
     (i64.const 0)
    )
    (set_local $7
     (i64.const 59)
    )
    (set_local $6
     (i32.const 1888)
    )
    (set_local $9
     (i64.const 0)
    )
    (loop $label$10
     (block $label$11
      (block $label$12
       (block $label$13
        (block $label$14
         (block $label$15
          (br_if $label$15
           (i64.gt_u
            (get_local $8)
            (i64.const 5)
           )
          )
          (br_if $label$14
           (i32.gt_u
            (i32.and
             (i32.add
              (tee_local $4
               (i32.load8_s
                (get_local $6)
               )
              )
              (i32.const -97)
             )
             (i32.const 255)
            )
            (i32.const 25)
           )
          )
          (set_local $4
           (i32.add
            (get_local $4)
            (i32.const 165)
           )
          )
          (br $label$13)
         )
         (set_local $10
          (i64.const 0)
         )
         (br_if $label$12
          (i64.le_u
           (get_local $8)
           (i64.const 11)
          )
         )
         (br $label$11)
        )
        (set_local $4
         (select
          (i32.add
           (get_local $4)
           (i32.const 208)
          )
          (i32.const 0)
          (i32.lt_u
           (i32.and
            (i32.add
             (get_local $4)
             (i32.const -49)
            )
            (i32.const 255)
           )
           (i32.const 5)
          )
         )
        )
       )
       (set_local $10
        (i64.shr_s
         (i64.shl
          (i64.extend_u/i32
           (get_local $4)
          )
          (i64.const 56)
         )
         (i64.const 56)
        )
       )
      )
      (set_local $10
       (i64.shl
        (i64.and
         (get_local $10)
         (i64.const 31)
        )
        (i64.and
         (get_local $7)
         (i64.const 4294967295)
        )
       )
      )
     )
     (set_local $6
      (i32.add
       (get_local $6)
       (i32.const 1)
      )
     )
     (set_local $8
      (i64.add
       (get_local $8)
       (i64.const 1)
      )
     )
     (set_local $9
      (i64.or
       (get_local $10)
       (get_local $9)
      )
     )
     (br_if $label$10
      (i64.ne
       (tee_local $7
        (i64.add
         (get_local $7)
         (i64.const -5)
        )
       )
       (i64.const -6)
      )
     )
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $11)
       (i32.const 24)
      )
      (i32.const 16)
     )
     (i64.load
      (i32.add
       (i32.add
        (get_local $11)
        (i32.const 104)
       )
       (i32.const 16)
      )
     )
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $11)
       (i32.const 24)
      )
      (i32.const 8)
     )
     (i64.load
      (i32.add
       (i32.add
        (get_local $11)
        (i32.const 104)
       )
       (i32.const 8)
      )
     )
    )
    (i64.store offset=24
     (get_local $11)
     (i64.load offset=104
      (get_local $11)
     )
    )
    (call $_ZN5eosio8currency15inline_transferEyyNS_14extended_assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEy
     (get_local $1)
     (get_local $3)
     (i32.add
      (get_local $11)
      (i32.const 24)
     )
     (i32.add
      (get_local $11)
      (i32.const 88)
     )
     (get_local $9)
    )
    (block $label$16
     (br_if $label$16
      (i32.eqz
       (i32.and
        (i32.load8_u offset=88
         (get_local $11)
        )
        (i32.const 1)
       )
      )
     )
     (call $_ZdlPv
      (i32.load offset=96
       (get_local $11)
      )
     )
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $11)
       (i32.const 64)
      )
      (i32.const 16)
     )
     (i64.load
      (i32.add
       (get_local $2)
       (i32.const 16)
      )
     )
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $11)
       (i32.const 64)
      )
      (i32.const 8)
     )
     (i64.load
      (i32.add
       (get_local $2)
       (i32.const 8)
      )
     )
    )
    (i64.store offset=64
     (get_local $11)
     (i64.load
      (get_local $2)
     )
    )
    (i32.store
     (i32.add
      (i32.add
       (get_local $11)
       (i32.const 48)
      )
      (i32.const 8)
     )
     (i32.const 0)
    )
    (i64.store offset=48
     (get_local $11)
     (i64.const 0)
    )
    (br_if $label$5
     (i32.ge_u
      (tee_local $6
       (call $strlen
        (i32.const 1872)
       )
      )
      (i32.const -16)
     )
    )
    (set_local $2
     (i32.add
      (get_local $0)
      (i32.const 16)
     )
    )
    (block $label$17
     (block $label$18
      (block $label$19
       (br_if $label$19
        (i32.ge_u
         (get_local $6)
         (i32.const 11)
        )
       )
       (i32.store8 offset=48
        (get_local $11)
        (i32.shl
         (get_local $6)
         (i32.const 1)
        )
       )
       (set_local $4
        (i32.or
         (i32.add
          (get_local $11)
          (i32.const 48)
         )
         (i32.const 1)
        )
       )
       (br_if $label$18
        (get_local $6)
       )
       (br $label$17)
      )
      (set_local $4
       (call $_Znwj
        (tee_local $0
         (i32.and
          (i32.add
           (get_local $6)
           (i32.const 16)
          )
          (i32.const -16)
         )
        )
       )
      )
      (i32.store offset=48
       (get_local $11)
       (i32.or
        (get_local $0)
        (i32.const 1)
       )
      )
      (i32.store offset=56
       (get_local $11)
       (get_local $4)
      )
      (i32.store offset=52
       (get_local $11)
       (get_local $6)
      )
     )
     (drop
      (call $memcpy
       (get_local $4)
       (i32.const 1872)
       (get_local $6)
      )
     )
    )
    (i32.store8
     (i32.add
      (get_local $4)
      (get_local $6)
     )
     (i32.const 0)
    )
    (i64.store
     (i32.add
      (get_local $11)
      (i32.const 16)
     )
     (i64.load
      (i32.add
       (i32.add
        (get_local $11)
        (i32.const 64)
       )
       (i32.const 16)
      )
     )
    )
    (i64.store
     (i32.add
      (get_local $11)
      (i32.const 8)
     )
     (i64.load
      (i32.add
       (i32.add
        (get_local $11)
        (i32.const 64)
       )
       (i32.const 8)
      )
     )
    )
    (i64.store
     (get_local $11)
     (i64.load offset=64
      (get_local $11)
     )
    )
    (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
     (get_local $2)
     (get_local $1)
     (get_local $11)
     (get_local $6)
    )
    (block $label$20
     (br_if $label$20
      (i32.eqz
       (i32.and
        (i32.load8_u offset=48
         (get_local $11)
        )
        (i32.const 1)
       )
      )
     )
     (call $_ZdlPv
      (i32.load offset=56
       (get_local $11)
      )
     )
    )
    (i32.store offset=4
     (i32.const 0)
     (i32.add
      (get_local $11)
      (i32.const 128)
     )
    )
    (return)
   )
   (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
    (i32.add
     (get_local $11)
     (i32.const 88)
    )
   )
   (unreachable)
  )
  (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
   (i32.add
    (get_local $11)
    (i32.const 48)
   )
  )
  (unreachable)
 )
 (func $_ZN5eosio8currency15inline_transferEyyNS_14extended_assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEy (param $0 i64) (param $1 i64) (param $2 i32) (param $3 i32) (param $4 i64)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i64)
  (local $9 i64)
  (local $10 i64)
  (local $11 i64)
  (local $12 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $12
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 112)
    )
   )
  )
  (set_local $5
   (i64.load offset=16
    (get_local $2)
   )
  )
  (set_local $9
   (i64.const 0)
  )
  (set_local $8
   (i64.const 59)
  )
  (set_local $7
   (i32.const 1904)
  )
  (set_local $10
   (i64.const 0)
  )
  (loop $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (br_if $label$5
         (i64.gt_u
          (get_local $9)
          (i64.const 7)
         )
        )
        (br_if $label$4
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $6
             (i32.load8_s
              (get_local $7)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $6
         (i32.add
          (get_local $6)
          (i32.const 165)
         )
        )
        (br $label$3)
       )
       (set_local $11
        (i64.const 0)
       )
       (br_if $label$2
        (i64.le_u
         (get_local $9)
         (i64.const 11)
        )
       )
       (br $label$1)
      )
      (set_local $6
       (select
        (i32.add
         (get_local $6)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $6)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $11
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $6)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $11
     (i64.shl
      (i64.and
       (get_local $11)
       (i64.const 31)
      )
      (i64.and
       (get_local $8)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $7
    (i32.add
     (get_local $7)
     (i32.const 1)
    )
   )
   (set_local $9
    (i64.add
     (get_local $9)
     (i64.const 1)
    )
   )
   (set_local $10
    (i64.or
     (get_local $11)
     (get_local $10)
    )
   )
   (br_if $label$0
    (i64.ne
     (tee_local $8
      (i64.add
       (get_local $8)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
    (i32.const 28)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 12)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
    (i32.const 24)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
    (i32.const 20)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 4)
    )
   )
  )
  (i64.store offset=16
   (get_local $12)
   (get_local $1)
  )
  (i64.store offset=8
   (get_local $12)
   (get_local $0)
  )
  (i32.store offset=24
   (get_local $12)
   (i32.load
    (get_local $2)
   )
  )
  (drop
   (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2ERKS5_
    (i32.add
     (i32.add
      (get_local $12)
      (i32.const 8)
     )
     (i32.const 32)
    )
    (get_local $3)
   )
  )
  (i64.store offset=64
   (get_local $12)
   (get_local $10)
  )
  (i64.store offset=56
   (get_local $12)
   (get_local $5)
  )
  (i64.store
   (tee_local $7
    (call $_Znwj
     (i32.const 16)
    )
   )
   (get_local $0)
  )
  (i64.store offset=8
   (get_local $7)
   (get_local $4)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 56)
    )
    (i32.const 32)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 56)
    )
    (i32.const 24)
   )
   (tee_local $6
    (i32.add
     (get_local $7)
     (i32.const 16)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 56)
    )
    (i32.const 20)
   )
   (get_local $6)
  )
  (i32.store offset=72
   (get_local $12)
   (get_local $7)
  )
  (i32.store offset=84
   (get_local $12)
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 56)
    )
    (i32.const 36)
   )
   (i32.const 0)
  )
  (set_local $7
   (i32.add
    (tee_local $6
     (select
      (i32.load
       (i32.add
        (i32.add
         (get_local $12)
         (i32.const 8)
        )
        (i32.const 36)
       )
      )
      (i32.shr_u
       (tee_local $7
        (i32.load8_u offset=40
         (get_local $12)
        )
       )
       (i32.const 1)
      )
      (i32.and
       (get_local $7)
       (i32.const 1)
      )
     )
    )
    (i32.const 32)
   )
  )
  (set_local $9
   (i64.extend_u/i32
    (get_local $6)
   )
  )
  (set_local $6
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 56)
    )
    (i32.const 28)
   )
  )
  (loop $label$6
   (set_local $7
    (i32.add
     (get_local $7)
     (i32.const 1)
    )
   )
   (br_if $label$6
    (i64.ne
     (tee_local $9
      (i64.shr_u
       (get_local $9)
       (i64.const 7)
      )
     )
     (i64.const 0)
    )
   )
  )
  (block $label$7
   (block $label$8
    (br_if $label$8
     (i32.eqz
      (get_local $7)
     )
    )
    (call $_ZNSt3__16vectorIcNS_9allocatorIcEEE8__appendEj
     (get_local $6)
     (get_local $7)
    )
    (set_local $6
     (i32.load
      (i32.add
       (get_local $12)
       (i32.const 88)
      )
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $12)
       (i32.const 84)
      )
     )
    )
    (br $label$7)
   )
   (set_local $6
    (i32.const 0)
   )
   (set_local $7
    (i32.const 0)
   )
  )
  (i32.store offset=100
   (get_local $12)
   (get_local $7)
  )
  (i32.store offset=96
   (get_local $12)
   (get_local $7)
  )
  (i32.store offset=104
   (get_local $12)
   (get_local $6)
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_8currency8transferE
    (i32.add
     (get_local $12)
     (i32.const 96)
    )
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
   )
  )
  (block $label$9
   (br_if $label$9
    (i32.eqz
     (i32.and
      (i32.load8_u
       (i32.add
        (get_local $12)
        (i32.const 40)
       )
      )
      (i32.const 1)
     )
    )
   )
   (call $_ZdlPv
    (i32.load
     (i32.add
      (get_local $12)
      (i32.const 48)
     )
    )
   )
  )
  (call $_ZN5eosio4packINS_6actionEEENSt3__16vectorIcNS2_9allocatorIcEEEERKT_
   (i32.add
    (get_local $12)
    (i32.const 8)
   )
   (i32.add
    (get_local $12)
    (i32.const 56)
   )
  )
  (call $send_inline
   (tee_local $7
    (i32.load offset=8
     (get_local $12)
    )
   )
   (i32.sub
    (i32.load offset=12
     (get_local $12)
    )
    (get_local $7)
   )
  )
  (block $label$10
   (br_if $label$10
    (i32.eqz
     (tee_local $7
      (i32.load offset=8
       (get_local $12)
      )
     )
    )
   )
   (i32.store offset=12
    (get_local $12)
    (get_local $7)
   )
   (call $_ZdlPv
    (get_local $7)
   )
  )
  (block $label$11
   (br_if $label$11
    (i32.eqz
     (tee_local $7
      (i32.load offset=84
       (get_local $12)
      )
     )
    )
   )
   (i32.store
    (i32.add
     (get_local $12)
     (i32.const 88)
    )
    (get_local $7)
   )
   (call $_ZdlPv
    (get_local $7)
   )
  )
  (block $label$12
   (br_if $label$12
    (i32.eqz
     (tee_local $7
      (i32.load offset=72
       (get_local $12)
      )
     )
    )
   )
   (i32.store
    (i32.add
     (get_local $12)
     (i32.const 76)
    )
    (get_local $7)
   )
   (call $_ZdlPv
    (get_local $7)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $12)
    (i32.const 112)
   )
  )
 )
 (func $_ZNSt3__16vectorIcNS_9allocatorIcEEE8__appendEj (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (br_if $label$4
        (i32.ge_u
         (i32.sub
          (tee_local $2
           (i32.load offset=8
            (get_local $0)
           )
          )
          (tee_local $6
           (i32.load offset=4
            (get_local $0)
           )
          )
         )
         (get_local $1)
        )
       )
       (br_if $label$2
        (i32.le_s
         (tee_local $4
          (i32.add
           (tee_local $3
            (i32.sub
             (get_local $6)
             (tee_local $5
              (i32.load
               (get_local $0)
              )
             )
            )
           )
           (get_local $1)
          )
         )
         (i32.const -1)
        )
       )
       (set_local $6
        (i32.const 2147483647)
       )
       (block $label$5
        (br_if $label$5
         (i32.gt_u
          (tee_local $2
           (i32.sub
            (get_local $2)
            (get_local $5)
           )
          )
          (i32.const 1073741822)
         )
        )
        (br_if $label$3
         (i32.eqz
          (tee_local $6
           (select
            (get_local $4)
            (tee_local $6
             (i32.shl
              (get_local $2)
              (i32.const 1)
             )
            )
            (i32.lt_u
             (get_local $6)
             (get_local $4)
            )
           )
          )
         )
        )
       )
       (set_local $2
        (call $_Znwj
         (get_local $6)
        )
       )
       (br $label$1)
      )
      (set_local $0
       (i32.add
        (get_local $0)
        (i32.const 4)
       )
      )
      (loop $label$6
       (i32.store8
        (get_local $6)
        (i32.const 0)
       )
       (i32.store
        (get_local $0)
        (tee_local $6
         (i32.add
          (i32.load
           (get_local $0)
          )
          (i32.const 1)
         )
        )
       )
       (br_if $label$6
        (tee_local $1
         (i32.add
          (get_local $1)
          (i32.const -1)
         )
        )
       )
       (br $label$0)
      )
     )
     (set_local $6
      (i32.const 0)
     )
     (set_local $2
      (i32.const 0)
     )
     (br $label$1)
    )
    (call $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
     (get_local $0)
    )
    (unreachable)
   )
   (set_local $4
    (i32.add
     (get_local $2)
     (get_local $6)
    )
   )
   (set_local $6
    (tee_local $5
     (i32.add
      (get_local $2)
      (get_local $3)
     )
    )
   )
   (loop $label$7
    (i32.store8
     (get_local $6)
     (i32.const 0)
    )
    (set_local $6
     (i32.add
      (get_local $6)
      (i32.const 1)
     )
    )
    (br_if $label$7
     (tee_local $1
      (i32.add
       (get_local $1)
       (i32.const -1)
      )
     )
    )
   )
   (set_local $5
    (i32.sub
     (get_local $5)
     (tee_local $2
      (i32.sub
       (i32.load
        (tee_local $3
         (i32.add
          (get_local $0)
          (i32.const 4)
         )
        )
       )
       (tee_local $1
        (i32.load
         (get_local $0)
        )
       )
      )
     )
    )
   )
   (block $label$8
    (br_if $label$8
     (i32.lt_s
      (get_local $2)
      (i32.const 1)
     )
    )
    (drop
     (call $memcpy
      (get_local $5)
      (get_local $1)
      (get_local $2)
     )
    )
    (set_local $1
     (i32.load
      (get_local $0)
     )
    )
   )
   (i32.store
    (get_local $0)
    (get_local $5)
   )
   (i32.store
    (get_local $3)
    (get_local $6)
   )
   (i32.store
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
    (get_local $4)
   )
   (br_if $label$0
    (i32.eqz
     (get_local $1)
    )
   )
   (call $_ZdlPv
    (get_local $1)
   )
   (return)
  )
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_8currency8transferE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (get_local $1)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNSt3__112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEE
   (get_local $0)
   (i32.add
    (get_local $1)
    (i32.const 32)
   )
  )
 )
 (func $_ZN5eosio4packINS_6actionEEENSt3__16vectorIcNS2_9allocatorIcEEEERKT_ (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i64)
  (local $7 i32)
  (local $8 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i32.store offset=8
   (get_local $0)
   (i32.const 0)
  )
  (i64.store align=4
   (get_local $0)
   (i64.const 0)
  )
  (set_local $5
   (i32.const 16)
  )
  (set_local $2
   (i32.add
    (get_local $1)
    (i32.const 16)
   )
  )
  (set_local $6
   (i64.extend_u/i32
    (i32.shr_s
     (tee_local $4
      (i32.sub
       (tee_local $7
        (i32.load
         (i32.add
          (get_local $1)
          (i32.const 20)
         )
        )
       )
       (tee_local $3
        (i32.load offset=16
         (get_local $1)
        )
       )
      )
     )
     (i32.const 4)
    )
   )
  )
  (loop $label$0
   (set_local $5
    (i32.add
     (get_local $5)
     (i32.const 1)
    )
   )
   (br_if $label$0
    (i64.ne
     (tee_local $6
      (i64.shr_u
       (get_local $6)
       (i64.const 7)
      )
     )
     (i64.const 0)
    )
   )
  )
  (block $label$1
   (br_if $label$1
    (i32.eq
     (get_local $3)
     (get_local $7)
    )
   )
   (set_local $5
    (i32.add
     (i32.and
      (get_local $4)
      (i32.const -16)
     )
     (get_local $5)
    )
   )
  )
  (set_local $5
   (i32.sub
    (i32.sub
     (tee_local $7
      (i32.load offset=28
       (get_local $1)
      )
     )
     (get_local $5)
    )
    (tee_local $3
     (i32.load
      (i32.add
       (get_local $1)
       (i32.const 32)
      )
     )
    )
   )
  )
  (set_local $4
   (i32.add
    (get_local $1)
    (i32.const 28)
   )
  )
  (set_local $6
   (i64.extend_u/i32
    (i32.sub
     (get_local $3)
     (get_local $7)
    )
   )
  )
  (loop $label$2
   (set_local $5
    (i32.add
     (get_local $5)
     (i32.const -1)
    )
   )
   (br_if $label$2
    (i64.ne
     (tee_local $6
      (i64.shr_u
       (get_local $6)
       (i64.const 7)
      )
     )
     (i64.const 0)
    )
   )
  )
  (set_local $7
   (i32.const 0)
  )
  (block $label$3
   (block $label$4
    (br_if $label$4
     (i32.eqz
      (get_local $5)
     )
    )
    (call $_ZNSt3__16vectorIcNS_9allocatorIcEEE8__appendEj
     (get_local $0)
     (i32.sub
      (i32.const 0)
      (get_local $5)
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $5
     (i32.load
      (get_local $0)
     )
    )
    (br $label$3)
   )
   (set_local $5
    (i32.const 0)
   )
  )
  (i32.store
   (get_local $8)
   (get_local $5)
  )
  (i32.store offset=8
   (get_local $8)
   (get_local $7)
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (get_local $7)
     (get_local $5)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (get_local $5)
    (get_local $1)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (get_local $7)
     (tee_local $0
      (i32.add
       (get_local $5)
       (i32.const 8)
      )
     )
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (get_local $0)
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $8)
   (i32.add
    (get_local $5)
    (i32.const 16)
   )
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNSt3__16vectorIcNS6_9allocatorIcEEEE
    (call $_ZN5eosiolsINS_10datastreamIPcEENS_16permission_levelEEERT_S6_RKNSt3__16vectorIT0_NS7_9allocatorIS9_EEEE
     (get_local $8)
     (get_local $2)
    )
    (get_local $4)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 16)
   )
  )
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEENS_16permission_levelEEERT_S6_RKNSt3__16vectorIT0_NS7_9allocatorIS9_EEEE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $4
   (i64.extend_u/i32
    (i32.shr_s
     (i32.sub
      (i32.load offset=4
       (get_local $1)
      )
      (i32.load
       (get_local $1)
      )
     )
     (i32.const 4)
    )
   )
  )
  (set_local $5
   (i32.load offset=4
    (get_local $0)
   )
  )
  (set_local $2
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (loop $label$0
   (set_local $3
    (i32.wrap/i64
     (get_local $4)
    )
   )
   (i32.store8 offset=15
    (get_local $7)
    (i32.or
     (i32.shl
      (tee_local $6
       (i64.ne
        (tee_local $4
         (i64.shr_u
          (get_local $4)
          (i64.const 7)
         )
        )
        (i64.const 0)
       )
      )
      (i32.const 7)
     )
     (i32.and
      (get_local $3)
      (i32.const 127)
     )
    )
   )
   (call $eosio_assert
    (i32.gt_s
     (i32.sub
      (i32.load
       (get_local $2)
      )
      (get_local $5)
     )
     (i32.const 0)
    )
    (i32.const 608)
   )
   (drop
    (call $memcpy
     (i32.load
      (tee_local $3
       (i32.add
        (get_local $0)
        (i32.const 4)
       )
      )
     )
     (i32.add
      (get_local $7)
      (i32.const 15)
     )
     (i32.const 1)
    )
   )
   (i32.store
    (get_local $3)
    (tee_local $5
     (i32.add
      (i32.load
       (get_local $3)
      )
      (i32.const 1)
     )
    )
   )
   (br_if $label$0
    (get_local $6)
   )
  )
  (block $label$1
   (br_if $label$1
    (i32.eq
     (tee_local $6
      (i32.load
       (get_local $1)
      )
     )
     (tee_local $1
      (i32.load
       (i32.add
        (get_local $1)
        (i32.const 4)
       )
      )
     )
    )
   )
   (set_local $3
    (i32.add
     (get_local $0)
     (i32.const 4)
    )
   )
   (loop $label$2
    (call $eosio_assert
     (i32.gt_s
      (i32.sub
       (i32.load
        (tee_local $2
         (i32.add
          (get_local $0)
          (i32.const 8)
         )
        )
       )
       (get_local $5)
      )
      (i32.const 7)
     )
     (i32.const 608)
    )
    (drop
     (call $memcpy
      (i32.load
       (get_local $3)
      )
      (get_local $6)
      (i32.const 8)
     )
    )
    (i32.store
     (get_local $3)
     (tee_local $5
      (i32.add
       (i32.load
        (get_local $3)
       )
       (i32.const 8)
      )
     )
    )
    (call $eosio_assert
     (i32.gt_s
      (i32.sub
       (i32.load
        (get_local $2)
       )
       (get_local $5)
      )
      (i32.const 7)
     )
     (i32.const 608)
    )
    (drop
     (call $memcpy
      (i32.load
       (get_local $3)
      )
      (i32.add
       (get_local $6)
       (i32.const 8)
      )
      (i32.const 8)
     )
    )
    (i32.store
     (get_local $3)
     (tee_local $5
      (i32.add
       (i32.load
        (get_local $3)
       )
       (i32.const 8)
      )
     )
    )
    (br_if $label$2
     (i32.ne
      (tee_local $6
       (i32.add
        (get_local $6)
        (i32.const 16)
       )
      )
      (get_local $1)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $7)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNSt3__16vectorIcNS6_9allocatorIcEEEE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
  (local $8 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $7
   (i64.extend_u/i32
    (i32.sub
     (i32.load offset=4
      (get_local $1)
     )
     (i32.load
      (get_local $1)
     )
    )
   )
  )
  (set_local $6
   (i32.load offset=4
    (get_local $0)
   )
  )
  (set_local $4
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (set_local $5
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
  )
  (loop $label$0
   (set_local $2
    (i32.wrap/i64
     (get_local $7)
    )
   )
   (i32.store8 offset=15
    (get_local $8)
    (i32.or
     (i32.shl
      (tee_local $3
       (i64.ne
        (tee_local $7
         (i64.shr_u
          (get_local $7)
          (i64.const 7)
         )
        )
        (i64.const 0)
       )
      )
      (i32.const 7)
     )
     (i32.and
      (get_local $2)
      (i32.const 127)
     )
    )
   )
   (call $eosio_assert
    (i32.gt_s
     (i32.sub
      (i32.load
       (get_local $4)
      )
      (get_local $6)
     )
     (i32.const 0)
    )
    (i32.const 608)
   )
   (drop
    (call $memcpy
     (i32.load
      (get_local $5)
     )
     (i32.add
      (get_local $8)
      (i32.const 15)
     )
     (i32.const 1)
    )
   )
   (i32.store
    (get_local $5)
    (tee_local $6
     (i32.add
      (i32.load
       (get_local $5)
      )
      (i32.const 1)
     )
    )
   )
   (br_if $label$0
    (get_local $3)
   )
  )
  (call $eosio_assert
   (i32.ge_s
    (i32.sub
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 8)
      )
     )
     (get_local $6)
    )
    (tee_local $5
     (i32.sub
      (i32.load
       (i32.add
        (get_local $1)
        (i32.const 4)
       )
      )
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
    )
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load
     (tee_local $6
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (get_local $2)
    (get_local $5)
   )
  )
  (i32.store
   (get_local $6)
   (i32.add
    (i32.load
     (get_local $6)
    )
    (get_local $5)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNSt3__112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
  (local $8 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $7
   (i64.extend_u/i32
    (select
     (i32.load offset=4
      (get_local $1)
     )
     (i32.shr_u
      (tee_local $5
       (i32.load8_u
        (get_local $1)
       )
      )
      (i32.const 1)
     )
     (i32.and
      (get_local $5)
      (i32.const 1)
     )
    )
   )
  )
  (set_local $6
   (i32.load offset=4
    (get_local $0)
   )
  )
  (set_local $4
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (set_local $5
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
  )
  (loop $label$0
   (set_local $2
    (i32.wrap/i64
     (get_local $7)
    )
   )
   (i32.store8 offset=15
    (get_local $8)
    (i32.or
     (i32.shl
      (tee_local $3
       (i64.ne
        (tee_local $7
         (i64.shr_u
          (get_local $7)
          (i64.const 7)
         )
        )
        (i64.const 0)
       )
      )
      (i32.const 7)
     )
     (i32.and
      (get_local $2)
      (i32.const 127)
     )
    )
   )
   (call $eosio_assert
    (i32.gt_s
     (i32.sub
      (i32.load
       (get_local $4)
      )
      (get_local $6)
     )
     (i32.const 0)
    )
    (i32.const 608)
   )
   (drop
    (call $memcpy
     (i32.load
      (get_local $5)
     )
     (i32.add
      (get_local $8)
      (i32.const 15)
     )
     (i32.const 1)
    )
   )
   (i32.store
    (get_local $5)
    (tee_local $6
     (i32.add
      (i32.load
       (get_local $5)
      )
      (i32.const 1)
     )
    )
   )
   (br_if $label$0
    (get_local $3)
   )
  )
  (block $label$1
   (br_if $label$1
    (i32.eqz
     (tee_local $5
      (select
       (i32.load
        (i32.add
         (get_local $1)
         (i32.const 4)
        )
       )
       (i32.shr_u
        (tee_local $5
         (i32.load8_u
          (get_local $1)
         )
        )
        (i32.const 1)
       )
       (tee_local $2
        (i32.and
         (get_local $5)
         (i32.const 1)
        )
       )
      )
     )
    )
   )
   (set_local $3
    (i32.load offset=8
     (get_local $1)
    )
   )
   (call $eosio_assert
    (i32.ge_s
     (i32.sub
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 8)
       )
      )
      (get_local $6)
     )
     (get_local $5)
    )
    (i32.const 608)
   )
   (drop
    (call $memcpy
     (i32.load
      (tee_local $6
       (i32.add
        (get_local $0)
        (i32.const 4)
       )
      )
     )
     (select
      (get_local $3)
      (i32.add
       (get_local $1)
       (i32.const 1)
      )
      (get_local $2)
     )
     (get_local $5)
    )
   )
   (i32.store
    (get_local $6)
    (i32.add
     (i32.load
      (get_local $6)
     )
     (get_local $5)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio8exchange8withdrawEyNS_14extended_assetE (type $FUNCSIG$viji) (param $0 i32) (param $1 i64) (param $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i64)
  (local $7 i64)
  (local $8 i64)
  (local $9 i64)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 112)
    )
   )
  )
  (call $require_auth
   (get_local $1)
  )
  (set_local $9
   (i64.load offset=8
    (get_local $2)
   )
  )
  (set_local $4
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i64.gt_u
     (i64.add
      (tee_local $6
       (i64.load
        (get_local $2)
       )
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $7
    (i64.shr_u
     (get_local $9)
     (i64.const 8)
    )
   )
   (set_local $5
    (i32.const 0)
   )
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $7)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $7
          (i64.shr_u
           (get_local $7)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $7
           (i64.shr_u
            (get_local $7)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $5
          (i32.add
           (get_local $5)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $4
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $5
        (i32.add
         (get_local $5)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $4
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $4)
   (i32.const 1840)
  )
  (call $eosio_assert
   (i32.xor
    (i32.wrap/i64
     (i64.shr_u
      (get_local $6)
      (i64.const 63)
     )
    )
    (i32.const 1)
   )
   (i32.const 1920)
  )
  (i64.store offset=96
   (get_local $10)
   (get_local $9)
  )
  (set_local $7
   (i64.load offset=16
    (get_local $2)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 24)
    )
    (i32.const 8)
   )
   (get_local $9)
  )
  (i64.store offset=104
   (get_local $10)
   (get_local $7)
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 24)
    )
    (i32.const 16)
   )
   (get_local $7)
  )
  (i64.store offset=88
   (get_local $10)
   (tee_local $7
    (i64.sub
     (i64.const 0)
     (get_local $6)
    )
   )
  )
  (i64.store offset=24
   (get_local $10)
   (get_local $7)
  )
  (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
   (i32.add
    (get_local $0)
    (i32.const 16)
   )
   (get_local $1)
   (i32.add
    (get_local $10)
    (i32.const 24)
   )
   (get_local $5)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 64)
    )
    (i32.const 20)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 20)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 64)
    )
    (i32.const 16)
   )
   (i32.load offset=16
    (get_local $2)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 64)
    )
    (i32.const 12)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 12)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 64)
    )
    (i32.const 8)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i32.store offset=68
   (get_local $10)
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 4)
    )
   )
  )
  (i32.store offset=64
   (get_local $10)
   (i32.load
    (get_local $2)
   )
  )
  (set_local $3
   (i64.load
    (get_local $0)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 48)
    )
    (i32.const 8)
   )
   (i32.const 0)
  )
  (i64.store offset=48
   (get_local $10)
   (i64.const 0)
  )
  (block $label$5
   (br_if $label$5
    (i32.ge_u
     (tee_local $5
      (call $strlen
       (i32.const 1968)
      )
     )
     (i32.const -16)
    )
   )
   (block $label$6
    (block $label$7
     (block $label$8
      (br_if $label$8
       (i32.ge_u
        (get_local $5)
        (i32.const 11)
       )
      )
      (i32.store8 offset=48
       (get_local $10)
       (i32.shl
        (get_local $5)
        (i32.const 1)
       )
      )
      (set_local $2
       (i32.or
        (i32.add
         (get_local $10)
         (i32.const 48)
        )
        (i32.const 1)
       )
      )
      (br_if $label$7
       (get_local $5)
      )
      (br $label$6)
     )
     (set_local $2
      (call $_Znwj
       (tee_local $4
        (i32.and
         (i32.add
          (get_local $5)
          (i32.const 16)
         )
         (i32.const -16)
        )
       )
      )
     )
     (i32.store offset=48
      (get_local $10)
      (i32.or
       (get_local $4)
       (i32.const 1)
      )
     )
     (i32.store offset=56
      (get_local $10)
      (get_local $2)
     )
     (i32.store offset=52
      (get_local $10)
      (get_local $5)
     )
    )
    (drop
     (call $memcpy
      (get_local $2)
      (i32.const 1968)
      (get_local $5)
     )
    )
   )
   (i32.store8
    (i32.add
     (get_local $2)
     (get_local $5)
    )
    (i32.const 0)
   )
   (set_local $7
    (i64.const 0)
   )
   (set_local $6
    (i64.const 59)
   )
   (set_local $5
    (i32.const 1888)
   )
   (set_local $8
    (i64.const 0)
   )
   (loop $label$9
    (block $label$10
     (block $label$11
      (block $label$12
       (block $label$13
        (block $label$14
         (br_if $label$14
          (i64.gt_u
           (get_local $7)
           (i64.const 5)
          )
         )
         (br_if $label$13
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $2
              (i32.load8_s
               (get_local $5)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $2
          (i32.add
           (get_local $2)
           (i32.const 165)
          )
         )
         (br $label$12)
        )
        (set_local $9
         (i64.const 0)
        )
        (br_if $label$11
         (i64.le_u
          (get_local $7)
          (i64.const 11)
         )
        )
        (br $label$10)
       )
       (set_local $2
        (select
         (i32.add
          (get_local $2)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $2)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $9
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $2)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $9
      (i64.shl
       (i64.and
        (get_local $9)
        (i64.const 31)
       )
       (i64.and
        (get_local $6)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $5
     (i32.add
      (get_local $5)
      (i32.const 1)
     )
    )
    (set_local $7
     (i64.add
      (get_local $7)
      (i64.const 1)
     )
    )
    (set_local $8
     (i64.or
      (get_local $9)
      (get_local $8)
     )
    )
    (br_if $label$9
     (i64.ne
      (tee_local $6
       (i64.add
        (get_local $6)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $10)
     (i32.const 16)
    )
    (i64.load
     (i32.add
      (i32.add
       (get_local $10)
       (i32.const 64)
      )
      (i32.const 16)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $10)
     (i32.const 8)
    )
    (i64.load
     (i32.add
      (i32.add
       (get_local $10)
       (i32.const 64)
      )
      (i32.const 8)
     )
    )
   )
   (i64.store
    (get_local $10)
    (i64.load offset=64
     (get_local $10)
    )
   )
   (call $_ZN5eosio8currency15inline_transferEyyNS_14extended_assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEy
    (get_local $3)
    (get_local $1)
    (get_local $10)
    (i32.add
     (get_local $10)
     (i32.const 48)
    )
    (get_local $8)
   )
   (block $label$15
    (br_if $label$15
     (i32.eqz
      (i32.and
       (i32.load8_u offset=48
        (get_local $10)
       )
       (i32.const 1)
      )
     )
    )
    (call $_ZdlPv
     (i32.load offset=56
      (get_local $10)
     )
    )
   )
   (i32.store offset=4
    (i32.const 0)
    (i32.add
     (get_local $10)
     (i32.const 112)
    )
   )
   (return)
  )
  (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
   (i32.add
    (get_local $10)
    (i32.const 48)
   )
  )
  (unreachable)
 )
 (func $_ZN5eosio8exchange2onERKNS0_5tradeE (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (local $12 i32)
  (local $13 i64)
  (local $14 i64)
  (local $15 i64)
  (local $16 i64)
  (local $17 i32)
  (local $18 i32)
  (local $19 i32)
  (local $20 i32)
  (local $21 i32)
  (local $22 i32)
  (local $23 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $23
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 1008)
    )
   )
  )
  (call $require_auth
   (i64.load
    (get_local $1)
   )
  )
  (set_local $3
   (i32.add
    (get_local $1)
    (i32.const 16)
   )
  )
  (set_local $21
   (i32.const 0)
  )
  (set_local $22
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i64.gt_u
     (i64.add
      (i64.load offset=16
       (get_local $1)
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $4
    (i64.shr_u
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 24)
      )
     )
     (i64.const 8)
    )
   )
   (set_local $20
    (i32.const 0)
   )
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $4)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $4
          (i64.shr_u
           (get_local $4)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $4
           (i64.shr_u
            (get_local $4)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $20
          (i32.add
           (get_local $20)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $22
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $20
        (i32.add
         (get_local $20)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $22
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $22)
   (i32.const 1984)
  )
  (call $eosio_assert
   (i64.gt_s
    (i64.load
     (get_local $3)
    )
    (i64.const 0)
   )
   (i32.const 2016)
  )
  (block $label$5
   (br_if $label$5
    (i64.gt_u
     (i64.add
      (i64.load offset=40
       (get_local $1)
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $4
    (i64.shr_u
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 48)
      )
     )
     (i64.const 8)
    )
   )
   (set_local $20
    (i32.const 0)
   )
   (block $label$6
    (loop $label$7
     (br_if $label$6
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $4)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$8
      (br_if $label$8
       (i64.ne
        (i64.and
         (tee_local $4
          (i64.shr_u
           (get_local $4)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$9
       (br_if $label$6
        (i64.ne
         (i64.and
          (tee_local $4
           (i64.shr_u
            (get_local $4)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$9
        (i32.lt_s
         (tee_local $20
          (i32.add
           (get_local $20)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $21
      (i32.const 1)
     )
     (br_if $label$7
      (i32.lt_s
       (tee_local $20
        (i32.add
         (get_local $20)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$5)
    )
   )
   (set_local $21
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $21)
   (i32.const 2048)
  )
  (call $eosio_assert
   (i32.xor
    (i32.wrap/i64
     (i64.shr_u
      (i64.load
       (i32.add
        (get_local $1)
        (i32.const 40)
       )
      )
      (i64.const 63)
     )
    )
    (i32.const 1)
   )
   (i32.const 2080)
  )
  (call $eosio_assert
   (i32.or
    (i64.ne
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 24)
      )
     )
     (tee_local $4
      (i64.load
       (i32.add
        (get_local $1)
        (i32.const 48)
       )
      )
     )
    )
    (i64.ne
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 32)
      )
     )
     (tee_local $5
      (i64.load
       (i32.add
        (get_local $1)
        (i32.const 56)
       )
      )
     )
    )
   )
   (i32.const 192)
  )
  (i64.store offset=552
   (get_local $23)
   (i64.shr_u
    (i64.load offset=8
     (get_local $1)
    )
    (i64.const 8)
   )
  )
  (set_local $13
   (i64.load
    (get_local $0)
   )
  )
  (set_local $20
   (call $_ZN5eosio14exchange_stateC2Ev
    (i32.add
     (i32.add
      (get_local $23)
      (i32.const 552)
     )
     (i32.const 8)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $23)
    (i32.const 808)
   )
   (i64.const -1)
  )
  (i64.store
   (i32.add
    (get_local $23)
    (i32.const 816)
   )
   (i64.const 0)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 824)
   )
   (i32.const 0)
  )
  (i64.store
   (i32.add
    (get_local $23)
    (i32.const 800)
   )
   (tee_local $14
    (i64.load offset=552
     (get_local $23)
    )
   )
  )
  (i64.store offset=792
   (get_local $23)
   (get_local $13)
  )
  (i64.store offset=832
   (get_local $23)
   (get_local $13)
  )
  (i64.store
   (i32.add
    (get_local $23)
    (i32.const 840)
   )
   (tee_local $16
    (i64.or
     (tee_local $15
      (i64.shl
       (get_local $14)
       (i64.const 4)
      )
     )
     (i64.const 1)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $23)
    (i32.const 848)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 856)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 860)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 864)
   )
   (i32.const 0)
  )
  (i32.store8
   (i32.add
    (get_local $23)
    (i32.const 868)
   )
   (i32.const 0)
  )
  (i64.store offset=872
   (get_local $23)
   (get_local $13)
  )
  (i64.store
   (i32.add
    (get_local $23)
    (i32.const 880)
   )
   (tee_local $15
    (i64.or
     (get_local $15)
     (i64.const 2)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $23)
    (i32.const 888)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 896)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 900)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 904)
   )
   (i32.const 0)
  )
  (i32.store8
   (i32.add
    (get_local $23)
    (i32.const 908)
   )
   (i32.const 0)
  )
  (i64.store offset=912
   (get_local $23)
   (get_local $13)
  )
  (i64.store
   (i32.add
    (get_local $23)
    (i32.const 920)
   )
   (get_local $16)
  )
  (i64.store
   (i32.add
    (get_local $23)
    (i32.const 928)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 936)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 940)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 944)
   )
   (i32.const 0)
  )
  (i64.store offset=952
   (get_local $23)
   (get_local $13)
  )
  (i64.store
   (i32.add
    (get_local $23)
    (i32.const 960)
   )
   (get_local $15)
  )
  (i64.store
   (i32.add
    (get_local $23)
    (i32.const 968)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 976)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 980)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 984)
   )
   (i32.const 0)
  )
  (i32.store offset=992
   (get_local $23)
   (tee_local $6
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
   )
  )
  (call $_ZNK5eosio11multi_indexILy10497615196363685888ENS_14exchange_stateEJEE4findEy
   (i32.add
    (get_local $23)
    (i32.const 996)
   )
   (i32.add
    (get_local $23)
    (i32.const 792)
   )
   (get_local $14)
  )
  (call $eosio_assert
   (i32.ne
    (i32.load
     (tee_local $21
      (i32.add
       (get_local $23)
       (i32.const 1000)
      )
     )
    )
    (i32.const 0)
   )
   (i32.const 720)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $23)
     (i32.const 320)
    )
    (tee_local $2
     (call $memcpy
      (get_local $20)
      (i32.load
       (get_local $21)
      )
      (i32.const 232)
     )
    )
    (i32.const 232)
   )
  )
  (i64.store
   (tee_local $20
    (i32.add
     (i32.add
      (get_local $23)
      (i32.const 272)
     )
     (i32.const 16)
    )
   )
   (i64.load
    (tee_local $17
     (i32.add
      (get_local $3)
      (i32.const 16)
     )
    )
   )
  )
  (i64.store
   (tee_local $21
    (i32.add
     (i32.add
      (get_local $23)
      (i32.const 272)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (tee_local $18
     (i32.add
      (get_local $3)
      (i32.const 8)
     )
    )
   )
  )
  (i64.store offset=272
   (get_local $23)
   (i64.load
    (get_local $3)
   )
  )
  (i64.store offset=256
   (get_local $23)
   (get_local $4)
  )
  (i64.store offset=264
   (get_local $23)
   (get_local $5)
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $23)
     (i32.const 104)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $21)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $23)
     (i32.const 104)
    )
    (i32.const 16)
   )
   (i64.load
    (get_local $20)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $23)
     (i32.const 88)
    )
    (i32.const 8)
   )
   (i64.load offset=264
    (get_local $23)
   )
  )
  (i64.store offset=104
   (get_local $23)
   (i64.load offset=272
    (get_local $23)
   )
  )
  (i64.store offset=88
   (get_local $23)
   (i64.load offset=256
    (get_local $23)
   )
  )
  (call $_ZN5eosio14exchange_state7convertENS_14extended_assetENS_15extended_symbolE
   (i32.add
    (get_local $23)
    (i32.const 296)
   )
   (i32.add
    (get_local $23)
    (i32.const 320)
   )
   (i32.add
    (get_local $23)
    (i32.const 104)
   )
   (i32.add
    (get_local $23)
    (i32.const 88)
   )
  )
  (set_local $12
   (i32.add
    (get_local $23)
    (i32.const 456)
   )
  )
  (set_local $11
   (i32.add
    (get_local $23)
    (i32.const 872)
   )
  )
  (set_local $10
   (i32.add
    (get_local $23)
    (i32.const 696)
   )
  )
  (set_local $9
   (i32.add
    (get_local $23)
    (i32.const 832)
   )
  )
  (set_local $8
   (i32.add
    (i32.add
     (get_local $23)
     (i32.const 552)
    )
    (i32.const 48)
   )
  )
  (set_local $7
   (i32.add
    (i32.add
     (get_local $23)
     (i32.const 320)
    )
    (i32.const 40)
   )
  )
  (set_local $19
   (i32.add
    (get_local $23)
    (i32.const 616)
   )
  )
  (block $label$10
   (loop $label$11
    (block $label$12
     (br_if $label$12
      (call $_ZNK5eosio14exchange_state20requires_margin_callERKNS0_9connectorE
       (i32.add
        (get_local $23)
        (i32.const 320)
       )
       (get_local $7)
      )
     )
     (br_if $label$10
      (i32.eqz
       (call $_ZNK5eosio14exchange_state20requires_margin_callERKNS0_9connectorE
        (i32.add
         (get_local $23)
         (i32.const 320)
        )
        (get_local $12)
       )
      )
     )
    )
    (block $label$13
     (block $label$14
      (br_if $label$14
       (i64.ne
        (get_local $4)
        (i64.load
         (i32.add
          (i32.add
           (get_local $23)
           (i32.const 552)
          )
          (i32.const 56)
         )
        )
       )
      )
      (br_if $label$14
       (i64.ne
        (get_local $5)
        (i64.load
         (get_local $19)
        )
       )
      )
      (call $_ZN5eosio12market_state11margin_callERNS_14exchange_state9connectorERNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS5_yXadL_ZNKS5_8get_callEvEEEEEEEEE
       (i32.add
        (get_local $23)
        (i32.const 552)
       )
       (get_local $8)
       (get_local $9)
      )
      (br $label$13)
     )
     (call $_ZN5eosio12market_state11margin_callERNS_14exchange_state9connectorERNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS5_yXadL_ZNKS5_8get_callEvEEEEEEEEE
      (i32.add
       (get_local $23)
       (i32.const 552)
      )
      (get_local $10)
      (get_local $11)
     )
    )
    (drop
     (call $memcpy
      (i32.add
       (get_local $23)
       (i32.const 320)
      )
      (get_local $2)
      (i32.const 232)
     )
    )
    (i64.store
     (tee_local $20
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 232)
       )
       (i32.const 16)
      )
     )
     (i64.load
      (get_local $17)
     )
    )
    (i64.store
     (tee_local $21
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 232)
       )
       (i32.const 8)
      )
     )
     (i64.load
      (get_local $18)
     )
    )
    (i64.store offset=232
     (get_local $23)
     (i64.load
      (get_local $3)
     )
    )
    (i64.store offset=216
     (get_local $23)
     (get_local $4)
    )
    (i64.store
     (tee_local $22
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 216)
       )
       (i32.const 8)
      )
     )
     (get_local $5)
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $23)
       (i32.const 16)
      )
      (i32.const 8)
     )
     (i64.load
      (get_local $21)
     )
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $23)
       (i32.const 16)
      )
      (i32.const 16)
     )
     (i64.load
      (get_local $20)
     )
    )
    (i64.store
     (i32.add
      (get_local $23)
      (i32.const 8)
     )
     (i64.load
      (get_local $22)
     )
    )
    (i64.store offset=16
     (get_local $23)
     (i64.load offset=232
      (get_local $23)
     )
    )
    (i64.store
     (get_local $23)
     (i64.load offset=216
      (get_local $23)
     )
    )
    (call $_ZN5eosio14exchange_state7convertENS_14extended_assetENS_15extended_symbolE
     (i32.add
      (get_local $23)
      (i32.const 128)
     )
     (i32.add
      (get_local $23)
      (i32.const 320)
     )
     (i32.add
      (get_local $23)
      (i32.const 16)
     )
     (get_local $23)
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $23)
       (i32.const 296)
      )
      (i32.const 16)
     )
     (i64.load
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 128)
       )
       (i32.const 16)
      )
     )
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $23)
       (i32.const 296)
      )
      (i32.const 8)
     )
     (i64.load
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 128)
       )
       (i32.const 8)
      )
     )
    )
    (i64.store offset=296
     (get_local $23)
     (i64.load offset=128
      (get_local $23)
     )
    )
    (br $label$11)
   )
  )
  (drop
   (call $memcpy
    (get_local $2)
    (i32.add
     (get_local $23)
     (i32.const 320)
    )
    (i32.const 232)
   )
  )
  (call $printn
   (i64.load
    (get_local $1)
   )
  )
  (call $prints
   (i32.const 2128)
  )
  (call $_ZNK5eosio5asset5printEv
   (get_local $3)
  )
  (call $prints
   (i32.const 1280)
  )
  (call $printn
   (i64.load
    (tee_local $20
     (i32.add
      (get_local $1)
      (i32.const 32)
     )
    )
   )
  )
  (call $prints
   (i32.const 2144)
  )
  (call $_ZNK5eosio5asset5printEv
   (i32.add
    (get_local $23)
    (i32.const 296)
   )
  )
  (call $prints
   (i32.const 1280)
  )
  (call $printn
   (i64.load offset=312
    (get_local $23)
   )
  )
  (call $prints
   (i32.const 1344)
  )
  (block $label$15
   (br_if $label$15
    (i64.eqz
     (tee_local $4
      (i64.load
       (i32.add
        (get_local $1)
        (i32.const 40)
       )
      )
     )
    )
   )
   (call $eosio_assert
    (i64.le_s
     (get_local $4)
     (i64.load offset=296
      (get_local $23)
     )
    )
    (i32.const 2160)
   )
  )
  (i64.store offset=200
   (get_local $23)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
   )
  )
  (i64.store offset=192
   (get_local $23)
   (i64.sub
    (i64.const 0)
    (i64.load
     (i32.add
      (get_local $1)
      (i32.const 16)
     )
    )
   )
  )
  (set_local $4
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=208
   (get_local $23)
   (i64.load
    (get_local $20)
   )
  )
  (i32.store
   (i32.add
    (get_local $23)
    (i32.const 136)
   )
   (i32.const 0)
  )
  (i64.store offset=128
   (get_local $23)
   (i64.const 0)
  )
  (block $label$16
   (block $label$17
    (block $label$18
     (br_if $label$18
      (i32.ge_u
       (tee_local $20
        (call $strlen
         (i32.const 2176)
        )
       )
       (i32.const -16)
      )
     )
     (block $label$19
      (block $label$20
       (block $label$21
        (br_if $label$21
         (i32.ge_u
          (get_local $20)
          (i32.const 11)
         )
        )
        (i32.store8 offset=128
         (get_local $23)
         (i32.shl
          (get_local $20)
          (i32.const 1)
         )
        )
        (set_local $21
         (i32.or
          (i32.add
           (get_local $23)
           (i32.const 128)
          )
          (i32.const 1)
         )
        )
        (br_if $label$20
         (get_local $20)
        )
        (br $label$19)
       )
       (set_local $21
        (call $_Znwj
         (tee_local $22
          (i32.and
           (i32.add
            (get_local $20)
            (i32.const 16)
           )
           (i32.const -16)
          )
         )
        )
       )
       (i32.store offset=128
        (get_local $23)
        (i32.or
         (get_local $22)
         (i32.const 1)
        )
       )
       (i32.store offset=136
        (get_local $23)
        (get_local $21)
       )
       (i32.store offset=132
        (get_local $23)
        (get_local $20)
       )
      )
      (drop
       (call $memcpy
        (get_local $21)
        (i32.const 2176)
        (get_local $20)
       )
      )
     )
     (i32.store8
      (i32.add
       (get_local $21)
       (get_local $20)
      )
      (i32.const 0)
     )
     (i64.store
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 64)
       )
       (i32.const 16)
      )
      (i64.load
       (i32.add
        (i32.add
         (get_local $23)
         (i32.const 192)
        )
        (i32.const 16)
       )
      )
     )
     (i64.store
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 64)
       )
       (i32.const 8)
      )
      (i64.load
       (i32.add
        (i32.add
         (get_local $23)
         (i32.const 192)
        )
        (i32.const 8)
       )
      )
     )
     (i64.store offset=64
      (get_local $23)
      (i64.load offset=192
       (get_local $23)
      )
     )
     (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
      (get_local $6)
      (get_local $4)
      (i32.add
       (get_local $23)
       (i32.const 64)
      )
      (get_local $23)
     )
     (block $label$22
      (br_if $label$22
       (i32.eqz
        (i32.and
         (i32.load8_u offset=128
          (get_local $23)
         )
         (i32.const 1)
        )
       )
      )
      (call $_ZdlPv
       (i32.load offset=136
        (get_local $23)
       )
      )
     )
     (i32.store
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 168)
       )
       (i32.const 20)
      )
      (i32.load
       (i32.add
        (i32.add
         (get_local $23)
         (i32.const 296)
        )
        (i32.const 20)
       )
      )
     )
     (i32.store
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 168)
       )
       (i32.const 16)
      )
      (i32.load
       (i32.add
        (i32.add
         (get_local $23)
         (i32.const 296)
        )
        (i32.const 16)
       )
      )
     )
     (i32.store
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 168)
       )
       (i32.const 12)
      )
      (i32.load
       (i32.add
        (i32.add
         (get_local $23)
         (i32.const 296)
        )
        (i32.const 12)
       )
      )
     )
     (i32.store
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 168)
       )
       (i32.const 8)
      )
      (i32.load
       (i32.add
        (i32.add
         (get_local $23)
         (i32.const 296)
        )
        (i32.const 8)
       )
      )
     )
     (i32.store offset=172
      (get_local $23)
      (i32.load offset=300
       (get_local $23)
      )
     )
     (i32.store offset=168
      (get_local $23)
      (i32.load offset=296
       (get_local $23)
      )
     )
     (set_local $4
      (i64.load
       (get_local $1)
      )
     )
     (i32.store
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 128)
       )
       (i32.const 8)
      )
      (i32.const 0)
     )
     (i64.store offset=128
      (get_local $23)
      (i64.const 0)
     )
     (br_if $label$17
      (i32.ge_u
       (tee_local $20
        (call $strlen
         (i32.const 2192)
        )
       )
       (i32.const -16)
      )
     )
     (block $label$23
      (block $label$24
       (block $label$25
        (br_if $label$25
         (i32.ge_u
          (get_local $20)
          (i32.const 11)
         )
        )
        (i32.store8 offset=128
         (get_local $23)
         (i32.shl
          (get_local $20)
          (i32.const 1)
         )
        )
        (set_local $21
         (i32.or
          (i32.add
           (get_local $23)
           (i32.const 128)
          )
          (i32.const 1)
         )
        )
        (br_if $label$24
         (get_local $20)
        )
        (br $label$23)
       )
       (set_local $21
        (call $_Znwj
         (tee_local $22
          (i32.and
           (i32.add
            (get_local $20)
            (i32.const 16)
           )
           (i32.const -16)
          )
         )
        )
       )
       (i32.store offset=128
        (get_local $23)
        (i32.or
         (get_local $22)
         (i32.const 1)
        )
       )
       (i32.store offset=136
        (get_local $23)
        (get_local $21)
       )
       (i32.store offset=132
        (get_local $23)
        (get_local $20)
       )
      )
      (drop
       (call $memcpy
        (get_local $21)
        (i32.const 2192)
        (get_local $20)
       )
      )
     )
     (i32.store8
      (i32.add
       (get_local $21)
       (get_local $20)
      )
      (i32.const 0)
     )
     (i64.store
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 40)
       )
       (i32.const 16)
      )
      (i64.load
       (i32.add
        (i32.add
         (get_local $23)
         (i32.const 168)
        )
        (i32.const 16)
       )
      )
     )
     (i64.store
      (i32.add
       (i32.add
        (get_local $23)
        (i32.const 40)
       )
       (i32.const 8)
      )
      (i64.load
       (i32.add
        (i32.add
         (get_local $23)
         (i32.const 168)
        )
        (i32.const 8)
       )
      )
     )
     (i64.store offset=40
      (get_local $23)
      (i64.load offset=168
       (get_local $23)
      )
     )
     (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
      (get_local $6)
      (get_local $4)
      (i32.add
       (get_local $23)
       (i32.const 40)
      )
      (get_local $23)
     )
     (block $label$26
      (br_if $label$26
       (i32.eqz
        (i32.and
         (i32.load8_u offset=128
          (get_local $23)
         )
         (i32.const 1)
        )
       )
      )
      (call $_ZdlPv
       (i32.load offset=136
        (get_local $23)
       )
      )
     )
     (block $label$27
      (br_if $label$27
       (i64.eq
        (i64.load
         (i32.add
          (i32.add
           (get_local $23)
           (i32.const 552)
          )
          (i32.const 16)
         )
        )
        (i64.load offset=8
         (tee_local $20
          (i32.load
           (i32.add
            (get_local $23)
            (i32.const 1000)
           )
          )
         )
        )
       )
      )
      (call $eosio_assert
       (i64.eq
        (i64.load
         (i32.add
          (get_local $23)
          (i32.const 584)
         )
        )
        (i64.load
         (i32.add
          (get_local $20)
          (i32.const 24)
         )
        )
       )
       (i32.const 800)
      )
      (set_local $4
       (i64.load
        (i32.add
         (i32.add
          (get_local $23)
          (i32.const 552)
         )
         (i32.const 16)
        )
       )
      )
      (call $eosio_assert
       (i64.eq
        (i64.load
         (i32.add
          (get_local $20)
          (i32.const 16)
         )
        )
        (tee_local $5
         (i64.load
          (i32.add
           (i32.add
            (get_local $23)
            (i32.const 552)
           )
           (i32.const 24)
          )
         )
        )
       )
       (i32.const 816)
      )
      (call $eosio_assert
       (i64.gt_s
        (tee_local $4
         (i64.sub
          (get_local $4)
          (i64.load
           (i32.add
            (get_local $20)
            (i32.const 8)
           )
          )
         )
        )
        (i64.const -4611686018427387904)
       )
       (i32.const 864)
      )
      (call $eosio_assert
       (i64.lt_s
        (get_local $4)
        (i64.const 4611686018427387904)
       )
       (i32.const 896)
      )
      (i64.store
       (i32.add
        (i32.add
         (get_local $23)
         (i32.const 128)
        )
        (i32.const 16)
       )
       (get_local $5)
      )
      (i64.store align=4
       (i32.add
        (get_local $23)
        (i32.const 156)
       )
       (i64.const 0)
      )
      (i64.store offset=136
       (get_local $23)
       (get_local $4)
      )
      (i32.store offset=152
       (get_local $23)
       (i32.const 0)
      )
      (i64.store offset=128
       (get_local $23)
       (i64.load
        (get_local $0)
       )
      )
      (set_local $21
       (i32.add
        (i32.add
         (get_local $23)
         (i32.const 128)
        )
        (i32.const 24)
       )
      )
      (br_if $label$16
       (i32.ge_u
        (tee_local $20
         (call $strlen
          (i32.const 2208)
         )
        )
        (i32.const -16)
       )
      )
      (set_local $22
       (i32.add
        (get_local $0)
        (i32.const 8)
       )
      )
      (block $label$28
       (block $label$29
        (block $label$30
         (br_if $label$30
          (i32.ge_u
           (get_local $20)
           (i32.const 11)
          )
         )
         (i32.store8
          (i32.add
           (get_local $23)
           (i32.const 152)
          )
          (i32.shl
           (get_local $20)
           (i32.const 1)
          )
         )
         (set_local $21
          (i32.add
           (get_local $21)
           (i32.const 1)
          )
         )
         (br_if $label$29
          (get_local $20)
         )
         (br $label$28)
        )
        (set_local $21
         (call $_Znwj
          (tee_local $3
           (i32.and
            (i32.add
             (get_local $20)
             (i32.const 16)
            )
            (i32.const -16)
           )
          )
         )
        )
        (i32.store
         (i32.add
          (get_local $23)
          (i32.const 152)
         )
         (i32.or
          (get_local $3)
          (i32.const 1)
         )
        )
        (i32.store
         (i32.add
          (get_local $23)
          (i32.const 160)
         )
         (get_local $21)
        )
        (i32.store
         (i32.add
          (get_local $23)
          (i32.const 156)
         )
         (get_local $20)
        )
       )
       (drop
        (call $memcpy
         (get_local $21)
         (i32.const 2208)
         (get_local $20)
        )
       )
      )
      (i32.store8
       (i32.add
        (get_local $21)
        (get_local $20)
       )
       (i32.const 0)
      )
      (call $_ZN5eosio8currency14issue_currencyERKNS0_5issueE
       (get_local $22)
       (i32.add
        (get_local $23)
        (i32.const 128)
       )
      )
      (br_if $label$27
       (i32.eqz
        (i32.and
         (i32.load8_u
          (i32.add
           (get_local $23)
           (i32.const 152)
          )
         )
         (i32.const 1)
        )
       )
      )
      (call $_ZdlPv
       (i32.load
        (i32.add
         (get_local $23)
         (i32.const 160)
        )
       )
      )
     )
     (call $_ZN5eosio12market_state4saveEv
      (i32.add
       (get_local $23)
       (i32.const 552)
      )
     )
     (drop
      (call $_ZN5eosio12market_stateD2Ev
       (i32.add
        (get_local $23)
        (i32.const 552)
       )
      )
     )
     (i32.store offset=4
      (i32.const 0)
      (i32.add
       (get_local $23)
       (i32.const 1008)
      )
     )
     (return)
    )
    (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
     (i32.add
      (get_local $23)
      (i32.const 128)
     )
    )
    (unreachable)
   )
   (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
    (i32.add
     (get_local $23)
     (i32.const 128)
    )
   )
   (unreachable)
  )
  (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
   (get_local $21)
  )
  (unreachable)
 )
 (func $_ZNK5eosio5asset5printEv (param $0 i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
  (local $8 i64)
  (local $9 i64)
  (local $10 i32)
  (set_local $10
   (tee_local $2
    (i32.load offset=4
     (i32.const 0)
    )
   )
  )
  (set_local $7
   (i64.const 1)
  )
  (block $label$0
   (br_if $label$0
    (tee_local $5
     (i64.eqz
      (tee_local $8
       (i64.load8_u offset=8
        (get_local $0)
       )
      )
     )
    )
   )
   (set_local $9
    (i64.add
     (get_local $8)
     (i64.const 1)
    )
   )
   (set_local $7
    (i64.const 1)
   )
   (loop $label$1
    (set_local $7
     (i64.mul
      (get_local $7)
      (i64.const 10)
     )
    )
    (br_if $label$1
     (i64.gt_s
      (tee_local $9
       (i64.add
        (get_local $9)
        (i64.const -1)
       )
      )
      (i64.const 1)
     )
    )
   )
  )
  (set_local $1
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (tee_local $2
    (i32.sub
     (get_local $2)
     (i32.and
      (i32.add
       (i32.wrap/i64
        (i64.add
         (get_local $8)
         (i64.const 1)
        )
       )
       (i32.const 15)
      )
      (i32.const 1008)
     )
    )
   )
  )
  (i32.store8
   (tee_local $6
    (i32.add
     (get_local $2)
     (tee_local $3
      (i32.wrap/i64
       (get_local $8)
      )
     )
    )
   )
   (i32.const 0)
  )
  (set_local $4
   (i64.load
    (get_local $0)
   )
  )
  (block $label$2
   (br_if $label$2
    (get_local $5)
   )
   (set_local $8
    (i64.add
     (get_local $8)
     (i64.const 1)
    )
   )
   (set_local $9
    (i64.rem_s
     (get_local $4)
     (get_local $7)
    )
   )
   (set_local $0
    (i32.add
     (get_local $6)
     (i32.const -1)
    )
   )
   (loop $label$3
    (i64.store8
     (get_local $0)
     (i64.add
      (i64.rem_s
       (get_local $9)
       (i64.const 10)
      )
      (i64.const 48)
     )
    )
    (set_local $0
     (i32.add
      (get_local $0)
      (i32.const -1)
     )
    )
    (set_local $9
     (i64.div_s
      (get_local $9)
      (i64.const 10)
     )
    )
    (br_if $label$3
     (i64.gt_s
      (tee_local $8
       (i64.add
        (get_local $8)
        (i64.const -1)
       )
      )
      (i64.const 1)
     )
    )
   )
  )
  (call $printi
   (i64.div_s
    (get_local $4)
    (get_local $7)
   )
  )
  (call $prints
   (i32.const 2352)
  )
  (call $prints_l
   (get_local $2)
   (get_local $3)
  )
  (call $prints
   (i32.const 2368)
  )
  (call $_ZNK5eosio11symbol_type5printEb
   (get_local $1)
   (i32.const 0)
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $10)
  )
 )
 (func $_ZN5eosio8currency14issue_currencyERKNS0_5issueE (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i64)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 80)
    )
   )
  )
  (set_local $6
   (i64.load
    (tee_local $3
     (i32.add
      (get_local $1)
      (i32.const 16)
     )
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $7)
    (i32.const 72)
   )
   (i32.const 0)
  )
  (i64.store offset=56
   (get_local $7)
   (i64.const -1)
  )
  (i64.store offset=64
   (get_local $7)
   (i64.const 0)
  )
  (i64.store offset=40
   (get_local $7)
   (i64.load
    (get_local $0)
   )
  )
  (i64.store offset=48
   (get_local $7)
   (tee_local $6
    (i64.shr_u
     (get_local $6)
     (i64.const 8)
    )
   )
  )
  (set_local $2
   (call $_ZNK5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE3getEyPKc
    (i32.add
     (get_local $7)
     (i32.const 40)
    )
    (get_local $6)
    (i32.const 2224)
   )
  )
  (i32.store offset=32
   (get_local $7)
   (get_local $1)
  )
  (call $_ZN5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE6modifyIZNS1_14issue_currencyERKNS1_5issueEEUlRT_E_EEvRKS2_yOS8_
   (i32.add
    (get_local $7)
    (i32.const 40)
   )
   (get_local $2)
   (i64.const 0)
   (i32.add
    (get_local $7)
    (i32.const 32)
   )
  )
  (i32.store
   (tee_local $4
    (i32.add
     (i32.add
      (get_local $7)
      (i32.const 16)
     )
     (i32.const 12)
    )
   )
   (i32.load
    (i32.add
     (get_local $1)
     (i32.const 20)
    )
   )
  )
  (i32.store
   (tee_local $5
    (i32.add
     (i32.add
      (get_local $7)
      (i32.const 16)
     )
     (i32.const 8)
    )
   )
   (i32.load
    (get_local $3)
   )
  )
  (i32.store offset=20
   (get_local $7)
   (i32.load
    (i32.add
     (get_local $1)
     (i32.const 12)
    )
   )
  )
  (i32.store offset=16
   (get_local $7)
   (i32.load offset=8
    (get_local $1)
   )
  )
  (set_local $6
   (i64.load offset=32
    (get_local $2)
   )
  )
  (i32.store
   (i32.add
    (get_local $7)
    (i32.const 12)
   )
   (i32.load
    (get_local $4)
   )
  )
  (i32.store
   (i32.add
    (get_local $7)
    (i32.const 8)
   )
   (i32.load
    (get_local $5)
   )
  )
  (i32.store offset=4
   (get_local $7)
   (i32.load offset=20
    (get_local $7)
   )
  )
  (i32.store
   (get_local $7)
   (i32.load offset=16
    (get_local $7)
   )
  )
  (call $_ZN5eosio8currency11add_balanceEyNS_5assetERKNS0_14currency_statsEy
   (get_local $0)
   (get_local $6)
   (get_local $7)
   (get_local $2)
   (get_local $6)
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (tee_local $0
      (i32.load offset=64
       (get_local $7)
      )
     )
    )
   )
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i32.eq
       (tee_local $1
        (i32.load
         (tee_local $3
          (i32.add
           (get_local $7)
           (i32.const 68)
          )
         )
        )
       )
       (get_local $0)
      )
     )
     (loop $label$3
      (set_local $2
       (i32.load
        (tee_local $1
         (i32.add
          (get_local $1)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $1)
       (i32.const 0)
      )
      (block $label$4
       (br_if $label$4
        (i32.eqz
         (get_local $2)
        )
       )
       (call $_ZdlPv
        (get_local $2)
       )
      )
      (br_if $label$3
       (i32.ne
        (get_local $0)
        (get_local $1)
       )
      )
     )
     (set_local $1
      (i32.load
       (i32.add
        (get_local $7)
        (i32.const 64)
       )
      )
     )
     (br $label$1)
    )
    (set_local $1
     (get_local $0)
    )
   )
   (i32.store
    (get_local $3)
    (get_local $0)
   )
   (call $_ZdlPv
    (get_local $1)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $7)
    (i32.const 80)
   )
  )
 )
 (func $_ZN5eosio12market_stateD2Ev (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (tee_local $1
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 424)
       )
      )
     )
    )
   )
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i32.eq
       (tee_local $4
        (i32.load
         (tee_local $3
          (i32.add
           (get_local $0)
           (i32.const 428)
          )
         )
        )
       )
       (get_local $1)
      )
     )
     (loop $label$3
      (set_local $2
       (i32.load
        (tee_local $4
         (i32.add
          (get_local $4)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $4)
       (i32.const 0)
      )
      (block $label$4
       (br_if $label$4
        (i32.eqz
         (get_local $2)
        )
       )
       (call $_ZdlPv
        (get_local $2)
       )
      )
      (br_if $label$3
       (i32.ne
        (get_local $1)
        (get_local $4)
       )
      )
     )
     (set_local $4
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 424)
       )
      )
     )
     (br $label$1)
    )
    (set_local $4
     (get_local $1)
    )
   )
   (i32.store
    (get_local $3)
    (get_local $1)
   )
   (call $_ZdlPv
    (get_local $4)
   )
  )
  (block $label$5
   (br_if $label$5
    (i32.eqz
     (tee_local $1
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 384)
       )
      )
     )
    )
   )
   (block $label$6
    (block $label$7
     (br_if $label$7
      (i32.eq
       (tee_local $4
        (i32.load
         (tee_local $3
          (i32.add
           (get_local $0)
           (i32.const 388)
          )
         )
        )
       )
       (get_local $1)
      )
     )
     (loop $label$8
      (set_local $2
       (i32.load
        (tee_local $4
         (i32.add
          (get_local $4)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $4)
       (i32.const 0)
      )
      (block $label$9
       (br_if $label$9
        (i32.eqz
         (get_local $2)
        )
       )
       (call $_ZdlPv
        (get_local $2)
       )
      )
      (br_if $label$8
       (i32.ne
        (get_local $1)
        (get_local $4)
       )
      )
     )
     (set_local $4
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 384)
       )
      )
     )
     (br $label$6)
    )
    (set_local $4
     (get_local $1)
    )
   )
   (i32.store
    (get_local $3)
    (get_local $1)
   )
   (call $_ZdlPv
    (get_local $4)
   )
  )
  (block $label$10
   (br_if $label$10
    (i32.eqz
     (tee_local $1
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 344)
       )
      )
     )
    )
   )
   (block $label$11
    (block $label$12
     (br_if $label$12
      (i32.eq
       (tee_local $4
        (i32.load
         (tee_local $3
          (i32.add
           (get_local $0)
           (i32.const 348)
          )
         )
        )
       )
       (get_local $1)
      )
     )
     (loop $label$13
      (set_local $2
       (i32.load
        (tee_local $4
         (i32.add
          (get_local $4)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $4)
       (i32.const 0)
      )
      (block $label$14
       (br_if $label$14
        (i32.eqz
         (get_local $2)
        )
       )
       (call $_ZdlPv
        (get_local $2)
       )
      )
      (br_if $label$13
       (i32.ne
        (get_local $1)
        (get_local $4)
       )
      )
     )
     (set_local $4
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 344)
       )
      )
     )
     (br $label$11)
    )
    (set_local $4
     (get_local $1)
    )
   )
   (i32.store
    (get_local $3)
    (get_local $1)
   )
   (call $_ZdlPv
    (get_local $4)
   )
  )
  (block $label$15
   (br_if $label$15
    (i32.eqz
     (tee_local $1
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 304)
       )
      )
     )
    )
   )
   (block $label$16
    (block $label$17
     (br_if $label$17
      (i32.eq
       (tee_local $4
        (i32.load
         (tee_local $3
          (i32.add
           (get_local $0)
           (i32.const 308)
          )
         )
        )
       )
       (get_local $1)
      )
     )
     (loop $label$18
      (set_local $2
       (i32.load
        (tee_local $4
         (i32.add
          (get_local $4)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $4)
       (i32.const 0)
      )
      (block $label$19
       (br_if $label$19
        (i32.eqz
         (get_local $2)
        )
       )
       (call $_ZdlPv
        (get_local $2)
       )
      )
      (br_if $label$18
       (i32.ne
        (get_local $1)
        (get_local $4)
       )
      )
     )
     (set_local $4
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 304)
       )
      )
     )
     (br $label$16)
    )
    (set_local $4
     (get_local $1)
    )
   )
   (i32.store
    (get_local $3)
    (get_local $1)
   )
   (call $_ZdlPv
    (get_local $4)
   )
  )
  (block $label$20
   (br_if $label$20
    (i32.eqz
     (tee_local $1
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 264)
       )
      )
     )
    )
   )
   (block $label$21
    (block $label$22
     (br_if $label$22
      (i32.eq
       (tee_local $4
        (i32.load
         (tee_local $3
          (i32.add
           (get_local $0)
           (i32.const 268)
          )
         )
        )
       )
       (get_local $1)
      )
     )
     (loop $label$23
      (set_local $2
       (i32.load
        (tee_local $4
         (i32.add
          (get_local $4)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $4)
       (i32.const 0)
      )
      (block $label$24
       (br_if $label$24
        (i32.eqz
         (get_local $2)
        )
       )
       (call $_ZdlPv
        (get_local $2)
       )
      )
      (br_if $label$23
       (i32.ne
        (get_local $1)
        (get_local $4)
       )
      )
     )
     (set_local $4
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 264)
       )
      )
     )
     (br $label$21)
    )
    (set_local $4
     (get_local $1)
    )
   )
   (i32.store
    (get_local $3)
    (get_local $1)
   )
   (call $_ZdlPv
    (get_local $4)
   )
  )
  (get_local $0)
 )
 (func $_ZNK5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE3getEyPKc (param $0 i32) (param $1 i64) (param $2 i32) (result i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (set_local $4
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i64.eq
      (i64.shr_u
       (i64.load offset=8
        (i32.load
         (get_local $6)
        )
       )
       (i64.const 8)
      )
      (get_local $1)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $5
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $5)
       (get_local $4)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (get_local $3)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=48
       (tee_local $6
        (i32.load
         (i32.add
          (get_local $7)
          (i32.const -24)
         )
        )
       )
      )
      (get_local $0)
     )
     (i32.const 224)
    )
    (br $label$2)
   )
   (set_local $6
    (i32.const 0)
   )
   (br_if $label$2
    (i32.lt_s
     (tee_local $5
      (call $db_find_i64
       (i64.load
        (get_local $0)
       )
       (i64.load offset=8
        (get_local $0)
       )
       (i64.const -4157508551318700032)
       (get_local $1)
      )
     )
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=48
      (tee_local $6
       (call $_ZNK5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE31load_object_by_primary_iteratorEl
        (get_local $0)
        (get_local $5)
       )
      )
     )
     (get_local $0)
    )
    (i32.const 224)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $6)
    (i32.const 0)
   )
   (get_local $2)
  )
  (get_local $6)
 )
 (func $_ZN5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE6modifyIZNS1_14issue_currencyERKNS1_5issueEEUlRT_E_EEvRKS2_yOS8_ (param $0 i32) (param $1 i32) (param $2 i64) (param $3 i32)
  (local $4 i64)
  (local $5 i64)
  (local $6 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $6
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 64)
    )
   )
  )
  (call $eosio_assert
   (i32.eq
    (i32.load offset=48
     (get_local $1)
    )
    (get_local $0)
   )
   (i32.const 400)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load
     (get_local $0)
    )
    (call $current_receiver)
   )
   (i32.const 448)
  )
  (i64.store
   (get_local $1)
   (tee_local $4
    (i64.add
     (i64.load
      (get_local $1)
     )
     (i64.load offset=8
      (i32.load
       (get_local $3)
      )
     )
    )
   )
  )
  (set_local $5
   (i64.load offset=8
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.xor
    (i32.wrap/i64
     (i64.shr_u
      (get_local $4)
      (i64.const 63)
     )
    )
    (i32.const 1)
   )
   (i32.const 1216)
  )
  (call $eosio_assert
   (i64.eq
    (tee_local $4
     (i64.shr_u
      (get_local $5)
      (i64.const 8)
     )
    )
    (i64.shr_u
     (i64.load offset=8
      (get_local $1)
     )
     (i64.const 8)
    )
   )
   (i32.const 544)
  )
  (i32.store offset=56
   (get_local $6)
   (i32.add
    (get_local $6)
    (i32.const 45)
   )
  )
  (i32.store offset=52
   (get_local $6)
   (get_local $6)
  )
  (i32.store offset=48
   (get_local $6)
   (get_local $6)
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_8currency14currency_statsE
    (i32.add
     (get_local $6)
     (i32.const 48)
    )
    (get_local $1)
   )
  )
  (call $db_update_i64
   (i32.load offset=52
    (get_local $1)
   )
   (get_local $2)
   (get_local $6)
   (i32.const 45)
  )
  (block $label$0
   (br_if $label$0
    (i64.lt_u
     (get_local $4)
     (i64.load offset=16
      (get_local $0)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (i64.add
     (get_local $4)
     (i64.const 1)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $6)
    (i32.const 64)
   )
  )
 )
 (func $_ZN5eosio8currency11add_balanceEyNS_5assetERKNS0_14currency_statsEy (param $0 i32) (param $1 i64) (param $2 i32) (param $3 i32) (param $4 i64)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 64)
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $7)
    (i32.const 56)
   )
   (i32.const 0)
  )
  (i64.store offset=40
   (get_local $7)
   (i64.const -1)
  )
  (i64.store offset=48
   (get_local $7)
   (i64.const 0)
  )
  (i64.store offset=24
   (get_local $7)
   (tee_local $5
    (i64.load
     (get_local $0)
    )
   )
  )
  (i64.store offset=32
   (get_local $7)
   (get_local $1)
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i32.le_s
       (tee_local $0
        (call $db_find_i64
         (get_local $5)
         (get_local $1)
         (i64.const 3607749779137757184)
         (i64.shr_u
          (i64.load offset=8
           (get_local $2)
          )
          (i64.const 8)
         )
        )
       )
       (i32.const -1)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=20
        (tee_local $0
         (call $_ZNK5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE31load_object_by_primary_iteratorEl
          (i32.add
           (get_local $7)
           (i32.const 24)
          )
          (get_local $0)
         )
        )
       )
       (i32.add
        (get_local $7)
        (i32.const 24)
       )
      )
      (i32.const 224)
     )
     (call $eosio_assert
      (select
       (i32.load8_u offset=17
        (get_local $0)
       )
       (i32.const 1)
       (i32.load8_u offset=44
        (get_local $3)
       )
      )
      (i32.const 2304)
     )
     (i32.store offset=8
      (get_local $7)
      (get_local $2)
     )
     (call $eosio_assert
      (i32.const 1)
      (i32.const 352)
     )
     (call $_ZN5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE6modifyIZNS1_11add_balanceEyNS_5assetERKNS1_14currency_statsEyEUlRT_E0_EEvRKS2_yOS9_
      (i32.add
       (get_local $7)
       (i32.const 24)
      )
      (get_local $0)
      (i64.const 0)
      (i32.add
       (get_local $7)
       (i32.const 8)
      )
     )
     (br_if $label$1
      (tee_local $3
       (i32.load offset=48
        (get_local $7)
       )
      )
     )
     (br $label$0)
    )
    (call $eosio_assert
     (i32.xor
      (i32.load8_u offset=44
       (get_local $3)
      )
      (i32.const 1)
     )
     (i32.const 2256)
    )
    (i32.store offset=16
     (get_local $7)
     (get_local $2)
    )
    (call $_ZN5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE7emplaceIZNS1_11add_balanceEyNS_5assetERKNS1_14currency_statsEyEUlRT_E_EENS3_14const_iteratorEyOS9_
     (i32.add
      (get_local $7)
      (i32.const 8)
     )
     (i32.add
      (get_local $7)
      (i32.const 24)
     )
     (get_local $4)
     (i32.add
      (get_local $7)
      (i32.const 16)
     )
    )
    (br_if $label$0
     (i32.eqz
      (tee_local $3
       (i32.load offset=48
        (get_local $7)
       )
      )
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (i32.eq
       (tee_local $2
        (i32.load
         (tee_local $6
          (i32.add
           (get_local $7)
           (i32.const 52)
          )
         )
        )
       )
       (get_local $3)
      )
     )
     (loop $label$5
      (set_local $0
       (i32.load
        (tee_local $2
         (i32.add
          (get_local $2)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $2)
       (i32.const 0)
      )
      (block $label$6
       (br_if $label$6
        (i32.eqz
         (get_local $0)
        )
       )
       (call $_ZdlPv
        (get_local $0)
       )
      )
      (br_if $label$5
       (i32.ne
        (get_local $3)
        (get_local $2)
       )
      )
     )
     (set_local $2
      (i32.load
       (i32.add
        (get_local $7)
        (i32.const 48)
       )
      )
     )
     (br $label$3)
    )
    (set_local $2
     (get_local $3)
    )
   )
   (i32.store
    (get_local $6)
    (get_local $3)
   )
   (call $_ZdlPv
    (get_local $2)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $7)
    (i32.const 64)
   )
  )
 )
 (func $_ZN5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE7emplaceIZNS1_11add_balanceEyNS_5assetERKNS1_14currency_statsEyEUlRT_E_EENS3_14const_iteratorEyOS9_ (param $0 i32) (param $1 i32) (param $2 i64) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i64.store offset=40
   (get_local $7)
   (get_local $2)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load
     (get_local $1)
    )
    (call $current_receiver)
   )
   (i32.const 288)
  )
  (i32.store offset=20
   (get_local $7)
   (get_local $3)
  )
  (i32.store offset=16
   (get_local $7)
   (get_local $1)
  )
  (i32.store offset=24
   (get_local $7)
   (i32.add
    (get_local $7)
    (i32.const 40)
   )
  )
  (i64.store offset=8
   (tee_local $4
    (call $_Znwj
     (i32.const 32)
    )
   )
   (i64.const 1398362884)
  )
  (i64.store
   (get_local $4)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $2
   (i64.const 5462355)
  )
  (set_local $3
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $2)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $2
          (i64.shr_u
           (get_local $2)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $2
           (i64.shr_u
            (get_local $2)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $3
          (i32.add
           (get_local $3)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $6
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $3
        (i32.add
         (get_local $3)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $6
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $6)
   (i32.const 80)
  )
  (i32.store offset=20
   (get_local $4)
   (get_local $1)
  )
  (i32.store16 offset=16
   (get_local $4)
   (i32.const 256)
  )
  (call $_ZZN5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE7emplaceIZNS1_11add_balanceEyNS_5assetERKNS1_14currency_statsEyEUlRT_E_EENS3_14const_iteratorEyOS9_ENKUlSA_E_clINS3_4itemEEEDaSA_
   (i32.add
    (get_local $7)
    (i32.const 16)
   )
   (get_local $4)
  )
  (i32.store offset=32
   (get_local $7)
   (get_local $4)
  )
  (i64.store offset=16
   (get_local $7)
   (tee_local $2
    (i64.shr_u
     (i64.load
      (i32.add
       (get_local $4)
       (i32.const 8)
      )
     )
     (i64.const 8)
    )
   )
  )
  (i32.store offset=12
   (get_local $7)
   (tee_local $6
    (i32.load offset=24
     (get_local $4)
    )
   )
  )
  (block $label$5
   (block $label$6
    (br_if $label$6
     (i32.ge_u
      (tee_local $3
       (i32.load
        (tee_local $5
         (i32.add
          (get_local $1)
          (i32.const 28)
         )
        )
       )
      )
      (i32.load
       (i32.add
        (get_local $1)
        (i32.const 32)
       )
      )
     )
    )
    (i64.store offset=8
     (get_local $3)
     (get_local $2)
    )
    (i32.store offset=16
     (get_local $3)
     (get_local $6)
    )
    (i32.store offset=32
     (get_local $7)
     (i32.const 0)
    )
    (i32.store
     (get_local $3)
     (get_local $4)
    )
    (i32.store
     (get_local $5)
     (i32.add
      (get_local $3)
      (i32.const 24)
     )
    )
    (br $label$5)
   )
   (call $_ZNSt3__16vectorIN5eosio11multi_indexILy3607749779137757184ENS1_8currency7accountEJEE8item_ptrENS_9allocatorIS6_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS5_4itemENS_14default_deleteISC_EEEERyRlEEEvDpOT_
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.add
     (get_local $7)
     (i32.const 32)
    )
    (i32.add
     (get_local $7)
     (i32.const 16)
    )
    (i32.add
     (get_local $7)
     (i32.const 12)
    )
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $4)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (set_local $3
   (i32.load offset=32
    (get_local $7)
   )
  )
  (i32.store offset=32
   (get_local $7)
   (i32.const 0)
  )
  (block $label$7
   (br_if $label$7
    (i32.eqz
     (get_local $3)
    )
   )
   (call $_ZdlPv
    (get_local $3)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $7)
    (i32.const 48)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE31load_object_by_primary_iteratorEl (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
  (local $8 i32)
  (local $9 i32)
  (set_local $8
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $9)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $6
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $2
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $3
    (i32.sub
     (i32.const 0)
     (get_local $2)
    )
   )
   (set_local $5
    (i32.add
     (get_local $6)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i32.eq
      (i32.load
       (i32.add
        (get_local $5)
        (i32.const 16)
       )
      )
      (get_local $1)
     )
    )
    (set_local $6
     (get_local $5)
    )
    (set_local $5
     (tee_local $4
      (i32.add
       (get_local $5)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $4)
       (get_local $3)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $6)
      (get_local $2)
     )
    )
    (set_local $4
     (i32.load
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br $label$2)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $5
       (call $db_get_i64
        (get_local $1)
        (i32.const 0)
        (i32.const 0)
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 656)
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.lt_u
       (get_local $5)
       (i32.const 513)
      )
     )
     (set_local $4
      (call $malloc
       (get_local $5)
      )
     )
     (br $label$4)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $4
      (i32.sub
       (get_local $9)
       (i32.and
        (i32.add
         (get_local $5)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $db_get_i64
     (get_local $1)
     (get_local $4)
     (get_local $5)
    )
   )
   (i32.store offset=36
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=32
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=40
    (get_local $8)
    (i32.add
     (get_local $4)
     (get_local $5)
    )
   )
   (block $label$6
    (br_if $label$6
     (i32.lt_u
      (get_local $5)
      (i32.const 513)
     )
    )
    (call $free
     (get_local $4)
    )
   )
   (set_local $3
    (i32.add
     (get_local $0)
     (i32.const 24)
    )
   )
   (i64.store offset=8
    (tee_local $4
     (call $_Znwj
      (i32.const 32)
     )
    )
    (i64.const 1398362884)
   )
   (i64.store
    (get_local $4)
    (i64.const 0)
   )
   (call $eosio_assert
    (i32.const 1)
    (i32.const 16)
   )
   (set_local $7
    (i64.const 5462355)
   )
   (set_local $5
    (i32.const 0)
   )
   (block $label$7
    (block $label$8
     (loop $label$9
      (br_if $label$8
       (i32.gt_u
        (i32.add
         (i32.shl
          (i32.wrap/i64
           (get_local $7)
          )
          (i32.const 24)
         )
         (i32.const -1073741825)
        )
        (i32.const 452984830)
       )
      )
      (block $label$10
       (br_if $label$10
        (i64.ne
         (i64.and
          (tee_local $7
           (i64.shr_u
            (get_local $7)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (loop $label$11
        (br_if $label$8
         (i64.ne
          (i64.and
           (tee_local $7
            (i64.shr_u
             (get_local $7)
             (i64.const 8)
            )
           )
           (i64.const 255)
          )
          (i64.const 0)
         )
        )
        (br_if $label$11
         (i32.lt_s
          (tee_local $5
           (i32.add
            (get_local $5)
            (i32.const 1)
           )
          )
          (i32.const 7)
         )
        )
       )
      )
      (set_local $6
       (i32.const 1)
      )
      (br_if $label$9
       (i32.lt_s
        (tee_local $5
         (i32.add
          (get_local $5)
          (i32.const 1)
         )
        )
        (i32.const 7)
       )
      )
      (br $label$7)
     )
    )
    (set_local $6
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (get_local $6)
    (i32.const 80)
   )
   (i32.store offset=20
    (get_local $4)
    (get_local $0)
   )
   (i32.store16 offset=16
    (get_local $4)
    (i32.const 256)
   )
   (drop
    (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_8currency7accountE
     (i32.add
      (get_local $8)
      (i32.const 32)
     )
     (get_local $4)
    )
   )
   (i32.store offset=24
    (get_local $4)
    (get_local $1)
   )
   (i32.store offset=24
    (get_local $8)
    (get_local $4)
   )
   (i64.store offset=16
    (get_local $8)
    (tee_local $7
     (i64.shr_u
      (i64.load
       (i32.add
        (get_local $4)
        (i32.const 8)
       )
      )
      (i64.const 8)
     )
    )
   )
   (i32.store offset=12
    (get_local $8)
    (tee_local $6
     (i32.load offset=24
      (get_local $4)
     )
    )
   )
   (block $label$12
    (block $label$13
     (br_if $label$13
      (i32.ge_u
       (tee_local $5
        (i32.load
         (tee_local $1
          (i32.add
           (get_local $0)
           (i32.const 28)
          )
         )
        )
       )
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 32)
        )
       )
      )
     )
     (i64.store offset=8
      (get_local $5)
      (get_local $7)
     )
     (i32.store offset=16
      (get_local $5)
      (get_local $6)
     )
     (i32.store offset=24
      (get_local $8)
      (i32.const 0)
     )
     (i32.store
      (get_local $5)
      (get_local $4)
     )
     (i32.store
      (get_local $1)
      (i32.add
       (get_local $5)
       (i32.const 24)
      )
     )
     (br $label$12)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy3607749779137757184ENS1_8currency7accountEJEE8item_ptrENS_9allocatorIS6_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS5_4itemENS_14default_deleteISC_EEEERyRlEEEvDpOT_
     (get_local $3)
     (i32.add
      (get_local $8)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 16)
     )
     (i32.add
      (get_local $8)
      (i32.const 12)
     )
    )
   )
   (set_local $5
    (i32.load offset=24
     (get_local $8)
    )
   )
   (i32.store offset=24
    (get_local $8)
    (i32.const 0)
   )
   (br_if $label$2
    (i32.eqz
     (get_local $5)
    )
   )
   (call $_ZdlPv
    (get_local $5)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 48)
   )
  )
  (get_local $4)
 )
 (func $_ZN5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE6modifyIZNS1_11add_balanceEyNS_5assetERKNS1_14currency_statsEyEUlRT_E0_EEvRKS2_yOS9_ (param $0 i32) (param $1 i32) (param $2 i64) (param $3 i32)
  (local $4 i64)
  (local $5 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $5
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (call $eosio_assert
   (i32.eq
    (i32.load
     (i32.add
      (get_local $1)
      (i32.const 20)
     )
    )
    (get_local $0)
   )
   (i32.const 400)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load
     (get_local $0)
    )
    (call $current_receiver)
   )
   (i32.const 448)
  )
  (i64.store
   (get_local $1)
   (i64.add
    (i64.load
     (get_local $1)
    )
    (i64.load
     (i32.load
      (get_local $3)
     )
    )
   )
  )
  (set_local $4
   (i64.load offset=8
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 544)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (get_local $5)
    (get_local $1)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.or
     (get_local $5)
     (i32.const 8)
    )
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store8 offset=31
   (get_local $5)
   (i32.load8_u offset=16
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $5)
     (i32.const 16)
    )
    (i32.add
     (get_local $5)
     (i32.const 31)
    )
    (i32.const 1)
   )
  )
  (i32.store8 offset=31
   (get_local $5)
   (i32.load8_u offset=17
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $5)
     (i32.const 17)
    )
    (i32.add
     (get_local $5)
     (i32.const 31)
    )
    (i32.const 1)
   )
  )
  (call $db_update_i64
   (i32.load offset=24
    (get_local $1)
   )
   (get_local $2)
   (get_local $5)
   (i32.const 18)
  )
  (block $label$0
   (br_if $label$0
    (i64.lt_u
     (tee_local $2
      (i64.shr_u
       (get_local $4)
       (i64.const 8)
      )
     )
     (i64.load offset=16
      (get_local $0)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (i64.add
     (get_local $2)
     (i64.const 1)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $5)
    (i32.const 32)
   )
  )
 )
 (func $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_8currency7accountE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $3
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $1)
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=8
     (get_local $0)
    )
    (get_local $2)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 14)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 1)
    )
   )
  )
  (i32.store8 offset=16
   (get_local $1)
   (i32.ne
    (i32.load8_u offset=14
     (get_local $3)
    )
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=8
     (get_local $0)
    )
    (get_local $2)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 15)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store8 offset=17
   (get_local $1)
   (i32.ne
    (i32.load8_u offset=15
     (get_local $3)
    )
    (i32.const 0)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $3)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZNSt3__16vectorIN5eosio11multi_indexILy3607749779137757184ENS1_8currency7accountEJEE8item_ptrENS_9allocatorIS6_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS5_4itemENS_14default_deleteISC_EEEERyRlEEEvDpOT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.ge_u
      (tee_local $5
       (i32.add
        (tee_local $4
         (i32.div_s
          (i32.sub
           (i32.load offset=4
            (get_local $0)
           )
           (tee_local $6
            (i32.load
             (get_local $0)
            )
           )
          )
          (i32.const 24)
         )
        )
        (i32.const 1)
       )
      )
      (i32.const 178956971)
     )
    )
    (set_local $7
     (i32.const 178956970)
    )
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.gt_u
        (tee_local $6
         (i32.div_s
          (i32.sub
           (i32.load offset=8
            (get_local $0)
           )
           (get_local $6)
          )
          (i32.const 24)
         )
        )
        (i32.const 89478484)
       )
      )
      (br_if $label$2
       (i32.eqz
        (tee_local $7
         (select
          (get_local $5)
          (tee_local $7
           (i32.shl
            (get_local $6)
            (i32.const 1)
           )
          )
          (i32.lt_u
           (get_local $7)
           (get_local $5)
          )
         )
        )
       )
      )
     )
     (set_local $6
      (call $_Znwj
       (i32.mul
        (get_local $7)
        (i32.const 24)
       )
      )
     )
     (br $label$0)
    )
    (set_local $7
     (i32.const 0)
    )
    (set_local $6
     (i32.const 0)
    )
    (br $label$0)
   )
   (call $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
    (get_local $0)
   )
   (unreachable)
  )
  (set_local $5
   (i32.load
    (get_local $1)
   )
  )
  (i32.store
   (get_local $1)
   (i32.const 0)
  )
  (i32.store
   (tee_local $1
    (i32.add
     (get_local $6)
     (i32.mul
      (get_local $4)
      (i32.const 24)
     )
    )
   )
   (get_local $5)
  )
  (i64.store offset=8
   (get_local $1)
   (i64.load
    (get_local $2)
   )
  )
  (i32.store offset=16
   (get_local $1)
   (i32.load
    (get_local $3)
   )
  )
  (set_local $4
   (i32.add
    (get_local $6)
    (i32.mul
     (get_local $7)
     (i32.const 24)
    )
   )
  )
  (set_local $5
   (i32.add
    (get_local $1)
    (i32.const 24)
   )
  )
  (block $label$4
   (block $label$5
    (br_if $label$5
     (i32.eq
      (tee_local $6
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
      )
      (tee_local $7
       (i32.load
        (get_local $0)
       )
      )
     )
    )
    (loop $label$6
     (set_local $3
      (i32.load
       (tee_local $2
        (i32.add
         (get_local $6)
         (i32.const -24)
        )
       )
      )
     )
     (i32.store
      (get_local $2)
      (i32.const 0)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
      (get_local $3)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -8)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -8)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -12)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -12)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -16)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -16)
       )
      )
     )
     (set_local $1
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
     )
     (set_local $6
      (get_local $2)
     )
     (br_if $label$6
      (i32.ne
       (get_local $7)
       (get_local $2)
      )
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $6
     (i32.load
      (get_local $0)
     )
    )
    (br $label$4)
   )
   (set_local $6
    (get_local $7)
   )
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $5)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
   (get_local $4)
  )
  (block $label$7
   (br_if $label$7
    (i32.eq
     (get_local $7)
     (get_local $6)
    )
   )
   (loop $label$8
    (set_local $1
     (i32.load
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.const 0)
    )
    (block $label$9
     (br_if $label$9
      (i32.eqz
       (get_local $1)
      )
     )
     (call $_ZdlPv
      (get_local $1)
     )
    )
    (br_if $label$8
     (i32.ne
      (get_local $6)
      (get_local $7)
     )
    )
   )
  )
  (block $label$10
   (br_if $label$10
    (i32.eqz
     (get_local $6)
    )
   )
   (call $_ZdlPv
    (get_local $6)
   )
  )
 )
 (func $_ZZN5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE7emplaceIZNS1_11add_balanceEyNS_5assetERKNS1_14currency_statsEyEUlRT_E_EENS3_14const_iteratorEyOS9_ENKUlSA_E_clINS3_4itemEEEDaSA_ (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $6
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (set_local $2
   (i32.load
    (get_local $0)
   )
  )
  (i64.store
   (get_local $1)
   (i64.load
    (tee_local $4
     (i32.load
      (i32.load offset=4
       (get_local $0)
      )
     )
    )
   )
  )
  (i64.store
   (tee_local $5
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (get_local $4)
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (get_local $6)
    (get_local $1)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.or
     (get_local $6)
     (i32.const 8)
    )
    (get_local $5)
    (i32.const 8)
   )
  )
  (i32.store8 offset=31
   (get_local $6)
   (i32.load8_u offset=16
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $6)
     (i32.const 16)
    )
    (i32.add
     (get_local $6)
     (i32.const 31)
    )
    (i32.const 1)
   )
  )
  (i32.store8 offset=31
   (get_local $6)
   (i32.load8_u offset=17
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $6)
     (i32.const 17)
    )
    (i32.add
     (get_local $6)
     (i32.const 31)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=24
   (get_local $1)
   (call $db_store_i64
    (i64.load offset=8
     (get_local $2)
    )
    (i64.const 3607749779137757184)
    (i64.load
     (i32.load offset=8
      (get_local $0)
     )
    )
    (tee_local $3
     (i64.shr_u
      (i64.load
       (get_local $5)
      )
      (i64.const 8)
     )
    )
    (get_local $6)
    (i32.const 18)
   )
  )
  (block $label$0
   (br_if $label$0
    (i64.lt_u
     (get_local $3)
     (i64.load offset=16
      (get_local $2)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $2)
     (i32.const 16)
    )
    (i64.add
     (get_local $3)
     (i64.const 1)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $6)
    (i32.const 32)
   )
  )
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_8currency14currency_statsE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $3
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (get_local $1)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (i32.store8 offset=11
   (get_local $3)
   (i32.load8_u offset=40
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 0)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $3)
     (i32.const 11)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 1)
    )
   )
  )
  (i32.store8 offset=12
   (get_local $3)
   (i32.load8_u offset=41
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 0)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $3)
     (i32.const 12)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 1)
    )
   )
  )
  (i32.store8 offset=13
   (get_local $3)
   (i32.load8_u offset=42
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 0)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $3)
     (i32.const 13)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 1)
    )
   )
  )
  (i32.store8 offset=14
   (get_local $3)
   (i32.load8_u offset=43
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 0)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $3)
     (i32.const 14)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 1)
    )
   )
  )
  (i32.store8 offset=15
   (get_local $3)
   (i32.load8_u offset=44
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 0)
   )
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $3)
     (i32.const 15)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $3)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZNK5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE31load_object_by_primary_iteratorEl (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (set_local $8
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $9)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $2
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $3
    (i32.sub
     (i32.const 0)
     (get_local $2)
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i32.eq
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const 16)
       )
      )
      (get_local $1)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $4
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $4)
       (get_local $3)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (get_local $2)
     )
    )
    (set_local $6
     (i32.load
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br $label$2)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $6
       (call $db_get_i64
        (get_local $1)
        (i32.const 0)
        (i32.const 0)
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 656)
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.lt_u
       (get_local $6)
       (i32.const 513)
      )
     )
     (set_local $4
      (call $malloc
       (get_local $6)
      )
     )
     (br $label$4)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $4
      (i32.sub
       (get_local $9)
       (i32.and
        (i32.add
         (get_local $6)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $db_get_i64
     (get_local $1)
     (get_local $4)
     (get_local $6)
    )
   )
   (i32.store offset=36
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=32
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=40
    (get_local $8)
    (i32.add
     (get_local $4)
     (get_local $6)
    )
   )
   (block $label$6
    (br_if $label$6
     (i32.lt_u
      (get_local $6)
      (i32.const 513)
     )
    )
    (call $free
     (get_local $4)
    )
   )
   (set_local $4
    (call $_ZN5eosio8currency14currency_statsC2Ev
     (tee_local $6
      (call $_Znwj
       (i32.const 64)
      )
     )
    )
   )
   (i32.store offset=48
    (get_local $6)
    (get_local $0)
   )
   (drop
    (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_8currency14currency_statsE
     (i32.add
      (get_local $8)
      (i32.const 32)
     )
     (get_local $4)
    )
   )
   (i32.store offset=52
    (get_local $6)
    (get_local $1)
   )
   (i32.store offset=24
    (get_local $8)
    (get_local $6)
   )
   (i64.store offset=16
    (get_local $8)
    (tee_local $5
     (i64.shr_u
      (i64.load offset=8
       (get_local $6)
      )
      (i64.const 8)
     )
    )
   )
   (i32.store offset=12
    (get_local $8)
    (tee_local $7
     (i32.load offset=52
      (get_local $6)
     )
    )
   )
   (block $label$7
    (block $label$8
     (br_if $label$8
      (i32.ge_u
       (tee_local $4
        (i32.load
         (tee_local $1
          (i32.add
           (get_local $0)
           (i32.const 28)
          )
         )
        )
       )
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 32)
        )
       )
      )
     )
     (i64.store offset=8
      (get_local $4)
      (get_local $5)
     )
     (i32.store offset=16
      (get_local $4)
      (get_local $7)
     )
     (i32.store offset=24
      (get_local $8)
      (i32.const 0)
     )
     (i32.store
      (get_local $4)
      (get_local $6)
     )
     (i32.store
      (get_local $1)
      (i32.add
       (get_local $4)
       (i32.const 24)
      )
     )
     (br $label$7)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy14289235522390851584ENS1_8currency14currency_statsEJEE8item_ptrENS_9allocatorIS6_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS5_4itemENS_14default_deleteISC_EEEERyRlEEEvDpOT_
     (i32.add
      (get_local $0)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 16)
     )
     (i32.add
      (get_local $8)
      (i32.const 12)
     )
    )
   )
   (set_local $4
    (i32.load offset=24
     (get_local $8)
    )
   )
   (i32.store offset=24
    (get_local $8)
    (i32.const 0)
   )
   (br_if $label$2
    (i32.eqz
     (get_local $4)
    )
   )
   (call $_ZdlPv
    (get_local $4)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 48)
   )
  )
  (get_local $6)
 )
 (func $_ZN5eosio8currency14currency_statsC2Ev (param $0 i32) (result i32)
  (local $1 i64)
  (local $2 i32)
  (local $3 i32)
  (i64.store offset=8
   (get_local $0)
   (i64.const 1398362884)
  )
  (i64.store
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load offset=8
     (get_local $0)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (i64.store
   (tee_local $2
    (i32.add
     (get_local $0)
     (i32.const 24)
    )
   )
   (i64.const 1398362884)
  )
  (i64.store offset=16
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load
     (get_local $2)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$5
   (block $label$6
    (loop $label$7
     (br_if $label$6
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$8
      (br_if $label$8
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$9
       (br_if $label$6
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$9
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$7
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$5)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (i32.store8 offset=44
   (get_local $0)
   (i32.const 0)
  )
  (i32.store offset=40
   (get_local $0)
   (i32.const 65793)
  )
  (get_local $0)
 )
 (func $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_8currency14currency_statsE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $3
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $1)
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=8
     (get_local $0)
    )
    (get_local $2)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 11)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 1)
    )
   )
  )
  (i32.store8 offset=40
   (get_local $1)
   (i32.ne
    (i32.load8_u offset=11
     (get_local $3)
    )
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=8
     (get_local $0)
    )
    (get_local $2)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 12)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 1)
    )
   )
  )
  (i32.store8 offset=41
   (get_local $1)
   (i32.ne
    (i32.load8_u offset=12
     (get_local $3)
    )
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=8
     (get_local $0)
    )
    (get_local $2)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 13)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 1)
    )
   )
  )
  (i32.store8 offset=42
   (get_local $1)
   (i32.ne
    (i32.load8_u offset=13
     (get_local $3)
    )
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=8
     (get_local $0)
    )
    (get_local $2)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 14)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 1)
    )
   )
  )
  (i32.store8 offset=43
   (get_local $1)
   (i32.ne
    (i32.load8_u offset=14
     (get_local $3)
    )
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=8
     (get_local $0)
    )
    (get_local $2)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 15)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store8 offset=44
   (get_local $1)
   (i32.ne
    (i32.load8_u offset=15
     (get_local $3)
    )
    (i32.const 0)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $3)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZNSt3__16vectorIN5eosio11multi_indexILy14289235522390851584ENS1_8currency14currency_statsEJEE8item_ptrENS_9allocatorIS6_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS5_4itemENS_14default_deleteISC_EEEERyRlEEEvDpOT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.ge_u
      (tee_local $5
       (i32.add
        (tee_local $4
         (i32.div_s
          (i32.sub
           (i32.load offset=4
            (get_local $0)
           )
           (tee_local $6
            (i32.load
             (get_local $0)
            )
           )
          )
          (i32.const 24)
         )
        )
        (i32.const 1)
       )
      )
      (i32.const 178956971)
     )
    )
    (set_local $7
     (i32.const 178956970)
    )
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.gt_u
        (tee_local $6
         (i32.div_s
          (i32.sub
           (i32.load offset=8
            (get_local $0)
           )
           (get_local $6)
          )
          (i32.const 24)
         )
        )
        (i32.const 89478484)
       )
      )
      (br_if $label$2
       (i32.eqz
        (tee_local $7
         (select
          (get_local $5)
          (tee_local $7
           (i32.shl
            (get_local $6)
            (i32.const 1)
           )
          )
          (i32.lt_u
           (get_local $7)
           (get_local $5)
          )
         )
        )
       )
      )
     )
     (set_local $6
      (call $_Znwj
       (i32.mul
        (get_local $7)
        (i32.const 24)
       )
      )
     )
     (br $label$0)
    )
    (set_local $7
     (i32.const 0)
    )
    (set_local $6
     (i32.const 0)
    )
    (br $label$0)
   )
   (call $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
    (get_local $0)
   )
   (unreachable)
  )
  (set_local $5
   (i32.load
    (get_local $1)
   )
  )
  (i32.store
   (get_local $1)
   (i32.const 0)
  )
  (i32.store
   (tee_local $1
    (i32.add
     (get_local $6)
     (i32.mul
      (get_local $4)
      (i32.const 24)
     )
    )
   )
   (get_local $5)
  )
  (i64.store offset=8
   (get_local $1)
   (i64.load
    (get_local $2)
   )
  )
  (i32.store offset=16
   (get_local $1)
   (i32.load
    (get_local $3)
   )
  )
  (set_local $4
   (i32.add
    (get_local $6)
    (i32.mul
     (get_local $7)
     (i32.const 24)
    )
   )
  )
  (set_local $5
   (i32.add
    (get_local $1)
    (i32.const 24)
   )
  )
  (block $label$4
   (block $label$5
    (br_if $label$5
     (i32.eq
      (tee_local $6
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
      )
      (tee_local $7
       (i32.load
        (get_local $0)
       )
      )
     )
    )
    (loop $label$6
     (set_local $3
      (i32.load
       (tee_local $2
        (i32.add
         (get_local $6)
         (i32.const -24)
        )
       )
      )
     )
     (i32.store
      (get_local $2)
      (i32.const 0)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
      (get_local $3)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -8)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -8)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -12)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -12)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -16)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -16)
       )
      )
     )
     (set_local $1
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
     )
     (set_local $6
      (get_local $2)
     )
     (br_if $label$6
      (i32.ne
       (get_local $7)
       (get_local $2)
      )
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $6
     (i32.load
      (get_local $0)
     )
    )
    (br $label$4)
   )
   (set_local $6
    (get_local $7)
   )
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $5)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
   (get_local $4)
  )
  (block $label$7
   (br_if $label$7
    (i32.eq
     (get_local $7)
     (get_local $6)
    )
   )
   (loop $label$8
    (set_local $1
     (i32.load
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.const 0)
    )
    (block $label$9
     (br_if $label$9
      (i32.eqz
       (get_local $1)
      )
     )
     (call $_ZdlPv
      (get_local $1)
     )
    )
    (br_if $label$8
     (i32.ne
      (get_local $6)
      (get_local $7)
     )
    )
   )
  )
  (block $label$10
   (br_if $label$10
    (i32.eqz
     (get_local $6)
    )
   )
   (call $_ZdlPv
    (get_local $6)
   )
  )
 )
 (func $_ZN5eosio8exchange2onERKNS0_8upmarginE (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i64)
  (local $5 i64)
  (local $6 i64)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 576)
    )
   )
  )
  (call $require_auth
   (i64.load
    (get_local $1)
   )
  )
  (set_local $9
   (i32.const 0)
  )
  (set_local $8
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i64.gt_u
     (i64.add
      (i64.load offset=16
       (get_local $1)
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $6
    (i64.shr_u
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 24)
      )
     )
     (i64.const 8)
    )
   )
   (set_local $7
    (i32.const 0)
   )
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $6)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $6
          (i64.shr_u
           (get_local $6)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $6
           (i64.shr_u
            (get_local $6)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $7
          (i32.add
           (get_local $7)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $8
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $7
        (i32.add
         (get_local $7)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $8
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $8)
   (i32.const 2384)
  )
  (set_local $2
   (i32.add
    (get_local $1)
    (i32.const 40)
   )
  )
  (block $label$5
   (br_if $label$5
    (i64.gt_u
     (i64.add
      (i64.load offset=40
       (get_local $1)
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $6
    (i64.shr_u
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 48)
      )
     )
     (i64.const 8)
    )
   )
   (set_local $7
    (i32.const 0)
   )
   (block $label$6
    (loop $label$7
     (br_if $label$6
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $6)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$8
      (br_if $label$8
       (i64.ne
        (i64.and
         (tee_local $6
          (i64.shr_u
           (get_local $6)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$9
       (br_if $label$6
        (i64.ne
         (i64.and
          (tee_local $6
           (i64.shr_u
            (get_local $6)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$9
        (i32.lt_s
         (tee_local $7
          (i32.add
           (get_local $7)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $9
      (i32.const 1)
     )
     (br_if $label$7
      (i32.lt_s
       (tee_local $7
        (i32.add
         (get_local $7)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$5)
    )
   )
   (set_local $9
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $9)
   (i32.const 2416)
  )
  (i64.store offset=120
   (get_local $10)
   (i64.shr_u
    (i64.load offset=8
     (get_local $1)
    )
    (i64.const 8)
   )
  )
  (set_local $6
   (i64.load
    (get_local $0)
   )
  )
  (set_local $7
   (call $_ZN5eosio14exchange_stateC2Ev
    (i32.add
     (get_local $10)
     (i32.const 128)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 376)
   )
   (i64.const -1)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 384)
   )
   (i64.const 0)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 392)
   )
   (i32.const 0)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 368)
   )
   (tee_local $3
    (i64.load offset=120
     (get_local $10)
    )
   )
  )
  (i64.store offset=360
   (get_local $10)
   (get_local $6)
  )
  (i64.store offset=400
   (get_local $10)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 408)
   )
   (tee_local $5
    (i64.or
     (tee_local $4
      (i64.shl
       (get_local $3)
       (i64.const 4)
      )
     )
     (i64.const 1)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 416)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 424)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 428)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 432)
   )
   (i32.const 0)
  )
  (i32.store8
   (i32.add
    (get_local $10)
    (i32.const 436)
   )
   (i32.const 0)
  )
  (i64.store offset=440
   (get_local $10)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 448)
   )
   (tee_local $4
    (i64.or
     (get_local $4)
     (i64.const 2)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 456)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 464)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 468)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 472)
   )
   (i32.const 0)
  )
  (i32.store8
   (i32.add
    (get_local $10)
    (i32.const 476)
   )
   (i32.const 0)
  )
  (i64.store offset=480
   (get_local $10)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 488)
   )
   (get_local $5)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 496)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 504)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 508)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 512)
   )
   (i32.const 0)
  )
  (i64.store offset=520
   (get_local $10)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 528)
   )
   (get_local $4)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 536)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 544)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 548)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $10)
    (i32.const 552)
   )
   (i32.const 0)
  )
  (i32.store offset=560
   (get_local $10)
   (tee_local $8
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
   )
  )
  (call $_ZNK5eosio11multi_indexILy10497615196363685888ENS_14exchange_stateEJEE4findEy
   (i32.add
    (get_local $10)
    (i32.const 564)
   )
   (i32.add
    (get_local $10)
    (i32.const 360)
   )
   (get_local $3)
  )
  (call $eosio_assert
   (i32.ne
    (i32.load
     (tee_local $9
      (i32.add
       (get_local $10)
       (i32.const 568)
      )
     )
    )
    (i32.const 0)
   )
   (i32.const 720)
  )
  (drop
   (call $memcpy
    (get_local $7)
    (i32.load
     (get_local $9)
    )
    (i32.const 232)
   )
  )
  (call $eosio_assert
   (i64.ne
    (i64.or
     (i64.load
      (get_local $2)
     )
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 16)
      )
     )
    )
    (i64.const 0)
   )
   (i32.const 2448)
  )
  (call $eosio_assert
   (i32.or
    (i64.ne
     (i64.load
      (tee_local $7
       (i32.add
        (get_local $1)
        (i32.const 24)
       )
      )
     )
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 48)
      )
     )
    )
    (i64.ne
     (i64.load
      (tee_local $9
       (i32.add
        (get_local $1)
        (i32.const 32)
       )
      )
     )
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 56)
      )
     )
    )
   )
   (i32.const 2464)
  )
  (set_local $6
   (i64.load
    (get_local $9)
   )
  )
  (block $label$10
   (block $label$11
    (br_if $label$11
     (i64.ne
      (i64.load
       (i32.add
        (i32.add
         (get_local $10)
         (i32.const 120)
        )
        (i32.const 56)
       )
      )
      (tee_local $3
       (i64.load
        (get_local $7)
       )
      )
     )
    )
    (br_if $label$11
     (i64.ne
      (i64.load
       (i32.add
        (get_local $10)
        (i32.const 184)
       )
      )
      (get_local $6)
     )
    )
    (call $eosio_assert
     (i32.const 1)
     (i32.const 2480)
    )
    (br $label$10)
   )
   (call $eosio_assert
    (i32.and
     (i64.eq
      (i64.load
       (i32.add
        (get_local $10)
        (i32.const 272)
       )
      )
      (get_local $3)
     )
     (i64.eq
      (i64.load
       (i32.add
        (get_local $10)
        (i32.const 280)
       )
      )
      (get_local $6)
     )
    )
    (i32.const 2480)
   )
  )
  (set_local $6
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 56)
    )
   )
  )
  (block $label$12
   (block $label$13
    (br_if $label$13
     (i64.ne
      (i64.load
       (i32.add
        (i32.add
         (get_local $10)
         (i32.const 120)
        )
        (i32.const 56)
       )
      )
      (tee_local $3
       (i64.load
        (i32.add
         (get_local $1)
         (i32.const 48)
        )
       )
      )
     )
    )
    (br_if $label$13
     (i64.ne
      (i64.load
       (i32.add
        (get_local $10)
        (i32.const 184)
       )
      )
      (get_local $6)
     )
    )
    (call $eosio_assert
     (i32.const 1)
     (i32.const 2480)
    )
    (br $label$12)
   )
   (call $eosio_assert
    (i32.and
     (i64.eq
      (i64.load
       (i32.add
        (get_local $10)
        (i32.const 272)
       )
      )
      (get_local $3)
     )
     (i64.eq
      (i64.load
       (i32.add
        (get_local $10)
        (i32.const 280)
       )
      )
      (get_local $6)
     )
    )
    (i32.const 2480)
   )
  )
  (set_local $7
   (i32.add
    (get_local $1)
    (i32.const 16)
   )
  )
  (set_local $6
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
   )
  )
  (set_local $3
   (i64.load
    (get_local $1)
   )
  )
  (block $label$14
   (block $label$15
    (br_if $label$15
     (i64.ne
      (tee_local $4
       (i64.load
        (i32.add
         (get_local $1)
         (i32.const 24)
        )
       )
      )
      (i64.load
       (i32.add
        (get_local $10)
        (i32.const 176)
       )
      )
     )
    )
    (br_if $label$15
     (i64.ne
      (get_local $6)
      (i64.load
       (i32.add
        (get_local $10)
        (i32.const 184)
       )
      )
     )
    )
    (call $_ZN5eosio12market_state13adjust_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetESG_
     (i32.add
      (get_local $10)
      (i32.const 120)
     )
     (get_local $3)
     (i32.add
      (get_local $10)
      (i32.const 400)
     )
     (i32.add
      (get_local $10)
      (i32.const 168)
     )
     (get_local $7)
     (get_local $2)
    )
    (br $label$14)
   )
   (block $label$16
    (br_if $label$16
     (i64.ne
      (get_local $4)
      (i64.load
       (i32.add
        (get_local $10)
        (i32.const 272)
       )
      )
     )
    )
    (br_if $label$16
     (i64.ne
      (get_local $6)
      (i64.load
       (i32.add
        (get_local $10)
        (i32.const 280)
       )
      )
     )
    )
    (call $_ZN5eosio12market_state13adjust_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetESG_
     (i32.add
      (get_local $10)
      (i32.const 120)
     )
     (get_local $3)
     (i32.add
      (get_local $10)
      (i32.const 440)
     )
     (i32.add
      (get_local $10)
      (i32.const 264)
     )
     (get_local $7)
     (get_local $2)
    )
    (br $label$14)
   )
   (call $eosio_assert
    (i32.const 0)
    (i32.const 1376)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 96)
    )
    (i32.const 20)
   )
   (i32.load
    (i32.add
     (get_local $7)
     (i32.const 20)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 96)
    )
    (i32.const 16)
   )
   (i32.load
    (i32.add
     (get_local $7)
     (i32.const 16)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 96)
    )
    (i32.const 12)
   )
   (i32.load
    (i32.add
     (get_local $7)
     (i32.const 12)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 96)
    )
    (i32.const 8)
   )
   (i32.load
    (i32.add
     (get_local $7)
     (i32.const 8)
    )
   )
  )
  (i32.store offset=96
   (get_local $10)
   (i32.load
    (get_local $7)
   )
  )
  (i32.store offset=100
   (get_local $10)
   (i32.load
    (i32.add
     (get_local $7)
     (i32.const 4)
    )
   )
  )
  (set_local $6
   (i64.load
    (get_local $1)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 80)
    )
    (i32.const 8)
   )
   (i32.const 0)
  )
  (i64.store offset=80
   (get_local $10)
   (i64.const 0)
  )
  (block $label$17
   (block $label$18
    (br_if $label$18
     (i32.ge_u
      (tee_local $7
       (call $strlen
        (i32.const 2512)
       )
      )
      (i32.const -16)
     )
    )
    (block $label$19
     (block $label$20
      (block $label$21
       (br_if $label$21
        (i32.ge_u
         (get_local $7)
         (i32.const 11)
        )
       )
       (i32.store8 offset=80
        (get_local $10)
        (i32.shl
         (get_local $7)
         (i32.const 1)
        )
       )
       (set_local $9
        (i32.or
         (i32.add
          (get_local $10)
          (i32.const 80)
         )
         (i32.const 1)
        )
       )
       (br_if $label$20
        (get_local $7)
       )
       (br $label$19)
      )
      (set_local $9
       (call $_Znwj
        (tee_local $0
         (i32.and
          (i32.add
           (get_local $7)
           (i32.const 16)
          )
          (i32.const -16)
         )
        )
       )
      )
      (i32.store offset=80
       (get_local $10)
       (i32.or
        (get_local $0)
        (i32.const 1)
       )
      )
      (i32.store offset=88
       (get_local $10)
       (get_local $9)
      )
      (i32.store offset=84
       (get_local $10)
       (get_local $7)
      )
     )
     (drop
      (call $memcpy
       (get_local $9)
       (i32.const 2512)
       (get_local $7)
      )
     )
    )
    (i32.store8
     (i32.add
      (get_local $9)
      (get_local $7)
     )
     (i32.const 0)
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $10)
       (i32.const 32)
      )
      (i32.const 16)
     )
     (i64.load
      (i32.add
       (i32.add
        (get_local $10)
        (i32.const 96)
       )
       (i32.const 16)
      )
     )
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $10)
       (i32.const 32)
      )
      (i32.const 8)
     )
     (i64.load
      (i32.add
       (i32.add
        (get_local $10)
        (i32.const 96)
       )
       (i32.const 8)
      )
     )
    )
    (i64.store offset=32
     (get_local $10)
     (i64.load offset=96
      (get_local $10)
     )
    )
    (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
     (get_local $8)
     (get_local $6)
     (i32.add
      (get_local $10)
      (i32.const 32)
     )
     (get_local $10)
    )
    (block $label$22
     (br_if $label$22
      (i32.eqz
       (i32.and
        (i32.load8_u offset=80
         (get_local $10)
        )
        (i32.const 1)
       )
      )
     )
     (call $_ZdlPv
      (i32.load offset=88
       (get_local $10)
      )
     )
    )
    (i64.store offset=64
     (get_local $10)
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 48)
      )
     )
    )
    (i64.store offset=56
     (get_local $10)
     (i64.sub
      (i64.const 0)
      (i64.load
       (i32.add
        (get_local $1)
        (i32.const 40)
       )
      )
     )
    )
    (set_local $6
     (i64.load
      (get_local $1)
     )
    )
    (i64.store offset=72
     (get_local $10)
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 56)
      )
     )
    )
    (i32.store
     (i32.add
      (i32.add
       (get_local $10)
       (i32.const 80)
      )
      (i32.const 8)
     )
     (i32.const 0)
    )
    (i64.store offset=80
     (get_local $10)
     (i64.const 0)
    )
    (br_if $label$17
     (i32.ge_u
      (tee_local $7
       (call $strlen
        (i32.const 2528)
       )
      )
      (i32.const -16)
     )
    )
    (block $label$23
     (block $label$24
      (block $label$25
       (br_if $label$25
        (i32.ge_u
         (get_local $7)
         (i32.const 11)
        )
       )
       (i32.store8 offset=80
        (get_local $10)
        (i32.shl
         (get_local $7)
         (i32.const 1)
        )
       )
       (set_local $1
        (i32.or
         (i32.add
          (get_local $10)
          (i32.const 80)
         )
         (i32.const 1)
        )
       )
       (br_if $label$24
        (get_local $7)
       )
       (br $label$23)
      )
      (set_local $1
       (call $_Znwj
        (tee_local $9
         (i32.and
          (i32.add
           (get_local $7)
           (i32.const 16)
          )
          (i32.const -16)
         )
        )
       )
      )
      (i32.store offset=80
       (get_local $10)
       (i32.or
        (get_local $9)
        (i32.const 1)
       )
      )
      (i32.store offset=88
       (get_local $10)
       (get_local $1)
      )
      (i32.store offset=84
       (get_local $10)
       (get_local $7)
      )
     )
     (drop
      (call $memcpy
       (get_local $1)
       (i32.const 2528)
       (get_local $7)
      )
     )
    )
    (i32.store8
     (i32.add
      (get_local $1)
      (get_local $7)
     )
     (i32.const 0)
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $10)
       (i32.const 8)
      )
      (i32.const 16)
     )
     (i64.load
      (i32.add
       (i32.add
        (get_local $10)
        (i32.const 56)
       )
       (i32.const 16)
      )
     )
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $10)
       (i32.const 8)
      )
      (i32.const 8)
     )
     (i64.load
      (i32.add
       (i32.add
        (get_local $10)
        (i32.const 56)
       )
       (i32.const 8)
      )
     )
    )
    (i64.store offset=8
     (get_local $10)
     (i64.load offset=56
      (get_local $10)
     )
    )
    (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
     (get_local $8)
     (get_local $6)
     (i32.add
      (get_local $10)
      (i32.const 8)
     )
     (get_local $10)
    )
    (block $label$26
     (br_if $label$26
      (i32.eqz
       (i32.and
        (i32.load8_u offset=80
         (get_local $10)
        )
        (i32.const 1)
       )
      )
     )
     (call $_ZdlPv
      (i32.load offset=88
       (get_local $10)
      )
     )
    )
    (call $_ZN5eosio12market_state4saveEv
     (i32.add
      (get_local $10)
      (i32.const 120)
     )
    )
    (drop
     (call $_ZN5eosio12market_stateD2Ev
      (i32.add
       (get_local $10)
       (i32.const 120)
      )
     )
    )
    (i32.store offset=4
     (i32.const 0)
     (i32.add
      (get_local $10)
      (i32.const 576)
     )
    )
    (return)
   )
   (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
    (i32.add
     (get_local $10)
     (i32.const 80)
    )
   )
   (unreachable)
  )
  (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
   (i32.add
    (get_local $10)
    (i32.const 80)
   )
  )
  (unreachable)
 )
 (func $_ZN5eosio8exchange2onERKNS0_11covermarginE (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i64)
  (local $5 i64)
  (local $6 i64)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 464)
    )
   )
  )
  (call $require_auth
   (i64.load
    (get_local $1)
   )
  )
  (set_local $2
   (i32.add
    (get_local $1)
    (i32.const 16)
   )
  )
  (set_local $8
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i64.gt_u
     (i64.add
      (i64.load offset=16
       (get_local $1)
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $6
    (i64.shr_u
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 24)
      )
     )
     (i64.const 8)
    )
   )
   (set_local $7
    (i32.const 0)
   )
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $6)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $6
          (i64.shr_u
           (get_local $6)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $6
           (i64.shr_u
            (get_local $6)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $7
          (i32.add
           (get_local $7)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $8
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $7
        (i32.add
         (get_local $7)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $8
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $8)
   (i32.const 2544)
  )
  (call $eosio_assert
   (i64.gt_s
    (i64.load
     (get_local $2)
    )
    (i64.const 0)
   )
   (i32.const 2576)
  )
  (i64.store offset=8
   (get_local $9)
   (i64.shr_u
    (i64.load offset=8
     (get_local $1)
    )
    (i64.const 8)
   )
  )
  (set_local $6
   (i64.load
    (get_local $0)
   )
  )
  (set_local $7
   (call $_ZN5eosio14exchange_stateC2Ev
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 264)
   )
   (i64.const -1)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 272)
   )
   (i64.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 280)
   )
   (i32.const 0)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 256)
   )
   (tee_local $3
    (i64.load offset=8
     (get_local $9)
    )
   )
  )
  (i64.store offset=248
   (get_local $9)
   (get_local $6)
  )
  (i64.store offset=288
   (get_local $9)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 296)
   )
   (tee_local $5
    (i64.or
     (tee_local $4
      (i64.shl
       (get_local $3)
       (i64.const 4)
      )
     )
     (i64.const 1)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 304)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 312)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 316)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 320)
   )
   (i32.const 0)
  )
  (i32.store8
   (i32.add
    (get_local $9)
    (i32.const 324)
   )
   (i32.const 0)
  )
  (i64.store offset=328
   (get_local $9)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 336)
   )
   (tee_local $4
    (i64.or
     (get_local $4)
     (i64.const 2)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 344)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 352)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 356)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 360)
   )
   (i32.const 0)
  )
  (i32.store8
   (i32.add
    (get_local $9)
    (i32.const 364)
   )
   (i32.const 0)
  )
  (i64.store offset=368
   (get_local $9)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 376)
   )
   (get_local $5)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 384)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 392)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 396)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 400)
   )
   (i32.const 0)
  )
  (i64.store offset=408
   (get_local $9)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 416)
   )
   (get_local $4)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 424)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 432)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 436)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 440)
   )
   (i32.const 0)
  )
  (i32.store offset=448
   (get_local $9)
   (i32.add
    (get_local $0)
    (i32.const 16)
   )
  )
  (call $_ZNK5eosio11multi_indexILy10497615196363685888ENS_14exchange_stateEJEE4findEy
   (i32.add
    (get_local $9)
    (i32.const 452)
   )
   (i32.add
    (get_local $9)
    (i32.const 248)
   )
   (get_local $3)
  )
  (call $eosio_assert
   (i32.ne
    (i32.load
     (tee_local $8
      (i32.add
       (get_local $9)
       (i32.const 456)
      )
     )
    )
    (i32.const 0)
   )
   (i32.const 720)
  )
  (drop
   (call $memcpy
    (get_local $7)
    (i32.load
     (get_local $8)
    )
    (i32.const 232)
   )
  )
  (set_local $6
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
   )
  )
  (set_local $3
   (i64.load
    (get_local $1)
   )
  )
  (block $label$5
   (block $label$6
    (br_if $label$6
     (i64.ne
      (tee_local $4
       (i64.load
        (i32.add
         (get_local $1)
         (i32.const 24)
        )
       )
      )
      (i64.load
       (i32.add
        (get_local $9)
        (i32.const 64)
       )
      )
     )
    )
    (br_if $label$6
     (i64.ne
      (get_local $6)
      (i64.load
       (i32.add
        (get_local $9)
        (i32.const 72)
       )
      )
     )
    )
    (call $_ZN5eosio12market_state12cover_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetE
     (i32.add
      (get_local $9)
      (i32.const 8)
     )
     (get_local $3)
     (i32.add
      (get_local $9)
      (i32.const 288)
     )
     (i32.add
      (get_local $9)
      (i32.const 56)
     )
     (get_local $2)
    )
    (br $label$5)
   )
   (block $label$7
    (br_if $label$7
     (i64.ne
      (get_local $4)
      (i64.load
       (i32.add
        (get_local $9)
        (i32.const 160)
       )
      )
     )
    )
    (br_if $label$7
     (i64.ne
      (get_local $6)
      (i64.load
       (i32.add
        (get_local $9)
        (i32.const 168)
       )
      )
     )
    )
    (call $_ZN5eosio12market_state12cover_marginEyRNS_11multi_indexILy10497546923563548672ENS_15margin_positionEJNS_10indexed_byILy4729653573519933440EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_8get_callEvEEEEEEEEERNS_14exchange_state9connectorERKNS_14extended_assetE
     (i32.add
      (get_local $9)
      (i32.const 8)
     )
     (get_local $3)
     (i32.add
      (get_local $9)
      (i32.const 328)
     )
     (i32.add
      (get_local $9)
      (i32.const 152)
     )
     (get_local $2)
    )
    (br $label$5)
   )
   (call $eosio_assert
    (i32.const 0)
    (i32.const 1376)
   )
  )
  (call $_ZN5eosio12market_state4saveEv
   (i32.add
    (get_local $9)
    (i32.const 8)
   )
  )
  (drop
   (call $_ZN5eosio12market_stateD2Ev
    (i32.add
     (get_local $9)
     (i32.const 8)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 464)
   )
  )
 )
 (func $_ZN5eosio8exchange7createxEyNS_5assetEmNS_14extended_assetES2_ (type $FUNCSIG$vijiiii) (param $0 i32) (param $1 i64) (param $2 i32) (param $3 i32) (param $4 i32) (param $5 i32)
  (local $6 i64)
  (local $7 i64)
  (local $8 i64)
  (local $9 i64)
  (local $10 i64)
  (local $11 i64)
  (local $12 i32)
  (local $13 i32)
  (local $14 i64)
  (local $15 i32)
  (local $16 i32)
  (local $17 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $17
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 464)
    )
   )
  )
  (call $require_auth
   (get_local $1)
  )
  (set_local $16
   (i32.const 0)
  )
  (set_local $13
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i64.gt_u
     (i64.add
      (tee_local $6
       (i64.load
        (get_local $2)
       )
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $14
    (i64.shr_u
     (i64.load offset=8
      (get_local $2)
     )
     (i64.const 8)
    )
   )
   (set_local $15
    (i32.const 0)
   )
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $14)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $14
          (i64.shr_u
           (get_local $14)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $14
           (i64.shr_u
            (get_local $14)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $15
          (i32.add
           (get_local $15)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $13
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $15
        (i32.add
         (get_local $15)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $13
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $13)
   (i32.const 2608)
  )
  (call $eosio_assert
   (i64.gt_s
    (get_local $6)
    (i64.const 0)
   )
   (i32.const 2640)
  )
  (block $label$5
   (br_if $label$5
    (i64.gt_u
     (i64.add
      (tee_local $6
       (i64.load
        (get_local $4)
       )
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $14
    (i64.shr_u
     (i64.load offset=8
      (get_local $4)
     )
     (i64.const 8)
    )
   )
   (set_local $15
    (i32.const 0)
   )
   (block $label$6
    (loop $label$7
     (br_if $label$6
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $14)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$8
      (br_if $label$8
       (i64.ne
        (i64.and
         (tee_local $14
          (i64.shr_u
           (get_local $14)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$9
       (br_if $label$6
        (i64.ne
         (i64.and
          (tee_local $14
           (i64.shr_u
            (get_local $14)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$9
        (i32.lt_s
         (tee_local $15
          (i32.add
           (get_local $15)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $16
      (i32.const 1)
     )
     (br_if $label$7
      (i32.lt_s
       (tee_local $15
        (i32.add
         (get_local $15)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$5)
    )
   )
   (set_local $16
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $16)
   (i32.const 2672)
  )
  (call $eosio_assert
   (i64.gt_s
    (get_local $6)
    (i64.const 0)
   )
   (i32.const 2704)
  )
  (set_local $6
   (i64.load offset=8
    (get_local $5)
   )
  )
  (set_local $13
   (i32.const 0)
  )
  (set_local $16
   (i32.const 0)
  )
  (block $label$10
   (br_if $label$10
    (i64.gt_u
     (i64.add
      (tee_local $7
       (i64.load
        (get_local $5)
       )
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $14
    (i64.shr_u
     (get_local $6)
     (i64.const 8)
    )
   )
   (set_local $15
    (i32.const 0)
   )
   (block $label$11
    (loop $label$12
     (br_if $label$11
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $14)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$13
      (br_if $label$13
       (i64.ne
        (i64.and
         (tee_local $14
          (i64.shr_u
           (get_local $14)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$14
       (br_if $label$11
        (i64.ne
         (i64.and
          (tee_local $14
           (i64.shr_u
            (get_local $14)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$14
        (i32.lt_s
         (tee_local $15
          (i32.add
           (get_local $15)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $16
      (i32.const 1)
     )
     (br_if $label$12
      (i32.lt_s
       (tee_local $15
        (i32.add
         (get_local $15)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$10)
    )
   )
   (set_local $16
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $16)
   (i32.const 2736)
  )
  (call $eosio_assert
   (i64.gt_s
    (get_local $7)
    (i64.const 0)
   )
   (i32.const 2768)
  )
  (call $eosio_assert
   (i32.or
    (i64.ne
     (tee_local $14
      (i64.load offset=8
       (get_local $4)
      )
     )
     (get_local $6)
    )
    (i64.ne
     (tee_local $7
      (i64.load offset=16
       (get_local $4)
      )
     )
     (tee_local $8
      (i64.load offset=16
       (get_local $5)
      )
     )
    )
   )
   (i32.const 2800)
  )
  (i64.store offset=216
   (get_local $17)
   (get_local $7)
  )
  (i64.store offset=208
   (get_local $17)
   (get_local $14)
  )
  (call $prints
   (i32.const 2848)
  )
  (call $_ZNK5eosio11symbol_type5printEb
   (i32.add
    (get_local $17)
    (i32.const 208)
   )
   (i32.const 1)
  )
  (call $prints
   (i32.const 1280)
  )
  (call $printn
   (i64.load offset=216
    (get_local $17)
   )
  )
  (i64.store offset=216
   (get_local $17)
   (get_local $8)
  )
  (i64.store offset=208
   (get_local $17)
   (get_local $6)
  )
  (call $prints
   (i32.const 2864)
  )
  (call $_ZNK5eosio11symbol_type5printEb
   (i32.add
    (get_local $17)
    (i32.const 208)
   )
   (i32.const 1)
  )
  (call $prints
   (i32.const 1280)
  )
  (call $printn
   (i64.load offset=216
    (get_local $17)
   )
  )
  (set_local $9
   (i64.load offset=8
    (get_local $2)
   )
  )
  (call $prints
   (i32.const 2880)
  )
  (call $printui
   (tee_local $10
    (i64.shr_u
     (get_local $9)
     (i64.const 8)
    )
   )
  )
  (call $prints
   (i32.const 2896)
  )
  (i32.store
   (i32.add
    (get_local $17)
    (i32.const 200)
   )
   (i32.const 0)
  )
  (i64.store offset=176
   (get_local $17)
   (get_local $10)
  )
  (i64.store offset=184
   (get_local $17)
   (i64.const -1)
  )
  (i64.store offset=192
   (get_local $17)
   (i64.const 0)
  )
  (i64.store offset=168
   (get_local $17)
   (tee_local $11
    (i64.load
     (get_local $0)
    )
   )
  )
  (block $label$15
   (br_if $label$15
    (i32.lt_s
     (tee_local $15
      (call $db_find_i64
       (get_local $11)
       (get_local $10)
       (i64.const -7949128877345865728)
       (get_local $10)
      )
     )
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=232
      (tee_local $13
       (call $_ZNK5eosio11multi_indexILy10497615196363685888ENS_14exchange_stateEJEE31load_object_by_primary_iteratorEl
        (i32.add
         (get_local $17)
         (i32.const 168)
        )
        (get_local $15)
       )
      )
     )
     (i32.add
      (get_local $17)
      (i32.const 168)
     )
    )
    (i32.const 224)
   )
  )
  (call $eosio_assert
   (i32.eqz
    (get_local $13)
   )
   (i32.const 2912)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load offset=168
     (get_local $17)
    )
    (call $current_receiver)
   )
   (i32.const 288)
  )
  (set_local $16
   (call $_ZN5eosio14exchange_stateC2Ev
    (tee_local $15
     (call $_Znwj
      (i32.const 248)
     )
    )
   )
  )
  (i32.store offset=232
   (get_local $15)
   (i32.add
    (get_local $17)
    (i32.const 168)
   )
  )
  (i64.store
   (get_local $15)
   (get_local $1)
  )
  (i64.store
   (tee_local $13
    (i32.add
     (i32.add
      (get_local $17)
      (i32.const 432)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=432
   (get_local $17)
   (i64.load
    (get_local $2)
   )
  )
  (set_local $10
   (i64.load
    (get_local $0)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $17)
     (i32.const 208)
    )
    (i32.const 8)
   )
   (tee_local $11
    (i64.load
     (get_local $13)
    )
   )
  )
  (i64.store
   (tee_local $13
    (i32.add
     (i32.add
      (get_local $17)
      (i32.const 448)
     )
     (i32.const 8)
    )
   )
   (get_local $11)
  )
  (i64.store offset=208
   (get_local $17)
   (tee_local $11
    (i64.load offset=432
     (get_local $17)
    )
   )
  )
  (i64.store offset=448
   (get_local $17)
   (get_local $11)
  )
  (i64.store offset=24
   (get_local $15)
   (get_local $10)
  )
  (i64.store offset=16
   (get_local $15)
   (i64.load
    (get_local $13)
   )
  )
  (i64.store offset=8
   (get_local $15)
   (i64.load offset=448
    (get_local $17)
   )
  )
  (i64.store
   (i32.add
    (get_local $15)
    (i32.const 56)
   )
   (i64.load
    (i32.add
     (get_local $4)
     (i32.const 16)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $15)
    (i32.const 48)
   )
   (i64.load
    (i32.add
     (get_local $4)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=40
   (get_local $15)
   (i64.load
    (get_local $4)
   )
  )
  (i64.store
   (i32.add
    (get_local $15)
    (i32.const 152)
   )
   (i64.load
    (i32.add
     (get_local $5)
     (i32.const 16)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $15)
    (i32.const 144)
   )
   (i64.load
    (i32.add
     (get_local $5)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=136
   (get_local $15)
   (i64.load
    (get_local $5)
   )
  )
  (i64.store offset=104
   (get_local $15)
   (get_local $14)
  )
  (i64.store offset=112
   (get_local $15)
   (get_local $7)
  )
  (i64.store offset=80
   (get_local $15)
   (get_local $14)
  )
  (i64.store offset=88
   (get_local $15)
   (get_local $7)
  )
  (i64.store offset=200
   (get_local $15)
   (get_local $6)
  )
  (i64.store offset=208
   (get_local $15)
   (get_local $8)
  )
  (i64.store offset=176
   (get_local $15)
   (get_local $6)
  )
  (i64.store offset=184
   (get_local $15)
   (get_local $8)
  )
  (i32.store offset=456
   (get_local $17)
   (i32.add
    (i32.add
     (get_local $17)
     (i32.const 208)
    )
    (i32.const 220)
   )
  )
  (i32.store offset=452
   (get_local $17)
   (i32.add
    (get_local $17)
    (i32.const 208)
   )
  )
  (i32.store offset=448
   (get_local $17)
   (i32.add
    (get_local $17)
    (i32.const 208)
   )
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_14exchange_stateE
    (i32.add
     (get_local $17)
     (i32.const 448)
    )
    (get_local $16)
   )
  )
  (i32.store offset=236
   (get_local $15)
   (tee_local $13
    (call $db_store_i64
     (i64.load
      (i32.add
       (i32.add
        (get_local $17)
        (i32.const 168)
       )
       (i32.const 8)
      )
     )
     (i64.const -7949128877345865728)
     (get_local $1)
     (tee_local $14
      (i64.shr_u
       (i64.load offset=16
        (get_local $15)
       )
       (i64.const 8)
      )
     )
     (i32.add
      (get_local $17)
      (i32.const 208)
     )
     (i32.const 220)
    )
   )
  )
  (block $label$16
   (br_if $label$16
    (i64.lt_u
     (get_local $14)
     (i64.load
      (tee_local $16
       (i32.add
        (i32.add
         (get_local $17)
         (i32.const 168)
        )
        (i32.const 16)
       )
      )
     )
    )
   )
   (i64.store
    (get_local $16)
    (i64.add
     (get_local $14)
     (i64.const 1)
    )
   )
  )
  (i32.store offset=448
   (get_local $17)
   (get_local $15)
  )
  (i64.store offset=208
   (get_local $17)
   (tee_local $14
    (i64.shr_u
     (i64.load
      (i32.add
       (get_local $15)
       (i32.const 16)
      )
     )
     (i64.const 8)
    )
   )
  )
  (i32.store offset=432
   (get_local $17)
   (get_local $13)
  )
  (block $label$17
   (block $label$18
    (br_if $label$18
     (i32.ge_u
      (tee_local $16
       (i32.load
        (tee_local $12
         (i32.add
          (get_local $17)
          (i32.const 196)
         )
        )
       )
      )
      (i32.load
       (i32.add
        (get_local $17)
        (i32.const 200)
       )
      )
     )
    )
    (i64.store offset=8
     (get_local $16)
     (get_local $14)
    )
    (i32.store offset=16
     (get_local $16)
     (get_local $13)
    )
    (i32.store offset=448
     (get_local $17)
     (i32.const 0)
    )
    (i32.store
     (get_local $16)
     (get_local $15)
    )
    (i32.store
     (get_local $12)
     (i32.add
      (get_local $16)
      (i32.const 24)
     )
    )
    (br $label$17)
   )
   (call $_ZNSt3__16vectorIN5eosio11multi_indexILy10497615196363685888ENS1_14exchange_stateEJEE8item_ptrENS_9allocatorIS5_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS4_4itemENS_14default_deleteISB_EEEERyRlEEEvDpOT_
    (i32.add
     (get_local $17)
     (i32.const 192)
    )
    (i32.add
     (get_local $17)
     (i32.const 448)
    )
    (i32.add
     (get_local $17)
     (i32.const 208)
    )
    (i32.add
     (get_local $17)
     (i32.const 432)
    )
   )
  )
  (set_local $16
   (i32.load offset=448
    (get_local $17)
   )
  )
  (set_local $15
   (i32.const 0)
  )
  (i32.store offset=448
   (get_local $17)
   (i32.const 0)
  )
  (block $label$19
   (br_if $label$19
    (i32.eqz
     (get_local $16)
    )
   )
   (call $_ZdlPv
    (get_local $16)
   )
  )
  (i64.store
   (tee_local $16
    (i32.add
     (get_local $17)
     (i32.const 224)
    )
   )
   (get_local $9)
  )
  (i64.store offset=216
   (get_local $17)
   (i64.const 0)
  )
  (i64.store offset=208
   (get_local $17)
   (i64.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $13
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (set_local $14
   (i64.shr_u
    (i64.load
     (get_local $16)
    )
    (i64.const 8)
   )
  )
  (block $label$20
   (block $label$21
    (loop $label$22
     (br_if $label$21
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $14)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$23
      (br_if $label$23
       (i64.ne
        (i64.and
         (tee_local $14
          (i64.shr_u
           (get_local $14)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$24
       (br_if $label$21
        (i64.ne
         (i64.and
          (tee_local $14
           (i64.shr_u
            (get_local $14)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$24
        (i32.lt_s
         (tee_local $15
          (i32.add
           (get_local $15)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $16
      (i32.const 1)
     )
     (br_if $label$22
      (i32.lt_s
       (tee_local $15
        (i32.add
         (get_local $15)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$20)
    )
   )
   (set_local $16
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $16)
   (i32.const 80)
  )
  (i32.store8 offset=234
   (get_local $17)
   (i32.const 0)
  )
  (i32.store16 offset=232
   (get_local $17)
   (i32.const 0)
  )
  (call $_ZN5eosio8currency15create_currencyERKNS0_6createE
   (get_local $13)
   (i32.add
    (get_local $17)
    (i32.const 208)
   )
  )
  (i32.store
   (i32.add
    (get_local $17)
    (i32.const 228)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 12)
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $17)
    (i32.const 224)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $17)
     (i32.const 208)
    )
    (i32.const 12)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 4)
    )
   )
  )
  (i64.store offset=208
   (get_local $17)
   (i64.load
    (get_local $0)
   )
  )
  (i32.store offset=216
   (get_local $17)
   (i32.load
    (get_local $2)
   )
  )
  (i32.store
   (i32.add
    (get_local $17)
    (i32.const 240)
   )
   (i32.const 0)
  )
  (i64.store offset=232
   (get_local $17)
   (i64.const 0)
  )
  (set_local $16
   (i32.add
    (get_local $17)
    (i32.const 232)
   )
  )
  (block $label$25
   (block $label$26
    (block $label$27
     (block $label$28
      (br_if $label$28
       (i32.ge_u
        (tee_local $15
         (call $strlen
          (i32.const 2944)
         )
        )
        (i32.const -16)
       )
      )
      (block $label$29
       (block $label$30
        (block $label$31
         (br_if $label$31
          (i32.ge_u
           (get_local $15)
           (i32.const 11)
          )
         )
         (i32.store8
          (i32.add
           (get_local $17)
           (i32.const 232)
          )
          (i32.shl
           (get_local $15)
           (i32.const 1)
          )
         )
         (set_local $16
          (i32.add
           (get_local $16)
           (i32.const 1)
          )
         )
         (br_if $label$30
          (get_local $15)
         )
         (br $label$29)
        )
        (set_local $16
         (call $_Znwj
          (tee_local $12
           (i32.and
            (i32.add
             (get_local $15)
             (i32.const 16)
            )
            (i32.const -16)
           )
          )
         )
        )
        (i32.store
         (i32.add
          (get_local $17)
          (i32.const 232)
         )
         (i32.or
          (get_local $12)
          (i32.const 1)
         )
        )
        (i32.store
         (i32.add
          (get_local $17)
          (i32.const 240)
         )
         (get_local $16)
        )
        (i32.store
         (i32.add
          (get_local $17)
          (i32.const 236)
         )
         (get_local $15)
        )
       )
       (drop
        (call $memcpy
         (get_local $16)
         (i32.const 2944)
         (get_local $15)
        )
       )
      )
      (i32.store8
       (i32.add
        (get_local $16)
        (get_local $15)
       )
       (i32.const 0)
      )
      (call $_ZN5eosio8currency14issue_currencyERKNS0_5issueE
       (get_local $13)
       (i32.add
        (get_local $17)
        (i32.const 208)
       )
      )
      (block $label$32
       (br_if $label$32
        (i32.eqz
         (i32.and
          (i32.load8_u
           (i32.add
            (get_local $17)
            (i32.const 232)
           )
          )
          (i32.const 1)
         )
        )
       )
       (call $_ZdlPv
        (i32.load
         (i32.add
          (get_local $17)
          (i32.const 240)
         )
        )
       )
      )
      (i64.store
       (tee_local $15
        (i32.add
         (i32.add
          (get_local $17)
          (i32.const 128)
         )
         (i32.const 8)
        )
       )
       (i64.load
        (i32.add
         (get_local $2)
         (i32.const 8)
        )
       )
      )
      (i64.store offset=128
       (get_local $17)
       (i64.load
        (get_local $2)
       )
      )
      (set_local $14
       (i64.load
        (get_local $0)
       )
      )
      (i64.store
       (tee_local $2
        (i32.add
         (i32.add
          (get_local $17)
          (i32.const 208)
         )
         (i32.const 8)
        )
       )
       (tee_local $6
        (i64.load
         (get_local $15)
        )
       )
      )
      (i64.store
       (i32.add
        (i32.add
         (get_local $17)
         (i32.const 144)
        )
        (i32.const 8)
       )
       (get_local $6)
      )
      (i64.store offset=208
       (get_local $17)
       (tee_local $6
        (i64.load offset=128
         (get_local $17)
        )
       )
      )
      (i64.store offset=144
       (get_local $17)
       (get_local $6)
      )
      (i64.store offset=160
       (get_local $17)
       (get_local $14)
      )
      (i32.store
       (get_local $2)
       (i32.const 0)
      )
      (i64.store offset=208
       (get_local $17)
       (i64.const 0)
      )
      (br_if $label$27
       (i32.ge_u
        (tee_local $15
         (call $strlen
          (i32.const 2976)
         )
        )
        (i32.const -16)
       )
      )
      (set_local $2
       (i32.add
        (get_local $0)
        (i32.const 16)
       )
      )
      (block $label$33
       (block $label$34
        (block $label$35
         (br_if $label$35
          (i32.ge_u
           (get_local $15)
           (i32.const 11)
          )
         )
         (i32.store8 offset=208
          (get_local $17)
          (i32.shl
           (get_local $15)
           (i32.const 1)
          )
         )
         (set_local $0
          (i32.or
           (i32.add
            (get_local $17)
            (i32.const 208)
           )
           (i32.const 1)
          )
         )
         (br_if $label$34
          (get_local $15)
         )
         (br $label$33)
        )
        (set_local $0
         (call $_Znwj
          (tee_local $16
           (i32.and
            (i32.add
             (get_local $15)
             (i32.const 16)
            )
            (i32.const -16)
           )
          )
         )
        )
        (i32.store offset=208
         (get_local $17)
         (i32.or
          (get_local $16)
          (i32.const 1)
         )
        )
        (i32.store offset=216
         (get_local $17)
         (get_local $0)
        )
        (i32.store offset=212
         (get_local $17)
         (get_local $15)
        )
       )
       (drop
        (call $memcpy
         (get_local $0)
         (i32.const 2976)
         (get_local $15)
        )
       )
      )
      (i32.store8
       (i32.add
        (get_local $0)
        (get_local $15)
       )
       (i32.const 0)
      )
      (i64.store
       (i32.add
        (i32.add
         (get_local $17)
         (i32.const 56)
        )
        (i32.const 16)
       )
       (i64.load
        (i32.add
         (i32.add
          (get_local $17)
          (i32.const 144)
         )
         (i32.const 16)
        )
       )
      )
      (i64.store
       (i32.add
        (i32.add
         (get_local $17)
         (i32.const 56)
        )
        (i32.const 8)
       )
       (i64.load
        (i32.add
         (i32.add
          (get_local $17)
          (i32.const 144)
         )
         (i32.const 8)
        )
       )
      )
      (i64.store offset=56
       (get_local $17)
       (i64.load offset=144
        (get_local $17)
       )
      )
      (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
       (get_local $2)
       (get_local $1)
       (i32.add
        (get_local $17)
        (i32.const 56)
       )
       (get_local $17)
      )
      (block $label$36
       (br_if $label$36
        (i32.eqz
         (i32.and
          (i32.load8_u offset=208
           (get_local $17)
          )
          (i32.const 1)
         )
        )
       )
       (call $_ZdlPv
        (i32.load offset=216
         (get_local $17)
        )
       )
      )
      (i64.store offset=104
       (get_local $17)
       (i64.sub
        (i64.const 0)
        (i64.load
         (get_local $4)
        )
       )
      )
      (i64.store offset=112
       (get_local $17)
       (i64.load
        (i32.add
         (get_local $4)
         (i32.const 8)
        )
       )
      )
      (i64.store offset=120
       (get_local $17)
       (i64.load
        (i32.add
         (get_local $4)
         (i32.const 16)
        )
       )
      )
      (i32.store
       (i32.add
        (i32.add
         (get_local $17)
         (i32.const 208)
        )
        (i32.const 8)
       )
       (i32.const 0)
      )
      (i64.store offset=208
       (get_local $17)
       (i64.const 0)
      )
      (br_if $label$26
       (i32.ge_u
        (tee_local $15
         (call $strlen
          (i32.const 3008)
         )
        )
        (i32.const -16)
       )
      )
      (block $label$37
       (block $label$38
        (block $label$39
         (br_if $label$39
          (i32.ge_u
           (get_local $15)
           (i32.const 11)
          )
         )
         (i32.store8 offset=208
          (get_local $17)
          (i32.shl
           (get_local $15)
           (i32.const 1)
          )
         )
         (set_local $4
          (i32.or
           (i32.add
            (get_local $17)
            (i32.const 208)
           )
           (i32.const 1)
          )
         )
         (br_if $label$38
          (get_local $15)
         )
         (br $label$37)
        )
        (set_local $4
         (call $_Znwj
          (tee_local $0
           (i32.and
            (i32.add
             (get_local $15)
             (i32.const 16)
            )
            (i32.const -16)
           )
          )
         )
        )
        (i32.store offset=208
         (get_local $17)
         (i32.or
          (get_local $0)
          (i32.const 1)
         )
        )
        (i32.store offset=216
         (get_local $17)
         (get_local $4)
        )
        (i32.store offset=212
         (get_local $17)
         (get_local $15)
        )
       )
       (drop
        (call $memcpy
         (get_local $4)
         (i32.const 3008)
         (get_local $15)
        )
       )
      )
      (i32.store8
       (i32.add
        (get_local $4)
        (get_local $15)
       )
       (i32.const 0)
      )
      (i64.store
       (i32.add
        (i32.add
         (get_local $17)
         (i32.const 32)
        )
        (i32.const 16)
       )
       (i64.load
        (i32.add
         (i32.add
          (get_local $17)
          (i32.const 104)
         )
         (i32.const 16)
        )
       )
      )
      (i64.store
       (i32.add
        (i32.add
         (get_local $17)
         (i32.const 32)
        )
        (i32.const 8)
       )
       (i64.load
        (i32.add
         (i32.add
          (get_local $17)
          (i32.const 104)
         )
         (i32.const 8)
        )
       )
      )
      (i64.store offset=32
       (get_local $17)
       (i64.load offset=104
        (get_local $17)
       )
      )
      (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
       (get_local $2)
       (get_local $1)
       (i32.add
        (get_local $17)
        (i32.const 32)
       )
       (get_local $17)
      )
      (block $label$40
       (br_if $label$40
        (i32.eqz
         (i32.and
          (i32.load8_u offset=208
           (get_local $17)
          )
          (i32.const 1)
         )
        )
       )
       (call $_ZdlPv
        (i32.load offset=216
         (get_local $17)
        )
       )
      )
      (i64.store offset=80
       (get_local $17)
       (i64.sub
        (i64.const 0)
        (i64.load
         (get_local $5)
        )
       )
      )
      (i64.store offset=88
       (get_local $17)
       (i64.load
        (i32.add
         (get_local $5)
         (i32.const 8)
        )
       )
      )
      (i64.store offset=96
       (get_local $17)
       (i64.load
        (i32.add
         (get_local $5)
         (i32.const 16)
        )
       )
      )
      (i32.store
       (i32.add
        (i32.add
         (get_local $17)
         (i32.const 208)
        )
        (i32.const 8)
       )
       (i32.const 0)
      )
      (i64.store offset=208
       (get_local $17)
       (i64.const 0)
      )
      (br_if $label$25
       (i32.ge_u
        (tee_local $15
         (call $strlen
          (i32.const 3008)
         )
        )
        (i32.const -16)
       )
      )
      (block $label$41
       (block $label$42
        (block $label$43
         (br_if $label$43
          (i32.ge_u
           (get_local $15)
           (i32.const 11)
          )
         )
         (i32.store8 offset=208
          (get_local $17)
          (i32.shl
           (get_local $15)
           (i32.const 1)
          )
         )
         (set_local $4
          (i32.or
           (i32.add
            (get_local $17)
            (i32.const 208)
           )
           (i32.const 1)
          )
         )
         (br_if $label$42
          (get_local $15)
         )
         (br $label$41)
        )
        (set_local $4
         (call $_Znwj
          (tee_local $5
           (i32.and
            (i32.add
             (get_local $15)
             (i32.const 16)
            )
            (i32.const -16)
           )
          )
         )
        )
        (i32.store offset=208
         (get_local $17)
         (i32.or
          (get_local $5)
          (i32.const 1)
         )
        )
        (i32.store offset=216
         (get_local $17)
         (get_local $4)
        )
        (i32.store offset=212
         (get_local $17)
         (get_local $15)
        )
       )
       (drop
        (call $memcpy
         (get_local $4)
         (i32.const 3008)
         (get_local $15)
        )
       )
      )
      (i32.store8
       (i32.add
        (get_local $4)
        (get_local $15)
       )
       (i32.const 0)
      )
      (i64.store
       (i32.add
        (i32.add
         (get_local $17)
         (i32.const 8)
        )
        (i32.const 16)
       )
       (i64.load
        (i32.add
         (i32.add
          (get_local $17)
          (i32.const 80)
         )
         (i32.const 16)
        )
       )
      )
      (i64.store
       (i32.add
        (i32.add
         (get_local $17)
         (i32.const 8)
        )
        (i32.const 8)
       )
       (i64.load
        (i32.add
         (i32.add
          (get_local $17)
          (i32.const 80)
         )
         (i32.const 8)
        )
       )
      )
      (i64.store offset=8
       (get_local $17)
       (i64.load offset=80
        (get_local $17)
       )
      )
      (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
       (get_local $2)
       (get_local $1)
       (i32.add
        (get_local $17)
        (i32.const 8)
       )
       (get_local $17)
      )
      (block $label$44
       (br_if $label$44
        (i32.eqz
         (i32.and
          (i32.load8_u offset=208
           (get_local $17)
          )
          (i32.const 1)
         )
        )
       )
       (call $_ZdlPv
        (i32.load offset=216
         (get_local $17)
        )
       )
      )
      (block $label$45
       (br_if $label$45
        (i32.eqz
         (tee_local $4
          (i32.load offset=192
           (get_local $17)
          )
         )
        )
       )
       (block $label$46
        (block $label$47
         (br_if $label$47
          (i32.eq
           (tee_local $15
            (i32.load
             (tee_local $5
              (i32.add
               (get_local $17)
               (i32.const 196)
              )
             )
            )
           )
           (get_local $4)
          )
         )
         (loop $label$48
          (set_local $2
           (i32.load
            (tee_local $15
             (i32.add
              (get_local $15)
              (i32.const -24)
             )
            )
           )
          )
          (i32.store
           (get_local $15)
           (i32.const 0)
          )
          (block $label$49
           (br_if $label$49
            (i32.eqz
             (get_local $2)
            )
           )
           (call $_ZdlPv
            (get_local $2)
           )
          )
          (br_if $label$48
           (i32.ne
            (get_local $4)
            (get_local $15)
           )
          )
         )
         (set_local $15
          (i32.load
           (i32.add
            (get_local $17)
            (i32.const 192)
           )
          )
         )
         (br $label$46)
        )
        (set_local $15
         (get_local $4)
        )
       )
       (i32.store
        (get_local $5)
        (get_local $4)
       )
       (call $_ZdlPv
        (get_local $15)
       )
      )
      (i32.store offset=4
       (i32.const 0)
       (i32.add
        (get_local $17)
        (i32.const 464)
       )
      )
      (return)
     )
     (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
      (get_local $16)
     )
     (unreachable)
    )
    (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
     (i32.add
      (get_local $17)
      (i32.const 208)
     )
    )
    (unreachable)
   )
   (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
    (i32.add
     (get_local $17)
     (i32.const 208)
    )
   )
   (unreachable)
  )
  (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
   (i32.add
    (get_local $17)
    (i32.const 208)
   )
  )
  (unreachable)
 )
 (func $_ZN5eosio8currency15create_currencyERKNS0_6createE (param $0 i32) (param $1 i32)
  (local $2 i64)
  (local $3 i32)
  (local $4 i64)
  (local $5 i32)
  (local $6 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $6
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 64)
    )
   )
  )
  (set_local $5
   (i32.const 0)
  )
  (set_local $4
   (tee_local $2
    (i64.shr_u
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 16)
      )
     )
     (i64.const 8)
    )
   )
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $4)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $4
          (i64.shr_u
           (get_local $4)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $4
           (i64.shr_u
            (get_local $4)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $5
          (i32.add
           (get_local $5)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $5
        (i32.add
         (get_local $5)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (set_local $5
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $6)
    (i32.const 56)
   )
   (i32.const 0)
  )
  (i64.store offset=40
   (get_local $6)
   (i64.const -1)
  )
  (i64.store offset=48
   (get_local $6)
   (i64.const 0)
  )
  (i64.store offset=24
   (get_local $6)
   (tee_local $4
    (i64.load
     (get_local $0)
    )
   )
  )
  (i64.store offset=32
   (get_local $6)
   (get_local $2)
  )
  (block $label$5
   (block $label$6
    (br_if $label$6
     (i32.lt_s
      (tee_local $3
       (call $db_find_i64
        (get_local $4)
        (get_local $2)
        (i64.const -4157508551318700032)
        (get_local $2)
       )
      )
      (i32.const 0)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=48
       (call $_ZNK5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE31load_object_by_primary_iteratorEl
        (i32.add
         (get_local $6)
         (i32.const 24)
        )
        (get_local $3)
       )
      )
      (i32.add
       (get_local $6)
       (i32.const 24)
      )
     )
     (i32.const 224)
    )
    (br $label$5)
   )
   (set_local $5
    (i32.const 1)
   )
  )
  (call $eosio_assert
   (get_local $5)
   (i32.const 3040)
  )
  (set_local $4
   (i64.load
    (get_local $1)
   )
  )
  (i32.store offset=16
   (get_local $6)
   (get_local $1)
  )
  (call $_ZN5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE7emplaceIZNS1_15create_currencyERKNS1_6createEEUlRT_E_EENS3_14const_iteratorEyOS8_
   (i32.add
    (get_local $6)
    (i32.const 8)
   )
   (i32.add
    (get_local $6)
    (i32.const 24)
   )
   (get_local $4)
   (i32.add
    (get_local $6)
    (i32.const 16)
   )
  )
  (block $label$7
   (br_if $label$7
    (i32.eqz
     (tee_local $1
      (i32.load offset=48
       (get_local $6)
      )
     )
    )
   )
   (block $label$8
    (block $label$9
     (br_if $label$9
      (i32.eq
       (tee_local $5
        (i32.load
         (tee_local $0
          (i32.add
           (get_local $6)
           (i32.const 52)
          )
         )
        )
       )
       (get_local $1)
      )
     )
     (loop $label$10
      (set_local $3
       (i32.load
        (tee_local $5
         (i32.add
          (get_local $5)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $5)
       (i32.const 0)
      )
      (block $label$11
       (br_if $label$11
        (i32.eqz
         (get_local $3)
        )
       )
       (call $_ZdlPv
        (get_local $3)
       )
      )
      (br_if $label$10
       (i32.ne
        (get_local $1)
        (get_local $5)
       )
      )
     )
     (set_local $5
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const 48)
       )
      )
     )
     (br $label$8)
    )
    (set_local $5
     (get_local $1)
    )
   )
   (i32.store
    (get_local $0)
    (get_local $1)
   )
   (call $_ZdlPv
    (get_local $5)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $6)
    (i32.const 64)
   )
  )
 )
 (func $_ZN5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE7emplaceIZNS1_15create_currencyERKNS1_6createEEUlRT_E_EENS3_14const_iteratorEyOS8_ (param $0 i32) (param $1 i32) (param $2 i64) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i64.store offset=40
   (get_local $7)
   (get_local $2)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load
     (get_local $1)
    )
    (call $current_receiver)
   )
   (i32.const 288)
  )
  (i32.store offset=20
   (get_local $7)
   (get_local $3)
  )
  (i32.store offset=16
   (get_local $7)
   (get_local $1)
  )
  (i32.store offset=24
   (get_local $7)
   (i32.add
    (get_local $7)
    (i32.const 40)
   )
  )
  (drop
   (call $_ZN5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE4itemC2IZNS3_7emplaceIZNS1_15create_currencyERKNS1_6createEEUlRT_E_EENS3_14const_iteratorEyOSA_EUlSB_E_EEPKS3_SE_
    (tee_local $3
     (call $_Znwj
      (i32.const 64)
     )
    )
    (get_local $1)
    (i32.add
     (get_local $7)
     (i32.const 16)
    )
   )
  )
  (i32.store offset=32
   (get_local $7)
   (get_local $3)
  )
  (i64.store offset=16
   (get_local $7)
   (tee_local $2
    (i64.shr_u
     (i64.load offset=8
      (get_local $3)
     )
     (i64.const 8)
    )
   )
  )
  (i32.store offset=12
   (get_local $7)
   (tee_local $4
    (i32.load offset=52
     (get_local $3)
    )
   )
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.ge_u
      (tee_local $5
       (i32.load
        (tee_local $6
         (i32.add
          (get_local $1)
          (i32.const 28)
         )
        )
       )
      )
      (i32.load
       (i32.add
        (get_local $1)
        (i32.const 32)
       )
      )
     )
    )
    (i64.store offset=8
     (get_local $5)
     (get_local $2)
    )
    (i32.store offset=16
     (get_local $5)
     (get_local $4)
    )
    (i32.store offset=32
     (get_local $7)
     (i32.const 0)
    )
    (i32.store
     (get_local $5)
     (get_local $3)
    )
    (i32.store
     (get_local $6)
     (i32.add
      (get_local $5)
      (i32.const 24)
     )
    )
    (br $label$0)
   )
   (call $_ZNSt3__16vectorIN5eosio11multi_indexILy14289235522390851584ENS1_8currency14currency_statsEJEE8item_ptrENS_9allocatorIS6_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS5_4itemENS_14default_deleteISC_EEEERyRlEEEvDpOT_
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.add
     (get_local $7)
     (i32.const 32)
    )
    (i32.add
     (get_local $7)
     (i32.const 16)
    )
    (i32.add
     (get_local $7)
     (i32.const 12)
    )
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $3)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (set_local $1
   (i32.load offset=32
    (get_local $7)
   )
  )
  (i32.store offset=32
   (get_local $7)
   (i32.const 0)
  )
  (block $label$2
   (br_if $label$2
    (i32.eqz
     (get_local $1)
    )
   )
   (call $_ZdlPv
    (get_local $1)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $7)
    (i32.const 48)
   )
  )
 )
 (func $_ZN5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE4itemC2IZNS3_7emplaceIZNS1_15create_currencyERKNS1_6createEEUlRT_E_EENS3_14const_iteratorEyOSA_EUlSB_E_EEPKS3_SE_ (param $0 i32) (param $1 i32) (param $2 i32) (result i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 64)
    )
   )
  )
  (set_local $5
   (call $_ZN5eosio8currency14currency_statsC2Ev
    (get_local $0)
   )
  )
  (i32.store offset=48
   (get_local $0)
   (get_local $1)
  )
  (i64.store offset=8
   (get_local $0)
   (i64.load
    (i32.add
     (i32.load
      (tee_local $1
       (i32.load offset=4
        (get_local $2)
       )
      )
     )
     (i32.const 16)
    )
   )
  )
  (set_local $3
   (i32.load
    (get_local $2)
   )
  )
  (i64.store offset=16
   (get_local $0)
   (i64.load offset=8
    (tee_local $6
     (i32.load
      (get_local $1)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 24)
   )
   (i64.load
    (i32.add
     (get_local $6)
     (i32.const 16)
    )
   )
  )
  (i64.store offset=32
   (get_local $0)
   (i64.load
    (i32.load
     (get_local $1)
    )
   )
  )
  (i32.store8 offset=40
   (get_local $0)
   (i32.ne
    (i32.load8_u offset=24
     (i32.load
      (get_local $1)
     )
    )
    (i32.const 0)
   )
  )
  (i32.store8 offset=41
   (get_local $0)
   (i32.ne
    (i32.load8_u offset=25
     (i32.load
      (get_local $1)
     )
    )
    (i32.const 0)
   )
  )
  (i32.store8 offset=42
   (get_local $0)
   (i32.ne
    (i32.load8_u offset=26
     (i32.load
      (get_local $1)
     )
    )
    (i32.const 0)
   )
  )
  (i32.store offset=56
   (get_local $7)
   (i32.add
    (get_local $7)
    (i32.const 45)
   )
  )
  (i32.store offset=52
   (get_local $7)
   (get_local $7)
  )
  (i32.store offset=48
   (get_local $7)
   (get_local $7)
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_8currency14currency_statsE
    (i32.add
     (get_local $7)
     (i32.const 48)
    )
    (get_local $5)
   )
  )
  (i32.store offset=52
   (get_local $0)
   (call $db_store_i64
    (i64.load offset=8
     (get_local $3)
    )
    (i64.const -4157508551318700032)
    (i64.load
     (i32.load offset=8
      (get_local $2)
     )
    )
    (tee_local $4
     (i64.shr_u
      (i64.load offset=8
       (get_local $0)
      )
      (i64.const 8)
     )
    )
    (get_local $7)
    (i32.const 45)
   )
  )
  (block $label$0
   (br_if $label$0
    (i64.lt_u
     (get_local $4)
     (i64.load offset=16
      (get_local $3)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $3)
     (i32.const 16)
    )
    (i64.add
     (get_local $4)
     (i64.const 1)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $7)
    (i32.const 64)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio8exchange4lendEyNS_11symbol_typeENS_14extended_assetE (type $FUNCSIG$vijji) (param $0 i32) (param $1 i64) (param $2 i64) (param $3 i32)
  (local $4 i64)
  (local $5 i64)
  (local $6 i64)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 464)
    )
   )
  )
  (call $require_auth
   (get_local $1)
  )
  (set_local $8
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i64.gt_u
     (i64.add
      (tee_local $4
       (i64.load
        (get_local $3)
       )
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $6
    (i64.shr_u
     (i64.load offset=8
      (get_local $3)
     )
     (i64.const 8)
    )
   )
   (set_local $7
    (i32.const 0)
   )
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $6)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $6
          (i64.shr_u
           (get_local $6)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $6
           (i64.shr_u
            (get_local $6)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $7
          (i32.add
           (get_local $7)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $8
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $7
        (i32.add
         (get_local $7)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $8
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $8)
   (i32.const 1840)
  )
  (call $eosio_assert
   (i64.gt_s
    (get_local $4)
    (i64.const 0)
   )
   (i32.const 3088)
  )
  (i64.store offset=8
   (get_local $9)
   (i64.shr_u
    (get_local $2)
    (i64.const 8)
   )
  )
  (set_local $6
   (i64.load
    (get_local $0)
   )
  )
  (set_local $7
   (call $_ZN5eosio14exchange_stateC2Ev
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 264)
   )
   (i64.const -1)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 272)
   )
   (i64.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 280)
   )
   (i32.const 0)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 256)
   )
   (tee_local $2
    (i64.load offset=8
     (get_local $9)
    )
   )
  )
  (i64.store offset=248
   (get_local $9)
   (get_local $6)
  )
  (i64.store offset=288
   (get_local $9)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 296)
   )
   (tee_local $5
    (i64.or
     (tee_local $4
      (i64.shl
       (get_local $2)
       (i64.const 4)
      )
     )
     (i64.const 1)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 304)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 312)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 316)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 320)
   )
   (i32.const 0)
  )
  (i32.store8
   (i32.add
    (get_local $9)
    (i32.const 324)
   )
   (i32.const 0)
  )
  (i64.store offset=328
   (get_local $9)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 336)
   )
   (tee_local $4
    (i64.or
     (get_local $4)
     (i64.const 2)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 344)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 352)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 356)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 360)
   )
   (i32.const 0)
  )
  (i32.store8
   (i32.add
    (get_local $9)
    (i32.const 364)
   )
   (i32.const 0)
  )
  (i64.store offset=368
   (get_local $9)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 376)
   )
   (get_local $5)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 384)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 392)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 396)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 400)
   )
   (i32.const 0)
  )
  (i64.store offset=408
   (get_local $9)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 416)
   )
   (get_local $4)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 424)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 432)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 436)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 440)
   )
   (i32.const 0)
  )
  (i32.store offset=448
   (get_local $9)
   (i32.add
    (get_local $0)
    (i32.const 16)
   )
  )
  (call $_ZNK5eosio11multi_indexILy10497615196363685888ENS_14exchange_stateEJEE4findEy
   (i32.add
    (get_local $9)
    (i32.const 452)
   )
   (i32.add
    (get_local $9)
    (i32.const 248)
   )
   (get_local $2)
  )
  (call $eosio_assert
   (i32.ne
    (i32.load
     (tee_local $8
      (i32.add
       (get_local $9)
       (i32.const 456)
      )
     )
    )
    (i32.const 0)
   )
   (i32.const 720)
  )
  (drop
   (call $memcpy
    (get_local $7)
    (i32.load
     (get_local $8)
    )
    (i32.const 232)
   )
  )
  (call $_ZN5eosio12market_state4lendEyRKNS_14extended_assetE
   (i32.add
    (get_local $9)
    (i32.const 8)
   )
   (get_local $1)
   (get_local $3)
  )
  (call $_ZN5eosio12market_state4saveEv
   (i32.add
    (get_local $9)
    (i32.const 8)
   )
  )
  (drop
   (call $_ZN5eosio12market_stateD2Ev
    (i32.add
     (get_local $9)
     (i32.const 8)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 464)
   )
  )
 )
 (func $_ZN5eosio8exchange6unlendEyNS_11symbol_typeEdNS_15extended_symbolE (type $FUNCSIG$vijjdi) (param $0 i32) (param $1 i64) (param $2 i64) (param $3 f64) (param $4 i32)
  (local $5 i32)
  (local $6 i64)
  (local $7 i64)
  (local $8 i64)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 464)
    )
   )
  )
  (call $require_auth
   (get_local $1)
  )
  (call $eosio_assert
   (f64.gt
    (get_local $3)
    (f64.const 0)
   )
   (i32.const 3120)
  )
  (i64.store offset=8
   (get_local $9)
   (i64.shr_u
    (get_local $2)
    (i64.const 8)
   )
  )
  (set_local $2
   (i64.load
    (get_local $0)
   )
  )
  (set_local $5
   (call $_ZN5eosio14exchange_stateC2Ev
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 264)
   )
   (i64.const -1)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 272)
   )
   (i64.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 280)
   )
   (i32.const 0)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 256)
   )
   (tee_local $6
    (i64.load offset=8
     (get_local $9)
    )
   )
  )
  (i64.store offset=248
   (get_local $9)
   (get_local $2)
  )
  (i64.store offset=288
   (get_local $9)
   (get_local $2)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 296)
   )
   (tee_local $8
    (i64.or
     (tee_local $7
      (i64.shl
       (get_local $6)
       (i64.const 4)
      )
     )
     (i64.const 1)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 304)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 312)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 316)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 320)
   )
   (i32.const 0)
  )
  (i32.store8
   (i32.add
    (get_local $9)
    (i32.const 324)
   )
   (i32.const 0)
  )
  (i64.store offset=328
   (get_local $9)
   (get_local $2)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 336)
   )
   (tee_local $7
    (i64.or
     (get_local $7)
     (i64.const 2)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 344)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 352)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 356)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 360)
   )
   (i32.const 0)
  )
  (i32.store8
   (i32.add
    (get_local $9)
    (i32.const 364)
   )
   (i32.const 0)
  )
  (i64.store offset=368
   (get_local $9)
   (get_local $2)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 376)
   )
   (get_local $8)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 384)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 392)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 396)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 400)
   )
   (i32.const 0)
  )
  (i64.store offset=408
   (get_local $9)
   (get_local $2)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 416)
   )
   (get_local $7)
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 424)
   )
   (i64.const -1)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 432)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 436)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 440)
   )
   (i32.const 0)
  )
  (i32.store offset=448
   (get_local $9)
   (i32.add
    (get_local $0)
    (i32.const 16)
   )
  )
  (call $_ZNK5eosio11multi_indexILy10497615196363685888ENS_14exchange_stateEJEE4findEy
   (i32.add
    (get_local $9)
    (i32.const 452)
   )
   (i32.add
    (get_local $9)
    (i32.const 248)
   )
   (get_local $6)
  )
  (call $eosio_assert
   (i32.ne
    (i32.load
     (tee_local $0
      (i32.add
       (get_local $9)
       (i32.const 456)
      )
     )
    )
    (i32.const 0)
   )
   (i32.const 720)
  )
  (drop
   (call $memcpy
    (get_local $5)
    (i32.load
     (get_local $0)
    )
    (i32.const 232)
   )
  )
  (call $_ZN5eosio12market_state6unlendEydRKNS_15extended_symbolE
   (i32.add
    (get_local $9)
    (i32.const 8)
   )
   (get_local $1)
   (get_local $3)
   (get_local $4)
  )
  (call $_ZN5eosio12market_state4saveEv
   (i32.add
    (get_local $9)
    (i32.const 8)
   )
  )
  (drop
   (call $_ZN5eosio12market_stateD2Ev
    (i32.add
     (get_local $9)
     (i32.const 8)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 464)
   )
  )
 )
 (func $_ZN5eosio8exchange2onERKNS_8currency8transferEy (param $0 i32) (param $1 i32) (param $2 i64)
  (local $3 i64)
  (local $4 i64)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i64)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (local $12 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $12
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (block $label$0
   (br_if $label$0
    (i64.ne
     (tee_local $8
      (i64.load
       (get_local $0)
      )
     )
     (get_local $2)
    )
   )
   (call $_ZN5eosio8currency2onERKNS0_8transferE
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
    (get_local $1)
   )
   (set_local $8
    (i64.load
     (get_local $0)
    )
   )
  )
  (block $label$1
   (br_if $label$1
    (i64.ne
     (i64.load offset=8
      (get_local $1)
     )
     (get_local $8)
    )
   )
   (set_local $4
    (i64.load
     (i32.add
      (get_local $1)
      (i32.const 24)
     )
    )
   )
   (set_local $10
    (i32.const 0)
   )
   (block $label$2
    (br_if $label$2
     (i64.gt_u
      (i64.add
       (tee_local $3
        (i64.load offset=16
         (get_local $1)
        )
       )
       (i64.const 4611686018427387903)
      )
      (i64.const 9223372036854775806)
     )
    )
    (set_local $8
     (i64.shr_u
      (get_local $4)
      (i64.const 8)
     )
    )
    (set_local $9
     (i32.const 0)
    )
    (block $label$3
     (loop $label$4
      (br_if $label$3
       (i32.gt_u
        (i32.add
         (i32.shl
          (i32.wrap/i64
           (get_local $8)
          )
          (i32.const 24)
         )
         (i32.const -1073741825)
        )
        (i32.const 452984830)
       )
      )
      (block $label$5
       (br_if $label$5
        (i64.ne
         (i64.and
          (tee_local $8
           (i64.shr_u
            (get_local $8)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (loop $label$6
        (br_if $label$3
         (i64.ne
          (i64.and
           (tee_local $8
            (i64.shr_u
             (get_local $8)
             (i64.const 8)
            )
           )
           (i64.const 255)
          )
          (i64.const 0)
         )
        )
        (br_if $label$6
         (i32.lt_s
          (tee_local $9
           (i32.add
            (get_local $9)
            (i32.const 1)
           )
          )
          (i32.const 7)
         )
        )
       )
      )
      (set_local $10
       (i32.const 1)
      )
      (br_if $label$4
       (i32.lt_s
        (tee_local $9
         (i32.add
          (get_local $9)
          (i32.const 1)
         )
        )
        (i32.const 7)
       )
      )
      (br $label$2)
     )
    )
    (set_local $10
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (get_local $10)
    (i32.const 3152)
   )
   (call $eosio_assert
    (i64.ne
     (get_local $3)
     (i64.const 0)
    )
    (i32.const 3184)
   )
   (block $label$7
    (block $label$8
     (block $label$9
      (br_if $label$9
       (i64.lt_s
        (get_local $3)
        (i64.const 1)
       )
      )
      (call $eosio_assert
       (i32.const 1)
       (i32.const 3232)
      )
      (set_local $11
       (i32.add
        (get_local $1)
        (i32.const 36)
       )
      )
      (set_local $10
       (i32.add
        (get_local $1)
        (i32.const 32)
       )
      )
      (br $label$8)
     )
     (set_local $9
      (i32.const 1)
     )
     (set_local $10
      (i32.add
       (get_local $1)
       (i32.const 32)
      )
     )
     (set_local $6
      (i32.const 0)
     )
     (block $label$10
      (br_if $label$10
       (i32.ne
        (tee_local $5
         (call $strlen
          (i32.const 1968)
         )
        )
        (select
         (i32.load
          (tee_local $11
           (i32.add
            (get_local $1)
            (i32.const 36)
           )
          )
         )
         (i32.shr_u
          (tee_local $7
           (i32.load8_u offset=32
            (get_local $1)
           )
          )
          (i32.const 1)
         )
         (i32.and
          (get_local $7)
          (i32.const 1)
         )
        )
       )
      )
      (set_local $6
       (i32.eqz
        (call $_ZNKSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7compareEjjPKcj
         (get_local $10)
         (i32.const 0)
         (i32.const -1)
         (i32.const 1968)
         (get_local $5)
        )
       )
      )
     )
     (call $eosio_assert
      (get_local $6)
      (i32.const 3232)
     )
     (br_if $label$7
      (i64.lt_s
       (get_local $3)
       (i64.const 0)
      )
     )
    )
    (set_local $9
     (i32.const 0)
    )
    (br_if $label$7
     (i32.ne
      (tee_local $6
       (call $strlen
        (i32.const 1872)
       )
      )
      (select
       (i32.load
        (get_local $11)
       )
       (i32.shr_u
        (tee_local $11
         (i32.load8_u
          (get_local $10)
         )
        )
        (i32.const 1)
       )
       (i32.and
        (get_local $11)
        (i32.const 1)
       )
      )
     )
    )
    (set_local $9
     (i32.eqz
      (call $_ZNKSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7compareEjjPKcj
       (get_local $10)
       (i32.const 0)
       (i32.const -1)
       (i32.const 1872)
       (get_local $6)
      )
     )
    )
   )
   (call $eosio_assert
    (get_local $9)
    (i32.const 3280)
   )
   (i64.store offset=32
    (get_local $12)
    (get_local $4)
   )
   (set_local $8
    (i64.load
     (get_local $1)
    )
   )
   (i64.store
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
    (get_local $4)
   )
   (i64.store offset=40
    (get_local $12)
    (get_local $2)
   )
   (i64.store
    (i32.add
     (get_local $12)
     (i32.const 16)
    )
    (get_local $2)
   )
   (i64.store offset=24
    (get_local $12)
    (get_local $3)
   )
   (i64.store
    (get_local $12)
    (get_local $3)
   )
   (call $_ZN5eosio17exchange_accounts14adjust_balanceEyNS_14extended_assetERKNSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (get_local $8)
    (get_local $12)
    (get_local $9)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $12)
    (i32.const 48)
   )
  )
 )
 (func $_ZN5eosio8currency2onERKNS0_8transferE (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
  (local $8 i64)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $11
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 112)
    )
   )
  )
  (call $require_auth
   (i64.load
    (get_local $1)
   )
  )
  (set_local $8
   (i64.load
    (tee_local $10
     (i32.add
      (get_local $1)
      (i32.const 24)
     )
    )
   )
  )
  (set_local $9
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $11)
    (i32.const 104)
   )
   (i32.const 0)
  )
  (i64.store offset=88
   (get_local $11)
   (i64.const -1)
  )
  (i64.store offset=96
   (get_local $11)
   (i64.const 0)
  )
  (i64.store offset=72
   (get_local $11)
   (i64.load
    (get_local $0)
   )
  )
  (i64.store offset=80
   (get_local $11)
   (tee_local $8
    (i64.shr_u
     (get_local $8)
     (i64.const 8)
    )
   )
  )
  (set_local $2
   (call $_ZNK5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE3getEyPKc
    (i32.add
     (get_local $11)
     (i32.const 72)
    )
    (get_local $8)
    (i32.const 2224)
   )
  )
  (call $require_recipient
   (i64.load offset=8
    (get_local $1)
   )
  )
  (set_local $3
   (i32.add
    (get_local $1)
    (i32.const 16)
   )
  )
  (block $label$0
   (br_if $label$0
    (i64.gt_u
     (i64.add
      (i64.load offset=16
       (get_local $1)
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $8
    (i64.shr_u
     (i64.load
      (get_local $10)
     )
     (i64.const 8)
    )
   )
   (set_local $10
    (i32.const 0)
   )
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $8)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $8
          (i64.shr_u
           (get_local $8)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $8
           (i64.shr_u
            (get_local $8)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $10
          (i32.add
           (get_local $10)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $9
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $10
        (i32.add
         (get_local $10)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $9
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $9)
   (i32.const 1840)
  )
  (call $eosio_assert
   (i64.gt_s
    (i64.load
     (get_local $3)
    )
    (i64.const 0)
   )
   (i32.const 3328)
  )
  (i32.store
   (tee_local $10
    (i32.add
     (i32.add
      (get_local $11)
      (i32.const 56)
     )
     (i32.const 12)
    )
   )
   (i32.load
    (tee_local $9
     (i32.add
      (get_local $3)
      (i32.const 12)
     )
    )
   )
  )
  (i32.store
   (tee_local $5
    (i32.add
     (i32.add
      (get_local $11)
      (i32.const 56)
     )
     (i32.const 8)
    )
   )
   (i32.load
    (tee_local $4
     (i32.add
      (get_local $3)
      (i32.const 8)
     )
    )
   )
  )
  (i32.store offset=60
   (get_local $11)
   (i32.load
    (tee_local $6
     (i32.add
      (get_local $3)
      (i32.const 4)
     )
    )
   )
  )
  (i32.store offset=56
   (get_local $11)
   (i32.load
    (get_local $3)
   )
  )
  (set_local $8
   (i64.load
    (get_local $1)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 24)
    )
    (i32.const 12)
   )
   (i32.load
    (get_local $10)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 24)
    )
    (i32.const 8)
   )
   (i32.load
    (get_local $5)
   )
  )
  (i32.store offset=28
   (get_local $11)
   (i32.load offset=60
    (get_local $11)
   )
  )
  (i32.store offset=24
   (get_local $11)
   (i32.load offset=56
    (get_local $11)
   )
  )
  (call $_ZN5eosio8currency11sub_balanceEyNS_5assetERKNS0_14currency_statsE
   (get_local $0)
   (get_local $8)
   (i32.add
    (get_local $11)
    (i32.const 24)
   )
   (get_local $2)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 40)
    )
    (i32.const 12)
   )
   (i32.load
    (get_local $9)
   )
  )
  (i32.store
   (tee_local $10
    (i32.add
     (i32.add
      (get_local $11)
      (i32.const 40)
     )
     (i32.const 8)
    )
   )
   (i32.load
    (get_local $4)
   )
  )
  (i32.store offset=44
   (get_local $11)
   (i32.load
    (get_local $6)
   )
  )
  (i32.store offset=40
   (get_local $11)
   (i32.load
    (get_local $3)
   )
  )
  (set_local $8
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
   )
  )
  (set_local $7
   (i64.load
    (get_local $1)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 8)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $10)
   )
  )
  (i64.store offset=8
   (get_local $11)
   (i64.load offset=40
    (get_local $11)
   )
  )
  (call $_ZN5eosio8currency11add_balanceEyNS_5assetERKNS0_14currency_statsEy
   (get_local $0)
   (get_local $8)
   (i32.add
    (get_local $11)
    (i32.const 8)
   )
   (get_local $2)
   (get_local $7)
  )
  (block $label$5
   (br_if $label$5
    (i32.eqz
     (tee_local $3
      (i32.load offset=96
       (get_local $11)
      )
     )
    )
   )
   (block $label$6
    (block $label$7
     (br_if $label$7
      (i32.eq
       (tee_local $10
        (i32.load
         (tee_local $9
          (i32.add
           (get_local $11)
           (i32.const 100)
          )
         )
        )
       )
       (get_local $3)
      )
     )
     (loop $label$8
      (set_local $1
       (i32.load
        (tee_local $10
         (i32.add
          (get_local $10)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $10)
       (i32.const 0)
      )
      (block $label$9
       (br_if $label$9
        (i32.eqz
         (get_local $1)
        )
       )
       (call $_ZdlPv
        (get_local $1)
       )
      )
      (br_if $label$8
       (i32.ne
        (get_local $3)
        (get_local $10)
       )
      )
     )
     (set_local $10
      (i32.load
       (i32.add
        (get_local $11)
        (i32.const 96)
       )
      )
     )
     (br $label$6)
    )
    (set_local $10
     (get_local $3)
    )
   )
   (i32.store
    (get_local $9)
    (get_local $3)
   )
   (call $_ZdlPv
    (get_local $10)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $11)
    (i32.const 112)
   )
  )
 )
 (func $_ZN5eosio8currency11sub_balanceEyNS_5assetERKNS0_14currency_statsE (param $0 i32) (param $1 i64) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $6
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $6)
    (i32.const 40)
   )
   (i32.const 0)
  )
  (i64.store offset=16
   (get_local $6)
   (get_local $1)
  )
  (i64.store offset=24
   (get_local $6)
   (i64.const -1)
  )
  (i64.store offset=32
   (get_local $6)
   (i64.const 0)
  )
  (i64.store offset=8
   (get_local $6)
   (i64.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i64.ge_s
    (i64.load
     (tee_local $0
      (call $_ZNK5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE3getEyPKc
       (i32.add
        (get_local $6)
        (i32.const 8)
       )
       (i64.shr_u
        (i64.load offset=8
         (get_local $2)
        )
        (i64.const 8)
       )
       (i32.const 2224)
      )
     )
    )
    (i64.load
     (get_local $2)
    )
   )
   (i32.const 3360)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (call $has_auth
       (get_local $1)
      )
     )
    )
    (set_local $5
     (i32.const 1)
    )
    (set_local $4
     (i32.const 1)
    )
    (block $label$2
     (br_if $label$2
      (i32.eqz
       (i32.load8_u offset=40
        (get_local $3)
       )
      )
     )
     (set_local $4
      (i32.xor
       (i32.load8_u offset=16
        (get_local $0)
       )
       (i32.const 1)
      )
     )
    )
    (call $eosio_assert
     (get_local $4)
     (i32.const 3392)
    )
    (block $label$3
     (br_if $label$3
      (i32.eqz
       (i32.load8_u
        (i32.add
         (get_local $3)
         (i32.const 40)
        )
       )
      )
     )
     (set_local $5
      (i32.xor
       (i32.load8_u offset=43
        (get_local $3)
       )
       (i32.const 1)
      )
     )
    )
    (call $eosio_assert
     (get_local $5)
     (i32.const 3424)
    )
    (call $eosio_assert
     (select
      (i32.load8_u offset=17
       (get_local $0)
      )
      (i32.const 1)
      (i32.load8_u offset=44
       (get_local $3)
      )
     )
     (i32.const 3472)
    )
    (br $label$0)
   )
   (block $label$4
    (br_if $label$4
     (i32.eqz
      (call $has_auth
       (i64.load offset=32
        (get_local $3)
       )
      )
     )
    )
    (call $eosio_assert
     (i32.load8_u offset=41
      (get_local $3)
     )
     (i32.const 3504)
    )
    (br $label$0)
   )
   (call $eosio_assert
    (i32.const 0)
    (i32.const 3536)
   )
  )
  (i32.store
   (get_local $6)
   (get_local $2)
  )
  (call $_ZN5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE6modifyIZNS1_11sub_balanceEyNS_5assetERKNS1_14currency_statsEEUlRT_E_EEvRKS2_yOS9_
   (i32.add
    (get_local $6)
    (i32.const 8)
   )
   (get_local $0)
   (get_local $1)
   (get_local $6)
  )
  (block $label$5
   (br_if $label$5
    (i32.eqz
     (tee_local $0
      (i32.load offset=32
       (get_local $6)
      )
     )
    )
   )
   (block $label$6
    (block $label$7
     (br_if $label$7
      (i32.eq
       (tee_local $2
        (i32.load
         (tee_local $5
          (i32.add
           (get_local $6)
           (i32.const 36)
          )
         )
        )
       )
       (get_local $0)
      )
     )
     (loop $label$8
      (set_local $3
       (i32.load
        (tee_local $2
         (i32.add
          (get_local $2)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $2)
       (i32.const 0)
      )
      (block $label$9
       (br_if $label$9
        (i32.eqz
         (get_local $3)
        )
       )
       (call $_ZdlPv
        (get_local $3)
       )
      )
      (br_if $label$8
       (i32.ne
        (get_local $0)
        (get_local $2)
       )
      )
     )
     (set_local $2
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const 32)
       )
      )
     )
     (br $label$6)
    )
    (set_local $2
     (get_local $0)
    )
   )
   (i32.store
    (get_local $5)
    (get_local $0)
   )
   (call $_ZdlPv
    (get_local $2)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $6)
    (i32.const 48)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE3getEyPKc (param $0 i32) (param $1 i64) (param $2 i32) (result i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (set_local $4
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i64.eq
      (i64.shr_u
       (i64.load offset=8
        (i32.load
         (get_local $6)
        )
       )
       (i64.const 8)
      )
      (get_local $1)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $5
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $5)
       (get_local $4)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (get_local $3)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load
       (i32.add
        (tee_local $6
         (i32.load
          (i32.add
           (get_local $7)
           (i32.const -24)
          )
         )
        )
        (i32.const 20)
       )
      )
      (get_local $0)
     )
     (i32.const 224)
    )
    (br $label$2)
   )
   (set_local $6
    (i32.const 0)
   )
   (br_if $label$2
    (i32.lt_s
     (tee_local $5
      (call $db_find_i64
       (i64.load
        (get_local $0)
       )
       (i64.load offset=8
        (get_local $0)
       )
       (i64.const 3607749779137757184)
       (get_local $1)
      )
     )
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=20
      (tee_local $6
       (call $_ZNK5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE31load_object_by_primary_iteratorEl
        (get_local $0)
        (get_local $5)
       )
      )
     )
     (get_local $0)
    )
    (i32.const 224)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $6)
    (i32.const 0)
   )
   (get_local $2)
  )
  (get_local $6)
 )
 (func $_ZN5eosio11multi_indexILy3607749779137757184ENS_8currency7accountEJEE6modifyIZNS1_11sub_balanceEyNS_5assetERKNS1_14currency_statsEEUlRT_E_EEvRKS2_yOS9_ (param $0 i32) (param $1 i32) (param $2 i64) (param $3 i32)
  (local $4 i64)
  (local $5 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $5
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (call $eosio_assert
   (i32.eq
    (i32.load
     (i32.add
      (get_local $1)
      (i32.const 20)
     )
    )
    (get_local $0)
   )
   (i32.const 400)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load
     (get_local $0)
    )
    (call $current_receiver)
   )
   (i32.const 448)
  )
  (i64.store
   (get_local $1)
   (i64.sub
    (i64.load
     (get_local $1)
    )
    (i64.load
     (i32.load
      (get_local $3)
     )
    )
   )
  )
  (set_local $4
   (i64.load offset=8
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 544)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (get_local $5)
    (get_local $1)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.or
     (get_local $5)
     (i32.const 8)
    )
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store8 offset=31
   (get_local $5)
   (i32.load8_u offset=16
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $5)
     (i32.const 16)
    )
    (i32.add
     (get_local $5)
     (i32.const 31)
    )
    (i32.const 1)
   )
  )
  (i32.store8 offset=31
   (get_local $5)
   (i32.load8_u offset=17
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 608)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $5)
     (i32.const 17)
    )
    (i32.add
     (get_local $5)
     (i32.const 31)
    )
    (i32.const 1)
   )
  )
  (call $db_update_i64
   (i32.load offset=24
    (get_local $1)
   )
   (get_local $2)
   (get_local $5)
   (i32.const 18)
  )
  (block $label$0
   (br_if $label$0
    (i64.lt_u
     (tee_local $2
      (i64.shr_u
       (get_local $4)
       (i64.const 8)
      )
     )
     (i64.load offset=16
      (get_local $0)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (i64.add
     (get_local $2)
     (i64.const 1)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $5)
    (i32.const 32)
   )
  )
 )
 (func $_ZN5eosio8exchange5applyEyy (param $0 i32) (param $1 i64) (param $2 i64)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i64)
  (local $7 i64)
  (local $8 i64)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 160)
    )
   )
  )
  (set_local $6
   (i64.const 0)
  )
  (set_local $5
   (i64.const 59)
  )
  (set_local $4
   (i32.const 1904)
  )
  (set_local $7
   (i64.const 0)
  )
  (loop $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (br_if $label$5
         (i64.gt_u
          (get_local $6)
          (i64.const 7)
         )
        )
        (br_if $label$4
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $3
             (i32.load8_s
              (get_local $4)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $3
         (i32.add
          (get_local $3)
          (i32.const 165)
         )
        )
        (br $label$3)
       )
       (set_local $8
        (i64.const 0)
       )
       (br_if $label$2
        (i64.le_u
         (get_local $6)
         (i64.const 11)
        )
       )
       (br $label$1)
      )
      (set_local $3
       (select
        (i32.add
         (get_local $3)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $3)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $8
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $3)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $8
     (i64.shl
      (i64.and
       (get_local $8)
       (i64.const 31)
      )
      (i64.and
       (get_local $5)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $4
    (i32.add
     (get_local $4)
     (i32.const 1)
    )
   )
   (set_local $6
    (i64.add
     (get_local $6)
     (i64.const 1)
    )
   )
   (set_local $7
    (i64.or
     (get_local $8)
     (get_local $7)
    )
   )
   (br_if $label$0
    (i64.ne
     (tee_local $5
      (i64.add
       (get_local $5)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (block $label$6
   (block $label$7
    (br_if $label$7
     (i64.ne
      (get_local $7)
      (get_local $2)
     )
    )
    (call $_ZN5eosio18unpack_action_dataINS_8currency8transferEEET_v
     (i32.add
      (get_local $9)
      (i32.const 48)
     )
    )
    (call $_ZN5eosio8exchange2onERKNS_8currency8transferEy
     (get_local $0)
     (i32.add
      (get_local $9)
      (i32.const 48)
     )
     (get_local $1)
    )
    (br_if $label$6
     (i32.eqz
      (i32.and
       (i32.load8_u offset=80
        (get_local $9)
       )
       (i32.const 1)
      )
     )
    )
    (call $_ZdlPv
     (i32.load
      (i32.add
       (get_local $9)
       (i32.const 88)
      )
     )
    )
    (br $label$6)
   )
   (br_if $label$6
    (i64.ne
     (i64.load
      (get_local $0)
     )
     (get_local $1)
    )
   )
   (block $label$8
    (block $label$9
     (block $label$10
      (block $label$11
       (block $label$12
        (block $label$13
         (block $label$14
          (block $label$15
           (br_if $label$15
            (i64.gt_s
             (get_local $2)
             (i64.const -2039333636196532225)
            )
           )
           (br_if $label$14
            (i64.gt_s
             (get_local $2)
             (i64.const -3106734271092490241)
            )
           )
           (br_if $label$12
            (i64.eq
             (get_local $2)
             (i64.const -8455912920667127808)
            )
           )
           (br_if $label$8
            (i64.ne
             (get_local $2)
             (i64.const -3617352573452812288)
            )
           )
           (call $_ZN5eosio18unpack_action_dataINS_8exchange5tradeEEET_v
            (i32.add
             (get_local $9)
             (i32.const 48)
            )
           )
           (call $_ZN5eosio8exchange2onERKNS0_5tradeE
            (get_local $0)
            (i32.add
             (get_local $9)
             (i32.const 48)
            )
           )
           (br $label$6)
          )
          (br_if $label$13
           (i64.gt_s
            (get_local $2)
            (i64.const 5031766168059248639)
           )
          )
          (br_if $label$11
           (i64.eq
            (get_local $2)
            (i64.const -2039333636196532224)
           )
          )
          (br_if $label$8
           (i64.ne
            (get_local $2)
            (i64.const 4987362516454843904)
           )
          )
          (call $_ZN5eosio18unpack_action_dataINS_8exchange11covermarginEEET_v
           (i32.add
            (get_local $9)
            (i32.const 48)
           )
          )
          (call $_ZN5eosio8exchange2onERKNS0_11covermarginE
           (get_local $0)
           (i32.add
            (get_local $9)
            (i32.const 48)
           )
          )
          (br $label$6)
         )
         (br_if $label$10
          (i64.eq
           (get_local $2)
           (i64.const -3106734271092490240)
          )
         )
         (br_if $label$8
          (i64.ne
           (get_local $2)
           (i64.const -3070210634466459648)
          )
         )
         (call $_ZN5eosio18unpack_action_dataINS_8exchange8upmarginEEET_v
          (i32.add
           (get_local $9)
           (i32.const 48)
          )
         )
         (call $_ZN5eosio8exchange2onERKNS0_8upmarginE
          (get_local $0)
          (i32.add
           (get_local $9)
           (i32.const 48)
          )
         )
         (br $label$6)
        )
        (br_if $label$9
         (i64.eq
          (get_local $2)
          (i64.const 5380477996647841792)
         )
        )
        (br_if $label$8
         (i64.ne
          (get_local $2)
          (i64.const 5031766168059248640)
         )
        )
        (i32.store offset=156
         (get_local $9)
         (i32.const 0)
        )
        (i32.store offset=152
         (get_local $9)
         (i32.const 1)
        )
        (i64.store offset=8 align=4
         (get_local $9)
         (i64.load offset=152
          (get_local $9)
         )
        )
        (drop
         (call $_ZN5eosio14execute_actionINS_8exchangeES1_JyNS_5assetEmNS_14extended_assetES3_EEEbPT_MT0_FvDpT1_E
          (get_local $0)
          (i32.add
           (get_local $9)
           (i32.const 8)
          )
         )
        )
        (br $label$8)
       )
       (i32.store offset=132
        (get_local $9)
        (i32.const 0)
       )
       (i32.store offset=128
        (get_local $9)
        (i32.const 2)
       )
       (i64.store offset=32 align=4
        (get_local $9)
        (i64.load offset=128
         (get_local $9)
        )
       )
       (drop
        (call $_ZN5eosio14execute_actionINS_8exchangeES1_JyNS_11symbol_typeENS_14extended_assetEEEEbPT_MT0_FvDpT1_E
         (get_local $0)
         (i32.add
          (get_local $9)
          (i32.const 32)
         )
        )
       )
       (br $label$8)
      )
      (i32.store offset=140
       (get_local $9)
       (i32.const 0)
      )
      (i32.store offset=136
       (get_local $9)
       (i32.const 3)
      )
      (i64.store offset=24 align=4
       (get_local $9)
       (i64.load offset=136
        (get_local $9)
       )
      )
      (drop
       (call $_ZN5eosio14execute_actionINS_8exchangeES1_JyNS_14extended_assetEEEEbPT_MT0_FvDpT1_E
        (get_local $0)
        (i32.add
         (get_local $9)
         (i32.const 24)
        )
       )
      )
      (br $label$8)
     )
     (i32.store offset=124
      (get_local $9)
      (i32.const 0)
     )
     (i32.store offset=120
      (get_local $9)
      (i32.const 4)
     )
     (i64.store offset=40 align=4
      (get_local $9)
      (i64.load offset=120
       (get_local $9)
      )
     )
     (drop
      (call $_ZN5eosio14execute_actionINS_8exchangeES1_JyNS_11symbol_typeEdNS_15extended_symbolEEEEbPT_MT0_FvDpT1_E
       (get_local $0)
       (i32.add
        (get_local $9)
        (i32.const 40)
       )
      )
     )
     (br $label$8)
    )
    (i32.store offset=148
     (get_local $9)
     (i32.const 0)
    )
    (i32.store offset=144
     (get_local $9)
     (i32.const 5)
    )
    (i64.store offset=16 align=4
     (get_local $9)
     (i64.load offset=144
      (get_local $9)
     )
    )
    (drop
     (call $_ZN5eosio14execute_actionINS_8exchangeES1_JyNS_14extended_assetEEEEbPT_MT0_FvDpT1_E
      (get_local $0)
      (i32.add
       (get_local $9)
       (i32.const 16)
      )
     )
    )
   )
   (drop
    (call $_ZN5eosio8currency5applyEyy
     (i32.add
      (get_local $0)
      (i32.const 8)
     )
     (get_local $1)
     (get_local $2)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 160)
   )
  )
 )
 (func $_ZN5eosio18unpack_action_dataINS_8currency8transferEEET_v (param $0 i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (set_local $6
   (tee_local $4
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $4)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.lt_u
      (tee_local $1
       (call $action_data_size)
      )
      (i32.const 513)
     )
    )
    (set_local $2
     (call $malloc
      (get_local $1)
     )
    )
    (br $label$0)
   )
   (i32.store offset=4
    (i32.const 0)
    (tee_local $2
     (i32.sub
      (get_local $4)
      (i32.and
       (i32.add
        (get_local $1)
        (i32.const 15)
       )
       (i32.const -16)
      )
     )
    )
   )
  )
  (drop
   (call $read_action_data
    (get_local $2)
    (get_local $1)
   )
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 24)
   )
   (i64.const 1398362884)
  )
  (i64.store offset=16
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $3
   (i64.const 5462355)
  )
  (set_local $4
   (i32.const 0)
  )
  (block $label$2
   (block $label$3
    (loop $label$4
     (br_if $label$3
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $3)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$5
      (br_if $label$5
       (i64.ne
        (i64.and
         (tee_local $3
          (i64.shr_u
           (get_local $3)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$6
       (br_if $label$3
        (i64.ne
         (i64.and
          (tee_local $3
           (i64.shr_u
            (get_local $3)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$6
        (i32.lt_s
         (tee_local $4
          (i32.add
           (get_local $4)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $5
      (i32.const 1)
     )
     (br_if $label$4
      (i32.lt_s
       (tee_local $4
        (i32.add
         (get_local $4)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$2)
    )
   )
   (set_local $5
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $5)
   (i32.const 80)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 40)
   )
   (i32.const 0)
  )
  (i64.store offset=32 align=4
   (get_local $0)
   (i64.const 0)
  )
  (i32.store offset=4
   (get_local $6)
   (get_local $2)
  )
  (i32.store
   (get_local $6)
   (get_local $2)
  )
  (i32.store offset=8
   (get_local $6)
   (i32.add
    (get_local $2)
    (get_local $1)
   )
  )
  (drop
   (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_8currency8transferE
    (get_local $6)
    (get_local $0)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $6)
    (i32.const 16)
   )
  )
 )
 (func $_ZN5eosio14execute_actionINS_8exchangeES1_JyNS_5assetEmNS_14extended_assetES3_EEEbPT_MT0_FvDpT1_E (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (set_local $10
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 336)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $8)
  )
  (set_local $2
   (i32.load offset=4
    (get_local $1)
   )
  )
  (set_local $9
   (i32.load
    (get_local $1)
   )
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.eqz
        (tee_local $1
         (call $action_data_size)
        )
       )
      )
      (br_if $label$2
       (i32.lt_u
        (get_local $1)
        (i32.const 513)
       )
      )
      (set_local $8
       (call $malloc
        (get_local $1)
       )
      )
      (br $label$1)
     )
     (set_local $8
      (i32.const 0)
     )
     (br $label$0)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $8
      (i32.sub
       (get_local $8)
       (i32.and
        (i32.add
         (get_local $1)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $read_action_data
     (get_local $8)
     (get_local $1)
    )
   )
  )
  (call $_ZN5eosio6unpackINSt3__15tupleIJyNS_5assetEmNS_14extended_assetES4_EEEEET_PKcj
   (i32.add
    (get_local $10)
    (i32.const 64)
   )
   (get_local $8)
   (get_local $1)
  )
  (block $label$4
   (br_if $label$4
    (i32.lt_u
     (get_local $1)
     (i32.const 513)
    )
   )
   (call $free
    (get_local $8)
   )
  )
  (i64.store
   (tee_local $1
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 192)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 64)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $3
   (i64.load offset=64
    (get_local $10)
   )
  )
  (i64.store offset=192
   (get_local $10)
   (i64.load offset=72
    (get_local $10)
   )
  )
  (set_local $8
   (i32.load offset=88
    (get_local $10)
   )
  )
  (i64.store
   (tee_local $4
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 168)
     )
     (i32.const 16)
    )
   )
   (i64.load
    (i32.add
     (get_local $10)
     (i32.const 112)
    )
   )
  )
  (i64.store
   (tee_local $5
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 168)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (get_local $10)
     (i32.const 104)
    )
   )
  )
  (i64.store offset=168
   (get_local $10)
   (i64.load offset=96
    (get_local $10)
   )
  )
  (i64.store
   (tee_local $6
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 144)
     )
     (i32.const 16)
    )
   )
   (i64.load
    (i32.add
     (get_local $10)
     (i32.const 136)
    )
   )
  )
  (i64.store
   (tee_local $7
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 144)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (get_local $10)
     (i32.const 128)
    )
   )
  )
  (i64.store offset=144
   (get_local $10)
   (i64.load offset=120
    (get_local $10)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 248)
    )
    (i32.const 16)
   )
   (i64.load
    (get_local $6)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 248)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $7)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 224)
    )
    (i32.const 16)
   )
   (i64.load
    (get_local $4)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 224)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $5)
   )
  )
  (i64.store offset=248
   (get_local $10)
   (i64.load offset=144
    (get_local $10)
   )
  )
  (i64.store offset=224
   (get_local $10)
   (i64.load offset=168
    (get_local $10)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 208)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=208
   (get_local $10)
   (i64.load offset=192
    (get_local $10)
   )
  )
  (set_local $1
   (i32.add
    (get_local $0)
    (i32.shr_s
     (get_local $2)
     (i32.const 1)
    )
   )
  )
  (block $label$5
   (br_if $label$5
    (i32.eqz
     (i32.and
      (get_local $2)
      (i32.const 1)
     )
    )
   )
   (set_local $9
    (i32.load
     (i32.add
      (i32.load
       (get_local $1)
      )
      (get_local $9)
     )
    )
   )
  )
  (i64.store
   (tee_local $2
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 320)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 208)
     )
     (i32.const 8)
    )
   )
  )
  (i64.store
   (tee_local $0
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 296)
     )
     (i32.const 16)
    )
   )
   (i64.load
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 224)
     )
     (i32.const 16)
    )
   )
  )
  (i64.store
   (tee_local $4
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 296)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 224)
     )
     (i32.const 8)
    )
   )
  )
  (i64.store offset=320
   (get_local $10)
   (i64.load offset=208
    (get_local $10)
   )
  )
  (i64.store offset=296
   (get_local $10)
   (i64.load offset=224
    (get_local $10)
   )
  )
  (i64.store
   (tee_local $5
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 272)
     )
     (i32.const 16)
    )
   )
   (i64.load
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 248)
     )
     (i32.const 16)
    )
   )
  )
  (i64.store
   (tee_local $6
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 272)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 248)
     )
     (i32.const 8)
    )
   )
  )
  (i64.store offset=272
   (get_local $10)
   (i64.load offset=248
    (get_local $10)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 48)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $2)
   )
  )
  (i64.store offset=48
   (get_local $10)
   (i64.load offset=320
    (get_local $10)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 24)
    )
    (i32.const 16)
   )
   (i64.load
    (get_local $0)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 24)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $4)
   )
  )
  (i64.store offset=24
   (get_local $10)
   (i64.load offset=296
    (get_local $10)
   )
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 16)
   )
   (i64.load
    (get_local $5)
   )
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 8)
   )
   (i64.load
    (get_local $6)
   )
  )
  (i64.store
   (get_local $10)
   (i64.load offset=272
    (get_local $10)
   )
  )
  (call_indirect (type $FUNCSIG$vijiiii)
   (get_local $1)
   (get_local $3)
   (i32.add
    (get_local $10)
    (i32.const 48)
   )
   (get_local $8)
   (i32.add
    (get_local $10)
    (i32.const 24)
   )
   (get_local $10)
   (get_local $9)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 336)
   )
  )
  (i32.const 1)
 )
 (func $_ZN5eosio14execute_actionINS_8exchangeES1_JyNS_14extended_assetEEEEbPT_MT0_FvDpT1_E (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i64)
  (local $7 i32)
  (local $8 i64)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (set_local $11
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 128)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $9)
  )
  (set_local $2
   (i32.load offset=4
    (get_local $1)
   )
  )
  (set_local $10
   (i32.load
    (get_local $1)
   )
  )
  (set_local $1
   (i32.const 0)
  )
  (set_local $7
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (tee_local $3
      (call $action_data_size)
     )
    )
   )
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i32.lt_u
       (get_local $3)
       (i32.const 513)
      )
     )
     (set_local $7
      (call $malloc
       (get_local $3)
      )
     )
     (br $label$1)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $7
      (i32.sub
       (get_local $9)
       (i32.and
        (i32.add
         (get_local $3)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $read_action_data
     (get_local $7)
     (get_local $3)
    )
   )
  )
  (i64.store
   (tee_local $4
    (i32.add
     (i32.add
      (get_local $11)
      (i32.const 24)
     )
     (i32.const 24)
    )
   )
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $11)
    (i32.const 40)
   )
   (i64.const 1398362884)
  )
  (i64.store offset=24
   (get_local $11)
   (i64.const 0)
  )
  (i64.store offset=32
   (get_local $11)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $8
   (i64.const 5462355)
  )
  (block $label$3
   (loop $label$4
    (set_local $9
     (i32.const 0)
    )
    (br_if $label$3
     (i32.gt_u
      (i32.add
       (i32.shl
        (i32.wrap/i64
         (get_local $8)
        )
        (i32.const 24)
       )
       (i32.const -1073741825)
      )
      (i32.const 452984830)
     )
    )
    (block $label$5
     (br_if $label$5
      (i64.ne
       (i64.and
        (tee_local $8
         (i64.shr_u
          (get_local $8)
          (i64.const 8)
         )
        )
        (i64.const 255)
       )
       (i64.const 0)
      )
     )
     (loop $label$6
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $8
          (i64.shr_u
           (get_local $8)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (br_if $label$6
       (i32.lt_s
        (tee_local $1
         (i32.add
          (get_local $1)
          (i32.const 1)
         )
        )
        (i32.const 7)
       )
      )
     )
    )
    (set_local $9
     (i32.const 1)
    )
    (br_if $label$4
     (i32.lt_s
      (tee_local $1
       (i32.add
        (get_local $1)
        (i32.const 1)
       )
      )
      (i32.const 7)
     )
    )
   )
  )
  (call $eosio_assert
   (get_local $9)
   (i32.const 80)
  )
  (call $eosio_assert
   (i32.gt_u
    (get_local $3)
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $11)
     (i32.const 24)
    )
    (get_local $7)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (tee_local $9
     (i32.and
      (get_local $3)
      (i32.const -8)
     )
    )
    (i32.const 8)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (tee_local $1
     (i32.add
      (i32.add
       (get_local $11)
       (i32.const 24)
      )
      (i32.const 8)
     )
    )
    (i32.add
     (get_local $7)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $9)
    (i32.const 16)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (i32.add
      (get_local $11)
      (i32.const 24)
     )
     (i32.const 16)
    )
    (i32.add
     (get_local $7)
     (i32.const 16)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $9)
    (i32.const 24)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $4)
    (i32.add
     (get_local $7)
     (i32.const 24)
    )
    (i32.const 8)
   )
  )
  (block $label$7
   (br_if $label$7
    (i32.lt_u
     (get_local $3)
     (i32.const 513)
    )
   )
   (call $free
    (get_local $7)
   )
  )
  (i64.store
   (tee_local $9
    (i32.add
     (i32.add
      (get_local $11)
      (i32.const 56)
     )
     (i32.const 16)
    )
   )
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
   )
  )
  (i64.store
   (tee_local $7
    (i32.add
     (i32.add
      (get_local $11)
      (i32.const 56)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
   )
  )
  (set_local $8
   (i64.load offset=24
    (get_local $11)
   )
  )
  (i64.store offset=56
   (get_local $11)
   (i64.load
    (get_local $1)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 80)
    )
    (i32.const 16)
   )
   (i64.load
    (get_local $9)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 80)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $7)
   )
  )
  (i64.store offset=80
   (get_local $11)
   (i64.load offset=56
    (get_local $11)
   )
  )
  (set_local $1
   (i32.add
    (get_local $0)
    (i32.shr_s
     (get_local $2)
     (i32.const 1)
    )
   )
  )
  (block $label$8
   (br_if $label$8
    (i32.eqz
     (i32.and
      (get_local $2)
      (i32.const 1)
     )
    )
   )
   (set_local $10
    (i32.load
     (i32.add
      (i32.load
       (get_local $1)
      )
      (get_local $10)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 104)
    )
    (i32.const 16)
   )
   (tee_local $5
    (i64.load
     (i32.add
      (i32.add
       (get_local $11)
       (i32.const 80)
      )
      (i32.const 16)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $11)
     (i32.const 104)
    )
    (i32.const 8)
   )
   (tee_local $6
    (i64.load
     (i32.add
      (i32.add
       (get_local $11)
       (i32.const 80)
      )
      (i32.const 8)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $11)
    (i32.const 16)
   )
   (get_local $5)
  )
  (i64.store
   (i32.add
    (get_local $11)
    (i32.const 8)
   )
   (get_local $6)
  )
  (i64.store offset=104
   (get_local $11)
   (tee_local $5
    (i64.load offset=80
     (get_local $11)
    )
   )
  )
  (i64.store
   (get_local $11)
   (get_local $5)
  )
  (call_indirect (type $FUNCSIG$viji)
   (get_local $1)
   (get_local $8)
   (get_local $11)
   (get_local $10)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $11)
    (i32.const 128)
   )
  )
  (i32.const 1)
 )
 (func $_ZN5eosio14execute_actionINS_8exchangeES1_JyNS_11symbol_typeENS_14extended_assetEEEEbPT_MT0_FvDpT1_E (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i64)
  (local $5 i64)
  (local $6 i64)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (set_local $9
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 144)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $7)
  )
  (set_local $2
   (i32.load offset=4
    (get_local $1)
   )
  )
  (set_local $8
   (i32.load
    (get_local $1)
   )
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.eqz
        (tee_local $1
         (call $action_data_size)
        )
       )
      )
      (br_if $label$2
       (i32.lt_u
        (get_local $1)
        (i32.const 513)
       )
      )
      (set_local $7
       (call $malloc
        (get_local $1)
       )
      )
      (br $label$1)
     )
     (set_local $7
      (i32.const 0)
     )
     (br $label$0)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $7
      (i32.sub
       (get_local $7)
       (i32.and
        (i32.add
         (get_local $1)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $read_action_data
     (get_local $7)
     (get_local $1)
    )
   )
  )
  (call $_ZN5eosio6unpackINSt3__15tupleIJyNS_11symbol_typeENS_14extended_assetEEEEEET_PKcj
   (i32.add
    (get_local $9)
    (i32.const 32)
   )
   (get_local $7)
   (get_local $1)
  )
  (block $label$4
   (br_if $label$4
    (i32.lt_u
     (get_local $1)
     (i32.const 513)
    )
   )
   (call $free
    (get_local $7)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 72)
    )
    (i32.const 20)
   )
   (i32.load
    (i32.add
     (get_local $9)
     (i32.const 68)
    )
   )
  )
  (i32.store
   (tee_local $1
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 72)
     )
     (i32.const 16)
    )
   )
   (i32.load
    (i32.add
     (get_local $9)
     (i32.const 64)
    )
   )
  )
  (set_local $4
   (i64.load offset=40
    (get_local $9)
   )
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 84)
   )
   (i32.load
    (i32.add
     (get_local $9)
     (i32.const 60)
    )
   )
  )
  (i32.store
   (tee_local $7
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 72)
     )
     (i32.const 8)
    )
   )
   (i32.load
    (i32.add
     (get_local $9)
     (i32.const 56)
    )
   )
  )
  (set_local $3
   (i64.load offset=32
    (get_local $9)
   )
  )
  (i32.store offset=72
   (get_local $9)
   (i32.load offset=48
    (get_local $9)
   )
  )
  (i32.store offset=76
   (get_local $9)
   (i32.load
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 32)
     )
     (i32.const 20)
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 96)
    )
    (i32.const 16)
   )
   (i64.load
    (get_local $1)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 96)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $7)
   )
  )
  (i64.store offset=96
   (get_local $9)
   (i64.load offset=72
    (get_local $9)
   )
  )
  (set_local $1
   (i32.add
    (get_local $0)
    (i32.shr_s
     (get_local $2)
     (i32.const 1)
    )
   )
  )
  (block $label$5
   (br_if $label$5
    (i32.eqz
     (i32.and
      (get_local $2)
      (i32.const 1)
     )
    )
   )
   (set_local $8
    (i32.load
     (i32.add
      (i32.load
       (get_local $1)
      )
      (get_local $8)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 120)
    )
    (i32.const 16)
   )
   (tee_local $5
    (i64.load
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 96)
      )
      (i32.const 16)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 120)
    )
    (i32.const 8)
   )
   (tee_local $6
    (i64.load
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 96)
      )
      (i32.const 8)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 8)
    )
    (i32.const 16)
   )
   (get_local $5)
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 8)
    )
    (i32.const 8)
   )
   (get_local $6)
  )
  (i64.store offset=120
   (get_local $9)
   (tee_local $5
    (i64.load offset=96
     (get_local $9)
    )
   )
  )
  (i64.store offset=8
   (get_local $9)
   (get_local $5)
  )
  (call_indirect (type $FUNCSIG$vijji)
   (get_local $1)
   (get_local $3)
   (get_local $4)
   (i32.add
    (get_local $9)
    (i32.const 8)
   )
   (get_local $8)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 144)
   )
  )
  (i32.const 1)
 )
 (func $_ZN5eosio14execute_actionINS_8exchangeES1_JyNS_11symbol_typeEdNS_15extended_symbolEEEEbPT_MT0_FvDpT1_E (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i64)
  (local $6 f64)
  (local $7 i64)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (set_local $9
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 112)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $10)
  )
  (set_local $2
   (i32.load offset=4
    (get_local $1)
   )
  )
  (set_local $8
   (i32.load
    (get_local $1)
   )
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.eqz
        (tee_local $3
         (call $action_data_size)
        )
       )
      )
      (br_if $label$2
       (i32.lt_u
        (get_local $3)
        (i32.const 513)
       )
      )
      (set_local $1
       (call $malloc
        (get_local $3)
       )
      )
      (br $label$1)
     )
     (set_local $1
      (i32.const 0)
     )
     (br $label$0)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $1
      (i32.sub
       (get_local $10)
       (i32.and
        (i32.add
         (get_local $3)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $read_action_data
     (get_local $1)
     (get_local $3)
    )
   )
  )
  (i64.store
   (tee_local $10
    (i32.add
     (get_local $9)
     (i32.const 56)
    )
   )
   (i64.const 0)
  )
  (i64.store offset=40
   (get_local $9)
   (i64.const 0)
  )
  (i64.store offset=24
   (get_local $9)
   (i64.const 0)
  )
  (i64.store offset=48
   (get_local $9)
   (i64.const 0)
  )
  (i32.store offset=100
   (get_local $9)
   (get_local $1)
  )
  (i32.store offset=96
   (get_local $9)
   (get_local $1)
  )
  (i32.store offset=104
   (get_local $9)
   (i32.add
    (get_local $1)
    (get_local $3)
   )
  )
  (i32.store offset=64
   (get_local $9)
   (i32.add
    (get_local $9)
    (i32.const 96)
   )
  )
  (i32.store offset=80
   (get_local $9)
   (i32.add
    (get_local $9)
    (i32.const 24)
   )
  )
  (call $_ZN5boost6fusion6detail17for_each_unrolledILi4EE4callINS0_18std_tuple_iteratorINSt3__15tupleIJyN5eosio11symbol_typeEdNS8_15extended_symbolEEEELi0EEEZNS8_rsINS8_10datastreamIPKcEEJyS9_dSA_EEERT_SJ_RNS7_IJDpT0_EEEEUlSJ_E_EEvRKSI_RKT0_
   (i32.add
    (get_local $9)
    (i32.const 80)
   )
   (i32.add
    (get_local $9)
    (i32.const 64)
   )
  )
  (block $label$4
   (br_if $label$4
    (i32.lt_u
     (get_local $3)
     (i32.const 513)
    )
   )
   (call $free
    (get_local $1)
   )
  )
  (set_local $5
   (i64.load offset=32
    (get_local $9)
   )
  )
  (i32.store
   (i32.add
    (get_local $9)
    (i32.const 76)
   )
   (i32.load
    (i32.add
     (get_local $9)
     (i32.const 60)
    )
   )
  )
  (i32.store
   (tee_local $1
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 64)
     )
     (i32.const 8)
    )
   )
   (i32.load
    (get_local $10)
   )
  )
  (set_local $4
   (i64.load offset=24
    (get_local $9)
   )
  )
  (i32.store offset=64
   (get_local $9)
   (i32.load offset=48
    (get_local $9)
   )
  )
  (i32.store offset=68
   (get_local $9)
   (i32.load
    (i32.add
     (get_local $9)
     (i32.const 52)
    )
   )
  )
  (set_local $6
   (f64.load
    (i32.add
     (get_local $9)
     (i32.const 40)
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 80)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=80
   (get_local $9)
   (i64.load offset=64
    (get_local $9)
   )
  )
  (set_local $1
   (i32.add
    (get_local $0)
    (i32.shr_s
     (get_local $2)
     (i32.const 1)
    )
   )
  )
  (block $label$5
   (br_if $label$5
    (i32.eqz
     (i32.and
      (get_local $2)
      (i32.const 1)
     )
    )
   )
   (set_local $8
    (i32.load
     (i32.add
      (i32.load
       (get_local $1)
      )
      (get_local $8)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 96)
    )
    (i32.const 8)
   )
   (tee_local $7
    (i64.load
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 80)
      )
      (i32.const 8)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 8)
    )
    (i32.const 8)
   )
   (get_local $7)
  )
  (i64.store offset=96
   (get_local $9)
   (tee_local $7
    (i64.load offset=80
     (get_local $9)
    )
   )
  )
  (i64.store offset=8
   (get_local $9)
   (get_local $7)
  )
  (call_indirect (type $FUNCSIG$vijjdi)
   (get_local $1)
   (get_local $4)
   (get_local $5)
   (get_local $6)
   (i32.add
    (get_local $9)
    (i32.const 8)
   )
   (get_local $8)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 112)
   )
  )
  (i32.const 1)
 )
 (func $_ZN5eosio18unpack_action_dataINS_8exchange5tradeEEET_v (param $0 i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (set_local $4
   (tee_local $2
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $2)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.lt_u
      (tee_local $1
       (call $action_data_size)
      )
      (i32.const 513)
     )
    )
    (set_local $3
     (call $malloc
      (get_local $1)
     )
    )
    (br $label$0)
   )
   (i32.store offset=4
    (i32.const 0)
    (tee_local $3
     (i32.sub
      (get_local $2)
      (i32.and
       (i32.add
        (get_local $1)
        (i32.const 15)
       )
       (i32.const -16)
      )
     )
    )
   )
  )
  (drop
   (call $read_action_data
    (get_local $3)
    (get_local $1)
   )
  )
  (set_local $2
   (call $_ZN5eosio8exchange5tradeC2Ev
    (get_local $0)
   )
  )
  (i32.store offset=4
   (get_local $4)
   (get_local $3)
  )
  (i32.store
   (get_local $4)
   (get_local $3)
  )
  (i32.store offset=8
   (get_local $4)
   (i32.add
    (get_local $3)
    (get_local $1)
   )
  )
  (i32.store offset=16
   (get_local $4)
   (get_local $4)
  )
  (i32.store offset=28
   (get_local $4)
   (i32.add
    (get_local $2)
    (i32.const 8)
   )
  )
  (i32.store offset=24
   (get_local $4)
   (get_local $2)
  )
  (i32.store offset=32
   (get_local $4)
   (i32.add
    (get_local $2)
    (i32.const 16)
   )
  )
  (i32.store offset=36
   (get_local $4)
   (i32.add
    (get_local $2)
    (i32.const 40)
   )
  )
  (i32.store offset=40
   (get_local $4)
   (i32.add
    (get_local $2)
    (i32.const 64)
   )
  )
  (i32.store offset=44
   (get_local $4)
   (i32.add
    (get_local $2)
    (i32.const 68)
   )
  )
  (call $_ZN5boost3pfr6detail19for_each_field_implINS1_14sequence_tuple5tupleIJRyRN5eosio11symbol_typeERNS6_14extended_assetESA_RmRhEEEZNS6_rsINS6_10datastreamIPKcEENS6_8exchange5tradeELPv0EEERT_SN_RT0_EUlSN_E_JLj0ELj1ELj2ELj3ELj4ELj5EEEEvSN_OSO_NSt3__116integer_sequenceIjJXspT1_EEEENSS_17integral_constantIbLb0EEE
   (i32.add
    (get_local $4)
    (i32.const 24)
   )
   (i32.add
    (get_local $4)
    (i32.const 16)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $4)
    (i32.const 48)
   )
  )
 )
 (func $_ZN5eosio18unpack_action_dataINS_8exchange8upmarginEEET_v (param $0 i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i32)
  (set_local $3
   (tee_local $2
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $2)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.lt_u
      (tee_local $1
       (call $action_data_size)
      )
      (i32.const 513)
     )
    )
    (set_local $2
     (call $malloc
      (get_local $1)
     )
    )
    (br $label$0)
   )
   (i32.store offset=4
    (i32.const 0)
    (tee_local $2
     (i32.sub
      (get_local $2)
      (i32.and
       (i32.add
        (get_local $1)
        (i32.const 15)
       )
       (i32.const -16)
      )
     )
    )
   )
  )
  (drop
   (call $read_action_data
    (get_local $2)
    (get_local $1)
   )
  )
  (set_local $0
   (call $_ZN5eosio8exchange8upmarginC2Ev
    (get_local $0)
   )
  )
  (i32.store offset=12
   (get_local $3)
   (get_local $2)
  )
  (i32.store offset=8
   (get_local $3)
   (get_local $2)
  )
  (i32.store offset=16
   (get_local $3)
   (i32.add
    (get_local $2)
    (get_local $1)
   )
  )
  (i32.store offset=24
   (get_local $3)
   (i32.add
    (get_local $3)
    (i32.const 8)
   )
  )
  (i32.store offset=36
   (get_local $3)
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (i32.store offset=32
   (get_local $3)
   (get_local $0)
  )
  (i32.store offset=40
   (get_local $3)
   (i32.add
    (get_local $0)
    (i32.const 16)
   )
  )
  (i32.store offset=44
   (get_local $3)
   (i32.add
    (get_local $0)
    (i32.const 40)
   )
  )
  (call $_ZN5boost3pfr6detail19for_each_field_implINS1_14sequence_tuple5tupleIJRyRN5eosio11symbol_typeERNS6_14extended_assetESA_EEEZNS6_rsINS6_10datastreamIPKcEENS6_8exchange8upmarginELPv0EEERT_SL_RT0_EUlSL_E_JLj0ELj1ELj2ELj3EEEEvSL_OSM_NSt3__116integer_sequenceIjJXspT1_EEEENSQ_17integral_constantIbLb0EEE
   (i32.add
    (get_local $3)
    (i32.const 32)
   )
   (i32.add
    (get_local $3)
    (i32.const 24)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $3)
    (i32.const 48)
   )
  )
 )
 (func $_ZN5eosio18unpack_action_dataINS_8exchange11covermarginEEET_v (param $0 i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i32)
  (set_local $3
   (tee_local $2
    (i32.load offset=4
     (i32.const 0)
    )
   )
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.lt_u
      (tee_local $1
       (call $action_data_size)
      )
      (i32.const 513)
     )
    )
    (set_local $2
     (call $malloc
      (get_local $1)
     )
    )
    (br $label$0)
   )
   (i32.store offset=4
    (i32.const 0)
    (tee_local $2
     (i32.sub
      (get_local $2)
      (i32.and
       (i32.add
        (get_local $1)
        (i32.const 15)
       )
       (i32.const -16)
      )
     )
    )
   )
  )
  (drop
   (call $read_action_data
    (get_local $2)
    (get_local $1)
   )
  )
  (call $_ZN5eosio6unpackINS_8exchange11covermarginEEET_PKcj
   (get_local $0)
   (get_local $2)
   (get_local $1)
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $3)
  )
 )
 (func $_ZN5eosio8currency5applyEyy (param $0 i32) (param $1 i64) (param $2 i64) (result i32)
  (local $3 i32)
  (local $4 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $4
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (set_local $3
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i64.ne
     (i64.load
      (get_local $0)
     )
     (get_local $1)
    )
   )
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i64.eq
       (get_local $2)
       (i64.const -3617168760277827584)
      )
     )
     (br_if $label$1
      (i64.eq
       (get_local $2)
       (i64.const 5031766152489992192)
      )
     )
     (br_if $label$0
      (i64.ne
       (get_local $2)
       (i64.const 8516769789752901632)
      )
     )
     (call $prints
      (i32.const 3568)
     )
     (call $_ZN5eosio18unpack_action_dataINS_8currency5issueEEET_v
      (get_local $4)
     )
     (call $_ZN5eosio8currency2onERKNS0_5issueE
      (get_local $0)
      (get_local $4)
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$0
      (i32.eqz
       (i32.and
        (i32.load8_u offset=24
         (get_local $4)
        )
        (i32.const 1)
       )
      )
     )
     (call $_ZdlPv
      (i32.load
       (i32.add
        (get_local $4)
        (i32.const 32)
       )
      )
     )
     (br $label$0)
    )
    (call $prints
     (i32.const 3584)
    )
    (call $_ZN5eosio18unpack_action_dataINS_8currency8transferEEET_v
     (get_local $4)
    )
    (call $_ZN5eosio8currency2onERKNS0_8transferE
     (get_local $0)
     (get_local $4)
    )
    (set_local $3
     (i32.const 1)
    )
    (br_if $label$0
     (i32.eqz
      (i32.and
       (i32.load8_u offset=32
        (get_local $4)
       )
       (i32.const 1)
      )
     )
    )
    (call $_ZdlPv
     (i32.load
      (i32.add
       (get_local $4)
       (i32.const 40)
      )
     )
    )
    (br $label$0)
   )
   (call $prints
    (i32.const 3600)
   )
   (call $_ZN5eosio18unpack_action_dataINS_8currency6createEEET_v
    (get_local $4)
   )
   (call $require_auth
    (i64.load
     (get_local $4)
    )
   )
   (call $_ZN5eosio8currency15create_currencyERKNS0_6createE
    (get_local $0)
    (get_local $4)
   )
   (set_local $3
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $4)
    (i32.const 48)
   )
  )
  (get_local $3)
 )
 (func $_ZN5eosio18unpack_action_dataINS_8currency5issueEEET_v (param $0 i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (set_local $6
   (tee_local $4
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $4)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.lt_u
      (tee_local $1
       (call $action_data_size)
      )
      (i32.const 513)
     )
    )
    (set_local $2
     (call $malloc
      (get_local $1)
     )
    )
    (br $label$0)
   )
   (i32.store offset=4
    (i32.const 0)
    (tee_local $2
     (i32.sub
      (get_local $4)
      (i32.and
       (i32.add
        (get_local $1)
        (i32.const 15)
       )
       (i32.const -16)
      )
     )
    )
   )
  )
  (drop
   (call $read_action_data
    (get_local $2)
    (get_local $1)
   )
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 16)
   )
   (i64.const 1398362884)
  )
  (i64.store offset=8
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $3
   (i64.const 5462355)
  )
  (set_local $4
   (i32.const 0)
  )
  (block $label$2
   (block $label$3
    (loop $label$4
     (br_if $label$3
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $3)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$5
      (br_if $label$5
       (i64.ne
        (i64.and
         (tee_local $3
          (i64.shr_u
           (get_local $3)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$6
       (br_if $label$3
        (i64.ne
         (i64.and
          (tee_local $3
           (i64.shr_u
            (get_local $3)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$6
        (i32.lt_s
         (tee_local $4
          (i32.add
           (get_local $4)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $5
      (i32.const 1)
     )
     (br_if $label$4
      (i32.lt_s
       (tee_local $4
        (i32.add
         (get_local $4)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$2)
    )
   )
   (set_local $5
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $5)
   (i32.const 80)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 32)
   )
   (i32.const 0)
  )
  (i64.store offset=24 align=4
   (get_local $0)
   (i64.const 0)
  )
  (i32.store
   (get_local $6)
   (get_local $2)
  )
  (i32.store offset=8
   (get_local $6)
   (tee_local $4
    (i32.add
     (get_local $2)
     (get_local $1)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (get_local $1)
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $0)
    (get_local $2)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (get_local $4)
     (tee_local $5
      (i32.add
       (get_local $2)
       (i32.const 8)
      )
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
    (get_local $5)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (get_local $4)
     (tee_local $5
      (i32.add
       (get_local $2)
       (i32.const 16)
      )
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (get_local $5)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $6)
   (i32.add
    (get_local $2)
    (i32.const 24)
   )
  )
  (drop
   (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNSt3__112basic_stringIcNS7_11char_traitsIcEENS7_9allocatorIcEEEE
    (get_local $6)
    (i32.add
     (get_local $0)
     (i32.const 24)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $6)
    (i32.const 16)
   )
  )
 )
 (func $_ZN5eosio8currency2onERKNS0_5issueE (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i64)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
  (local $8 i64)
  (local $9 i64)
  (local $10 i64)
  (local $11 i32)
  (local $12 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $12
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 128)
    )
   )
  )
  (set_local $8
   (i64.load
    (tee_local $11
     (i32.add
      (get_local $1)
      (i32.const 16)
     )
    )
   )
  )
  (set_local $6
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 88)
    )
    (i32.const 32)
   )
   (i32.const 0)
  )
  (i64.store offset=104
   (get_local $12)
   (i64.const -1)
  )
  (i64.store offset=112
   (get_local $12)
   (i64.const 0)
  )
  (i64.store offset=88
   (get_local $12)
   (i64.load
    (get_local $0)
   )
  )
  (i64.store offset=96
   (get_local $12)
   (tee_local $8
    (i64.shr_u
     (get_local $8)
     (i64.const 8)
    )
   )
  )
  (call $require_auth
   (i64.load offset=32
    (tee_local $2
     (call $_ZNK5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE3getEyPKc
      (i32.add
       (get_local $12)
       (i32.const 88)
      )
      (get_local $8)
      (i32.const 2224)
     )
    )
   )
  )
  (set_local $5
   (i32.add
    (get_local $1)
    (i32.const 8)
   )
  )
  (block $label$0
   (br_if $label$0
    (i64.gt_u
     (i64.add
      (i64.load offset=8
       (get_local $1)
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $8
    (i64.shr_u
     (i64.load
      (get_local $11)
     )
     (i64.const 8)
    )
   )
   (set_local $11
    (i32.const 0)
   )
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $8)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $8
          (i64.shr_u
           (get_local $8)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $8
           (i64.shr_u
            (get_local $8)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $11
          (i32.add
           (get_local $11)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $6
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $11
        (i32.add
         (get_local $11)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $6
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $6)
   (i32.const 1840)
  )
  (call $eosio_assert
   (i64.gt_s
    (i64.load
     (get_local $5)
    )
    (i64.const 0)
   )
   (i32.const 3616)
  )
  (i32.store offset=80
   (get_local $12)
   (get_local $1)
  )
  (call $_ZN5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE6modifyIZNS1_2onERKNS1_5issueEEUlRT_E_EEvRKS2_yOS8_
   (i32.add
    (get_local $12)
    (i32.const 88)
   )
   (get_local $2)
   (i64.const 0)
   (i32.add
    (get_local $12)
    (i32.const 80)
   )
  )
  (set_local $8
   (i64.load
    (tee_local $11
     (i32.add
      (get_local $2)
      (i32.const 32)
     )
    )
   )
  )
  (i64.store
   (tee_local $6
    (i32.add
     (i32.add
      (get_local $12)
      (i32.const 64)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (get_local $5)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=64
   (get_local $12)
   (i64.load
    (get_local $5)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 16)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $6)
   )
  )
  (i32.store offset=16
   (get_local $12)
   (i32.load offset=64
    (get_local $12)
   )
  )
  (i32.store offset=20
   (get_local $12)
   (i32.load offset=68
    (get_local $12)
   )
  )
  (call $_ZN5eosio8currency11add_balanceEyNS_5assetERKNS0_14currency_statsEy
   (get_local $0)
   (get_local $8)
   (i32.add
    (get_local $12)
    (i32.const 16)
   )
   (get_local $2)
   (get_local $8)
  )
  (block $label$5
   (br_if $label$5
    (i64.eq
     (tee_local $3
      (i64.load
       (get_local $1)
      )
     )
     (tee_local $4
      (i64.load
       (get_local $11)
      )
     )
    )
   )
   (i64.store
    (i32.add
     (i32.add
      (get_local $12)
      (i32.const 48)
     )
     (i32.const 8)
    )
    (i64.load
     (i32.add
      (get_local $5)
      (i32.const 8)
     )
    )
   )
   (i64.store offset=48
    (get_local $12)
    (i64.load
     (get_local $5)
    )
   )
   (drop
    (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2ERKS5_
     (i32.add
      (get_local $12)
      (i32.const 32)
     )
     (i32.add
      (get_local $1)
      (i32.const 24)
     )
    )
   )
   (set_local $8
    (i64.const 0)
   )
   (set_local $7
    (i64.const 59)
   )
   (set_local $11
    (i32.const 1888)
   )
   (set_local $9
    (i64.const 0)
   )
   (loop $label$6
    (block $label$7
     (block $label$8
      (block $label$9
       (block $label$10
        (block $label$11
         (br_if $label$11
          (i64.gt_u
           (get_local $8)
           (i64.const 5)
          )
         )
         (br_if $label$10
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $1
              (i32.load8_s
               (get_local $11)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $1
          (i32.add
           (get_local $1)
           (i32.const 165)
          )
         )
         (br $label$9)
        )
        (set_local $10
         (i64.const 0)
        )
        (br_if $label$8
         (i64.le_u
          (get_local $8)
          (i64.const 11)
         )
        )
        (br $label$7)
       )
       (set_local $1
        (select
         (i32.add
          (get_local $1)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $1)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $10
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $1)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $10
      (i64.shl
       (i64.and
        (get_local $10)
        (i64.const 31)
       )
       (i64.and
        (get_local $7)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $11
     (i32.add
      (get_local $11)
      (i32.const 1)
     )
    )
    (set_local $8
     (i64.add
      (get_local $8)
      (i64.const 1)
     )
    )
    (set_local $9
     (i64.or
      (get_local $10)
      (get_local $9)
     )
    )
    (br_if $label$6
     (i64.ne
      (tee_local $7
       (i64.add
        (get_local $7)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
    (i64.load
     (i32.add
      (i32.add
       (get_local $12)
       (i32.const 48)
      )
      (i32.const 8)
     )
    )
   )
   (i64.store
    (get_local $12)
    (i64.load offset=48
     (get_local $12)
    )
   )
   (call $_ZN5eosio8currency15inline_transferEyyNS_5assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEy
    (get_local $0)
    (get_local $4)
    (get_local $3)
    (get_local $12)
    (i32.add
     (get_local $12)
     (i32.const 32)
    )
    (get_local $9)
   )
   (br_if $label$5
    (i32.eqz
     (i32.and
      (i32.load8_u offset=32
       (get_local $12)
      )
      (i32.const 1)
     )
    )
   )
   (call $_ZdlPv
    (i32.load offset=40
     (get_local $12)
    )
   )
  )
  (block $label$12
   (br_if $label$12
    (i32.eqz
     (tee_local $5
      (i32.load offset=112
       (get_local $12)
      )
     )
    )
   )
   (block $label$13
    (block $label$14
     (br_if $label$14
      (i32.eq
       (tee_local $11
        (i32.load
         (tee_local $6
          (i32.add
           (get_local $12)
           (i32.const 116)
          )
         )
        )
       )
       (get_local $5)
      )
     )
     (loop $label$15
      (set_local $1
       (i32.load
        (tee_local $11
         (i32.add
          (get_local $11)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $11)
       (i32.const 0)
      )
      (block $label$16
       (br_if $label$16
        (i32.eqz
         (get_local $1)
        )
       )
       (call $_ZdlPv
        (get_local $1)
       )
      )
      (br_if $label$15
       (i32.ne
        (get_local $5)
        (get_local $11)
       )
      )
     )
     (set_local $11
      (i32.load
       (i32.add
        (get_local $12)
        (i32.const 112)
       )
      )
     )
     (br $label$13)
    )
    (set_local $11
     (get_local $5)
    )
   )
   (i32.store
    (get_local $6)
    (get_local $5)
   )
   (call $_ZdlPv
    (get_local $11)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $12)
    (i32.const 128)
   )
  )
 )
 (func $_ZN5eosio18unpack_action_dataINS_8currency6createEEET_v (param $0 i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (set_local $6
   (tee_local $4
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $4)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.lt_u
      (tee_local $1
       (call $action_data_size)
      )
      (i32.const 513)
     )
    )
    (set_local $2
     (call $malloc
      (get_local $1)
     )
    )
    (br $label$0)
   )
   (i32.store offset=4
    (i32.const 0)
    (tee_local $2
     (i32.sub
      (get_local $4)
      (i32.and
       (i32.add
        (get_local $1)
        (i32.const 15)
       )
       (i32.const -16)
      )
     )
    )
   )
  )
  (drop
   (call $read_action_data
    (get_local $2)
    (get_local $1)
   )
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 16)
   )
   (i64.const 1398362884)
  )
  (i64.store offset=8
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $3
   (i64.const 5462355)
  )
  (set_local $4
   (i32.const 0)
  )
  (block $label$2
   (block $label$3
    (loop $label$4
     (br_if $label$3
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $3)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$5
      (br_if $label$5
       (i64.ne
        (i64.and
         (tee_local $3
          (i64.shr_u
           (get_local $3)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$6
       (br_if $label$3
        (i64.ne
         (i64.and
          (tee_local $3
           (i64.shr_u
            (get_local $3)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$6
        (i32.lt_s
         (tee_local $4
          (i32.add
           (get_local $4)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $5
      (i32.const 1)
     )
     (br_if $label$4
      (i32.lt_s
       (tee_local $4
        (i32.add
         (get_local $4)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$2)
    )
   )
   (set_local $5
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $5)
   (i32.const 80)
  )
  (i32.store8 offset=26
   (get_local $0)
   (i32.const 1)
  )
  (i32.store16 offset=24
   (get_local $0)
   (i32.const 257)
  )
  (i32.store offset=4
   (get_local $6)
   (get_local $2)
  )
  (i32.store
   (get_local $6)
   (get_local $2)
  )
  (i32.store offset=8
   (get_local $6)
   (i32.add
    (get_local $2)
    (get_local $1)
   )
  )
  (drop
   (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_8currency6createE
    (get_local $6)
    (get_local $0)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $6)
    (i32.const 16)
   )
  )
 )
 (func $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_8currency6createE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $1)
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=8
     (get_local $0)
    )
    (get_local $2)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 1)
    )
   )
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=8
     (get_local $0)
    )
    (get_local $2)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 25)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 1)
    )
   )
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=8
     (get_local $0)
    )
    (get_local $2)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 26)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 1)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio11multi_indexILy14289235522390851584ENS_8currency14currency_statsEJEE6modifyIZNS1_2onERKNS1_5issueEEUlRT_E_EEvRKS2_yOS8_ (param $0 i32) (param $1 i32) (param $2 i64) (param $3 i32)
  (local $4 i64)
  (local $5 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $5
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 64)
    )
   )
  )
  (call $eosio_assert
   (i32.eq
    (i32.load offset=48
     (get_local $1)
    )
    (get_local $0)
   )
   (i32.const 400)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load
     (get_local $0)
    )
    (call $current_receiver)
   )
   (i32.const 448)
  )
  (i64.store
   (get_local $1)
   (i64.add
    (i64.load
     (get_local $1)
    )
    (i64.load offset=8
     (i32.load
      (get_local $3)
     )
    )
   )
  )
  (set_local $4
   (i64.load offset=8
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 544)
  )
  (i32.store offset=56
   (get_local $5)
   (i32.add
    (get_local $5)
    (i32.const 45)
   )
  )
  (i32.store offset=52
   (get_local $5)
   (get_local $5)
  )
  (i32.store offset=48
   (get_local $5)
   (get_local $5)
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_8currency14currency_statsE
    (i32.add
     (get_local $5)
     (i32.const 48)
    )
    (get_local $1)
   )
  )
  (call $db_update_i64
   (i32.load offset=52
    (get_local $1)
   )
   (get_local $2)
   (get_local $5)
   (i32.const 45)
  )
  (block $label$0
   (br_if $label$0
    (i64.lt_u
     (tee_local $2
      (i64.shr_u
       (get_local $4)
       (i64.const 8)
      )
     )
     (i64.load offset=16
      (get_local $0)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (i64.add
     (get_local $2)
     (i64.const 1)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $5)
    (i32.const 64)
   )
  )
 )
 (func $_ZN5eosio8currency15inline_transferEyyNS_5assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEy (param $0 i32) (param $1 i64) (param $2 i64) (param $3 i32) (param $4 i32) (param $5 i64)
  (local $6 i64)
  (local $7 i32)
  (local $8 i64)
  (local $9 i64)
  (local $10 i64)
  (local $11 i64)
  (local $12 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $12
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 112)
    )
   )
  )
  (set_local $6
   (i64.load
    (get_local $0)
   )
  )
  (set_local $9
   (i64.const 0)
  )
  (set_local $8
   (i64.const 59)
  )
  (set_local $0
   (i32.const 1904)
  )
  (set_local $10
   (i64.const 0)
  )
  (loop $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (br_if $label$5
         (i64.gt_u
          (get_local $9)
          (i64.const 7)
         )
        )
        (br_if $label$4
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $7
             (i32.load8_s
              (get_local $0)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $7
         (i32.add
          (get_local $7)
          (i32.const 165)
         )
        )
        (br $label$3)
       )
       (set_local $11
        (i64.const 0)
       )
       (br_if $label$2
        (i64.le_u
         (get_local $9)
         (i64.const 11)
        )
       )
       (br $label$1)
      )
      (set_local $7
       (select
        (i32.add
         (get_local $7)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $7)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $11
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $7)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $11
     (i64.shl
      (i64.and
       (get_local $11)
       (i64.const 31)
      )
      (i64.and
       (get_local $8)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $0
    (i32.add
     (get_local $0)
     (i32.const 1)
    )
   )
   (set_local $9
    (i64.add
     (get_local $9)
     (i64.const 1)
    )
   )
   (set_local $10
    (i64.or
     (get_local $11)
     (get_local $10)
    )
   )
   (br_if $label$0
    (i64.ne
     (tee_local $8
      (i64.add
       (get_local $8)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
    (i32.const 28)
   )
   (i32.load
    (i32.add
     (get_local $3)
     (i32.const 12)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
    (i32.const 24)
   )
   (i32.load
    (i32.add
     (get_local $3)
     (i32.const 8)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
    (i32.const 20)
   )
   (i32.load
    (i32.add
     (get_local $3)
     (i32.const 4)
    )
   )
  )
  (i64.store offset=16
   (get_local $12)
   (get_local $2)
  )
  (i64.store offset=8
   (get_local $12)
   (get_local $1)
  )
  (i32.store offset=24
   (get_local $12)
   (i32.load
    (get_local $3)
   )
  )
  (drop
   (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2ERKS5_
    (i32.add
     (i32.add
      (get_local $12)
      (i32.const 8)
     )
     (i32.const 32)
    )
    (get_local $4)
   )
  )
  (i64.store offset=64
   (get_local $12)
   (get_local $10)
  )
  (i64.store offset=56
   (get_local $12)
   (get_local $6)
  )
  (i64.store
   (tee_local $0
    (call $_Znwj
     (i32.const 16)
    )
   )
   (get_local $1)
  )
  (i64.store offset=8
   (get_local $0)
   (get_local $5)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 56)
    )
    (i32.const 32)
   )
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 56)
    )
    (i32.const 24)
   )
   (tee_local $7
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 56)
    )
    (i32.const 20)
   )
   (get_local $7)
  )
  (i32.store offset=72
   (get_local $12)
   (get_local $0)
  )
  (i32.store offset=84
   (get_local $12)
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 56)
    )
    (i32.const 36)
   )
   (i32.const 0)
  )
  (set_local $0
   (i32.add
    (tee_local $7
     (select
      (i32.load
       (i32.add
        (i32.add
         (get_local $12)
         (i32.const 8)
        )
        (i32.const 36)
       )
      )
      (i32.shr_u
       (tee_local $0
        (i32.load8_u offset=40
         (get_local $12)
        )
       )
       (i32.const 1)
      )
      (i32.and
       (get_local $0)
       (i32.const 1)
      )
     )
    )
    (i32.const 32)
   )
  )
  (set_local $9
   (i64.extend_u/i32
    (get_local $7)
   )
  )
  (set_local $7
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 56)
    )
    (i32.const 28)
   )
  )
  (loop $label$6
   (set_local $0
    (i32.add
     (get_local $0)
     (i32.const 1)
    )
   )
   (br_if $label$6
    (i64.ne
     (tee_local $9
      (i64.shr_u
       (get_local $9)
       (i64.const 7)
      )
     )
     (i64.const 0)
    )
   )
  )
  (block $label$7
   (block $label$8
    (br_if $label$8
     (i32.eqz
      (get_local $0)
     )
    )
    (call $_ZNSt3__16vectorIcNS_9allocatorIcEEE8__appendEj
     (get_local $7)
     (get_local $0)
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $12)
       (i32.const 88)
      )
     )
    )
    (set_local $0
     (i32.load
      (i32.add
       (get_local $12)
       (i32.const 84)
      )
     )
    )
    (br $label$7)
   )
   (set_local $7
    (i32.const 0)
   )
   (set_local $0
    (i32.const 0)
   )
  )
  (i32.store offset=100
   (get_local $12)
   (get_local $0)
  )
  (i32.store offset=96
   (get_local $12)
   (get_local $0)
  )
  (i32.store offset=104
   (get_local $12)
   (get_local $7)
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_8currency8transferE
    (i32.add
     (get_local $12)
     (i32.const 96)
    )
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
   )
  )
  (block $label$9
   (br_if $label$9
    (i32.eqz
     (i32.and
      (i32.load8_u
       (i32.add
        (get_local $12)
        (i32.const 40)
       )
      )
      (i32.const 1)
     )
    )
   )
   (call $_ZdlPv
    (i32.load
     (i32.add
      (get_local $12)
      (i32.const 48)
     )
    )
   )
  )
  (call $_ZN5eosio4packINS_6actionEEENSt3__16vectorIcNS2_9allocatorIcEEEERKT_
   (i32.add
    (get_local $12)
    (i32.const 8)
   )
   (i32.add
    (get_local $12)
    (i32.const 56)
   )
  )
  (call $send_inline
   (tee_local $0
    (i32.load offset=8
     (get_local $12)
    )
   )
   (i32.sub
    (i32.load offset=12
     (get_local $12)
    )
    (get_local $0)
   )
  )
  (block $label$10
   (br_if $label$10
    (i32.eqz
     (tee_local $0
      (i32.load offset=8
       (get_local $12)
      )
     )
    )
   )
   (i32.store offset=12
    (get_local $12)
    (get_local $0)
   )
   (call $_ZdlPv
    (get_local $0)
   )
  )
  (block $label$11
   (br_if $label$11
    (i32.eqz
     (tee_local $0
      (i32.load offset=84
       (get_local $12)
      )
     )
    )
   )
   (i32.store
    (i32.add
     (get_local $12)
     (i32.const 88)
    )
    (get_local $0)
   )
   (call $_ZdlPv
    (get_local $0)
   )
  )
  (block $label$12
   (br_if $label$12
    (i32.eqz
     (tee_local $0
      (i32.load offset=72
       (get_local $12)
      )
     )
    )
   )
   (i32.store
    (i32.add
     (get_local $12)
     (i32.const 76)
    )
    (get_local $0)
   )
   (call $_ZdlPv
    (get_local $0)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $12)
    (i32.const 112)
   )
  )
 )
 (func $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNSt3__112basic_stringIcNS7_11char_traitsIcEENS7_9allocatorIcEEEE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i32.store offset=24
   (get_local $7)
   (i32.const 0)
  )
  (i64.store offset=16
   (get_local $7)
   (i64.const 0)
  )
  (drop
   (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNSt3__16vectorIcNS7_9allocatorIcEEEE
    (get_local $0)
    (i32.add
     (get_local $7)
     (i32.const 16)
    )
   )
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (block $label$6
         (block $label$7
          (block $label$8
           (br_if $label$8
            (i32.ne
             (tee_local $5
              (i32.load offset=20
               (get_local $7)
              )
             )
             (tee_local $4
              (i32.load offset=16
               (get_local $7)
              )
             )
            )
           )
           (br_if $label$7
            (i32.and
             (i32.load8_u
              (get_local $1)
             )
             (i32.const 1)
            )
           )
           (i32.store16
            (get_local $1)
            (i32.const 0)
           )
           (set_local $4
            (i32.add
             (get_local $1)
             (i32.const 8)
            )
           )
           (br $label$6)
          )
          (i32.store
           (i32.add
            (get_local $7)
            (i32.const 8)
           )
           (i32.const 0)
          )
          (i64.store
           (get_local $7)
           (i64.const 0)
          )
          (br_if $label$0
           (i32.ge_u
            (tee_local $2
             (i32.sub
              (get_local $5)
              (get_local $4)
             )
            )
            (i32.const -16)
           )
          )
          (br_if $label$5
           (i32.ge_u
            (get_local $2)
            (i32.const 11)
           )
          )
          (i32.store8
           (get_local $7)
           (i32.shl
            (get_local $2)
            (i32.const 1)
           )
          )
          (set_local $6
           (i32.or
            (get_local $7)
            (i32.const 1)
           )
          )
          (br_if $label$4
           (get_local $2)
          )
          (br $label$3)
         )
         (i32.store8
          (i32.load offset=8
           (get_local $1)
          )
          (i32.const 0)
         )
         (i32.store offset=4
          (get_local $1)
          (i32.const 0)
         )
         (set_local $4
          (i32.add
           (get_local $1)
           (i32.const 8)
          )
         )
        )
        (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7reserveEj
         (get_local $1)
         (i32.const 0)
        )
        (i32.store
         (get_local $4)
         (i32.const 0)
        )
        (i64.store align=4
         (get_local $1)
         (i64.const 0)
        )
        (br_if $label$2
         (tee_local $4
          (i32.load offset=16
           (get_local $7)
          )
         )
        )
        (br $label$1)
       )
       (set_local $6
        (call $_Znwj
         (tee_local $5
          (i32.and
           (i32.add
            (get_local $2)
            (i32.const 16)
           )
           (i32.const -16)
          )
         )
        )
       )
       (i32.store
        (get_local $7)
        (i32.or
         (get_local $5)
         (i32.const 1)
        )
       )
       (i32.store offset=8
        (get_local $7)
        (get_local $6)
       )
       (i32.store offset=4
        (get_local $7)
        (get_local $2)
       )
      )
      (set_local $3
       (get_local $2)
      )
      (set_local $5
       (get_local $6)
      )
      (loop $label$9
       (i32.store8
        (get_local $5)
        (i32.load8_u
         (get_local $4)
        )
       )
       (set_local $5
        (i32.add
         (get_local $5)
         (i32.const 1)
        )
       )
       (set_local $4
        (i32.add
         (get_local $4)
         (i32.const 1)
        )
       )
       (br_if $label$9
        (tee_local $3
         (i32.add
          (get_local $3)
          (i32.const -1)
         )
        )
       )
      )
      (set_local $6
       (i32.add
        (get_local $6)
        (get_local $2)
       )
      )
     )
     (i32.store8
      (get_local $6)
      (i32.const 0)
     )
     (block $label$10
      (block $label$11
       (br_if $label$11
        (i32.and
         (i32.load8_u
          (get_local $1)
         )
         (i32.const 1)
        )
       )
       (i32.store16
        (get_local $1)
        (i32.const 0)
       )
       (br $label$10)
      )
      (i32.store8
       (i32.load offset=8
        (get_local $1)
       )
       (i32.const 0)
      )
      (i32.store offset=4
       (get_local $1)
       (i32.const 0)
      )
     )
     (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7reserveEj
      (get_local $1)
      (i32.const 0)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const 8)
      )
      (i32.load
       (i32.add
        (get_local $7)
        (i32.const 8)
       )
      )
     )
     (i64.store align=4
      (get_local $1)
      (i64.load
       (get_local $7)
      )
     )
     (br_if $label$1
      (i32.eqz
       (tee_local $4
        (i32.load offset=16
         (get_local $7)
        )
       )
      )
     )
    )
    (i32.store offset=20
     (get_local $7)
     (get_local $4)
    )
    (call $_ZdlPv
     (get_local $4)
    )
   )
   (i32.store offset=4
    (i32.const 0)
    (i32.add
     (get_local $7)
     (i32.const 32)
    )
   )
   (return
    (get_local $0)
   )
  )
  (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
   (get_local $7)
  )
  (unreachable)
 )
 (func $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNSt3__16vectorIcNS7_9allocatorIcEEEE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i64)
  (local $7 i32)
  (set_local $5
   (i32.load offset=4
    (get_local $0)
   )
  )
  (set_local $7
   (i32.const 0)
  )
  (set_local $6
   (i64.const 0)
  )
  (set_local $2
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (set_local $3
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
  )
  (loop $label$0
   (call $eosio_assert
    (i32.lt_u
     (get_local $5)
     (i32.load
      (get_local $2)
     )
    )
    (i32.const 704)
   )
   (set_local $4
    (i32.load8_u
     (tee_local $5
      (i32.load
       (get_local $3)
      )
     )
    )
   )
   (i32.store
    (get_local $3)
    (tee_local $5
     (i32.add
      (get_local $5)
      (i32.const 1)
     )
    )
   )
   (set_local $6
    (i64.or
     (i64.extend_u/i32
      (i32.shl
       (i32.and
        (get_local $4)
        (i32.const 127)
       )
       (tee_local $7
        (i32.and
         (get_local $7)
         (i32.const 255)
        )
       )
      )
     )
     (get_local $6)
    )
   )
   (set_local $7
    (i32.add
     (get_local $7)
     (i32.const 7)
    )
   )
   (br_if $label$0
    (i32.shr_u
     (get_local $4)
     (i32.const 7)
    )
   )
  )
  (block $label$1
   (block $label$2
    (br_if $label$2
     (i32.le_u
      (tee_local $3
       (i32.wrap/i64
        (get_local $6)
       )
      )
      (tee_local $2
       (i32.sub
        (tee_local $7
         (i32.load offset=4
          (get_local $1)
         )
        )
        (tee_local $4
         (i32.load
          (get_local $1)
         )
        )
       )
      )
     )
    )
    (call $_ZNSt3__16vectorIcNS_9allocatorIcEEE8__appendEj
     (get_local $1)
     (i32.sub
      (get_local $3)
      (get_local $2)
     )
    )
    (set_local $5
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $1)
       (i32.const 4)
      )
     )
    )
    (set_local $4
     (i32.load
      (get_local $1)
     )
    )
    (br $label$1)
   )
   (br_if $label$1
    (i32.ge_u
     (get_local $3)
     (get_local $2)
    )
   )
   (i32.store
    (i32.add
     (get_local $1)
     (i32.const 4)
    )
    (tee_local $7
     (i32.add
      (get_local $4)
      (get_local $3)
     )
    )
   )
  )
  (call $eosio_assert
   (i32.ge_u
    (i32.sub
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 8)
      )
     )
     (get_local $5)
    )
    (tee_local $5
     (i32.sub
      (get_local $7)
      (get_local $4)
     )
    )
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $4)
    (i32.load
     (tee_local $7
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (get_local $5)
   )
  )
  (i32.store
   (get_local $7)
   (i32.add
    (i32.load
     (get_local $7)
    )
    (get_local $5)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio6unpackINS_8exchange11covermarginEEET_PKcj (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (i64.store offset=16
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 24)
   )
   (i64.const 1398362884)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $3
   (i64.const 5462355)
  )
  (set_local $4
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $3)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $3
          (i64.shr_u
           (get_local $3)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $3
           (i64.shr_u
            (get_local $3)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $4
          (i32.add
           (get_local $4)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $5
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $4
        (i32.add
         (get_local $4)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $5
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $5)
   (i32.const 80)
  )
  (call $eosio_assert
   (i32.gt_u
    (get_local $2)
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $0)
    (get_local $1)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (tee_local $4
     (i32.and
      (get_local $2)
      (i32.const -8)
     )
    )
    (i32.const 8)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $4)
    (i32.const 16)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $4)
    (i32.const 24)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 24)
    )
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $4)
    (i32.const 32)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 32)
    )
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.const 8)
   )
  )
 )
 (func $_ZN5eosio8exchange8upmarginC2Ev (param $0 i32) (result i32)
  (local $1 i64)
  (local $2 i32)
  (local $3 i32)
  (i64.store offset=16
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (tee_local $2
    (i32.add
     (get_local $0)
     (i32.const 24)
    )
   )
   (i64.const 1398362884)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load
     (get_local $2)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (i64.store
   (tee_local $2
    (i32.add
     (get_local $0)
     (i32.const 48)
    )
   )
   (i64.const 1398362884)
  )
  (i64.store offset=40
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load
     (get_local $2)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$5
   (block $label$6
    (loop $label$7
     (br_if $label$6
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$8
      (br_if $label$8
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$9
       (br_if $label$6
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$9
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$7
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$5)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (get_local $0)
 )
 (func $_ZN5boost3pfr6detail19for_each_field_implINS1_14sequence_tuple5tupleIJRyRN5eosio11symbol_typeERNS6_14extended_assetESA_EEEZNS6_rsINS6_10datastreamIPKcEENS6_8exchange8upmarginELPv0EEERT_SL_RT0_EUlSL_E_JLj0ELj1ELj2ELj3EEEEvSL_OSM_NSt3__116integer_sequenceIjJXspT1_EEEENSQ_17integral_constantIbLb0EEE (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (set_local $3
   (i32.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $3)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $3
   (i32.load offset=4
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $3)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $3
   (i32.load offset=8
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $3)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $4
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $4)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $4
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $4)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $0
   (i32.load offset=12
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $0)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $1
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $1)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $1
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $1)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
 )
 (func $_ZN5eosio8exchange5tradeC2Ev (param $0 i32) (result i32)
  (local $1 i64)
  (local $2 i32)
  (local $3 i32)
  (i64.store offset=16
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (tee_local $2
    (i32.add
     (get_local $0)
     (i32.const 24)
    )
   )
   (i64.const 1398362884)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load
     (get_local $2)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (i64.store
   (tee_local $2
    (i32.add
     (get_local $0)
     (i32.const 48)
    )
   )
   (i64.const 1398362884)
  )
  (i64.store offset=40
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $1
   (i64.shr_u
    (i64.load
     (get_local $2)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$5
   (block $label$6
    (loop $label$7
     (br_if $label$6
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$8
      (br_if $label$8
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$9
       (br_if $label$6
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$9
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$7
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$5)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 80)
  )
  (i32.store8 offset=68
   (get_local $0)
   (i32.const 1)
  )
  (i32.store offset=64
   (get_local $0)
   (i32.const 0)
  )
  (get_local $0)
 )
 (func $_ZN5boost3pfr6detail19for_each_field_implINS1_14sequence_tuple5tupleIJRyRN5eosio11symbol_typeERNS6_14extended_assetESA_RmRhEEEZNS6_rsINS6_10datastreamIPKcEENS6_8exchange5tradeELPv0EEERT_SN_RT0_EUlSN_E_JLj0ELj1ELj2ELj3ELj4ELj5EEEEvSN_OSO_NSt3__116integer_sequenceIjJXspT1_EEEENSS_17integral_constantIbLb0EEE (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (set_local $3
   (i32.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $3)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $3
   (i32.load offset=4
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $3)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $3
   (i32.load offset=8
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $3)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $4
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $4)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $4
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $4)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $3
   (i32.load offset=12
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $3)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $4
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $4)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $4
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $4)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $3
   (i32.load offset=16
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 3)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $3)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 4)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 4)
   )
  )
  (set_local $0
   (i32.load offset=20
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=8
     (tee_local $2
      (i32.load
       (get_local $1)
      )
     )
    )
    (i32.load offset=4
     (get_local $2)
    )
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $0)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 1)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 1)
   )
  )
 )
 (func $_ZN5boost6fusion6detail17for_each_unrolledILi4EE4callINS0_18std_tuple_iteratorINSt3__15tupleIJyN5eosio11symbol_typeEdNS8_15extended_symbolEEEELi0EEEZNS8_rsINS8_10datastreamIPKcEEJyS9_dSA_EEERT_SJ_RNS7_IJDpT0_EEEEUlSJ_E_EEvRKSI_RKT0_ (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (set_local $3
   (i32.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $3)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $2
   (i32.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $0
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $0
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $2)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $1
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $1)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $2)
     (i32.const 24)
    )
    (i32.load offset=4
     (get_local $1)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $1)
   (tee_local $0
    (i32.add
     (i32.load offset=4
      (get_local $1)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $1)
     )
     (get_local $0)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $2)
     (i32.const 32)
    )
    (i32.load offset=4
     (get_local $1)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $1)
   (i32.add
    (i32.load offset=4
     (get_local $1)
    )
    (i32.const 8)
   )
  )
 )
 (func $_ZN5eosio6unpackINSt3__15tupleIJyNS_11symbol_typeENS_14extended_assetEEEEEET_PKcj (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i32)
  (local $6 i32)
  (i64.store
   (get_local $0)
   (i64.const 0)
  )
  (i64.store offset=16
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (tee_local $3
    (i32.add
     (get_local $0)
     (i32.const 32)
    )
   )
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 24)
   )
   (i64.const 1398362884)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $4
   (i64.const 5462355)
  )
  (set_local $5
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $4)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $4
          (i64.shr_u
           (get_local $4)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $4
           (i64.shr_u
            (get_local $4)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $5
          (i32.add
           (get_local $5)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $6
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $5
        (i32.add
         (get_local $5)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $6
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $6)
   (i32.const 80)
  )
  (call $eosio_assert
   (i32.gt_u
    (get_local $2)
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $0)
    (get_local $1)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (tee_local $5
     (i32.and
      (get_local $2)
      (i32.const -8)
     )
    )
    (i32.const 8)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $5)
    (i32.const 16)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $5)
    (i32.const 24)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 24)
    )
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $5)
    (i32.const 32)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $3)
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.const 8)
   )
  )
 )
 (func $_ZN5eosio6unpackINSt3__15tupleIJyNS_5assetEmNS_14extended_assetES4_EEEEET_PKcj (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $6
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i64.store offset=8
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 16)
   )
   (i64.const 1398362884)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $3
   (i64.const 5462355)
  )
  (set_local $4
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $3)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $3
          (i64.shr_u
           (get_local $3)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $3
           (i64.shr_u
            (get_local $3)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $4
          (i32.add
           (get_local $4)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $5
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $4
        (i32.add
         (get_local $4)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $5
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $5)
   (i32.const 80)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 48)
   )
   (i64.const 0)
  )
  (i32.store offset=24
   (get_local $0)
   (i32.const 0)
  )
  (i64.store offset=32
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 40)
   )
   (i64.const 1398362884)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $3
   (i64.const 5462355)
  )
  (set_local $4
   (i32.const 0)
  )
  (block $label$5
   (block $label$6
    (loop $label$7
     (br_if $label$6
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $3)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$8
      (br_if $label$8
       (i64.ne
        (i64.and
         (tee_local $3
          (i64.shr_u
           (get_local $3)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$9
       (br_if $label$6
        (i64.ne
         (i64.and
          (tee_local $3
           (i64.shr_u
            (get_local $3)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$9
        (i32.lt_s
         (tee_local $4
          (i32.add
           (get_local $4)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $5
      (i32.const 1)
     )
     (br_if $label$7
      (i32.lt_s
       (tee_local $4
        (i32.add
         (get_local $4)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$5)
    )
   )
   (set_local $5
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $5)
   (i32.const 80)
  )
  (i64.store offset=56
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 72)
   )
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $0)
    (i32.const 64)
   )
   (i64.const 1398362884)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 16)
  )
  (set_local $3
   (i64.const 5462355)
  )
  (set_local $4
   (i32.const 0)
  )
  (block $label$10
   (block $label$11
    (loop $label$12
     (br_if $label$11
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $3)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$13
      (br_if $label$13
       (i64.ne
        (i64.and
         (tee_local $3
          (i64.shr_u
           (get_local $3)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$14
       (br_if $label$11
        (i64.ne
         (i64.and
          (tee_local $3
           (i64.shr_u
            (get_local $3)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$14
        (i32.lt_s
         (tee_local $4
          (i32.add
           (get_local $4)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $5
      (i32.const 1)
     )
     (br_if $label$12
      (i32.lt_s
       (tee_local $4
        (i32.add
         (get_local $4)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$10)
    )
   )
   (set_local $5
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $5)
   (i32.const 80)
  )
  (i32.store offset=4
   (get_local $6)
   (get_local $1)
  )
  (i32.store
   (get_local $6)
   (get_local $1)
  )
  (i32.store offset=8
   (get_local $6)
   (i32.add
    (get_local $1)
    (get_local $2)
   )
  )
  (i32.store offset=16
   (get_local $6)
   (get_local $6)
  )
  (i32.store offset=24
   (get_local $6)
   (get_local $0)
  )
  (call $_ZN5boost6fusion6detail17for_each_unrolledILi5EE4callINS0_18std_tuple_iteratorINSt3__15tupleIJyN5eosio5assetEmNS8_14extended_assetESA_EEELi0EEEZNS8_rsINS8_10datastreamIPKcEEJyS9_mSA_SA_EEERT_SJ_RNS7_IJDpT0_EEEEUlSJ_E_EEvRKSI_RKT0_
   (i32.add
    (get_local $6)
    (i32.const 24)
   )
   (i32.add
    (get_local $6)
    (i32.const 16)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $6)
    (i32.const 32)
   )
  )
 )
 (func $_ZN5boost6fusion6detail17for_each_unrolledILi5EE4callINS0_18std_tuple_iteratorINSt3__15tupleIJyN5eosio5assetEmNS8_14extended_assetESA_EEELi0EEEZNS8_rsINS8_10datastreamIPKcEEJyS9_mSA_SA_EEERT_SJ_RNS7_IJDpT0_EEEEUlSJ_E_EEvRKSI_RKT0_ (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (set_local $2
   (i32.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $3
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $3)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $2)
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (set_local $0
   (i32.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $3
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $3)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $3)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $3)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $3
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $3)
     )
    )
    (i32.const 3)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 24)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 4)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 4)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $3
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $3)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 32)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $3)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $3)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 40)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $3)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $3)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 48)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $3
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $3)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 56)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (tee_local $1
    (i32.add
     (i32.load offset=4
      (get_local $3)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $3)
     )
     (get_local $1)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 64)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (tee_local $1
    (i32.add
     (i32.load offset=4
      (get_local $3)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $3)
     )
     (get_local $1)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 72)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
 )
 (func $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_8currency8transferE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (get_local $1)
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 688)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNSt3__112basic_stringIcNS7_11char_traitsIcEENS7_9allocatorIcEEEE
   (get_local $0)
   (i32.add
    (get_local $1)
    (i32.const 32)
   )
  )
 )
 (func $apply (param $0 i64) (param $1 i64) (param $2 i64)
  (local $3 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $3
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $3)
    (i32.const 32)
   )
   (i64.const 0)
  )
  (i32.store
   (i32.add
    (get_local $3)
    (i32.const 40)
   )
   (i32.const 0)
  )
  (i64.store offset=16
   (get_local $3)
   (get_local $0)
  )
  (i64.store offset=8
   (get_local $3)
   (get_local $0)
  )
  (i64.store offset=24
   (get_local $3)
   (get_local $0)
  )
  (call $_ZN5eosio8exchange5applyEyy
   (i32.add
    (get_local $3)
    (i32.const 8)
   )
   (get_local $1)
   (get_local $2)
  )
  (call $eosio_exit
   (i32.const 0)
  )
  (unreachable)
 )
 (func $_Znwj (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (block $label$0
   (br_if $label$0
    (tee_local $0
     (call $malloc
      (tee_local $1
       (select
        (get_local $0)
        (i32.const 1)
        (get_local $0)
       )
      )
     )
    )
   )
   (loop $label$1
    (set_local $0
     (i32.const 0)
    )
    (br_if $label$0
     (i32.eqz
      (tee_local $2
       (i32.load offset=3648
        (i32.const 0)
       )
      )
     )
    )
    (call_indirect (type $FUNCSIG$v)
     (get_local $2)
    )
    (br_if $label$1
     (i32.eqz
      (tee_local $0
       (call $malloc
        (get_local $1)
       )
      )
     )
    )
   )
  )
  (get_local $0)
 )
 (func $_ZdlPv (param $0 i32)
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (get_local $0)
    )
   )
   (call $free
    (get_local $0)
   )
  )
 )
 (func $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv (param $0 i32)
  (call $abort)
  (unreachable)
 )
 (func $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7reserveEj (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (br_if $label$0
    (i32.ge_u
     (get_local $1)
     (i32.const -16)
    )
   )
   (set_local $2
    (i32.const 10)
   )
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (i32.and
       (tee_local $5
        (i32.load8_u
         (get_local $0)
        )
       )
       (i32.const 1)
      )
     )
    )
    (set_local $2
     (i32.add
      (i32.and
       (tee_local $5
        (i32.load
         (get_local $0)
        )
       )
       (i32.const -2)
      )
      (i32.const -1)
     )
    )
   )
   (block $label$2
    (block $label$3
     (br_if $label$3
      (i32.and
       (get_local $5)
       (i32.const 1)
      )
     )
     (set_local $3
      (i32.shr_u
       (i32.and
        (get_local $5)
        (i32.const 254)
       )
       (i32.const 1)
      )
     )
     (br $label$2)
    )
    (set_local $3
     (i32.load offset=4
      (get_local $0)
     )
    )
   )
   (set_local $4
    (i32.const 10)
   )
   (block $label$4
    (br_if $label$4
     (i32.lt_u
      (tee_local $1
       (select
        (get_local $3)
        (get_local $1)
        (i32.gt_u
         (get_local $3)
         (get_local $1)
        )
       )
      )
      (i32.const 11)
     )
    )
    (set_local $4
     (i32.add
      (i32.and
       (i32.add
        (get_local $1)
        (i32.const 16)
       )
       (i32.const -16)
      )
      (i32.const -1)
     )
    )
   )
   (block $label$5
    (br_if $label$5
     (i32.eq
      (get_local $4)
      (get_local $2)
     )
    )
    (block $label$6
     (block $label$7
      (br_if $label$7
       (i32.ne
        (get_local $4)
        (i32.const 10)
       )
      )
      (set_local $6
       (i32.const 1)
      )
      (set_local $1
       (i32.add
        (get_local $0)
        (i32.const 1)
       )
      )
      (set_local $2
       (i32.load offset=8
        (get_local $0)
       )
      )
      (set_local $7
       (i32.const 0)
      )
      (br $label$6)
     )
     (set_local $1
      (call $_Znwj
       (i32.add
        (get_local $4)
        (i32.const 1)
       )
      )
     )
     (block $label$8
      (br_if $label$8
       (i32.gt_u
        (get_local $4)
        (get_local $2)
       )
      )
      (br_if $label$5
       (i32.eqz
        (get_local $1)
       )
      )
     )
     (block $label$9
      (br_if $label$9
       (i32.and
        (tee_local $5
         (i32.load8_u
          (get_local $0)
         )
        )
        (i32.const 1)
       )
      )
      (set_local $7
       (i32.const 1)
      )
      (set_local $2
       (i32.add
        (get_local $0)
        (i32.const 1)
       )
      )
      (set_local $6
       (i32.const 0)
      )
      (br $label$6)
     )
     (set_local $2
      (i32.load offset=8
       (get_local $0)
      )
     )
     (set_local $6
      (i32.const 1)
     )
     (set_local $7
      (i32.const 1)
     )
    )
    (block $label$10
     (block $label$11
      (br_if $label$11
       (i32.and
        (get_local $5)
        (i32.const 1)
       )
      )
      (set_local $5
       (i32.shr_u
        (i32.and
         (get_local $5)
         (i32.const 254)
        )
        (i32.const 1)
       )
      )
      (br $label$10)
     )
     (set_local $5
      (i32.load offset=4
       (get_local $0)
      )
     )
    )
    (block $label$12
     (br_if $label$12
      (i32.eqz
       (tee_local $5
        (i32.add
         (get_local $5)
         (i32.const 1)
        )
       )
      )
     )
     (drop
      (call $memcpy
       (get_local $1)
       (get_local $2)
       (get_local $5)
      )
     )
    )
    (block $label$13
     (br_if $label$13
      (i32.eqz
       (get_local $6)
      )
     )
     (call $_ZdlPv
      (get_local $2)
     )
    )
    (block $label$14
     (br_if $label$14
      (i32.eqz
       (get_local $7)
      )
     )
     (i32.store offset=4
      (get_local $0)
      (get_local $3)
     )
     (i32.store offset=8
      (get_local $0)
      (get_local $1)
     )
     (i32.store
      (get_local $0)
      (i32.or
       (i32.add
        (get_local $4)
        (i32.const 1)
       )
       (i32.const 1)
      )
     )
     (return)
    )
    (i32.store8
     (get_local $0)
     (i32.shl
      (get_local $3)
      (i32.const 1)
     )
    )
   )
   (return)
  )
  (call $abort)
  (unreachable)
 )
 (func $_ZNKSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7compareEjjPKcj (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (param $4 i32) (result i32)
  (local $5 i32)
  (local $6 i32)
  (block $label$0
   (block $label$1
    (br_if $label$1
     (tee_local $5
      (i32.and
       (tee_local $6
        (i32.load8_u
         (get_local $0)
        )
       )
       (i32.const 1)
      )
     )
    )
    (set_local $6
     (i32.shr_u
      (get_local $6)
      (i32.const 1)
     )
    )
    (br $label$0)
   )
   (set_local $6
    (i32.load offset=4
     (get_local $0)
    )
   )
  )
  (block $label$2
   (br_if $label$2
    (i32.eq
     (get_local $4)
     (i32.const -1)
    )
   )
   (br_if $label$2
    (i32.lt_u
     (get_local $6)
     (get_local $1)
    )
   )
   (set_local $6
    (select
     (tee_local $6
      (i32.sub
       (get_local $6)
       (get_local $1)
      )
     )
     (get_local $2)
     (i32.lt_u
      (get_local $6)
      (get_local $2)
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (get_local $5)
     )
     (set_local $0
      (i32.add
       (get_local $0)
       (i32.const 1)
      )
     )
     (br $label$3)
    )
    (set_local $0
     (i32.load offset=8
      (get_local $0)
     )
    )
   )
   (block $label$5
    (br_if $label$5
     (i32.eqz
      (tee_local $2
       (select
        (get_local $4)
        (get_local $6)
        (tee_local $5
         (i32.gt_u
          (get_local $6)
          (get_local $4)
         )
        )
       )
      )
     )
    )
    (br_if $label$5
     (i32.eqz
      (tee_local $1
       (call $memcmp
        (i32.add
         (get_local $0)
         (get_local $1)
        )
        (get_local $3)
        (get_local $2)
       )
      )
     )
    )
    (return
     (get_local $1)
    )
   )
   (return
    (select
     (i32.const -1)
     (get_local $5)
     (i32.lt_u
      (get_local $6)
      (get_local $4)
     )
    )
   )
  )
  (call $abort)
  (unreachable)
 )
 (func $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv (param $0 i32)
  (call $abort)
  (unreachable)
 )
 (func $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2ERKS5_ (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (i64.store align=4
   (get_local $0)
   (i64.const 0)
  )
  (i32.store
   (tee_local $3
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
   )
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.and
     (i32.load8_u
      (get_local $1)
     )
     (i32.const 1)
    )
   )
   (i64.store align=4
    (get_local $0)
    (i64.load align=4
     (get_local $1)
    )
   )
   (i32.store
    (get_local $3)
    (i32.load
     (i32.add
      (get_local $1)
      (i32.const 8)
     )
    )
   )
   (return
    (get_local $0)
   )
  )
  (block $label$1
   (br_if $label$1
    (i32.ge_u
     (tee_local $3
      (i32.load offset=4
       (get_local $1)
      )
     )
     (i32.const -16)
    )
   )
   (set_local $2
    (i32.load offset=8
     (get_local $1)
    )
   )
   (block $label$2
    (block $label$3
     (block $label$4
      (br_if $label$4
       (i32.ge_u
        (get_local $3)
        (i32.const 11)
       )
      )
      (i32.store8
       (get_local $0)
       (i32.shl
        (get_local $3)
        (i32.const 1)
       )
      )
      (set_local $1
       (i32.add
        (get_local $0)
        (i32.const 1)
       )
      )
      (br_if $label$3
       (get_local $3)
      )
      (br $label$2)
     )
     (set_local $1
      (call $_Znwj
       (tee_local $4
        (i32.and
         (i32.add
          (get_local $3)
          (i32.const 16)
         )
         (i32.const -16)
        )
       )
      )
     )
     (i32.store
      (get_local $0)
      (i32.or
       (get_local $4)
       (i32.const 1)
      )
     )
     (i32.store offset=8
      (get_local $0)
      (get_local $1)
     )
     (i32.store offset=4
      (get_local $0)
      (get_local $3)
     )
    )
    (drop
     (call $memcpy
      (get_local $1)
      (get_local $2)
      (get_local $3)
     )
    )
   )
   (i32.store8
    (i32.add
     (get_local $1)
     (get_local $3)
    )
    (i32.const 0)
   )
   (return
    (get_local $0)
   )
  )
  (call $abort)
  (unreachable)
 )
 (func $pow (param $0 f64) (param $1 f64) (result f64)
  (local $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 f64)
  (local $11 i64)
  (local $12 f64)
  (local $13 f64)
  (local $14 f64)
  (local $15 f64)
  (local $16 f64)
  (local $17 f64)
  (local $18 f64)
  (local $19 i32)
  (local $20 f64)
  (local $21 f64)
  (set_local $21
   (f64.const 1)
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (i32.or
      (tee_local $8
       (i32.and
        (tee_local $5
         (i32.wrap/i64
          (i64.shr_u
           (tee_local $4
            (i64.reinterpret/f64
             (get_local $1)
            )
           )
           (i64.const 32)
          )
         )
        )
        (i32.const 2147483647)
       )
      )
      (tee_local $6
       (i32.wrap/i64
        (get_local $4)
       )
      )
     )
    )
   )
   (set_local $2
    (i32.wrap/i64
     (i64.shr_u
      (tee_local $11
       (i64.reinterpret/f64
        (get_local $0)
       )
      )
      (i64.const 32)
     )
    )
   )
   (block $label$1
    (br_if $label$1
     (tee_local $3
      (i32.wrap/i64
       (get_local $11)
      )
     )
    )
    (br_if $label$0
     (i32.eq
      (get_local $2)
      (i32.const 1072693248)
     )
    )
   )
   (block $label$2
    (block $label$3
     (br_if $label$3
      (i32.gt_u
       (tee_local $7
        (i32.and
         (get_local $2)
         (i32.const 2147483647)
        )
       )
       (i32.const 2146435072)
      )
     )
     (br_if $label$3
      (i32.and
       (i32.ne
        (get_local $3)
        (i32.const 0)
       )
       (i32.eq
        (get_local $7)
        (i32.const 2146435072)
       )
      )
     )
     (br_if $label$3
      (i32.gt_u
       (get_local $8)
       (i32.const 2146435072)
      )
     )
     (br_if $label$2
      (i32.eqz
       (get_local $6)
      )
     )
     (br_if $label$2
      (i32.ne
       (get_local $8)
       (i32.const 2146435072)
      )
     )
    )
    (return
     (f64.add
      (get_local $0)
      (get_local $1)
     )
    )
   )
   (set_local $19
    (i32.const 0)
   )
   (block $label$4
    (block $label$5
     (block $label$6
      (block $label$7
       (br_if $label$7
        (i32.gt_s
         (get_local $2)
         (i32.const -1)
        )
       )
       (set_local $19
        (i32.const 2)
       )
       (br_if $label$7
        (i32.gt_u
         (get_local $8)
         (i32.const 1128267775)
        )
       )
       (set_local $19
        (i32.const 0)
       )
       (br_if $label$7
        (i32.lt_u
         (get_local $8)
         (i32.const 1072693248)
        )
       )
       (br_if $label$6
        (i32.lt_s
         (i32.add
          (tee_local $9
           (i32.shr_u
            (get_local $8)
            (i32.const 20)
           )
          )
          (i32.const -1023)
         )
         (i32.const 21)
        )
       )
       (set_local $19
        (select
         (i32.sub
          (i32.const 2)
          (i32.and
           (tee_local $9
            (i32.shr_u
             (get_local $6)
             (tee_local $19
              (i32.sub
               (i32.const 1075)
               (get_local $9)
              )
             )
            )
           )
           (i32.const 1)
          )
         )
         (i32.const 0)
         (i32.eq
          (i32.shl
           (get_local $9)
           (get_local $19)
          )
          (get_local $6)
         )
        )
       )
      )
      (br_if $label$5
       (i32.eqz
        (get_local $6)
       )
      )
      (br $label$4)
     )
     (set_local $19
      (i32.const 0)
     )
     (br_if $label$4
      (get_local $6)
     )
     (set_local $19
      (select
       (i32.sub
        (i32.const 2)
        (i32.and
         (tee_local $19
          (i32.shr_u
           (get_local $8)
           (tee_local $6
            (i32.sub
             (i32.const 1043)
             (get_local $9)
            )
           )
          )
         )
         (i32.const 1)
        )
       )
       (i32.const 0)
       (i32.eq
        (i32.shl
         (get_local $19)
         (get_local $6)
        )
        (get_local $8)
       )
      )
     )
    )
    (block $label$8
     (block $label$9
      (block $label$10
       (block $label$11
        (br_if $label$11
         (i32.ne
          (get_local $8)
          (i32.const 2146435072)
         )
        )
        (br_if $label$0
         (i32.eqz
          (i32.or
           (i32.add
            (get_local $7)
            (i32.const -1072693248)
           )
           (get_local $3)
          )
         )
        )
        (br_if $label$10
         (i32.lt_u
          (get_local $7)
          (i32.const 1072693248)
         )
        )
        (return
         (select
          (get_local $1)
          (f64.const 0)
          (i32.gt_s
           (get_local $5)
           (i32.const -1)
          )
         )
        )
       )
       (block $label$12
        (br_if $label$12
         (i32.ne
          (get_local $8)
          (i32.const 1072693248)
         )
        )
        (br_if $label$8
         (i32.le_s
          (get_local $5)
          (i32.const -1)
         )
        )
        (return
         (get_local $0)
        )
       )
       (br_if $label$9
        (i32.ne
         (get_local $5)
         (i32.const 1073741824)
        )
       )
       (return
        (f64.mul
         (get_local $0)
         (get_local $0)
        )
       )
      )
      (return
       (select
        (f64.const 0)
        (f64.neg
         (get_local $1)
        )
        (i32.gt_s
         (get_local $5)
         (i32.const -1)
        )
       )
      )
     )
     (br_if $label$4
      (i32.lt_s
       (get_local $2)
       (i32.const 0)
      )
     )
     (br_if $label$4
      (i32.ne
       (get_local $5)
       (i32.const 1071644672)
      )
     )
     (return
      (call $sqrt
       (get_local $0)
      )
     )
    )
    (return
     (f64.div
      (f64.const 1)
      (get_local $0)
     )
    )
   )
   (set_local $21
    (call $fabs
     (get_local $0)
    )
   )
   (block $label$13
    (block $label$14
     (block $label$15
      (block $label$16
       (block $label$17
        (br_if $label$17
         (get_local $3)
        )
        (br_if $label$16
         (i32.eqz
          (get_local $7)
         )
        )
        (br_if $label$16
         (i32.eq
          (i32.or
           (get_local $7)
           (i32.const 1073741824)
          )
          (i32.const 2146435072)
         )
        )
       )
       (set_local $10
        (f64.const 1)
       )
       (br_if $label$13
        (i32.gt_s
         (get_local $2)
         (i32.const -1)
        )
       )
       (br_if $label$15
        (i32.eq
         (get_local $19)
         (i32.const 1)
        )
       )
       (br_if $label$13
        (get_local $19)
       )
       (return
        (f64.div
         (tee_local $1
          (f64.sub
           (get_local $0)
           (get_local $0)
          )
         )
         (get_local $1)
        )
       )
      )
      (set_local $21
       (select
        (f64.div
         (f64.const 1)
         (get_local $21)
        )
        (get_local $21)
        (i32.lt_s
         (get_local $5)
         (i32.const 0)
        )
       )
      )
      (br_if $label$0
       (i32.gt_s
        (get_local $2)
        (i32.const -1)
       )
      )
      (br_if $label$14
       (i32.eqz
        (i32.or
         (get_local $19)
         (i32.add
          (get_local $7)
          (i32.const -1072693248)
         )
        )
       )
      )
      (return
       (select
        (f64.neg
         (get_local $21)
        )
        (get_local $21)
        (i32.eq
         (get_local $19)
         (i32.const 1)
        )
       )
      )
     )
     (set_local $10
      (f64.const -1)
     )
     (br $label$13)
    )
    (return
     (f64.div
      (tee_local $1
       (f64.sub
        (get_local $21)
        (get_local $21)
       )
      )
      (get_local $1)
     )
    )
   )
   (block $label$18
    (block $label$19
     (block $label$20
      (block $label$21
       (block $label$22
        (block $label$23
         (block $label$24
          (block $label$25
           (block $label$26
            (block $label$27
             (br_if $label$27
              (i32.lt_u
               (get_local $8)
               (i32.const 1105199105)
              )
             )
             (br_if $label$26
              (i32.lt_u
               (get_local $8)
               (i32.const 1139802113)
              )
             )
             (br_if $label$23
              (i32.gt_u
               (get_local $7)
               (i32.const 1072693247)
              )
             )
             (return
              (select
               (f64.const inf)
               (f64.const 0)
               (i32.lt_s
                (get_local $5)
                (i32.const 0)
               )
              )
             )
            )
            (set_local $8
             (i32.const 0)
            )
            (br_if $label$25
             (i32.gt_u
              (get_local $7)
              (i32.const 1048575)
             )
            )
            (set_local $7
             (i32.wrap/i64
              (i64.shr_u
               (i64.reinterpret/f64
                (tee_local $21
                 (f64.mul
                  (get_local $21)
                  (f64.const 9007199254740992)
                 )
                )
               )
               (i64.const 32)
              )
             )
            )
            (set_local $5
             (i32.const -53)
            )
            (br $label$24)
           )
           (br_if $label$22
            (i32.gt_u
             (get_local $7)
             (i32.const 1072693246)
            )
           )
           (return
            (f64.mul
             (tee_local $1
              (select
               (f64.const 1.e+300)
               (f64.const 1e-300)
               (i32.lt_s
                (get_local $5)
                (i32.const 0)
               )
              )
             )
             (f64.mul
              (get_local $1)
              (get_local $10)
             )
            )
           )
          )
          (set_local $5
           (i32.const 0)
          )
         )
         (set_local $2
          (i32.or
           (tee_local $6
            (i32.and
             (get_local $7)
             (i32.const 1048575)
            )
           )
           (i32.const 1072693248)
          )
         )
         (set_local $5
          (i32.add
           (i32.add
            (i32.shr_s
             (get_local $7)
             (i32.const 20)
            )
            (get_local $5)
           )
           (i32.const -1023)
          )
         )
         (br_if $label$20
          (i32.lt_u
           (get_local $6)
           (i32.const 235663)
          )
         )
         (br_if $label$21
          (i32.ge_u
           (get_local $6)
           (i32.const 767610)
          )
         )
         (set_local $8
          (i32.const 1)
         )
         (br $label$20)
        )
        (return
         (select
          (f64.const inf)
          (f64.const 0)
          (i32.gt_s
           (get_local $5)
           (i32.const 0)
          )
         )
        )
       )
       (br_if $label$19
        (i32.lt_u
         (get_local $7)
         (i32.const 1072693249)
        )
       )
       (return
        (f64.mul
         (tee_local $1
          (select
           (f64.const 1.e+300)
           (f64.const 1e-300)
           (i32.gt_s
            (get_local $5)
            (i32.const 0)
           )
          )
         )
         (f64.mul
          (get_local $1)
          (get_local $10)
         )
        )
       )
      )
      (set_local $2
       (i32.add
        (get_local $2)
        (i32.const -1048576)
       )
      )
      (set_local $5
       (i32.add
        (get_local $5)
        (i32.const 1)
       )
      )
     )
     (set_local $20
      (f64.sub
       (f64.sub
        (f64.sub
         (tee_local $0
          (f64.reinterpret/i64
           (i64.and
            (i64.reinterpret/f64
             (f64.add
              (tee_local $20
               (f64.convert_s/i32
                (get_local $5)
               )
              )
              (f64.add
               (tee_local $18
                (f64.load
                 (i32.add
                  (tee_local $6
                   (i32.shl
                    (get_local $8)
                    (i32.const 3)
                   )
                  )
                  (i32.const 3696)
                 )
                )
               )
               (f64.add
                (tee_local $12
                 (f64.mul
                  (tee_local $0
                   (f64.reinterpret/i64
                    (i64.and
                     (i64.reinterpret/f64
                      (f64.add
                       (tee_local $14
                        (f64.mul
                         (tee_local $0
                          (f64.reinterpret/i64
                           (i64.and
                            (i64.reinterpret/f64
                             (tee_local $21
                              (f64.mul
                               (tee_local $14
                                (f64.sub
                                 (tee_local $12
                                  (f64.reinterpret/i64
                                   (i64.or
                                    (i64.shl
                                     (i64.extend_u/i32
                                      (get_local $2)
                                     )
                                     (i64.const 32)
                                    )
                                    (i64.and
                                     (i64.reinterpret/f64
                                      (get_local $21)
                                     )
                                     (i64.const 4294967295)
                                    )
                                   )
                                  )
                                 )
                                 (tee_local $13
                                  (f64.load
                                   (i32.add
                                    (get_local $6)
                                    (i32.const 3664)
                                   )
                                  )
                                 )
                                )
                               )
                               (tee_local $15
                                (f64.div
                                 (f64.const 1)
                                 (f64.add
                                  (get_local $13)
                                  (get_local $12)
                                 )
                                )
                               )
                              )
                             )
                            )
                            (i64.const -4294967296)
                           )
                          )
                         )
                         (tee_local $0
                          (f64.reinterpret/i64
                           (i64.and
                            (i64.reinterpret/f64
                             (f64.add
                              (f64.add
                               (tee_local $17
                                (f64.mul
                                 (get_local $0)
                                 (get_local $0)
                                )
                               )
                               (f64.const 3)
                              )
                              (tee_local $13
                               (f64.add
                                (f64.mul
                                 (f64.add
                                  (get_local $21)
                                  (get_local $0)
                                 )
                                 (tee_local $12
                                  (f64.mul
                                   (get_local $15)
                                   (f64.sub
                                    (f64.sub
                                     (get_local $14)
                                     (f64.mul
                                      (get_local $0)
                                      (tee_local $16
                                       (f64.reinterpret/i64
                                        (i64.shl
                                         (i64.extend_u/i32
                                          (i32.add
                                           (i32.add
                                            (i32.or
                                             (i32.shr_s
                                              (get_local $2)
                                              (i32.const 1)
                                             )
                                             (i32.const 536870912)
                                            )
                                            (i32.shl
                                             (get_local $8)
                                             (i32.const 18)
                                            )
                                           )
                                           (i32.const 524288)
                                          )
                                         )
                                         (i64.const 32)
                                        )
                                       )
                                      )
                                     )
                                    )
                                    (f64.mul
                                     (get_local $0)
                                     (f64.sub
                                      (get_local $12)
                                      (f64.sub
                                       (get_local $16)
                                       (get_local $13)
                                      )
                                     )
                                    )
                                   )
                                  )
                                 )
                                )
                                (f64.mul
                                 (f64.mul
                                  (tee_local $0
                                   (f64.mul
                                    (get_local $21)
                                    (get_local $21)
                                   )
                                  )
                                  (get_local $0)
                                 )
                                 (f64.add
                                  (f64.mul
                                   (get_local $0)
                                   (f64.add
                                    (f64.mul
                                     (get_local $0)
                                     (f64.add
                                      (f64.mul
                                       (get_local $0)
                                       (f64.add
                                        (f64.mul
                                         (get_local $0)
                                         (f64.add
                                          (f64.mul
                                           (get_local $0)
                                           (f64.const 0.20697501780033842)
                                          )
                                          (f64.const 0.23066074577556175)
                                         )
                                        )
                                        (f64.const 0.272728123808534)
                                       )
                                      )
                                      (f64.const 0.33333332981837743)
                                     )
                                    )
                                    (f64.const 0.4285714285785502)
                                   )
                                  )
                                  (f64.const 0.5999999999999946)
                                 )
                                )
                               )
                              )
                             )
                            )
                            (i64.const -4294967296)
                           )
                          )
                         )
                        )
                       )
                       (tee_local $21
                        (f64.add
                         (f64.mul
                          (get_local $12)
                          (get_local $0)
                         )
                         (f64.mul
                          (get_local $21)
                          (f64.sub
                           (get_local $13)
                           (f64.sub
                            (f64.add
                             (get_local $0)
                             (f64.const -3)
                            )
                            (get_local $17)
                           )
                          )
                         )
                        )
                       )
                      )
                     )
                     (i64.const -4294967296)
                    )
                   )
                  )
                  (f64.const 0.9617967009544373)
                 )
                )
                (tee_local $13
                 (f64.add
                  (f64.load
                   (i32.add
                    (get_local $6)
                    (i32.const 3680)
                   )
                  )
                  (f64.add
                   (f64.mul
                    (f64.sub
                     (get_local $21)
                     (f64.sub
                      (get_local $0)
                      (get_local $14)
                     )
                    )
                    (f64.const 0.9617966939259756)
                   )
                   (f64.mul
                    (get_local $0)
                    (f64.const -7.028461650952758e-09)
                   )
                  )
                 )
                )
               )
              )
             )
            )
            (i64.const -4294967296)
           )
          )
         )
         (get_local $20)
        )
        (get_local $18)
       )
       (get_local $12)
      )
     )
     (br $label$18)
    )
    (set_local $20
     (f64.sub
      (tee_local $0
       (f64.reinterpret/i64
        (i64.and
         (i64.reinterpret/f64
          (f64.add
           (tee_local $21
            (f64.mul
             (tee_local $0
              (f64.add
               (get_local $21)
               (f64.const -1)
              )
             )
             (f64.const 1.4426950216293335)
            )
           )
           (tee_local $13
            (f64.add
             (f64.mul
              (get_local $0)
              (f64.const 1.9259629911266175e-08)
             )
             (f64.mul
              (f64.mul
               (f64.mul
                (get_local $0)
                (get_local $0)
               )
               (f64.sub
                (f64.const 0.5)
                (f64.mul
                 (get_local $0)
                 (f64.add
                  (f64.mul
                   (get_local $0)
                   (f64.const -0.25)
                  )
                  (f64.const 0.3333333333333333)
                 )
                )
               )
              )
              (f64.const -1.4426950408889634)
             )
            )
           )
          )
         )
         (i64.const -4294967296)
        )
       )
      )
      (get_local $21)
     )
    )
   )
   (set_local $8
    (i32.wrap/i64
     (tee_local $4
      (i64.reinterpret/f64
       (tee_local $0
        (f64.add
         (tee_local $21
          (f64.mul
           (tee_local $12
            (f64.reinterpret/i64
             (i64.and
              (get_local $4)
              (i64.const -4294967296)
             )
            )
           )
           (get_local $0)
          )
         )
         (tee_local $1
          (f64.add
           (f64.mul
            (f64.sub
             (get_local $1)
             (get_local $12)
            )
            (get_local $0)
           )
           (f64.mul
            (f64.sub
             (get_local $13)
             (get_local $20)
            )
            (get_local $1)
           )
          )
         )
        )
       )
      )
     )
    )
   )
   (block $label$28
    (block $label$29
     (block $label$30
      (block $label$31
       (block $label$32
        (br_if $label$32
         (i32.lt_s
          (tee_local $2
           (i32.wrap/i64
            (i64.shr_u
             (get_local $4)
             (i64.const 32)
            )
           )
          )
          (i32.const 1083179008)
         )
        )
        (br_if $label$31
         (i32.eqz
          (i32.or
           (i32.add
            (get_local $2)
            (i32.const -1083179008)
           )
           (get_local $8)
          )
         )
        )
        (return
         (f64.mul
          (f64.mul
           (get_local $10)
           (f64.const 1.e+300)
          )
          (f64.const 1.e+300)
         )
        )
       )
       (br_if $label$29
        (i32.lt_u
         (i32.and
          (get_local $2)
          (i32.const 2147482624)
         )
         (i32.const 1083231232)
        )
       )
       (br_if $label$30
        (i32.eqz
         (i32.or
          (i32.add
           (get_local $2)
           (i32.const 1064252416)
          )
          (get_local $8)
         )
        )
       )
       (return
        (f64.mul
         (f64.mul
          (get_local $10)
          (f64.const 1e-300)
         )
         (f64.const 1e-300)
        )
       )
      )
      (br_if $label$29
       (i32.or
        (f64.le
         (tee_local $12
          (f64.add
           (get_local $1)
           (f64.const 8.008566259537294e-17)
          )
         )
         (tee_local $0
          (f64.sub
           (get_local $0)
           (get_local $21)
          )
         )
        )
        (i32.or
         (f64.ne
          (get_local $12)
          (get_local $12)
         )
         (f64.ne
          (get_local $0)
          (get_local $0)
         )
        )
       )
      )
      (return
       (f64.mul
        (f64.mul
         (get_local $10)
         (f64.const 1.e+300)
        )
        (f64.const 1.e+300)
       )
      )
     )
     (br_if $label$28
      (i32.eqz
       (i32.or
        (f64.gt
         (get_local $1)
         (tee_local $0
          (f64.sub
           (get_local $0)
           (get_local $21)
          )
         )
        )
        (i32.or
         (f64.ne
          (get_local $1)
          (get_local $1)
         )
         (f64.ne
          (get_local $0)
          (get_local $0)
         )
        )
       )
      )
     )
    )
    (block $label$33
     (block $label$34
      (br_if $label$34
       (i32.lt_u
        (tee_local $8
         (i32.and
          (get_local $2)
          (i32.const 2147483647)
         )
        )
        (i32.const 1071644673)
       )
      )
      (set_local $2
       (select
        (i32.sub
         (i32.const 0)
         (tee_local $5
          (i32.shr_u
           (i32.or
            (i32.and
             (tee_local $8
              (i32.add
               (i32.shr_u
                (i32.const 1048576)
                (i32.add
                 (i32.shr_u
                  (get_local $8)
                  (i32.const 20)
                 )
                 (i32.const -1022)
                )
               )
               (get_local $2)
              )
             )
             (i32.const 1048575)
            )
            (i32.const 1048576)
           )
           (i32.sub
            (i32.const 1043)
            (tee_local $6
             (i32.and
              (i32.shr_u
               (get_local $8)
               (i32.const 20)
              )
              (i32.const 2047)
             )
            )
           )
          )
         )
        )
        (get_local $5)
        (i32.lt_s
         (get_local $2)
         (i32.const 0)
        )
       )
      )
      (set_local $21
       (f64.sub
        (get_local $21)
        (f64.reinterpret/i64
         (i64.shl
          (i64.extend_u/i32
           (i32.and
            (get_local $8)
            (i32.xor
             (i32.shr_u
              (i32.const 1048575)
              (i32.add
               (get_local $6)
               (i32.const -1023)
              )
             )
             (i32.const -1)
            )
           )
          )
          (i64.const 32)
         )
        )
       )
      )
      (br $label$33)
     )
     (set_local $2
      (i32.const 0)
     )
    )
    (block $label$35
     (br_if $label$35
      (i32.le_s
       (i32.shr_s
        (tee_local $8
         (i32.add
          (i32.wrap/i64
           (i64.shr_u
            (tee_local $4
             (i64.reinterpret/f64
              (tee_local $1
               (f64.sub
                (f64.const 1)
                (f64.sub
                 (f64.sub
                  (f64.div
                   (f64.mul
                    (tee_local $1
                     (f64.add
                      (tee_local $12
                       (f64.mul
                        (tee_local $0
                         (f64.reinterpret/i64
                          (i64.and
                           (i64.reinterpret/f64
                            (f64.add
                             (get_local $1)
                             (get_local $21)
                            )
                           )
                           (i64.const -4294967296)
                          )
                         )
                        )
                        (f64.const 0.6931471824645996)
                       )
                      )
                      (tee_local $21
                       (f64.add
                        (f64.mul
                         (f64.sub
                          (get_local $1)
                          (f64.sub
                           (get_local $0)
                           (get_local $21)
                          )
                         )
                         (f64.const 0.6931471805599453)
                        )
                        (f64.mul
                         (get_local $0)
                         (f64.const -1.904654299957768e-09)
                        )
                       )
                      )
                     )
                    )
                    (tee_local $0
                     (f64.sub
                      (get_local $1)
                      (f64.mul
                       (tee_local $0
                        (f64.mul
                         (get_local $1)
                         (get_local $1)
                        )
                       )
                       (f64.add
                        (f64.mul
                         (get_local $0)
                         (f64.add
                          (f64.mul
                           (get_local $0)
                           (f64.add
                            (f64.mul
                             (get_local $0)
                             (f64.add
                              (f64.mul
                               (get_local $0)
                               (f64.const 4.1381367970572385e-08)
                              )
                              (f64.const -1.6533902205465252e-06)
                             )
                            )
                            (f64.const 6.613756321437934e-05)
                           )
                          )
                          (f64.const -2.7777777777015593e-03)
                         )
                        )
                        (f64.const 0.16666666666666602)
                       )
                      )
                     )
                    )
                   )
                   (f64.add
                    (get_local $0)
                    (f64.const -2)
                   )
                  )
                  (f64.add
                   (tee_local $0
                    (f64.sub
                     (get_local $21)
                     (f64.sub
                      (get_local $1)
                      (get_local $12)
                     )
                    )
                   )
                   (f64.mul
                    (get_local $1)
                    (get_local $0)
                   )
                  )
                 )
                 (get_local $1)
                )
               )
              )
             )
            )
            (i64.const 32)
           )
          )
          (i32.shl
           (get_local $2)
           (i32.const 20)
          )
         )
        )
        (i32.const 20)
       )
       (i32.const 0)
      )
     )
     (return
      (f64.mul
       (get_local $10)
       (f64.reinterpret/i64
        (i64.or
         (i64.shl
          (i64.extend_u/i32
           (get_local $8)
          )
          (i64.const 32)
         )
         (i64.and
          (get_local $4)
          (i64.const 4294967295)
         )
        )
       )
      )
     )
    )
    (return
     (f64.mul
      (get_local $10)
      (call $scalbn
       (get_local $1)
       (get_local $2)
      )
     )
    )
   )
   (return
    (f64.mul
     (f64.mul
      (get_local $10)
      (f64.const 1e-300)
     )
     (f64.const 1e-300)
    )
   )
  )
  (get_local $21)
 )
 (func $sqrt (param $0 f64) (result f64)
  (local $1 i64)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (block $label$0
   (br_if $label$0
    (i32.ne
     (i32.and
      (tee_local $7
       (i32.wrap/i64
        (i64.shr_u
         (tee_local $1
          (i64.reinterpret/f64
           (get_local $0)
          )
         )
         (i64.const 32)
        )
       )
      )
      (i32.const 2146435072)
     )
     (i32.const 2146435072)
    )
   )
   (return
    (f64.add
     (f64.mul
      (get_local $0)
      (get_local $0)
     )
     (get_local $0)
    )
   )
  )
  (set_local $2
   (i32.wrap/i64
    (get_local $1)
   )
  )
  (block $label$1
   (block $label$2
    (block $label$3
     (block $label$4
      (block $label$5
       (br_if $label$5
        (i32.le_s
         (get_local $7)
         (i32.const 0)
        )
       )
       (br_if $label$3
        (tee_local $8
         (i32.wrap/i64
          (i64.shr_u
           (get_local $1)
           (i64.const 52)
          )
         )
        )
       )
       (set_local $8
        (i32.const 1)
       )
       (set_local $9
        (get_local $2)
       )
       (br $label$4)
      )
      (br_if $label$2
       (i32.eqz
        (i32.or
         (i32.and
          (get_local $7)
          (i32.const 2147483647)
         )
         (get_local $2)
        )
       )
      )
      (br_if $label$1
       (i32.lt_s
        (get_local $7)
        (i32.const 0)
       )
      )
      (set_local $8
       (i32.const 1)
      )
      (loop $label$6
       (set_local $8
        (i32.add
         (get_local $8)
         (i32.const -21)
        )
       )
       (set_local $7
        (i32.shr_u
         (get_local $2)
         (i32.const 11)
        )
       )
       (set_local $2
        (tee_local $9
         (i32.shl
          (get_local $2)
          (i32.const 21)
         )
        )
       )
       (br_if $label$6
        (i32.eqz
         (get_local $7)
        )
       )
      )
     )
     (set_local $5
      (i32.const 0)
     )
     (block $label$7
      (br_if $label$7
       (i32.and
        (get_local $7)
        (i32.const 1048576)
       )
      )
      (set_local $5
       (i32.const 0)
      )
      (loop $label$8
       (set_local $5
        (i32.add
         (get_local $5)
         (i32.const 1)
        )
       )
       (br_if $label$8
        (i32.eqz
         (i32.and
          (tee_local $7
           (i32.shl
            (get_local $7)
            (i32.const 1)
           )
          )
          (i32.const 1048576)
         )
        )
       )
      )
     )
     (set_local $2
      (i32.shl
       (get_local $9)
       (get_local $5)
      )
     )
     (set_local $8
      (i32.sub
       (get_local $8)
       (get_local $5)
      )
     )
     (set_local $7
      (i32.or
       (i32.shr_u
        (get_local $9)
        (i32.sub
         (i32.const 32)
         (get_local $5)
        )
       )
       (get_local $7)
      )
     )
    )
    (set_local $7
     (i32.or
      (i32.and
       (get_local $7)
       (i32.const 1048575)
      )
      (i32.const 1048576)
     )
    )
    (block $label$9
     (br_if $label$9
      (i32.eqz
       (i32.and
        (tee_local $10
         (i32.add
          (get_local $8)
          (i32.const -1023)
         )
        )
        (i32.const 1)
       )
      )
     )
     (set_local $7
      (i32.or
       (i32.shl
        (get_local $7)
        (i32.const 1)
       )
       (i32.shr_u
        (get_local $2)
        (i32.const 31)
       )
      )
     )
     (set_local $2
      (i32.shl
       (get_local $2)
       (i32.const 1)
      )
     )
    )
    (set_local $7
     (i32.or
      (i32.shr_u
       (get_local $2)
       (i32.const 31)
      )
      (i32.shl
       (get_local $7)
       (i32.const 1)
      )
     )
    )
    (set_local $5
     (i32.shl
      (get_local $2)
      (i32.const 1)
     )
    )
    (set_local $4
     (i32.const 0)
    )
    (set_local $9
     (i32.const 2097152)
    )
    (set_local $8
     (i32.const 0)
    )
    (loop $label$10
     (set_local $6
      (get_local $5)
     )
     (block $label$11
      (br_if $label$11
       (i32.lt_s
        (get_local $7)
        (tee_local $5
         (i32.add
          (get_local $9)
          (get_local $8)
         )
        )
       )
      )
      (set_local $4
       (i32.add
        (get_local $9)
        (get_local $4)
       )
      )
      (set_local $7
       (i32.sub
        (get_local $7)
        (get_local $5)
       )
      )
      (set_local $8
       (i32.add
        (get_local $5)
        (get_local $9)
       )
      )
     )
     (set_local $7
      (i32.or
       (i32.shl
        (get_local $7)
        (i32.const 1)
       )
       (i32.and
        (i32.shr_u
         (get_local $2)
         (i32.const 30)
        )
        (i32.const 1)
       )
      )
     )
     (set_local $5
      (i32.shl
       (get_local $6)
       (i32.const 1)
      )
     )
     (set_local $2
      (get_local $6)
     )
     (br_if $label$10
      (tee_local $9
       (i32.shr_u
        (get_local $9)
        (i32.const 1)
       )
      )
     )
    )
    (set_local $3
     (i32.shr_u
      (get_local $10)
      (i32.const 1)
     )
    )
    (set_local $9
     (i32.const -2147483648)
    )
    (set_local $10
     (i32.const 0)
    )
    (set_local $2
     (i32.const 0)
    )
    (loop $label$12
     (set_local $6
      (i32.add
       (get_local $2)
       (get_local $9)
      )
     )
     (block $label$13
      (block $label$14
       (br_if $label$14
        (i32.gt_s
         (get_local $7)
         (get_local $8)
        )
       )
       (br_if $label$13
        (i32.ne
         (get_local $7)
         (get_local $8)
        )
       )
       (br_if $label$13
        (i32.lt_u
         (get_local $5)
         (get_local $6)
        )
       )
      )
      (set_local $7
       (i32.add
        (i32.sub
         (get_local $7)
         (get_local $8)
        )
        (select
         (i32.const -1)
         (i32.const 0)
         (i32.lt_u
          (get_local $5)
          (get_local $6)
         )
        )
       )
      )
      (set_local $8
       (i32.add
        (i32.and
         (i32.lt_s
          (get_local $6)
          (i32.const 0)
         )
         (i32.gt_s
          (tee_local $2
           (i32.add
            (get_local $6)
            (get_local $9)
           )
          )
          (i32.const -1)
         )
        )
        (get_local $8)
       )
      )
      (set_local $10
       (i32.add
        (get_local $10)
        (get_local $9)
       )
      )
      (set_local $5
       (i32.sub
        (get_local $5)
        (get_local $6)
       )
      )
     )
     (set_local $7
      (i32.or
       (i32.shr_u
        (get_local $5)
        (i32.const 31)
       )
       (i32.shl
        (get_local $7)
        (i32.const 1)
       )
      )
     )
     (set_local $5
      (i32.shl
       (get_local $5)
       (i32.const 1)
      )
     )
     (br_if $label$12
      (tee_local $9
       (i32.shr_u
        (get_local $9)
        (i32.const 1)
       )
      )
     )
    )
    (block $label$15
     (br_if $label$15
      (i32.eqz
       (i32.or
        (get_local $5)
        (get_local $7)
       )
      )
     )
     (block $label$16
      (br_if $label$16
       (i32.eq
        (get_local $10)
        (i32.const -1)
       )
      )
      (set_local $10
       (i32.add
        (i32.and
         (get_local $10)
         (i32.const 1)
        )
        (get_local $10)
       )
      )
      (br $label$15)
     )
     (set_local $4
      (i32.add
       (get_local $4)
       (i32.const 1)
      )
     )
     (set_local $10
      (i32.const 0)
     )
    )
    (set_local $0
     (f64.reinterpret/i64
      (i64.or
       (i64.shl
        (i64.extend_u/i32
         (i32.add
          (i32.add
           (i32.shl
            (get_local $3)
            (i32.const 20)
           )
           (i32.shr_s
            (get_local $4)
            (i32.const 1)
           )
          )
          (i32.const 1071644672)
         )
        )
        (i64.const 32)
       )
       (i64.extend_u/i32
        (i32.or
         (i32.shr_u
          (get_local $10)
          (i32.const 1)
         )
         (i32.shl
          (get_local $4)
          (i32.const 31)
         )
        )
       )
      )
     )
    )
   )
   (return
    (get_local $0)
   )
  )
  (f64.div
   (tee_local $0
    (f64.sub
     (get_local $0)
     (get_local $0)
    )
   )
   (get_local $0)
  )
 )
 (func $fabs (param $0 f64) (result f64)
  (f64.reinterpret/i64
   (i64.and
    (i64.reinterpret/f64
     (get_local $0)
    )
    (i64.const 9223372036854775807)
   )
  )
 )
 (func $scalbn (param $0 f64) (param $1 i32) (result f64)
  (local $2 i32)
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.lt_s
        (get_local $1)
        (i32.const 1024)
       )
      )
      (set_local $0
       (f64.mul
        (get_local $0)
        (f64.const 8988465674311579538646525e283)
       )
      )
      (br_if $label$2
       (i32.lt_s
        (tee_local $2
         (i32.add
          (get_local $1)
          (i32.const -1023)
         )
        )
        (i32.const 1024)
       )
      )
      (set_local $1
       (select
        (tee_local $1
         (i32.add
          (get_local $1)
          (i32.const -2046)
         )
        )
        (i32.const 1023)
        (i32.lt_s
         (get_local $1)
         (i32.const 1023)
        )
       )
      )
      (set_local $0
       (f64.mul
        (get_local $0)
        (f64.const 8988465674311579538646525e283)
       )
      )
      (br $label$0)
     )
     (br_if $label$0
      (i32.gt_s
       (get_local $1)
       (i32.const -1023)
      )
     )
     (set_local $0
      (f64.mul
       (get_local $0)
       (f64.const 2.004168360008973e-292)
      )
     )
     (br_if $label$1
      (i32.gt_s
       (tee_local $2
        (i32.add
         (get_local $1)
         (i32.const 969)
        )
       )
       (i32.const -1023)
      )
     )
     (set_local $1
      (select
       (tee_local $1
        (i32.add
         (get_local $1)
         (i32.const 1938)
        )
       )
       (i32.const -1022)
       (i32.gt_s
        (get_local $1)
        (i32.const -1022)
       )
      )
     )
     (set_local $0
      (f64.mul
       (get_local $0)
       (f64.const 2.004168360008973e-292)
      )
     )
     (br $label$0)
    )
    (set_local $1
     (get_local $2)
    )
    (br $label$0)
   )
   (set_local $1
    (get_local $2)
   )
  )
  (f64.mul
   (get_local $0)
   (f64.reinterpret/i64
    (i64.shl
     (i64.extend_u/i32
      (i32.add
       (get_local $1)
       (i32.const 1023)
      )
     )
     (i64.const 52)
    )
   )
  )
 )
 (func $memcmp (param $0 i32) (param $1 i32) (param $2 i32) (result i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (set_local $5
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (get_local $2)
    )
   )
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.ne
       (tee_local $3
        (i32.load8_u
         (get_local $0)
        )
       )
       (tee_local $4
        (i32.load8_u
         (get_local $1)
        )
       )
      )
     )
     (set_local $1
      (i32.add
       (get_local $1)
       (i32.const 1)
      )
     )
     (set_local $0
      (i32.add
       (get_local $0)
       (i32.const 1)
      )
     )
     (br_if $label$2
      (tee_local $2
       (i32.add
        (get_local $2)
        (i32.const -1)
       )
      )
     )
     (br $label$0)
    )
   )
   (set_local $5
    (i32.sub
     (get_local $3)
     (get_local $4)
    )
   )
  )
  (get_local $5)
 )
 (func $strlen (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (set_local $2
   (get_local $0)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (i32.and
       (get_local $0)
       (i32.const 3)
      )
     )
    )
    (set_local $2
     (get_local $0)
    )
    (loop $label$2
     (br_if $label$0
      (i32.eqz
       (i32.load8_u
        (get_local $2)
       )
      )
     )
     (br_if $label$2
      (i32.and
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 3)
      )
     )
    )
   )
   (set_local $2
    (i32.add
     (get_local $2)
     (i32.const -4)
    )
   )
   (loop $label$3
    (br_if $label$3
     (i32.eqz
      (i32.and
       (i32.and
        (i32.xor
         (tee_local $1
          (i32.load
           (tee_local $2
            (i32.add
             (get_local $2)
             (i32.const 4)
            )
           )
          )
         )
         (i32.const -1)
        )
        (i32.add
         (get_local $1)
         (i32.const -16843009)
        )
       )
       (i32.const -2139062144)
      )
     )
    )
   )
   (br_if $label$0
    (i32.eqz
     (i32.and
      (get_local $1)
      (i32.const 255)
     )
    )
   )
   (loop $label$4
    (br_if $label$4
     (i32.load8_u
      (tee_local $2
       (i32.add
        (get_local $2)
        (i32.const 1)
       )
      )
     )
    )
   )
  )
  (i32.sub
   (get_local $2)
   (get_local $0)
  )
 )
 (func $malloc (param $0 i32) (result i32)
  (call $_ZN5eosio14memory_manager6mallocEm
   (i32.const 3712)
   (get_local $0)
  )
 )
 (func $_ZN5eosio14memory_manager6mallocEm (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (local $12 i32)
  (local $13 i32)
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (get_local $1)
    )
   )
   (block $label$1
    (br_if $label$1
     (tee_local $13
      (i32.load offset=8384
       (get_local $0)
      )
     )
    )
    (set_local $13
     (i32.const 16)
    )
    (i32.store
     (i32.add
      (get_local $0)
      (i32.const 8384)
     )
     (i32.const 16)
    )
   )
   (set_local $2
    (select
     (i32.sub
      (i32.add
       (get_local $1)
       (i32.const 8)
      )
      (tee_local $2
       (i32.and
        (i32.add
         (get_local $1)
         (i32.const 4)
        )
        (i32.const 7)
       )
      )
     )
     (get_local $1)
     (get_local $2)
    )
   )
   (block $label$2
    (block $label$3
     (block $label$4
      (br_if $label$4
       (i32.ge_u
        (tee_local $10
         (i32.load offset=8388
          (get_local $0)
         )
        )
        (get_local $13)
       )
      )
      (set_local $1
       (i32.add
        (i32.add
         (get_local $0)
         (i32.mul
          (get_local $10)
          (i32.const 12)
         )
        )
        (i32.const 8192)
       )
      )
      (block $label$5
       (br_if $label$5
        (get_local $10)
       )
       (br_if $label$5
        (i32.load
         (tee_local $13
          (i32.add
           (get_local $0)
           (i32.const 8196)
          )
         )
        )
       )
       (i32.store
        (get_local $1)
        (i32.const 8192)
       )
       (i32.store
        (get_local $13)
        (get_local $0)
       )
      )
      (set_local $10
       (i32.add
        (get_local $2)
        (i32.const 4)
       )
      )
      (loop $label$6
       (block $label$7
        (br_if $label$7
         (i32.gt_u
          (i32.add
           (tee_local $13
            (i32.load offset=8
             (get_local $1)
            )
           )
           (get_local $10)
          )
          (i32.load
           (get_local $1)
          )
         )
        )
        (i32.store
         (tee_local $13
          (i32.add
           (i32.load offset=4
            (get_local $1)
           )
           (get_local $13)
          )
         )
         (i32.or
          (i32.and
           (i32.load
            (get_local $13)
           )
           (i32.const -2147483648)
          )
          (get_local $2)
         )
        )
        (i32.store
         (tee_local $1
          (i32.add
           (get_local $1)
           (i32.const 8)
          )
         )
         (i32.add
          (i32.load
           (get_local $1)
          )
          (get_local $10)
         )
        )
        (i32.store
         (get_local $13)
         (i32.or
          (i32.load
           (get_local $13)
          )
          (i32.const -2147483648)
         )
        )
        (br_if $label$3
         (tee_local $1
          (i32.add
           (get_local $13)
           (i32.const 4)
          )
         )
        )
       )
       (br_if $label$6
        (tee_local $1
         (call $_ZN5eosio14memory_manager16next_active_heapEv
          (get_local $0)
         )
        )
       )
      )
     )
     (set_local $4
      (i32.sub
       (i32.const 2147483644)
       (get_local $2)
      )
     )
     (set_local $11
      (i32.add
       (get_local $0)
       (i32.const 8392)
      )
     )
     (set_local $12
      (i32.add
       (get_local $0)
       (i32.const 8384)
      )
     )
     (set_local $13
      (tee_local $3
       (i32.load offset=8392
        (get_local $0)
       )
      )
     )
     (loop $label$8
      (call $eosio_assert
       (i32.eq
        (i32.load
         (i32.add
          (tee_local $1
           (i32.add
            (get_local $0)
            (i32.mul
             (get_local $13)
             (i32.const 12)
            )
           )
          )
          (i32.const 8200)
         )
        )
        (i32.load
         (tee_local $5
          (i32.add
           (get_local $1)
           (i32.const 8192)
          )
         )
        )
       )
       (i32.const 12112)
      )
      (set_local $13
       (i32.add
        (tee_local $6
         (i32.load
          (i32.add
           (get_local $1)
           (i32.const 8196)
          )
         )
        )
        (i32.const 4)
       )
      )
      (loop $label$9
       (set_local $7
        (i32.add
         (get_local $6)
         (i32.load
          (get_local $5)
         )
        )
       )
       (set_local $1
        (i32.and
         (tee_local $9
          (i32.load
           (tee_local $8
            (i32.add
             (get_local $13)
             (i32.const -4)
            )
           )
          )
         )
         (i32.const 2147483647)
        )
       )
       (block $label$10
        (br_if $label$10
         (i32.lt_s
          (get_local $9)
          (i32.const 0)
         )
        )
        (block $label$11
         (br_if $label$11
          (i32.ge_u
           (get_local $1)
           (get_local $2)
          )
         )
         (loop $label$12
          (br_if $label$11
           (i32.ge_u
            (tee_local $10
             (i32.add
              (get_local $13)
              (get_local $1)
             )
            )
            (get_local $7)
           )
          )
          (br_if $label$11
           (i32.lt_s
            (tee_local $10
             (i32.load
              (get_local $10)
             )
            )
            (i32.const 0)
           )
          )
          (br_if $label$12
           (i32.lt_u
            (tee_local $1
             (i32.add
              (i32.add
               (get_local $1)
               (i32.and
                (get_local $10)
                (i32.const 2147483647)
               )
              )
              (i32.const 4)
             )
            )
            (get_local $2)
           )
          )
         )
        )
        (i32.store
         (get_local $8)
         (i32.or
          (select
           (get_local $1)
           (get_local $2)
           (i32.lt_u
            (get_local $1)
            (get_local $2)
           )
          )
          (i32.and
           (get_local $9)
           (i32.const -2147483648)
          )
         )
        )
        (block $label$13
         (br_if $label$13
          (i32.le_u
           (get_local $1)
           (get_local $2)
          )
         )
         (i32.store
          (i32.add
           (get_local $13)
           (get_local $2)
          )
          (i32.and
           (i32.add
            (get_local $4)
            (get_local $1)
           )
           (i32.const 2147483647)
          )
         )
        )
        (br_if $label$2
         (i32.ge_u
          (get_local $1)
          (get_local $2)
         )
        )
       )
       (br_if $label$9
        (i32.lt_u
         (tee_local $13
          (i32.add
           (i32.add
            (get_local $13)
            (get_local $1)
           )
           (i32.const 4)
          )
         )
         (get_local $7)
        )
       )
      )
      (set_local $1
       (i32.const 0)
      )
      (i32.store
       (get_local $11)
       (tee_local $13
        (select
         (i32.const 0)
         (tee_local $13
          (i32.add
           (i32.load
            (get_local $11)
           )
           (i32.const 1)
          )
         )
         (i32.eq
          (get_local $13)
          (i32.load
           (get_local $12)
          )
         )
        )
       )
      )
      (br_if $label$8
       (i32.ne
        (get_local $13)
        (get_local $3)
       )
      )
     )
    )
    (return
     (get_local $1)
    )
   )
   (i32.store
    (get_local $8)
    (i32.or
     (i32.load
      (get_local $8)
     )
     (i32.const -2147483648)
    )
   )
   (return
    (get_local $13)
   )
  )
  (i32.const 0)
 )
 (func $_ZN5eosio14memory_manager16next_active_heapEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (set_local $1
   (i32.load offset=8388
    (get_local $0)
   )
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (i32.load8_u offset=12198
       (i32.const 0)
      )
     )
    )
    (set_local $7
     (i32.load offset=12200
      (i32.const 0)
     )
    )
    (br $label$0)
   )
   (set_local $7
    (current_memory)
   )
   (i32.store8 offset=12198
    (i32.const 0)
    (i32.const 1)
   )
   (i32.store offset=12200
    (i32.const 0)
    (tee_local $7
     (i32.shl
      (get_local $7)
      (i32.const 16)
     )
    )
   )
  )
  (set_local $3
   (get_local $7)
  )
  (block $label$2
   (block $label$3
    (block $label$4
     (block $label$5
      (br_if $label$5
       (i32.le_u
        (tee_local $2
         (i32.shr_u
          (i32.add
           (get_local $7)
           (i32.const 65535)
          )
          (i32.const 16)
         )
        )
        (tee_local $8
         (current_memory)
        )
       )
      )
      (drop
       (grow_memory
        (i32.sub
         (get_local $2)
         (get_local $8)
        )
       )
      )
      (set_local $8
       (i32.const 0)
      )
      (br_if $label$4
       (i32.ne
        (get_local $2)
        (current_memory)
       )
      )
      (set_local $3
       (i32.load offset=12200
        (i32.const 0)
       )
      )
     )
     (set_local $8
      (i32.const 0)
     )
     (i32.store offset=12200
      (i32.const 0)
      (get_local $3)
     )
     (br_if $label$4
      (i32.lt_s
       (get_local $7)
       (i32.const 0)
      )
     )
     (set_local $2
      (i32.add
       (get_local $0)
       (i32.mul
        (get_local $1)
        (i32.const 12)
       )
      )
     )
     (set_local $7
      (i32.sub
       (i32.sub
        (i32.add
         (get_local $7)
         (select
          (i32.const 65536)
          (i32.const 131072)
          (tee_local $6
           (i32.lt_u
            (tee_local $8
             (i32.and
              (get_local $7)
              (i32.const 65535)
             )
            )
            (i32.const 64513)
           )
          )
         )
        )
        (select
         (get_local $8)
         (i32.and
          (get_local $7)
          (i32.const 131071)
         )
         (get_local $6)
        )
       )
       (get_local $7)
      )
     )
     (block $label$6
      (br_if $label$6
       (i32.load8_u offset=12198
        (i32.const 0)
       )
      )
      (set_local $3
       (current_memory)
      )
      (i32.store8 offset=12198
       (i32.const 0)
       (i32.const 1)
      )
      (i32.store offset=12200
       (i32.const 0)
       (tee_local $3
        (i32.shl
         (get_local $3)
         (i32.const 16)
        )
       )
      )
     )
     (set_local $2
      (i32.add
       (get_local $2)
       (i32.const 8192)
      )
     )
     (br_if $label$3
      (i32.lt_s
       (get_local $7)
       (i32.const 0)
      )
     )
     (set_local $6
      (get_local $3)
     )
     (block $label$7
      (br_if $label$7
       (i32.le_u
        (tee_local $8
         (i32.shr_u
          (i32.add
           (i32.add
            (tee_local $5
             (i32.and
              (i32.add
               (get_local $7)
               (i32.const 7)
              )
              (i32.const -8)
             )
            )
            (get_local $3)
           )
           (i32.const 65535)
          )
          (i32.const 16)
         )
        )
        (tee_local $4
         (current_memory)
        )
       )
      )
      (drop
       (grow_memory
        (i32.sub
         (get_local $8)
         (get_local $4)
        )
       )
      )
      (br_if $label$3
       (i32.ne
        (get_local $8)
        (current_memory)
       )
      )
      (set_local $6
       (i32.load offset=12200
        (i32.const 0)
       )
      )
     )
     (i32.store offset=12200
      (i32.const 0)
      (i32.add
       (get_local $6)
       (get_local $5)
      )
     )
     (br_if $label$3
      (i32.eq
       (get_local $3)
       (i32.const -1)
      )
     )
     (br_if $label$2
      (i32.eq
       (i32.add
        (tee_local $6
         (i32.load
          (i32.add
           (tee_local $1
            (i32.add
             (get_local $0)
             (i32.mul
              (get_local $1)
              (i32.const 12)
             )
            )
           )
           (i32.const 8196)
          )
         )
        )
        (tee_local $8
         (i32.load
          (get_local $2)
         )
        )
       )
       (get_local $3)
      )
     )
     (block $label$8
      (br_if $label$8
       (i32.eq
        (get_local $8)
        (tee_local $1
         (i32.load
          (tee_local $5
           (i32.add
            (get_local $1)
            (i32.const 8200)
           )
          )
         )
        )
       )
      )
      (i32.store
       (tee_local $6
        (i32.add
         (get_local $6)
         (get_local $1)
        )
       )
       (i32.or
        (i32.and
         (i32.load
          (get_local $6)
         )
         (i32.const -2147483648)
        )
        (i32.add
         (i32.sub
          (i32.const -4)
          (get_local $1)
         )
         (get_local $8)
        )
       )
      )
      (i32.store
       (get_local $5)
       (i32.load
        (get_local $2)
       )
      )
      (i32.store
       (get_local $6)
       (i32.and
        (i32.load
         (get_local $6)
        )
        (i32.const 2147483647)
       )
      )
     )
     (i32.store
      (tee_local $2
       (i32.add
        (get_local $0)
        (i32.const 8388)
       )
      )
      (tee_local $2
       (i32.add
        (i32.load
         (get_local $2)
        )
        (i32.const 1)
       )
      )
     )
     (i32.store
      (i32.add
       (tee_local $0
        (i32.add
         (get_local $0)
         (i32.mul
          (get_local $2)
          (i32.const 12)
         )
        )
       )
       (i32.const 8196)
      )
      (get_local $3)
     )
     (i32.store
      (tee_local $8
       (i32.add
        (get_local $0)
        (i32.const 8192)
       )
      )
      (get_local $7)
     )
    )
    (return
     (get_local $8)
    )
   )
   (block $label$9
    (br_if $label$9
     (i32.eq
      (tee_local $8
       (i32.load
        (get_local $2)
       )
      )
      (tee_local $7
       (i32.load
        (tee_local $1
         (i32.add
          (tee_local $3
           (i32.add
            (get_local $0)
            (i32.mul
             (get_local $1)
             (i32.const 12)
            )
           )
          )
          (i32.const 8200)
         )
        )
       )
      )
     )
    )
    (i32.store
     (tee_local $3
      (i32.add
       (i32.load
        (i32.add
         (get_local $3)
         (i32.const 8196)
        )
       )
       (get_local $7)
      )
     )
     (i32.or
      (i32.and
       (i32.load
        (get_local $3)
       )
       (i32.const -2147483648)
      )
      (i32.add
       (i32.sub
        (i32.const -4)
        (get_local $7)
       )
       (get_local $8)
      )
     )
    )
    (i32.store
     (get_local $1)
     (i32.load
      (get_local $2)
     )
    )
    (i32.store
     (get_local $3)
     (i32.and
      (i32.load
       (get_local $3)
      )
      (i32.const 2147483647)
     )
    )
   )
   (i32.store offset=8384
    (get_local $0)
    (tee_local $3
     (i32.add
      (i32.load
       (tee_local $7
        (i32.add
         (get_local $0)
         (i32.const 8388)
        )
       )
      )
      (i32.const 1)
     )
    )
   )
   (i32.store
    (get_local $7)
    (get_local $3)
   )
   (return
    (i32.const 0)
   )
  )
  (i32.store
   (get_local $2)
   (i32.add
    (get_local $8)
    (get_local $7)
   )
  )
  (get_local $2)
 )
 (func $free (param $0 i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i32)
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (get_local $0)
     )
    )
    (br_if $label$1
     (i32.lt_s
      (tee_local $2
       (i32.load offset=12096
        (i32.const 0)
       )
      )
      (i32.const 1)
     )
    )
    (set_local $3
     (i32.const 11904)
    )
    (set_local $1
     (i32.add
      (i32.mul
       (get_local $2)
       (i32.const 12)
      )
      (i32.const 11904)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i32.eqz
       (tee_local $2
        (i32.load
         (i32.add
          (get_local $3)
          (i32.const 4)
         )
        )
       )
      )
     )
     (block $label$3
      (br_if $label$3
       (i32.gt_u
        (i32.add
         (get_local $2)
         (i32.const 4)
        )
        (get_local $0)
       )
      )
      (br_if $label$0
       (i32.gt_u
        (i32.add
         (get_local $2)
         (i32.load
          (get_local $3)
         )
        )
        (get_local $0)
       )
      )
     )
     (br_if $label$2
      (i32.lt_u
       (tee_local $3
        (i32.add
         (get_local $3)
         (i32.const 12)
        )
       )
       (get_local $1)
      )
     )
    )
   )
   (return)
  )
  (i32.store
   (tee_local $3
    (i32.add
     (get_local $0)
     (i32.const -4)
    )
   )
   (i32.and
    (i32.load
     (get_local $3)
    )
    (i32.const 2147483647)
   )
  )
 )
 (func $__wasm_nullptr (type $FUNCSIG$v)
  (unreachable)
 )
)
