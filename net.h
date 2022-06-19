//
// Created by Nick Visalli on 6/4/22.
//

#ifndef __NET__
#define __NET__

#include "utils.h"
#include <memory.h>
//#include "graph.h"

typedef struct graph_ graph_t;
typedef struct interface_ interface_t;
typedef struct node_ node_t;

#define IP_ADDR_SIZE 16
#define MAC_SIZE 6

#pragma pack (push,1)
typedef struct ip_add_ {
//    unsigned char ip_addr[IP_ADDR_SIZE];
    char ip_addr[16];
} ip_add_t;

typedef struct mac_add_ {
    unsigned char mac[6];
} mac_add_t;
#pragma pack(pop)

typedef struct node_nw_prop_ {
    // L3 Properties
    // lb = loopback
    bool_t is_lb_addr_config;
    ip_add_t lb_addr;
} node_nw_prop_t;

static inline void
init_node_nw_prop(node_nw_prop_t *node_nw_prop) {

    node_nw_prop->is_lb_addr_config = FALSE;
    memset(node_nw_prop->lb_addr.ip_addr, 0, IP_ADDR_SIZE);
}

typedef struct inft_nw_props_ {
    // L2 Properties
    mac_add_t mac_add;

    // L3 Properties
    bool_t is_ipadd_config;
    ip_add_t ip_add;
    char mask;
} inft_nw_props_t;

static inline void
init_intf_nw_prop(inft_nw_props_t *intf_nw_props) {

    memset(intf_nw_props->mac_add.mac, 0, MAC_SIZE);
    intf_nw_props->is_ipadd_config = FALSE;

    memset(intf_nw_props->ip_add.ip_addr, 0, IP_ADDR_SIZE);
    intf_nw_props->mask = 0;
}

void
interface_assign_mac_address(interface_t *interface);

#define IF_MAC(intf_ptr)   ((intf_ptr)->intf_nw_props.mac_add.mac)
#define IF_IP(intf_ptr)    ((intf_ptr)->intf_nw_props.ip_add.ip_addr)

#define NODE_LO_ADDR(node_ptr) (node_ptr->node_nw_prop.lb_addr.ip_addr)

bool_t node_set_loopback_address(node_t *node, char *ip_addr);
bool_t node_set_intf_ip_address(node_t *node, char *local_if, char *ip_addr, char mask);
//boot_t node_unset_intf_ip_address(node_t *node, char *local_if);

void dump_nw_graph(graph_t *graph);
void dump_node_nw_props(node_t *node);
void dump_intf_props(interface_t *interface);

#endif
