//
// Created by Nick Visalli on 6/5/22.
//

#include "graph.h"
#include <memory.h>
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "net.h"
#include <assert.h>
#include <string.h>

static unsigned int
hash_code(void *ptr, unsigned int size) {

    unsigned int value = 0;
    unsigned int i = 0;
    char *str = (char*)ptr;
    while (i < size) {
        value += *str;
        value *= 97;
        str++;
        i++;
    }
    return value;
}

void
interface_assign_mac_address(interface_t *interface) {

    node_t * node = interface->att_node;

    if (!node) {
        return;
    }

    unsigned int hash_code_val = 0;
    hash_code_val = hash_code(node->node_name, NODE_NAME_SIZE);
    hash_code_val *= hash_code(interface->if_name, IF_NAME_SIZE);
    memset(IF_MAC(interface), 0, sizeof(IF_MAC(interface)));
    memcpy(IF_MAC(interface), (char *)&hash_code_val, sizeof(unsigned int));
}

typedef struct l3_route l3_route_t;

bool_t
node_set_loopback_address(node_t *node, char *ip_addr) {

    assert(ip_addr);

    node->node_nw_prop.is_lb_addr_config = TRUE;

    strncpy(NODE_LO_ADDR(node), ip_addr, 16);
    NODE_LO_ADDR(node)[15] = '\0';

    return TRUE;
}

bool_t
node_set_intf_ip_address(node_t *node, char *local_if, char *ip_addr, char mask) {

    interface_t *interface = get_node_if_by_name(node, local_if);
    if(!interface) assert(0);

    strncpy(IF_IP(interface), ip_addr, 16);
    IF_IP(interface)[15] = '\0';
    interface->intf_nw_props.mask = mask;
    interface->intf_nw_props.is_ipadd_config = TRUE;
    return TRUE;
}

void
dump_node_nw_props(node_t *node) {

    if(node->node_nw_prop.is_lb_addr_config) {
        printf("\t lo addr : %s/32", NODE_LO_ADDR(node));
    }
    printf("\n");
}

void
dump_intf_props(interface_t *interface) {

    dump_interface(interface);

    if(interface->intf_nw_props.is_ipadd_config) {
        printf("\t IP Addr = %s/%u", IF_IP(interface), interface->intf_nw_props.mask);
        printf("\t MAC : %u:%u:%u:%u:%u:%u\n",
               IF_MAC(interface)[0], IF_MAC(interface)[1],
               IF_MAC(interface)[2], IF_MAC(interface)[3],
               IF_MAC(interface)[4], IF_MAC(interface)[5]);
    }
}


void
dump_nw_graph(graph_t *graph) {

    node_t *node;
    glthread_t *curr;
    interface_t *interface;
    unsigned int i;

    printf("Topology Name = %s\n", graph->topology_name);

    ITERATE_GLTHREAD_BEGIN(&graph->node_list, curr) {

//        printf("Calling graph glue\n");
        node = graph_glue_to_node(curr);
//        printf("Calling node nw\n");
        dump_node_nw_props(node);
//        printf("after node nw\n");
        for(i = 0; i < MAX_INTF_PER_NODE; i++) {
//            printf("In loop %i\n", i);
            interface = node->intf[i];
//            printf("got interface\n");
            if(!interface) break;
//            printf("dump inft props\n");
            dump_intf_props(interface);
        }
    } ITERATE_GLTHREAD_END(&graph->node_list, curr);
}



