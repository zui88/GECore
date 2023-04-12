#pragma once

#if defined(ENTRY_POINT)

int main(int argc, char **argv) {
  std::unique_ptr<GECore::Application> app{GECore::CreateApplication()};
  app->startup();
  app->run();
  app->shutdown();
  return 0;
}

#endif