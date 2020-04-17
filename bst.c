/*
  Save file as bst.c
  To compile program: type @ terminal
   $ gcc bst.c -o bst
  To execute the program: type @ terminal
   $ ./bst
*/
/*
  If any warnings are issued then simply ignore, they are not related to logic of code.
*/
//Functionality:
//to create a bst
//to search a node
//to insert  node
//to delete a node(2 Methods)
//to traverse tree(inorder,preoder,postorder)-using non recursive approach


//to create a bst
//to search a node
//to insert  node
//to delete a node(2 Methods)
//to traverse tree(inorder,preoder,postorder)-using non recursive approach
#include<stdio.h>
#define MAX_STACK_SIZE 200
typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}node;

typedef struct par_child_data{
    node *par;//victim's parent
    node *ptr;//victim
    int type;//type of Victim
    /**
    type var specifies the type of victim:
        0->victim has 0 child
        1->victim has 1 child
        2->victim has 2 child
    **/
}info;
//stack auxiliaries
int top=-1;
node* stack[200];
push(node *el){
    if(top==MAX_STACK_SIZE){
        printf("\nError Stack Overflow");
    
    }
    else{
        stack[++top]=el;
    }
}
node* pop(){
    if(top==-1){
        printf("\nError Stack Underflow");
    }
    else{
        printf(" %d",stack[top]->data);
        node *nd=stack[top];
        top--;
        return nd;
    }
}
node* pop_postOrder(){
    if(top==-1){
        printf("\nError Stack Underflow");
    }
    else{
        node *nd=stack[top];
        top--;
        return nd;
    }
}
peek_postOrder(){
    if(top==-1){
        return -1;
    }
    else
        return stack[top]->data;
}
is_empty(int top){
    if(top==-1){
        return 1;//return true if stack is empty
    }
    return 0;//return false when stack is non empty
}

node *start=NULL;
node* create_tree(){
    int val;
    start=malloc(sizeof(node));
    start->left=NULL;
    start->right=NULL;
    printf("\nEnter Root Node value = ");
    scanf("%d",&val);
    start->data=val;
    return start;
}
print_tree(node *start){
    //preorder traversal
    if(start!=NULL){
        printf("%d ",start->data);
        print_tree(start->left);
        print_tree(start->right);
    }
    
}   
insert_element(node *start){
    int val;
    printf("\nEnter val = ");
    scanf("%d",&val);
    node *newNode=malloc(sizeof(node));
    newNode->data=val;
    newNode->left=NULL;
    newNode->right=NULL;
    node *ptr=start;
    node *par_ptr=ptr;
    //to search for val
    while(ptr!=NULL){
        if(val<ptr->data){
            par_ptr=ptr;
            ptr=ptr->left;
        }
        else if(val>ptr->data){
            par_ptr=ptr;
            ptr=ptr->right;
        }
        else if(val==ptr->data){
            printf("\nElement Already Exists");
            tree_Functions(start);
        }
    }
    if(val<par_ptr->data)
        par_ptr->left=newNode;
    else
        par_ptr->right=newNode;
    printf("\n");
    print_tree(start);
}
node* inorderSucc(node* start) 
{ 
    node* ptr = start; 
    while (ptr->left != NULL) 
        ptr = ptr->left; 
    return ptr; 
} 

node* find_inorder_succ(node *p){
    //this is the min element in the right subtree of the node with value = val
    node *ptr=p->right;
    while(ptr->left!=NULL){
        ptr=ptr->left;
    }
    return ptr;//this node is the inorder succ of p
}
dnc(node *start,info *pc){
    //to identify whether leftchild/rightchid of its parent
    if(pc->par==NULL){
        //means root node
        start=NULL;
    }
    else{
        //100% sure leaf
        if(pc->ptr->data<pc->par->data)
            pc->par->left==NULL;
        else{
            pc->par->right=NULL;
        }
        free(pc->ptr);
    }
    tree_Functions();
}
d1c(node *start,info *pc){
    if(pc->par==NULL){
        //means root node
        start=NULL;
    }
    else if(pc->ptr->data<pc->par->data){
        pc->par->left=pc->ptr->left!=NULL?pc->ptr->left:pc->ptr->right;
    }
    else{
        pc->par->right=pc->ptr->right!=NULL?pc->ptr->right:pc->ptr->left;
    }
    tree_Functions();
}
d2c(node *start,info *pc){
    if(pc->par==NULL){
        //means root node
        start=NULL;
    }
    else {
        while(1){
            node *is=find_inorder_succ(pc->ptr);
            pc->ptr->data=is->data;
            del(pc->ptr->right,is->data);
        }
    }
}
node_type(node *start,info *parChld){
    switch(parChld->type){
        case 0:
            dnc(start,parChld);
            break;
        case 1:
            d1c(start,parChld);
            break;
        case 2:
            d2c(start,parChld);
            break;
    }
}
info* find_node(node *start,int val){
    info *par_child_data=malloc(sizeof(info));
    node *ptr=start;
    node *par=ptr;
    while(ptr!=NULL){
        if(val<ptr->data){
            par=ptr;
            ptr=ptr->left;
        }
        else if(val>ptr->data){
            par=ptr;
            ptr=ptr->right;
        }
        else if(val==ptr->data){
            par_child_data->par=par;
            par_child_data->ptr=ptr;
            if(ptr->left!=NULL && ptr->right!=NULL){
                par_child_data->type=2;//victim has 2 child
            }
            else if(ptr->left==NULL){
                par_child_data->type=1;//victim has 1 child
            }
            else if(ptr->right==NULL){
                par_child_data->type=1;//victim has 1 child
            }
            else{
                par_child_data->type=0;//victim has 0 child
            }
            return par_child_data;
        }
    }
    printf("\nNode does not exists");
    tree_Functions(start);
}
del(node *start,int val){
    if(start==NULL){
        printf("\nTree Empty");
    }
    else{
        node_type(start,find_node(start,val));
    }
}


node* delete_element(node *start,int to_delete){ 
    if (start == NULL) return start;
    if (to_delete < start->data) 
        start->left = delete_element(start->left, to_delete);
    else if (to_delete > start->data) 
        start->right = delete_element(start->right, to_delete); 
    else{ 
        if (start->left == NULL) { 
            node *temp = start->right; 
            free(start); 
            return temp; 
        } 
        else if (start->right == NULL) { 
            struct node *temp = start->left; 
            free(start); 
            return temp; 
        } 
        node* temp = (node*)inorderSucc(start->right); 
        start->data = temp->data; 
        start->right = delete_element(start->right,temp->data); 
    } 
    return start; 
} 


search_element(node *start){
    int val;
    printf("\nEnter val to search = ");
    scanf("%d",&val);
    node *ptr=start;
    while(ptr!=NULL){
        if(val<ptr->data){
            ptr=ptr->left;
        }
        else if(val>ptr->data){
            ptr=ptr->right;
        }
        else if(val==ptr->data){
            printf("\nElement Exists");
            tree_Functions(start);
        }
    }
    printf("\nElement Does Not Exists");
}
pre(node *start){
    /*
        To do preorder traversal of the tree in non recrusive fashion
        -push the root
        -to_here:   pop it
        -           push right then left child node of poped element
        -           loop to_here
        //Conditional looping: loop till stack is empty
    */
    node *nd;
    printf("\nPreorder traversal of tree is:\n");
    push(start);
    while(!is_empty(top)){
        nd=pop();
        if(nd->right!=NULL){
            push(nd->right);
        }
        if(nd->left!=NULL){
            push(nd->left);
        }
    }
}
in(node *start){
    /*
    1) Create an empty stack S.
    2) Initialize current node as root
    3) Push the current node to S and set current = current->left until current is NULL
    4) If current is NULL and stack is not empty then 
        a) Pop the top item from stack.
        b) Print the popped item, set current = popped_item->right 
        c) Go to step 3.
    5) If current is NULL and stack is empty then we are done.
    */
    node *nd;
    nd=start;
    printf("\Inorder traversal of tree is:\n");
    while(!is_empty(top) || nd!=NULL){
        while(nd!=NULL){
            push(nd); 
            nd=nd->left;  
        }
        nd=pop();
        nd=nd->right;
    }
}
post(node *start){
    /*
    1.1 Create an empty stack
    2.1 Do following while root is not NULL
        a) Push root's right child and then root to stack.
        b) Set root as root's left child.
    2.2 Pop an item from stack and set it as root.
        a) If the popped item has a right child and the right child 
       is at top of stack, then remove the right child from stack,
       push the root back and set root as root's right child.
        b) Else print root's data and set root as NULL.
    2.3 Repeat steps 2.1 and 2.2 while stack is not empty.
    */
    node *nd;
    nd=start;
    printf("\nPostorder traversal of tree is:\n");
    do{
        while(nd!=NULL){
            if(nd->right!=NULL)
                push(nd->right);//right child
            push(nd);//root
            nd=nd->left;
        }
        nd=pop_postOrder();
        if(nd->right!=NULL && nd->right->data==peek_postOrder()){
            pop_postOrder();   //pop the right child
            push(nd);//push back the earlier popped node
            nd=nd->right;
        }
        else{
            printf(" %d",nd->data);
            nd=NULL;
        }
    }while(!is_empty(top));
}
traversal(node *start){
    int ch;
    while(1){
        printf("\n1.PreOrder Traversal\n2.InOrder traversal\n3.PostOrder Travesal\n4.Exit\n\nEnter Choice: ");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                pre(start);
                break;
            case 2:
                in(start);
                break;
            case 3:
                post(start);
                break;
            default:
                tree_Functions();
                
        }
    }
}
tree_Functions(){
    int ch;
    int val;
    while(1){
        printf("\nFunctions available:\n1.Insert\n2.Search\n3.Delete\n4.del\n5.Traversal\n6.Exit\n");
        printf("\nEnter Choice: ");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                if(start==NULL){
                    start=create_tree();
                }
                insert_element(start);
                break;
            case 2:
                search_element(start);
                break;
            case 3:
                printf("\nEnter val to delete = ");
                scanf("%d",&val);
                delete_element(start,val);
                print_tree(start);
                break;
            case 4:
                printf("\nEnter val to delete = ");
                scanf("%d",&val);
                del(start,val);
                break;
            case 5:
                traversal(start);
                break;
            default: 
                exit(0);  
        }  
    }

}

main(){
    start=create_tree();
    tree_Functions(); 
}
