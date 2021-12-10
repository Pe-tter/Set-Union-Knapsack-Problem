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
#include<math.h>
#include<unordered_set>
#include <string> 
#include <experimental/algorithm>
#include "knapsack.hpp"

using namespace std;


int loadData(list<Element>& ,list<Item>&,int); // función que cargará los datos del dataset en la lista
void random_greedy(Knapsack& kn, list<Item>& items,int n);
void simulated_annealing(Knapsack& init_kn,int max_iterations,float t_max, float t_min);
bool knapsack_swap(Knapsack& init_kn,vector<int>& mov);
void moves(int num_mov, vector<int>& mov);

int main(int argc, char *argv[])
{
    // Parámetros
/*    
    int seed = atoi(argv[1]);
    int n_greedy = atoi(argv[2]);
    int instance= atoi(argv[3]);
    float t_max = stof(argv[4]);
    float t_min = stof(argv[5]); // no ser 0, no int
    int max_iterations = atoi(argv[6]);
*/
    int seed = 10001;
    int n_greedy = 100;
    int instance= 1;
    float t_max= 100;
    float t_min= 5;
    int max_iterations = 10000;


    int no_improvements = 100;
 
    srand(seed);
    list<Item> total_items;
    list<Element> total_elements;
    int capacity;
    capacity = loadData(total_elements,total_items,instance); 

    Knapsack init_kn(capacity, total_items);
    
    random_greedy(init_kn,total_items,n_greedy);
    cout << "Beneficio inicial: " << init_kn.getTotalProfit() << " con peso:" << init_kn.getTotalWeight() << endl;

    simulated_annealing(init_kn,max_iterations,t_max,t_min);
    cout << endl;
    cout << "Beneficio final: " << init_kn.getTotalProfit() << " con peso:" << init_kn.getTotalWeight() << endl;
  
}

int loadData(list<Element>& total_elements, list<Item>& total_items,int instance) {
    ifstream file; // variable que recibirá los datos desde el archivo
    string text; // variable que se usrá para ir leyendo la variable archivo
    int i=0,j=0,a=0,m,n,capac,number, cont = 0; // variables de lectura
    
    switch (instance)
    {
    // m = n
    case 1:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m equal n)/sukp 100_100_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 2:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m equal n)/sukp 100_100_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 3:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m equal n)/sukp 200_200_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 4:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m equal n)/sukp 200_200_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 5:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m equal n)/sukp 300_300_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 6:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m equal n)/sukp 300_300_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 7:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m equal n)/sukp 400_400_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 8:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m equal n)/sukp 400_400_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 9:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m equal n)/sukp 500_500_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 10:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m equal n)/sukp 500_500_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    // m > n
    case 11:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m greater than n)/sukp 100_85_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 12:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m greater than n)/sukp 100_85_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 13:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m greater than n)/sukp 200_185_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 14:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m greater than n)/sukp 200_185_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 15:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m greater than n)/sukp 300_285_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 16:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m greater than n)/sukp 300_285_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 17:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m greater than n)/sukp 400_385_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 18:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m greater than n)/sukp 400_385_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 19:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m greater than n)/sukp 500_485_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 20:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m greater than n)/sukp 500_485_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
        // m < n
    case 21:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m less than n)/sukp 85_100_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 22:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m less than n)/sukp 85_100_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 23:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m less than n)/sukp 185_200_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 24:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m less than n)/sukp 185_200_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 25:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m less than n)/sukp 285_300_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 26:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m less than n)/sukp 285_300_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 27:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m less than n)/sukp 385_400_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 28:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m less than n)/sukp 385_400_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 29:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m less than n)/sukp 485_500_0.10_0.75.txt",ios::in); // se abre el archivo en modo lectura
        break;
    case 30:
        file.open("../Three kinds of SUKP instances (EAs)/SUKP Instances (m less than n)/sukp 485_500_0.15_0.85.txt",ios::in); // se abre el archivo en modo lectura
        break;
    default:
        break;
    }
    
    
    if(file.fail()){ // en caso de que no se pueda abrir el archivo se mostrará una linea de texto por pantalla 
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    file >> number;
    m = number;
  
    file >> number;
    n= number;
  
    file >> number;
    capac= number;
  
    while(file >> number){
            cont++;
            Item item(cont, number);

            total_items.push_back(item);
            a++;
            if(a == m){
                break;
            }
    }
    a=0;
    int id=1;
    while(file >> number){
        Element el(id, number);
        total_elements.push_back(el);
            cont++;
            a++;
            id++;
            if(a == n){
                break;
            }
    }
    
    int relations[m][n];// matriz que guardará las relaciones de los elementos consus respectivos items
    i=0;
    j=0;
            while (file >> number)
            {
                if(j == n){
                    i++;
                    j=0;
                }
                relations[i][j]= number;
                j++;
            }
      

    
    float ratio;
    list<Element>::iterator el;
    el = total_elements.begin();
    list<Item>::iterator it;
    it = total_items.begin();
    for ( i = 0; i < m; i++)
    {
        for ( j = 0; j < n; j++)
        {
            if (relations[i][j] != 0)
            {
                Element* aux = &(*el);
                Item* auxI = &(*it);
                it->add_element(aux);
                el->items.insert(auxI);

            }
            el++;
        }
        it++;
        el =total_elements.begin();
    }
    
    file.close(); // se cierra el archivo
    return capac;
}



#include <random>

//n corresponde a la cantidad de items que selecciona como candidatos
//en cada iteracion. Si n es grande se comporta como un greedy,
//si es pequeño (n=1), como un algoritmo que escoge aleatoriamente items.
void random_greedy(Knapsack& kn, list<Item>& total_items,int n){
    // dejar en clases
    if(n==0) n=1;
    
    while(true){
        //items that can be placed in the knapsack
        unordered_set <Item*> candidate_items;
        for(auto item: kn.unselected_items){
            if(item.second <= kn.getCapacity() - kn.getTotalWeight())
                candidate_items.insert(item.first);
        }

        if(candidate_items.size()==0) break;

        list <Item*> cand;
        std::experimental::sample(candidate_items.begin(), candidate_items.end(), std::back_inserter(cand),
                n, std::mt19937{std::random_device{}()});

        Item* selected_item=NULL;
        double ratio_max=0.0;

        for(auto item: cand){
            double ratio=(double)item->getProfit() / (double)  kn.unselected_items[item];
            if(ratio>ratio_max){
                ratio_max=ratio;
                selected_item=item;
            }
        }


        kn.addItem(selected_item);
    }

}


void simulated_annealing(Knapsack& init_kn,int max_iterations,float t_max, float t_min)
{
    float alpha = pow((t_min/t_max),0.01); // alpha que irá reduciendo la tmeperatura
    int n_iter = max_iterations * 0.01; // número de swap por cada valor de temperatura
    long double prob; //probabilidad de aceptación de una mala solución
    double r_01; // número random netre 0 y 1
    int mov_type; // tipo de movimiento a realizar 1, 2 o 3
    vector<int> mov = {0,0}; // vector para guardar los movimientos a ejecutar
    int c_swap = 0; // contador de swaps por cada valor de temperatura
    int cont = 0 ; // contador de vueltas en n_veces
    bool result = false; //guardará el resultado del swap
    int aux; // para calculos
    cout << alpha << " " << n_iter << " " << endl;
   
    mov_type = 1 + rand() % 2;
    //tipo_mov = 3;
    moves(mov_type,mov);
    //cout << kn_inicial.getBeneficioTotal() << endl;
    result = knapsack_swap(init_kn,mov);


    while ( c_swap <= max_iterations)
    {
        break;
        while (cont < n_iter)
        {
            mov_type = 1 + rand() % 2;
            //tipo_mov = 3;
            moves(mov_type,mov);
            //cout << kn_inicial.getBeneficioTotal() << endl;
            result = knapsack_swap(init_kn,mov);
             if (result == true)
            {
                if (init_kn.getTotalProfit() /*> best.getBeneficioTotal()*/)
                {
                    //best = kn_inicial;
                    cout << "El swap se aceptó: " << init_kn.getTotalProfit() << endl; 
                }else
                {
                    //aux = abs( /*best.getBeneficioTotal()*/ - kn_inicial.getBeneficioTotal() );
                    prob = (double) aux/ (double) t_max;
                    prob = exp(-prob);
                    r_01 = (double)rand()/(double)RAND_MAX;
                    if (r_01 < prob)
                    {
                        //best = kn_inicial;
                        cout << "El swap se aceptó: " << init_kn.getTotalProfit() << " con prob de: " << prob << endl; 
                    }
                }
                
                cont++;
                c_swap++;
            }
        }
        cont = 0;
        t_max *= alpha;
        if (t_max < t_min)
        {
            break;
        }
        
    }
    
    
}
bool knapsack_swap(Knapsack& init_kn,vector<int>& mov)
{
    //srand(10001);
    cout << endl;
    cout << "swap" <<  endl;
    bool result = true; // guardará el resultado del swap
    int q = mov[0], p = mov[1], extra_weight;
    cout << "q= " << q << " p= " << p << endl;
    set<Element*> remove;
    map<Item*, int> tentative_items; // guardará los items tentativos a guardar en mochila
    //resultado = kn_inicial.eliminarElemento(mov[0]); // guardará el resultado de eliminar el elemento
    Element* aux; // auxiliar que obtendrá el item del mapa
    Item* auxi;
    int pos_r; //posición del elemento a ingresar en mochila
    int cont = 1; // contador de posiciones

    while (q > 0)
    {
        pos_r = 1 + rand() & (init_kn.items.size());

        cout << "pos= " << pos_r<< endl;
        for (auto element: init_kn.elements)
        {
            if (pos_r == cont)
            {
                aux = element;
                remove.insert(element);
                break;
            }
            cont++;
        }
        cont = 1;
        cout << "elemento seleccionado: " << aux->getWeight()<< endl;
        init_kn.removeElement(aux);
        
        q--;
    }
    // buscar por fuera antes de eliminar
    // seleccionar q items aleatorio
    // identificar elementos a eliminar
    // si se eliminan mas de 0, es un mov prometedor
    // luego realizar eliminar 

    //tomo lo que falta y lo agrego
    // luego agregar items
    init_kn.removeParentlessElement();
    extra_weight = init_kn.getCapacity() - init_kn.getTotalWeight();
    cout << "peso disponible: " << extra_weight << endl;
    for (auto item: init_kn.unselected_items)
    {
        auxi = item.first;
        //cout << auxi->getPesoElementos() << endl;
            if (auxi->getElementWeight() <= extra_weight)
            {
                tentative_items.insert(make_pair(auxi,auxi->getProfit()));
            }
            
    }
    cout << "la cantidad de items tentativos es: " << tentative_items.size() << endl;
    for (auto item: init_kn.unselected_items)
    {
        auxi=item.first;
        init_kn.addItem(auxi);
        //cout << "se agregó: " << auxi->getBeneficio() << endl; 
    }
    
    

    return result;
}
void moves(int num_mov, vector<int>& mov)
{
    int q,p;
    switch (num_mov)
    {
    case 1:
        q = 0 + rand() % 2;
        p = 1;
        break;
    
    case 2:
        do{
            q = 1 + rand() % 3;
            p = 1 + rand() % 3;
        }while((q == 1) && (p==1));
        break;
    
    case 3:
        do{
            q = 0 + rand() % 2;
            p = 0 + rand() % 2;          
        }while((q == 0) && (p==0));
        break;
    
    default:
        break;
    }
    mov[0] = q;
    mov[1] = p;
}
// a temp bajo el sa debe funcionar como hill climbing