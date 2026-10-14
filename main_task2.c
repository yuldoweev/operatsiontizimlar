
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 256

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

static int read_int(const char *prompt, int *value) {
    char line[LINE_SIZE];
    char *end = NULL;

    printf("%s", prompt);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    long parsed = strtol(line, &end, 10);
    if (end == line || errno == ERANGE || parsed < -2147483647L - 1L ||
        parsed > 2147483647L) {
        return 0;
    }
    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
        end++;
    }
    if (*end != '\0') {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

static Node *create_node(int value) {
    Node *node = malloc(sizeof *node);
    if (node == NULL) {
        fprintf(stderr, "Xato: xotira ajratilmadi.\n");
        return NULL;
    }
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static Node *insert(Node *root, int value, int *ok) {
    if (root == NULL) {
        Node *node = create_node(value);
        if (node == NULL) {
            *ok = 0;
        }
        return node;
    }

    if (value < root->value) {
        Node *child = insert(root->left, value, ok);
        if (*ok) {
            root->left = child;
        }
    } else if (value > root->value) {
        Node *child = insert(root->right, value, ok);
        if (*ok) {
            root->right = child;
        }
    } else {
        puts("Eslatma: bu qiymat daraxtda bor, takroran qo'shilmadi.");
    }
    return root;
}

static const Node *search(const Node *root, int value) {
    const Node *current = root;
    while (current != NULL) {
        if (value == current->value) {
            return current;
        }
        current = (value < current->value) ? current->left : current->right;
    }
    return NULL;
}

static void inorder(const Node *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->value);
    inorder(root->right);
}
static void free_tree(Node *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void) {
    Node *root = NULL;
    int count;

    if (!read_int("Nechta son kiritasiz? ", &count) || count < 0 || count > 10000) {
        puts("Xato: sonlar miqdori 0 dan 10000 gacha butun son bo'lishi kerak.");
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        int value;
        char prompt[64];
        (void)snprintf(prompt, sizeof prompt, "%d-son: ", i + 1);

        if (!read_int(prompt, &value)) {
            puts("Xato: butun son kiriting. Daraxt xotirasi bo'shatiladi.");
            free_tree(root);
            return 1;
        }

        int ok = 1;
        root = insert(root, value, &ok);
        if (!ok) {
            puts("Xato: xotira yetarli emas. Daraxt xotirasi bo'shatiladi.");
            free_tree(root);
            return 1;
        }
    }

    printf("In-order tartibi: ");
    if (root == NULL) {
        printf("(daraxt bo'sh)");
    } else {
        inorder(root);
    }
    putchar('\n');

    int target;
    if (!read_int("Qidiriladigan son: ", &target)) {
        puts("Xato: qidiruv qiymati butun son bo'lishi kerak.");
        free_tree(root);
        return 1;
    }

    if (search(root, target) != NULL) {
        printf("%d daraxtdan topildi.\n", target);
    } else {
        printf("%d daraxtdan topilmadi.\n", target);
    }

    free_tree(root);
    puts("Xotira bo'shatildi.");
    return 0;
}
