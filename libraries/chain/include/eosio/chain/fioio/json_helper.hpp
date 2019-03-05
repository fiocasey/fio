/** chain_control definitions file
 *  Description: Sets up the supported chain data structure
 *  @author Casey Gardiner
 *  @file fio_name_validator.hpp
 *  @copyright Dapix
 *
 *  Changes:
 */

#include <string>
#include <fc/io/json.hpp>
#include <boost/filesystem.hpp>
#include <eosio/chain/fioio/chain_control.hpp>

namespace fioio {

    using namespace std;
    namespace bs = boost::filesystem;

    inline void chain () {
        bs::path cp = bs::current_path() / "config" / "bip44chains.json";

        try {
            fc::json::from_file(cp).as<clist>(approvedTokens.chainList);
        } catch (const fc::exception ex) {
            elog ("from_file threw ${ex}", ("ex", ex));
        } catch (...) {
            elog ("failed to read ${f}", ("f", cp.string()));
        }
    };
}
FC_REFLECT(fioio::clentry, (index)(chain));
FC_REFLECT(fioio::clist, (chains));
