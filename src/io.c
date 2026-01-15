#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include "io.h"
#include "stack.h"
#include "sort.h"
#include "timer.h"


void clearInputBuffer() {
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF); }

static void print_stack(Stack *s) {
    for (Node *n = s->top; n; n = n->next)
        printf("%d ", n->data);
    printf("\n");
}

static void save_stack(const char *name, Stack *s) {
    FILE *f = fopen(name, "w");
    if (!f) return;
    for (Node *n = s->top; n; n = n->next)
        fprintf(f, "%d ", n->data);
    fclose(f);
}

static void read_input(Stack *s, int *elementsNum) {
    int x;
    printf("Введите числа через пробел (любую букву + enter чтобы закончить):\n");
    while (scanf("%d", &x) == 1) {
	stack_push(s, x);
	*elementsNum += 1;
	}

	clearInputBuffer();
}

static void read_file(const char *name, Stack *s, int *elementsNum) {
    FILE *f = fopen(name, "r");
    int x;
    if (!f) return;
    while (fscanf(f, "%d", &x) == 1){
        stack_push(s, x);
	*elementsNum +=1;
    }
    fclose(f);
}


void stack_reverse(Stack *s) {
    Stack tmp;
    stack_init(&tmp);

    while (!stack_is_empty(s)) {
        stack_push_node(&tmp, stack_pop_node(s));
    }

    s->top = tmp.top;
}


int stack_edit_by_index(Stack *s, int index, int new_value, int *elementsNum) {

    if(index < 1 || index > *elementsNum){
	printf("\n!неверный элемент!\n\n");
	*elementsNum = -1;
	return 0;
}
    Node *curr = s->top;
    int current_index = 1;

    while (curr != NULL) {
        if (current_index == index) {
            curr->data = new_value;  // change value
            return 1;                // success
        }
        curr = curr->next;
        current_index++;
    }
 return 0;
}


int IO(int argc, char **argv) {
   // SetConsoleOutputCP(CP_UTF8);
   // SetConsoleCP(CP_UTF8);
    Stack s;
    stack_init(&s);
    int option = 6;
    int elementsNum = 0;
    int index = 1;
    int value = 0;

    if (argc == 1)
        read_input(&s, &elementsNum);
    else{
           char *txtFile = NULL;
           int found = 0;  // 0 = false, 1 = true
        
        for (int i = 1; i < argc; i++) {
            size_t len = strlen(argv[i]);
            if (len >= 4 && strcmp(argv[i] + len - 4, ".txt") == 0) {
                txtFile = argv[i];
                found = 1;
                break;
            }
        }
            
        if (found) {
            read_file(txtFile, &s, &elementsNum);
        } else {
            // No .txt file found
            read_file(argv[1], &s, &elementsNum);
          }
    
	printf("\nпредыдущий стек\n");
	FILE *file_pointer;
	int number;
	file_pointer = fopen("unsorted.txt", "r");
	if (file_pointer == NULL) {
	printf("Error: Could not open the file unsorted.txt\n");
	 exit(1);
	}
	 while (fscanf(file_pointer, "%d", &number) == 1) {
	printf("%d ", number); 
	 }
	printf("\n");
	fclose(file_pointer);
	}


    if (stack_is_empty(&s)) {
        printf("Нет данных\n");
    }

    Stack tmp_reverse = copy_stack(&s);
    stack_reverse(&tmp_reverse);
    save_stack("unsorted.txt", &tmp_reverse);

    double ti = measure_insertion(&s);
    double tm = measure_merge(&s);

    merge_sort_stack(&s);
    save_stack("sorted.txt", &s);

    printf("Отсортированный стек:\n");
    print_stack(&s);
    printf("количество элементов: %d\n", elementsNum);
    printf("Время сортировки вставки: %.6f s\n", ti);
    printf("Время сортировки слиянием: %.6f s\n", tm);

    if (argc == 1) {
	do{
	   printf("Выберите вариант: (Если иначе, то выход)");
	   printf("\n0)сортировка");
	   printf("\n1)вставка");
  	   printf("\n2)удаление");
	   printf("\n3)вывод списка");
	   printf("\n4)Редактирование значения элемента по его номеру");
	   printf("\n5)повторить программу");
	   printf("\n6)выход\n");
           if(scanf(" %d", &option) != 1){
		clearInputBuffer();
		option = 6;
	   }
	   if (option == 0){
		elementsNum = 0;
		stack_free(&s);
		stack_init(&s);
		read_file("unsorted.txt", &s, &elementsNum);
		double ti = measure_insertion(&s);
    		double tm = measure_merge(&s);
    		merge_sort_stack(&s);
    		save_stack("sorted.txt", &s);

    		printf("Отсортированный стек:\n");
    		print_stack(&s);
    		printf("количество элементов: %d\n", elementsNum);
    		printf("Время сортировки вставки: %.6f s\n", ti);
    		printf("Время сортировки слиянием: %.6f s\n", tm);
}
	  else  if (option == 1){
		int addToStack = 0;
		elementsNum = 0;
	   	printf("введите число: ");
		if(scanf("%d", &addToStack) != 1){
			clearInputBuffer();
			addToStack = 0;}
                stack_free(&s);
		stack_free(&tmp_reverse);
		stack_init(&s);
		read_file("unsorted.txt", &s, &elementsNum);
		tmp_reverse = copy_stack(&s);
    		stack_reverse(&tmp_reverse);
		stack_free(&s);
		s = copy_stack(&tmp_reverse);
		stack_push(&s, addToStack);
    		save_stack("unsorted.txt", &s);
		printf("стек после вставки:\n");
		print_stack(&s);
		elementsNum += 1;
	   }
           else if (option == 2){
		elementsNum = 0;
		stack_free(&tmp_reverse);
                stack_free(&s);
		stack_init(&s);
                read_file("unsorted.txt", &s, &elementsNum);
		tmp_reverse = copy_stack(&s);
    		stack_reverse(&tmp_reverse);
		stack_free(&s);
		s = copy_stack(&tmp_reverse);
		if (!stack_is_empty(&s)) {
 		       free(stack_pop_node(&s));
		       elementsNum -= 1;
		       save_stack("unsorted.txt", &s);
               	       printf("стек после удаление:\n");
                       print_stack(&s);
		}else {
    		save_stack("unsorted.txt", &s);
		printf("стек пустой\n");
                }
	   }
	   else if (option == 3){
		elementsNum = 0;
                stack_free(&s);
		stack_free(&tmp_reverse);
                stack_init(&s);
                read_file("unsorted.txt", &s, &elementsNum);
		tmp_reverse = copy_stack(&s);
    		stack_reverse(&tmp_reverse);
		print_stack(&tmp_reverse);
	   }
	   else if (option == 4){
			elementsNum = 0;
               		stack_free(&tmp_reverse);
                	stack_free(&s);
                	stack_init(&s);
                	read_file("unsorted.txt", &s, &elementsNum);
                	tmp_reverse = copy_stack(&s);
                	stack_reverse(&tmp_reverse);
                	stack_free(&s);
                	s = copy_stack(&tmp_reverse);
			printf("количество элементов: %d\n", elementsNum);
			printf("Выберите какой элемент вы хотите изменить: ");
			if (scanf("%d", &index) !=1){
			   clearInputBuffer();
			   index = -1;
			}
			printf("выберите новое значение элемента: ");
			if (scanf("%d", &value) !=1){
			   clearInputBuffer();
			   value = 0;
			}
			stack_edit_by_index(&s, index, value, &elementsNum);
			save_stack("unsorted.txt", &s);
			if (elementsNum != -1){
                        	printf("стек после изменение значение:\n");
				print_stack(&s);
			}
	   }
	   else if (option == 5){
			stack_free(&tmp_reverse);
	    		stack_free(&s);
			return IO(argc, argv);
		}else{
		     stack_free(&tmp_reverse);
	             stack_free(&s);
		     return 0;
		}
	}while(option != 6);
    }

    stack_free(&tmp_reverse);
    stack_free(&s);
    return 0;
}
