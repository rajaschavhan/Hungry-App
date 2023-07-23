#include "user.h"
#include<stdio.h>
#include<stdlib.h>
//#include "mergesort.c"
#include "menu.h"
#include "restaurant.c"
#include "date.h"


void initialize_user(User *new_user){
    new_user->user_id = 0;
    new_user->name[0] = '\0';
    new_user->address[0] = '\0';
    new_user->u_phone_no = 0;
    
    new_user->pn = NULL;

}

uNode* updateUser(uNode *current,char name[],char address[],int id,long long Phone_no){
	int flag=0;
	while(flag==0 && current->user.user_id!=0 && current){
		if(strcmp(current->user.name,name)==0){
			flag=1;
		}
		else{
			current=current->next;
		}
	}
	if(flag==0){
		strcpy(current->user.name,name);
		strcpy(current->user.address,address);
		current->user.user_id=id;
		current->user.u_phone_no=Phone_no;
	}
	return current;
}


uNode* create_user_list(int n){

    uNode *user_list,*last;
    user_list=(uNode*)malloc(sizeof(uNode));
    initialize_user(&(user_list->user));
    user_list->next=NULL;
    last=user_list;

    for(int i=1;i<n;i++){
        uNode *temp=(uNode*)malloc(sizeof(uNode));
        initialize_user(&temp->user);
        last->next=temp;
        last=temp;
        temp->next=NULL;
    }
    return user_list;
}

void Find_favfood(uNode *ulist,int id){
	uNode *current=ulist;
	int flag=0;
	uNode *ptr;
	while(current && flag==0){
		if(current->user.user_id==id){
			ptr=current;
			flag=1;
		}
		else{
			current=current->next;
		}
	}

	poNode *preOrd;
	preOrd=ptr->user.pn;
	item *favlist =NULL,*last=NULL;
	while(preOrd){
		if(favlist==NULL){
			item *temp=(item*)malloc(sizeof(item));
			temp->count=1;
			strcpy(temp->fname,preOrd->p_order.item_name);
			temp->next=NULL;
			favlist=temp;
			last=temp;
		}
		else{
			int flag=0;
			item *l=favlist;
			while(l&&flag==0){
				if(strcmp(l->fname,preOrd->p_order.item_name)==0){
					flag=1;
					l->count++;
				}
				else{
					l=l->next;
				}
			}
			if(l==NULL){
				item *temp=(item*)malloc(sizeof(item));
				temp->count=1;
				strcpy(temp->fname,preOrd->p_order.item_name);
				temp->next=NULL;
				last->next=temp;
				last=temp;
			}
		}
		preOrd=preOrd->next;
	}
	favlist=mergeSort(favlist);
	favlist = reverseList(favlist);
	last=favlist;
	for(int i=0;i<3&&last;i++){
		printf("The %d favourite food item of user is %s \n",i+1,last->fname);
		last=last->next;
	}
}
