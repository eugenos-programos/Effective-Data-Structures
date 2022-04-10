#include "stdio.h"
#include "stdlib.h"

struct Tree
{
    int data;
    struct Tree* right,* left;
    char* name;
}*root;


struct Tree* create_root(int data, char* name)
{
    struct Tree* new_node;
    new_node->data = data;
    new_node->name = name;
    new_node->left = new_node->right = NULL;
    return new_node;
}

struct pair{
    int data;
    char* name;
}el;

void make_balance(struct Tree** p, int n, int k, int* a, struct pair* array_1)
{
    if(n == k)
    {
        *p = NULL;
        return;
    }
    int m = (n + k) / 2;
    *p = malloc(sizeof(**p));
    (*p)->data = a[m];
    int length = sizeof(array_1) / sizeof(el);
    for(int i = 0;i < length; ++i)
    {
        if(array_1[i].data == a[m])
        {
            (*p)->name = array_1[i].name;
            break;
        }
    }
    make_balance(&(*p)->left, n, m, a, array_1);
    make_balance(&(*p)->right, m + 1, k, a, array_1);
}

void print_tree(struct Tree* p, int level)
{
    if(p)
    {
        for(int i = 0; i < level; ++i) printf("    ");
        printf("%d %c\n", p->data, p->name);
        print_tree(p->right, level + 1);
        print_tree(p->left, level + 1);
    }
}

struct Tree* del_info(struct Tree* root, int key)
{
    struct Tree* Del, prev_del, r, prev_r;
    Del = root;
    prev_del = NULL;
    while(Del != NULL && Del->data != key)
    {
        prev_del = Del;
        if(Del->data > key) Del = Del->left;
        else Del = Del->right;
    }
    if(Del == NULL)
    {
        printf("Key doesn't found!\n");
        return root;
    }
    if(Del->right == NULL) r = Del->left;
    else
        if (Del->left == NULL) r = Del->right;
        else
        {
            prev_r = Del;
            r = Del->left;
            while (r->right != NULL)
            {
                prev_r = r;
                r = r->right;
            }
			if(prev_r == Del)  r->right = Del->right;
			else {
				r->right = Del->right;
				prev_r->right = r->left;
				r->left = Del->left;    // R->left = Prev_R
			}
    }
	if (Del == root) root = r;			// Удаляя корень, заменяем его на R
	else
	if (Del->data < prev_del->data)
			prev_del->left = r;				// На левую ветвь
		else	prev_del->right = r;
						// На правую ветвь
	delete Del;
	return root;
}

void create_list(struct Tree* root,int key, char* name) {
    if (root == NULL) { printf("Empty tree\n"); return; };
    struct Tree* prev, * t;
    bool find = true;
    t = root;
    prev = t;
    while ((t != NULL) && find) {
        prev = t;
        if (t->data == key) {
            find = false;
            printf("Key has been used! Please try again!");
        }
        else {
            if (key < t->data)t = t->left;
            else t = t->right;
        }
    }
    if (prev == NULL) return;
    if (find) {
        t = create_root(key, name);
        if (key > prev->data)prev->right = t;
        else prev->left = t;
    }
}

int main(int argc, char const *argv[])
{
    char* name = "Hello!";
    printf("%c", name[2]);
    return 0;
}
