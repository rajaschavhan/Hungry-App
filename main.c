#include <stdio.h>
#include <stdlib.h>

#include "restaurant.h"
//#include "restaurant.c"
#include "agent.h"
//#include "agent.c"
#include "user.h"
#include "user.c"
#include "order.h"
//#include "order.c"
#include "prevorder.h"
#include "menu.h"


void FindFavoriteRestaurants(rNode *rlist){
    rNode *r = rlist,*first = rlist, *sec=rlist,*third = rlist;
    int max_orders = -1;

    while(r){
        if(r->res.no_of_orders > max_orders){
            max_orders = r->res.no_of_orders;
            first = r;
        }
        r=r->next;
    }

    r=rlist;
    int sec_max = -1;

    while(r){
        if(r!= first && r->res.no_of_orders >= sec_max){
            sec_max = r->res.no_of_orders;
            sec = r;
        }
        r=r->next;
    }

    r=rlist;
    int third_max = -1;

    while(r){
        if(r!= first && r!= sec && r->res.no_of_orders >= third_max){
            third_max = r->res.no_of_orders;
            third = r;
        }
        r=r->next;
    }

    printf("top 3 restaurants are : ");
    printf("%s \n",first->res.res_name);
    printf("%s \n",sec->res.res_name);
    printf("%s \n",third->res.res_name);

}



int main(){

    

    uNode *u_list = create_user_list(5);
    uNode *p = u_list;

    aNode *a_list = create_agent_list(5);
    aNode *a = a_list;

    rNode *res_list = create_res_list(5);
    rNode *r = res_list;



    FILE *fptr1 = fopen("agentData.txt","r");
    Agent agents[5];

    if(fptr1){
        fread(&agents,sizeof(Agent),5,fptr1);
    }


    FILE *fptr2 = fopen("resData.txt","r");
    Restaurant restaurants[5];

    if(fptr2){
        fread(&restaurants,sizeof(Restaurant),5,fptr2);
    }


    for(int i=0;i<5;i++){
        r->res = restaurants[i];
        r = r->next;
    }   

    r = res_list;       

    for(int i=0;i<5;i++){
        a->agent = agents[i];
        a=a->next;
    }
    a = a_list;
                           


    uNode *multi_order;

    for(int i=0;i<5;i++){
        char cname[SIZE],fname[SIZE],addr[SIZE],rname[SIZE];
        int id;
        long long pno;

        printf("enter your name: ");
        scanf("%s",cname);
        printf("enter address: ");
        scanf("%s",addr);
        printf("enter your id: ");
        scanf("%d",&id);
        printf("enter you phone no: ");
        scanf("%lld",&pno);
        printf("what you want to order: ");
        scanf("%s",fname);
        printf("from where: ");
        scanf("%s",rname);

        multi_order=updateUser(p,cname,addr,id,pno);
        Order_placing(cname,addr,pno,rname,fname,a,multi_order);


    }
    FindFavoriteFoodsAcrossRestaurants();

    delivery(res_list);
    delivery(res_list);
    delivery(res_list);
    delivery(res_list);
    delivery(res_list);

    FindFavoriteRestaurants(res_list);
    Find_favfood(u_list,1);
    
    return 0;
}
