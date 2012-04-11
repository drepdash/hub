#include <stdlib.h>
#include <stdio.h>
#ifndef WIN32
#	include <getopt.h>
#else
#	include "wingetopt.h"
#endif /* WIN32 */
#include <string.h>
#include <signal.h>
#include <event2/event.h>
#include "hub.h"

#define DEFAULT_PORT 8989

static struct event_base *evbase;
static struct hub hub;

static void
handle_quit(int sig)
{
  event_base_loopexit(evbase, NULL);
}

static void
usage(char const *progname)
{
  fprintf(stderr, "Usage: %s [-a addr/mask] [-i interface] [-p port] peer0 peer1 peerN\n",
      progname);
  exit(EXIT_FAILURE);
}

int
main(int argc, char * const argv[])
{
  int opt;
#ifndef WIN32
  struct sigaction sa;
#endif /*WIN32*/
  memset(&hub, 0, sizeof(hub));

  hub.port = DEFAULT_PORT;
  hub.ipaddr = NULL;
  hub.tun.fd = -1;
  hub.tun.interfce = NULL;
  hub.tun.type = TNT_TAP;

  while ((opt = getopt(argc, argv, "a:i:p:")) != -1)
  {
    switch (opt)
    {
      case 'a':
        hub.ipaddr = strdup(optarg);
        break;
      case 'i':
        hub.tun.interfce = strdup(optarg);
        break;
      case 'p':
        hub.port = (short) evutil_strtoll(optarg, NULL, 10);
        break;
      default:
        usage(argv[0]);
    }
  }

  for (; optind < argc; ++optind)
    hub_add_peer(&hub, argv[optind]);
  
  evbase = event_base_new();

#ifndef WIN32
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = handle_quit;
  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGTERM, &sa, NULL);
#else
  signal(SIGINT, handle_quit);
  signal(SIGTERM, handle_quit);
#endif /* WIN32 */
  hub_init(&hub, evbase);
  hub_start(&hub);
  event_base_dispatch(evbase);
  hub_uninit(&hub);
  event_base_free(evbase);
  return EXIT_SUCCESS;
}
