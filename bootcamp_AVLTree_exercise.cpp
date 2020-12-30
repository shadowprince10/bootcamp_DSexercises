#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Konsep Height dan Balance Factor 
// Left Rotation -- cek BFLeft, BFRight, dan BFRoot
// bikin kondisi yang ngecek
struct node
{
    int value;
    int height;
    node *left, *right;
};

int max(int num1, int num2)
{
    return (num1 > num2) ? num1 : num2;
}

int get_height(node *root)
{
    return (root) ? root -> height : 0; // kalau root ada isi, return tinggi by default 1. Kalau root NULL, berarti sudah pasti tingginya 0
}

// saat berotasi, kita meng-update height dan balance factor
int get_balance_factor(node *root) // kodingan tidak dapat memprediksi condong ke kiri atau kanan, makanya tidak memakai absolute kalau di kodingan meski di simulasi menggunakan absolute
{
    return (root) ? get_height(root -> left) - get_height(root -> right) : 0; 
}

int compute_new_height(node *root)
{
    return max(get_height(root -> left), get_height(root -> right)) + 1;
}

node *create_node(int value)
{
    node *temp = (node*)malloc(sizeof(node));
    temp -> value = value;
    temp -> height = 1;
    temp -> left = temp -> right = NULL;
    return temp;
}

// rotate sifatnya rekursi
node *left_rotate(node *x)
{
    node *y = x -> right;
    node *z = y -> left;
    y -> left = x;
    x -> right = z;
    x -> height = compute_new_height(x);
    y -> height = compute_new_height(y);
    
    return y;
}

node *right_rotate(node *x)
{
    node *y = x -> left;
    node *z = y -> right;
    y -> right = x;
    x -> left = z;
    x -> height = compute_new_height(x);
    y -> height = compute_new_height(y);

    return y;
}

// rotate function adalah fungsi validasi untuk mengecek apakah balance factornya merusak property avl atau tidak
node* rotation(node *root)
{
    // lANGKAH-LANGKAH:
    // tinggi root baru pakai compute
    // dapatkan balanced factor root, left, dan right (karena harus tahu tipe left left, right right, right left, atau left right)
    // menentukan balance / unbalanced
    // meentukan tipe rotasi
    // membuat left_rotate() dan right_rotate()

    root -> height = compute_new_height(root);
    int balanced_factor_of_root = get_balance_factor(root);
    int right_balanced_factor = get_balance_factor(root -> right);
    int left_balanced_factor = get_balance_factor(root -> left);

    if (balanced_factor_of_root > 1 && left_balanced_factor >= 0) // kalau balanced_factor_of_root > 1 dominan kiri, selisih lebih dari 1 (anak kiri > anak kanan)
    {
        return right_rotate(root);
    }

    else if (balanced_factor_of_root > 1 && left_balanced_factor < 0) 
    {
        root -> left = left_rotate(root -> left);
        return right_rotate(root);
    }

    else if (balanced_factor_of_root < -1 && right_balanced_factor > 0)
    {
        root -> right = right_rotate(root -> right);
        return left_rotate(root);
    }   
}

node *insert_node(node *root, int value)
{
    if(!root)
    {
        return create_node(value);
    }

    else if (value < root -> value)
    {
        root -> left = insert_node(root -> left, value);
    }

    else if (value > root -> value)
    {
        root -> right = insert_node(root -> right, value);
    }

    // penjelasan dasarnya, kenapa kita melakukan rotation di insert, karena node yang mau diinsert, pasti menjadi leaf. dan karena menjadi leaf. tinggi dari tree kita berubah dari tinggi tree berubah ini, kan bisa aja melanggar peraturan avl


    return (root) ? rotation(root) : root;
    // rotate function adalah fungsi validasi untuk mengecek apakah balance factornya merusak property avl atau tidak
}

// Kalau successor, ke kanan, ke kiri hingga habis
node *predecessor(node *root) // ke kiri sekali, ke kanan hingga habis
{
    node *current = root -> left; // kalau pakai left, root saja, tidak perlu root -> left

    while (current && current -> right)
    {
        current = current -> right;
    }

    return current;
}

node *delete_node(node *root, int value)
{
    if(!root)
    {
        return root;
    }

    else if (value < root -> value)
    {
        root -> left = delete_node(root -> left, value);
    }

    else if (value > root -> value)
    {
        root -> right = delete_node(root -> right, value);
    }

    else
    {
        if(!root -> left || root -> right) // TRUE || TRUE == TRUE and FALSE || TRUE == TRUE and TRUE || FALSE == TRUE (if kondisional ini berlaku untuk kasus 0 anak, 1 anak (memiliki anak kiri atau kanan))
        {
            // jika dia punya anak kiri, penggantinya adalah anak kiri
            // jika dia tidak punya anak kiri, penggantinya adalah anak kanan
            node *new_root = root -> left ? root -> left : root -> right;
            free(root);
            root = NULL;
            return new_root;
        }
    }
    
    node *temp = predecessor(root);
    root -> value = temp -> value;
    root -> left = delete_node(root -> left, temp -> value);
}

int main()
{
    node *base_root = NULL;

    return 0;
}