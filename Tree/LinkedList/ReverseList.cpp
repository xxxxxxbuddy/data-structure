#include <stdlib.h>
#include <malloc.h>

typedef struct LinkedList* Node;
struct LinkedList{
    int Value;
    Node next;
};

/**
 * Reverse Linked List
 *
 * @param {LinkedList*}
 * @param {int} numbers to reverse
 * @return {LinkedList*}
 */
 LinkedList ReverseList(Node head, int k)
{
     Node NEW = head->next;
     Node OLD = NEW->next;
     Node tmp;
     int i = 1;
     while(i < k){
         tmp = OLD->next;
         OLD->next = NEW;
         NEW = OLD;
         OLD = tmp;
         i++;
     }
     head->next->next = OLD;
    return *NEW;
}


int main()
{

}