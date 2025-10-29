#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct ProductDetails
{
    int id;
    char name[20];
    float price;
    int quantity;
};

bool isDuplicateID(struct ProductDetails *productDetail, int numberOfProducts, int id)
{
    for(int idx=0; idx<numberOfProducts; idx++)
    {
        if(productDetail[idx].id == id)
        {
            return true;
        }
    }
    return false;
}

void input_details(struct ProductDetails *productDetail, int numberOfProducts)
{
    for (int product = 0; product < numberOfProducts; product++)
    {
        printf("Enter details for product %d:\n", product + 1);

        int productID;

        while(1)
        {
            printf("Enter Product id: ");
            if(scanf("%d", &productID) != 1 || productID < 0)
            {
                while(getchar() != '\n');
                printf("---- Please Enter a valid product id ----\n");
                continue;
            }

            if(isDuplicateID(productDetail, product, productID))
            {
                printf("---- Please enter a unique id ----\n");
                continue;
            }
            while(getchar() != '\n');
            break;
        }
        productDetail[product].id = productID;
        

        printf("Product Name: ");
        scanf("%s", productDetail[product].name);

        float productPrice;

        while(1)
        {
            printf("Product Price: ");
            if(scanf("%f", &productPrice) != 1 || productPrice < 0)
            {
                while(getchar() != '\n');
                printf("---- Please enter a valid product price ----\n");
                continue;
            } 
            break;
        }
        productDetail[product].price = productPrice;    


        int productQuantity;

        while(1)
        {
            printf("Product Quantity: ");
            if(scanf("%d", &productQuantity) != 1 || productQuantity < 0)
            {
                while(getchar() != '\n');
                printf("---- Please enter a valid quantity ----\n");
                continue;
            }
            while(getchar() != '\n');
            break;
        }
        productDetail[product].quantity = productQuantity;
    }
}

void add_new_product(struct ProductDetails **productDetail, int *numberOfProducts)
{

    int newID;

    while(1)
        {
            printf("Enter Product id: ");
            if(scanf("%d", &newID) != 1 || newID < 0)
            {
                while(getchar() != '\n');
                printf("---- Please Enter a valid product id ----\n");
                continue;
            }

            if(isDuplicateID(*productDetail, *numberOfProducts, newID))
            {
                printf("---- Please enter a unique id ----\n");
                continue;
            }
            while(getchar() != '\n');
            break;
        }


     (*numberOfProducts)++;
    *productDetail = (struct ProductDetails *)realloc(*productDetail, (*numberOfProducts) * sizeof(struct ProductDetails));

    if (*productDetail == NULL)
    {
        printf("Memeory reallocation failed");
        return;
    }

    printf("Enter new Product Details: \n");
    (*productDetail)[(*numberOfProducts) - 1].id = newID;
    printf("Product Name: ");
    scanf("%s", (*productDetail)[(*numberOfProducts) - 1].name);

    float productPrice;

        while(1)
        {
            printf("Product Price: ");
            if(scanf("%f", &productPrice) != 1 || productPrice < 0)
            {
                while(getchar() != '\n');
                printf("---- Please enter a valid product price ----\n");
                continue;
            } 
            while(getchar() != '\n');
            break;
        }
        (*productDetail)[(*numberOfProducts) - 1].price = productPrice;
        int productQuantity;

        while(1)
        {
            printf("Product Quantity: ");
            if(scanf("%d", &productQuantity) != 1 || productQuantity < 0)
            {
                while(getchar() != '\n');
                printf("---- Please enter a valid quantity ----\n");
                continue;
            }
            while(getchar() != '\n');
            break;
        }
    (*productDetail)[(*numberOfProducts) - 1].quantity = productQuantity;
    printf("Product added successfully!");

    printf("\n");
}

void view_products(struct ProductDetails *productDetail, int numberOfProducts)
{
    for (int product = 0; product < numberOfProducts; product++)
    {
        printf("Product ID: %d | Name: %s | Price: %.2f | Quantity: %d", productDetail[product].id, productDetail[product].name, productDetail[product].price, productDetail[product].quantity);
        printf("\n");
    }
    printf("\n");
}

void update_quantity(struct ProductDetails *productDetail, int numberOfProducts)
{
    int productID;
    printf("Enter Product ID to update quantity: ");
    scanf("%d", &productID);

    int productQuantity;

        while(1)
        {
            printf("Product Quantity: ");
            if(scanf("%d", &productQuantity) != 1 || productQuantity < 0)
            {
                while(getchar() != '\n');
                printf("---- Please enter a valid quantity ----\n");
                continue;
            }
            while(getchar() != '\n');
            break;
        }

    int found = 0;

    for (int product = 0; product < numberOfProducts; product++)
    {
        if (productDetail[product].id == productID)
        {
            productDetail[product].quantity = productQuantity;
            found = 1;
        }
    }
    if (found)
    {
        printf("---- Quantity updated successfully! ----\n");
    }
    else
    {
        printf("ID not found\n");
    }
    printf("\n");
}

void search_by_id(struct ProductDetails *productDetail, int numberOfProducts)
{
    int searchId;

    while(1)
    {
        printf("Enter Product ID to search: ");
        if(scanf("%d", &searchId) != 1 || searchId < 0)
        {
            while(getchar() != '\n');
            printf("---- Please enter valid ID ----\n");
            continue;
        }
        while(getchar() != '\n');
        break;

    }


    int found = 0;
    for (int product = 0; product < numberOfProducts; product++)
    {
        if (productDetail[product].id == searchId)
        {
            printf("Product Found : Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n", productDetail[product].id, productDetail[product].name, productDetail[product].price, productDetail[product].quantity);
            found = 1;
        }
    }
    if (!found)
    {
        printf("ID not found!\n");
    }
    printf("\n");
}

void search_by_name(struct ProductDetails *productDetail, int numberOfProducts)
{
    char productName[20];
    printf("Enter name to search (partial allowed): ");
    scanf("%s", productName);

    int found = 0;
    for (int product = 0; product < numberOfProducts; product++)
    {
        if (strstr(productDetail[product].name, productName) != NULL)
        {
            printf("Product Found : Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n", productDetail[product].id, productDetail[product].name, productDetail[product].price, productDetail[product].quantity);
            found = 1;
        }
    }
    if (!found)
    {
        printf("No products found matching '%s'\n", productName);
    }
    printf("\n");
}

void search_by_price(struct ProductDetails *productDetail, int numberOfProducts)
{
    int minimumPrice, maximumPrice;
    while(1)
    {
        printf("Enter minimum price: ");
        if(scanf("%d", &minimumPrice) != 1 || minimumPrice < 0)
        {
            while(getchar() != '\n');
            printf("---- Please enter valid price ----\n");
            continue;
        }
        while(getchar() != '\n');
        break;
    }

    while(1)
    {
        printf("Enter maximum price: ");
        if(scanf("%d", &maximumPrice) != 1 || maximumPrice < 0)
        {
            while(getchar() != '\n');
            printf("---- Please enter valid price ----\n");
            continue;
        }
        while(getchar() != '\n');
        break;
    }
    
    int found = 0;
    for (int product = 0; product < numberOfProducts; product++)
    {
        if (productDetail[product].price >= minimumPrice && productDetail[product].price <= maximumPrice)
        {
            printf("Product Found : Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n", productDetail[product].id, productDetail[product].name, productDetail[product].price, productDetail[product].quantity);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No Product Found with price between %d and %d!\n", minimumPrice, maximumPrice);
    }
}

void delete_by_id(struct ProductDetails **productDetail, int *numberOfProducts)
{
    int deleteId;
    while(1)
    {
        printf("Enter product id to delete: ");
        if(scanf("%d", &deleteId) != 1 || deleteId < 0)
        {
            while(getchar() != '\n');
            printf("---- Please enter a valid id ----\n");
            continue;
        }
        while(getchar() != '\n');
        break;
    }
   

    int found = 0;

    for (int product = 0; product < (*numberOfProducts); product++)
    {
        if ((*productDetail)[product].id == deleteId)
        {
            found = 1;

            for (int j = product; j < (*numberOfProducts) - 1; j++)
            {
                (*productDetail)[j] = (*productDetail)[j + 1];
            }

            (*numberOfProducts)--;

            (*productDetail) = (struct ProductDetails *)realloc((*productDetail), (*numberOfProducts) * sizeof(struct ProductDetails));

            if ((*productDetail) == NULL && *numberOfProducts > 0)
            {
                printf("Reallocation failed");
                return;
            }

            printf("Product Deleted successfully\n");
            break;
        }
    }

    if (!found)
    {
        printf("Product not found\n");
    }
}

void exit_program(struct ProductDetails *productDetail)
{
    free(productDetail);
    productDetail = NULL;

    printf("Memory released successfully. Exiting program...");
}
int main()
{
    int numberOfProducts = 0;
    printf("Enter initial number of products: ");
    scanf("%d", &numberOfProducts);

    if(numberOfProducts <= 0)
    {
        printf("Please enter a valid number");
        return 1;
    }

    struct ProductDetails *productDetail = (struct ProductDetails *)calloc(numberOfProducts, sizeof(struct ProductDetails));

    if (productDetail == NULL)
    {
        printf("Memory allocation failed");
        return 1;
    }

    // Getting Input about product deatils
    input_details(productDetail, numberOfProducts);

    printf("\n");

    int choice;

    do
    {
        printf("\n-------INVENTORY MENU-------\n");
        printf("1. Add New Product\n");
        printf("2. View All Products\n");
        printf("3. Update Quantity\n");
        printf("4. Search Product by ID\n");
        printf("5. Search Product by Name\n");
        printf("6. Search Product by Price Range\n");
        printf("7. Delete Product\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        if (choice == 1)
        {
            add_new_product(&productDetail, &numberOfProducts);   // Add New Product
        }

        else if (choice == 2)
        {
            view_products(productDetail, numberOfProducts);      // View All Products
        }
        else if (choice == 3)
        {
            update_quantity(productDetail, numberOfProducts);    // Update Quantity
        }
        else if (choice == 4)
        {
            search_by_id(productDetail, numberOfProducts);       // Search Product by ID
        }
        else if (choice == 5)
        {
            search_by_name(productDetail, numberOfProducts);     // Search Product by Name
        }
        else if (choice == 6)
        {
            search_by_price(productDetail, numberOfProducts);    // Search Product by Price
        }
        else if (choice == 7)
        {
            delete_by_id(&productDetail, &numberOfProducts);     // Delete Product
        }
        else if (choice == 8)
        {
            exit_program(productDetail);                         // Exit Program
        }

        printf("\n");

    } while (choice != 8);
}