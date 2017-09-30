/*
 * Carla JACK API for external applications
 * Copyright (C) 2016-2017 Filipe Coelho <falktx@falktx.com>
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

#include "libjack.hpp"

CARLA_BACKEND_USE_NAMESPACE

// --------------------------------------------------------------------------------------------------------------------

CARLA_EXPORT
int jack_client_name_size(void)
{
    return STR_MAX;
}

CARLA_EXPORT
char* jack_get_client_name(jack_client_t* client)
{
    carla_stdout("%s(%p)", __FUNCTION__, client);

    JackClientState* const jclient = (JackClientState*)client;
    CARLA_SAFE_ASSERT_RETURN(jclient != nullptr, nullptr);

    return jclient->name;
}

CARLA_EXPORT
char* jack_get_uuid_for_client_name(jack_client_t*, const char*)
{
    return nullptr;
}

CARLA_EXPORT
char* jack_get_client_name_by_uuid(jack_client_t*, const char*)
{
    return nullptr;
}

// --------------------------------------------------------------------------------------------------------------------

CARLA_EXPORT
int jack_internal_client_new(const char*, const char*, const char*)
{
    return 1;
}

CARLA_EXPORT
void jack_internal_client_close(const char*)
{
}

// --------------------------------------------------------------------------------------------------------------------

CARLA_EXPORT
int jack_activate(jack_client_t* client)
{
    carla_stdout("%s(%p)", __FUNCTION__, client);

    JackClientState* const jclient = (JackClientState*)client;
    CARLA_SAFE_ASSERT_RETURN(jclient != nullptr, 1);

    const CarlaMutexLocker cms(jclient->mutex);

    jclient->activated = true;
    jclient->deactivated = false;
    return 0;
}

CARLA_EXPORT
int jack_deactivate(jack_client_t* client)
{
    carla_stdout("%s(%p)", __FUNCTION__, client);

    JackClientState* const jclient = (JackClientState*)client;
    CARLA_SAFE_ASSERT_RETURN(jclient != nullptr, 1);

    const CarlaMutexLocker cms(jclient->mutex);

    jclient->activated = false;
    jclient->deactivated = true;
    return 0;
}

// --------------------------------------------------------------------------------------------------------------------

CARLA_EXPORT
int jack_get_client_pid(const char*)
{
    return 0;
}

// --------------------------------------------------------------------------------------------------------------------