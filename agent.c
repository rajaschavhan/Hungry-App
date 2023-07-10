#include "agent.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void initialize_agent(Agent *cur_agent){

    cur_agent->agent_id = 0;
    cur_agent->name[0] = '\0';
    cur_agent->a_phone_no = 0;
    cur_agent->curr_acc_comm = 0;
    cur_agent->free = YES;
}

aNode* create_agent_list(int n){

    aNode *head,*last,*temp;
    head = (aNode*)malloc(sizeof(aNode));
    initialize_agent(&(head->agent));
    head->next = NULL;
    last=head;

    for(int i=1;i<n;i++){

        temp = (aNode*)malloc(sizeof(aNode));
        initialize_agent(&(temp->agent));
        last->next = temp;
        last=temp;
        last->next = NULL;
    }

    return head;
}

void set_agent_details(aNode *cur_agent,int id,char n[],long long l){

    cur_agent->agent.agent_id=id;
    strcpy(cur_agent->agent.name,n);
    cur_agent->agent.a_phone_no=l;
}

void print_agent_details(aNode *cur_agent){

    printf("ordered will be delivered by: %s\n",cur_agent->agent.name);
    printf("agent id: %d\n",cur_agent->agent.agent_id);
    printf("agent phone number: %lld\n",cur_agent->agent.a_phone_no);

}

void take_agent_input_and_set(aNode *a_list,int num_agent){

    aNode *head_agent;
    head_agent=a_list;
    for(int i=0;i<num_agent;i++){
        char name[SIZE],food[SIZE],add[SIZE];
        int id;
        long long phone_no;
        printf("enter id: ");
        scanf("%d",&id);
        printf("enter name: ");
        scanf("%s",name);
        printf("enter phone number: ");
        scanf("%lld",&phone_no);
        
        set_agent_details(head_agent,id,name,phone_no);
        head_agent=head_agent->next;
    }
}

void print_agent_list(aNode *a_list){

    aNode *head= a_list;
    while(head){
        printf("agent id: %d\n",head->agent.agent_id);
        printf("agent name: %s\n",head->agent.name);
        printf("phone no: %lld\n",head->agent.a_phone_no);
        if(head->agent.free == YES){
            printf("agent is free");
        }
        else{
            printf("agent is not free");
        }

        head=head->next;
    }
}

void print_area_wise_agents(aNode *a_list){

    aNode *head = a_list;
    printf("----- Area1 ------\n");
    while(head){
        if(strcmp(head->agent.area ,"Area1")==0){
            printf("%s\n",head->agent.name);
        }
    }
    head=a_list;
    printf("----- Area2 ------\n");
    while(head){
        if(strcmp(head->agent.area ,"Area2")==0){
            printf("%s\n",head->agent.name);
        }
    }
    head=a_list;
    printf("----- Area3 ------\n");
    while(head){
        if(strcmp(head->agent.area ,"Area3")==0){
            printf("%s\n",head->agent.name);
        }
    }

}