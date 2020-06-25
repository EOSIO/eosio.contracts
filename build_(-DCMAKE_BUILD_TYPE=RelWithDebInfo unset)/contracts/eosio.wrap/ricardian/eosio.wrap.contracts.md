<h1 class="contract">exec</h1>

---
spec_version: "0.2.0"
title: Privileged Execute
summary: '{{nowrap executer}} executes a transaction while bypassing authority checks'
icon: http://127.0.0.1/ricardian_assets/eosio.contracts/icons/admin.png#9bf1cec664863bd6aaac0f814b235f8799fb02c850e9aa5da34e8a004bd6518e
---

{{executer}} executes the following transaction while bypassing authority checks:
{{to_json trx}}

{{$action.account}} must also authorize this action.
