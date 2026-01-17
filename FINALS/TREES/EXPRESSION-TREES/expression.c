#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
===========================================
            STRUCT DEFINITIONS
===========================================
*/

typedef struct {
    char* data[100];
    int top;
} Stack;

typedef struct node {
    char label[20];      // node label (e.g., "R", "A", "L2")
    char data[10];       // operator ("+", "-", "*", "/") or number ("12")
    struct node* left;
    struct node* right;
} Node, *Tree;

/*
===========================================
        FUNCTION PROTOTYPES
===========================================
*/
void printInfix(Tree root);
void printPostfix(Tree root);
void printPrefix(Tree root);
Tree makeNode(const char* label, const char* data);
// YOU implement this:
int evaluateTree(Tree root);
void init_stack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, const char* str) {
    s->data[++s->top] = strdup(str);
}

char* pop(Stack* s) {
    if (s->top == -1) return NULL;
    return s->data[s->top--];
}

char* peek(Stack* s) {
    if (s->top == -1) return NULL;
    return s->data[s->top];
}

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

char** infixToPostfix(char* expr, int* count) {
    Stack s;
    init_stack(&s);

    char** output = malloc(sizeof(char*) * strlen(expr));
    int outCount = 0;

    for (int i = 0; expr[i]; i++) {

        if (isspace(expr[i])) continue;

        // ---- NUMBER (multi-digit)
        if (isdigit(expr[i])) {
            char buffer[50];
            int k = 0;

            while (isdigit(expr[i])) {
                buffer[k++] = expr[i++];
            }
            buffer[k] = '\0';
            output[outCount++] = strdup(buffer);

            i--; // adjust position
        }

        // ---- LEFT PAREN
        else if (expr[i] == '(') {
            push(&s, "(");
        }

        // ---- RIGHT PAREN
        else if (expr[i] == ')') {
            while (s.top >= 0 && strcmp(peek(&s), "(") != 0) {
                output[outCount++] = pop(&s);
            }
            pop(&s);   // remove "("
        }

        // ---- OPERATOR
        else {
            char op = expr[i];

            while (s.top >= 0 &&
                   strcmp(peek(&s), "(") != 0 &&
                   precedence(peek(&s)[0]) >= precedence(op)) {

                output[outCount++] = pop(&s);
            }

            char temp[2] = { op, '\0' };
            push(&s, temp);
        }
    }

    // Pop remaining operators
    while (s.top >= 0) {
        output[outCount++] = pop(&s);
    }

    *count = outCount;
    return output;
}



Tree buildTree(char** postfix, int count) {
    Tree stack[100];
    int top = -1;

    for (int i = 0; i < count; i++) {
        char* token = postfix[i];

        // NUMBER ⇒ leaf node
        if (isdigit(token[0])) {
            stack[++top] = makeNode("N", token);
        }
        // OPERATOR ⇒ pop two nodes
        else {
            Tree right = stack[top--];
            Tree left = stack[top--];

            Tree newNode = makeNode("O", token);
            newNode->left = left;
            newNode->right = right;

            stack[++top] = newNode;
        }
    }

    return stack[top];
}

void runExpressionTest(const char* expr, int expected) {
    int count = 0;

    printf("\n---------------------------------------------\n");
    printf("Expression: %s\n", expr);

    // Convert infix → postfix
    char* temp = strdup(expr);
    char** postfix = infixToPostfix(temp, &count);

    printf("Postfix: ");
    for (int i = 0; i < count; i++) {
        printf("%s ", postfix[i]);
    }
    printf("\n");

    // Build expression tree from postfix
    Tree T = buildTree(postfix, count);

    // Evaluate the tree
    int result = evaluateTree(T);
    printf("Result: %d\n", result);

    // Check correctness
    printf("Status: %s\n", (result == expected ? "PASS" : "FAIL"));

    // Display different traversals
    printf("Infix:   ");
    printInfix(T);
    printf("\n");

    printf("Prefix:  ");
    printPrefix(T);
    printf("\n");

    printf("Postfix: ");
    printPostfix(T);
    printf("\n");

    free(temp);
}

// Helpers already done:

// Test case builders:
Tree buildTest1();   // (2 * 3) + 5
Tree buildTest2();   // 10 - (4 / 2)
Tree buildTest3();   // 7 + (6 * 2)
Tree buildTest4();   // (5 * (8 - 3)) + 1
Tree buildTest5();   // ((20 / 2) * (3 + 1)) - 7

/*
===========================================
                 MAIN
===========================================
*/


int main() {
    printf("===== EXPRESSION TREE TESTS (AUTO-GENERATED) =====\n");

    runExpressionTest("(2 * 3) + 5",                11);
    runExpressionTest("10 - (4 / 2)",               8);
    runExpressionTest("7 + (6 * 2)",                19);
    runExpressionTest("(5 * (8 - 3)) + 1",          26);
    runExpressionTest("((20 / 2) * (3 + 1)) - 7",   33);

    return 0;
}
/*
===========================================
          FUNCTION YOU MUST DO
===========================================
*/

// typedef struct node {
//     char label[20];      // node label (e.g., "R", "A", "L2")
//     char data[10];       // operator ("+", "-", "*", "/") or number ("12")
//     struct node* left;
//     struct node* right;
// } Node, *Tree;


int evaluateTree(Tree root) {
    /*
       TODO: Implement this function.

       Rules:
       - If root->data is a number → return atoi(root->data)
       - Otherwise, it's an operator ("+", "-", "*", "/")
       - Recursively evaluate left & right children
       - Apply the operator

       Example guideline:
            if (strcmp(root->data, "+") == 0)
                return evaluateTree(root->left) + evaluateTree(root->right);
    */
    if (strcmp(root->data, "+") == 0){
        return evaluateTree(root->left) + evaluateTree(root->right);
    }else if(strcmp(root->data, "-") == 0){
        return evaluateTree(root->left) - evaluateTree(root->right);
    }else if(strcmp(root->data, "*") == 0){
        return evaluateTree(root->left) * evaluateTree(root->right);
    }else if(strcmp(root->data, "/") == 0){
        return evaluateTree(root->left) / evaluateTree(root->right);
    }else{
        return atoi(root->data);
    }
}

void printInfix(Tree root) {
    if (!root) return;

    // Print parentheses ONLY for non-leaf nodes
    if (root->left || root->right) printf("(");

    printInfix(root->left);
    printf("%s", root->data);
    printInfix(root->right);

    if (root->left || root->right) printf(")");
}

void printPrefix(Tree root) {
    if (!root) return;
    printf("%s ", root->data);
    printPrefix(root->left);
    printPrefix(root->right);
}

void printPostfix(Tree root) {
    if (!root) return;
    printPostfix(root->left);
    printPostfix(root->right);
    printf("%s ", root->data);
}


/*
===========================================
        TREE CREATION HELPER
===========================================
*/

Tree makeNode(const char* label, const char* data) {
    Tree t = malloc(sizeof(Node));
    strcpy(t->label, label);
    strcpy(t->data, data);
    t->left = t->right = NULL;
    return t;
}

/*
===========================================
                TEST CASE 1
          (2 * 3) + 5
===========================================
*/

Tree buildTest1() {
    Tree R = makeNode("R", "+");
    Tree A = makeNode("A", "*");
    Tree L1 = makeNode("L1", "2");
    Tree L2 = makeNode("L2", "3");
    Tree B = makeNode("B", "5");

    R->left = A;
    R->right = B;
    A->left = L1;
    A->right = L2;

    return R;
}

/*
===========================================
                TEST CASE 2
           10 - (4 / 2)
===========================================
*/

Tree buildTest2() {
    Tree R = makeNode("R", "-");
    Tree L = makeNode("L", "10");
    Tree A = makeNode("A", "/");
    Tree L1 = makeNode("L1", "4");
    Tree L2 = makeNode("L2", "2");

    R->left = L;
    R->right = A;
    A->left = L1;
    A->right = L2;

    return R;
}

/*
===========================================
                TEST CASE 3
             7 + (6 * 2)
===========================================
*/

Tree buildTest3() {
    Tree R = makeNode("R", "+");
    Tree L = makeNode("L", "7");
    Tree A = makeNode("A", "*");
    Tree L1 = makeNode("L1", "6");
    Tree L2 = makeNode("L2", "2");

    R->left = L;
    R->right = A;
    A->left = L1;
    A->right = L2;

    return R;
}

/*
===========================================
                TEST CASE 4
         (5 * (8 - 3)) + 1
===========================================
*/

Tree buildTest4() {
    Tree R = makeNode("R", "+");
    Tree A = makeNode("A", "*");
    Tree L1 = makeNode("L1", "5");
    Tree B = makeNode("B", "-");
    Tree C1 = makeNode("C1", "8");
    Tree C2 = makeNode("C2", "3");
    Tree D = makeNode("D", "1");

    R->left = A;
    R->right = D;

    A->left = L1;
    A->right = B;

    B->left = C1;
    B->right = C2;

    return R;
}

/*
===========================================
                TEST CASE 5
       ((20 / 2) * (3 + 1)) - 7
===========================================
*/

Tree buildTest5() {
    Tree R = makeNode("R", "-");

    Tree A = makeNode("A", "*");
    Tree B = makeNode("B", "/");
    Tree C = makeNode("C", "+");

    Tree L1 = makeNode("L1", "20");
    Tree L2 = makeNode("L2", "2");
    Tree L3 = makeNode("L3", "3");
    Tree L4 = makeNode("L4", "1");
    Tree L5 = makeNode("L5", "7");

    // Left subtree: (20 / 2) * (3 + 1)
    B->left = L1; B->right = L2;
    C->left = L3; C->right = L4;

    A->left = B;
    A->right = C;

    R->left = A;
    R->right = L5;

    return R;
}