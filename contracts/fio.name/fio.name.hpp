/** FioName Token header file
 *  Description: FioName smart contract allows issuance of unique domains and names for easy public address resolution
 *  @author Adam Androulidakis, Ciju John, Casey Gardiner, Ed Rotthoff
 *  @file fio.name.hpp
 *  @copyright Dapix
 */

#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/asset.hpp>
#include <string>

using std::string;

namespace fioio {

    using namespace eosio;

    // @abi table fionames i64
    struct fioname {

        string name = nullptr;
        uint64_t namehash = 0;
        string domain = nullptr;
        uint64_t domainhash = 0;
        uint32_t expiration;
        uint64_t account;

        // Chain specific keys
        vector<string> addresses;

        // primary_key is required to store structure in multi_index table
        uint64_t primary_key() const { return namehash; }
        uint64_t by_domain() const { return domainhash; }

        EOSLIB_SERIALIZE(fioname, (name)(namehash)(domain)(domainhash)(expiration)(account)(addresses))
    };

    //Where fioname tokens are stored
    typedef multi_index<N(fionames), fioname,
            indexed_by<N(bydomain), const_mem_fun<fioname, uint64_t, &fioname::by_domain> > > fionames_table;

    // @abi table domains i64
    struct domain {
        string name;
        uint64_t domainhash;
        uint32_t expiration;
        uint64_t account;

        uint64_t primary_key() const { return domainhash; }
        uint64_t by_account() const { return account; }

        EOSLIB_SERIALIZE(domain, (name)(domainhash)(expiration)(account))
    };

    typedef multi_index<N(domains), domain,
            indexed_by<N(byaccount), const_mem_fun<domain, uint64_t, &domain::by_account> > > domains_table;

    // @abi table chains i64
    struct chainList {
        string chainname = nullptr;
        uint32_t id = 0;
        uint64_t chainhash = 0;

        uint64_t primary_key() const { return chainhash; }
        uint64_t by_index() const { return id; }

        EOSLIB_SERIALIZE(chainList, (chainname)(id)(chainhash))
    };

    typedef multi_index<N(chains), chainList> chains_table;

    // Structures/table for mapping chain key to FIO name
    // @abi table keynames i64
    struct key_name {
        uint64_t id;
        string key = nullptr;       // user key on a chain
        uint64_t keyhash = 0;       // chainkey hash
        uint64_t chaintype;         // maps to chain_control vector position
        string name = nullptr;      // FIO name
        uint32_t expiration;        //expiration of the fioname.

        uint64_t primary_key() const { return id; }
        uint64_t by_keyhash() const { return keyhash; }

        EOSLIB_SERIALIZE(key_name, (id)(key)(keyhash)(chaintype)(name)(expiration))
    };

    typedef multi_index<N(keynames), key_name,
            indexed_by<N(bykey), const_mem_fun<key_name, uint64_t, &key_name::by_keyhash> > > keynames_table;

    // Maps client wallet generated public keys to EOS user account names.
    // @abi table eosionames i64
    struct eosio_name {

        uint64_t account = 0;
        string clientkey = nullptr;

        uint64_t primary_key() const { return account; }

        EOSLIB_SERIALIZE(eosio_name, (account)(clientkey))
    };

    typedef multi_index<N(eosionames), eosio_name> eosio_names_table;


    //    struct config {
    //        name tokencontr; // owner of the token contract

    //        EOSLIB_SERIALIZE(config, (tokencontr))
    //    };

    //    typedef singleton<N(configs), config> configs;

    struct account {
        asset balance;

        uint64_t primary_key() const { return balance.symbol.name(); }
    };

    typedef eosio::multi_index<N(accounts), account> accounts;
}