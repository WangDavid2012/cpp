#include <stdio.h>  
#include <stdlib.h>  
#include "queue.h"  

struct QUEUE_ITEM {
	int value;
	TAILQ_ENTRY(QUEUE_ITEM) entries;
};
TAILQ_HEAD(, QUEUE_ITEM) queue_head;


int linux_queue_test() {
	struct QUEUE_ITEM *item;
	struct QUEUE_ITEM *tmp_item;

	TAILQ_INIT(&queue_head);
	int i = 0;
	for (i = 5; i < 10; i += 2) {
		item = (struct QUEUE_ITEM *)malloc(sizeof(item));
		item->value = i;
		TAILQ_INSERT_TAIL(&queue_head, item, entries);
	}

	struct QUEUE_ITEM *ins_item;
	ins_item = (struct QUEUE_ITEM *)malloc(sizeof(ins_item));

	ins_item->value = 100;
	TAILQ_INSERT_BEFORE(item, ins_item, entries);


	tmp_item = TAILQ_FIRST(&queue_head);
	printf("first element is %d\n", tmp_item->value);

	tmp_item = TAILQ_NEXT(tmp_item, entries);
	printf("next element is %d\n", tmp_item->value);

	tmp_item = TAILQ_NEXT(tmp_item, entries);
	printf("next element is %d\n", tmp_item->value);

	tmp_item = TAILQ_NEXT(tmp_item, entries);
	printf("next element is %d\n", tmp_item->value);
	return 0;

}