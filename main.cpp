#include <iostream>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <chrono>
using namespace std;


string llenadoCadena(int l)
{
    //srand(time(0));
    string c;
    string alfabeto = "aeiou";
    for(int i=0;i<l;i++)
    {
        c+= alfabeto[rand()%alfabeto.size()];
    }
    return c;
}

void contador(string c, int ini,int fin,int *cont)
{
    for(int i=ini;i<fin;i++)
    {
        if(c[i]=='a') (*cont)++;
        else if(c[i]=='e') (*(cont+1))++;
        else if(c[i]=='i') (*(cont+2))++;
        else if(c[i]=='o') (*(cont+3))++;
        else if(c[i]=='u') (*(cont+4))++;
    }
}


int main()
{
    int TAM=10000;
    string cadenaVocales;
    cadenaVocales = llenadoCadena(TAM);
    //hilos detectado por procesador
    int cores = thread::hardware_concurrency();
    int *cuenta= new int[5];
    int razon = cadenaVocales.size()/cores;

    *cuenta=0;
    *(cuenta+1) = 0;    *(cuenta+2) = 0;    *(cuenta+3) = 0;    *(cuenta+4) = 0;
    //int menorr
    vector<thread> threads;

    //con hilos
    auto start = std::chrono::system_clock::now();
    for (int i=0; i<cores; i++)
    {
        threads.push_back(thread(contador,cadenaVocales,i*razon,razon*(i+1),cuenta));
        cout << "\nini: " << i*razon << " fin: " << razon*(i+1) << endl;
    }
    for (auto& th : threads) th.join();
    auto end = std::chrono::system_clock::now();

    //sin hilos
    auto start2 = std::chrono::system_clock::now();
    contador(cadenaVocales,0,TAM,cuenta);
    auto end2 = std::chrono::system_clock::now();


    std::chrono::duration<float,std::milli> duration = end - start;
    cout << " \ncon hilos " << duration.count() << "s\n" << endl;

    std::chrono::duration<float,std::milli> duration2 = end2 - start2;
    cout << " \nsin hilos " << duration2.count() << "s\n" << endl;

    //output
    cout <<  "\na :" << *cuenta << endl;
    cout <<  "\ne :" << *(cuenta+1) << endl;    cout <<  "\ni :" << *(cuenta+2) << endl;    cout <<  "\no :" << *(cuenta+3) << endl;    cout <<  "\nu :" << *(cuenta+4) << endl;
    cout <<  "\ntotal :" << (cuenta[0] + cuenta[1] +cuenta[2] + cuenta[3] + cuenta[4]) <<endl;
    cout <<"\n razon: " << razon << endl;
    delete cuenta;
    return 0;
}


