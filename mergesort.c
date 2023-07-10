#include <stdio.h>
#include "menu.h"

item *Divide(item *lptr)
{
    item *fast, *mid;
    mid = fast = lptr;
    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            fast = fast->next;
        }
        if (fast)
        {
            mid = mid->next;
        }
    }
    lptr = mid->next;
    mid->next = NULL;
    return lptr;
}

item *merge(item *head1, item *head2)
{
    item *last, *third;
    if (head1->count < head2->count)
    {
        third = last = head1;
        head1 = head1->next;
        third->next = NULL;
    }
    else
    {
        third = last = head2;
        head2 = head2->next;
        third->next = NULL;
    }
    while (head1 && head2)
    {
        if (head1->count < head2->count)
        {
            last->next = head1;
            last = head1;
            head1 = head1->next;
            last->next = NULL;
        }
        else
        {
            last->next = head2;
            last = head2;
            head2 = head2->next;
            last->next = NULL;
        }
    }
    if (head1)
    {
        last->next = head1;
    }
    if (head2)
    {
        last->next = head2;
    }
    return third;
}

item *mergeSort(item *head)
{
    // your code here

    item *nptr, *lptr;
    lptr = head;
    if ((lptr != NULL) && (lptr->next != NULL))
    {
        nptr = Divide(lptr);
        lptr = mergeSort(lptr);
        nptr = mergeSort(nptr);
        lptr = merge(lptr, nptr);
    }
    return lptr;
}

item* reverseList(item* start){
    item *head=start,*mid=NULL,*tail=NULL;

    while(head){
        tail = mid;
        mid = head;
        head = head->next;
        mid->next = tail;
    }
    return mid;

}