#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Product {
private:
    string name;
    double price;
    int id;

public:
    Product(const string& productName, double productPrice, int productId)
        : name(productName), price(productPrice), id(productId) {}

    const string& getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getId() const {
        return id;
    }

    bool setPrice(double newPrice) {
        if (newPrice <= 0) {
            return false;
        }

        price = newPrice;
        return true;
    }

    void print() const {
        cout << name << " price: " << price << ", id: " << id << '\n';
    }
};

class Store {
private:
    vector<Product> products;

public:
    bool addProduct(const Product& newProduct) {
        for (const auto& product : products) {
            if (product.getId() == newProduct.getId()) {
                return false; // IDs must be unique in this store.
            }
        }

        products.push_back(newProduct);
        return true;
    }

    void printAll() const {
        if (products.empty()) {
            cout << "The store has no products.\n";
            return;
        }

        for (const auto& product : products) {
            product.print();
        }
    }

    bool findByName(const string& nameToFind) const {
        for (const auto& product : products) {
            if (product.getName() == nameToFind) {
                product.print();
                return true;
            }
        }

        return false;
    }

    bool setNewPrice(int productId, double newPrice) {
        for (auto& product : products) {
            if (product.getId() == productId) {
                return product.setPrice(newPrice);
            }
        }

        return false;
    }

    bool removeById(int idToRemove) {
        for (size_t i = 0; i < products.size(); i++) {
            if (products[i].getId() == idToRemove) {
                products.erase(products.begin() + i);
                return true;
            }
        }

        return false;
    }
};

int main() {
    Store store;

    store.addProduct({"Apple", 0.70, 0});
    store.addProduct({"Banana", 0.45, 1});
    store.addProduct({"Cucumber", 1.20, 2});
    store.addProduct({"Durian", 3.40, 3});

    cout << "All products:\n";
    store.printAll();

    if (store.setNewPrice(0, 2.99)) {
        cout << "\nApple's price was changed:\n";
    } else {
        cout << "\nCould not change the price. Check the ID and price.\n";
    }
    store.printAll();

    if (store.findByName("Banana")) {
        cout << "That product was found.\n";
    } else {
        cout << "That product was not found.\n";
    }

    if (store.removeById(0)) {
        cout << "\nApple was removed. Products left:\n";
    } else {
        cout << "\nCould not remove a product with that ID.\n";
    }
    store.printAll();

    return 0;
}
