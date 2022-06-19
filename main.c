//
// Created by Nick Visalli on 5/26/22.
//

#include "net.h"
#include <unistd.h>
#include "graph.h"
#include "comm.h"
#include "CommandParser/libcli.h"

extern void nw_init_cli();
extern graph_t *build_first_topo();
graph_t *topo = NULL;

int
main(int argc, char **argv) {

    nw_init_cli();
    topo = build_first_topo();
    dump_nw_graph(topo);

    sleep(2);

    node_t *snode = get_node_by_node_name(topo, "R0_re");
    interface_t *oif = get_node_if_by_name(snode, "eth0/0");

    char msg[] = "Hello there\0";
    send_pkt_out(msg, strlen(msg), oif);

    start_shell();
    return 0;
}