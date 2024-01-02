#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <limits>
using namespace std;

const int ALLOWED_ATTEMPTS = 3;

class Product 
{
/// @Product information
private:

    string productID;
    string productName;
    int productQuantaty;
    float productPrice;

public:

    Product(string productID, string productName, int productQuantaty, float productPrice)
    {
        this->productID = productID;
        this->productName = productName;
        this->productQuantaty = productQuantaty;
        this->productPrice = productPrice;
    }

    void setID(long productId)
    {
        this->productID = productId;
    }

    string getID() 
    {
        return this->productID;
    }

    void setName(string productN)
    {
	    this->productName = productN;
    }

    string getName()
    {
	    return this->productName;
    }

    void setQuantaty(int productQ)
    {
        this->productQuantaty = productQ;
    }

    int getQuantaty() 
    {
        return this->productQuantaty;
    }

    void setPrice(float productP)
    {   
        this->productPrice = productP;
    }

    float getPrice()
    {
        return this->productPrice;        
    }
};

class Menu 
{
    const string menu =
            "\n"
            "------------------------------------------------ \n"
            "-----------Ivenotory Managment System----------- \n"
            "-----------------Welcome------------------------ \n"
            "Please choose an option \n"
            "1. Add product. \n"
            "2. Remove product. \n"
            "3. Update product. \n"
            "4. Find product. \n"
            "5. View all products. \n"
            "Q. Quit. \n";

    char menuOption;

public:

    void printMenu()
    {
        cout << menu << endl;
    }

    const char  getOption()
    {
        cout << "Your option: ";
        cin >> menuOption;
        cout << endl;
        return menuOption;
    }

};

class Inventorty
{
    vector<Product> products;

public:

    void addProduct(Product product)
    {
        bool present = false;
        for (auto& prod : products)
        {
            if (prod.getID() == product.getID())
            {
                cout << "The product: " << product.getID() << " with name: " 
                << product.getName() << " already exists!" << endl;
                present = true;
                break;
            }
        }

        if (!present)
        {
            products.push_back(product);
            cout << "Product was added succesfully..." << endl;
        }
    } // addProduct

    void removeProduct(string id)
    {
        bool present = false;
        for (auto i = products.begin(); i != products.end(); ++i)
        {
            if (i->getID() == id)
            {
                products.erase(i);
                present = true;
                cout << "Product is removed..." << endl;
                break;
            }
        }

        if (!present)
        {
            cout << "Item doesn't exist...";
        }
    } // removeProduct

    void findProduct(string prodName)
    {
        bool present = false;
        regex prodS(prodName);
        for (auto& product : products)
        {
            if (regex_match(product.getName(), prodS))
            {
                cout << "Product name: " << product.getName() << endl;
                cout << "Product ID: " << product.getID() << endl;
                cout << "Product price: " << product.getPrice() << endl;
                cout << "Product quantaty: " << product.getQuantaty() << endl;
                present = true;
                break;
            }

        }

        if (!present)
        {
            cout << "Product was not found!...";
        } 

    }

    void listAll()
    {
        bool present = false;
        int count = 1;
        for (auto i = products.begin(); i != products.end(); ++i)
        {
            cout << "Product Number " << count << endl;
            cout << "Product name: " << i->getName() << endl;
            cout << "Product ID: " << i->getID() << endl;
            cout << "Product price: " << i->getPrice() << endl;
            cout << "Product quantaty: " << i->getQuantaty() << endl;
            cout << endl;
            ++count;
            present = true; 
        }

        if (!present)
        {
            cout << "No products were found...";
        }
    }

};


template <typename T>
T getInputNum() {
  string input;
  T number;
  regex intPattern("^(0|[1-9][0-9]*)$");
  regex floatPattern("^(0|[1-9][0-9]*\\.?[0-9]*)$");
  for (int i = 0; i != ALLOWED_ATTEMPTS; ++i) //three attemps allowed
  {
    std::cin >> input;
    if (regex_match(input, intPattern))
    {
      number = stoi(input);
      break;
    }
    else if (regex_match(input, floatPattern))
    {
      number = stof(input);
      break;
    }
    else 
    { 
      cout << "\nWrong input, please insert again: ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  return number;
}

int main()
{
    
    Menu menu;
    Inventorty inventory;
    
    bool running = true;
    do
    {
    menu.printMenu();
    
    switch (menu.getOption())
    {
        case '1':
        {   
            string productID;
            string productName;
            int productQuantaty;
            float productPrice;
            
            cout << "Plase insert product information..." << endl;
            cout << "Product ID: ";
            cin >> productID;
            cin.ignore();
            cout << "Product name: ";
            getline(std::cin, productName);
            cout << "Product quantaty: ";
            productQuantaty = getInputNum<int>(); 
            cout << "Prooduct price: ";
            productPrice = getInputNum<float>();

            Product product(productID, productName, productQuantaty, productPrice);
            inventory.addProduct(product);

            break;
        }
        case '2':
        {
            string id;
            cout << "Insert ID number to erase product: ";
            cin >> id;
            inventory.removeProduct(id);
            break;
        }
        case '3':
        {
            cout << "In development...";
            break;
        }
        case '4':
        {
            string name;
            cout << "Search option supports regex." << endl;
            cout << "Please insert product name to search: ";
            cin.ignore();
            getline(cin, name);
            inventory.findProduct(name);
            break;
        }
        case '5':
        {   
            inventory.listAll();
            break;
        }
        case 'q':
        case 'Q':
        {
            cout << "End of programe..." << endl;
            running = false;
            break;
        }
        default:
            cout << "Not a valid choice..." << endl;


    } // switch menu
} while (running);
    return 0;
}

