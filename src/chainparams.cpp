// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
		(      0, uint256("0x96e9ee342a81adb2558e877cf0732ee413762da43018f555702f7d2ee69c99e9"))
		(   7356, uint256("0x5bda3a3bd226cd609b093593e9a2653e4c9e2bc0e84c20abfdfa8f0b98be0228"))
		(  25000, uint256("0x45b539abb29ed00c18bafe77181fad68b47eddd686231c217a22f0b8592e8437"))
		(  50000, uint256("0x71df8ab07e3d40aa34d7647bcfca7f9114d0436fdd38f4b51daf22dca8d91092"))
		( 100000, uint256("0x9c05134706aad749f11e72473ef3370f448a91716fb0dcb58296651d3926ed11"))
		( 200000, uint256("0x5f54457ae4ac46e4ea4d094a24e01e4f5b89b4bbe9ecb7b02b6b5aca070d04b8"))
		( 300000, uint256("0xc3dece54d1a658c65be9bd7f999074a36e6efbbcdfe95636bc4fc03fd313a6e7"))
		( 400000, uint256("0xc3184d95fa248c46ceaeaf2235ad8d7ff75d7f898b6f72e44f35833699d4d9cb"))
		( 500000, uint256("0xdd0873b91edfb00c55bba58f509f33406fa9a0f69e53bb11705251074413e518"))
		( 600000, uint256("0xd8da0db4a90a334b4aae4d33274a74bcf2f9533e0304304408f747c22c13f4c9"))
		( 658200, uint256("0xc457a10672e7740f57d9554db2483f0e8260a7f2900912d83bc89bedb23235d0"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1440951840, // * UNIX timestamp of last checkpoint block
        //160,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        //1100.0     // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 546, uint256("0xa0fea99a6897f531600c8ae53367b126824fd6a847b2b2b73817a95b8e27e602"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1365458829,
        547,
        576
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x3b;
        pchMessageStart[1] = 0xa1;
        pchMessageStart[2] = 0xc9;
        pchMessageStart[3] = 0x2a;
        vAlertPubKey = ParseHex("211184710fa679ad5023590c80f3a49c8f13f8d45b8b857fbcac8bc4a8b4d3eb3b10f4b4604fa18dce611aaf0f170216ae1a5175bb4bcf2bb279cb5170bc6b03b6");
        nDefaultPort = 42511;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 840000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 5 * 60; // 5 minutes
        nTargetSpacing = 1 * 30; // 30 seconds
        nMaxTipAge = 24 * 60 * 60;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         * 
         * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
         *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
         *   vMerkleTree: 4a5e1e
         */
		 
		/**
		 *  "hash": "96e9ee342a81adb2558e877cf0732ee413762da43018f555702f7d2ee69c99e9",
		 *  "confirmations": 657174,
		 *  "size": 246,
		 *  "height": 0,
		 *  "version": 1,
		 *  "merkleroot": "234383ad6f89ee376010cda0a0ffcdae20f772eb60d917eb1048a6686bcf789e",
		 *  "tx": [ "234383ad6f89ee376010cda0a0ffcdae20f772eb60d917eb1048a6686bcf789e" ],
		 *  "time": 1440696188,
		 *  "nonce": 1021531,
		 *  "bits": "1e0ffff0",
		 *  "difficulty": 0.00024414,
		 *  "nextblockhash": "044b69a8bcf7ae0933a2863c47a9f878806ccc5654931de7731423a16840a2d4"
		 */
		 
        const char* pszTimestamp = "27-08-2015 With love for miners";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("42183710aa589ada023691c80f3a49a8f13f1d45bac857fbcba8bc4a8ead3eb4b10a4d4a04fa08dce60aaaf0fa7021afe1b51850a2acf21ba79c45070aa7b13a8") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1440696188;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 1021531;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x96e9ee342a81adb2558e877cf0732ee413762da43018f555702f7d2ee69c99e9"));
        assert(genesis.hashMerkleRoot == uint256("0x234383ad6f89ee376010cda0a0ffcdae20f772eb60d917eb1048a6686bcf789e"));

        vSeeds.push_back(CDNSSeedData("minecoin.info", "dnsseed.minecoin.info"));
        vSeeds.push_back(CDNSSeedData("midnightminer.net", "xmineseed.midnightminer.net"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(50);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
        base58Prefixes[SECRET_KEY] =     list_of(178);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0x3b)(0xa1);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xc9)(0x2a);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        // Minecoin: Mainnet v2 enforced as of block 710k
        nEnforceV2AfterHeight = 710000;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x16;
        pchMessageStart[1] = 0x23;
        pchMessageStart[2] = 0xa1;
        pchMessageStart[3] = 0xbc;
        vAlertPubKey = ParseHex("311184710fa679ad5023590c80f3a49c8f13f8d45b8b857fbcac8bc4a8b4d3eb3b10f4b4604fa18dce611aaf0f170216ae1a5175bb4bcf2bb279cb5170bc6b03b6");
        nDefaultPort = 43511;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
       nTargetTimespan = 5 * 60; // 5 minutes
        nTargetSpacing = 1 * 30; // 30 seconds
        nMaxTipAge = 0x7fffffff;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1440696188;
        genesis.nNonce = 1021531;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x96e9ee342a81adb2558e877cf0732ee413762da43018f555702f7d2ee69c99e9"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("minecoin.info", "testnet-seed.minecoin.info"));
        vSeeds.push_back(CDNSSeedData("midnightminer.net", "testnet-xmineseed.midnightminer.net"));
//        vSeeds.push_back(CDNSSeedData("wemine-testnet.com", "dnsseed.wemine-testnet.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x16)(0x23);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0xa1)(0xbc);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        // Minecoin: Testnet v2 enforced as of block 400k
        nEnforceV2AfterHeight = 400000;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 5 * 60; // 5 minutes
        nTargetSpacing = 1 * 30; // 30 seconds
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nMaxTipAge = 24 * 60 * 60;
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19444;
//		printf("RegTest GenesisBlock = %s \n", hashGenesisBlock.ToString().c_str());
        assert(hashGenesisBlock == uint256("0x1c717ec1ebccb72884a1b6271f871629a7914ac7f8eac04ed862863e3c7d44cd"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        // Minecoin: v2 enforced using Bitcoin's supermajority rule
        nEnforceV2AfterHeight = -1;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;

        // Minecoin: v2 enforced using Bitcoin's supermajority rule
        nEnforceV2AfterHeight = -1;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
