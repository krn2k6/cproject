#include<stdio.h>

//Books
#define maxBooks 100
struct Books{
    int id;
    char title[50];
    char author[50];
    char category[50];
    int copies;
    float price;
};
struct Books book[maxBooks]; 
int bookCount = 0;

void addBooks(){
    int n;
    printf("How many books do you want to add? ");
    scanf("%d", &n);
    printf("==============================\n");
    for(int i=bookCount; i<bookCount+n; i++){
        printf("Book %d ID: ", i+1);
        scanf("%d", &book[i].id);
        printf("Book %d Title: ", i+1);
        scanf("%s", book[i].title);
        // fgets(book[i].title, sizeof(book[i].title), stdin);
        printf("Book %d Author: ", i+1);
        scanf("%s", book[i].author);
        // fgets(book[i].author, sizeof(book[i].author), stdin);
        printf("Book %d Category: ", i+1);
        scanf("%s", book[i].category);
        // fgets(book[i].category, sizeof(book[i].category), stdin);
        printf("How many copies of Book %d: ", i+1);
        scanf("%d", &book[i].copies);
        printf("Book %d Price: ", i+1);
        scanf("%f", &book[i].price);
        printf("\n\n");
    }
    printf("==============================\n\n");
    bookCount += n;

}

void updateBooks(){
    printf("Book ID of the book to update: \n");
    int id;
    scanf("%d", &id);

    for(int i=0; i<bookCount; i++){
        if(book[i].id == id){

            printf("Book ID: ");
            scanf("%d", &book[i].id);
            printf("Book Title: ");
            scanf("%s", book[i].title);
            printf("Book Author: ");
            scanf("%s", book[i].author);
        printf("Book Category: ");
        scanf("%s", book[i].category);
        printf("How many copies of Book: ");
        scanf("%d", &book[i].copies);
        printf("Book Price: ");
        scanf("%f", &book[i].price);
        printf("\n\n");
    }
    }
}

void removeBooks(){
    printf("Book ID of the book to delete: ");
    int id;
    scanf("%d", &id);

    int find = 0;
    for(int i=0; i<bookCount; i++){
        if(id == book[i].id){
            find = i;
            break;
        }
    }
    if(find == 0){
        printf("Book ni mili\n");
        return;
    }

    for(int i=find; i<bookCount-1; i++){
        book[i] = book[i+1];
    }
    bookCount--;

    printf("done\n");
}

int menuBooksforCustomers(){
    printf("2. Display Books\n");
    printf("5. Exit\n");

    int choice;
    scanf("%d", &choice);
    
    if(choice == 2){
        displayBooks();
    }
    else if(choice == 5){
        return 0;
    }
 return 1;   
}

// int ENUM menuBooksm(){

// }

enum goodMenu{
    Add_Books = 1,
    Display_Books,
    Update_Books,
    Remove_Books,
    Exit_program,
};

int menuBooks(){
    printf("1. Add Books\n");
    printf("2. Display Books\n");
    printf("3. Update Books\n");
    printf("4. Remove Books\n");
    printf("5. Exit\n");

    int choice;
    scanf("%d", &choice);
    
    if(choice == Add_Books){
        addBooks();
    }
    else if(choice == Display_Books){
        displayBooks();
    }
    else if(choice == Update_Books){
        updateBooks();
    }
    else if(choice == Remove_Books){
        removeBooks();
    }
    else if(choice == Exit_program){
        return 0;
    }
 return 1;   
}

void displayBooks(){

    printf("All books in the library\n");
    printf("========================================\n");
    for(int i=0; i<bookCount; i++){
        printf("Book Id: %d\n", book[i].id);
        printf("Book Title: %s\n", book[i].title);
        printf("Book Author: %s\n", book[i].author);
        printf("Book Category: %s\n", book[i].category);
        printf("Number of Copies: %d\n", book[i].copies);
        printf("Book Price: %.2f\n", book[i].price);
        printf("========================================\n\n");

        printf("\n");
    }
}

//Employees
struct Employees{
    int id;
    char name[50];
    float salary;
};

int main()
{
    int choice;
    printf("\nWelcome to the Library Management System\n");
    // printf("Are you employee or a customer: ");
    // scanf("%d", &choice);


    int flag1 = 1;
    while (flag1)
    {
        printf("\nFor Employee --> (1)\nFor Customer --> (2)\nOR just want to exit enter anything: \n\n");
    scanf("%d", &choice);
        
        if(choice == 1){
            printf("Employee LOGIN!!!\n");
            int flag = 1;
            while(flag){
                flag = menuBooks();     
                
            }
        }
        else if(choice == 2){
        printf("Customer LOGIN!!!\n");
        int flag = 1;
        while(flag){
            flag = menuBooksforCustomers();
        }

        
    }
    else if(choice == 3){
        flag1 = 0;
    }
}
    return 0;
}