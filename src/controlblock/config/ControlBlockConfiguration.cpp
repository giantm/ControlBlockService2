/**
 * (c) Copyright 2017  Florian Müller (contact@petrockblock.com)
 * https://github.com/petrockblog/ControlBlock2
 *
 * Permission to use, copy, modify and distribute the program in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * This program is freeware for PERSONAL USE only. Commercial users must
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for the program or software derived from the program.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so everyone can benefit from the modifications
 * in future versions.
 */

#include <iostream>
#include <fstream>
#include <assert.h>
#include "json/json.h"

#include "ControlBlockConfiguration.h"

ControlBlockConfiguration::ControlBlockConfiguration() :
        hasLoadedConfiguration(false),
        singleConfiguration{nullptr}
{
}

ControlBlockConfiguration::~ControlBlockConfiguration()
{
    if (hasLoadedConfiguration) {
        for (auto & index : singleConfiguration) {
            if (index != nullptr) {
                delete index;
            }
        }
    }
}

void ControlBlockConfiguration::loadConfiguration()
{
    Json::Value root;   // will contains the root value after parsing.
    try {
        Json::Reader reader;

        std::ifstream configStream(CONFIGFILEPATH);
        std::string config_doc((std::istreambuf_iterator<char>(configStream)), std::istreambuf_iterator<char>());

        bool parsingSuccessful = reader.parse(config_doc, root);
        if (!parsingSuccessful) {
            // report to the user the failure and their locations in the document.
            throw std::runtime_error("ControlBlockConfiguration: Failed to parse configuration");
        }

        singleConfiguration[0] = new SingleConfiguration(root["controlblocks"][0]["enabled"].asBool(),
                (uint8_t) (root["controlblocks"][0]["address"]["SJ2"].asInt() << 2
                         | root["controlblocks"][0]["address"]["SJ1"].asInt() << 1),
                root["controlblocks"][0]["gamepadtype"].asString(), root["controlblocks"][0]["powerswitchOn"].asBool(),
                root["controlblocks"][0]["onlyOneGamepad"].asBool());
        singleConfiguration[1] = new SingleConfiguration(root["controlblocks"][1]["enabled"].asBool(),
                (uint8_t) (root["controlblocks"][1]["address"]["SJ2"].asInt() << 2
                         | root["controlblocks"][1]["address"]["SJ1"].asInt() << 1),
                root["controlblocks"][1]["gamepadtype"].asString(), root["controlblocks"][1]["powerswitchOn"].asBool(),
                root["controlblocks"][1]["onlyOneGamepad"].asBool());
    }
    catch (std::exception& exc) {
        std::cout << "ControlBlockConfiguration: Error while initializing ControlBlockConfiguration instance. Error number: " << errno
                  << std::endl;
    }
    hasLoadedConfiguration = true;
}

SingleConfiguration& ControlBlockConfiguration::getConfiguration(int controlBlockID)
{
    assert(controlBlockID < MAX_CONTROLBLOCK_ID);
    assert(hasLoadedConfiguration);

    return *singleConfiguration[controlBlockID];
}
