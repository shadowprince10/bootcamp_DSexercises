#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// root pindah-pindah?
struct node
{
    int value;
    node *left, *right;
};

node *create_node(int value)
{
    node *new_node = (node*)(malloc(sizeof(node)));
    new_node -> value = value;
    new_node -> left = new_node -> right = NULL;
    return new_node;
}

node *insert_node(node *root, int value)
{
    if (!root) // jika tidak ada root atau tree kosong
    {
        return create_node(value); // langsung buat node baru
    }

    else if (value < root -> value) // masuk ke subtree kiri
    {
        root -> left = insert_node(root -> left, value); // traverse ke subtree kiri
    }

    else if (value > root -> value) // masuk ke subtree kanan
    {
        root -> right = insert_node(root -> right, value); // traverse ke subtree kanan
    }

    return root; // (?)
}

node *minimum_value_of_node(node *root)
{
    node *current = root;

    // traverse ke kiri hingga ketemu minimum value dari node (kenapa ke kiri terus?)
    while(current && current -> left)
    {
        current = current -> left;
    }

    return current;
}

node *delete_node(node *root, int value)
{
    if (!root) // kalau misalkan yang kita delete tidak ada
    {
        return root; // kenapa return root kalau memang tidak ada yang ingin di-delete?
    }

    else if (value < root -> value)
    {
        root -> left = delete_node(root -> left, value);
    }

    else if (value > root -> value)
    {
        root -> right = delete_node(root -> right, value);
    }

    else if (value == root -> value) // (?)
    {
        // kasus 0 anak dan 1 anak
        if (!root -> left) // jika kiri NULL, maka kita cari ke kanan
        {
            node *temp = root -> right;
            free(root); // kenapa tidak di-NULL-kan root-nya?
            return temp;
        }

        else if (!root -> right) // jika kanan NULL, maka kita cari ke kiri
        {
            node *temp = root -> left;
            free(root);
            return temp;
        }

        // mencari nilai terkecil di subtree kanan (?) -- BUTUH VISUALISASI (???)
        node *minimum = minimum_value_of_node(root -> right);
        root -> value = minimum -> value; // copy value-nya terlebih dahulu sebelum dihapus supaya yang dihapus bukan nilai node terkecil di subtree kanan, tetapi penggantinya
        root -> right = delete_node(root -> right, minimum -> value);
    }

    return root;
}

// tidak perlu initialisasi linked list di sini. Kita hanya membutuhkan recursion. (Konsep sama seperti Linear Search)
bool search_node(node *root, int key)
{
    if (!root) // selama root tidak NULL
    {
        if (root -> value == key) // jika nilai root adalah target yang kita ingin cari
        {
            return true;
        }

        else if (key < root -> value)
        {
            return search_node(root -> left, key); // kenapa dia return? bukannya dia cari alias traverse ke kiri terus?
        }

        else if (key > root -> value)
        {
            return search_node(root -> right, key);
        }
    }

    // selain kondisi-kondisi di atas atau kalau tidak ketemu value yang dicari, maka dia return false
    return false;
}

/// maksud preorder dan postorder?
void preorder(node *root)
{
    if (root)
    {
        printf("%d ", root -> value);
        preorder(root -> left);
        preorder(root -> right);
    }
}

void postorder(node *root)
{
    if (root)
    {
        postorder(root -> left);
        postorder(root -> right);
        printf("%d ", root -> value);
    }
}

void print_all(node *root) // inorder: print sorted value
{
    if (root)
    {
        print_all(root -> left);
        printf("%d ", root -> value);
        print_all(root -> right);  
    }
}

int main()
{
    node *base_root = NULL; // declare NULL (?)
    base_root = insert_node(base_root, 25);
    base_root = insert_node(base_root, 15);
    base_root = insert_node(base_root, 10);
    base_root = insert_node(base_root, 24);
    base_root = insert_node(base_root, 13);
    print_all(base_root);
    puts("");
    base_root = delete_node(base_root, 13);
    print_all(base_root);
    puts("");
    base_root = delete_node(base_root, 25);
    print_all(base_root);
    puts("");

    return 0;
}


