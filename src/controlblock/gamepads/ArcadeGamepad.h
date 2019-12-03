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

#ifndef ARCADEGAMEPAD_H
#define ARCADEGAMEPAD_H

#include "InputDevice.h"
#include "uinput/IUInputDevice.h"
#include "hal/IDigitalIO.h"
#include "uinput/IUInputFactory.h"

/**
 * This class implements a gamepad for arcade controls.
 * It polls a four-way joystick and various buttons.
 */
class ArcadeGamepad: public InputDevice
{
public:
    /**
     * Constructor
     * @param uiFactory - Reference with IUInputFactory interface
     * @param digitalInRef - Reference with IigitalIn interface
     */
    ArcadeGamepad(IUInputFactory& uiFactory, IDigitalIO& digitalIORef);

    /**
     * Destructor
     */
    ~ArcadeGamepad() = default;

    /**
     * See \ref InputDevice::initialize()
     */
    void initialize(InputDevice::Channel_e channel) override;

    /**
     * See \ref InputDevice::update()
     */
    void update() override;

private:
    InputDevice::Channel_e channel;
    IUInputDevice* gamepad;
    IDigitalIO& digitalIO;
};

#endif
