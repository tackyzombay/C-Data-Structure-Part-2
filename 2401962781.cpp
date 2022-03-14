#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Haha{
	char name[100];
	struct Haha* left;
	struct Haha* right;
	int value;
	char color[100];
	char type[100];
	char farm[100];
	
	int height;
};

int max(int a, int b){
	return (a > b) ? a : b;
}

int get_height(struct Haha* node){
	if(node == NULL)return 0;
	return node->height;
}

int get_balance(struct Haha* node){
	if(node == NULL) return 0;
	return get_height(node->left) - get_height(node->right);	
}

struct Haha* right_rotate(struct Haha* node){
	struct Haha* x = node->left;
	struct Haha* sub_x = x->right;
	
	x->right = node;
	node->left = sub_x;
	
	node->height = max(get_height(node->left), get_height(node->right));
	x->height = max(get_height(x->left), get_height(x->right));
	
	return x;
}

struct Haha* left_rotate(struct Haha* node){
	struct Haha* x = node->right;
	struct Haha* sub_x = x->left;
	
	x->left = node;
	node->right = sub_x;
	
	node->height = max(get_height(node->left), get_height(node->right));
	x->height = max(get_height(x->left), get_height(x->right));
	
	return x;
}

struct Haha* new_node(int value, char* name, char* color, char* type, char* farm){
	struct Haha* newHaha = (struct Haha*) malloc(sizeof(struct Haha));
	newHaha->value = value;
	strcpy(newHaha->name, name);
	strcpy(newHaha->color, color);
	strcpy(newHaha->type, type);
	strcpy(newHaha->farm, farm);
	newHaha->left = NULL;
	newHaha->right = NULL;
	newHaha->height = 1;
	return newHaha;
}

struct Haha* insert(struct Haha* node, int value, char* name, char* color, char* type, char* farm){
	if(node == NULL){
		return new_node(value ,name, color, type, farm);
	}
	
	if(value < node->value){
		node->left = insert(node->left,value,name, color, type, farm);
	}else if(value > node->value){
		node->right = insert(node->right,value,name, color, type, farm);
	}else return node;
	
	node->height = 1 + max(get_height(node->left), get_height(node->right));
	int balance = get_balance(node);
	
	if(balance > 1 && value < node->left->value){

		return right_rotate(node);
	}
	

	if(balance > 1 && value > node->left->value){

		node->left = left_rotate(node->left);

		return right_rotate(node);
	}
	

	if(balance < -1 && value > node->right->value){

		return left_rotate(node);
	}
	

	if(balance < -1 && value < node->right->value){

		node->right = right_rotate(node->right);

		return left_rotate(node);
	}
	return node;
}

int startsWith(char a[], char b[]){
	if(strncmp(a ,b ,strlen(b)) == 0){
		return 1;
	}else{
		return 0;
	}
}

int check2Words(char string[]){
	int i = 0;
	int count = 0;
	int flag = 0;
	while(string[i] != '\n'){
		if(string[i] == ' '){
			count++;
		}
		if(string[i-1] != NULL && string[i+1] != NULL){
			flag = 1;
		}
		
		i++;
	}	
	if(count >= 1 && string[0] != ' ' && flag == 1){
		return 1;
	}else{
		return 0;
	}
}

void insertFish(){
	char name[100];
	int value;
	char color[100];
	char type[100];
	char farm[100];
	
	do{
		printf("Input Fish Name [5..20]:");
		scanf("[^\n]", name);
		getchar();
	}while(strlen(name) < 5 && strlen(name) > 20);
	
	do{
		printf("Input Fish Color [Starts with Light | Normal | Dark]:");
		scanf("[^\n]", color);
		getchar();
	}while(startsWith(name, "Light") == 0 && startsWith(name, "Normal") == 0 && startsWith(name, "Dark") == 0 && check2Words(name) == 0);
	
	do{
		printf("Input Fish Type [Freshwater | Saltwater]:");
		scanf("[^\n]", type);
		getchar();
	}while(strcmp(type, "Freshwater") != 0 && strcmp(type, "Saltwater") != 0);
	
	do{
		printf("Input Fish Price [10000...100000]:");
		scanf("%d", &value);
		getchar();
	}while(value < 10000 && value > 100000);
	
	do{
		printf("Input Fish Farm [Ends with Co. | Inc. | Ltd.]:");
		scanf("[^\n]", farm);
		getchar();
	}while(check2Words(name) == 0);
	
	struct Haha* insert(struct Haha* node, int value, char* name, char* color, char* type, char* farm);
}

void pre_order(struct Haha* node){
	if(node==NULL){
		return;
	}
		printf("%s - %s - %s - %d - %s\n", node->name, node->color, node->type, node->value, node->farm);
		pre_order(node->left);
		pre_order(node->right);
	
}

void post_order(struct Haha *node){
	
    if(node==NULL){
	return;
	}
	post_order(node->left);
 
    post_order(node->right);
 
    printf("%s - %s - %s - %d - %s\n", node->name, node->color, node->type, node->value, node->farm);
    
	
	
}

void in_order(struct Haha *node){
	
	if(node==NULL){
	return;
	}
		in_order(node->left);
		
		printf("%s - %s - %s - %d - %s\n", node->name, node->color, node->type, node->value, node->farm);
		
		in_order(node->right);
	
	
}

struct Haha* find_product(struct Haha* node, int value){
	if(node == NULL){
		printf("Product not found!\n");
		return NULL;
	}
	
	if(value < node->value){
		return find_product(node->left, value);
	}else if(value > node->value){
		return find_product(node->right, value);
	}
	
	return node;
}

struct Haha* get_pred(struct Haha* node){
	struct Haha* curr = node->left;
	while(curr->right){
		curr = curr->right;
	}
	return curr;
}

struct Haha* get_su(struct Haha* node){
	struct Haha* curr = node->right;
	while(curr->left){
		curr = curr->left;
	}
	return curr;
}

struct Haha* delete_product(struct Haha* node, int value){

	if(node == NULL){
		printf("Not found!\n");
		return NULL;
	}
	
	if(value < node->value){
		node->left = delete_product(node->left, value);
	}else if(value > node->value){
		node->right = delete_product(node->right, value);
	}else{
		if(node->right == NULL || node->left == NULL){
			struct Haha* temp = NULL;
			if(node->left){
				temp = node->left;
			}else{
				temp = node->right;
			}
			
			free(node);
			node = temp;
			
			if(node == NULL){
				return NULL;
			}
		}else{
			struct Haha* pred = get_pred(node);
			node->value = pred->value;
			strcpy(node->name, pred->name);
			
			node->left = delete_product(node->left, pred->value);
		}
	}


	node->height = 1 + max(get_height(node->left), get_height(node->right));
	int balance = get_balance(node);
	
 
	if(balance > 1 && get_balance(node->left) >= 0 ){

		return right_rotate(node);
	}
	

	if(balance > 1 && get_balance(node->left) < 0){

		node->left = left_rotate(node->left);
	
		return right_rotate(node);
	}
	
	
	if(balance < -1 && get_balance(node->left) <= 0){

		return left_rotate(node);
	}
	

	if(balance < -1 && get_balance(node->left) > 0){
	
		node->right = right_rotate(node->right);
		
		return left_rotate(node);
	}
	
	return node;
	
}

int main(){
	
	int menu = 0;
	char cetak[100];
	struct Haha* node = NULL;
	int value;
	
	do{
		printf("FishyMart\n");
		printf("=========\n");
		printf("1. View Fish\n");
		printf("2. Insert Fish\n");
		printf("3. Delete Fish\n");
		printf("4. Exit\n");
		
		printf(">>");
		scanf("%d", &menu);
		getchar();
		
		if(menu==1){
			printf("Choose Order [Pre | In | Post]:");
			scanf("[^\n]", cetak);
			
			if(struct Haha* node = NULL){
				printf("No Fish Availabe!");
			}else{
				
				if(cetak == "Pre"){
					pre_order(node);
				}else if(cetak=="In"){
					in_order(node);
				}else{
					post_order(node);
				}
			
			}
			
		}else if(menu==2){
			insertFish();
			printf("\n");
			printf("Insert Success!");
		}else if(menu==3){
			if(struct Haha* node = NULL){
				printf("No Fish Availabe!");
			}else{
				do{
					printf("Input Fish Price:");
					scanf("[^\n]", value);
					getchar();
				}while(value < 10000 || value > 100000);
				
				delete_product(node, value);
				printf("Delete success!");
			}
		}
		
	}while(menu!=4);
	
	
	
	
}
