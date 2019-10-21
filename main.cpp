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
    string ID;
public:
    transakcija(int nr_=0, string keyFrom_="", string keyTo_="", double suma_=0): nr(nr_), keyFrom(keyFrom_), keyTo(keyTo_), suma(suma_){ID=hashFunction(keyFrom+keyTo+to_string(suma));}
    inline int getNr() const {return nr;}
    inline string getKeyFrom() const {return keyFrom;}
    inline string getKeyTo() const {return keyTo;}
    inline double getSuma() const {return suma;}
    inline string getID() const {return ID;}
};

class block{
private:
    time_t timestamp;
    float versija = 1.0;
    string blockHash;
    string prevBlockHash;
    int difficulty;
    vector<transakcija> blokoTransakcijos;
public:
    int nonce;
    block(int nonce_=0,int difficulty_=1, string prevBlockHash_="", string blockHash_="", int blockChainSize=1 ):nonce(nonce_), difficulty(difficulty_), prevBlockHash(prevBlockHash_), blockHash(blockHash_){
        timestamp=time(0);
        if(blockChainSize%25==0) difficulty++; //padidina blocko difficulty
    };
    inline string getBlockHash() const { return blockHash;};
    inline string getPrevBlockHash() const { return prevBlockHash;};
    inline int getDifficulty() const { return difficulty;};
    char* getTimeStamp() const {  char* dt = ctime(&timestamp); return dt; };
    void assignTransactions(vector<transakcija>& transakcijos) { blokoTransakcijos.assign(transakcijos.begin(), transakcijos.begin()+100); }
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
        string temp1 = vartotojai[std::rand()%vartotojai.size()].getPublicKey();
        string temp2 = vartotojai[std::rand()%vartotojai.size()].getPublicKey();
        double temp3 = 100+(std::rand()%(10000-100+1));
        fout << temp1 << " " << temp2 << " " << temp3 << " " << hashFunction(temp1+temp2+to_string(temp3)) << endl;
    }
        // publicKeyFrom << publicKeyTo << amount << transakcijosID
}

bool arUztenkaBalanso(string publicKey, double suma, vector<vartotojas>& vartotojai){
    int i=0;
    while(vartotojai[i].getPublicKey()!=publicKey){
        i++;
    }
    if(vartotojai[i].getBalansas()>=suma) return 1;
    else return 0;
}

void transakcijuNuskaitymas(vector<transakcija>& transakcijos, vector<vartotojas>& vartotojai){
    ifstream fin ("transakcijos.txt");
    string line, temp1, temp2, temp4;
    double temp3;
    int i=0;
    while (getline(fin, line))
    {
        i++;
        std::istringstream iss(line);
        iss >> temp1;
        iss >> temp2;
        iss >> temp3;
        iss >> temp4;
        transakcija tempTransakcija(i, temp1, temp2, temp3);
        //patikrina ar transakcijos informacijos hashas sutampa su transakcijos ID ir ar uztenka balanso
        if(tempTransakcija.getID()==temp4&&arUztenkaBalanso(temp1, temp3, vartotojai)) transakcijos.push_back(tempTransakcija);
    }
}


void mineBlocks(vector<transakcija>& transakcijos, vector<vartotojas>& vartotojai ){
    //sukuria blockchaina ir inicializuoja genesis blocka
    vector<block> blockChain;
    block genesisBlock(0, 1);
    blockChain.push_back(genesisBlock);

    while(transakcijos.size()>=500){
        unsigned long nonce=0;
        int Blocks=5;
        string Temphash;
        string difString(blockChain.back().getDifficulty(), '0'); //stringas, skirtas tikrinimui ar hashas atitinka sudetinguma
        int kelintasWhile=1; //parodo, kelinta karta nepavyko rasti hasho (tries!=maxTries) while
        while(Blocks!=0){
            int tries=0;
            int maxTries=kelintasWhile*300*Blocks;
            while(tries!=maxTries){
                Temphash = hashFunction(to_string(nonce)+blockChain.back().getBlockHash());
                if(Temphash.substr(0, blockChain.back().getDifficulty()) == difString){
                    Blocks--;
                    block newBlock(nonce, blockChain.back().getDifficulty(), blockChain.back().getBlockHash(), Temphash, blockChain.size());
                    newBlock.assignTransactions(transakcijos);
                    blockChain.push_back(newBlock);
                    transakcijos.erase(transakcijos.begin(), transakcijos.begin() + 100);
                    break;
                }
                nonce++;
                tries++;
            }
            if(tries==maxTries) kelintasWhile++;
        }
    }

    bool ar=1;
    while(ar){
        if(transakcijos.size()>=100){
            int tempNonce=0;
            string temphash;
            string dString(blockChain.back().getDifficulty(), '0'); //stringas, skirtas tikrinimui ar hashas atitinka sudetinguma
            do{
                tempNonce++;
                temphash = hashFunction(to_string(tempNonce)+blockChain.back().getBlockHash());
            } while (temphash.substr(0, blockChain.back().getDifficulty()) != dString);

            block newBlock(tempNonce, blockChain.back().getDifficulty(), blockChain.back().getBlockHash(), temphash, blockChain.size());
            newBlock.assignTransactions(transakcijos);
            blockChain.push_back(newBlock);
            transakcijos.erase(transakcijos.begin(), transakcijos.begin() + 100);
        }
        else ar=0;
    }

    for(int i=0; i<blockChain.size(); i++){
        cout << i << " " << blockChain[i].getBlockHash() << " " << blockChain[i].getTimeStamp() << endl;
    }
    cout << "Is viso bloku: " << blockChain.size() << endl;
}

int main()
{
    vector<vartotojas> vartotojai;
    int vartotojuKiekis = 10000;
    vartotojuKurimas(vartotojai, vartotojuKiekis);

    int transakcijuKiekis = 200;
    transakcijuKurimas(vartotojai, transakcijuKiekis);

    vector<transakcija> transakcijos;
    transakcijuNuskaitymas(transakcijos, vartotojai);

    mineBlocks(transakcijos, vartotojai);

    return 0;
}
