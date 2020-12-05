#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/queue.h>
 
 
 
 
typedef struct Animal {
    LIST_ENTRY(Animal) p;
 
    //相当于
    // struct {								
        // struct Animal *le_next;	
        // struct Animal **le_prev; 
    // }p;
 
    char name[25];
    int age;
}Animal;
 
typedef LIST_HEAD(AnimalList, Animal) AnimalList;
// 相当于如下
// typedef struct AnimalList {		
	// struct Animal *lh_first;	
// } AnimalList;
 
Animal* newAnimal(const char* name, int age)
{
    Animal* a = (Animal*)malloc(sizeof(Animal));
    memset(a, 0, sizeof(Animal));
 
    a->age = age;
    strncpy(a->name, name, sizeof(a->name));
    return a;
}
 
void freeAnimals(Animal* a)
{
    printf("free name = %s age = %d\n", a->name, a->age);
    free(a);
}
 
void showAnimals(AnimalList* list)
{
    Animal* iter=NULL;
    LIST_FOREACH(iter, list, p) {
        printf("name = %s age = %d\n", iter->name, iter->age);
    }    
}
 
int main()
{
    AnimalList  animals;
    LIST_INIT(&animals);
    
    //相当于
    //&animals->lh_first = NULL;
 
    // list 好像只提供了头部插入的接口  不能在尾部插入
    // 也没有计算列表长度的函数
    Animal* a = newAnimal("tiger", 3);
    LIST_INSERT_HEAD(&animals, a, p);
 
    /*
    千万不要这样， 毕竟是宏展开， newAnimal("tiger", 3) 会被调用多次
    LIST_INSERT_HEAD(&animals, newAnimal("tiger", 3), p);
    */
    
    a = newAnimal("dog", 1);
    LIST_INSERT_HEAD(&animals, a, p);
 
    a = newAnimal("cat", 4);
    LIST_INSERT_HEAD(&animals, a, p);
 
    showAnimals(&animals);
 
    // 计算链表长度
    int listn = 0;
    Animal* iter=NULL;
    LIST_FOREACH(iter, &animals, p) {
        ++listn;
    }
    printf("list len = %d\n", listn);
 
    printf("删除 一个动物 %s\n", a->name);
    LIST_REMOVE(a, p);
    freeAnimals(a);
 
    showAnimals(&animals);
 
    // 清空
    Animal* next=NULL;
    for (iter = animals.lh_first; iter; ) {
        next = iter->p.le_next; 
        freeAnimals(iter);
        iter = next;
    }
    animals.lh_first = NULL;
 
    showAnimals(&animals);
 
    printf("\n");
    a = newAnimal("frog", 1);
    LIST_INSERT_HEAD(&animals, a, p);
    showAnimals(&animals);
    
    return 0;
}