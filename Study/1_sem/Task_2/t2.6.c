#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 10


enum
{
    ERROR_CODE_FOR_INPUT = 1,
    ERROR_CODE_FOR_FLOAT_INPUT = 2
};

typedef unsigned int Data;
typedef struct Node Node;

struct Node 
{
    Data data;
    Node *left;
    Node *right;
    Node *parent;
};

int 
is_empty(Data *root)
{
    return root==NULL;
}

Node *min(Node *root)
{
    Node *l = root;
    while (l -> left != NULL)
        l = l -> left;
    return l;
}

// Максимальный элемент дерева
Node *max(Node *root)
{
    Node *r = root;
    while (r -> right != NULL)
        r = r -> right;
    return r;
}


void
create(Node **root, unsigned int key)
{
    Node *tmp = calloc(1,sizeof(Node));
    tmp->data = key;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = NULL;
    *root = tmp;
}

void 
add_key(Node **root, unsigned int key)
{    
    Node *tmp = calloc(1,sizeof(Node));
 
    tmp->data = key;
    tmp->left = NULL;
    tmp->right = NULL;

    Node *move_root = *root;
    Node *save_root = NULL;

    while (move_root != NULL)
    {
        save_root = move_root;

        if(move_root->data > key)
            move_root = move_root -> left;
        else
            move_root = move_root -> right;
    }

    tmp->parent = save_root;
    
    if (save_root -> data > key)
        save_root -> left = tmp;
    else
        save_root -> right = tmp;

}

void 
print_tree(Node *root)
{
    if (root == NULL)
        return;
    printf("%d ",root->data);
    print_tree(root->left);
    print_tree(root->right);
}

Node *
search_next(Node* tree)
{
    Node *p = tree, *l = NULL;

    if (p->left != NULL)
        return min(p->left);
    l = p->parent;
    while ((l != NULL) && (p == l->left))
    {
        p = l;
        l = l->parent;
    }
    return l;
}


Node *
search(Node *tree, int key)
{
    if ((tree == NULL) || (tree->data)==key)
        return tree;
    
    if (key < tree->data)
        return search(tree->left,key);
    else
        return search(tree->right,key);
    
}

void 
delete_tree(Node **tree)
{
    if (*tree != NULL)
    {
        delete_tree(&((*tree)->left));
        delete_tree(&((*tree)->right));
        free(*tree);
        *tree = NULL;
    }
}

int 
delete_key(Node *root, int key)
{
    Node *l = search(root,key);
    
    Node *m;
    int res;
    if (l == NULL)
    {
        return -1;
    }
    if ((l->left)==NULL && (l->right)==NULL)
    {
        m = l->parent;
        if (l == m->right)
            m->right = NULL;
        else
            m->left = NULL;
        res = l->data;
        free(l);
        return res;

    }
    if ((l->left)!=NULL && (l->right)==NULL)
    {
        m = l->parent;
        if (l == m->right)
            m->right = l->left;
        else
            m->left = l->left;

        res = l->data;
        free(l);
        return res;
    }
    if ((l->left)==NULL && (l->right)!=NULL)
    {
        m = l->parent;
        if (l == m->right)
            m->right = l->right;
        else
            m->left = l->right;
        
        res = l->data;
        free(l);
        return res;
    }
    if ((l->left)!=NULL && (l->right)!=NULL)
    {
        m = search_next(l);
        // printf("pops %d\n",m->data);
        res = l->data;
        l->data = m->data;
        
        if (m->right == NULL)
            (m->parent)->left = NULL;
        else
            (m->parent)->left = m->right;
        free(m);
        
    }
    return res;
    
}

int
error(char *s)
{
    if (!(*s == '+' || *s == '-' || *s == '?'))
            return ERROR_CODE_FOR_INPUT;
        
    for (int i = 1; i < strlen(s); i++)
    {
        if (s[i]<'0' || s[i]>'9')
            return ERROR_CODE_FOR_INPUT;
    }
    return 0;
}

int
main(void)
{
    Node *tree = NULL;
    Node *ptr;

    char *s;
    int key,e,f = 0,d = 1;
    double keyf;

    while (scanf("%s",s) != EOF && !(e = error(s)))
    {
        // printf("%s\n",s);
        // printf("%s\n",s);
        key = atoi(s+1);
        
        if (*s == '+')
        {
            if (f==0)
            {
                create(&tree,key);
                f = 1;
            }
            else
                add_key(&tree,key);
        }
        else if (*s == '-')
            delete_key(tree,key);
        else
        {
            putchar('\n');
            if (search(tree,key)==NULL)
                printf("%d no\n",key);
            else
                printf("%d yes\n",key);
        }
        // printf("%d\n",key);


        // print_tree(tree);
        // putchar('\n');
    }

    // printf("e: %d\n",e);
    
    if (e == 1)
    {
        fprintf(stderr, "There is an error in input: %d\n", ERROR_CODE_FOR_INPUT);
        delete_tree(&tree);
        return ERROR_CODE_FOR_INPUT;
    }

    // if (d==0)
    // {
    //     fprintf(stderr, "There is an error in input (float): %d\n", ERROR_CODE_FOR_FLOAT_INPUT);
    //     return ERROR_CODE_FOR_FLOAT_INPUT;
    // }
    
    
    print_tree(tree);
    putchar('\n');
    

    // create(&tree,50);
    // add_key(&tree,10);
    // add_key(&tree,5);
    // add_key(&tree,60);
    // add_key(&tree,55);

    // print_tree(tree);
    // putchar('\n');

    // printf("%d\n",delete_key(tree,100));
    // print_tree(tree);
    // putchar('\n');

    delete_tree(&tree);
}