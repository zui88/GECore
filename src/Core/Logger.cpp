#include "GECore/Core/Logger.h"

#define INIT_LOGGER(ENTT,PATTERN)\
spdlog::set_pattern(PATTERN);\
s_##ENTT##Logger = spdlog::stdout_color_st(#ENTT)

const char* GECore::Logger::c_pattern{ "%^[%T] %n: %v%$" };
GECore::Logger_h GECore::Logger::s_ClientLogger;
GECore::Logger_h GECore::Logger::s_CoreLogger;

// ToDo: dynamic switching message priority
// for filtering messages
GECore::Logger_h& GECore::Logger::GetClientLogger() {
    if (!s_ClientLogger) {
        INIT_LOGGER(Client,c_pattern);
        // Nachrichten mit geringerer Stufe werden NICHT angezeigt
        spdlog::set_level(spdlog::level::trace);
    }
    return s_ClientLogger;
}

GECore::Logger_h& GECore::Logger::GetCoreLogger() {
    if (!s_CoreLogger) {
        INIT_LOGGER(Core,c_pattern);
        spdlog::set_level(spdlog::level::trace);
    }
    return s_CoreLogger;
}
