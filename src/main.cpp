/*
 * Copyright (c) 2010-2020 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <framework/core/application.h>
#include <framework/core/resourcemanager.h>
#include <framework/luaengine/luainterface.h>
#include <client/client.h>

// ------ JUST FOR TESTING, TO BE REMOVED ------ 
#include <pwd.h>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <fc/crypto/hex.hpp>
#include <fc/variant.hpp>
#include <fc/io/datastream.hpp>
#include <fc/io/json.hpp>
#include <fc/io/console.hpp>
#include <fc/exception/exception.hpp>
#include <fc/variant_object.hpp>
#include <fc/static_variant.hpp>

#include <eosio/chain/name.hpp>
#include <eosio/chain/config.hpp>
#include <eosio/chain/wast_to_wasm.hpp>
#include <eosio/chain/trace.hpp>
#include <eosio/chain_plugin/chain_plugin.hpp>
#include <eosio/chain/contract_types.hpp>

#include <eosio/version/version.hpp>

#pragma push_macro("N")
#undef N

// #include <boost/asio.hpp>
// #include <boost/format.hpp>
// #include <boost/dll/runtime_symbol_info.hpp>
// #include <boost/filesystem.hpp>
// #include <boost/process.hpp>
// #include <boost/process/spawn.hpp>
// #include <boost/range/algorithm/find_if.hpp>
// #include <boost/range/algorithm/sort.hpp>
// #include <boost/range/adaptor/transformed.hpp>
// #include <boost/algorithm/string/predicate.hpp>
// #include <boost/algorithm/string/split.hpp>
// #include <boost/range/algorithm/copy.hpp>
// #include <boost/algorithm/string/classification.hpp>
// 
// #pragma pop_macro("N")
// 
// #include <Inline/BasicTypes.h>
// #include <IR/Module.h>
// #include <IR/Validate.h>
// #include <WASM/WASM.h>
// #include <Runtime/Runtime.h>
// 
// #include <fc/io/fstream.hpp>
// ------ JUST FOR TESTING, TO BE REMOVED ------ 

int main(int argc, const char* argv[])
{
    std::vector<std::string> args(argv, argv + argc);

    // setup application name and version
    g_app.setName("OTClient");
    g_app.setCompactName("otclient");
    g_app.setVersion(VERSION);

    // initialize application framework and otclient
    g_app.init(args);
    g_client.init(args);

    // find script init.lua and run it
    if(!g_resources.discoverWorkDir("init.lua"))
        g_logger.fatal("Unable to find work directory, the application cannot be initialized.");

    if(!g_lua.safeRunScript("init.lua"))
        g_logger.fatal("Unable to run script init.lua!");

    // the run application main loop
    g_app.run();

    // unload modules
    g_app.deinit();

    // terminate everything and free memory
    g_client.terminate();
    g_app.terminate();
    return 0;
}
