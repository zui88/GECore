#pragma once

#if defined(ENTRY_POINT)

extern GECore::Scope<GECore::Application> GECore::CreateApplication();

int main(int argc, char **argv) {
  auto app{ GECore::CreateApplication() };
  app->startup();
  app->run();
  app->shutdown();
  return 0;
}

#endif
