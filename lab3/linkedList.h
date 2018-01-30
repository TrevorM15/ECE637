#ifndef linkedList
#define linkedList

int llInit(void);
void pushEnd(node_t * head, int val);
void pushHead(node_t ** head, int val);
int popHead(node_t ** head);
int popEnd(node_t* head);
int popInd(node_t ** head, int n);

#endif //linkedList
