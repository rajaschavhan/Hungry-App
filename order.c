#include "order.h"
#include "agent.h"
#include "agent.c"
#include "menu.h"
#include "restaurant.h"
#include "date.h"
#include "prevorder.h"
#include "prevorder.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{FALSE,TRUE} Boolean;

order_list list;


void initialize_order_list(order_list *ord){
    ord->front=NULL;
    ord->rear=NULL;
}



Boolean isOrderlist_empty(order_list *ord){

    Boolean retval;
    if(ord->front==NULL && ord->rear==NULL){
        retval=TRUE;
    }
    else{
        retval=FALSE;
    }
    return retval;
}

void Insert(order_list *ord,oNode *new_ord){

    if(isOrderlist_empty(ord)){
        ord->front=ord->rear=new_ord;
    }
    else{
        ord->rear->next=new_ord;
        ord->rear=new_ord;
    }
}


void initialize_order(Order *ord)
{
    ord->cus_name[0] = '\0';
    ord->add[0] = '\0';
    ord->Phone_no =0;
    ord->Eating_joint[0] = '\0';
    ord->item[0] ='\0';
    ord->d.day=0;
    ord->d.month=0;
    ord->d.year=0;
    ord->ord_ag_ptr=NULL;
    ord->ord_u_ptr = NULL;
}

void print_order_details(oNode *cur_ord){

    printf("ordered by: %s\n",cur_ord->ord.cus_name);
    printf("will be delivered at: %s\n",cur_ord->ord.add);
    printf("Item ordered is : %s\n",cur_ord->ord.item);
}


void cancel_order(order_list *ord,char name[],char item[]){
    oNode *ord_cancel;
    oNode *head=ord->front;
    int flag=0;
    while(head && flag==0){

        if(strcmp(head->ord.cus_name,name)==0&&strcmp(head->ord.item,item)==0){
            ord_cancel=head;
            flag=1;
        }
        else{
            head=head->next;
        }
    }

    if(flag==0){
        printf("order not found");
        return;
    }

    // p is pointing to the node to be deleted.
    head=ord->front;
    oNode *del,*prev=NULL;

    if(ord_cancel==ord->front){
        del=ord->front;
        ord->front=ord->front->next;

        if(ord->front==NULL){
            ord->rear=NULL;
        }
        // freeing agent
        head->ord.ord_ag_ptr->agent.free = YES;
        head->ord.ord_ag_ptr = NULL;

        free(del);
    }
    else{
        while(head){
            if(head==ord_cancel){
                del=head;
                prev->next=head->next;
                if(prev->next==NULL){
                    ord->rear=prev;
                }
                // freeing agent
                head->ord.ord_ag_ptr->agent.free = YES;
                head->ord.ord_ag_ptr = NULL;

                free(del);
            }
            else{
                prev=head;
                head=head->next;
            }
        }
    }
    
}

void Order_placing(char name[],char address[],long long no,char eat[],char item[],aNode *ap,uNode *u){

    aNode *aptr = ap;
    oNode *temp;
    
    Date dm;
    printf("enter the date-Day,month,year");
    scanf("%d %d %d",&dm.day,&dm.month,&dm.year);
    
    temp=(oNode*)malloc(sizeof(oNode));
    strcpy(temp->ord.cus_name,name);
    strcpy(temp->ord.add,address);
    temp->ord.Phone_no=no;
    strcpy(temp->ord.Eating_joint,eat);
    strcpy(temp->ord.item,item);
    temp->next=NULL;
    temp->ord.ord_u_ptr=u;
    temp->ord.d=dm;
    
    Insert(&list,temp);

    int flag=0;
    while(aptr&&flag==0){
        if(aptr->agent.free == YES){
            flag=1;
            
            print_order_details(temp);
            print_agent_details(aptr);

            aptr->agent.free = NO;
            temp->ord.ord_ag_ptr = aptr;
        }
        else{
            aptr=aptr->next;
        }
    }
    if(flag==0){
        printf("No agent is free please wait for sometime\n");
    }
    
}

void delivery(rNode *res){

	oNode *head,*del;
	aNode *ag;
	poNode *pre;
	uNode *user_Node;
	
	

	if(isOrderlist_empty(&list)){
		printf("ALL order delivered\n");
	}
	else{
        // increment no of orders from that restaurant
        res->res.no_of_orders++;

		head=list.front;
		del=head;
		user_Node=head->ord.ord_u_ptr;
		
		pre=(poNode*)malloc(sizeof(poNode));

		strcpy(pre->p_order.item_name,head->ord.item);
		strcpy(pre->p_order.r_name,head->ord.Eating_joint);
		pre->p_order.order_date=head->ord.d;
        
		user_Node->user.pn=update_preOrder(user_Node,pre);
		
		list.front=list.front->next;
		if(list.front==NULL){
			list.rear=NULL;
		}
		ag=head->ord.ord_ag_ptr;
		ag->agent.free=YES;
		printf("order delivered to %s by agent %s\n",head->ord.cus_name,ag->agent.name);



		//ag=NULL;
		rNode *res_head=res;
		int flag=0,prime;
		int cost;
		while(res_head && flag==0){
			if(strcmp((res_head->res.res_name),head->ord.Eating_joint)==0){
				prime=0;
                res_head->res.no_of_orders++;

				for(int i=0;i<NUM_MENU&&prime==0;i++){

					if(strcmp(res_head->res.menu[i].fname,head->ord.item)==0){
						prime=1;
						flag=1;
						cost=res_head->res.menu[i].price;
                        res_head->res.menu[i].num_orders++;
					}
				}
			}
			res_head=res_head->next;
		}
		ag->agent.curr_acc_comm+=(0.1)*cost;

		free(head);	
	}
}

void print_live_orders(){
    oNode *ord_head = list.front;

    while(ord_head){
        printf("ordered: %s",ord_head->ord.item);
        printf("ordered from: %s",ord_head->ord.Eating_joint);
        printf("ordered by: %s",ord_head->ord.cus_name);
        printf("ordered on: %d/%d/%d",ord_head->ord.d.day,ord_head->ord.d.month,ord_head->ord.d.year);

        ord_head=ord_head->next;
    }

}
