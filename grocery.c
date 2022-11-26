// Name  	: Lau Qi Ming
// ID 		: 20202456
// Title 	: Grocery Store Database
// Date 	: 16 / 12 / 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item {
	int id;
	char name[20];
	double cost;
	char category;
	struct item *next;
};

int saveFlag;
char fn[256];  // To store filename and pass to function save

void foodList(struct item *node);
void addNewItem(struct item *node);
void delItem(struct item **node);
void updateItem(struct item *node);
void searchItem(struct item *node);
void showInventory(struct item *node);
struct item *sort(struct item *node, int sortOrder, int sortKey, int *saveFlag);
void sortID (struct item * node, int sortOrder);
void sortName(struct item *node, int sortOrder);
void sortCost(struct item *node, int sortOrder);
void sortCategory (struct item *node, int sortOrder);
void save (struct item *node, char filename[]);
void showMenu(struct item *node);


int main() {
	struct item *node = NULL;
	struct item *curNode = NULL;
	char filename[256];
	FILE *file = NULL;
	char row[1000];

	printf("\n---------Welcome to the grocery store!---------\n\n");
	printf("Please key in the file name you'd like to load into stock:\n->");
	scanf("%s", filename);

	file = fopen(filename, "r");
	if (file == NULL) {
		// Display error message and exit program if cannot find file
		printf("ERROR : %s not found!\n\n", filename);
		exit(0);
	}
	strcpy(fn, filename);
	
	// Read text line by line and load into linked list
	while (fgets(row, 1000, file)) {
		
		// Split the line by tab and get the values
		char *col = strtok(row, "\t");
		struct item *newNode = (struct item*)malloc(sizeof(struct item));

		newNode->id = atoi(col);
		
		col = strtok(NULL, "\t");
		strcpy(newNode->name, col);
		
		col = strtok(NULL, "\t");
		newNode->cost = atof(col);
		
		col = strtok(NULL, "\t");
		newNode->category = col[0];
		
		newNode->next = NULL;

		if (node == NULL) {
			node = newNode;
		}
		else {
			curNode = node;
			while (curNode->next != NULL)
			curNode = curNode->next;
			curNode->next = newNode;
		}
}

	saveFlag = 0;
	fclose(file);
	printf("%s has been properly loaded into the database!\n\n", filename);
	showMenu(node);
	return 0;
}
void foodList(struct item *node)
{
  struct item *curNode = node;     // Final result after each option has performed an action

  printf("\nFood List\n");
  printf("=========\n");
  while( curNode != NULL )
  {
    // Loop through each line in the file and print the output to allow the user to see
    printf("%d %s %.2lf %c\n", curNode->id, curNode->name, curNode->cost, curNode->category);
    curNode = curNode->next;
  }
}

void addNewItem(struct item *node) {
	int id = 0;
	char name[20];
	double cost = 0;
	char category = ' ';
	struct item *newNode = NULL;
	struct item *curNode = NULL;

	newNode = (struct item*)malloc(sizeof(struct item));
	
	printf("\n\n--------- ADD NEW ITEM ---------\n");
	printf("\nWhat is the id of the item to add?:\n->");
	scanf("%d", &id);
	printf("What is the name of the item to be added?:\n->");
	scanf("%s", &name);
	printf("What is the cost of the item to be added?:\n->");
	scanf("%lf", &cost);
	printf("What is the product category of the item to be added?:\n->");
	scanf(" %c", &category);

	newNode->id = id;
	strcpy(newNode->name, name);
	newNode->cost = cost;
	newNode->category = category;
	newNode->next = NULL;

	if (node == NULL) {
		node = newNode;
	}
	else {
		if (node -> id == newNode -> id || !strcmp( node -> name, newNode -> name)) {
			printf("ERROR: Duplicate found!\n\n");				 
		}
		else {
			
			// Travel to the last node of the linked list
			curNode = node;
			while (curNode->next != NULL) {
				curNode = curNode->next;
			}
			
			// Add the new node to the end of the linked list
			curNode->next = newNode;
			saveFlag = 1;
			printf("%s has been added into the database.\n\n", name );
		}
	}
}

void delItem(struct item **node) {
	int id;
	struct item* curNode = *node;
	struct item *prevNode = NULL;
	 
	printf("\n\n--------- DELETE ITEM ---------\n");
	printf("\nPlease key in the ID number of the product to delete:\n->");
	scanf("%d", &id);
  
    // Iterate to delete's position-1 element
    if (curNode != NULL && curNode->id == id) 
    { 
        *node = curNode->next;  
        free(curNode);
		printf("Your chosen item has been deleted!\n\n");
		saveFlag = 1;                
        return; 
    } 
  
	// Search for the matching Id & keep track of previous node
    while (curNode != NULL && curNode->id != id) 
    { 
        prevNode = curNode; 
        curNode = curNode->next; 
    } 
  
    // Display message if no match found
    if (curNode == NULL) {
		printf("ERROR : Unable to delete item due to ID %d not found!\n\n", id);
		return;
	}
  
    // If match found, unlink the node from linked list 
    prevNode->next = curNode->next; 
    free (curNode);
	saveFlag = 1;
}

void updateItem(struct item *node) {
	int id = 0;
	int counter = 1;
	double cost = 0;
	struct item *curNode = node;
	int foundFlag = 0;  // To indicate whether the ID has been found
	
	printf("\n\n--------- CHANGE ITEM'S COST ---------\n");
	printf("\nKey in the ID to update the cost:\n->");
	scanf("%d", &id);

	printf("Key in the new cost for it:\n->");
	scanf("%lf", &cost);

	while (curNode != NULL) {
			if (curNode->id == id) {
				curNode->cost = cost;
				printf("The cost for item with ID %d is now %1f\n\n", id , cost);
				foundFlag = 1;   // set found flag to 1 when the ID is found
				saveFlag = 1;
				break; 
			}
			curNode = curNode->next;
		}
		
		// check found flag
		if (foundFlag == 0) {  
			printf("ERROR :Invalid ID\n\n");
		}	
}

void searchItem(struct item *node) {
	struct item *curNode = node;
	char name[20];
	int foundFlag = 0;  // To indicate whether the ID has been found
	
	printf("\n\n--------- SEARCH ITEM ---------\n");
	printf("\nWhich item to search?\n->");
	scanf("%s", name);

	while (curNode != NULL) {
		if (strcmp(curNode->name, name) == 0) {
			printf("ID\tNAME\t\tCOST\tCATEGORY\n");
			printf("==\t====\t\t====\t========\n");
			printf("%d\t%s\t\t%.2f\t%c\n\n", curNode->id, curNode->name, curNode->cost, curNode->category);
			foundFlag = 1;  // set found flag to 1 when the ID is found
		}
			curNode = curNode->next;
	}

		// Display if no match found
		if (foundFlag == 0) {  
				printf("Sorry, we do not have %s in the store.\n\n", name);
		}
}
void showInventory(struct item *node){
 	int sortOrder, sortKey;
 	struct item *curNode;
	printf("\n--------- INVENTORY DETAILS ---------\n\n");
	printf("1 - Sorted in ascending\n");
	printf("2 - Sorted in descending\n");
	printf("3 - Unsorted\n");
	printf("\nPlease select the sorting order\n-> ");
	scanf("%d", &sortOrder);
	// Perform sorting 
	if (sortOrder == 1 || sortOrder == 2){
		printf("\n--------- SORTING BASE ---------\n");
		printf("\n1 - Sort based on item ID\n");
		printf("2 - Sort based on item name\n");
		printf("3 - Sort based on item cost\n");
  		printf("4 - Sort based on item category\n");
  		printf("\nPlease select the sorting key\n-> ");
    	scanf("%d", &sortKey);
     		if (sortKey > 0 && sortKey < 5){
                    printf("\nID\t\tProduct\t\tPrice\t\tCategory\n");
                    curNode = sort(node, sortOrder, sortKey, &saveFlag);
                    if (curNode == NULL){
                        printf("\nWARNING: Inventory is empty!\n"); // Display message if it doesn't match
                   	 }
						else {
                        node = curNode;
                        showMenu(node); 
                    }
     			}
						else {
                    printf("\nERROR: No such sorting key!\n");  // Display message if it doesn't match
                }
            } 
				else if (sortOrder == 3){
                printf("\nID\t\tProduct\t\tPrice\tCategory\n");
                if (node == NULL){
                    printf("\nWARNING: Inventory is empty!\n");  // Display message if the inventory is empty
                } 
				else {
                    showMenu(node);
                }
        	    } 	
				else {
                printf("\nERROR: No such sorting order!\n");  // Display message if no sorting order found
    }	
}

struct item *sort(struct item *node, int sortOrder, int sortKey, int *saveFlag){
   switch (sortKey){
        case 1:
         sortID (node, sortOrder); 
         break;
        case 2:
         sortName(node, sortOrder); 
         break;
        case 3:
         sortCost(node, sortOrder); 
         break;
        case 4:
         sortCategory(node, sortOrder);
         break;
    }
    *saveFlag = 1;
    return node;
}

void sortID (struct item *node, int sortOrder){
    struct item *ptr1, *ptr2;
    int size = 1;
    int i = 0;
    ptr1 = node;
    ptr2 = node;

    while(ptr1->next != NULL){
      size = size + 1;
      ptr1 = ptr1->next;
    }
  
    int id[size];
    ptr1 = node;

    while(ptr1->next != NULL){
      id[i] = ptr1->id;
      i = i + 1;
      ptr1 = ptr1->next;

      if(ptr1->next == NULL){
        id[i] = ptr1->id;    
      }
    }

    if(sortOrder == 1){
    // To sort ID in ascending 
      for(int count=1; count<size; ++count){
        int hold;
        
        for(i=0; i<size-1; ++i){
          if(id[i] > id[i+1]){
            hold = id[i];
            id[i] = id[i+1];
            id[i+1] = hold;
          }
        }
      }
    }
    else if (sortOrder == 2){
	// To sort ID in descending
      for(int count=1; count<size; ++count){
        int hold;

        for(i=0; i<size-1; ++i){
          if(id[i] < id[i+1]){
            hold = id[i];
            id[i] = id[i+1];
            id[i+1] = hold;
          }
        }
      }
    } 
    else{
      printf("ERROR : Please select one of the Sort Orders!\n");  // Display message if no sort order found
    }

    // To print ID
    for(i=0; i < size; i++){
      ptr2 = node;
  
      while(ptr2->next != NULL){
        if(ptr2->id == id[i]){
          printf("%d\t\t%s\t\t%.2lf\t\t%c\n", ptr2->id, ptr2->name, ptr2->cost, ptr2->category);
        }
    
        ptr2 = ptr2->next;

        if(ptr2->next == NULL){
          if(ptr2->id == id[i]){
            printf("%d\t\t%s\t\t%.2lf\t\t%c\n", ptr2->id, ptr2->name, ptr2->cost, ptr2->category);
          }
        } 
      }
    }
}

void sortName(struct item *node, int sortOrder){
    struct item *ptr1, *ptr2;
    int size = 1;
    int i = 0;
    ptr1 = node;
    ptr2 = node;

    while(ptr1->next != NULL){

      size = size + 1;
      ptr1 = ptr1->next;
    }
  
    char name[size];
    ptr1 = node;

    while(ptr1->next != NULL){
      name[i] = ptr1->name[0];
      i = i + 1;
      ptr1 = ptr1->next;

      if(ptr1->next == NULL){
        name[i] = ptr1->name[0];    
      }
    }

    if(sortOrder == 1){
      // To sort name in ascending 
      for(int count = 1; count < size; ++count){
        char hold;

        for(i=0; i<size-1; ++i){
          if(name[i] > name[i+1]){
            hold = name[i];
            name[i] = name[i+1];
            name[i+1] = hold;
          }
        }
      }
    }
    else if (sortOrder == 2) {
      // To sort name in descending
      for(int count = 1; count < size; ++count){
        char hold;

        for(i=0; i<size-1; ++i){
          if(name[i] < name[i+1]){
            hold = name[i];
            name[i] = name[i+1];
            name[i+1] = hold;
          }
        }
      }
    }
    else{
      printf("ERROR : Please select one of the Sort Orders!\n");  // Display message if no sort order found
    }

    // To print name
    for(i=0; i < size; i++){
      ptr2 = node;
    
      while(ptr2->next != NULL){

        if(ptr2->name[0] == name[i]){
          printf("%d\t\t%s\t\t%.2lf\t\t%c\n", ptr2->id, ptr2->name, ptr2->cost, ptr2->category);
        }
    
        ptr2 = ptr2->next;

        if(ptr2->next == NULL){
            if(ptr2->name[0] == name[i]){
              printf("%d\t\t%s\t\t%.2lf\t\t%c\n", ptr2->id, ptr2->name, ptr2->cost, ptr2->category);
            }
        } 
      }
    }
}

void sortCost(struct item *node, int sortOrder){
    struct item *ptr1, *ptr2;
    int size = 1;
    int i = 0;
    ptr1 = node;
    ptr2 = node;

    while(ptr1->next != NULL){
      size = size + 1;
      ptr1 = ptr1->next;
    }
 
    double cost[size];
    ptr1 = node;

    while(ptr1->next != NULL){
      cost[i] = ptr1->cost;
      i = i + 1;
      ptr1 = ptr1->next;

      if(ptr1->next == NULL){
        cost[i] = ptr1->cost;    
      }
    }

    if(sortOrder == 1){
      // To sort cost in ascending 
      for(int count = 1; count < size; ++count){
        double hold;
        for(i=0; i<size-1; ++i){
          if(cost[i] > cost[i+1]){
            hold = cost[i];
            cost[i] = cost[i+1];
            cost[i+1] = hold;
          }
        }
      }
    }
    else if (sortOrder == 2){
      //  To sort cost in descending
      for(int count = 1; count < size; ++count){
        double hold;
        for(i=0; i < size - 1; ++i){
          if(cost[i] < cost[i+1]){
            hold = cost[i];
            cost[i] = cost[i+1];
            cost[i+1] = hold;
          }
        }
      }
    }
    else{
      printf("ERROR : Please select one of the Sort Order!\n");  // Display message if no sort order found
    }

    // To print cost
    for(i=0 ; i < size; i++){
      ptr2 = node;
    
      while(ptr2->next != NULL){
        if(ptr2->cost == cost[i]){
          printf("%d\t\t%s\t\t%.2lf\t\t%c\n", ptr2->id, ptr2->name, ptr2->cost, ptr2->category);
        }
    
        ptr2 = ptr2->next;

        if(ptr2->next == NULL){
          if(ptr2->cost == cost[i]){
            printf("%d\t\t%s\t\t%.2lf\t\t%c\n", ptr2->id, ptr2->name, ptr2->cost, ptr2->category);
          }
        } 
      }
    }
}

void sortCategory (struct item *node, int sortOrder){
    struct item *ptr1, *ptr2;
    int size = 1;
    int i = 0;
    ptr1 = node;
    ptr2 = node;

    while(ptr1->next != NULL){
      size = size + 1;
      ptr1 = ptr1->next;
    }
 
    char category[size];
    ptr1 = node;

    while(ptr1->next != NULL){
      category[i] = ptr1->category;
      i = i + 1;
      ptr1 = ptr1->next;

      if(ptr1->next == NULL){
      category[i] = ptr1->category;    
      }
    }

    if(sortOrder == 1){
      // To sort category in ascending 
      for(int count = 1; count < size; ++count){
        char hold;
        for(i=0; i < size - 1; ++i){
         if(category[i] > category[i+1]){
          hold = category[i];
          category[i] = category[i+1];
          category[i+1] = hold;
         }      
        }
       }
    }
    else if (sortOrder == 2)  {
      // To sort category in descending
      for(int count = 1; count < size; ++count){
        char hold;

        for(i=0; i<size-1; ++i){
          if(category[i] < category[i+1]){
            hold = category[i];
            category[i] = category[i+1];
            category[i+1] = hold;
          }
        }
      }  
    }
    else{
      printf("ERROR : Please select one of the Sort Orders!\n");  // Display message if no sort orders found
    }

    // To print category
    for(i=0; i<size; i++){
      ptr2 = node;   

      while(ptr2->next != NULL){
        if(ptr2->category == category[i]){
          printf("%d\t\t%s\t\t%.2lf\t\t\t%c\n", ptr2->id, ptr2->name, ptr2->cost, ptr2->category);
        }
    
        ptr2 = ptr2->next;

        if(ptr2->next == NULL){
          if(ptr2->category == category[i]){
            printf("%d\t\t%s\t\t%.2lf\t\t\t%c\n", ptr2->id, ptr2->name, ptr2->cost, ptr2->category);
          }
        } 
      }
   }
}


void save(struct item *node, char filename[]) {
	struct item *curNode = node;
	FILE *filePtr;
	char newfile[15];
		
		// If saveFlag = 1, prompt to save linked list to file
		if (saveFlag == 1) { 
		char option;
		printf("\n\n--------- QUIT ---------\n\n");
		printf("Do you want to save the changes made? (Yes[Y] or No [N])\n");
		scanf("%s", &option);
		if (option == 'Y'){	
			while(1){
			printf("Enter new file name to load the contents into (eg. newfood.txt):\n->");
			scanf("%s", newfile);
     
		 // Check if new file has the same name as the original
		 	if (strcmp(newfile, filename) == 0){
			printf("ERROR : Duplicate File Name detected!\n\n");  // Display message if duplicate file found
		 }
		 else {  
			 if ((filePtr = fopen(newfile, "w")) == NULL){
			  perror("Error\n");
			 }
			 else {
				break;
			 }
		 } 
	}

	   // Write into new file with the new changes
	   while (curNode != NULL){
		fprintf(filePtr, "%d\t%s\t%.2lf\t%c\n", curNode->id, curNode->name, curNode->cost, curNode->category);   // <===== tab separated
		curNode = curNode->next;
	   }
	   fclose(filePtr);
	   printf("\nFile is successfully saved, thanks for shopping and come again next time!!\n\n");
   }
   		else if( option == 'N' ) {
		   printf("Thank you. Your database has not been updated!\n");	
	}
		else{
			printf("ERROR : Invalid choice!"); // Display message if it doesnt match the choice
		}
		}
}

void showMenu(struct item *node) {
	int choice;
	foodList(node);
	printf("\nPlease make one of the following selections:\n");
	printf("============================================\n");
	printf("[1] Add new item\n");
	printf("[2] Delete item\n");
	printf("[3] Change the cost of an item\n");
	printf("[4] Search for item\n");
	printf("[5] Display inventory details\n");
	printf("[6] Quit\n");
	printf("Please key in option:\n->");
	scanf("%d", &choice);
	
	
	if (choice == 1) {
		addNewItem(node);
	}
	else if (choice == 2) {
		delItem(&node);
	}
	else if (choice == 3) {
		updateItem(node);
	}
	else if (choice == 4) {
		searchItem(node);
	}
	else if (choice == 5) {
		showInventory(node);
	}
	else if (choice == 6) {
		save(node, fn);  
		exit(0);
	}
	else {
		printf("Invalid option! Please try again\n");
	}
	showMenu(node);
}