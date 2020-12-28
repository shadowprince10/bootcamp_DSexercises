#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// setiap kali memanggil node, parameter root

//                15
//    10                         23
//8       12                 18      27

// Alur Rekursi
// 15 -> left = insert_node(15 -> left, 13)
// 10 -> right = insert_node(10 -> right, 13)
// 12 -> right = insert_node(12 -> right, 13)
// if(!root), create_node(13);

// 15 -> left -> right -> right = create_node(13) -- kita pakai rekursi karena ribet kalau traverse satu-satu

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
    if (!root) // jika tidak ada root atau tree kosong atau root sekarang belum ada isi
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

    return root; // karena root paling atas ~ return tree yang sudah jadi ~ itu karena root telah dilink dengan anak-anaknya dan leaf
}

// mencari nilai terkecil di subtree kanan
node *minimum_value_of_node(node *root)
{
    node *current = root; // curr adalah parent di subtree kanan

    // traverse ke kiri hingga ketemu minimum value dari node (kenapa ke kiri terus?)
    while(current && current -> left)
    {
        current = current -> left;
    }

    return current;
}

node *maximum_value_of_node(node *root)
{
    node *current = root;

    while (current && current -> right)
    {
        current = current -> right;
    }
    
    return current;
}

// di BINUS lebih sering pakai inorder karena di post order dan pre order tidak pakai pattern

// pembagian kasus delete ada 4
// Tree akan berubah sehingga ada link yang berubah, maka kita return base_root yang telah berubah, jadi bukan void
// kalau variabel root global, langsung bisa update
// karena variabel root lokal, harus return manual
node *delete_node(node *root, int value)
{
    if (!root) // kalau misalkan yang kita delete tidak ada
    {
        return root; // kenapa return root kalau memang tidak ada yang ingin di-delete?
        // if (!root) bukan berarti tidak ada root
        // krn ini rekursi, ini sedang dicek
        // apakah saat kita mencari data yang mau kita hapus
        // kita kalau sudah sampai leaf, brarti data itu kan ga ada
        // makanya return root disini return parent terakhir
    }

    else if (value < root -> value) // masuk subtree kiri
    {
        root -> left = delete_node(root -> left, value);
    }

    else if (value > root -> value) // masuk subtree kanan
    {
        root -> right = delete_node(root -> right, value);
    }

    else if (value == root -> value) // ketemu apa yang ingin dihapus
    {
        // kasus 0 anak dan 1 anak
        if (!root -> left) // jika kiri NULL, maka kita cari ke kanan
        {
            node *temp = root -> right;
            free(root); // hapus root lama 
            root = NULL;
            return temp;
        }

        else if (!root -> right) // jika kanan NULL, maka kita cari ke kiri
        {
            node *temp = root -> left;
            free(root);
            root = NULL;
            return temp;
        }

        // Kalau langsung delete node, node terhapus, tapi tetap ada pointer yang menunjuk ke dia
        // kalau gak berhasil return atau tembus kedua if kita (KASUS 2 ANAK)
        node *minimum_value_of_right_subtree = minimum_value_of_node(root -> right); // mencari nilai tree di subtree kanan
        // tinggal ke kanan sampai habis
        root -> value = minimum_value_of_right_subtree -> value; // copy value-nya terlebih dahulu sebelum dihapus supaya yang dihapus bukan nilai node terkecil di subtree kanan, tetapi penggantinya.
        // Kalau langsung hapus, nanti ribet menggabung-gabungkan link-nya
        // Kalau hapus node parent, harus pakai predecessor atau successor alias pengganti sebuah node. Ada dua pilihan -- nilai terbesar dari subtree kiri dan nilai terkecil dari subtree kanan
        // Jadi kita timpa value, lalu mengganti node
        root -> right = delete_node(root -> right, minimum_value_of_right_subtree -> value);
    }

    return root; // setelah kita hapus, return root
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

void pre_order(node *root)
{
    if (root)
    {
        printf("%d ", root -> value);
        pre_order(root -> left);
        pre_order(root -> right);
    }
}

void post_order(node *root) // kiri kanan dulu, baru print
{
    if (root)
    {
        post_order(root -> left);
        post_order(root -> right);
        printf("%d ", root -> value);
    }
}

// VISUALISASI INORDER
//                15
//    10                         23
//8       12                 18      27

// left, naik, baru right (print sorted)
void in_order(node *root) // inorder: print sorted value
{
    //in_order(15 -> left);
    //in_order(10 -> left);
    //in_order(8 -> left);
    // print(8)

    if (root)
    {
        in_order(root -> left);
        printf("%d ", root -> value);
        in_order(root -> right);  
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
    in_order(base_root);
    puts("");
    base_root = delete_node(base_root, 13);
    in_order(base_root);
    puts("");
    base_root = delete_node(base_root, 25);
    in_order(base_root);

    // kondisi buat kasus duplicate
    // if(search_node(base_root, 15))
    // {
    //    puts("Duplicate key is detected!");
    //}

    // tapi kalau angka yang sama tetap ingin dimasukkan, kita buat kondisi yang bisa memasukkan angka yang sama
    // tapi di BINUS, tidak pernah kasusnya duplicate karena angka selalu unik
    puts("");

    return 0;
}

// MVC: Model, View, Controller
// Kalau nanti ada banyak struct, program makin ke bawah.
// Supaya lebih modular, ada file khusus struct, manipulasi struct, apa yang user lihat
// Kalau di BINUS, tidak sampai 3 file terus. Dari semua tugas, satu file membutuhkan satu Data Structure
// BST dan AVL itu akan memakai rekursi
// di file main include #struct, model, view, controller
// #include <models.h>
// Kalau include cpp, akan ada dua buah int main dan akan konflik karena .cpp expect int main
// tetap include plural stdio.h di satu folder untuk menghindari bug-bug-nya
// cukup pakai satu file karena kuis BINUS tidak terlalu banyak
// bisa pakai #ifguard (kalau sudah include, jangan include lagi)


