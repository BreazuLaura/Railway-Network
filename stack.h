typedef struct {
	/* Valoarea retinuta de catre nod. */
	int val;

	/* Pointer catre urmatorul element de tip nod. */
	struct stack_node_t *next;
} stack_node_t;
typedef struct {
	/* Capul listei inlantuite. */
	struct stack_node_t *head;

	/* Dimensiunea stivei. */
	unsigned int length;
} stack_t;
stack_t *stack_create();
stack_node_t *stack_node_create(int val);
void stack_push(stack_t *stack, int val);
void stack_print(stack_t *stack);
int stack_pop(stack_t *stack);
int stack_top(stack_t *stack);
int stack_empty(stack_t *stack);
int stack_length(stack_t *stack);

