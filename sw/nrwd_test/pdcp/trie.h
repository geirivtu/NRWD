/**
 * @file    trie.h
 * @brief
 * @details
 * @author  Andreas Nordal @n NTNU in Trondheim (NORWAY)
 * @date    2010, spring 2012
 */

#include <limits.h> //CHAR_BIT

#include "types.h"
#include "config.h"

//index_t and NODEBITS is tweakable
typedef u8 index_t;
#define NODEBITS CONFIG_TRIE_BITS_PER_NODE

//These are untweakable
#define INDEXBITS (CHAR_BIT*sizeof(index_t))
#define OUTDEGREE (1<<NODEBITS)
#define NODBITSMASK (OUTDEGREE-1)

struct trienode{
	struct trienode *child[OUTDEGREE];
};

/*
 * Not storing the leaf pointer, we do not support efficient dereferencing.
 * The leaf pointer should instead be returned by functions manipulating this.
 */
struct trie_iterator{
	struct trienode *comefrom[INDEXBITS/NODEBITS - 1]; //nodes above leaf
	index_t index;
};

typedef void (*callback_f)(void*, index_t);

void trie_init(struct trienode *);
void trie_destroy(struct trienode *, callback_f);
void* trie_lookup(struct trienode *, index_t);
void* trie_iterator_begin(struct trie_iterator*, struct trienode*, index_t);
void* trie_iterate(struct trie_iterator *);
void** trie_push(struct trienode *, index_t);
void* trie_pop(struct trienode *, index_t);
