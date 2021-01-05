#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 2
#define MIN 1 

struct node
{
    int key[MAX + 1];
    int ctr;
    node *child[MAX + 1];
}*root;

// bagaimana cara menginsert data baru, search dan delete dari salah satu dari lima method di bawah ini:

// Alasan yang paling logis: codingan sangat panjang (200 baris)
node *create_node(int key, node *child)
{
    node *new_node = (node*)malloc(sizeof(node));
    new_node -> key[1] = key;
    new_node -> ctr = 1;
    new_node -> child[0] = root;
    new_node -> child[1] = child;
    return new_node;
}

void insert_key(int key, int target_position, node *leaf, node *child)
{
    int current_position = leaf -> ctr;

    while(current_position > target_position)
    {
        leaf -> key[current_position + 1] = leaf -> key[current_position];
        leaf -> child[current_position + 1] = leaf -> child[current_position];
        current_position--;
    }

    leaf -> key[current_position + 1];
    leaf -> child[current_position + 1] = child;
    leaf -> ctr++;
}

void split(int key, int *pot_key, int position, node *node_temp, node *child, node **new_node)
{
    int median = (position > MIN) ? MIN + 1 : MIN;
    int j = median + 1;
    *new_node = (node*)malloc(sizeof(node));

    while (j <= MAX)
    {
        (*new_node) -> key[j - median] = node_temp -> key[j];
        (*new_node) -> child[j - median] = node_temp -> child[j];
        j++;
    }

    node_temp -> ctr = median;
    (*new_node) -> ctr = MAX - median;
    (position <= MIN) ? insert_key(key, position, node_temp, child) : insert_key(key, position - median, *new_node, child);
    *pot_key = node_temp -> key[node_temp -> ctr];
    (*new_node) -> child[0] = node_temp -> child[node_temp -> ctr];
    node_temp -> ctr--;
}

int set_key_of_node(int key, int *pot_key, node *node_temp, node **child)
{
    int position;

    if(!node_temp)
    {
        *pot_key = key;
        *child = NULL;
        return 1;
    }

    if (key < node_temp -> key[1])
    {
        position = 0; // leaf paling kiri
    }

    else
    {
        position = node_temp -> ctr;

        while (key < node_temp -> key[position] && position > 1)
        {
            position--;
        }

        if (key == node_temp -> key[position])
        {
            return 0; // prompt sudah ada
        }
    }
    
    if (set_key_of_node(key, pot_key, node_temp -> child[position], child))
    {
        if (node_temp -> ctr < MAX)
        {
            insert_key(*pot_key, position, node_temp, *child);
        }

        else
        {
            split(*pot_key, pot_key, position, node_temp, *child, child);
            return 1;
        } 
    }

    return 0;
}

void insertion(int key)
{
    int key_copy;
    node *child;

    if (set_key_of_node(key, &key_copy, root, &child) == 1)
    {
        root = create_node(key_copy, child); // root berubah menjadi root baru
    }
}

void inorder(node *root)
{
    int i;
    
    if(root)
    {
        for (i = 0; i < root -> ctr; i++)
        {
            inorder(root -> child[i]);
            printf("%d ", root -> key[i + 1]);
        }

        inorder(root -> child[i]);
    }
}

int main()
{
    insertion(15);
    insertion(10);
    insertion(13);
    insertion(25);
    insertion(24);
    inorder(root);

    return 0;
}



