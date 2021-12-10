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

#include "knapsack.hpp"

Element::Element(int id, int p) : weight(p), id_element(id) { }

int Element::getWeight()
{
    return weight;
}

int Element::getId()
{
    return id_element;
}

bool Element::is_contained(Item* I){
    return items.find(I)!=items.end();
}
Item::Item(int id_item, int profit) : 
        id_item(id_item), profit(profit), element_weight(0)
{


}

int Item::getProfit()
{
    return profit;
}

int Item::getId()
{
    return id_item;
}

int Item::getElementWeight()
{
    return element_weight;
}


bool Item::contains(Element* h)
{
    return elements.find(h)!=elements.end();
}

void Item::add_element(Element* el){
    element_weight+=el->getWeight();
    elements.insert(el);

}


Knapsack::Knapsack(int c, list<Item>& items): capacity(c), total_weight(0), total_profit(0)
{
    for(Item& item:items)
        unselected_items[&item] = item.getElementWeight();
    
}

int Knapsack::getCapacity()
{
    return capacity;
}

int Knapsack::getTotalWeight()
{
    return total_weight;
}

int Knapsack::getTotalProfit()
{
    return total_profit;
}


void Knapsack::addElement(Element* el){
    if(!contains_element(el)){
        elements.insert(el);
        total_weight+=el->getWeight();

        //se actualiza beneficio de la mochila
        //y pesos restantes de los items no seleccionados
        for(auto item:el->items){
            unselected_items[item]-=el->getWeight();
            if (unselected_items[item]==0){
               total_profit += item->getProfit();  
               unselected_items.erase(item);
               items.insert(item);
            }
        }
    }
}

void Knapsack::removeElement(Element* el){
    if(contains_element(el)){
        elements.erase(el);
        total_weight-=el->getWeight();

        //se actualiza beneficio de la mochila
        //y pesos restantes de los items no seleccionados
        for(auto item:el->items){
            if(unselected_items.find(item)==unselected_items.end()){
                unselected_items[item] = el->getWeight();
                total_profit -= item->getProfit();
                //eliminarItem(item); //lo agregué yo  
            }else unselected_items[item] += el->getWeight();
        }
    }
}

bool Knapsack::addItem(Item* item)
{
        
    if(contains_item(item)) return false;
    if(unselected_items[item] > capacity-total_weight) return false;
    
    //se agregan los elementos que no están en la mochila
    for(auto el:item->elements)
        addElement(el);

    return true;
}

bool Knapsack::contains_item(Item* i){
    return (items.find(i)!=items.end());
}

bool Knapsack::contains_element(Element* h){
    return (elements.find(h)!=elements.end());
}
void Knapsack::removeParentlessElement()
{
    int cont_p=0;
    list<Element*> to_remove;
    for (auto elem: elements)
    {
        cont_p = 0;
        for (auto item: items)
        {
            if (item->contains(elem))
                cont_p++;
        }
        if (cont_p == 0)
            to_remove.push_back(elem);
        
    }
    
    for (auto elem: to_remove)
    {
        removeElement(elem);
    }
    
}
void Knapsack::removeItem(Item* i)
{
    total_profit -= i->getProfit();
    items.erase(i);
    unselected_items[i] = i->getElementWeight();
    removeParentlessElement();
}