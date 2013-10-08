/**
 * @file    trie.c
 * @brief
 * @details
 * @author  Andreas Nordal @n NTNU in Trondheim (NORWAY)
 * @date    2010, spring 2012
 */

#include <stdlib.h>
#include "trie.h"

static uint_fast8_t childcount(struct trienode *cur, uint_fast8_t outdegree){
	uint_fast8_t count=0;
	while(outdegree--) if(cur->child[outdegree]) count++;
	return count;
}

void trie_init(struct trienode *root){
	uint_fast8_t i=OUTDEGREE;
	while(i--) root->child[i] = NULL;
}

void* trie_lookup(struct trienode *cur, index_t index){
	uint_fast8_t level = INDEXBITS;
	do{
		if(!cur) break; //Not found
		level -= NODEBITS;
		uint_fast8_t direction = (index >> level) & NODBITSMASK;
		cur = cur->child[direction];
	}while(level);
	return (void*) cur;
}

void* trie_iterator_begin(struct trie_iterator *it, struct trienode *cur, index_t index){
	uint_fast8_t level = INDEXBITS;
	do{
		level -= NODEBITS;
		it->comefrom[level/NODEBITS] = cur;
		uint_fast8_t direction = (index >> level) & NODBITSMASK;
		uint_fast8_t i = direction;
		while(cur->child[i] == NULL){
			if(i-- == 0) return NULL; //empty
		}
		if(i != direction){
			//direction changed => update index
			index &= ~((index_t)NODBITSMASK << level); //reset current bits
			index |=  (((index_t)i + 1) << level) - 1;
		}
		cur = cur->child[i];
	}while(level);
	it->index = index;
	return (void*) cur;
}

void* trie_iterate(struct trie_iterator *it){
	uint_fast8_t level = INDEXBITS - NODEBITS; //bit level above leaves
	struct trienode *cur = it->comefrom[level/NODEBITS];
	uint_fast8_t i = (it->index >> level) & NODBITSMASK;
	
	for(;;){
		while(i--){
			if(cur->child[i]){
				it->index &= ~((index_t)NODBITSMASK) << level; //reset low bits
				it->index |=  ((index_t)i          ) << level;
				if(level){
					level -= NODEBITS;
					it->comefrom[level/NODEBITS] = cur;
					cur = cur->child[i];
					i = OUTDEGREE;
				}else{
					return (void*) cur->child[i];
				}
			}
		}
		if(level == INDEXBITS-NODEBITS) break;
		cur = it->comefrom[level/NODEBITS];
		level += NODEBITS;
		i = (it->index >> level) & NODBITSMASK;
	}
	return NULL;
}

void* trie_pop(struct trienode *cur, index_t index){
	void *ret = NULL;
	struct trienode *trace[INDEXBITS/NODEBITS];
	uint_fast8_t level = INDEXBITS;
	do{
		if(!cur) break; //Not found
		level -= NODEBITS;
		uint_fast8_t direction = (index >> level) & NODBITSMASK;
		trace[level/NODEBITS] = cur;
		cur = cur->child[direction];
	}while(level);
	ret = (void*) cur;

	for(;;){
		cur = trace[level/NODEBITS];
		uint_fast8_t direction = (index >> level) & NODBITSMASK;
		cur->child[direction] = NULL;

		level += NODEBITS;
		if(level == INDEXBITS) break; //root
		if(childcount(cur, OUTDEGREE) == 0) free(cur);
		else break;
	}
	return ret;
}

void** trie_push(struct trienode *root, index_t index){
	struct trienode *cur = root;
	uint_fast8_t level = INDEXBITS;
	for(;;){
		level -= NODEBITS;
		uint_fast8_t direction = (index >> level) & NODBITSMASK;
		if(level){
			if(cur->child[direction] == NULL){
				cur->child[direction] = calloc(OUTDEGREE, sizeof(struct trienode *));
				if(cur->child[direction] == NULL){
					trie_pop(root, index);
					return NULL;
				}
			}
		}else return (void**) cur->child+direction;
		cur = cur->child[direction];
	}
}

void trie_destroy(struct trienode *cur, callback_f func){
	uint_fast8_t level = INDEXBITS - NODEBITS;
	struct trienode *comefrom[INDEXBITS/NODEBITS - 1];
	uint_fast8_t i = OUTDEGREE;
	index_t index=0;

	parentnode:
	while(i--){
		if(cur->child[i]){
			//Casting is critical!!!!!!!!!!!!!!!!!!!!!
			index &= ~((index_t)NODBITSMASK) << level; //reset low bits
			index |=  ((index_t)i          ) << level;
			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if(level){
				level -= NODEBITS;
				comefrom[level/NODEBITS] = cur;
				cur = cur->child[i];
				i = OUTDEGREE;
			}else{
				func((void*) cur->child[i], index);
			}
		}
	}
	if(level != INDEXBITS-NODEBITS){
		cur = comefrom[level/NODEBITS];
		level += NODEBITS;
		i = (index >> level) & NODBITSMASK;
		free(cur->child[i]);
		cur->child[i] = NULL;
		goto parentnode;
	}
}
