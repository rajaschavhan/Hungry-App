
#include "order.c"
#include "restaurant.h"
#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include "mergesort.c"
#include <string.h>

void initialize_res(Restaurant *res){
    res->address[0]='\0';
    res->no_of_seats=0;
    for(int i=0;i<NUM_MENU;i++){
    	res->menu[i].fname[0]='\0';
    	res->menu[i].price=0;
        res->menu[i].num_orders = 0;
    }
    res->res_category[0]='\0';
    res->food_category[0]='\0';
    res->res_name[0] = '\0';
}

rNode* create_res_list(int n){

    rNode *head,*last,*temp;
    head=(rNode*)malloc(sizeof(rNode));
    initialize_res(&(head->res));
    head->next=NULL;
    last=head;

    for(int i=1;i<n;i++){
        temp=(rNode*)malloc(sizeof(rNode));
        initialize_res(&temp->res);
        last->next=temp;
        last=temp;
        temp->next=NULL;
    }
    return head;

}

void set_res_details(rNode *r, char name[], char category[], char food_cat[],char address[]){

    strcpy(r->res.res_name,name);
    strcpy(r->res.res_category,category);
    strcpy(r->res.food_category,food_cat);
    strcpy(r->res.address,address);

}

void take_res_input_and_set(rNode *res_list,int num_res){

    rNode *head;
    head=res_list;

    for(int i=0;i<num_res;i++){
        char name[SIZE],cat[SIZE],food[SIZE],add[SIZE];
        printf("enter name\n");
        scanf("%s",name);
        printf("enter restaurant category: ");
        scanf("%s",cat);
        printf("enter food category: ");
        scanf("%s",food);
        printf("enter address: ");
        scanf("%s",add);
        set_res_details(head,name,cat,food,add);
        head=head->next;
    }
}




// --------------------- QUESTION 1  ---------------------
void search_by_res_category(rNode *res_list, char category[] ){
    rNode *head=res_list;
    int flag=0;
    while(head){

        if(strcmp(category,head->res.res_category)==0){
            printf("%s\n",head->res.res_name);
            flag=1;
        }
        head=head->next;
    }
    if(!flag){
        printf("none found :( ");
    }
}

//searching by Category

void search_by_food_category(rNode *res_list, char food[]){
    rNode *head=res_list;
    int flag=0;
    while(head){

        if(strcmp(food,head->res.food_category)==0){
            printf("%s\n",head->res.res_name);
            flag=1;
        }
        head=head->next;
    }
    if(!flag){
        printf("none found :( ");
    }
}

//searching by area

void search_by_area(rNode *res_list, char add[]){

    rNode *head=res_list;
    int flag=0;
    while(head){

        if(strcmp(add,head->res.address)==0){
            printf("%s\n",head->res.res_name);
            flag=1;
        }
        head=head->next;
    }
    if(!flag){
        printf("none found :( ");
    }
}



void FindFavoriteFoodsAcrossRestaurants(int N){

	oNode *o_start=list.front;
	item *favlist=NULL,*last=NULL;
	while(o_start){

		if(favlist==NULL){
			item *temp=(item*)malloc(sizeof(item));
			temp->count=1;
			strcpy(temp->fname,o_start->ord.item);
			temp->next=NULL;
			favlist=temp;
			last=temp;
		}
		else{
			int flag=0;
			item *l=favlist;
			while(l&&flag==0){
				if(strcmp(l->fname,o_start->ord.item)==0){
					flag=1;
					l->count++;
				}
				else{
					l=l->next;
				}
			}
			if(l==NULL){
				item *t=(item*)malloc(sizeof(item));
				t->count=1;
				strcpy(t->fname,o_start->ord.item);
				t->next=NULL;
				last->next=t;
				last=t;
			}
		}
		o_start=o_start->next;
	}
	favlist=mergeSort(favlist);
    favlist = reverseList(favlist);
	last=favlist;
	for(int i=0;i<3&&last;i++){
		printf("The %d favourite food item in restaurant is %s \n",i+1,last->fname);
		last=last->next;
	}
	
	
}
