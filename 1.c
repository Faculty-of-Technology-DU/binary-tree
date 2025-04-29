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

// Insertion Logic only applicable for a BST
TreeNode* insert_node(TreeNode* root, int data) {
    if (root == NULL) {
        return create_tree_node(data);
    }

    if (data < root->data) {
        root->left = insert_node(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert_node(root->right, data);
    }

    return root;
}


TreeNode* in_order_traversal(TreeNode* root) {
    if (root != NULL) {
        in_order_traversal(root->left);
        printf("%d ", root->data); // Key Operation
        in_order_traversal(root->right);
    }
    return NULL;
}


TreeNode* delete_tree(TreeNode* node) {
    if (node == NULL) {
        return NULL;
    }
    delete_tree(node->left);
    delete_tree(node->right);
    free(node); // Key Operation

    return NULL;
}


TreeNode* clone_tree(TreeNode* node) {
    if (node == NULL) {
        return NULL;
    }
    TreeNode* new_node = create_tree_node(node->data);  // Key Operation
    new_node->left = clone_tree(node->left);
    new_node->right = clone_tree(node->right);

    return new_node;
}


// Only works for a BST
TreeNode* find_min(TreeNode* node) {
    TreeNode* current = node;

    // Left-most node in a BST is the Minimum Valued Node
    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

// Applicable only for BST
TreeNode* delete_node(TreeNode* root, int data) {

    if (root == NULL) {
        return NULL;
    }

    if (data == root->data) {
        // => Either the right child is also NULL OR there is only a Non-NULL right child
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root); // node has been deleted.
            // After deleting the target node, you need to 
            // connect the right child (NULL / Non-NULL) of the 
            // deleted node to the "parent" of the deleted node.
            return temp;
        }
        else if (root->right == NULL) {
            // Only if right child does not exist BUT left child definitely exists
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // If the node to be deleted is a node that has both
        // the left and right child nodes

        // Find Inorder Successor => Only search the Right Subtree for minimum element
        // Finding the Left-mode node in the Right Sub-tree (in-case of BST)
        TreeNode* temp = find_min(root->right); // node containing 15.5

        root->data = temp->data; // Replace 15 by 15.5 (by its in-order successor)

        // Delete the node that contains 15.5
        // The left-most node in the right sub-tree (15.5) 
        // does not have any further left childs.

        // To delete the node containing 15.5, the solution is equivalent to 
        // the one discussed in the first if condition.
        root->right = delete_node(root->right, temp->data); // Delete the node in the right sub tree containing the value 25 
    }
    else if (data < root->data) {
        root->left = delete_node(root->left, data);
    }
    else {
        root->right = delete_node(root->right, data);
    }

    return root;
}

int main() {
    BinaryTree tree;
    tree.root = NULL;

    tree.root = insert_node(tree.root, 17);
    tree.root = insert_node(tree.root, 15);
    tree.root = insert_node(tree.root, 18);
    tree.root = insert_node(tree.root, 11);
    tree.root = insert_node(tree.root, 16);
    tree.root = insert_node(tree.root, 21);
    tree.root = insert_node(tree.root, 7);
    tree.root = insert_node(tree.root, 12);
    tree.root = insert_node(tree.root, 19);
    tree.root = insert_node(tree.root, 89);

    printf("In-order traversal of the binary tree:\n");
    in_order_traversal(tree.root);
    printf(" -- Tree \n");

    BinaryTree tree_copy;
    tree_copy.root = clone_tree(tree.root);
    in_order_traversal(tree_copy.root);
    printf(" -- Tree Copy \n");


    delete_node(tree.root, 89);
    in_order_traversal(tree.root);
    printf(" -- Tree after delete_node(89)\n");

    delete_node(tree.root, 7);
    in_order_traversal(tree.root);
    printf(" -- Tree after delete_node(7)\n");

    delete_node(tree.root, 17);
    in_order_traversal(tree.root);
    printf(" -- Tree after delete_node(17)\n");

    delete_node(tree.root, 21);
    in_order_traversal(tree.root);
    printf(" -- Tree after delete_node(21)\n");

    // delete_tree(tree.root);
    // in_order_traversal(tree.root);
    // printf("Tree after deletion \n");

    // in_order_traversal(tree_copy.root);
    // printf("Tree Copy after tree deletion \n");

    return 0;
}
