#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<cstdlib>
#include<list>
#include<fstream>
#include<iterator>
#include<map>
#include<set>
#include<queue>
#include<vector>
//#include<time.h>
#include<math.h>
#include<unordered_set>
#include <string> 
#include <experimental/algorithm>
#include <random>
using namespace std;


class Item;
class Element;
class Knapsack;

class Element{ // clase para cada elemento
    private:
        int weight; // variable que guardará el peso del elemento
        int id_element;
        
  public:
        Element(int id, int p);
        int getWeight();
        int getId();
        bool is_contained(Item* I); //return true if the elemet is in I
        std::unordered_set <Item*> items; //items que contienen el elemento
};


class Item{
    private:
        int profit;
        int id_item;
        int element_weight =0;

    public:
        Item(int id_item, int profit);
        int getProfit();
        int getId();
        int getElementWeight();
        float getRatio();
        void add_element(Element* el);
        bool contains(Element* h);
        
        std::unordered_set<Element*> elements;
};




//usar unsorted_set 
// multimap para los no seleccionados
class Knapsack{
    private:
        int capacity;
        int total_weight =0;
        int total_profit=0;

    public:
        Knapsack(int c, list<Item>& items);
        int getCapacity();
        int getTotalWeight();
        int getTotalProfit();
        bool addItem(Item* i);
        void removeItem(Item* i);
        void addElement(Element* e);
        void removeElement(Element* e);
        void removeParentlessElement();

        bool contains_item(Item* i);
        bool contains_element(Element* h);

        std::unordered_set<Item*> items;
        std::unordered_set<Element*> elements;
        map<Item*, int> unselected_items; 
        // para cada item, guarda el peso faltante para completar dicho item
};


