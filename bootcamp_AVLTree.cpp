#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// AVL TREE

// 1. maksud rotate? Rotate untuk apa?
// 2. Balance Factor
// 3. di fungsi rotation -- kenapa rotate right, lalu return yang left dan sebaliknya?
// 4. Kenapa kita harus rotate untuk insert node di AVL Tree?
// 5. Function Delete Node
// 6. int main()
// 7. apakah kalau untuk menghapus data di AVL Tree, harus pakai random number? Atau AVL Tree adalah tree yang bisa memungkinkan untuk itu, sedangkan BST dan linked list tidak bisa?

struct node
{
    int value, height;
    node *left, *right;
};

int max_value(int num1, int num2)
{
    return (num1 > num2) ? num1 : num2;
}

int get_height(node *root)
{
    return (root) ? root -> height : 0;
}

int get_BalanceFactor(node *root)
{
    return (root) ? get_height(root -> left) - get_height(root -> right) : 0;
}

// (?)
int compute_new_height(node *root)
{
    return max_value(get_height(root -> left), get_height(root -> right)) + 1;
}

// (?)
node *rotation_type(node *x, const char *type)
{
    node *y, *z;

    if (strcmp(type, "left") == 0)
    {
        y = x -> right;
        z = y -> left;
        y -> left = x;
        x -> right = z;
    }

    else
    {
        y = x -> left;
        z = y -> right;
        y -> right = x;
        x -> left = z;
    }

    x -> height = compute_new_height(x);
    y -> height = compute_new_height(y);
    return y;
}

node *create_node(int value)
{
    node *new_node = (node*)malloc(sizeof(node));
    new_node -> value = value;
    new_node -> height = 1;
    new_node -> left = new_node -> right = NULL;
    return new_node;
}

// (?)
node *rotation(node *root)
{
    root -> height = compute_new_height(root);
    int balance_factor_of_root = get_BalanceFactor(root);
    int balance_left_factor = get_BalanceFactor(root -> left);
    int balance_right_factor = get_BalanceFactor(root -> right);

    if (balance_factor_of_root > 1 && balance_left_factor >= 0)
    {
        return rotation_type(root, "right");
    }

    else if (balance_factor_of_root > 1 && balance_left_factor < 0)
    {
        root -> left = rotation_type(root -> left, "left");
        return rotation_type(root, "right");
    }

    else if (balance_factor_of_root < -1 && balance_right_factor <= 0)
    {
        return rotation_type(root, "left");
    }

    else if (balance_factor_of_root < -1 && balance_right_factor > 0)
    {
        root -> right = rotation_type(root -> right, "right");
        return rotation_type(root, "left");
    }

    return root;
}

node *insert_node(node *root, int value)
{
    if (!root)
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

    return rotation(root);
}

node *predecessor(node *root)
{
    node *current = root;

    while(current && current -> right)
    {
        current = current -> right;
    }

    return current;
}

node *delete_node(node *root, int value)
{
    if (!root)
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
        if (!root -> left || !root -> right)
        {
            node *temp = (root -> left) ? root -> left : root -> right;

            if (!temp)
            {
                temp = root;
                root = NULL;
            }

            else // (?)
            {
                *root = *temp;
                free(temp);
            }
        }

        else
        {
            node *temp = predecessor(root -> left); // kenapa bukan root -> right?
            root -> value = temp -> value;
            root -> left = delete_node(root -> left, temp -> value);
        }
    }

    return (root) ? rotation(root) : root;
}

node *in_order(node *root)
{
    if (!root)
    {
        in_order(root -> left);
        printf("Height: %d\n", root -> height);
        printf("Value: %d\n", root -> value);
        in_order(root -> right);
    }
}

void avl_tree(node *root)
{
    puts("Current Tree: ");
    in_order(root);
    puts("");
}

int main()
{
    node *base_root = NULL;
    int insert_data[] = {10, 15, 24, 13, 25};

    for (int i = 0; i < 5; i++)
    {
        base_root = insert_node(base_root, insert_data[i]);
        printf("Added %d to the AVL Tree\n", insert_data[i]);
        avl_tree(base_root);
    }

    // (?)
    time_t t;
    srand((unsigned) time(&t));

    for (int i = 0; i < 5; i++)
    {
        bool removed = false;

        while (!removed)
        {
            int random_number = rand() % 31; // untuk apa?

            for (int j = 0; j < 5; j++)
            {
                if (insert_data[j] = random_number)
                {
                    printf("Removed %d from the AVL Tree\n", random_number);
                    base_root = delete_node(base_root, random_number);
                    avl_tree(base_root);
                    insert_data[j] = -1; // untuk apa?
                    removed = true;
                    break;
                }
            }
        }
    }


    return 0;
}


