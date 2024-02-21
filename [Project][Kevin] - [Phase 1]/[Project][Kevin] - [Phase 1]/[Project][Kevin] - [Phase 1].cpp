#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Ingredient //contine ingredientele/materiile prime 
{
    char* ingredient;
    const int id;
    static int idPrecedent;

public:

    Ingredient(int id) :id{ id }
    {
        this->ingredient = nullptr;
    }

    Ingredient(char* ingredient) :id{ generareId() }
    {
        this->ingredient = new char[strlen(ingredient) + 1];
        strcpy(this->ingredient, ingredient);

    }

    Ingredient(const Ingredient& original) :id{ original.id }
    {
        if (original.ingredient != nullptr) {
            delete[] this->ingredient;
            this->ingredient = new char[strlen(original.ingredient) + 1];
            strcpy(this->ingredient, original.ingredient);
        }

    }

    const int getId()
    {
        return this->id;
    }

    const static int getIdPrecedent()
    {
        return Ingredient::idPrecedent;
    }


    string getDenumire()
    {
        string str(this->ingredient);
        return str;
    }
    void setIngredient(char* Ingredient)
    {
        if (Ingredient != nullptr)
        {
            delete[] this->ingredient;
            this->ingredient = new char[strlen(Ingredient) + 1];
            strcpy(this->ingredient, Ingredient);
        }
    }

    static int generareId()
    {
        return ++Ingredient::idPrecedent;
    }

    ~Ingredient()
    {

        delete[] this->ingredient;
        this->ingredient = nullptr;
    }

    Ingredient& operator=(const Ingredient& dreapta)
    {
        if (this != &dreapta) {
            if (dreapta.ingredient != nullptr) {
                delete[] this->ingredient;
                this->ingredient = new char[strlen(dreapta.ingredient) + 1];
                strcpy(this->ingredient, dreapta.ingredient);
            }
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Ingredient* obj)
    {
        os << "\n=============================";
        os << "\nId: " << obj->id;
        os << "\nIngredient: " << obj->ingredient;
        os << "\n=============================\n";
        return os;
    }

    friend istream& operator>>(istream& is, Ingredient* obj)
    {
        cout << "\nIntroduceti noul ingredient: ";
        delete[] obj->ingredient;
        string buffer;
        is >> buffer;
        obj->ingredient = new char[buffer.size() + 1];
        strcpy(obj->ingredient, buffer.data());
        cout << endl;
        return is;
    }

};
int Ingredient::idPrecedent = 0;


class Stoc //tine minte cantitatea din fiecare ingredient
{
private:
    Ingredient** ingrediente = nullptr; //vector alocat dinamic de pointer la ingrediente
    int* cantitate = 0;
public:
    Stoc(int* cantitate, Ingredient** ingrediente)
    {
        this->cantitate = new int[Ingredient::getIdPrecedent()];
        for (int i = 0; i < Ingredient::getIdPrecedent(); i++)
        {
            this->cantitate[i] = cantitate[i];
        }
        this->ingrediente = new Ingredient * [Ingredient::getIdPrecedent()];
        for (int i = 0; i < Ingredient::getIdPrecedent(); i++)
        {
            this->ingrediente[i] = ingrediente[i];
        }

    }

    const int getCantitate(int poz)
    {
        return this->cantitate[poz];
    }

    void setCantitate(int cantitate, int pozitie)
    {
        if (cantitate >= 0)
        {
            this->cantitate[pozitie] = cantitate;
        }
    }

    Ingredient** getIngrediente()
    {
        return this->ingrediente;
    }


    Stoc(const Stoc& original)
    {
        delete[] this->ingrediente;
        this->ingrediente = nullptr;
        delete[] this->cantitate;
        this->cantitate = nullptr;
        this->cantitate = new int[Ingredient::getIdPrecedent()];
        for (int i = 0; i < Ingredient::getIdPrecedent(); i++)
        {
            this->cantitate[i] = original.cantitate[i];
        }
        this->ingrediente = new Ingredient * [Ingredient::getIdPrecedent()];
        for (int i = 0; i < Ingredient::getIdPrecedent(); i++)
        {
            this->ingrediente[i] = original.ingrediente[i];
        }
    }

    Stoc& operator=(const Stoc& dreapta)
    {
        if (this != &dreapta)
        {
            delete[] this->ingrediente;
            this->ingrediente = nullptr;
            delete[] this->cantitate;
            this->cantitate = nullptr;
            this->cantitate = new int[Ingredient::getIdPrecedent()];
            for (int i = 0; i < Ingredient::getIdPrecedent(); i++)
            {
                this->cantitate[i] = dreapta.cantitate[i];
            }
            this->ingrediente = new Ingredient * [Ingredient::getIdPrecedent()];
            for (int i = 0; i < Ingredient::getIdPrecedent(); i++)
            {
                this->ingrediente[i] = dreapta.ingrediente[i];
            }
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Stoc* dreapta)
    {
        os << "\n=============================================";
        os << "\nIngredientele si cantitatea echivalenta:\n";
        for (int i = 0; i < Ingredient::getIdPrecedent(); i++)
        {
            if (dreapta->ingrediente[i]->getId() != 25)
                if (dreapta->ingrediente[i]->getId() != 26)
                {
                    os << dreapta->ingrediente[i]->getDenumire() << " de cantitate " << dreapta->cantitate[i] << endl;
                }
        }
        os << "\n=============================================\n";
        return os;
    }

    friend istream& operator>>(istream& is, Stoc& dreapta)
    {
        cout << "Selectati ingredientul caruia vreti sa ii modificati cantitatea:" << endl;
        for (int i = 0; i < Ingredient::getIdPrecedent(); i++)
        {
            if (dreapta.ingrediente[i]->getId() != 25)
                if (dreapta.ingrediente[i]->getId() != 26) {
                    cout << i + 1 << "-" << dreapta.ingrediente[i]->getDenumire() << "; ";
                    cout << endl;
                }
        }
        cout << "Introduceti id-ul:";
        int id;
        cin >> id;
        cout << "\nIntroduceti valoarea noului stoc:";
        is >> dreapta.cantitate[id - 1];
        cout << "\nStocul a fost modificat cu succes!";
        return is;

    }

    Stoc& operator+=(int cantitateInPlus)
    {
        for (int i = 0; i < Ingredient::getIdPrecedent(); i++)
        {
            this->cantitate[i] += cantitateInPlus;
        }
        cout << "\nComanda efectuata cu succes";
        return *this;
    }

    Stoc& operator-=(int cantitateInPlus)
    {
        for (int i = 0; i < Ingredient::getIdPrecedent(); i++)
        {
            this->cantitate[i] -= cantitateInPlus;
        }
        cout << "\nComanda efectuata cu succes";
        return *this;
    }

    ~Stoc()
    {
        delete[] this->cantitate;
        this->cantitate = nullptr;
        delete[] this->ingrediente;
        this->ingrediente = nullptr;
    }

};

class Reteta //combina ingredientele in diferite retete
{
    Ingredient** ingredienteNecesare = nullptr;
    int* cantitateNecesara = nullptr;
    int nrIngrediente = 0;
public:
    Reteta(Ingredient** ingredienteNecesare, int* cantitateNecesara, int nrIngrediente)
    {
        this->nrIngrediente = nrIngrediente;
        this->cantitateNecesara = new int[this->nrIngrediente];
        for (int i = 0; i < this->nrIngrediente; i++)
        {
            this->cantitateNecesara[i] = cantitateNecesara[i];
        }
        this->ingredienteNecesare = new Ingredient * [this->nrIngrediente];
        for (int i = 0; i < this->nrIngrediente; i++)
        {
            this->ingredienteNecesare[i] = ingredienteNecesare[i];
        }
    }


    void setIngredienteNecesare(Ingredient** original, int dimensiune)
    {

        this->ingredienteNecesare = new Ingredient * [dimensiune];
        for (int i = 0; i < dimensiune; i++)
        {
            this->ingredienteNecesare[i] = original[i];
        }
    }

    Ingredient** getIngredienteNecesare()
    {
        return this->ingredienteNecesare;
    }

    const int getCantitateNecesara(int poz)
    {
        return this->cantitateNecesara[poz];
    }

    void setCantitateNecesara()
    {
        int cantitateNoua = 0;
        for (int i = 0; i < this->nrIngrediente; i++)
        {
            cout << "Cantitate ingredient " << i << ":";
            cin >> cantitateNoua;
            this->cantitateNecesara[i] = cantitateNoua;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    }

    const int getNrIngrediente()
    {
        return this->nrIngrediente;
    }

    Reteta(const Reteta& original)
    {
        delete[] this->ingredienteNecesare;
        this->ingredienteNecesare = nullptr;
        delete[] this->cantitateNecesara;
        cantitateNecesara = nullptr;

        this->nrIngrediente = original.nrIngrediente;
        this->cantitateNecesara = new int[this->nrIngrediente];
        for (int i = 0; i < this->nrIngrediente; i++)
        {
            this->cantitateNecesara[i] = original.cantitateNecesara[i];
        }
        this->ingredienteNecesare = new Ingredient * [this->nrIngrediente];
        for (int i = 0; i < this->nrIngrediente; i++)
        {
            this->ingredienteNecesare[i] = original.ingredienteNecesare[i];
        }
    }

    Reteta& operator=(const Reteta& dreapta)
    {
        if (this != &dreapta)
        {
            delete[] this->ingredienteNecesare;
            this->ingredienteNecesare = nullptr;
            delete[] this->cantitateNecesara;
            cantitateNecesara = nullptr;

            this->nrIngrediente = dreapta.nrIngrediente;
            this->cantitateNecesara = new int[this->nrIngrediente];
            for (int i = 0; i < this->nrIngrediente; i++)
            {
                this->cantitateNecesara[i] = dreapta.cantitateNecesara[i];
            }
            this->ingredienteNecesare = new Ingredient * [this->nrIngrediente];
            for (int i = 0; i < this->nrIngrediente; i++)
            {
                this->ingredienteNecesare[i] = dreapta.ingredienteNecesare[i];
            }

        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, Reteta* dreapta)
    {
        os << "\n==========================================";
        os << "\nIngrediente necesare si cantitatile lor: ";
        for (int i = 0; i < dreapta->nrIngrediente; i++)
        {
            os << dreapta->ingredienteNecesare[i]->getDenumire() << " - " << dreapta->cantitateNecesara[i] << ";  ";
        }
        os << "\n==========================================\n";
        return os;
    }

    friend istream& operator>>(istream& is, Reteta* dreapta)
    {
        string buffer;
        cout << "\nIntroduceti ingredientul pe care doriti sa il modificati:";
        getline(cin, buffer);
        for (int i = 0; i < dreapta->nrIngrediente; i++)
        {
            if (buffer == dreapta->ingredienteNecesare[i]->getDenumire())
            {
                cin >> dreapta->ingredienteNecesare[i];
            }
        }
        cout << "\nModificarea a fost efectuata cu succes!";
        return is;
    }

    ~Reteta()
    {
        delete[] this->ingredienteNecesare;
        this->ingredienteNecesare = nullptr;
        delete[] this->cantitateNecesara;
        this->cantitateNecesara = nullptr;
    }

};

class Produs
{
    Reteta* retetaProdus = nullptr; //pointer la o reteta
    string denumire = "Necunoscuta";
    float pret = 0;
public:

    Produs()
    {
        this->retetaProdus = nullptr;
        this->denumire = "Necunoscuta";
        this->pret = 0;
    }

    Produs(string denumire)
    {
        this->retetaProdus = nullptr;
        this->denumire = denumire;
    }

    Produs(Reteta* retetaProdus, string denumire, float pret)
    {
        this->retetaProdus = retetaProdus;
        this->denumire = denumire;
        this->pret = pret;
    }

    Produs(const Produs& original)
    {
        delete this->retetaProdus;
        this->retetaProdus = original.retetaProdus;
        this->denumire = original.denumire;
        this->pret = original.pret;
    }

    Produs& operator=(const Produs& dreapta)
    {
        if (this != &dreapta)
        {
            delete this->retetaProdus;
            this->retetaProdus = dreapta.retetaProdus;
            this->denumire = dreapta.denumire;
            this->pret = dreapta.pret;
        }
        return *this;
    }

    void setDenumire(string denumire)
    {
        this->denumire = denumire;
    }

    int getPret()
    {
        return this->pret;
    }

    void setPret(float valoare)
    {
        this->pret = valoare;
    }

    const string getDenumire()
    {
        return this->denumire;
    }

    Reteta* getRetetaProdus()
    {
        return this->retetaProdus;
    }

    bool operator==(Produs& dreapta)
    {
        if (this->retetaProdus->getNrIngrediente() != dreapta.retetaProdus->getNrIngrediente())
        {
            return false;
        }
        else
        {
            for (int i = 0; i < this->retetaProdus->getNrIngrediente(); i++)
            {
                if (this->retetaProdus->getIngredienteNecesare()[i] != dreapta.retetaProdus->getIngredienteNecesare()[i])
                {
                    return false;
                }
            }
        }
        return true;
    }

    friend ostream& operator<<(ostream& os, const Produs* dreapta)
    {
        Ingredient** temp = dreapta->retetaProdus->getIngredienteNecesare();
        int dimensiuneTemp = dreapta->retetaProdus->getNrIngrediente();

        os << "\n----------------------------------------------------------------------------------------------------";
        os << "\n" << dreapta->denumire << ", " << "cu pretul de " << dreapta->pret << " de lei. Ingrediente: ";
        for (int i = 0; i < dimensiuneTemp; i++)
        {
            os << temp[i]->getDenumire() << " ";
        }
        return os;
    }

    friend istream& operator>>(istream& is, Produs* dreapta)
    {
        int pretNou;
        cout << "\nIntroduceti noul pret:";
        is >> pretNou;
        dreapta->pret = pretNou;
        return is;
    }

    ~Produs()
    {

    }

};

class Meniu //centralizeaza produsele
{
    Produs** listaProduse;
    int nrProduse;
public:
    Meniu(Produs** listaProduse, int nrProduse)
    {
        this->nrProduse = nrProduse;
        this->listaProduse = new Produs * [this->nrProduse];
        for (int i = 0; i < this->nrProduse; i++)
        {
            this->listaProduse[i] = listaProduse[i];
        }
    }

    const int getNrProduse()
    {
        return this->nrProduse;
    }

    Meniu(Meniu& original)
    {
        delete this->listaProduse;
        this->listaProduse = nullptr;
        this->nrProduse = original.nrProduse;
        this->listaProduse = new Produs * [this->nrProduse];
        for (int i = 0; i < this->nrProduse; i++)
        {
            this->listaProduse[i] = original.listaProduse[i];
        }
    }

    Meniu& operator=(Meniu& original)
    {
        if (this != &original) {
            delete this->listaProduse;
            this->listaProduse = nullptr;
            this->nrProduse = original.nrProduse;
            this->listaProduse = new Produs * [this->nrProduse];
            for (int i = 0; i < this->nrProduse; i++)
            {
                this->listaProduse[i] = original.listaProduse[i];
            }
        }
        return *this;
    }

    void modificareIngredienteReteta(string input)
    {
        for (int i = 0; i < this->nrProduse; i++)
        {
            if (input == this->listaProduse[i]->getDenumire())
            {
                cin >> listaProduse[i]->getRetetaProdus();
            }
        }
    }

    void operator[](float pretNou)
    {
        for (int i = 0; i < this->nrProduse; i++)
        {
            if (pretNou >= this->listaProduse[i]->getPret())
            {
                cout << this->listaProduse[i];
            }

        }
        cout << "\n----------------------------------------------------------------------------------------------------";
        cout << endl;
    }

    void operator()()
    {
        for (int i = 0; i < this->nrProduse; i++)
        {
            if (this->listaProduse[i]->getDenumire()[0] == 'P' && this->listaProduse[i]->getDenumire()[1] == 'i' && this->listaProduse[i]->getDenumire()[2] == 'z' &&
                this->listaProduse[i]->getDenumire()[3] == 'z' && this->listaProduse[i]->getDenumire()[4] == 'a')
            {
                cout << this->listaProduse[i];
            }
        }
        cout << "\n----------------------------------------------------------------------------------------------------";
        cout << endl;
    }

    void operator!()
    {
        for (int i = 0; i < this->nrProduse; i++)
        {
            if (this->listaProduse[i]->getDenumire()[0] == 'B' && this->listaProduse[i]->getDenumire()[1] == 'a' && this->listaProduse[i]->getDenumire()[2] == 'u' &&
                this->listaProduse[i]->getDenumire()[3] == 't' && this->listaProduse[i]->getDenumire()[4] == 'u' && this->listaProduse[i]->getDenumire()[5] == 'r'
                && this->listaProduse[i]->getDenumire()[6] == 'a')
            {
                cout << this->listaProduse[i];
            }
        }
        cout << "\n----------------------------------------------------------------------------------------------------";
        cout << endl;
    }

    friend ostream& operator<<(ostream& os, const Meniu& dreapta)
    {
        os << "\nMENIUL, CE INCLUDE PRODUSELE, PRETURILE LOR SI INGREDIENTELE AFERENTE:";


        for (int i = 0; i < dreapta.nrProduse; i++)
        {
            os << dreapta.listaProduse[i];
        }

        os << "\n----------------------------------------------------------------------------------------------------";
        return os;
    }

    friend istream& operator>>(istream& is, const Meniu& dreapta)
    {
        string input;
        cout << "\nIntroduceti produsul caruia doriti sa ii modificati pretul:";
        getline(cin, input);
        for (int i = 0; i < dreapta.nrProduse; i++)
        {
            if (input == dreapta.listaProduse[i]->getDenumire())
            {
                is >> dreapta.listaProduse[i];
                cout << "\nModificarea a fost efectuata cu succes.";
                return is;
            }

        }
        cout << "Nu s-a gasit produsul cautat.";
        return is;
    }

    ~Meniu()
    {
        delete[] this->listaProduse;
        this->listaProduse = nullptr;
    }
};


class Restaurant //ofera o interfata utilizatorului si 
    //gestioneaza restul claselor
{
    Produs** produse;
    Stoc* stoc;
    int nrProduse;
public:
    Restaurant(Produs** produse, Stoc* stoc, int nrProduse)
    {
        this->nrProduse = nrProduse;
        this->produse = new Produs * [this->nrProduse];
        for (int i = 0; i < this->nrProduse; i++)
        {
            this->produse[i] = produse[i];

        }
        this->stoc = stoc;
    }

    Restaurant(Restaurant& original)
    {
        delete[] this->produse;
        this->produse = nullptr;

        this->nrProduse = original.nrProduse;
        this->produse = new Produs * [this->nrProduse];
        for (int i = 0; i < this->nrProduse; i++)
        {
            this->produse[i] = original.produse[i];

        }
        this->stoc = original.stoc;
    }


    Restaurant& operator=(Restaurant& original)
    {
        if (this != &original)
        {
            delete[] this->produse;
            this->produse = nullptr;

            this->nrProduse = original.nrProduse;
            this->produse = new Produs * [this->nrProduse];
            for (int i = 0; i < this->nrProduse; i++)
            {
                this->produse[i] = original.produse[i];

            }
            this->stoc = original.stoc;
        }
        return *this;
    }



    const int getNrProduse()
    {
        return this->nrProduse;
    }

    Restaurant& operator++()
    {
        for (int i = 0; i < this->nrProduse; i++)
        {
            this->produse[i]->setPret(this->produse[i]->getPret() + 10);
        }
        cout << "\nAti crescut pretul cu succes.";
        return *this;
    }

    Restaurant& operator--()
    {
        for (int i = 0; i < this->nrProduse; i++)
        {
            this->produse[i]->setPret(this->produse[i]->getPret() - 5);
        }
        return *this;
    }

    friend bool operator>(Restaurant& stanga, int numar)
    {
        for (int i = 0; i < Ingredient::getIdPrecedent(); i++)
        {
            if (numar > stanga.stoc->getCantitate(i))
            {
                return false;
            }

        }
        return true;
    }

    bool verificareProdus()
    {
        Produs produs1;
        Produs produs2;
        bool verificare;
        string input;
        cout << "\nIntroduceti numele primului produs:";
        getline(cin, input);
        int i = 0;

        while (i < this->nrProduse && input != this->produse[i]->getDenumire())
        {
            i++;
        }

        if (i < this->nrProduse)
        {
            produs1 = *this->produse[i];

        }
        else
        {
            cout << "Produsul introdus este invalid, deci";
            verificare = false;
            return verificare;
        }

        cout << "\nIntroduceti numele celui de-al doilea produs:";
        getline(cin, input);
        while (i < this->nrProduse && input == this->produse[i]->getDenumire())
        {
            i++;
        }

        if (i < this->nrProduse)
        {
            produs2 = *this->produse[i];
        }
        else
        {
            cout << "Produsul introdus este invalid, deci";
            verificare = false;
            return verificare;
        }
        verificare = produs1 == produs2;
        return verificare;

    }


    bool verificareStoc(string denumire, int nrProduseCerute)
    {
        Produs produsComandat(denumire);
        int i = 0;
        while (produsComandat.getDenumire() != this->produse[i]->getDenumire())
        {
            i++;
        }
        produsComandat = *this->produse[i];

        int dimensiuneVector = produsComandat.getRetetaProdus()->getNrIngrediente();
        int temp = 0;
        int cantitateNecesaraIngredient = 0;
        for (int i = 0; i < Ingredient::getIdPrecedent(); i++)
        {
            for (int j = 0; j < dimensiuneVector; j++)
            {
                if (i + 1 == produsComandat.getRetetaProdus()->getIngredienteNecesare()[j]->getId())
                {
                    cantitateNecesaraIngredient = produsComandat.getRetetaProdus()->getCantitateNecesara(j);
                    temp = this->stoc->getCantitate(i) - cantitateNecesaraIngredient * nrProduseCerute;
                    if (temp < 0)
                        return false;
                    else
                        this->stoc->setCantitate(temp, i);
                }
            }

        }


        return true;

    }



    friend ostream& operator<<(ostream& os, const Restaurant& dreapta)
    {
        os << "\nProdusele prezente in meniu, preturile si ingredientele lor:";


        for (int i = 0; i < dreapta.nrProduse; i++)
        {
            os << dreapta.produse[i];
        }

        os << "\n----------------------------------------------------------------------------------------------------";
        return os;
    }


    friend istream& operator>>(istream& is, const Restaurant& dreapta)
    {
        string input;
        cout << "\nIntroduceti produsul caruia doriti sa ii modificati numele:";
        getline(cin, input);
        for (int i = 0; i < dreapta.nrProduse; i++)
        {
            if (input == dreapta.produse[i]->getDenumire())
            {
                cout << "\nIntroduceti noua denumire:";
                getline(cin, input);
                dreapta.produse[i]->setDenumire(input);
                cout << "\nModificarea a fost efectuata cu succes.";
                return is;
            }

        }
        cout << "Nu s-a gasit produsul cautat.";
        return is;
    }


    void afisareLegendaMeniu()
    {
        cout << "\nLEGENDA MENIU:";
        cout << "\n1.Tastati 'meniu principal' pentru a va intoarce la comenzile initiale.";
        cout << "\n2.Tastati numele produsului pentru a efectua o comanda.";
        cout << "\n3.Tastati 'meniu pizza' daca vreti sa vedeti doar meniul de pizza.";
        cout << "\n4.Tastati 'meniu bauturi' pentru a vedea bauturile.";
        cout << "\n5.Daca doriti sa vedeti produse incadrate in bugetul disponibil scrieti 'sunt sarac'.";

    }

    void afisareLegendaInitiala()
    {
        cout << "\nCOMENZI DISPONIBILE:";
        cout << "\n1.Tastati 'meniu' pentru a vedea meniul.";
        cout << "\n2.Tastati 'administrator' urmat de parola pentru a accesa modul de administrator(pentru uz de verificare al comenzilor, parola e sudoku).";
        cout << "\n3.Tastati 'iesire' pentru a parasi programul.";
        cout << "\nComanda dumneavoastra:";
    }
    void afisareLegendaAdministrator()
    {
        cout << "\nLEGENDA ADMINISTRATOR:";
        cout << "\n1.Tastati 'stoc' pentru a verifica stocul.";
        cout << "\n2.Tastati 'aprovizionare' pentru a creste stocul.";
        cout << "\n3.Tastati 'reducere' pentru a reduce stocul.";
        cout << "\n4.Tastati 'modificare stoc produs' pentru a modifica stocul unui produs specific.";
        cout << "\n5.Tastati 'sunt businessman' ca sa mariti preturile inainte de un eveniment cu 10 lei.";
        cout << "\n6.Tastati 'lasam si noi un pic la pret' ca sa scadeti preturile la o oferta cu 5 lei.";
        cout << "\n7.Tastati 'vizualizare produse' pentru a vedea produsele.";
        cout << "\n8.Tastati 'modificare nume produs' pentru a modifica numele unui produs.";
        cout << "\n9.Tastati 'modificare pret produs' pentru a modifica pretul unui produs.";
        cout << "\n10.Tastati 'verificare' pentru a vedeti daca cantitatea tuturor ingredientelor depaseste o cantitate data.";
        cout << "\n11.Tastati 'comparare ingrediente produse' pentru a verifica daca doua produse au aceleasi ingrediente.";
        cout << "\n12.Tastati 'meniu principal' pentru a va intoarce la meniul principal.";

    }



    ~Restaurant()
    {
        delete[] this->produse;
        this->produse = nullptr;
    }
};



int main()
{
    //INGREDIENTE
    char rosii[] = { "Rosii" }; //se masoara in nr rosii
    char faina[] = { "Faina" }; //se masoara in grame
    char sunca[] = { "Sunca" }; //se masoara in bucati de sunca
    char mozarella[] = { "Mozarella" }; //se masoara in grame
    char oua[] = { "Oua" }; //se masoara in nr oua
    char ardeiIute[] = { "Ardei iute" }; //se masoara in nr ardei
    char salam[] = { "Salam" }; //se masoara in felii salam
    char salamIute[] = { "Salam Iute" }; //la fel
    char ciuperci[] = { "Ciuperci" }; //se masoara in bucati ciuperci
    char paste[] = { "Paste" }; //se masoara in grame
    char pecorino[] = { "Pecorino" }; //se masoara in grame
    char guanciale[] = { "Guanciale" }; //se masoara in grame
    char morcovi[] = { "Morcovi" }; //se masoara in nr morcovi
    char ceapa[] = { "Ceapa" }; // sa masoara in nr cepe
    char vita[] = { "Vita" }; //se masoara in grame
    char unt[] = { "Unt" }; //se masoara in grame
    char lapte[] = { "Lapte" }; // sa masoara in mililitri 
    char zahar[] = { "Zahar" };//se masoara in grame
    char mascarpone[] = { "Mascarpone" };//se masoara in grame
    char piscoturi[] = { "Piscoturi" };//se masoara in grame
    char arome[] = { "Arome" }; //ciocolata, vanilie etc.
    char cafea[] = { "Cafea" }; //se masoara in mililitri
    char lamaie[] = { "Lamaie" }; //se masoara in bucati lamaie
    char apa[] = { "Apa" }; //se masoara in mililitri

    char cofeina[] = { "Cofeina" };
    char alcool[] = { "Alcool - 12%" };


    Ingredient* Rosii;
    Rosii = new Ingredient(rosii);
    Ingredient* Faina;
    Faina = new Ingredient(faina);
    Ingredient* Sunca;
    Sunca = new Ingredient(sunca);
    Ingredient* Mozarella;
    Mozarella = new Ingredient(mozarella);
    Ingredient* Oua;
    Oua = new Ingredient(oua);
    Ingredient* ArdeiIute;
    ArdeiIute = new Ingredient(ardeiIute);
    Ingredient* Salam;
    Salam = new Ingredient(salam);
    Ingredient* SalamIute;
    SalamIute = new Ingredient(salamIute);
    Ingredient* Ciuperci;
    Ciuperci = new Ingredient(ciuperci);
    Ingredient* Paste;
    Paste = new Ingredient(paste);
    Ingredient* Pecorino;
    Pecorino = new Ingredient(pecorino);
    Ingredient* Guanciale;
    Guanciale = new Ingredient(guanciale);
    Ingredient* Morcovi;
    Morcovi = new Ingredient(morcovi);
    Ingredient* Ceapa;
    Ceapa = new Ingredient(ceapa);
    Ingredient* Vita;
    Vita = new Ingredient(vita);
    Ingredient* Unt;
    Unt = new Ingredient(unt);
    Ingredient* Lapte;
    Lapte = new Ingredient(lapte);
    Ingredient* Zahar;
    Zahar = new Ingredient(zahar);
    Ingredient* Piscoturi;
    Piscoturi = new Ingredient(piscoturi);
    Ingredient* Mascarpone;
    Mascarpone = new Ingredient(mascarpone);
    Ingredient* Arome;
    Arome = new Ingredient(arome);
    Ingredient* Cafeaa;
    Cafeaa = new Ingredient(cafea);
    Ingredient* Lamaie;
    Lamaie = new Ingredient(lamaie);
    Ingredient* Apa;
    Apa = new Ingredient(apa);
    Ingredient* Cofeina;
    Cofeina = new Ingredient(cofeina);
    Ingredient* Alcool;
    Alcool = new Ingredient(alcool);

    //STOC DE INGREDIENTE

    Ingredient* ingrediente[] = { Rosii, Faina, Sunca, Mozarella, Oua, ArdeiIute, Salam, SalamIute, Ciuperci, Paste, Pecorino, Guanciale, Morcovi, Ceapa, Vita, Unt, Lapte,
        Zahar, Piscoturi, Mascarpone, Arome, Cafeaa, Lamaie, Apa, Cofeina, Alcool };
    int cantitati[] = { 50, 5000, 70, 3000, 90, 100, 45, 30, 90, 5000, 4000, 10000, 40, 65, 7000, 2000, 10000, 3000, 4000, 4500, 100, 1500, 20, 25000, 500, 500 };
    Stoc* stoc;
    stoc = new Stoc(cantitati, ingrediente);



    //RETETE SI PRODUSE

    Ingredient* ingredienteVin[] = { Alcool };
    int cantitatiNecesareVin[] = { 1 };
    Reteta* RetetaVin;
    RetetaVin = new Reteta(ingredienteVin, cantitatiNecesareVin, 1);
    Produs* Vin;
    Vin = new Produs(RetetaVin, "Bautura Vin", 20);


    Ingredient* ingredienteCafea[] = { Apa, Cofeina };
    int cantitatiNecesareCafea[] = { 50, 1 };
    Reteta* RetetaCafea;
    RetetaCafea = new Reteta(ingredienteCafea, cantitatiNecesareCafea, 2);
    Produs* Cafea;
    Cafea = new Produs(RetetaCafea, "Bautura Cafea", 15);

    Ingredient* ingredienteInghetata[] = { Lapte, Zahar, Arome };
    int cantitatiNecesareInghetata[] = { 200, 20, 1 };
    Reteta* RetetaInghetata;
    RetetaInghetata = new Reteta(ingredienteInghetata, cantitatiNecesareInghetata, 3);
    Produs* Inghetata;
    Inghetata = new Produs(RetetaInghetata, "Inghetata", 12);

    Ingredient* ingredientePizzaDiavola[] = { Rosii, Faina, ArdeiIute, Salam, SalamIute };
    int cantitateNecesarePizzaDiavola[] = { 4, 200, 3, 10, 10 };
    Reteta* RetetaPizzaDiavola;
    RetetaPizzaDiavola = new Reteta(ingredientePizzaDiavola, cantitateNecesarePizzaDiavola, 5);
    Produs* PizzaDiavola;
    PizzaDiavola = new Produs(RetetaPizzaDiavola, "Pizza Diavola", 38);

    Ingredient* ingredienteTiramisu[] = { Oua, Zahar, Piscoturi, Mascarpone, Cafeaa };
    int cantitatiNecesareTiramisu[] = { 1, 20, 80, 100, 10 };
    Reteta* RetetaTiramisu;
    RetetaTiramisu = new Reteta(ingredienteTiramisu, cantitatiNecesareTiramisu, 5);
    Produs* Tiramisu;
    Tiramisu = new Produs(RetetaTiramisu, "Tiramisu", 23);

    Ingredient* ingredienteLasagna[] = { Rosii, Paste, Morcovi, Ceapa, Vita, Lapte, Faina, Unt };
    int cantitatiNecesareLasagna[] = { 5, 200, 1, 1, 200, 400, 150, 50 };
    Reteta* RetetaLasagna;
    RetetaLasagna = new Reteta(ingredienteLasagna, cantitatiNecesareLasagna, 8);
    Produs* Lasagna;
    Lasagna = new Produs(RetetaLasagna, "Lasagna", 50);

    Ingredient* ingredientePasteBolognese[] = { Rosii, Paste, Morcovi, Ceapa, Vita };
    int cantitatiNecesarePasteBolognese[] = { 5, 200, 1, 1, 200 };
    Reteta* RetetaPasteBolognese;
    RetetaPasteBolognese = new Reteta(ingredientePasteBolognese, cantitatiNecesarePasteBolognese, 5);
    Produs* PasteBolognese;
    PasteBolognese = new Produs(RetetaPasteBolognese, "Paste Bolognese", 40);

    Ingredient* ingredientePasteCarbonara[] = { Oua, Paste, Pecorino, Guanciale };
    int cantitatiNecesarePasteCarbonara[] = { 4, 200, 100, 200 };
    Reteta* RetetaPasteCarbonara;
    RetetaPasteCarbonara = new Reteta(ingredientePasteCarbonara, cantitatiNecesarePasteCarbonara, 4);
    Produs* PasteCarbonara;
    PasteCarbonara = new Produs(RetetaPasteCarbonara, "Paste Carbonara", 32);

    Ingredient* ingredientePasteAmatriciana[] = { Rosii, Paste, Guanciale };
    int cantitatiNecesarePasteAmatriciana[] = { 5, 200, 200 };
    Reteta* RetetaPasteAmatriciana;
    RetetaPasteAmatriciana = new Reteta(ingredientePasteAmatriciana, cantitatiNecesarePasteAmatriciana, 3);
    Produs* PasteAmatriciana;
    PasteAmatriciana = new Produs(RetetaPasteAmatriciana, "Paste Amatriciana", 30);

    Ingredient* ingredientePizzaProsciuttoEFunghi[] = { Rosii, Faina, Sunca ,Mozarella, Ciuperci };
    int cantitatiNecesarePizzaProsciuttoEFunghi[] = { 3,200,4,30,10 };
    Reteta* RetetaPizzaProsciuttoEFunghi;
    RetetaPizzaProsciuttoEFunghi = new Reteta(ingredientePizzaProsciuttoEFunghi, cantitatiNecesarePizzaProsciuttoEFunghi, 5);
    Produs* PizzaProsciuttoEFunghi;
    PizzaProsciuttoEFunghi = new Produs(RetetaPizzaProsciuttoEFunghi, "Pizza Prosciutto E Funghi", 40);

    Ingredient* ingredientePizzaProsciutto[] = { Rosii, Faina, Sunca, Mozarella };
    int cantitatiNecesarePizzaProsciutto[] = { 3, 200, 5, 30 };
    Reteta* RetetaPizzaProsciutto;
    RetetaPizzaProsciutto = new Reteta(ingredientePizzaProsciutto, cantitatiNecesarePizzaProsciutto, 4);
    Produs* PizzaProsciutto;
    PizzaProsciutto = new Produs(RetetaPizzaProsciutto, "Pizza Prosciutto", 35);

    Ingredient* ingredientePizzaMargherita[] = { Rosii, Faina, Mozarella };
    int cantitatiNecesarePizzaMargherita[] = { 4, 200, 50 };
    Reteta* RetetaPizzaMargherita;
    RetetaPizzaMargherita = new Reteta(ingredientePizzaMargherita, cantitatiNecesarePizzaMargherita, 3);
    Produs* PizzaMargherita;
    PizzaMargherita = new Produs(RetetaPizzaMargherita, "Pizza Margherita", 30);

    Ingredient* ingredientePizzaMargheritaXXL[] = { Rosii, Faina, Mozarella };
    int cantitatiNecesarePizzaMargheritaXXL[] = { 8, 400, 100 };
    Reteta* RetetaPizzaMargheritaXXL;
    RetetaPizzaMargheritaXXL = new Reteta(ingredientePizzaMargheritaXXL, cantitatiNecesarePizzaMargheritaXXL, 3);
    Produs* PizzaMargheritaXXL;
    PizzaMargheritaXXL = new Produs(RetetaPizzaMargheritaXXL, "Pizza Margherita XXL", 50);


    Ingredient* ingredienteLimonada[] = { Lamaie, Apa };
    int cantitatiNecesareLimonada[] = { 1, 300 };
    Reteta* RetetaLimonada;
    RetetaLimonada = new Reteta(ingredienteLimonada, cantitatiNecesareLimonada, 2);
    Produs* Limonada;
    Limonada = new Produs(RetetaLimonada, "Bautura Limonada", 10);


    //MENIU

    Produs* vectorProduse[] = { PasteCarbonara, PasteBolognese, PasteAmatriciana, Lasagna, PizzaProsciuttoEFunghi, PizzaDiavola, PizzaProsciutto, PizzaMargherita, PizzaMargheritaXXL, Tiramisu, Inghetata, Limonada, Cafea, Vin };
    class Meniu meniu(vectorProduse, 14);

    //RESTAURANT 


    class Restaurant restaurant(vectorProduse, stoc, 14);


    //INTERFATA CU UTILIZATORUL
    string input;
    int inputNumeric = 0;
    cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-BUN VENIT LA RESTAURANTUL 'LA COSTELUS'-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
    cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
    while (true)
    {
        if (input == "meniu principal")
        {
            system("cls");
            cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-BUN VENIT LA RESTAURANTUL 'LA COSTELUS'-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
            cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
        }
        restaurant.afisareLegendaInitiala();
        bool iesireComanda = false;
        getline(cin, input);
        if (input == "meniu")
        {
            system("cls");
            cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-BUN VENIT LA RESTAURANTUL 'LA COSTELUS'-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
            cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
            cout << meniu;
            cout << endl;
            restaurant.afisareLegendaMeniu();
            while (!iesireComanda)
            {

                bool verificare = false;
                cout << "\nComanda dumneavoastra:";
                getline(cin, input);
                if (input == "Pizza Margherita")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }

                }

                if (input == "Pizza Margherita XXL")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }

                }

                else if (input == "Pizza Diavola")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }
                }

                else if (input == "Paste Amatriciana")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }
                }

                else if (input == "Paste Bolognese")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }
                }

                else if (input == "Lasagna")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }
                }

                else if (input == "Inghetata")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }
                }

                else if (input == "Tiramisu")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }
                }

                else if (input == "Bautura Cafea")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }
                }


                else if (input == "Bautura Vin")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }
                }


                else if (input == "Pizza Prosciutto E Funghi")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }
                }

                else if (input == "Pizza Prosciutto")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }
                }
                else if (input == "Paste Carbonara")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }
                }
                else if (input == "Limonada")
                {
                    cout << ("\nCate produse doriti?Introduceti cantitatea:");
                    cin >> inputNumeric;
                    if (inputNumeric > 0)
                    {
                        verificare = restaurant.verificareStoc(input, inputNumeric);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (verificare == true)
                        {
                            cout << "\nComanda a fost realizata cu succes!";

                        }
                        else
                        {
                            cout << "\nComanda nu a putut fi realizata deoarece stocul este insuficient. Incercati alt produs.";
                        }
                    }
                    else
                    {
                        cout << "Cantitate invalida, plasati comanda din nou.";
                    }
                }
                else if (input == "meniu principal")
                {
                    iesireComanda = true;
                }
                else if (input == "sunt sarac")
                {
                    cout << "\nBugetul dumneavoastra:";
                    cin >> inputNumeric;
                    meniu[inputNumeric];
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else if (input == "meniu pizza")
                {
                    meniu();
                }
                else if (input == "meniu bauturi")
                {
                    !meniu;
                }

                else
                {
                    cout << "\nComanda invalida. Incercati din nou.\n";
                }


            }

        }
        else if (input == "iesire")
        {
            cout << "La revedere!";
            break;
        }

        else if (input == "administrator sudoku")
        {
            system("cls");
            cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-BUN VENIT LA RESTAURANTUL 'LA COSTELUS'-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
            cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
            restaurant.afisareLegendaAdministrator();
            while (!iesireComanda)
            {
                cout << "\nComanda dumneavoastra:";
                getline(cin, input);
                if (input == "stoc")
                {
                    cout << stoc;
                }
                else if (input == "vizualizare produse")
                {
                    cout << restaurant;
                }

                else if (input == "comparare ingrediente produse")
                {
                    bool test2;
                    test2 = restaurant.verificareProdus();
                    if (test2 == 0)
                    {
                        cout << "\nProdusele nu au aceleasi ingrediente.";
                    }
                    else
                    {
                        cout << "\nProdusele au aceleasi ingrediente!";
                    }
                }
                else if (input == "verificare")
                {
                    bool test;
                    cout << "\nNumarul cu care doriti sa comparati:";
                    cin >> inputNumeric;
                    test = restaurant > inputNumeric;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (test == true)
                    {
                        cout << "Stocul este suficient de mare.";
                    }
                    if (test != true)
                    {
                        cout << "Unul sau mai multe ingrediente nu au cantitatea necesara.";
                    }
                }
                else if (input == "meniu principal")
                {
                    iesireComanda = true;
                }
                else if (input == "modificare nume produs")
                {
                    cin >> restaurant;
                }

                else if (input == "modificare pret produs")
                {
                    cin >> meniu;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                }
                else if (input == "aprovizionare")
                {
                    cout << "\nIntroduceti cantitatea cu care doriti sa aprovizionati:";
                    cin >> inputNumeric;
                    *stoc += inputNumeric;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else if (input == "reducere")
                {
                    cout << "\nIntroduceti cantitatea cu care va fi redus stocul:";
                    cin >> inputNumeric;
                    *stoc -= inputNumeric;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                else if (input == "sunt businessman")
                {
                    ++restaurant;
                    
                }
                else if (input == "lasam si noi un pic la pret")
                {
                    --restaurant;
                    cout << "\nPretul a fost modificat cu succes.";
                }

                else if (input == "modificare stoc produs")
                {
                    cin >> *stoc;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    cout << "\nComanda invalida. Incercati din nou.";
                }
            }
        }

        else
        {
            cout << "\nComanda invalida. Incercati din nou.";
        }
    }

    //DEZALOCARE MEMORIE

    delete Rosii;
    delete Faina;
    delete Sunca;
    delete Mozarella;
    delete Oua;
    delete ArdeiIute;
    delete Salam;
    delete SalamIute;
    delete Ciuperci;
    delete Paste;
    delete Pecorino;
    delete Guanciale;
    delete Morcovi;
    delete Ceapa;
    delete Vita;
    delete Unt;
    delete Lapte;
    delete Zahar;
    delete Piscoturi;
    delete Mascarpone;
    delete Arome;
    delete Cafeaa;
    delete Lamaie;
    delete Apa;
    delete Cofeina;
    delete Alcool;
    delete stoc;
    delete RetetaVin;
    delete Vin;
    delete RetetaCafea;
    delete Cafea;
    delete RetetaPizzaDiavola;
    delete PizzaDiavola;
    delete RetetaTiramisu;
    delete Tiramisu;
    delete RetetaLasagna;
    delete Lasagna;
    delete RetetaPasteBolognese;
    delete PasteBolognese;
    delete RetetaPasteCarbonara;
    delete PasteCarbonara;
    delete RetetaPasteAmatriciana;
    delete PasteAmatriciana;
    delete RetetaPizzaProsciuttoEFunghi;
    delete PizzaProsciuttoEFunghi;
    delete RetetaPizzaProsciutto;
    delete PizzaProsciutto;
    delete RetetaPizzaMargherita;
    delete PizzaMargherita;
    delete RetetaPizzaMargheritaXXL;
    delete PizzaMargheritaXXL;
    delete RetetaLimonada;
    delete Limonada;
    return 0;
}