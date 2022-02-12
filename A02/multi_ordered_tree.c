//
// AED, January 2022
//
// Solution of the second practical assignement (multi-ordered tree)
//
// Place your student numbers and names here
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AED_2021_A02.h"

//
// the custom tree node structure
//
// we want to maintain three ordered trees (using the same nodes!), so we need three left and three right pointers
// so, when inserting a new node we need to do it three times (one for each index), so we will end upo with 3 three roots
//

typedef struct tree_node_s {
    char name[MAX_NAME_SIZE + 1];                                      // index 0 data item
    char zip_code[MAX_ZIP_CODE_SIZE + 1];                              // index 1 data item
    char telephone_number[MAX_TELEPHONE_NUMBER_SIZE + 1];              // index 2 data item
    char social_security_number[MAX_SOCIAL_SECURITY_NUMBER_SIZE + 1];  // index 3 data item
    struct tree_node_s *left[4];                                       // left pointers (one for each index) ---- left means smaller
    struct tree_node_s *right[4];                                      // right pointers (one for each index) --- right means larger
} tree_node_t;

//
// the node comparison function (do not change this)
//

int compare_tree_nodes(tree_node_t *node1, tree_node_t *node2, int main_idx) {
    int i, c;

    for (i = 0; i < 4; i++) {
        if (main_idx == 0)
            c = strcmp(node1->name, node2->name);
        else if (main_idx == 1)
            c = strcmp(node1->zip_code, node2->zip_code);
        else if (main_idx == 2)
            c = strcmp(node1->telephone_number, node2->telephone_number);
        else
            c = strcmp(node1->social_security_number, node2->social_security_number);
        if (c != 0)
            return c;  // different on this index, so return
        //main_idx = (main_idx == 2) ? 0 : main_idx + 1;  // advance to the next index

        if (main_idx == 0) {
            main_idx = 1;
        } else if (main_idx == 1) {
            main_idx = 2;
        } else if (main_idx == 2) {
            main_idx = 3;
        } else {
            main_idx = 0;
        }
    }
    return 0;
}

int compare_node_parameters(tree_node_t *node1, char *string, int main_idx) {
    int c;
    if (main_idx == 0)
        c = strcmp(node1->name, string);
    else if (main_idx == 1)
        c = strcmp(node1->zip_code, string);
    else if (main_idx == 2)
        c = strcmp(node1->telephone_number, string);
    else
        c = strcmp(node1->social_security_number, string);

    return c;  // different on this index, so return  // advance to the next index
}

//
// tree insertion routine (place your code here)
// arguments
//  - pointer to pointer of root
//  - pointer to node to insert
//  - order criterion index [0 || 1 || 2 || 3]

void tree_insert(tree_node_t **root, tree_node_t *node, int main_index) {
    // recursive

    //Check if tree is empty
    if (*root == NULL) {
        *root = node;
        return;
    }

    int c = compare_tree_nodes(*root, node, main_index);
    if (c > 0) {  // if smaller, insert in left side
        /*if ((*root)->left[main_index] == NULL) {
            (*root)->left[main_index] = node;
        } else {
            tree_insert(&((*root)->left[main_index]), node, main_index);
        }*/
        tree_insert(&((*root)->left[main_index]), node, main_index);
    } else if (c < 0) {  // if bigger, insert in right side
        /*if ((*root)->right[main_index] == NULL) {
            (*root)->right[main_index] = node;
        } else {
            tree_insert(&((*root)->right[main_index]), node, main_index);
        }*/
        tree_insert(&((*root)->right[main_index]), node, main_index);

    } else {
        printf("Não podem existir dois nodes iguais !!!\n");
        exit(1);
    }
}

//
// tree search routine (place your code here)
// returns a pointer to the node that was found (if found)
//

tree_node_t *find(tree_node_t *root, tree_node_t *node, int main_index) {
    if (root == NULL) {  // tree is empty, do nothing
        return;
    }

    int c = compare_tree_nodes(root, node, main_index);

    if (c < 0) {
        find(root->right[main_index], node, main_index);
    } else if (c > 0) {
        find(root->left[main_index], node, main_index);
    } else {
        return root;
    }
}

//
// tree depth
// finds the tree depth on specified index
//

int tree_depth(tree_node_t *root, int main_index, int depthLeft, int depthRight) {
    if (root == NULL) {
        return 0;
    } else {
        depthLeft = tree_depth(root->left[main_index], main_index, depthLeft, depthRight);
        depthRight = tree_depth(root->right[main_index], main_index, depthLeft, depthRight);

        if (depthLeft > depthRight) {
            return (depthLeft + 1);
        } else {
            return (depthRight + 1);
        }
    }
}

//
// list, i,e, traverse the tree (place your code here)
// list prints the tree contents
// arguments
//  - pointer to root
//  - order criterion index [0 || 1 || 2]
//  - next index for ordered person (starts at 1 always)
//
// return value
//  - returns position
//  - if 0, then tree was empty
//

int list(tree_node_t *root, int main_index, int position) {
    // recursive
    // if root points to nothing, tree is empty, do nothing
    if (root == NULL) {
        return position;
    }

    // if elements left from root, start from there
    //if (root->left[main_index] != NULL) {
    position = list(root->left[main_index], main_index, position);
    //}

    // after doing left stuff, print this node
    position++;
    printNode(root, position);

    // if elements right, return right-most position
    //if (root->right[main_index] != NULL) {
    position = list(root->right[main_index], main_index, position);
    //}

    return position;
}

int findNode(tree_node_t *root, char *string, int main_index, int position) {
    if (compare_node_parameters(root, string, main_index) < 0) {
        //if (root->right[main_index] != 0) {
        position = findNode(root->right[main_index], string, main_index, position);
        //}

    } else if (compare_node_parameters(root, string, main_index) > 0) {
        //if (root->left[main_index] != 0) {
        position = findNode(root->left[main_index], string, main_index, position);
        //}

    } else {
        printNode(root, position);
        position++;

        //if (root->left[main_index] != 0 && root->right[main_index] != 0) {
        position = findNode(root->left[main_index], string, main_index, position);
        position = findNode(root->right[main_index], string, main_index, position);

        //}
        return position;
    }
}

// prints node parameters

void printNode(tree_node_t *node, int position) {
    printf("Person #%d\n", position);
    printf("name --------------------- %s\n", node->name);
    printf("zip code ----------------- %s\n", node->zip_code);
    printf("telephone number --------- %s\n", node->telephone_number);
    printf("social security number --- %s\n", node->social_security_number);
}

//
// main program
//

int main(int argc, char **argv) {
    double dt;

    // process the command line arguments
    if (argc < 3) {
        fprintf(stderr, "Usage: %s student_number number_of_persons [options ...]\n", argv[0]);
        fprintf(stderr, "Recognized options:\n");
        fprintf(stderr, "  -list[N]              # list the tree contents, sorted by key index N (the default is index 0)\n");
        // place a description of your own options here
        return 1;
    }

    int student_number = atoi(argv[1]);
    if (student_number < 1 || student_number >= 1000000) {
        fprintf(stderr, "Bad student number (%d) --- must be an integer belonging to [1,1000000{\n", student_number);
        return 1;
    }

    int n_persons = atoi(argv[2]);
    if (n_persons < 3 || n_persons > 10000000) {
        fprintf(stderr, "Bad number of persons (%d) --- must be an integer belonging to [3,10000000]\n", n_persons);
        return 1;
    }

    // generate all data
    tree_node_t *persons = (tree_node_t *)calloc((size_t)n_persons, sizeof(tree_node_t));
    if (persons == NULL) {
        fprintf(stderr, "Output memory!\n");
        return 1;
    }
    aed_srandom(student_number);
    for (int i = 0; i < n_persons; i++) {
        random_name(&(persons[i].name[0]));
        random_zip_code(&(persons[i].zip_code[0]));
        random_telephone_number(&(persons[i].telephone_number[0]));
        random_social_security_number(&(persons[i].social_security_number[0]));
        for (int j = 0; j < 4; j++)
            persons[i].left[j] = persons[i].right[j] = NULL;  // make sure the pointers are initially NULL
    }

    // create the ordered binary trees
    dt = cpu_time();
    tree_node_t *roots[4];  // four indices, four roots
    for (int main_index = 0; main_index < 4; main_index++)
        roots[main_index] = NULL;

    for (int i = 0; i < n_persons; i++) {
        for (int main_index = 0; main_index < 4; main_index++) {
            tree_insert(&roots[main_index], &persons[i], main_index);  // place your code here to insert &(persons[i]) in the tree with number main_index
        }
    }
    dt = cpu_time() - dt;

    printf("Tree creation time (%d persons): %.3es\n", n_persons, dt);

    // search the tree
    for (int main_index = 0; main_index < 4; main_index++) {
        dt = cpu_time();
        for (int i = 0; i < n_persons; i++) {
            tree_node_t n = persons[i];                                    // make a copy of the node data
            if (find(roots[main_index], &n, main_index) != &(persons[i]))  // place your code here to find a given person, searching for it using the tree with number main_index
            {
                fprintf(stderr, "person %d not found using index %d\n", i, main_index);
                return 1;
            }
        }
        dt = cpu_time() - dt;
        printf("Tree search time (%d persons, index %d): %.3es\n", n_persons, main_index, dt);
    }

    // compute the largest tree depdth
    for (int main_index = 0; main_index < 4; main_index++) {
        dt = cpu_time();
        int depth = tree_depth(roots[main_index], main_index, 0, 0);  // place your code here to compute the depth of the tree with number main_index
        dt = cpu_time() - dt;
        printf("Tree depth for index %d: %d (done in %.3es)\n", main_index, depth, dt);
    }

    // process the command line optional arguments
    for (int i = 3; i < argc; i++) {
        if (strncmp(argv[i], "-list", 5) == 0) {  // list all (optional)
            int main_index = atoi(&(argv[i][5]));
            if (main_index < 0)
                main_index = 0;
            if (main_index > 3)
                main_index = 3;
            printf("Main index: %d\n", main_index);
            printf("List of persons:\n");
            (void)list(roots[main_index], main_index, 0);  // place your code here to traverse, in order, the tree with number main_index
        }
        // place your own options here

        if (strncmp(argv[i], "-find", 5) == 0) {  // find node with specific index
            int main_index = atoi(&(argv[i][5]));
            if (main_index < 0)
                main_index = 0;
            if (main_index > 3)
                main_index = 3;
            char *string = argv[i + 1];
            printf("List of persons:\n");
            (void)findNode(roots[main_index], string, main_index, 1);
        }
    }
    // clean up --- don't forget to test your program with valgrind, we don't want any memory leaks
    free(persons);
    return 0;
}
