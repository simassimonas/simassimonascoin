#include "header.h"

class vartotojas{
private:
    string vardas;
    string publicKey;
    double balansas;
public:
    vartotojas(string vardas_ = "", string publicKey_ = "", double sscoin_ = 0): vardas(vardas_), publicKey(publicKey_), balansas(sscoin_){};
    void setVardas(string vardas_) { vardas = vardas_;}
	void setPublicKey(string publicKey_) { publicKey = publicKey_;}
	void setBalansas(double balansas_) { balansas = balansas_;}
    inline string getVardas() const { return vardas;}
    inline string getPublicKey() const { return publicKey;}
    inline double getBalansas() const { return balansas;}
    void addBalansas(double balansas_) {balansas+=balansas_;}
    void subBalansas(double balansas_) {balansas-=balansas_;}
};

class transakcija{
private:
    int nr;
    string keyFrom;
    string keyTo;
    double suma;
public:
    transakcija(int nr_=0, string keyFrom_="", string keyTo_="", double suma_=0): nr(nr_), keyFrom(keyFrom_), keyTo(keyTo_), suma(suma_){};
    inline int getNr() const {return nr;}
    inline string getKeyFrom() const {return keyFrom;}
    inline string getKeyTo() const {return keyTo;}
    inline double getSuma() const {return suma;}
};

void vartotojuKurimas(vector<vartotojas>& vartotojai, int vartotojuKiekis){
    for(int i=0; i<vartotojuKiekis; i++){
        vartotojas temp("vardas"+to_string(i+1), hashFunction(to_string(i)), 100+(std::rand()%(1000000-100+1)));
        vartotojai.push_back(temp);
    }
}

void transakcijuKurimas(vector<vartotojas>& vartotojai, int transakcijuKiekis){
    ofstream fout ("transakcijos.txt");
    for(int i=0; i<transakcijuKiekis; i++){
        fout << vartotojai[std::rand()%vartotojai.size()].getPublicKey() << " " << vartotojai[std::rand()%vartotojai.size()].getPublicKey() << " " << 100+(std::rand()%(10000-100+1)) << endl;
    }
        // publicKeyFrom << publicKeyTo << amount
}

void transakcijuNuskaitymas(vector<transakcija>& transakcijos){
    ifstream fin ("transakcijos.txt");
    string line, temp1, temp2;
    double temp3;
    int i=0;
    while (getline(fin, line))
    {
        i++;
        std::istringstream iss(line);
        iss >> temp1;
        iss >> temp2;
        iss >> temp3;
        transakcija tempTransakcija(i, temp1, temp2, temp3);
        transakcijos.push_back(tempTransakcija);
    }
}

int main()
{
    vector<vartotojas> vartotojai;
    int vartotojuKiekis = 100;
    vartotojuKurimas(vartotojai, vartotojuKiekis);

    int transakcijuKiekis = 10000;
    transakcijuKurimas(vartotojai, transakcijuKiekis);
    vector<transakcija> transakcijos;
    transakcijuNuskaitymas(transakcijos);
    cout << transakcijos[1].getNr() << transakcijos[9999].getKeyFrom() << endl;


    return 0;
}
