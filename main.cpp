#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/fs.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <boost/asio.hpp>
#include "server.hpp"
#include "threadpool.hpp"
#include "log.h"
#include <syslog.h>

int main(int argc, char* argv[])
{
  try
  {
    int opt = 0;
    std::string addr;
    std::string port;
    std::string dir;
    while ((opt = getopt(argc, argv, "hpd")) != -1) {
      switch (opt) {
      case 'h':
        addr = argv[optind];
        break;
      case 'p':
        port = argv[optind];
        break;
      case 'd':
        dir = argv[optind];
        break;
      default: /* '?' */
        printf("failed to parse parameter %c", (char) opt);
        exit(EXIT_FAILURE);
      }
    }

    if (daemon(0, 0) == -1) {
      perror("daemon failed");
      return -1;
    }
    
    fprintf(Log::GetLog(), "address %s port %s directory %s\n", addr.c_str(),
                            port.c_str(), dir.c_str() );

    fprintf(Log::GetLog(), "thread count: %d\n",
           boost::thread::hardware_concurrency() );
    thread_pool pool(1);
    // Initialise the server.
    http::server::server s(pool.get_io_service(), addr, port, dir);

    // Run the server until stopped.
    pause();
  }
  catch (std::exception& e)
  {
    fprintf(Log::GetLog(), "exception: %s",  e.what());
  }

  return 0;
}
