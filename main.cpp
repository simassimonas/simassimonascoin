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

class block{
private:
    time_t timestamp;
    float versija = 1.0;
    string blockHash;
    string prevBlockHash;
    int difficulty;
public:
    int nonce;
    block(int nonce_=0,int difficulty_=1, string prevBlockHash_="", string blockHash_="" ):nonce(nonce_), difficulty(difficulty_), prevBlockHash(prevBlockHash_), blockHash(blockHash_){
        timestamp=time(0);
    };
    inline string getBlockHash() const { return blockHash;};
    inline string getPrevBlockHash() const { return prevBlockHash;};
    inline int getDifficulty() const { return difficulty;};
    char* getTimeStamp() const {  char* dt = ctime(&timestamp); return dt; };
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


void mineBlocks(vector<transakcija>& transakcijos, vector<vartotojas>& vartotojai ){
    //sukuria blockchaina ir inicializuoja genesis blocka
    vector<block> blockChain;
    block genesisBlock(0, 1);
    blockChain.push_back(genesisBlock);

    bool ar=1;
    while(ar){
        if(transakcijos.size()/100>1){
            int tempNonce=0;
            string temphash;
            string dString(blockChain.back().getDifficulty(), '0'); //stringas, skirtas tikrinimui ar hashas atitinka sudetinguma
            do{
                tempNonce++;
                temphash = hashFunction(to_string(tempNonce)+blockChain.back().getPrevBlockHash());
            } while (temphash.substr(0, blockChain.back().getDifficulty()) != dString);
            //tikrina, ar reikia padidinti sunkuma
            if(blockChain.size()%25==0){
                block newBlock(tempNonce, blockChain.back().getDifficulty()+1, blockChain.back().getBlockHash(), temphash);
                blockChain.push_back(newBlock);
            }
            else{
                block newBlock(tempNonce, blockChain.back().getDifficulty(), blockChain.back().getBlockHash(), temphash);
                blockChain.push_back(newBlock);
            }
            transakcijos.erase(transakcijos.begin(), transakcijos.begin() + 100);
        }
        else ar=0;
    }

    for(int i=0; i<blockChain.size(); i++){
        cout << blockChain[i].getBlockHash() << " " << blockChain[i].getTimeStamp() << endl;
    }
    cout << blockChain.size();
}

int main()
{
    vector<vartotojas> vartotojai;
    int vartotojuKiekis = 10000;
    vartotojuKurimas(vartotojai, vartotojuKiekis);

    int transakcijuKiekis = 10045;
    transakcijuKurimas(vartotojai, transakcijuKiekis);

    vector<transakcija> transakcijos;
    transakcijuNuskaitymas(transakcijos);

    mineBlocks(transakcijos, vartotojai);

    return 0;
}
