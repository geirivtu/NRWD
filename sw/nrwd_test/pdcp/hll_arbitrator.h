/**
 * @file    hll_arbitrator.h
 * @brief
 * @details
 * @author  Andreas Nordal @n NTNU in Trondheim (NORWAY)
 * @date    spring 2012
 */

#if CONFIG_BUS_MODE == BUS_ARBITRATOR

void post_office(struct socket *so);
void hll_arbdev_init(void);

struct nodeinfo{
	struct request_bind personality;
};

#ifdef CONFIG_USE_MALLOC
#	include "trie.h"
extern struct trienode nodeinfo_byId;
typedef struct trie_iterator nodeinfo_iterator;
#else
extern struct nodeinfo nodeinfo_byId[254];
typedef struct{u8 index;} nodeinfo_iterator;
#endif

#ifdef CONFIG_USE_MALLOC

inline struct nodeinfo *
nodeinfo_lookup(u8 index){
	return trie_lookup(&nodeinfo_byId, index);
}

inline struct nodeinfo *
nodeinfo_iterate(nodeinfo_iterator *it){
	return trie_iterate(it);
}

inline struct nodeinfo *
nodeinfo_iterator_begin(nodeinfo_iterator *it, index_t index){
	return trie_iterator_begin(it, &nodeinfo_byId, index);
}

#else

inline struct nodeinfo *
nodeinfo_lookup(u8 index){
	struct nodeinfo *node = &nodeinfo_byId[index-1];
	return (
		node->personality.vendor_id == ~0 &&
		node->personality.product_id == ~0 &&
		node->personality.serial_number == ~0
	) ? NULL : node;
}

inline struct nodeinfo *
nodeinfo_iterate(nodeinfo_iterator *it){
	while(it->index--){
		struct nodeinfo *ret = nodeinfo_lookup(it->index);
		if(ret) return ret;
	}
	return NULL;
}

inline struct nodeinfo *
nodeinfo_iterator_begin(nodeinfo_iterator *it, u8 index){
	it->index = index+1;
	return nodeinfo_iterate(it);
}

inline void
nodeinfo_setUnused(struct nodeinfo *node){
	node->personality.vendor_id = ~0;
	node->personality.product_id = ~0;
	node->personality.serial_number = ~0;
}

#endif


#endif