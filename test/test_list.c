#include  <stdio.h>
#include  <stdlib.h>
#include "list.h"

struct my_list{
    struct list_head list;
    char value[10]; 
};

int main(int argc, char **argv){
    
    struct my_list *tmp;
    struct list_head *pos, *q;
    unsigned int i;
    
    struct my_list mylist;
    INIT_LIST_HEAD(&mylist.list); /*��ʼ������ͷ*/
    
    /* ��mylist����Ԫ�� */
    for(i=3; i!=0; --i){
        tmp= (struct my_list *)malloc(sizeof(struct my_list));
        
        /* ����INIT_LIST_HEAD(&tmp->list); */
        printf("enter value:");
        scanf("%s", tmp->value);
        
        
        list_add(&(tmp->list), &(mylist.list));
        /* Ҳ������list_add_tail() �ڱ�β����Ԫ��*/
    }
    printf("\n");
    
    printf("traversing the list using list_for_each()\n");
    list_for_each(pos, &mylist.list){
        
    /* ������ pos->next ָ��next �ڵ�, pos->prevָ��ǰһ���ڵ�.����Ľڵ���
        struct my_list����. ���ǣ�������Ҫ���ʽڵ㱾��,�����ǽڵ��е�list�ֶΣ�
        ��list_entry()����Ϊ��Ŀ�ġ�*/     
        
    tmp= list_entry(pos, struct my_list, list);
    printf("%s ", tmp->value);
    }
    printf("\n");

    printf("deleting the list using list_for_each_safe()\n");
    list_for_each_safe(pos, q,&mylist.list){
        tmp= list_entry(pos, struct my_list, list);
        printf("%s ", tmp->value);
        list_del(pos);
        free(tmp);
    }
}