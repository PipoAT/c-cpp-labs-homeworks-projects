/* 
 * Code for basic C skills diagnostic.
 * Developed by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 * 
 * @author Andrew Pipo
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "harness.h"
#include "queue.h"

queue_t *q_new()
{
    queue_t *q  = (queue_t *)malloc(sizeof(queue_t));
    if(!q)
     return q;
    else
    { 
    
    q->head = NULL;
    q->tail = NULL;
    q->qsize = 0;
    return q;
    } 
}


void q_free(queue_t *q)
{
    
    list_ele_t *temp;
    if(!q)
      return;
    if(q != NULL)
    {    
    while(q->head!=NULL)
    {
        temp = q->head;
        q->head = q->head->next;
        free(temp->value);
        free(temp);
    }    
    free(q);
}
}

bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *new_h;
    char *new_s;
    /* What should you do if the q is NULL? */ // return false
    if(!q)
      return false;
    else
    {  
     new_h = (list_ele_t *)malloc(sizeof(list_ele_t));
     if(!new_h)
     {     
       return false;
      } 
     else
     {   
      new_s = malloc(strlen(s) + 1); 
      if(!new_s)
       {
       	free(new_h); 
	      return false; 
	     
       }
      else
      {
       strcpy(new_s,s);
    
       new_h->value = new_s;
      if(q->head != NULL)
      {
        new_h->next = q->head;
        q->head = new_h;
        q->qsize++;
        return true;
        
      }
      else{
      new_h->next = NULL;
      q->head = new_h;
      q->tail = new_h;
      q->qsize++;
      return true;
      }
      }
}
}
}

bool q_insert_tail(queue_t *q, char *s)
{
	list_ele_t *new_t;
    char *new_s;
    /* What should you do if the q is NULL? */ // return false
    if(q == NULL)
      return false;
    else
    {  
     new_t = (list_ele_t *)malloc(sizeof(list_ele_t));
     if(!new_t)
       return false;
     else
     {   
      new_s = malloc(strlen(s)+1); 
      if(!new_s)
       {
	       free(new_t);
         return false;
       }
      else
      {
       strcpy(new_s,s);
       new_t->value=new_s;
    
      if(q->tail != NULL)
      {
        
        q->tail->next = new_t;
        new_t->next = NULL;
        q->tail = new_t;
        q->qsize++;
        return true;
      }
      else{
      new_t->next = NULL;
      q->tail = new_t;
      q->head = new_t;
      q->qsize++;
      return true;
      }
      }
}
}
}


bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *temp;  
    if(q == NULL)
      return false;
    else
    if(q->qsize == 0)
      return false;  
    else
    {  
      if(q->head != NULL && sp !=NULL )
      {
        size_t n;
        n = bufsize-1;
        q->qsize--;
        temp = q->head;
        if(bufsize<strlen(temp->value))
        {
         q->head = q->head->next;
         strncpy(sp,temp->value,n);
         sp[n] = '\0';
         free(temp->value);
         free(temp);
         return true;
         }
        else
        {
         q->head = q->head->next;
         strcpy(sp,temp->value);
         free(temp->value);
         free(temp);
         return true;
         
        }
      }
      
      else
      {
        return false;
        
      }
       
      }
}


int q_size(queue_t *q)
{
  
   if(!q)
      return 0;
   else
     return (q->qsize);   
}


void q_reverse(queue_t *q)
{

  list_ele_t *prev;
  list_ele_t *current;
  list_ele_t *next;

  
  if(!q)
  {
   return;
   }
  else
  if(q->qsize <= 1)
    return;
  else
  {
  prev = q->head;
  current = prev->next;
  prev->next = NULL;
  q->tail = prev;   
  while(current!=NULL)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current =next;
  }
  
  q->head = prev;
  q->tail->next = NULL;
  }
}