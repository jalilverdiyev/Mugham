#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
#include <experimental/algorithm>
using namespace std;

class Mugham
{

private:
    vector<string> shobeler;
    string name;

public:
    int size;
    Mugham(string mName, vector<string> shobe_siyahisi)
    {
        name = mName;
        shobeler = shobe_siyahisi;
        size = shobe_siyahisi.size();
    }

    string get_mugham()
    {
        return name;
    }

    vector<string> get_shobes()
    {
        return shobeler;
    }
    string get_shobe(int indis)
    {
        return shobeler[indis];
    }
};

vector<string> createChoices(vector<string> raw_choices)
{
    random_shuffle(raw_choices.begin(), raw_choices.end());
    return raw_choices;
}

void ask(vector<Mugham> v)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::uniform_int_distribution<int> distr_mugham(0, (v.size() - 1));
    int randomMugham = distr_mugham(e);
    std::uniform_int_distribution<int> distr_indis(0, ((v[randomMugham].size - 1)));
    int randomIndis = distr_indis(e);
    // int afterorBefore = 1 + rand() % (2 - 1 + 1);
    string question = v[randomMugham].get_shobe(randomIndis);
    string rightAnswer;
    int indexofRightAnswer;

    if (randomIndis == 0)
    {
        cout << "What comes after " << question << " in " << v[randomMugham].get_mugham() << endl;
        rightAnswer = v[randomMugham].get_shobe(randomIndis + 1);
        indexofRightAnswer = randomIndis + 1;
    }
    else if (randomIndis == ((v[randomMugham].size) - 1))
    {
        cout << "What comes before " << question << " in " << v[randomMugham].get_mugham() << endl;
        rightAnswer = v[randomMugham].get_shobe(randomIndis - 1);
        indexofRightAnswer = randomIndis - 1;
    }
    else
    {
        std::uniform_int_distribution<int> randomAfterorBefore(0, 1); // After->0,Before->1
        int afterorBefore = randomAfterorBefore(e);
        if (afterorBefore == 0)
        {
            cout << "What comes after " << question << " in " << v[randomMugham].get_mugham() << endl;
            rightAnswer = v[randomMugham].get_shobe(randomIndis + 1);
            indexofRightAnswer = randomIndis + 1;
        }
        else
        {
            cout << "What comes before " << question << " in " << v[randomMugham].get_mugham() << endl;
            rightAnswer = v[randomMugham].get_shobe(randomIndis - 1);
            indexofRightAnswer = randomIndis - 1;
        }
    }
    size_t numberofElements = 4;
    vector<string> raw = v[randomMugham].get_shobes();
    raw.erase(raw.begin() + indexofRightAnswer);
    vector<string> lraw = {rightAnswer};
    std::experimental::fundamentals_v2::sample(raw.begin(), raw.end(), std::back_inserter(lraw), numberofElements, std::mt19937{std::random_device{}()});
    vector<string> final_choices = createChoices(lraw);
    vector<char> variants = {'a', 'b', 'c', 'd', 'e'};
    char answer;
    for (int j = 0; j < 5; j++)
    {
        cout << variants[j] << ") " << final_choices[j] << "\t";
    }
    string chosen;
    cout << endl
         << "Your answer: ";
    cin >> answer;
    switch(answer)
    {
        case 'a':
            chosen = final_choices[0];
            break;            
        case 'b':
            chosen = final_choices[1];
            break;
        case 'c':
            chosen = final_choices[2];
            break;
        case 'd':
            chosen = final_choices[3];
            break;
        case 'e':
            chosen = final_choices[4];
            break;
        default:
            cout<<"Wrong input"<<endl;
            break;
    }
    if(chosen == rightAnswer)
    {
        cout<<"Correct"<<endl;
    }
    else
    {
        cout<<"False"<<endl;
    }
}


int main()
{
    Mugham Rast("Rast", {"Berdash", "Maye", "Ussaq", "Huseyni", "Vilayeti", "Dilkes", "Kurdu", "Shikeste", "Eraq", "Pancigah", "Rak", "Qarai"});
    Mugham Chargah("Chargah", {"Berdash", "Maye", "Basti-nigar", "Hisar", "Muxalif", "Mansuriyye", "Maghrur"});
    Mugham Shur("Shur", {"Berdash", "Maye", "Shurshahnaz", "Bayati-turk", "Shikeste", "Simayi-shems", "Hicaz", "Sarenc", "Qamangiz", "Ayaq"});
    Mugham BayatiShiraz("Bayati-Shiraz", {"Berdash", "Maye", "Nishibi-ferez", "Bayati-Isfahan", "Zil bayati-shiraz", "Xaveran", "Uzzal", "Dilruba", "Ayaq"});
    Mugham ZabulSegah("Zabul-Segah", {"Berdash", "Maye-Zabul", "Manendi-Muxalif", "Orta-Segah", "Zil-Zabul", "Hisar", "Muxalif", "Zabula-Ayaq"});
    Mugham Humayun("Humayun", {"Berdash", "Maye", "Feili", "Molevi", "Shushter", "Tarkib", "Bidad", "Ayaq"});

    ask({Rast, Chargah, Shur, BayatiShiraz, ZabulSegah, Humayun});

    return 0;
}