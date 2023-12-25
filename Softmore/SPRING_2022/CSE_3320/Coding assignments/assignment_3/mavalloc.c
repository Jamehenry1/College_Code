#include "mavalloc.h"
#include "stdlib.h"
#include <stdio.h>


enum Type
{
  FREE = 0,
  USED
};

struct Node
{
  int size;
  enum Type type;
  void * arena;
  struct Node *next;
  struct Node *prev;
};

struct Node *alloc_list;
struct Node *previous_node;
enum ALGORITHM allocation_algorithm = FIRST_FIT;

void *arena;
struct Node *head;
int MAX = 99999999;
int MIN = -99999999;

int mavalloc_init( size_t size, enum ALGORITHM algorithm )
{
  arena = malloc(ALIGN4(size));

  allocation_algorithm = algorithm;

  alloc_list = (struct Node *)malloc(sizeof(struct Node));

  alloc_list -> arena = arena;
  alloc_list -> size = ALIGN4(size);
  alloc_list -> type = FREE;
  alloc_list -> next = NULL;
  alloc_list -> prev = NULL;

  previous_node = alloc_list;
  return 0;
}

void mavalloc_destroy( )
{
  free(arena); 
  struct Node *current = alloc_list;
  struct Node *next;
  while(current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }

  alloc_list = NULL;


  return;
}

void * mavalloc_alloc( size_t size )
{
  // only return NULL on failure

  struct Node * node;

  if(allocation_algorithm != NEXT_FIT)
  {
    node = alloc_list;
  }
  else if(allocation_algorithm == NEXT_FIT)
  {
    node = previous_node;
  }
  else
  {
    printf("ERROR: Unknown allocation algorithm");
  }

  int aligned_size = ALIGN4(size);

  //First fit
  if(allocation_algorithm == FIRST_FIT)
  {
    while(node)
    {
      if(node -> size >= aligned_size && node -> type == FREE)
      {
        int leftover_size = 0;

        node -> type = USED;
        leftover_size = node -> size - aligned_size;
        node -> size = aligned_size;

        if(leftover_size > 0)
        {
          //if there is a node that was in connected before 
          //we have create this node then store it 
          //[n]->[n1] goes to [n]->[n2]->[n1]; [n1] gets stored in previous next
          struct Node * previous_next = node -> next; 

          //creates [n2]
          struct Node * leftover_node = (struct Node *)malloc(sizeof(struct Node));

          leftover_node -> arena = node -> arena + size;
          leftover_node -> type = FREE;
          leftover_node -> size = leftover_size;

          //[n2]->[n1]     next = previous_next?
          leftover_node -> next = previous_next;

          //[n]->[n2]->[n1]
          node -> next = leftover_node;
        } 

        // holds the previous node [n] = [p]; [p]->[n2]->[n1]
        previous_node = node;
        return (void *)node -> arena;
      }
      //put the start of the next node at [n2]; 
      node = node -> next;
    }
  }

  //Nextfit
  if(allocation_algorithm == NEXT_FIT)
  {
   // head = node;
    if(previous_node == NULL)
    {
      previous_node = head;
    }

    node = previous_node;

    //struct Node nodeN = previous_node;
    while(node)
    {
      if(node -> size >= aligned_size && node -> type == FREE)
      {
        int leftover_size = 0;

        node -> type = USED;
        leftover_size = node -> size - aligned_size;
        node -> size = aligned_size;

        if(leftover_size > 0)
        {
          //if there is a node that was in connected before 
          //we have create this node then store it 
          //[n]->[n1] goes to [n]->[n2]->[n1]; [n1] gets stored in previous next
          struct Node * previous_next = node -> next; 

          //creates [n2]
          struct Node * leftover_node = (struct Node *)malloc(sizeof(struct Node));

          leftover_node -> arena = node -> arena + size;
          leftover_node -> type = FREE;
          leftover_node -> size = leftover_size;

          //[n2]->[n1]     next = previous_next?
          leftover_node -> next = previous_next;

          //[n]->[n2]->[n1]
          node -> next = leftover_node;
        } 

        // holds the previous node [n] = [p]; [p]->[n2]->[n1]
        previous_node = node;
        return (void *)node -> arena;
      }
      //put the start of the next node at [n2]; 
      node = node->next;


      if(node == previous_node)
      {
        break;
      }

      if(node == NULL)
        node = alloc_list;


      
    }
    /*
    node = node->next;
    if(node == previous_node)
    {
      break;
    }

    if(node == NULL)
      node = head;
    */
  }
  
  //Bestfit
  int winning_size = MAX;

  //struct Node *beforeNode = NULL;
  //struct Node *beforeWin = NULL;

  struct Node *bestStuff = alloc_list;
  struct Node *worstStuff = alloc_list;
  struct Node *winnerNode = NULL;

  if(allocation_algorithm == BEST_FIT)
  {
    while(bestStuff)
    {
      //Keep track of the node before the FREE node I am using
      //Keep track of the Node I am using
      //Winning side will be the second FREE node after you create the process node

      if(bestStuff->type == FREE && bestStuff->size >= aligned_size )
      {
        if ( (bestStuff->size - aligned_size) <= winning_size ) 
        {
          winnerNode = bestStuff;
          winning_size = bestStuff->size - aligned_size;
        } 
      }
     
      //beforeNode = bestStuff;
      bestStuff = bestStuff->next;
    }

    if( winnerNode )
    {

      //struct Node newNodeProcess = (struct Node *)malloc(sizeof(struct Node));;
      winnerNode->type = USED;
      winnerNode->size = aligned_size; 

      if( winning_size > 0 )
      {
        struct Node *newFree = (struct Node *)malloc(sizeof(struct Node));
        newFree->type = FREE;
        newFree->arena = winnerNode->arena + aligned_size;
        newFree->size = winning_size;
  
        newFree->next = winnerNode->next; 
        winnerNode->next = newFree;
      }
      return (void*)winnerNode->arena;
    }
    return NULL;

  }

  //Worstfit
  if(allocation_algorithm == WORST_FIT)
  {
    winning_size = MIN;
    while(worstStuff)
    {
      //Keep track of the node before the FREE node I am using
      //Keep track of the Node I am using
      //Winning side will be the second FREE node after you create the process node
      if(worstStuff->type == FREE && worstStuff->size >= aligned_size )
      {
        if ( (worstStuff->size - aligned_size) >= winning_size ) 
        {
          winnerNode = worstStuff;
          winning_size = worstStuff->size - aligned_size;
        } 
      }

      //beforeNode = worstStuff;
      worstStuff = worstStuff->next;
    }

    if( winnerNode )
    {

      //struct Node newNodeProcess = (struct Node *)malloc(sizeof(struct Node));;
      winnerNode->type = USED;
      winnerNode->size = aligned_size; 

      if( winning_size > 0 )
      {
        struct Node *newFree = (struct Node *)malloc(sizeof(struct Node));
        newFree->type = FREE;
        newFree->arena = winnerNode->arena + aligned_size;
        newFree->size = winning_size;
  
        newFree->next = winnerNode->next; 
        winnerNode->next = newFree;
      }
      return (void*)winnerNode->arena;
    }

    return NULL;
  }
  return NULL;
}

void mavalloc_free( void * ptr )
{
  struct Node * node = alloc_list;
  while( node )
  {
    if( node -> arena == ptr )
    {
      if( node -> type == FREE )
      {
        printf("Warning: Double free detected\n");
      }

      node -> type = FREE;

      break;
    }
    node = node -> next;
  }

  node = alloc_list;

  while( node )
  {
    if( node -> next && node -> type == FREE && node -> next -> type == FREE  )
    {
      struct Node * previous = node -> next;
      node -> size = node -> size + node -> next -> size;
      node -> next = node -> next -> next;
      free( previous );
      continue;
    }
    node = node -> next;
  }

  return;

}

int mavalloc_size( )
{
  int number_of_nodes = 0;
  struct Node *node = alloc_list;
  while( node )
  {
    number_of_nodes ++;
    node = node ->next;
  }

  return number_of_nodes;
}
