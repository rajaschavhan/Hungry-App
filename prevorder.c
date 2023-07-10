#include "prevorder.h"
#include "user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void update_date(Date date,int d,int m, int y){
    date.day = d;
    date.month = m;
    date.year = y;
}

poNode* update_preOrder(uNode *ptr,poNode *preOrd){
	
	poNode *start=ptr->user.pn;
	if(ptr){
		if(start){
			while(start->next!=NULL){
				start=start->next;
			}
			start->next=preOrd;
			start=preOrd;
			start->next=NULL;
		}
		else{
			ptr->user.pn=preOrd;
		}
	}
	return ptr->user.pn;
}