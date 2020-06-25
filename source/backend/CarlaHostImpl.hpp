/*
 * Carla Plugin Host
 * Copyright (C) 2011-2020 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the doc/GPL.txt file.
 */

#ifndef CARLA_HOST_IMPL_HPP_INCLUDED
#define CARLA_HOST_IMPL_HPP_INCLUDED

#include "CarlaHost.h"
#include "CarlaUtils.h"
#include "CarlaEngine.hpp"

#ifdef BUILD_BRIDGE
# include "CarlaString.hpp"
#else
# include "CarlaLogThread.hpp"
#endif

namespace CB = CarlaBackend;
using CB::EngineOptions;

// --------------------------------------------------------------------------------------------------------------------
// Shared code, WIP

typedef struct _CarlaHostHandle {
    // required pointers
    CarlaEngine* engine;

    // flags
    bool isStandalone : 1;
    bool isPlugin     : 1;

    _CarlaHostHandle() noexcept
        : engine(nullptr),
          isStandalone(false),
          isPlugin(false) {}
} CarlaHostHandleImpl;

// --------------------------------------------------------------------------------------------------------------------
// Single, standalone engine

struct CarlaHostStandalone : CarlaHostHandleImpl {
    EngineCallbackFunc engineCallback;
    void*              engineCallbackPtr;
    FileCallbackFunc   fileCallback;
    void*              fileCallbackPtr;

#ifndef BUILD_BRIDGE
    CarlaString    clientNamePrefix;
    EngineOptions  engineOptions;
    CarlaLogThread logThread;
    bool           logThreadEnabled;
#endif

    CarlaString lastError;

    CarlaHostStandalone() noexcept
        : CarlaHostHandleImpl(),
          engineCallback(nullptr),
          engineCallbackPtr(nullptr),
          fileCallback(nullptr),
          fileCallbackPtr(nullptr),
#ifndef BUILD_BRIDGE
          clientNamePrefix(),
          engineOptions(),
          logThread(),
          logThreadEnabled(false),
#endif
          lastError()
    {
        isStandalone = true;
    }

    ~CarlaHostStandalone() noexcept
    {
        CARLA_SAFE_ASSERT(engine == nullptr);
    }

    CARLA_PREVENT_HEAP_ALLOCATION
    CARLA_DECLARE_NON_COPY_STRUCT(CarlaHostStandalone)
};

// --------------------------------------------------------------------------------------------------------------------

#endif // CARLA_HOST_IMPL_HPP_INCLUDED
