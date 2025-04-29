#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


typedef struct BinaryTree {
    TreeNode* root;
} BinaryTree;


TreeNode* create_tree_node(int data) {
    TreeNode* new_node = (TreeNode*) malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        printf("Memory not available!\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


TreeNode* insert_node(TreeNode* root, int data) {
    if (root == NULL) {
        return create_tree_node(data);
    }

    if (data < root->data) {
        root->left = insert_node(root->left, data);
    } else if (data > root->data) {
        root->right = insert_node(root->right, data);
    }

    return root;
}


int get_node_depth(TreeNode* root, int val) {
    if (root == NULL) {
        return -1;
    }
    if (root->data == val) {
        return 0;
    }
    if (val < root->data) {
        return 1 + get_node_depth(root->left, val);
    }
    else {
        return 1 + get_node_depth(root->right, val);
    }
}


TreeNode* find_node(TreeNode* root, int val) {

    if (root == NULL) {
        return NULL;
    }

    if (root->data == val) {
        return root;
    }

    TreeNode* left_search = find_node(root->left, val);
    if (left_search != NULL) {
        return left_search;
    }

    return find_node(root->right, val);
}


int get_node_height(TreeNode* node) {
    if (node == NULL) {
        return -1;
    }
    int left_height = get_node_height(node->left);
    int right_height = get_node_height(node->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}


int get_node_level(TreeNode* root, int val) {
    return get_node_depth(root, val) + 1;
}


TreeNode* get_node_sibling(TreeNode* root, int val) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return NULL;
    }

    if (root->left != NULL && root->right != NULL) {
        if (root->left->data == val) {
            return root->right;
        }
        if (root->right->data == val) {
            return root->left;
        }
    }

    TreeNode* left_search = get_node_sibling(root->left, val);
    if (left_search != NULL) {
        return left_search;
    }

    return get_node_sibling(root->right, val);
}

int in_order_traversal(TreeNode* root) {
    if (root != NULL) {
        in_order_traversal(root->left);
        printf("%d ", root->data); // KO
        in_order_traversal(root->right);

        // printf("%d ", root->data); // KO
        // pre_order_traversal(root->left);
        // pre_order_traversal(root->right);


        // post_order_traversal(root->left);
        // post_order_traversal(root->right);
        // free(root); // KO
    }
    
    return 0;
}

int any_order_traversal(TreeNode* root) {
    if (root != NULL) {
        // Possibility of Key Operation - Pre-order
        any_order_traversal(root->left);
        // Possibility of Key Operation - In-order
        any_order_traversal(root->right);
        // Possibility of Key Operation - Post-order
    }
    
    return 0;
}

/*
TreeNode* min_value_node(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

TreeNode* delete_node(TreeNode* root, int data) {
    if (root == NULL) return root;

    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } 
    else if (data > root->data) {
        root->right = delete_node(root->right, data);
    }
    else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        TreeNode* temp = min_value_node(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    return root;
}
*/

int main() {
    BinaryTree tree;
    tree.root = NULL;

    tree.root = insert_node(tree.root, 8);
    tree.root = insert_node(tree.root, 3);
    tree.root = insert_node(tree.root, 10);
    tree.root = insert_node(tree.root, 1);
    tree.root = insert_node(tree.root, 6);
    tree.root = insert_node(tree.root, 14);
    tree.root = insert_node(tree.root, 4);
    tree.root = insert_node(tree.root, 7);
    tree.root = insert_node(tree.root, 13);

    printf("In-order traversal of the binary tree:\n");
    in_order_traversal(tree.root);
    printf("\n");

    int value = 8;
    TreeNode* node = find_node(tree.root, value);
    if (node) {
        printf("Height of %d is %d\n", value, get_node_height(node));
        TreeNode* sibling = get_node_sibling(tree.root, value);
        if (sibling) {
            printf("Sibling of %d is %d\n", value, sibling->data);
        }
        else {
            printf("No sibling found for %d\n", value);
        }
        printf("Depth of %d is %d\n", value, get_node_depth(tree.root, value));
        printf("Level of %d is %d\n", value, get_node_level(tree.root, value));
    } else {
        printf("Node %d not found in the tree.\n", value);
    }


    return 0;
}
