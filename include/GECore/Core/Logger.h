#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace GECore {

  using Logger_h = std::shared_ptr<spdlog::logger>; 

  class Logger {
  public:
      static Logger_h& GetClientLogger();
      static Logger_h& GetCoreLogger();

  private:
      static const char* c_pattern;
      static Logger_h s_ClientLogger;
      static Logger_h s_CoreLogger;
  };

}

#ifndef RELEASE
#define GE_CORE_TRACE(...)      GECore::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_INFO(...)       GECore::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_CRITICAL(...)   GECore::Logger::GetCoreLogger()->critical(__VA_ARGS__)
#define GE_CORE_ERROR(...)      GECore::Logger::GetCoreLogger()->error(__VA_ARGS__)
#else
#define GE_CORE_TRACE(...)  
#define GE_CORE_INFO(...)   
#define GE_CORE_CRITICAL(...)   
#define GE_CORE_ERROR(...)  
#endif

#ifndef RELEASE
#define GE_TRACE(...)           GECore::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define GE_INFO(...)            GECore::Logger::GetClientLogger()->info(__VA_ARGS__)
#define GE_CRITICAL(...)        GECore::Logger::GetClientLogger()->critical(__VA_ARGS__)
#define GE_ERROR(...)           GECore::Logger::GetClientLogger()->error(__VA_ARGS__)
#else
#define GE_TRACE(...)       
#define GE_INFO(...)        
#define GE_CRITICAL(...)   
#define GE_ERROR(...)       
#endif
