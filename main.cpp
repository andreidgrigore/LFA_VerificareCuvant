#include <fstream>
#include <list>
#include <utility>
#include <string>
#include <iostream>
#include <cstring>
#define lgmaxlinie 50
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");

class Gramatica {
    int numar_neterminale;
    list<char> neterminale;
    int numar_terminale;
    char start;
    list<char> terminale;
    list<char> finale;
    list<pair<pair<char, char>, char> >productii;
    public:
        Gramatica();
        void Test(const char*);
        void DFS(const char*, int, char, bool&);
        friend istream & operator >> (istream &, Gramatica &);
        friend ostream & operator << (ostream &, const Gramatica &);
};

Gramatica::Gramatica(){
    numar_terminale=0;
    numar_neterminale=0;
}
void Gramatica::DFS(const char* cuv, int poz, char neterminal, bool &rezultat){
    if(poz==strlen(cuv)){
        list<char>::iterator it;
        for(it=finale.begin(); it!=finale.end(); it++)
            if(*it==neterminal)
                rezultat=true;
    }
    list<pair<pair<char, char>, char> >::iterator it;
    for(it=productii.begin(); it!=productii.end(); it++)
        if((*it).first.first==neterminal && (*it).second==cuv[poz])
            DFS(cuv, poz+1, (*it).first.second, rezultat);
}
void Gramatica::Test(const char* cuv){
    bool test=false;
    DFS(cuv, 0, start, test);
    if(test==true)
        cout<<"Cuvant acceptat";
    else cout<<"Cuvant neacceptat";
    cout<<endl;
}
istream & operator >> (istream &in, Gramatica &g){
    in>>g.numar_neterminale;
    int i;
    char c;
    for(i=1; i<=g.numar_neterminale; i++){
        in>>c;
        g.neterminale.push_back(c);
    }
    g.start=*(g.neterminale.begin());
    in>>g.numar_terminale;
    for(i=1; i<=g.numar_terminale; i++){
        in>>c;
        g.terminale.push_back(c);
    }
    char linie[lgmaxlinie];
    in.get();
    for(i=1; i<=g.numar_neterminale; i++){
        in.getline(linie, lgmaxlinie);
        char nt1=linie[0];
        char *tok=linie;
        while((tok=strtok(tok, "->/"))!=NULL){
            if(strcmp(tok, "0")==0)
                g.finale.push_back(nt1);
            else if(strlen(tok)==2){
                char trm=tok[0];
                char nt2=tok[1];
                g.productii.push_back(make_pair(make_pair(nt1, nt2), trm));
            }
            tok=NULL;
        }
    }
    return in;
}
ostream & operator << (ostream &out, const Gramatica &g){
    out<<"Numar neterminale: "<<g.numar_neterminale<<endl;
    out<<"Neterminalele: ";
    list<char>::const_iterator it;
    for(it=g.neterminale.begin(); it!=g.neterminale.end(); it++)
        out<<*it<<" ";
    out<<endl<<"Neterminalul de start este: "<<g.start<<endl;
    out<<"Numar terminale: "<<g.numar_terminale<<endl;
    out<<"Terminalele: ";
    for(it=g.terminale.begin(); it!=g.terminale.end(); it++)
        out<<*it<<" ";
    out<<endl<<"Productiile: "<<endl;
    list<pair<pair<char, char>, char> >::const_iterator it2;
    for(it2=g.productii.begin(); it2!=g.productii.end(); it2++)
        out<<(*it2).first.first<<"->"<<(*it2).second<<(*it2).first.second<<endl;
    out<<"Finalele: ";
    for(it=g.finale.begin(); it!=g.finale.end(); it++)
        out<<*it<<" ";
    return out;
}



int main(){
    Gramatica g;
    fin>>g;
    g.Test("aaaabbbbbb");

    fout<<g;
    return 0;
}
